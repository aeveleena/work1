#include <iostream>
#include <fstream>
#include <Windows.h>
#include <iomanip>
#include <vector>
using namespace std;

const string subjects[] = {"���", "���������", "����������������", "���������", "������", "����������", "�������", "��������"};

void line(){
    //cout << "_______________________________";
    cout << "������������������������������";
}

struct Student {
    string fullName;
    string sex;
    int group{};
    int listNum{};
    int grades[8]{};
    float average{};
};

void loadFromFile(Student students[], int& numOfStud){
    ifstream read;
    read.open("C:/Users/abram/CLionProjects/work1/stud.txt");
    while (!read.eof()) {
        string name, surname, patronymic, full;
        read >> surname;
        read >> name;
        read >> patronymic;
        full = surname + ' ' + name + ' ' + patronymic;
        students[numOfStud].fullName = full;
        read >> students[numOfStud].group;
        read >> students[numOfStud].listNum;
        for (int i = 0; i < 8; ++i) read >> students[numOfStud].grades[i];
        numOfStud++;
    }
    numOfStud--;
    read.close();
}

void getSex(Student students[], int& numOfStud){
    for (int i = 0; i < numOfStud; i++){
        string theLastElem;
        theLastElem = students[i].fullName[students[i].fullName.length()-1];
        if (theLastElem == "�") students[i].sex = "���";
        else students[i].sex = "���";
    }
}

void loadToFile(Student students[], int& numOfStud){
    ofstream write;
    write.open("C:/Users/abram/CLionProjects/work1/stud.txt");
    for (int i = 1; i < numOfStud; i++){
        write << students[i].fullName << endl << students[i].sex << endl << students[i].group << endl << students[i].listNum << endl;
        for (int j = 0; j < 8; j++) {
            write << students[i].grades[j];
        }
        write << endl;
    }
    write.close();
}

void addStudents(Student students[], int& numOfStud){
    int num;
    cout << "\n\n������� ���������� ���������, ������� ������ ������ � ������: ";
    cin >> num;
    for (int i = 1; i <= num; i++){
        cout << "\n������� " << i << "\n";
        cout << "\n���: ";
        getline(cin.ignore(), students[numOfStud].fullName);
        cout << "\n����� ������: ";
        cin >> students[numOfStud].group;
        cout << "\n������:\n";
        for (int j = 0; j < 8; j++){
            cout << subjects[j] << ": ";
            cin >> students[numOfStud].grades[j];
            if (students[numOfStud].grades[j] <= 2 || students[numOfStud].grades[j] > 5){
                cout << "������ ������, ������� �������� �����\n";
                j--;
            }
        }
        int numInList = 0;
        for (int g = 0; g < numOfStud; g++){
            if (students[numOfStud].group == students[g].group){
                if (students[g].listNum > numInList) numInList = students[g].listNum;
            }
        }
        students[numOfStud].listNum = numInList+1;
        numOfStud = numOfStud+1;
    }
    getSex(students, numOfStud);
}

void editStudent(Student students[], int& numOfStud){
    int group, num;
    bool YorN;
    int param;
    string sub;
    cout << "\n������� ����� ������ ��������, ������ �������� ������ ��������: ";
    cin >> group;
    cout << "\n������� ��� ����� � ������ ������: ";
    cin >> num;
    for (int i = 0; i < numOfStud; i++){
        if (group != students[i].group || num != students[i].listNum) continue;
        if (group == students[i].group && num == students[i].listNum) cout << "\n�� ������ �������� ������ �������� " << students[i].fullName << "? (1 - ��, 0 - ���)" << endl;
        cin >> YorN;
        while (YorN){
            cout << "\n����� ���������� � �������� ����� ��������? (��� ������ ������� 0)";
            cout << "\n1. ���: " << students[i].fullName << "\n2. ���: " << students[i].sex << "\n3. ������: " << students[i].group << "\n4. ������\n" << endl;
            cin >> param;
            switch(param){
                case 0: break;
                case 1:{
                    cout << "\n���: ";
                    getline(cin.ignore(), students[i].fullName);
                } break;
                case 2:{
                    cout << "\n2. ��� (���/���): ";
                    cin >> students[i].sex;
                } break;
                case 3:{
                    cout << "\n3. ������: ";
                    cin >> students[i].group;
                } break;
                case 4: {
                    cout << "\n��� ������ ������:" << endl;
                    for (int j = 0; j < 8; j++) cout << subjects[j] << ": " << students[i].grades[j] << endl;
                    cout << "\n������ �� ������ �������� ��������� ��������?" << endl;
                    cin >> sub;
                    for (int k = 0; k < 8; k++) {
                        if (sub == subjects[k]) {
                            cout << "\n������� ������ �� �������� " << sub << ": ";
                            cin >> students[i].grades[k];
                            if (students[i].grades[k] <= 2 || students[i].grades[k] > 5){
                                cout << "\n������ ������, ������� �������� �����\n";
                                cin >> students[i].grades[k];
                            }
                        }
                    }
                    cout << "\n������ ������� ������������!" << endl;
                } break;
            }
            cout << "\n\t�������������� ���������� � ��������";
            cout << "\n1. ���: " << students[i].fullName << "\n2. ���: " << students[i].sex << "\n3. ������: " << students[i].group << "\n4. ������:" << endl;
            for (int o = 0; o < 8; o++) cout << "\t" <<subjects[o] << ": " << students[i].grades[o] << endl;
            cout << "\n��������� �� �������� ��� ���-����?\n(1 - ��, 0 - ���)" << endl;
            cin >> YorN;
        }
    }
    getSex(students, numOfStud);
}

