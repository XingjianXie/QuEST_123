#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

#define N 128

double mR[2][2] = {{1, 2}, {3, 4}};
double mI[2][2] = {{5, 6}, {7, 8}};
double *vLR;
double *vLI;
double *vUR;
double *vUI;

int main() {
    vLR = (double *) malloc(N * sizeof(double));
    vLI = (double *) malloc(N * sizeof(double));
    vUR = (double *) malloc(N * sizeof(double));
    vUI = (double *) malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        vLR[i] = 4 * i;
        vLI[i] = 4 * i + 1;
        vUR[i] = 4 * i + 2;
        vUI[i] = 4 * i + 3;
    }

    #pragma omp for simd
    for (int i = 0; i < N; i++) {
        double rLR, rLI, rUR, rUI;

        rLR = mR[0][0] * vLR[i] - mI[0][0] * vLI[i] + mR[0][1] * vUR[i] - mI[0][1] * vUI[i];
        rLI = mR[0][0] * vLI[i] + mI[0][0] * vLR[i] + mR[0][1] * vUI[i] + mI[0][1] * vUR[i];
        rUR = mR[1][0] * vLR[i] - mI[1][0] * vLI[i] + mR[1][1] * vUR[i] - mI[1][1] * vUI[i];
        rUI = mR[1][0] * vLI[i] + mI[1][0] * vLR[i] + mR[1][1] * vUI[i] + mI[1][1] * vUR[i];

        vLR[i] = rLR;
        vLI[i] = rLI;
        vUR[i] = rUR;
        vUI[i] = rUI;
    }

    for (int i = 0; i < N; i++) {
        printf("vLR[%d] = %f\n", i, vLR[i]);
        printf("vLI[%d] = %f\n", i, vLI[i]);
        
        printf("vUR[%d] = %f\n", i, vUR[i]);
        printf("vUI[%d] = %f\n", i, vUI[i]);

        printf("\n");
    }
}