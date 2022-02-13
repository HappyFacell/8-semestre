#define _GNU_SOURCE //para usar clone
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <signal.h>
#include <sched.h>
#include <malloc.h>
#include <sys/wait.h>
#include <math.h>
#define iteraciones 2000000000
//1024*64 (64kb)
#define FIBER_STACK 1024*64
//Los núcleos de la máquina virtual.
#define NTHREADS 4

//donde vamos a sumar el resultado de las iteraciones de la serie de Leibniz.
double acum_global;

//La función que vamos a clonar, cuyo resultado se guardará en acum_global.
int calcularPi(void* n);

int main(){
	void* stack;
	pid_t pid;

    //para calcular el tiempo
	long long start_ts;
	long long stop_ts;
	long long elapsed_time;
	long lElapsedTime;
	struct timeval ts;
	
	int i, status, params[NTHREADS];
	double sum = 0;
	double num_elevado, pi;
	
	stack = malloc(FIBER_STACK * NTHREADS);
	if(stack == 0){
		perror("malloc error");
		exit(1);
	}
	
    //para calcular el tiempo
	gettimeofday(&ts, NULL);
    start_ts = ts.tv_sec; // Tiempo inicial
	
    //un ciclo que se ejecuta cuatro veces para llenar cada núcleo con la función calcularPi clonada y que cada núcleo se encargue de calcular el resultado.
	for(i=0; i<NTHREADS; i++){
		params[i]=i;
		pid = clone(calcularPi,
		 (char*) stack + FIBER_STACK*(i+1),
        //estas señales hacen que se comparta la memoria, la información del sistema, la file descriptor table
		SIGCHLD |CLONE_FS|CLONE_FILES|CLONE_SIGHAND|CLONE_VM,
		 &params[i]);

        //si pid es -1 no funcionó el clone
		if(pid == -1){
			perror("clone");
			exit(2);
		}
        usleep(1000);
	}
	
	for(i=0; i<NTHREADS; i++){
		pid=wait(&status);
		if(pid == -1){
			perror("waitpid");
			exit(3);
		}
	}
	
    gettimeofday(&ts, NULL);
    stop_ts = ts.tv_sec; // Tiempo final
    elapsed_time = stop_ts - start_ts;
	pi = acum_global * 4;
	
    printf("PI = %1.20lf\n", pi);
	printf("------------------------------\n");
	elapsed_time = (int) (stop_ts - start_ts);
    printf("Tiempo total: %lld segundos.\n", elapsed_time);
	
	free(stack);
	
	return 0;
}

int calcularPi(void* n)
{
	double num_elevado = 0;
	double sum;
	int start = *((int *) n)*(iteraciones/NTHREADS);
	int end = start+(iteraciones/NTHREADS);
    for(int i=start; i<end; i++){
        num_elevado += pow(-1,i)/(2*i+1);
    }
    acum_global += num_elevado;

}