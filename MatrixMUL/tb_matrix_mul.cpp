#include <stdio.h>
#include <stdint.h>
#include <sys/time.h>
#include <stdlib.h>
#define lm 8
#define ln 8
#define lp 8
#define M (1<<lm)
#define N (1<<ln)
#define P (1<<lp)
#define PRINT_RESULTS false

void MATRIX_MUL(uint8_t A[N][M], uint8_t B[M][P], uint32_t C[N][P]);

void sw_MATRIX_MUL(uint8_t A[N][M], uint8_t B[M][P], uint32_t C[N][P]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < P; j++){
			int result=0;
	        for(int k = 0; k < M; k++){
	            result += (uint32_t)(A[i][k] * B[k][j]);
	        }
	        C[i][j] = result;
	    }
	}
}

int main(){
	struct timeval start;
	struct timeval end;
	srand(1);
	uint8_t A[N][M];
	uint8_t B[M][P];
	uint32_t C[N][P];
	uint32_t test_C[N][P];
	for(int i=0;i<N;i++){
		for(int j=0;j<M;j++){
			A[i][j] = (uint8_t)rand() % 256;
		}
	}
	for(int i=0;i<M;i++){
		for(int j=0;j<P;j++){
			B[i][j] = (uint8_t)rand() % 256;
		}
	}
	MATRIX_MUL(A,B,C);
	gettimeofday(&start,NULL);
	sw_MATRIX_MUL(A,B,test_C);
	gettimeofday(&end,NULL);
	printf("SW TIME: %d us\n",1000000*(end.tv_sec-start.tv_sec)+end.tv_usec-start.tv_usec);

	int flag=0;
	for(int i=0;i<N;i++){
		for(int j=0;j<P;j++){
			if(C[i][j]!=test_C[i][j]){
				flag=1;
			}
		}
	}
	if(PRINT_RESULTS){
		printf("\nMATRIX A:\n");
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				printf("%3d ",A[i][j]);
			}
			printf("\n");
		}
		printf("\nMATRIX B:\n");
		for(int i=0;i<M;i++){
			for(int j=0;j<P;j++){
				printf("%3d ",B[i][j]);
			}
			printf("\n");
			}
		printf("\nMATRIX C:\n");
		for(int i=0;i<N;i++){
			for(int j=0;j<P;j++){
				printf("%10d ",C[i][j]);
				}
		printf("\n");
		}
	}


	if(flag==0){
		printf("Test Passed\n");
	}
	else{
		printf("Test Failed\n");
	}
	return 0;
}

