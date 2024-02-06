/* sample hello world program  *
 *  C Michael Hanke 2006-10-19 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include <complex.h>    /* Standard Library of Complex Numbers */

int w = 2048;
int h = 2048;
int N = 256;
int b = 2;
int size = 16;
int chunk_size = 128;

int calc_pixel(double complex d) {
    int count = 1;
    double complex z = 0;

    while ((cabs(z) < b) && (count < N)) {
        z = z*z + d;
        count++;
    }
    return count;
}

int* mandelbrot(int rank) {
    int x, x_low,x_high,y;
    double dreal,dimag;
    double dx = 2*b/(w-1);
    double dy = 2*b/(h-1);
    double complex d;
    int* colvals = (int*)malloc(sizeof(int)*h*chunk_size);

    x_low = chunk_size * rank;
    // x_high = (chunk_size+1)*rank - 1;

    for (x=0;x<chunk_size;x++) {
        dreal = (x+x_low)*dx - b;
        for (y=0;y<h;y++) {
            dimag = y*dy-b;
            d = dreal + I*dimag;    
            colvals[x*chunk_size+y] = calc_pixel(d);
        }
    }  
    return colvals;
}

int main(int argc, char **argv) {
    int rank, size, tag, rc, i;
    MPI_Status status;
    char message[20];
    int rbuf[(size*h*chunk_size)];

    rc = MPI_Public/helloC.cInit(&argc, &argv);
    rc = MPI_Comm_size(MPI_COMM_WORLD, &size);
    rc = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int* mandel = mandelbrot(rank);
    printf("Rank %d address: %p",rank,mandel);

    // if (rank==0) {
    //     rbuf = (int *)malloc(size*sizeof(int)*h*chunk_size); 
    // }
    rc = MPI_Gather(mandel, h*chunk_size, MPI_INT, rbuf, h*chunk_size, MPI_INT, 0, MPI_COMM_WORLD); 


	// strcpy(message, "Hello, world");
	// for (i = 1; i < size; ++i)
	//     rc = MPI_Send(message, 13, MPI_CHAR, i, tag, MPI_COMM_WORLD);
    // }
    // else
	// rc = MPI_Recv(message, 13, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);

    // printf("node %d : %.13s\n", rank, message);
    
    rc = MPI_Finalize();
    return 0;
}