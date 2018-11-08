#include<stdio.h>
#include"mpi.h"
int main(void)
{
  int rank,value,size;
  MPI_Status status;
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  do{
    if(rank==0){
      fprintf(stderr, "\nplesase give new value = ");
      scanf("%d",&value);
      fprintf(stderr, "%d  read <-<- (%d)\n",rank,value);
      if(size>1){
        MPI_Send(&value,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        fprintf(stderr, "%d send (%d)->-> %d \n",rank,value,rank+1);
      }
    }
    else{
      MPI_Recv(&value,1,MPI_INT,rank-1,0,MPI_COMM_WORLD,&status);
      fprintf(stderr, "%d recieve value(%d) <-<- %d\n",rank,value,rank-1);
      if(rank<size-1){
        MPI_Send(&value,1,MPI_INT,rank+1,0,MPI_COMM_WORLD);
        fprintf(stderr, "%d send (%d) ->-> %d\n",rank,value,rank+1);
      }

    }
  MPI_Barrier(MPI_COMM_WORLD);
} while(value>=0);
MPI_Finalize();

}
