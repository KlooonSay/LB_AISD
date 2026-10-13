#include <iostream>
#include <vector>
#include <cstring>
#include <string>
using namespace std;
struct Data {
    char name[32];
    float key;
    char group;
};
struct Node {
    Data data;
    Node* left;
    Node* right;
};
Data makeData(const string& name,float key,char group) {
    Data d {
    };
    strncpy(d.name,name.c_str(),31);
    d.name[31]='\0';
    d.key=key;
    d.group=group;
    return d;
}
Node* insert(Node* root,const Data& d) {
    if(!root) return new Node {
        d,nullptr,nullptr
    };
    if(d.key<root->data.key) root->left=insert(root->left,d);
    else if(d.key>root->data.key) root->right=insert(root->right,d);
    return root;
}
Node* minNode(Node* r) {
    while(r&&r->left) r=r->left;
    return r;
}
Node* erase(Node* root,float key) {
    if(!root) return nullptr;
    if(key<root->data.key) root->left=erase(root->left,key);
    else if(key>root->data.key) root->right=erase(root->right,key);
    else {
        if(!root->left) {
            Node* t=root->right;
            delete root;
            return t;
        }
        if(!root->right) {
            Node* t=root->left;
            delete root;
            return t;
        }
        Node* t=minNode(root->right);
        root->data=t->data;
        root->right=erase(root->right,t->data.key);
    }
    return root;
}
Node* search(Node* root,float key) {
    if(!root||root->data.key==key) return root;
    return key<root->data.key?search(root->left,key):search(root->right,key);
}
void ascending(Node* r) {
    if(!r)return;
    ascending(r->left);
    cout<<r->data.key<<' ';
    ascending(r->right);
}
void descending(Node* r) {
    if(!r)return;
    descending(r->right);
    cout<<r->data.key<<' ';
    descending(r->left);
}
void preorder(Node* r) {
    if(!r)return;
    cout<<r->data.key<<' ';
    preorder(r->left);
    preorder(r->right);
}
void destroy(Node* r) {
    if(!r)return;
    destroy(r->left);
    destroy(r->right);
    delete r;
}
Node* buildBalanced(const vector<Data>& a,int l,int r) {
    if(l>r) return nullptr;
    int m=(l+r)/2;
    Node* n=new Node {
        a[m],nullptr,nullptr
    };
    n->left=buildBalanced(a,l,m-1);
    n->right=buildBalanced(a,m+1,r);
    return n;
}
int main() {
    cout<<"========================================\nЛАБОРАТОРНАЯ РАБОТА №9\nДвоичные деревья\nВариант 5\n========================================\n\n";
    vector<Data> items= {
        makeData("A",5,'A'),makeData("B",3,'B'),makeData("C",8,'C'),makeData("D",2,'D'),makeData("E",4,'E'),makeData("F",7,'F'),makeData("G",9,'G')
    };
    Node* root=nullptr;
    for(auto &d:items) root=insert(root,d);
    cout<<"1. Дерево создано вставкой узлов.\n   восходящий обход:    ";
    ascending(root);
    cout<<'\n';
    cout<<"   нисходящий обход:    ";
    descending(root);
    cout<<'\n';
    cout<<"   последовательный:    ";
    preorder(root);
    cout<<"\n\n";
    cout<<"2. Удаление узлов 2 и 8, контроль нисходящим обходом:\n";
    root=erase(root,2);
    cout<<"   после удаления 2: ";
    descending(root);
    cout<<'\n';
    root=erase(root,8);
    cout<<"   после удаления 8: ";
    descending(root);
    cout<<"\n\n";
    cout<<"3. Идеально сбалансированное дерево из 7 узлов:\n";
    vector<Data> sorted= {
        makeData("N1",1,'A'),makeData("N2",2,'A'),makeData("N3",3,'A'),makeData("N4",4,'A'),makeData("N5",5,'A'),makeData("N6",6,'A'),makeData("N7",7,'A')
    };
    Node* balanced=buildBalanced(sorted,0,(int)sorted.size()-1);
    cout<<"   нисходящий обход: ";
    descending(balanced);
    cout<<'\n';
    balanced=insert(balanced,makeData("N8",8,'A'));
    balanced=insert(balanced,makeData("N0",0,'A'));
    cout<<"   после добавления 0 и 8: ";
    descending(balanced);
    cout<<"\n\n";
    cout<<"4. Поиск:\n";
    Node* yes=search(balanced,6);
    Node* no=search(balanced,10);
    cout<<"   ключ 6: "<<(yes?"НАЙДЕН":"НЕ НАЙДЕН");
    if(yes) cout<<", узел "<<yes->data.name;
    cout<<'\n';
    cout<<"   ключ 10: "<<(no?"НАЙДЕН":"НЕ НАЙДЕН")<<'\n';
    destroy(root);
    destroy(balanced);
    cout<<"\nВывод: двоичное дерево поддерживает вставку, удаление, поиск и разные\nпорядки обхода. Сбалансированное дерево уменьшает высоту и ускоряет поиск.\n";
    return 0;
}
