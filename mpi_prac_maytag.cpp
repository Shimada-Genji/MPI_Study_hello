#include<stdio.h>
#include<mpi.h>
#include<string.h>
#define maxsize 100
int main(void)
{
  int mysize,myrank;
  char message[maxsize];
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  MPI_Comm_size(MPI_COMM_WORLD,&mysize);
  if(myrank!=0)
  {
   for(int tag=0;tag<5;tag++)
   {
    sprintf(message,"the NO.%d message from %d of %d processors to 0 !\n",tag,myrank,mysize);
    MPI_Send(message,strlen(message)+1,MPI_CHAR,0,tag,MPI_COMM_WORLD);

   }
  }
  else
  {
    printf("hello im processors 0 !\n");
    for(int i=1;i<mysize;i++)
    {
     for(int rec_tag=0;rec_tag<5;rec_tag++)
     {
      MPI_Recv(message,maxsize,MPI_CHAR,i,rec_tag,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      printf("%s\n",message);
     }
    }

  }
MPI_Finalize();

}
