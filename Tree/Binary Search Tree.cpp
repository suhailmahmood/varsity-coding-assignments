#include <bits/stdc++.h>
using namespace std;

struct node
{
    int data;
    struct node *right, *left, *prev;
};


stack<node*>Stack;
node *root = NULL;
class Tree
{
    int data;
public:
    Tree();
    void add();
    node* createNode();
    void Insert(node*, node*);
    void inorderTraverse();
    node* Find(node*, int);
};

Tree::Tree()
{
    node *temp = createNode();
    root = temp;
}

node* Tree::createNode()
{
    node *temp = new node;
    cout << "Enter data for a node : ";
    cin >> temp->data;
    temp->left = NULL;
    temp->right = NULL;
    temp->prev = NULL;
}

void Tree::add()
{
    int num = 1;
    cout << "1 to continue   0 to finish\n";
    cin >> num;
    while(num)
    {
        node *temp = createNode();
        Insert(root, temp);
        cout << "1 to continue   0 to finish\n";
        cin >> num;
    }
}

void Tree::Insert(node* rt, node* temp)
{
    if(temp->data < rt->data)
    {
        if(rt->left != NULL)
            Insert(rt->left, temp);
        else
        {
            rt->left = temp;
            temp->prev = rt;
        }
    }
    else
    {
        if(rt->right != NULL)
            Insert(rt->right, temp);
        else
        {
            rt->right = temp;
            temp->prev = rt;
        }
    }
}

node* Tree::Find(node *rt, int item)
{
    if(item == rt->data)
    {
        return rt;
    }
    if(item < rt->data)
    {
        if(rt->left != NULL)
            Find(rt->left, item);
    }
    else if(item > rt->data)
    {
        if(rt->right != NULL)
            Find(rt->right, item);
    }
}

void Tree::inorderTraverse()
{
    while(!Stack.empty())
        Stack.pop();

    Stack.push(NULL);
    node *n = root;
    cout << "\nIn-order-traversal: ";
Step2:
    while(n != NULL)
    {
        Stack.push(n);
        n = n->left;
    }

    n = Stack.top();
    Stack.pop();
    while(n != NULL)
    {
        cout << n->data << " ";
        if(n->right != NULL)
        {
            n = n->right;
            goto Step2;
        }
        n = Stack.top();
        Stack.pop();
    }
}

int main()
{
    Tree t;
    t.add();
    t.inorderTraverse();
    cout << "\n\nenter data to search: ";
    int num;
    cin >> num;
    node *loc = t.Find(root, num);

    cout << loc->data << "\n";

    if(loc->prev != NULL)
        cout << "Parent: " << loc->prev->data << endl;
    else
        cout << "Parent is NULL\n";
    if(loc->left != NULL)
        cout << "Left child: " << loc->left->data << endl;
    else
        cout << "Left child is NULL\n";

    if(loc->right != NULL)
        cout << "Right child: " << loc->right->data << endl;
    else
        cout << "Right child is NULL\n";


    return 0;
}
