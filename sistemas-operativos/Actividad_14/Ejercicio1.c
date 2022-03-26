#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <libsem.h>

#define PLAYERS 4

SEMAPHORE xmut;
SEMAPHORE block;

int gturno = 0;

void cwait()
{
    signalsem(&exmut);
    waitsem(&block);
    waitsem(&exmut);
}

void cnotifyAll()
{
    for (int i = 0; i < bloqueados(&block); i++)
    {
        signalsem(&block)
    }
}

void esperar_turno(int turno)
{
    waitsem(&exmut);
    while (turno != gturno)
    {
        cwait();
    }
    signalsem(&exmut);
}

void ceder_turno(int turno)
{
    waitsem(&exmut);
    gturno = turno;
    cnotifyAll();
    signalsem(&exmut);
}

void jugador(int i)
{
    int next = (i + 1) % 4;
    while (1)
    {
        esperar_turno(i);
        hacer_jugada();
        ceder_turno(next);
    }
}
int main()
{
    initsem(&exmut, 1);
    initsem(&block,0);
    cobegin
    {
        jugador(0);
        jugador(1);
        jugador(2);
        jugador(3);
    }
    return 0;
}
