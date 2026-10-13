#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
template <typename T, size_t N>
void printArray(const T (&a)[N], const string& name) {
    cout << name << ": ";
    for (const auto& x : a) cout << x << ' ';
    cout << '\n';
}
int main() {
    cout << "========================================\nЛАБОРАТОРНАЯ РАБОТА №1\nМассивы автоматические, статические и динамические\nВариант 5\n========================================\n\n";
    float a[5];
    float* p = nullptr;
    static char s[6] = {
        'A','B','C','D','E','\0'
    };
    char (*ps)[6] = &s;
    int cube[2][2][3] = {
        {
            {
                1,2,3
            }
            , {
                4,5,6
            }
        }
        , {
            {
                7,8,9
            }
            , {
                10,11,12
            }
        }
    };
    int (*plane)[2][3] = cube;
    cout << "1. Автоматический массив float до заполнения:\n   Значения не читаем до инициализации (они неопределены).\n";
    istringstream demoInput("1.5 2.5 3.5 4.5 5.5");
    cout << "2. Заполняем массив значениями: 1.5 2.5 3.5 4.5 5.5\n";
    for (float &x : a) demoInput >> x;
    printArray(a, "   a");
    p = a;
    cout << "\n3. Работа через указатель:\n   адрес массива a     = " << static_cast<void*>(a) << '\n' << "   значение указателя p= " << static_cast<void*>(p) << '\n' << "   первый элемент *p   = " << *p << '\n' << "   элементы через p: ";
    for (int i=0;i<5;i++) cout << *(p+i) << ' ';
    cout << "\n";
    cout << "\n4. Статический массив char:\n   s = " << s << '\n' << "   адрес s = " << static_cast<void*>(s) << '\n';
    cout << "\n5. Динамический одномерный массив float:\n";
    p = new float[5] {
        10,20,30,40,50
    };
    cout << "   ";
    for (int i=0;i<5;i++) cout << p[i] << ' ';
    cout << '\n';
    delete[] p;
    p = nullptr;
    cout << "   память освобождена\n";
    cout << "\n6. Динамический двумерный массив char через указатель №4:\n";
    const int rows = 3;
    char (*dyn2d)[6] = new char[rows][6] {
        {
            'H','E','L','L','O','\0'
        }
        , {
            'W','O','R','L','D','\0'
        }
        , {
            'C','+','+','!','!','\0'
        }
    };
    ps = dyn2d;
    for (int i=0;i<rows;i++) cout << "   строка " << i << ": " << ps[i] << '\n';
    delete[] dyn2d;
    cout << "\n7. Трехмерный массив int:\n   cube[1][0][2] = " << cube[1][0][2] << '\n' << "   то же через указатели = " << *(*(*(cube+1)+0)+2) << '\n' << "   через указатель plane  = " << plane[1][0][2] << '\n';
    cout << "\nВывод: массив и указатель могут обращаться к одним и тем же данным;\nдинамические массивы создаются во время работы программы и после\nиспользования должны быть освобождены оператором delete[].\n";
    return 0;
}
