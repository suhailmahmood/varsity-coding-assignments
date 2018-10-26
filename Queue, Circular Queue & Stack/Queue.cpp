#include <iostream>
#include <cstdio>
#define N 20
using namespace std;

int Q[N];
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
        cout << "1 - INSERT\t2 - DELETE\t0 - EXIT\n";
        cin >> ch;
        if(ch == '1')
            Insert();
        else if(ch == '2')
            Delete();
    }while(ch != '0');
}

void Insert()
{
    if(F == 0 && R == N-1)
    {
        cout << "Overflow\n\n";
        return;
    }
    cout << "Enter data to insert: ";
    int item;
    cin >> item;
    Q[R-1] = item;
    cout << "Front : " << F+1 << endl;
    cout << "Rear  : " << R+1 << endl;
    R++;
    Show();
}

void Delete()
{
    if(F == N-1 || (F == R))
    {
        cout << "Underflow\n\n";
        return;
    }

    F++;
    cout << "Front : " << F+1 << endl;
    cout << "Rear  : " << R+1 << endl;
    Show();
}

void Show()
{
    cout << "Current Queue:\n\n";
    for(int i=F-1; i<R-1; i++)
    {
        cout << Q[i] << endl;
    }
}
