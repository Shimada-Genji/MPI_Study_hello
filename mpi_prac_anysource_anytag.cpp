#include<stdio.h>
#include<mpi.h>
#include<string.h>
#define maxsize 100000
#define tag_num 5
#define namesize 100
int main(void)
{
  int mysize,myrank;
  int NameLen;
  char MyProcessorsName;
  char message[maxsize];
  MPI_Init(NULL,NULL);
  MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
  MPI_Comm_size(MPI_COMM_WORLD,&mysize);
  MPI_Get_processor_name(&MyProcessorsName,&NameLen);
  if(myrank!=0)
  {
   for(int tag=0;tag<tag_num;tag++)
   {
    sprintf(message,"the NO.%d message from %d of %d processors to 0 ! my processor is %s !\n",tag,myrank,mysize,MyProcessorsName);//derectly write send_source&send_tag to the message.(status.MPI_SOURCE/status.MPI_TAG)
    MPI_Send(message,strlen(message)+1,MPI_CHAR,0,tag,MPI_COMM_WORLD);

   }
  }
  else
  {
    printf("hello im processors 0 !\n");
     for(int mes=0;mes<tag_num*(mysize-1);mes++)
	{
       MPI_Recv(message,maxsize,MPI_CHAR,MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
       printf("%s\n",message);
	}
     

  }
MPI_Finalize();

}
