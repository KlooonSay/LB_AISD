#include <iostream>
#include <cstring>
#include <string>
using namespace std;
struct Student {
    char name[32];
    char* surname;
    float id;
    float* values;
    char group;
    int size;
};
void initStudent(Student& s, int size) {
    s.name[0] = '\0';
    s.surname = nullptr;
    s.id = 0;
    s.group = '-';
    s.size = size;
    s.values = new float[size] {
    };
}
void setSurname(Student* s, const string& surname) {
    delete[] s->surname;
    s->surname = new char[surname.size()+1];
    strcpy(s->surname, surname.c_str());
}
void fillValues(Student& s, const float* source) {
    for (int i=0;i<s.size;i++) s.values[i] = source[i];
}
void printValues(const Student* s) {
    cout << "   значения: ";
    for (int i=0;i<s->size;i++) cout << s->values[i] << ' ';
    cout << '\n';
}
void setData(Student& s, const string& name, const string& surname, float id, char group, const float* values) {
    strncpy(s.name, name.c_str(), sizeof(s.name)-1);
    s.name[sizeof(s.name)-1] = '\0';
    setSurname(&s, surname);
    s.id = id;
    s.group = group;
    fillValues(s, values);
}
void printFields(const Student& s) {
    cout << "   имя: " << s.name << ", фамилия: " << (s.surname ? s.surname : "") << ", id: " << s.id << ", группа: " << s.group << ", размер массива: " << s.size << '\n';
}
void freeStudent(Student* s) {
    delete[] s->surname;
    delete[] s->values;
    s->surname = nullptr;
    s->values = nullptr;
}
int main() {
    cout << "========================================\nЛАБОРАТОРНАЯ РАБОТА №2\nМассивы и структурированные типы данных\nВариант 5\n========================================\n\n";
    Student one;
    initStudent(one, 3);
    float a[] = {
        4.5f, 5.0f, 4.0f
    };
    setData(one, "Maxim", "Petrov", 101.0f, 'A', a);
    cout << "1. Отдельный объект структуры:\n";
    printFields(one);
    printValues(&one);
    cout << "\n2. Динамический массив из трех структур:\n";
    Student* group = new Student[3];
    const char* names[] = {
        "Anna","Boris","Clara"
    };
    const char* surnames[] = {
        "Ivanova","Sidorov","Orlova"
    };
    float ids[] = {
        201,202,203
    };
    char letters[] = {
        'A','B','C'
    };
    float vals[3][3] = {
        {
            5,4,5
        }
        , {
            4,4,3
        }
        , {
            5,5,5
        }
    };
    for (int i=0;i<3;i++) {
        initStudent(group[i], 3);
        setData(group[i], names[i], surnames[i], ids[i], letters[i], vals[i]);
        cout << "Элемент " << i+1 << ":\n";
        printFields(group[i]);
        printValues(&group[i]);
    }
    cout << "\n3. Локальный объект внутри блока:\n";
    {
        Student local;
        initStudent(local, 2);
        float v[] = {
            1,2
        };
        setData(local, "Local", "Object", 999, 'L', v);
        printFields(local);
        freeStudent(&local);
    }
    cout << "   За пределами блока local недоступен: область видимости закончилась.\n";
    freeStudent(&one);
    for (int i=0;i<3;i++) freeStudent(&group[i]);
    delete[] group;
    cout << "\nВывод: структура объединяет данные разных типов, а динамические поля\nтребуют отдельного выделения и освобождения памяти. Объект, объявленный\nвнутри блока, за его пределами недоступен.\n";
    return 0;
}
