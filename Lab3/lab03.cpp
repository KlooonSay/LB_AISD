#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <cstdint>
using namespace std;
struct Student {
    char name[32];
    char* surname;
    float id;
    float* values;
    char group;
    int size;
};
FILE* binOut = nullptr;
FILE* binIn = nullptr;
void initStudent(Student& s, int size=0) {
    s.name[0]='\0';
    s.surname=nullptr;
    s.id=0;
    s.values=nullptr;
    s.group='-';
    s.size=size;
    if (size>0) s.values = new float[size] {
    };
}
void setSurname(Student& s, const string& x) {
    delete[] s.surname;
    s.surname = new char[x.size()+1];
    strcpy(s.surname,x.c_str());
}
void setStudent(Student& s,const string& n,const string& sn,float id,char g,const vector<float>& v) {
    strncpy(s.name,n.c_str(),31);
    s.name[31]='\0';
    setSurname(s,sn);
    s.id=id;
    s.group=g;
    delete[] s.values;
    s.size=(int)v.size();
    s.values=new float[s.size];
    for(int i=0;i<s.size;i++) s.values[i]=v[i];
}
void freeStudent(Student& s) {
    delete[] s.surname;
    delete[] s.values;
    s.surname=nullptr;
    s.values=nullptr;
}
void printStudent(const Student& s) {
    cout<<s.name<<' '<<(s.surname?s.surname:"")<<" | id="<<s.id<<" | group="<<s.group<<" | values:";
    for(int i=0;i<s.size;i++) cout<<' '<<s.values[i];
    cout<<'\n';
}
void writeText(FILE* f,const Student& s) {
    fprintf(f,"%s;%s;%.1f;%c;%d",s.name,s.surname,s.id,s.group,s.size);
    for(int i=0;i<s.size;i++) fprintf(f,";%.1f",s.values[i]);
    fputc('\n',f);
}
bool readText(FILE* f,Student& s) {
    char line[512];
    if(!fgets(line,sizeof(line),f)) return false;
    char* tok=strtok(line,";\n");
    if(!tok) return false;
    string name=tok;
    tok=strtok(nullptr,";\n");
    if(!tok) return false;
    string surname=tok;
    tok=strtok(nullptr,";\n");
    float id=stof(tok);
    tok=strtok(nullptr,";\n");
    char group=tok[0];
    tok=strtok(nullptr,";\n");
    int n=stoi(tok);
    vector<float> v;
    for(int i=0;i<n;i++) {
        tok=strtok(nullptr,";\n");
        v.push_back(tok?stof(tok):0);
    }
    initStudent(s);
    setStudent(s,name,surname,id,group,v);
    return true;
}
void writeBinary(FILE* f,const Student& s) {
    fwrite(s.name,sizeof(s.name),1,f);
    uint32_t len=(uint32_t)strlen(s.surname);
    fwrite(&len,sizeof(len),1,f);
    fwrite(s.surname,1,len,f);
    fwrite(&s.id,sizeof(s.id),1,f);
    fwrite(&s.group,sizeof(s.group),1,f);
    fwrite(&s.size,sizeof(s.size),1,f);
    fwrite(s.values,sizeof(float),s.size,f);
}
bool readBinary(FILE* f,Student& s) {
    char name[32];
    if(fread(name,sizeof(name),1,f)!=1) return false;
    uint32_t len=0;
    fread(&len,sizeof(len),1,f);
    string surname(len,' ');
    fread(surname.data(),1,len,f);
    float id;
    char g;
    int n;
    fread(&id,sizeof(id),1,f);
    fread(&g,sizeof(g),1,f);
    fread(&n,sizeof(n),1,f);
    vector<float> v(n);
    fread(v.data(),sizeof(float),n,f);
    initStudent(s);
    setStudent(s,name,surname,id,g,v);
    return true;
}
bool same(const Student& a,const Student& b) {
    if(strcmp(a.name,b.name)!=0 || strcmp(a.surname,b.surname)!=0 || a.id!=b.id || a.group!=b.group || a.size!=b.size) return false;
    for(int i=0;i<a.size;i++) if(a.values[i]!=b.values[i]) return false;
    return true;
}
int main() {
    cout<<"========================================\nЛАБОРАТОРНАЯ РАБОТА №3\nФайлы\nВариант 5\n========================================\n\n";
    Student src[3];
    for(auto &x:src) initStudent(x);
    setStudent(src[0],"Anna","Ivanova",201,'A', {
        5,4,5
    }
    );
    setStudent(src[1],"Boris","Sidorov",202,'B', {
        4,4,3
    }
    );
    setStudent(src[2],"Clara","Orlova",203,'C', {
        5,5,5
    }
    );
    FILE* txt=fopen("students.txt","w");
    binOut=fopen("students.bin","wb");
    for(auto &s:src) {
        writeText(txt,s);
        writeBinary(binOut,s);
    }
    fclose(txt);
    fclose(binOut);
    cout<<"1. Исходные данные записаны в students.txt и students.bin\n2. Чтение текстового файла:\n";
    Student fromText[3];
    txt=fopen("students.txt","r");
    bool textOk=true;
    for(int i=0;i<3;i++) {
        initStudent(fromText[i]);
        readText(txt,fromText[i]);
        printStudent(fromText[i]);
        textOk &= same(src[i],fromText[i]);
    }
    fclose(txt);
    cout<<"   Совпадение с исходным массивом: "<<(textOk?"ДА":"НЕТ")<<"\n\n";
    cout<<"3. Чтение двоичного файла:\n";
    Student fromBin[3];
    binIn=fopen("students.bin","rb");
    bool binOk=true;
    for(int i=0;i<3;i++) {
        initStudent(fromBin[i]);
        readBinary(binIn,fromBin[i]);
        printStudent(fromBin[i]);
        binOk &= same(src[i],fromBin[i]);
    }
    fclose(binIn);
    cout<<"   Совпадение с исходным массивом: "<<(binOk?"ДА":"НЕТ")<<"\n";
    cout<<"\n4. Текстовый файл можно прочитать обычным редактором.\n   Двоичный файл содержит те же данные в машинном представлении.\n";
    for(auto &s:src) freeStudent(s);
    for(auto &s:fromText) freeStudent(s);
    for(auto &s:fromBin) freeStudent(s);
    cout<<"\nВывод: данные структуры успешно сохраняются и восстанавливаются\nкак из текстового, так и из двоичного файла.\n";
    return 0;
}
