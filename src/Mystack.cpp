/*================================================================
* Filename:mystack.cpp
* Author: KCN_yu
* Createtime:Mon 30 Nov 2020 06:16:40 PM CST
================================================================*/

#include <iostream>
#include "Mystack.h"
using namespace std;

node::node(){
    next = nullptr;
}
node::node(char e){
    elem = e;
    next = nullptr;
}
bool Mystack::full(){
    return cnts == dim;
}
bool Mystack::empty(){
    return cnts == 0;
}
Mystack::Mystack(){
    dim = MAX;
    cnts = 0;
    head = nullptr;
}
Mystack::Mystack(int n){
    dim = n;
    cnts = 0;
    head = nullptr;
}
void Mystack::push(char e){
    if(cnts >= dim){
        cout << "error! full!" << endl;
        return;
    }
    if(head == nullptr){
        head = new node(e);
    }
    else{
        node* tmp = new node(e);
        tmp->next = head;
        head = tmp;
    }
    cnts++;
}
void Mystack::pop(){
    if(head != nullptr){
        node* tmp = head;
        head = head->next;
        delete tmp;
        cnts--;
    }
}
char Mystack::top(){
    if(head != nullptr)
        return head->elem;
    return '\0';
}
void Mystack::print(){
    if(head != nullptr && head->next == nullptr){
        cout << head->elem << endl;
        return;
    }
    node* tmp = head;
    while(tmp != nullptr){
        cout << tmp->elem << endl;
        tmp = tmp->next;
    }
}
Mystack::~Mystack(){
    node* tmp;
    while(head != nullptr){
        tmp = head->next;
        delete head;
        head = tmp;
    }
}
