#include <iostream>
using namespace std;

struct node
{
    int data;
    node *next;
};

class LinkedList
{
public:
    node *Start;
    int number_of_nodes;
    int initial_node_number;

    LinkedList();
    node* newNode();
    void Insert();
    void Traverse();
    void DeleteFirst();
};

// constructor
LinkedList::LinkedList()
{
    Start = NULL;
    number_of_nodes = 0;
}

// new node creation, incrementing node counter each time it is called
node* LinkedList::newNode()
{
    int d;
    cout << "ENTER DATA: ";
    cin >> d;
    node *temp = new node;
    temp->data = d;
    temp->next = Start;

    number_of_nodes++;
    return temp;
}

void LinkedList::Insert()
{
    node *temp = newNode();

    if(Start == NULL)
    {
        temp->next = temp;
        Start = temp;
        return;
    }
    node *iter = new node;
    iter = Start;
    while(iter->next != Start)
        iter = iter->next;
    iter->next = temp;
}

void LinkedList::Traverse()
{
    node *iter = new node;
    iter = Start;

    do
    {
        cout << iter->data;
        if(iter->next != Start)
                cout << " --> ";
        iter = iter->next;
    } while(iter != Start);
    cout << "\tNumber of nodes: " << number_of_nodes << "\n\n";
}
void LinkedList::DeleteFirst()
{
    if(number_of_nodes == 1)
    {
        Start = NULL;
        number_of_nodes--;
        return;
    }
    node *iter = new node;
    iter = Start;
    while(iter->next != Start)
        iter = iter->next;

    node *newStart = new node;
    newStart = Start->next;
    iter->next = newStart;
    Start = newStart;

    number_of_nodes--;
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
    if((Front == 1 && Rear == number_of_elements) || Front == Rear+1)
    {
        cout << "Overflow\n";
        return;
    }
    if(Front == 0)
    {
        l.Insert();
        Front = Rear = 1;
    }
    else if(Rear == number_of_elements)
    {
        l.Insert();
        Rear = 1;
    }
    else
    {
        l.Insert();
        Rear++;
    }

}
void Queue::Pop(LinkedList &l)
{
    if(Front == 0)
    {
        cout << "Underflow\n";
        return;
    }
    if(Front == Rear)
    {
        Front = Rear = 0;
        l.DeleteFirst();
    }
    else if(Front == number_of_elements)
    {
        Front = 1;
        l.DeleteFirst();
    }
    else
    {
        Front++;
        l.DeleteFirst();
    }
}
void Queue::Display(LinkedList &l)
{
    if(Front == 0)
    {
        cout << "Queue empty\n";
        return;
    }
    l.Traverse();
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
