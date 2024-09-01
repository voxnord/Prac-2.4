#include <iostream>
#include <Windows.h>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>

using namespace std;

struct Employee 
{
    char name[100];
    char pos[100];
    double sal;
};

void manageEmployees() 
{
    vector<Employee> employees;
    fstream file("employees.bin", ios::in | ios::out | ios::binary);

    if (!file) 
    {
        // Если файл не существует, создадим новый
        file.open("employees.bin", ios::out);
        file.close();
        file.open("employees.bin", ios::in | ios::out | ios::binary);
    }

    int choice;
    do 
    {
        cout << "Меню:" << endl;
        cout << "1. Добавить сотрудника" << endl;
        cout << "2. Удалить сотрудника" << endl;
        cout << "3. Поиск сотрудника" << endl;
        cout << "4. Выход" << endl;
        cout << "Выберите опцию: ";
        cin >> choice;
        cin.ignore();  // Игнорируем символ новой строки после ввода числа

        system("cls");

        if (choice == 1) 
        {
            // Добавление сотрудника
            Employee emp;
            cout << "Введите ФИО: ";
            cin.getline(emp.name, 100);
            cout << "Введите должность: ";
            cin.getline(emp.pos, 100);
            cout << "Введите зарплату: ";
            cin >> emp.sal;
            cin.ignore();  // Игнорируем символ новой строки после ввода числа

            file.seekp(0, ios::end);  // Перемещаемся в конец файла
            file.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
            cout << "Сотрудник добавлен.\n";

            Sleep(1000);

            system("cls");
        }

        else if (choice == 2) 
        {
            // Удаление сотрудника

            vector<Employee> employees;
            Employee emp;

            cout << "Введите ФИО сотрудника, которого хотите удалить: ";

            char nameToDelete[100];
            cin.getline(nameToDelete, 100);

            file.clear();  // Сбрасываем флаги EOF и ошибок
            file.seekg(0, ios::beg);

            bool found = false;
            while (file.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) 
            {
                if (strcmp(emp.name, nameToDelete) != 0) 
                {
                    employees.push_back(emp);
                }
                else 
                {
                    found = true;
                }
            }

            if (found) 
            {
                file.close();
                file.open("employees.bin", ios::out | ios::binary | ios::trunc);

                for (const auto& e : employees) 
                {
                    file.write(reinterpret_cast<const char*>(&e), sizeof(Employee));
                }

                cout << "Сотрудник удален." << endl;

                file.close();
                file.open("employees.bin", ios::in | ios::out | ios::binary);

                Sleep(1000);

                system("cls");
            }
            else 
            {
                cout << "Сотрудник не найден." << endl;

                Sleep(1000);

                system("cls");
            }

        }
        else if (choice == 3) 
        {
            // Поиск сотрудника
            Employee emp;
            cout << "Введите ФИО сотрудника для поиска: ";
            char nameToSearch[100];
            cin.getline(nameToSearch, 100);

            file.clear();  // Сбрасываем флаги EOF и ошибок
            file.seekg(0, ios::beg);

            bool found = false;
            while (file.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) 
            {
                if (strcmp(emp.name, nameToSearch) == 0) 
                {
                    cout << "Сотрудник найден: " << endl;
                    cout << "ФИО: " << emp.name << endl;
                    cout << "Должность: " << emp.pos << endl;
                    cout << "Зарплата: " << emp.sal << endl;

                    found = true;

                    break;
                }
            }

            if (!found) 
            {
                cout << "Сотрудник не найден.\n";

                Sleep(1000);

                system("cls");
            }
        }

    } 

    while (choice != 4);

    file.close();
}

int main() 
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    manageEmployees();
    return 0;
}
