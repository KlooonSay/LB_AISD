#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct Node {
    char value;
    Node* prev;
    Node* next;
};
Node* build(const vector<char>& v) {
    Node* head=nullptr;
    Node* tail=nullptr;
    for(char c:v) {
        Node* n=new Node {
            c,tail,nullptr
        };
        if(tail) tail->next=n;
        else head=n;
        tail=n;
    }
    return head;
}
void destroy(Node*& head) {
    while(head) {
        Node* n=head->next;
        delete head;
        head=n;
    }
}
void print(Node* head) {
    for(Node* p=head;p;p=p->next) cout<<p->value<<(p->next?' ':'\n');
}
bool sorted(Node* head) {
    for(Node* p=head;p&&p->next;p=p->next) if(p->value>p->next->value) return false;
    return true;
}
void detach(Node*& head, Node* n) {
    if(n->prev) n->prev->next=n->next;
    else head=n->next;
    if(n->next) n->next->prev=n->prev;
}
void insertBefore(Node*& head,Node* pos,Node* n) {
    n->next=pos;
    n->prev=pos?pos->prev:nullptr;
    if(pos) {
        if(pos->prev) pos->prev->next=n;
        else head=n;
        pos->prev=n;
    }
}
void insertionSort(Node*& head) {
    if(!head) return;
    Node* cur=head->next;
    while(cur) {
        Node* next=cur->next;
        Node* pos=head;
        while(pos!=cur && pos->value<=cur->value) pos=pos->next;
        if(pos!=cur) {
            detach(head,cur);
            insertBefore(head,pos,cur);
        }
        cur=next;
    }
}
void swapAdjacent(Node*& head,Node* a,Node* b) {
    Node* before=a->prev;
    Node* after=b->next;
    if(before) before->next=b;
    else head=b;
    b->prev=before;
    b->next=a;
    a->prev=b;
    a->next=after;
    if(after) after->prev=a;
}
void bubblePointerSort(Node*& head) {
    if(!head) return;
    bool changed;
    do {
        changed=false;
        Node* p=head;
        while(p && p->next) {
            Node* q=p->next;
            if(p->value>q->value) {
                swapAdjacent(head,p,q);
                changed=true;
            }
            else p=p->next;
        }
    }
    while(changed);
}
void run(const string& title,const vector<char>& values) {
    cout<<title<<"\n   исходный: ";
    Node* a=build(values);
    print(a);
    insertionSort(a);
    cout<<"   вставками: ";
    print(a);
    cout<<"   проверка: "<<(sorted(a)?"OK":"ОШИБКА")<<'\n';
    destroy(a);
    Node* b=build(values);
    bubblePointerSort(b);
    cout<<"   пузырьковая (перестановка указателей): ";
    print(b);
    cout<<"   проверка: "<<(sorted(b)?"OK":"ОШИБКА")<<"\n\n";
    destroy(b);
}
int main() {
    cout<<"========================================\nЛАБОРАТОРНАЯ РАБОТА №7\nСортировка списков\nВариант 5: линейный двусвязный список char\nМетоды: вставками; пузырьковая с заменой указателей\n========================================\n\n";
    run("1. Случайный порядок:", {
        'D','A','E','B','C'
    }
    );
    run("2. Обратный порядок:", {
        'E','D','C','B','A'
    }
    );
    run("3. Уже отсортировано:", {
        'A','B','C','D','E'
    }
    );
    cout<<"Вывод: оба алгоритма корректно сортируют линейный двусвязный список.\nВо втором методе меняются связи между узлами, а не сами значения.\n";
    return 0;
}
