#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define n 5
#define N (1 << n)

double mR[2][2] = {{1, 2}, {3, 4}};
double mI[2][2] = {{5, 6}, {7, 8}};
double *vR;
double *vI;

void compute(int k) {
    int K = 1 << k;
    for (int i = 0; i < N; i += 2 * K) {
        #pragma omp for simd
        for (int j = 0; j < K; j++) {
            double rLR, rLI, rUR, rUI;
            double *vLR = vR + i;
            double *vLI = vI + i;
            double *vUR = vR + i + K;
            double *vUI = vI + i + K;

            rLR = mR[0][0] * vLR[j] - mI[0][0] * vLI[j] + mR[0][1] * vUR[j] - mI[0][1] * vUI[j];
            rLI = mR[0][0] * vLI[j] + mI[0][0] * vLR[j] + mR[0][1] * vUI[j] + mI[0][1] * vUR[j];
            rUR = mR[1][0] * vLR[j] - mI[1][0] * vLI[j] + mR[1][1] * vUR[j] - mI[1][1] * vUI[j];
            rUI = mR[1][0] * vLI[j] + mI[1][0] * vLR[j] + mR[1][1] * vUI[j] + mI[1][1] * vUR[j];

            vLR[j] = rLR;
            vLI[j] = rLI;
            vUR[j] = rUR;
            vUI[j] = rUI;
        }
    }
}

int main() {
    vR = (double *) malloc(N * sizeof(double));
    vI = (double *) malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        vR[i] = 2 * i;
        vI[i] = 2 * i + 1;
    }

    compute(3);

    for (int i = 0; i < N; i++) {
        printf("vR[%d] = %f\n", i, vR[i]);
        printf("vI[%d] = %f\n", i, vI[i]);
        printf("\n");
    }
}