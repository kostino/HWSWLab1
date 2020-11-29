#include <stdint.h>
#define lm 8
#define ln 8
#define lp 8
#define M (1<<lm)
#define N (1<<ln)
#define P (1<<lp)

void UNOPTIMIZED_MATRIX_MUL(uint8_t A[N][M], uint8_t B[M][P], uint32_t C[N][P]){
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