void printListOfGroup(Student students[], int& numOfStud){
    int group;
    cout << "\n������� ����� ������, ��� ������� ����� ������� ���������� � ���������: ";
    cin >> group;
    cout << "\n\t������ ��������� ������ " << group << endl;
    for (int i = 0; i < numOfStud; i++){
        if (group != students[i].group) continue;
        if (group == students[i].group){
            cout << "\n" << students[i].listNum << ". " << students[i].fullName << "\n���: " << students[i].sex << "\n\t������" << endl;
            for (int o = 0; o < 8; o++) cout << "\t" << subjects[o] << ": " << students[i].grades[o] << endl;
            line();
        }
    }
}

void printAllStudents(Student students[], int& numOfStud){
    cout << "\n\t������ ���� ���������\n" << endl;
    for (int i = 1; i < numOfStud; i++){
        cout << "\n\t������ " << students[i].group << endl << students[i].listNum << ". " << students[i].fullName << endl;
        cout << "���: " << students[i].sex << endl << "\t������" << endl;
        for (int o = 0; o < 8; o++) cout << subjects[o] << ": " << students[i].grades[o] << endl;
        line();
    }
}

void averageScore(Student students[], int& numOfStud){
    for (int i = 0; i < numOfStud; i++){
        float score = 0;
        for (int o = 0; o < 8; o++) score += students[i].grades[o];
        students[i].average = score/8;
    }
}

void theBest(Student students[], int& numOfStud, int& top){
    float allScores[numOfStud];
    int indexes[numOfStud];
    for (int i = 0; i < numOfStud; i++){
        allScores[i] = students[i].average;
        indexes[i] = i;
    }
    for (int i = 0; i < numOfStud; i++){
        for (int j = i; j < numOfStud - 1 - i; j++){
            if (allScores[j] > allScores[j+1]){
                swap(allScores[j], allScores[j+1]);
                swap(indexes[j], indexes[j+1]);
            }
        }
        for (int j = numOfStud-1; j >= i; j--){
            if (allScores[j] < allScores[j-1]){
                swap(allScores[j], allScores[j-1]);
                swap(indexes[j], indexes[j-1]);
            }
        }
    }
    cout << "\n\t��� " << top << endl;
    for (int t = 1; t <= top; t++) cout << t << ". " << students[indexes[numOfStud-t]].fullName << ": " << allScores[numOfStud-t] << endl;
}

void sexCount(Student students[], int& numOfStud){
    int men(0), women(0);
    for (int i = 0; i < numOfStud; i++){
        string theLastElem;
        theLastElem = students[i].fullName[students[i].fullName.length()-1];
        (theLastElem == "�") ? women++ : men++;
    }
    cout << "\n���������� ��������� �������� ����: " << women << "\n���������� ��������� �������� ����: " << men << endl;
}

