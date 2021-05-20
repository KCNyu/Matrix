/*================================================================
* Filename:mystack.h
* Author: KCN_yu
* Createtime:Mon 30 Nov 2020 06:16:40 PM CST
================================================================*/
#ifndef MYSTACK_H
#define MYSTACK_H
#define MAX 256

class node{
public:
    char elem;
    node* next;
    node();
    node(char e);
};

class Mystack{
private:
    int dim;
    int cnts;
    node* head;
public:
    Mystack();
    Mystack(int n);
    void push(char e);
    void pop();
    char top();
    bool full();
    bool empty();
    void print();
    ~Mystack();
};

#endif /* MYSTACK_H */
