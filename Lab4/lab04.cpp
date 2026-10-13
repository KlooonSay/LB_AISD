#include <iostream>
using namespace std;
const int SIZE=5;
struct Node {
    float value;
    Node* next;
};
struct SimpleQueue {
    float data[SIZE] {
    };
    int head=0, tail=0;
    bool push(float v) {
        if(tail==SIZE) return false;
        data[tail++]=v;
        return true;
    }
    bool pop(float& v) {
        if(head==tail) return false;
        v=data[head++];
        return true;
    }
};
struct CircularQueue {
    float data[SIZE] {
    };
    int head=0, tail=0, count=0;
    bool push(float v) {
        if(count==SIZE) return false;
        data[tail]=v;
        tail=(tail+1)%SIZE;
        count++;
        return true;
    }
    bool pop(float& v) {
        if(count==0) return false;
        v=data[head];
        head=(head+1)%SIZE;
        count--;
        return true;
    }
};
struct ArrayStack {
    float data[SIZE] {
    };
    int top=-1;
    bool push(float v) {
        if(top==SIZE-1) return false;
        data[++top]=v;
        return true;
    }
    bool pop(float& v) {
        if(top<0) return false;
        v=data[top--];
        return true;
    }
};
void listPush(Node*& top,float v) {
    top=new Node {
        v,top
    };
}
bool listPop(Node*& top,float& v) {
    if(!top) return false;
    Node* old=top;
    v=top->value;
    top=top->next;
    delete old;
    return true;
}
int main() {
    cout<<"========================================\nЛАБОРАТОРНАЯ РАБОТА №4\nОчереди и стеки\nВариант 5 (тип float)\n========================================\n\n";
    cout<<"1. Простая очередь:\n";
    SimpleQueue q;
    for(int i=1;i<=6;i++) {
        bool ok=q.push((float)i);
        cout<<"   push "<<i<<" -> "<<(ok?"OK":"ПЕРЕПОЛНЕНИЕ")<<" | head="<<q.head<<" tail="<<q.tail<<'\n';
    }
    float x;
    q.pop(x);
    q.pop(x);
    cout<<"   после двух pop: head="<<q.head<<" tail="<<q.tail<<'\n';
    cout<<"   push 7 -> "<<(q.push(7)?"OK":"ПЕРЕПОЛНЕНИЕ")<<" (освободившееся место в начале не используется)\n\n";
    cout<<"2. Циклическая очередь:\n";
    CircularQueue cq;
    for(int i=1;i<=5;i++) cq.push((float)i);
    cq.pop(x);
    cq.pop(x);
    cout<<"   после двух pop: head="<<cq.head<<" tail="<<cq.tail<<" count="<<cq.count<<'\n';
    cq.push(6);
    cq.push(7);
    cout<<"   после push 6,7: head="<<cq.head<<" tail="<<cq.tail<<" count="<<cq.count<<'\n';
    cout<<"   push 8 -> "<<(cq.push(8)?"OK":"ПЕРЕПОЛНЕНИЕ")<<"\n\n";
    cout<<"3. Стек на массиве:\n";
    ArrayStack st;
    for(int i=1;i<=6;i++) {
        bool ok=st.push((float)i);
        cout<<"   push "<<i<<" -> "<<(ok?"OK":"ПЕРЕПОЛНЕНИЕ")<<" | top="<<st.top<<'\n';
    }
    st.pop(x);
    cout<<"   pop -> "<<x<<" | top="<<st.top<<"\n\n";
    cout<<"4. Стек на связном списке:\n";
    Node* top=nullptr;
    for(int i=1;i<=3;i++) {
        listPush(top,(float)i);
        cout<<"   push "<<i<<" | адрес вершины="<<top<<'\n';
    }
    while(listPop(top,x)) cout<<"   pop "<<x<<" | новая вершина="<<top<<'\n';
    cout<<"\nВывод: простая очередь не использует освободившиеся ячейки в начале,\nциклическая очередь повторно использует их. Стек работает по принципу LIFO;\nв массиве его размер ограничен, а связный стек растет динамически.\n";
    return 0;
}
