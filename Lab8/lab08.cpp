#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int linearSearch(const vector<float>& a,float key) {
    for(size_t i=0;i<a.size();i++) if(a[i]==key) return (int)i;
    return -1;
}
int binarySearch(const vector<float>& a,float key) {
    int l=0,r=(int)a.size()-1;
    while(l<=r) {
        int m=(l+r)/2;
        if(a[m]==key) return m;
        if(a[m]<key) l=m+1;
        else r=m-1;
    }
    return -1;
}
struct Node {
    char value;
    Node* prev;
    Node* next;
};
Node* build(const vector<char>& v) {
    Node* h=nullptr,*t=nullptr;
    for(char c:v) {
        Node* n=new Node {
            c,t,nullptr
        };
        if(t)t->next=n;
        else h=n;
        t=n;
    }
    return h;
}
Node* listSearch(Node* h,char key) {
    for(Node* p=h;p;p=p->next) if(p->value==key)return p;
    return nullptr;
}
void destroy(Node*& h) {
    while(h) {
        Node*n=h->next;
        delete h;
        h=n;
    }
}
void showResult(const string& method,const string& key,int index) {
    cout<<"   "<<method<<", ключ "<<key<<": "<<(index>=0?"НАЙДЕН, индекс "+to_string(index):"НЕ НАЙДЕН")<<'\n';
}
int main() {
    cout<<"========================================\nЛАБОРАТОРНАЯ РАБОТА №8\nПоиск в массивах и списках\nВариант 5\n========================================\n\n";
    vector<float> a= {
        4.2f,1.0f,3.5f,2.1f,5.0f
    };
    cout<<"Исходный массив: ";
    for(float x:a) cout<<x<<' ';
    cout<<"\n\n1. Линейный поиск:\n";
    showResult("успешный","3.5",linearSearch(a,3.5f));
    showResult("неуспешный","9.9",linearSearch(a,9.9f));
    sort(a.begin(),a.end());
    cout<<"\n2. После сортировки для двоичного поиска: ";
    for(float x:a) cout<<x<<' ';
    cout<<'\n';
    showResult("успешный","3.5",binarySearch(a,3.5f));
    showResult("неуспешный","9.9",binarySearch(a,9.9f));
    cout<<"\n3. Поиск в двусвязном списке char:\n";
    Node* list=build( {
        'A','B','C','D','E'
    }
    );
    Node* ok=listSearch(list,'C');
    Node* no=listSearch(list,'Z');
    cout<<"   ключ C: "<<(ok?"НАЙДЕН":"НЕ НАЙДЕН");
    if(ok) cout<<", адрес узла="<<ok;
    cout<<'\n';
    cout<<"   ключ Z: "<<(no?"НАЙДЕН":"НЕ НАЙДЕН")<<'\n';
    destroy(list);
    cout<<"\nВывод: линейный поиск работает без предварительной сортировки;\nдвоичный поиск требует упорядоченного массива, но сокращает число\nсравнений. В связном списке поиск выполняется последовательным обходом.\n";
    return 0;
}
