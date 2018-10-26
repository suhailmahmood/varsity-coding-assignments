#include <iostream>
#include <cstdio>
#define N 5
using namespace std;

int Q[N+1];
void Insert();
void Delete();
void Show();
void Manage();
int F = 0, R = 0;


int main()
{
    Manage();

    return 0;
}

void Manage()
{
    char ch;
    do
    {
        cout << "1 - INSERT\t2 - DELETE\t3 - SHOW\t0 - EXIT\n";
        cin >> ch;
        if(ch == '1')
            Insert();
        else if(ch == '2')
            Delete();
        else if(ch == '3')
            Show();
    }while(ch != '0');
}

void Insert()
{
    if((F == 1 && R == N) || F == R+1)
    {
        cout << "Overflow\n\n";
        return;
    }
    if(F == 0)
    {
        F = 1;
        R = 1;
    }
    else if(R == N)
        R = 1;
    else
        R++;
    cout << "Enter data to insert: ";
    int item;
    cin >> item;
    Q[R] = item;
    cout << "Front : " << F << endl;
    cout << "Rear  : " << R << endl;
    Show();
}

void Delete()
{
    if(F == 0)
    {
        cout << "Underflow\n\n";
        return;
    }
    if(F == R)
    {
        F = 0;
        R = 0;
    }
    else if(F == N)
        F = 1;
    else
        F++;
    cout << "Front : " << F << endl;
    cout << "Rear  : " << R << endl;
    Show();
}

void Show()
{
    cout << "\nCurrent Queue:\n\n";
    if(R >= F)
        for(int i=F; i<=R; i++)
            cout << Q[i] << endl;

    if(R < F)
    {
        for(int i=F; i<=N; i++)
            cout << Q[i] << endl;
        for(int i=1; i<=R; i++)
            cout << Q[i] << endl;
    }
}


