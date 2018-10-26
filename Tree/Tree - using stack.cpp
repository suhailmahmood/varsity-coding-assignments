#include <iostream>
#include <stack>
#include <stdio.h>
using namespace std;

struct node
{
    int data;
    struct node *right, *left, *prev;
};
node *root = NULL;

class Tree
{
    node V;
public:
    Tree();
    void add(node*);
    node* createNode();
    void inorderTraverse();
    void preorderTraverse();
    void postorderTraverse();
};

stack<node*>Stack;

int main()
{
    Tree t;
    t.add(root);
    t.inorderTraverse();
    t.preorderTraverse();
//    t.postorderTraverse();

    return 0;
}




Tree::Tree()
{
    cout << "create root\n";
    node *temp = createNode();
    root = temp;
}

void Tree::add(node* rt)
{
    cout << "In node " << rt->data << endl;
    cout << "1: add to left    2: add to right    3: go to parent    0: finish\n";

    int choice;
    cin >> choice;
    if(choice == 0)
        return;

    if(choice == 1)
    {
        rt->left = createNode();
        rt->left->prev = rt;
        add(rt->left);
    }

    if(choice == 2)
    {
        rt->right = createNode();
        rt->right->prev = rt;
        add(rt->right);
    }

    if(choice == 3)
    {
        if(rt->prev != NULL)
            add(rt->prev);
        else
            add(rt);
    }
}

node* Tree::createNode()
{
    node* temp = new node;
    cout << "Enter data: ";
    cin >> temp->data;
    temp->left = NULL;
    temp->right = NULL;
    temp->prev = NULL;

}

void Tree::inorderTraverse()
{
    while(!Stack.empty())
        Stack.pop();

    Stack.push(NULL);
    node *n = root;
    cout << "\nIn-order-traversal:";
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

void Tree::preorderTraverse()
{
    while(!Stack.empty())
        Stack.pop();
    cout << "\nPreorder traversal: ";

    Stack.push(NULL);
    node *n = root;
    while(n != NULL)
    {
        cout << n->data << " ";
        if(n->right != NULL)
            Stack.push(n->right);
        if(n->left != NULL)
            n = n->left;
        else
        {
            n = Stack.top();
            Stack.pop();
        }
    }
}

//void Tree::postorderTraverse()
//{
//    while(!Stack.empty())
//        Stack.pop();
//    cout << "\nPostorder traversal: ";
//    Stack.push(NULL);
//
//    node *ptr = root;
//
//Step2:
//    while(ptr != NULL)
//    {
//        Stack.push(ptr);
//        if(ptr->right != NULL)
//            Stack.push(-ptr->right);
//        ptr = ptr->left;
//    }
//    ptr = Stack.top();
//    Stack.pop();
//    while(ptr > 0)
//    {
//        cout << ptr->data << " ";
//        ptr = Stack.top();
//        Stack.pop();
//    }
//    if(ptr < 0)
//    {
//        ptr = -ptr;
//        goto Step2;
//    }
//}
