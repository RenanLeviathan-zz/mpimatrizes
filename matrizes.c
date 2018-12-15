#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#define ORDEM 500
int main(int argc, char** argv){
MPI_Init(NULL, NULL);
int world_rank;
MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
int world_size;
MPI_Comm_size(MPI_COMM_WORLD, &world_size);
int a[ORDEM][ORDEM];
int b[ORDEM][ORDEM];
int c[ORDEM][ORDEM];
if (world_size != 4 ) {
		fprintf(stderr, "4 processos são necessários");
		MPI_Abort(MPI_COMM_WORLD, 1);
}
//função de cópia de submatrizes
void copy(int M1[][ORDEM], int M2[][ORDEM], int l, int c, int L, int C){
	for(int i=l;i<L;i++){
		for(int j=c;j<++C;j++){
			M1[i][j]=M2[i][j];
		}
	}
} 

void soma(int res[][ORDEM], int a[][ORDEM], int b[][ORDEM], int i, int I, int j, int J){
	for(int k=i;k<I;k++){
		for(int l=j;l<J;l++){
			res[k][l] = a[k][l]+b[k][l];
		}
	}
}

void mostra(int m[ORDEM][ORDEM]){
for(int i=0;i<ORDEM;i++){
  for(int j=0;j<ORDEM;j++){
   printf("%i ",c[i][j]);
  }
printf("\n");
 }
}
for(int i=0;i<ORDEM;i++){
 for(int j=0;j<ORDEM;j++){
  a[i][j]=1;
  b[i][j]=1;
  c[i][j]=0;
 }
}

if(world_rank == 0){
 soma(c,a,b,0,ORDEM/2,0,ORDEM/2);
//envia o endereço da matriz resultado
for(int i=1;i<=3;i++){
MPI_Send(c, ORDEM*ORDEM, MPI_INT, i, 0, MPI_COMM_WORLD);
MPI_Recv(c, ORDEM*ORDEM, MPI_INT, i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
}
//exibindo Resultado final
mostra(c);
}
if(world_rank == 1){
MPI_Recv(c, ORDEM*ORDEM, MPI_INT, 0, 0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
soma(c,a,b,0,ORDEM/2,ORDEM/2,ORDEM);
MPI_Send(c, ORDEM*ORDEM, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
if(world_rank == 2){
MPI_Recv(c, ORDEM*ORDEM, MPI_INT, 0, 0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
soma(c,a,b,ORDEM/2,ORDEM,0,ORDEM/2);
MPI_Send(c, ORDEM*ORDEM, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
if(world_rank == 3){
MPI_Recv(c, ORDEM*ORDEM, MPI_INT, 0, 0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
soma(c,a,b,ORDEM/2,ORDEM,ORDEM/2,ORDEM);
MPI_Send(c, ORDEM*ORDEM, MPI_INT, 0, 0, MPI_COMM_WORLD);
}
MPI_Finalize();
}

