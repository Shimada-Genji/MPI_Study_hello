#include "mpi.h"
#include<stdio.h>
#include<stdlib.h>
void Hello(void);
int main(void)
{
  int rank,option,size;
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&rank);
  MPI_Comm_size(MPI_COMM_WORLD,&size);
  if(size<2){
    fprintf(stderr, "systest requires at least 2 processors\n");
    MPI_Abort(MPI_COMM_WORLD,1);
  }
  fprintf(stderr, "I am processor %d\n",rank);
  MPI_Barrier(MPI_COMM_WORLD);
  Hello();
  MPI_Finalize();

  
}
void Hello(void)
{
  int nproc,me;
  int type=1;
  int buffer[2],node;
  MPI_Status status;
  MPI_Comm_rank(MPI_COMM_WORLD,&me);
  MPI_Comm_size(MPI_COMM_WORLD,&nproc);
  if(me==0){
    printf("\nhello test from all to all\n");
    fflush(stdout);
  }
  for (node=0;node<nproc;node++)//every processors send a buffer message to other processors(node)
  {
    if(node!=me)
    {
      buffer[0]=me;
      buffer[1]=node;
      MPI_Send(buffer,2,MPI_INT,node,type,MPI_COMM_WORLD);//send to all node
      MPI_Recv(buffer,2,MPI_INT,node,type,MPI_COMM_WORLD,&status);//recieve form all node
      if((buffer[0]!=node)||(buffer[1]!=me)){
        (void)fprintf(stderr, "Hello:%d!=%d or %d!=%d\n",buffer[0],node,buffer[1],me);
        printf("Mismarch on hello processor ids;node= %d\n",node);
      }
      
      printf("hello from %d to %d\n",me,node);
      fflush(stdout);
    }
  }
}
