#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "mpi.h"

int main( int argc, char **argv ){
int proc_nr;
double wynik = 0;
int proc_il;
MPI_Status status;
MPI_Init( &argc, &argv );
MPI_Comm_size( MPI_COMM_WORLD, &proc_il);
MPI_Comm_rank( MPI_COMM_WORLD, &proc_nr);
if(proc_nr == 0){
    wynik += 4*(pow(-1, proc_nr)/(2*(proc_nr+1)-1));
    printf("NR: %d pi = %f\n", proc_nr, wynik);
    MPI_Send(&wynik, 1, MPI_DOUBLE, proc_nr+1, 7, MPI_COMM_WORLD);
}

if(proc_nr != 0){
    MPI_Recv(&wynik, 1, MPI_DOUBLE, proc_nr-1, 7, MPI_COMM_WORLD, &status);
    wynik += 4*(pow(-1, proc_nr)/(2*(proc_nr+1)-1));
    printf("NR: %d pi = %f\n", proc_nr, wynik);
    if(proc_nr != proc_il-1){
        MPI_Send(&wynik, 1, MPI_DOUBLE, proc_nr+1, 7, MPI_COMM_WORLD);
    }
}
MPI_Finalize();
return 0;
}