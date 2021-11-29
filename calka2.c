#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "mpi.h"

double funct(double x){
    return x*x;
}

double Trapez(double a, int proc_nr, double krok, int proc_il){
    double wynik = 0;
    if(proc_nr == 0 || proc_nr == proc_il) {
        wynik = funct(a+proc_nr*krok)/2;
    } else {
        wynik = funct(a+proc_nr*krok);
    }
    return wynik;
}

double Prostokat(double a, int proc_nr, double krok){
	double wynik = 0;
    wynik = funct(a+proc_nr*krok);
    return wynik;
}

int main( int argc, char **argv ){   
    int proc_nr;
    double wynikCalkowania = 0;
    double poleJednegoKawalka = 0;
    int proc_il;
    double pocz = 0;
    double kon = 2;
    double krok = (kon - pocz)/proc_il;
    MPI_Status status;
    MPI_Init( &argc, &argv );
    MPI_Comm_size( MPI_COMM_WORLD, &proc_il);
    MPI_Comm_rank( MPI_COMM_WORLD, &proc_nr);
    if(proc_nr == proc_il-1){
        poleJednegoKawalka = Trapez(pocz, proc_nr+1, krok, proc_il); // lub zamienic na Prostokat(pocz, proc_nr+1, krok);
        wynikCalkowania += krok*poleJednegoKawalka;
        printf("NR: %d poleJednegoKawalka = %f   wynikCalkowania = %f \n", proc_nr, poleJednegoKawalka, wynikCalkowania);
        MPI_Send(&wynikCalkowania, 1, MPI_DOUBLE, proc_nr-1, 7, MPI_COMM_WORLD);
    } 
    if(proc_nr != proc_il-1){
        MPI_Recv(&wynikCalkowania, 1, MPI_DOUBLE, proc_nr+1, 7, MPI_COMM_WORLD, &status);
        poleJednegoKawalka = Trapez(pocz, proc_nr+1, krok, proc_il); //lub zamienic na Prostokat(pocz, proc_nr+1, krok);
        wynikCalkowania += krok*poleJednegoKawalka;
        printf("Nr procesu: %d poleJednegoKawalka = %f   wynikCalkowania = %f \n", proc_nr, poleJednegoKawalka, wynikCalkowania);
        if(proc_nr != 0){
            MPI_Send(&wynikCalkowania, 1, MPI_DOUBLE, proc_nr-1, 7, MPI_COMM_WORLD);
        }
    } 
    MPI_Finalize();
    return 0;
}