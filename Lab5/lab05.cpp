#include <iostream>
#include <cstring>
#include <string>
using namespace std;
struct Data {
    char name[32];
    float id;
    char group;
};
struct Node {
    Data data;
    Node* next;
    Node* prev;
};
Data makeData(const string& name,float id,char group) {
    Data d {
    };
    strncpy(d.name,name.c_str(),31);
    d.name[31]='\0';
    d.id=id;
    d.group=group;
    return d;
}
void printNode(Node* n) {
    cout<<"["<<n<<"] "<<n->data.name<<" id="<<n->data.id<<" group="<<n->data.group;
}
void pushBackSingly(Node*& head,const Data& d) {
    Node* n=new Node {
        d,nullptr,nullptr
    };
    if(!head) {
        head=n;
        return;
    }
    Node* p=head;
    while(p->next) p=p->next;
    p->next=n;
}
void eraseByIdSingly(Node*& head,float id) {
    Node* cur=head;
    Node* prev=nullptr;
    while(cur && cur->data.id!=id) {
        prev=cur;
        cur=cur->next;
    }
    if(!cur) return;
    if(prev) prev->next=cur->next;
    else head=cur->next;
    delete cur;
}
void printSingly(Node* head) {
    for(Node* p=head;p;p=p->next) {
        printNode(p);
        cout<<" -> "<<p->next<<'\n';
    }
}
void destroyLinear(Node*& head) {
    while(head) {
        Node* n=head->next;
        delete head;
        head=n;
    }
}
Node* makeDoubly() {
    Node* head=nullptr;
    Node* tail=nullptr;
    Data items[]= {
        makeData("Anna",1,'A'),makeData("Boris",2,'B'),makeData("Clara",3,'C')
    };
    for(auto &d:items) {
        Node* n=new Node {
            d,nullptr,tail
        };
        if(tail) tail->next=n;
        else head=n;
        tail=n;
    }
    return head;
}
void printDoubly(Node* head) {
    Node* tail=nullptr;
    cout<<"   вперед:\n";
    for(Node* p=head;p;p=p->next) {
        cout<<"   ";
        printNode(p);
        cout<<" prev="<<p->prev<<" next="<<p->next<<'\n';
        tail=p;
    }
    cout<<"   назад: ";
    for(Node* p=tail;p;p=p->prev) cout<<p->data.name<<(p->prev?" <- ":"\n");
}
void makeCircular(Node* head) {
    if(!head) return;
    Node* tail=head;
    while(tail->next) tail=tail->next;
    tail->next=head;
    head->prev=tail;
}
void printCircularOneRound(Node* head) {
    if(!head) return;
    Node* p=head;
    do {
        cout<<p->data.name<<" -> ";
        p=p->next;
    }
    while(p!=head);
    cout<<"(снова "<<head->data.name<<")\n";
}
void destroyCircular(Node*& head) {
    if(!head) return;
    Node* p=head->next;
    while(p!=head) {
        Node* n=p->next;
        delete p;
        p=n;
    }
    delete head;
    head=nullptr;
}
int main() {
    cout<<"========================================\nЛАБОРАТОРНАЯ РАБОТА №5\nСвязные списки\nВариант 5\n========================================\n\n";
    cout<<"1. Односвязный линейный список:\n";
    Node* single=nullptr;
    pushBackSingly(single,makeData("Anna",1,'A'));
    pushBackSingly(single,makeData("Boris",2,'B'));
    pushBackSingly(single,makeData("Clara",3,'C'));
    printSingly(single);
    cout<<"   удаляем id=2\n";
    eraseByIdSingly(single,2);
    printSingly(single);
    destroyLinear(single);
    cout<<"\n2. Двусвязный линейный список:\n";
    Node* doubly=makeDoubly();
    printDoubly(doubly);
    cout<<"\n3. Преобразуем двусвязный список в кольцевой:\n";
    makeCircular(doubly);
    cout<<"   один полный круг: ";
    printCircularOneRound(doubly);
    cout<<"   head->prev = "<<doubly->prev<<" (последний узел)\n";
    destroyCircular(doubly);
    cout<<"\nВывод: связный список хранит элементы в отдельных узлах, связанных\nуказателями. Двусвязный список позволяет двигаться в обе стороны,\nа в кольцевом последний узел снова указывает на первый.\n";
    return 0;
}
