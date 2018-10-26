#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next, *prev;
};

class LinkedList
{
public:
    node *Start;
    node *End;
    int counter;

    LinkedList();
    node* newNode();
    void InsertFirst();
    void InsertLast();
    void ForwardTraverse();
    void DeleteFirst();
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
    int d;
    cout << "ENTER DATA: ";
    cin >> d;
    node *temp = new node;
    temp->data = d;
    temp->next = NULL;
    temp->prev = NULL;

    counter++;
    return temp;
}

void LinkedList::InsertFirst()
{
    node *temp = newNode();

    if(Start == NULL)
    {
        Start = temp;
        End = temp;
        return;
    }
    temp->next = Start;
    Start->prev = temp;
    Start = temp;
}

void LinkedList::InsertLast()
{
    if(Start == NULL)
    {
        InsertFirst();
        return;
    }
    node *temp = newNode();
    End->next = temp;
    temp->prev = End;
    End = temp;
}

void LinkedList::ForwardTraverse()
{
    node *iter = new node;
    iter = Start;
    cout << endl << "Traversing forward:\n";

    while(iter != NULL)
    {
        cout << iter->data << endl;
        iter = iter->next;
    }
//    cout << "Number of nodes: " << counter << "\n\n";
}

void LinkedList::DeleteFirst()
{
    if(counter == 1)
    {
        Start = End = NULL;
        counter--;
        return;
    }
    node *iter = new node;
    iter = Start;
    Start = iter->next;
    Start->prev = NULL;
    counter--;

    delete(iter);
}

class Queue
{
public:
    int Front, Rear;
    int number_of_elements;
    Queue();
    void Push(LinkedList &l);
    void Pop(LinkedList &l);
    void Display(LinkedList &l);
    void Operate(LinkedList &l);
};

Queue::Queue()
{
    int no;
    cout << "Enter size of queue: ";
    cin >> no;
    number_of_elements = no;
    Front = 0;
    Rear = 0;
}
void Queue::Push(LinkedList &l)
{
    if(Rear == number_of_elements)
    {
        cout << "Overflow\n";
        return;
    }
    if(Front == 0)
    {
        l.InsertFirst();
        Front = Rear = 1;
    }
    else
    {
        l.InsertLast();
        Rear++;
    }

}
void Queue::Pop(LinkedList &l)
{
    if(Front == 0 || Front == number_of_elements+1)
    {
        cout << "Underflow\n";
        return;
    }
    Front++;
    l.DeleteFirst();
}
void Queue::Display(LinkedList &l)
{
    if(Front == 0)
    {
        cout << "Queue empty\n";
        return;
    }
    l.ForwardTraverse();
}
void Queue::Operate(LinkedList &l)
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

    Queue Q;
    Q.Operate(list);

    return 0;
}
