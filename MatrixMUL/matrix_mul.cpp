#include <stdint.h>
#define lm 8
#define ln 8
#define lp 8
#define M (1<<lm)
#define N (1<<ln)
#define P (1<<lp)

void MATRIX_MUL(uint8_t A[N][M], uint8_t B[M][P], uint32_t C[N][P]){

	uint8_t BRAM_A[N][M];
	uint8_t BRAM_B[M][P];
	int f = M / 2;

#pragma HLS ARRAY_PARTITION variable=BRAM_A cyclic factor=f dim=2
#pragma HLS ARRAY_PARTITION variable=BRAM_B cyclic factor=f dim=1

	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
#pragma HLS PIPELINE II=1
			BRAM_A[i][j] = A[i][j];
		}
	}
	for(int i = 0; i < M; i++){
		for(int j = 0; j < P; j++){
#pragma HLS PIPELINE II=1
			BRAM_B[i][j] = B[i][j];
		}
	}

    for(int i = 0; i < N; i++){
        for(int j = 0; j < P; j++){
#pragma HLS PIPELINE II=1
            int result=0;
            for(int k = 0; k < M; k++){
                result += (uint32_t)(BRAM_A[i][k] * BRAM_B[k][j]);
            }
            C[i][j] = result;
        }
    }
}
