#include <bits/stdc++.h>
using namespace std;
#define N 7

int A[N] = {54,57,10,28,66,74,43};
int B[N];

void BottomUpMerge(int iLeft, int iRight, int iEnd)
{
    int i0 = iLeft;
    int i1 = iRight;
    int j;

    /* While there are elements in the left or right runs */
    for (j = i0; j < iEnd; j++)
    {
        /* If left run head exists and is <= existing right run head */
        if (i0 < iRight && (i1 >= iEnd || A[i0] <= A[i1]))
        {
            B[j] = A[i0];
            i0 = i0 + 1;
        }
        else
        {
            B[j] = A[i1];
            i1 = i1 + 1;
        }
    }
}

void CopyArray(int n)
{
    for(int i=0; i<N; i++)
    {
        printf("%d ", B[i]);
    }

    printf("\n");
    for(int i = 0; i < n; i++)
        A[i] = B[i];
}

void BottomUpSort(int n)
{
    /* Each 1-element run in A is already "sorted". */
    /* Make successively longer sorted runs of length 2, 4, 8, 16... until whole array is sorted. */
    for (int width = 1; width < n; width = 2 * width)
    {
        /* Array A is full of runs of length width. */
        for (int i = 0; i < n; i = i + 2 * width)
        {
            /* Merge two runs: A[i:i+width-1] and A[i+width:i+2*width-1] to B[] */
            /* or copy A[i:n-1] to B[] ( if(i+width >= n) ) */
            BottomUpMerge(i, min(i+width, n), min(i+2*width, n));
        }
        /* Now work array B is full of runs of length 2*width. */
        /* Copy array B to array A for next iteration. */
        /* A more efficient implementation would swap the roles of A and B */
        CopyArray(n);
        /* Now array A is full of runs of length 2*width. */
    }
}


int main()
{
    int seed = time(0);
    srand(seed);

//    for(int i=0; i<N; i++)
//    {
//        A[i] = rand() % 100;
//        printf("%d ", A[i]);
//    }
    BottomUpSort(N);

    printf("\n\n");
    int fo = 0;
    int i;
    for(i=0; i<N-1; i++)
    {
        if(A[i] > A[i+1])
            fo++;
        printf("%d ", A[i]);
    }
    printf("%d\n", A[i]);
    printf("\n%d", fo);

    return 0;
}

