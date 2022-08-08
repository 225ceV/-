#include<iostream>
#include<malloc.h>
using namespace std;
#ifndef LINKLIST_H
#define LINKLIST_H

template<typename Dtype>
struct Node
{
    Dtype data;
    Node* next;
};

template<typename Dtype>
class LinkList
{
private:
    /* data */
    struct Node<Dtype>* head;
    int size;
public:
    LinkList():size(0)
    {
        /* 头节点 */
        head=(Node<Dtype>*)malloc(sizeof(Node<Dtype>));
        head->next=NULL;
    }
    LinkList(int num):size(num)
    {
        LinkList();
        Node<Dtype>* p;
        for(int i=0; i<num; i++){
            p=(Node<Dtype>*)malloc(sizeof(Node<Dtype>));
            p->data=(Dtype)i;
            p->next=head->next;
            head->next=p;
        }
    }
    ~LinkList()
    {
        Node<Dtype> *p=head->next, *q;
        while(p){
            q=p->next;
            free(p);
            p=q;
        }
    }
    /* 访问 */
    const Dtype& operator[](int index) const
    { 
        Node<Dtype>* p=head->next;
        for(int i=0; i<index; i++){
            p=p->next;
        }
        return p->data;
    }
    Dtype& operator[](int index)
    { 
        Node<Dtype>* p=head->next;
        for(int i=0; i<index; i++){
            p=p->next;
        }
        return p->data;
    } 
    /* 在指向元素前插入元素 */
    int ins(int index, Dtype value)
    {
        Node<Dtype>* p=head;
        if(index>=0 && index<size){
            for(int i=0; i<index; i++){
                p=p->next;
            }
            Node<Dtype>*s=(Node<Dtype>*)malloc(sizeof(Node<Dtype>));
            s->data=value;
            s->next=p->next;
            p->next=s;
            size++;
            return 0;
        }else{
            return 1;
        }
    }
    int del(int index)
    {
        Node<Dtype> *p=head, *q;

        if(index>=0 && index<size){
            for(int i=0; i<index; i++){
                p=p->next;
            }
            q=p->next;
            p->next=q->next;
            free(q);
            size--;
            return 0;
        }else{
            return 1;
        }
    }
    void print()
    {
        Node<Dtype>* p=head->next;
        cout<<"linked list size: "<<size<<endl;
        for(int i=0; i<size; i++){
            cout<<p->data<<",";
            p=p->next;
        }
        cout<<endl;
    }
};
#endif

int main(int argc, char const *argv[])
{
    /* code */
    LinkList<double> l(10);
    l.ins(0, 99.0/2);
    l.ins(5, 66);
    l.del(2);
    l[5]=666.9;
    l.print();
    //cout<<typeof(l[0])<<endl;
    
    return 0;
}
