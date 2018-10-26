#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next, *prev;
};

class LinkedList
{
    node *Start;
    node *End;
    int counter;

public:
    LinkedList();
    node* newNode();
    void Insert();
    void ForwardTraverse();
    void Delete();
};

// constructor
LinkedList::LinkedList()
{
    Start = End = NULL;
    counter = 0;
}

// new node creation, incrementing node counter each time it is called
node* LinkedList::newNode()
{
    int d1;
    cout << "ENTER DATA: ";
    cin >> d1;
    node *temp = new node;
    temp->data = d1;
    temp->next = NULL;
    temp->prev = NULL;

    counter++;
    return temp;
}

void LinkedList::Insert()
{
    node *temp = newNode();
    if(Start == NULL)
    {
        Start = temp;
        End = temp;
        return;
    }

    End->next = temp;
    temp->prev = End;
    End = temp;
}

void LinkedList::ForwardTraverse()
{
    if(counter == 0)
    {
        cout << "Linked List is EMPTY! -- Create one first.\n";
        return;
    }
    node *iter = new node;
    iter = Start;
    cout << endl << "Traversing forward:\n";

    while(iter != NULL)
    {
        cout << iter->data << endl;
        iter = iter->next;
    }
    cout << "Number of nodes: " << counter << "\n\n";
}
void LinkedList::Delete()
{
    if(counter == 1)
    {
        Start = End = NULL;
        counter--;
        return;
    }
    node *iter = new node;
    iter = End;
    End = iter->prev;
    End->next = NULL;
    counter--;

    delete(iter);
}

class Stack
{
public:
    int Top;
    int number_of_elements;
    Stack();
    void Push(LinkedList &l);
    void Pop(LinkedList &l);
    void Display(LinkedList &l);
    void Operate(LinkedList &l);
};

Stack::Stack()
{
    int no;
    cout << "Enter size of Stack: ";
    cin >> no;
    number_of_elements = no;
    Top = 0;
}
void Stack::Push(LinkedList &l)
{
    if(Top == number_of_elements)
    {
        cout << "Overflow\n";
        return;
    }

    l.Insert();
    Top++;
}
void Stack::Pop(LinkedList &l)
{
    if(Top == 0)
    {
        cout << "Underflow\n";
        return;
    }
    Top--;
    l.Delete();
}
void Stack::Display(LinkedList &l)
{
    if(Top == 0)
    {
        cout << "Stack empty\n";
        return;
    }
    l.ForwardTraverse();
}
void Stack::Operate(LinkedList &l)
{
    char ch;
    do
    {
        cout << "1 - Push\t2 - Pop\t3 - Display\t4 - Exit\n";
        cin >> ch;
        if(ch == '1')
            Push(l);
        if(ch == '2')
            Pop(l);
        if(ch == '3')
            Display(l);
    }while(ch != '4');
}

int main()
{
    LinkedList list;

    Stack stk;

    stk.Operate(list);

    return 0;

}
