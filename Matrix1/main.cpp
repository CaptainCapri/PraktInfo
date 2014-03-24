#include <iostream>
#include <time.h>
#include <ctime>
#define N 1000
#define BILLION 1E9

using namespace std;

int main()
{
    int i = 0;
    int j = 0;
    int k = 0;
    double **res;
    double **mul1;
    double **mul2;

    time_t t;
    struct timespec requestStart, requestEnd;

    time(&t);

    res = new double *[N];
    mul1 = new double *[N];
    mul2 = new double *[N];

    for(int i = 0; i <N; i++){
        res[i] = new double[N];
        mul1[i] = new double[N];
        mul2[i] = new double[N];
    }

    clock_gettime(CLOCK_REALTIME, &requestStart);
    for (i = 0; i < N; ++i)
        for (j = 0; j < N; ++j)
            for (k = 0; k < N; ++k)
                res[i][j] += mul1[i][k] * mul2[k][j];

    clock_gettime(CLOCK_REALTIME, &requestEnd);
    double accum = ( requestEnd.tv_sec - requestStart.tv_sec )
            + ( requestEnd.tv_nsec - requestStart.tv_nsec )
            / BILLION;
    cout << accum << endl;


    return 0;
}


