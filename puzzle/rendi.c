/*********************************************************************

  rendi.c

 ******************************************************************/

#include <stdio.h>
#include <sys/time.h>
#include <omp.h>

#define VECES 5
int veces;

// Declaracion de constantes y variables

#define N1 3558000
#define N2 3980000
#define N3 3000000

struct timeval 	t0, t1;

int	i, j, k;
int	sum, x;

int	A[N1], B[N1], E[N1];
int	C[N2], J[N2];
int	H[N3], N[N3];


// RUTINAS AUXILIARES

void TrazaTiempo(char * pTexto, struct timeval *pt0, struct timeval *pt1) {
	double tej;

	tej = (pt1->tv_sec - pt0->tv_sec) + (pt1->tv_usec - pt0->tv_usec) / 1e6;
	printf("%s = %10.3f ms\n",pTexto, tej*1000);
}

void SumarVector(char * pTexto, int *v, int n) {
	double suma=0;
	int i;

	for (i=0;i<n;i++) {
		suma+=v[i];
	}

	printf ("La suma del vector %s es %.1f\n", pTexto, suma);

}

// PROGRAMA PRINCIPAL

int main (int argc, char **argv) {

	for (veces=1; veces<VECES; veces++) {

		//Inicializaciones

		for(i=0; i<N1; i++) {
			A[i] = 0;
			B[i] = N1-i+2;
			E[i] = 0;
		}

		for(i=0; i<N2; i++) {
			C[i] = (i+20) / 10;
			J[i] = 6;
		}

		for(i=0; i<N3; i++) {
			H[i] = 1;
			N[i] = 3;
		}

		// Comienzo del programa

		printf("\n");

		gettimeofday(&t0, 0);
		#pragma omp parallel for private(x)
		for(i=1; i<N1; i++) {
			x = B[i] / (B[i] + 1);
			A[i] = (x + B[i] + 1) / 10;
			E[i] = (x * x / (x * x + 1))*(x * x / (x * x + 1));
		}
		gettimeofday(&t1, 0);
		TrazaTiempo("T1", &t0, &t1);

		gettimeofday(&t0, 0);
		#pragma omp parallel for
		for(i=1; i<N2; i++) {
			C[i] = C[i] / (J[i] + 1);
			J[i] = C[i] * J[i] / (C[i] * J[i] + 1);
		}
		gettimeofday(&t1, 0);
		TrazaTiempo("T2", &t0, &t1);

		gettimeofday(&t0, 0);
		// Hay una dependencia de datos, no se puede paralelizar
		for(i=2; i<N3; i++) {
			H[i] = 35 / (7/N[i-1] + 2/H[i]);
			N[i] = N[i] / (H[i-1]+2) + 3 / N[i];
		}
		gettimeofday(&t1, 0);
		TrazaTiempo("T3", &t0, &t1);

	} //fin del for VECES

	// RESULTADOS FINALES: se imprimen las sumas de los vectores

	printf("\n\n");
	SumarVector("A", A, N1);
	SumarVector("E", E, N1);
	SumarVector("C", C, N2);
	SumarVector("J", J, N2);
	SumarVector("H", H, N3);
	SumarVector("N", N, N3);

	return 0;

}
