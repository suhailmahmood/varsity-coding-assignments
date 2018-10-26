#include <iostream>
#include <cstdio>
#define N 5
using namespace std;

int ST[N];

void Push();
void Pop();
void Manage();
void show();
int Top = -1;


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
            Push();
        else if(ch == '2')
            Pop();
        else if(ch == '3')
            show();
    }while(ch != '0');
}

void Push()
{
    if(Top == N-1)
    {
        cout << "Overflow\n";
        return;
    }
    if(Top == -1)
        Top = 0;
    else
        Top++;

    int data;
    cout << "Enter data to insert: ";


    cin >> data;
    ST[Top] = data;
    show();
}

void Pop()
{
    if(Top == -1)
    {
        cout << "Underflow\n";
        return;
    }
    Top--;
    show();
}

void show()
{
    cout << "\nCurrent Stack:\n\n";
    for(int i=0; i<=Top; i++)
        cout << ST[i] << endl;
}

