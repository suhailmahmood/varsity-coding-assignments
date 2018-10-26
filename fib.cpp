#include <iostream>
#include <vector>
#define REP(i,n) for (int i = 1; i <= n; i++)
using namespace std;

typedef long long ll;
typedef vector<vector<ll> > matrix;
const int K = 2;
ll MOD;

// computes A * B
matrix mul(matrix A, matrix B)
{
    matrix C(K+1, vector<ll>(K+1));
    REP(i, K) REP(j, K) REP(k, K)
        C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % MOD;
    return C;
}

// computes A ^ p
matrix pow(matrix A, ll p)
{
    if (p == 1)
        return A;
    if (p % 2)
        return mul(A, pow(A, p-1));
    matrix X = pow(A, p/2);
    return mul(X, X);
}

//void printMatrix(matrix mat)
//{
//    cout << mat[1][1] << " " << mat[1][2] << endl;
//    cout << mat[2][1] << " " << mat[2][2] << endl;
//}

// returns the N-th term of Fibonacci sequence
int fib(ll N)
{
    // create vector F1
    vector<ll> F1(K+1);
    F1[1] = 1;
    F1[2] = 1;

    // create matrix T
    matrix T(K+1, vector<ll>(K+1));
    T[1][1] = 0, T[1][2] = 1;
    T[2][1] = 1, T[2][2] = 1;

    // raise T to the (N-1)th power
    if (N == 1)
        return 1;
    T = pow(T, N-1);

    printMatrix(T);

    // the answer is the first row of T . F1
    ll res = 0;
    REP(i, K)
        res = (res + T[1][i] * F1[i]) % MOD;
    return res;
}


int main()
{
    ll n;
    while(true)
    {
        cout << "Enter n & MOD:\n";
        cin >> n;
        cin >> MOD;
        cout << fib(n);
        cout << "\n";
    }

    return 0;
}
