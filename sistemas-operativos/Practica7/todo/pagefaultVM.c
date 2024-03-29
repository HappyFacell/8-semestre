#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <mmu.h>

#define NUMPROCS 4
#define PAGESIZE 4096
#define PHISICALMEMORY 12 * PAGESIZE
#define TOTFRAMES PHISICALMEMORY / PAGESIZE
#define RESIDENTSETSIZE PHISICALMEMORY / (PAGESIZE * NUMPROCS)

extern char *base;
extern int framesbegin;
extern int idproc;
extern int systemframetablesize;
extern int ptlr;

extern struct SYSTEMFRAMETABLE *systemframetable;
extern struct PROCESSPAGETABLE *ptbr;

int getfreeframe();
int searchvirtualframe();
int getlru(); // Cambiamos por lru en lugar de fifo para mayor eficiencia

int pagefault(char *vaddress)
{
    int i;
    int frame, vframe;
    long pag_a_expulsar;
    int fd;
    char buffer[PAGESIZE];
    int pag_del_proceso;

    // A partir de la dirección que provocó el fallo, calculamos la página
    pag_del_proceso = (long)vaddress >> 12;
    // Si la página del proceso está en un marco virtual del disco
    //
    if (ptbr[pag_del_proceso].framenumber >= (framesbegin + TOTFRAMES))
    {
        // Lee el marco virtual al buffer
        vframe = (ptbr + pag_del_proceso)->framenumber;
        readblock(buffer, vframe);
        // Libera el frame virtual
        systemframetable[vframe].assigned = 0;
    }
    // Cuenta los marcos asignados al proceso
    i = countframesassigned();
    // Si ya ocupó todos sus marcos, expulsa una página
    if (i >= RESIDENTSETSIZE)
    {
        // Buscar una página a expulsar
        pag_a_expulsar = getlru();
        // Poner el bitde presente en 0 en la tabla de páginas
        (ptbr + pag_a_expulsar)->presente = 0;
        // Si la página ya fue modificada, grábala en disco
        if ((ptbr + pag_a_expulsar)->modificado == 1)
        {
            // Escribe el frame de la página en el archivo de respaldo y pon en 0 el bit de modificado
            frame = (ptbr + pag_a_expulsar)->framenumber;
            saveframe(frame);
            (ptbr + pag_a_expulsar)->modificado = 0;
        }

        // Busca un frame virtual en memoria secundaria
        vframe = searchvirtualframe();
        // Si no hay frames virtuales en memoria secundaria regresa error
        if (vframe == -1)
        {
            return -1;
        }
        // Copia el frame a memoria secundaria, actualiza la tabla de páginas y libera el marco de la memoria principal
        frame = (ptbr + pag_a_expulsar)->framenumber;
        copyframe(frame, vframe);
        (ptbr + pag_a_expulsar)->presente = 0;
        (ptbr + pag_a_expulsar)->framenumber = vframe;
        systemframetable[frame].assigned = 0;
    }

    // Busca un marco físico libre en el sistema
    frame = getfreeframe();

    // Si no hay marcos físicos libres en el sistema regresa error
    if (frame == -1)
    {
        return -1;// Regresar indicando error de memoria insuficiente
    }

    // Si la página estaba en memoria secundaria
    if ((ptbr + pag_del_proceso)->presente == 0 && (ptbr + pag_del_proceso)->framenumber >= 11)
    {
        // Cópialo al frame libre encontrado en memoria principal y transfiérelo a la memoria física
        writeblock(buffer, frame);
        loadframe(frame);
    }

    // Poner el bit de presente en 1 en la tabla de páginas y el frame
    (ptbr + pag_del_proceso)->presente = 1;
    (ptbr + pag_del_proceso)->framenumber = frame;

    systemframetable[frame].assigned = 1;

    return 1; // Regresar todo bien
}

int getfreeframe()
{
    // Encontrar marco no asignado
    for (int i = framesbegin; i < (2 * systemframetablesize) + framesbegin; i++)
    {
        if (!systemframetable[i].assigned)
        {
            systemframetable[i].assigned = 1;
            return i;
        }
    }
    return -1;
}

int searchvirtualframe()
{
    for (int i = framesbegin; i < (2 * systemframetablesize) + framesbegin; i++)
    {
        if (!systemframetable[i].assigned)
        {
            systemframetable[i].assigned = 1;
            return i;
        }
    }
    return -1;
}

int getlru()
{
    int i = 0;
    int oldest;
    unsigned long fFrame;

    while (!ptbr[i].presente && i < ptlr)
        i++;

    if (i == ptlr)
        return -1;

    // ver el frame más viejo mediante tlastaccess
    fFrame = ptbr[i].tlastaccess;
    oldest = i;

    for (int j = 0; j < ptlr; j++)
    {
        if (ptbr[j].presente && ptbr[j].tlastaccess > fFrame)
        {
            fFrame = ptbr[i].tlastaccess;
            oldest = i;
        }
    }
    return oldest;
}