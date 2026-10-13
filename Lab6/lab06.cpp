#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;
void print(const vector<float>& a) {
    for(float x:a) cout<<fixed<<setprecision(1)<<x<<' ';
    cout<<'\n';
}
void selectionSort(vector<float>& a) {
    for(size_t i=0;i<a.size();i++) {
        size_t m=i;
        for(size_t j=i+1;j<a.size();j++) if(a[j]<a[m]) m=j;
        swap(a[i],a[m]);
    }
}
void quickSort(vector<float>& a,int l,int r) {
    if(l>=r) return;
    float pivot=a[(l+r)/2];
    int i=l,j=r;
    while(i<=j) {
        while(a[i]<pivot) i++;
        while(a[j]>pivot) j--;
        if(i<=j) swap(a[i++],a[j--]);
    }
    if(l<j) quickSort(a,l,j);
    if(i<r) quickSort(a,i,r);
}
void quickSort(vector<float>& a) {
    if(!a.empty()) quickSort(a,0,(int)a.size()-1);
}
void runCase(const string& title,const vector<float>& src) {
    cout<<title<<"\n   исходный: ";
    print(src);
    auto a=src;
    selectionSort(a);
    cout<<"   отбором:  ";
    print(a);
    auto b=src;
    quickSort(b);
    cout<<"   быстрая:  ";
    print(b);
    cout<<"   проверка: "<<((is_sorted(a.begin(),a.end())&&is_sorted(b.begin(),b.end()))?"OK":"ОШИБКА")<<"\n\n";
}
int main() {
    cout<<"========================================\nЛАБОРАТОРНАЯ РАБОТА №6\nСортировка массивов\nВариант 5: отбором и быстрая\n========================================\n\n";
    runCase("1. Случайный порядок:", {
        4.2f,1.0f,3.5f,2.1f,5.0f
    }
    );
    runCase("2. Обратный порядок:", {
        5,4,3,2,1
    }
    );
    runCase("3. Уже отсортировано:", {
        1,2,3,4,5
    }
    );
    cout<<"Вывод: оба алгоритма правильно сортируют массив во всех трех случаях.\nСортировка отбором проста, но выполняет O(n^2) сравнений. Быстрая\nсортировка в среднем работает за O(n log n).\n";
    return 0;
}
