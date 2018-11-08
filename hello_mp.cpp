#include<stdio.h>
#include<mpi.h>
#include<string.h>
#define max_size 100

int main(void)
{
  int myrank;
  int mysize;
  MPI_Init(NULL,NULL);
  MPI_Comm_size(MPI_COMM_WORLD£¬&mysize);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  printf("hello word!form %d of %d processors\n",myrank,mysize);
  MPI_Finalize();
  return 0;
}