void scholarship(Student students[], int& numOfStud){
    vector<int> grad3, grade4, grade5;
    bool tri;
    for (int i = 0; i < numOfStud; i++){
        tri = false;
        for (int o = 0; o < 8; o++){
            if (students[i].grades[o] == 3){
                grad3.push_back(i);
                tri = true;
                break;
            }
        }
        if (tri != true) {
            if (students[i].average >= 4 && students[i].average < 5) grade4.push_back(i);
            else if (students[i].average == 5) grade5.push_back(i);
        }
        else continue;
    }

    int choice;
    cin >> choice;
    switch(choice){
        case 1: {
            cout << "\n\t��������, �������� �� �������";
            for (int i = 0; i < grade5.size(); i++) {
                cout << "\n���: " << students[grade5[i]].fullName << "\n���: " << students[grade5[i]].sex
                     << "\n������: " << students[grade5[i]].group <<
                     "\n����� � ������ ������: " << students[grade5[i]].listNum << "\n������:" << endl;
                for (int o = 0; o < 8; o++)
                    cout << "\t" << subjects[o] << ": " << students[grade5[i]].grades[o] << endl;
                line();
            } break;
        };
        case 2:{
            cout << "\n\t��������, �������� �� ������ � �������";
            for (int i = 0; i < grade4.size(); i++) {
                cout << "\n���: " << students[grade4[i]].fullName << "\n���: " << students[grade4[i]].sex
                     << "\n������: " << students[grade4[i]].group <<
                     "\n����� � ������ ������: " << students[grade4[i]].listNum << "\n������:" << endl;
                for (int o = 0; o < 8; o++)
                    cout << "\t" << subjects[o] << ": " << students[grade4[i]].grades[o] << endl;
                line();
            } break;
        };
        case 3:{
            cout << "\n\t��������, �� ���������� ���������";
            for (int i = 0; i < grad3.size(); i++) {
                cout << "\n���: " << students[grad3[i]].fullName << "\n���: " << students[grad3[i]].sex
                     << "\n������: " << students[grad3[i]].group <<
                     "\n����� � ������ ������: " << students[grad3[i]].listNum << "\n������:" << endl;
                for (int o = 0; o < 8; o++)
                    cout << "\t" << subjects[o] << ": " << students[grad3[i]].grades[o] << endl;
                line();
            } break;
        };
    }
}

void findWithNumber(Student students[], int& numOfStud){
    int k;
    vector<int> index;
    cin >> k;
    bool find;
    for (int i = 0; i < numOfStud; i++) if (k == students[i].listNum) index.push_back(i);
    switch(index.size()){
        case 0:{
            cout << "\n��������� � ����� ������� � ������ �� �������" << endl;
        }break;
        case 1:{
            cout << "\n������ 1 ������� � ������� � ������ " << k << endl;
        }break;
        default:{
            cout << "\n�������� � ������� � ������ " << k << endl;
        }break;
    }
    for (int i = 0; i < index.size(); i++){
        cout << "\n���: " << students[index[i]].fullName << "\n���: " << students[index[i]].sex
             << "\n������: " << students[index[i]].group <<
             "\n����� � ������ ������: " << students[index[i]].listNum << "\n������:" << endl;
        for (int o = 0; o < 8; o++)
            cout << "\t" << subjects[o] << ": " << students[index[i]].grades[o] << endl;
        line();
    }
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int numOfStud;
    Student students[30];
    loadFromFile(students, numOfStud);
    getSex(students, numOfStud);
    //averageScore(students, numOfStud);
    cout << "\t����:\n1. ������� ����� ������ � ��������\n2. �������� ��������� ������\n3. ������� ������ ������\n4. ������ ��� ���������"
            "\n5. ������ ����� ��������� �������� � �������� ����\n6. ������ ������������ ��������� (���������)\n7. ����� ��������� ��� ������ ������� � ������\n8. ������� ���������� ��� ���� ���������\n" << endl;
    int kek(1), command;
    while (kek) {
        cout << "������� ����� ������, ������� ��������� ���������: ";
        cin >> command;
        switch(command){
            case 1:{
                addStudents(students, numOfStud);
            }break;

            case 2:{
                editStudent(students, numOfStud);
            }break;

            case 3:{
                printListOfGroup(students, numOfStud);
            }break;

            case 4:{
                averageScore(students, numOfStud);
                int top;
                cout << "������� ������ ����: ";
                cin >> top;
                theBest(students, numOfStud, top);
            }break;

            case 5:{
                sexCount(students, numOfStud);
            }break;

            case 6:{
                cout << "\n� ����� ��������� �� ������ �������� ����������?\n1) ���������\n2) �������� �� ������ � �������\n3) �� ���������� ���������\n�������: ";
                scholarship(students, numOfStud);
            }break;

            case 7:{
                cout << "\n�������, ��� ����� ������� � ������ �������� ��� ����������: ";
                findWithNumber(students, numOfStud);
            }break;

            case 8:{
                printAllStudents(students, numOfStud);
                cout << endl;
            }break;
        }
        loadToFile(students, numOfStud);
        cout << "\n ���������� ����������? (1 - ��, 0 - ���)" << endl;
        cin >> kek;
    }
    return 0;
}
