#include "iostream"
#include "time.h"

using namespace std;

int start = 0, finish = 0;

struct employer
{
    int id;     // уникальный идентификатор
    int salary; // зарплата сотрудника

    employer *Emloyee; // указатель на список сотрудников
    employer *next;    // указатель на следующего сотрудника в списке

    employer(int id, int salary, employer *Emloyee = nullptr, employer *next = nullptr)
    {
        this->id = id;
        this->salary = salary;

        this->next = next;
        this->Emloyee = Emloyee;
    }
};

void recursion(employer *employer, int salary)
{

    while (employer->next != nullptr)
    {
        employer->salary += salary;
        if (employer->Emloyee != nullptr)
        {
            recursion(employer->Emloyee, salary);
        }
    }
}

int main()
{

    start = clock();

    int countOfPersons, countOfRequests, directorSalary;

    cin >> countOfPersons;
    cin >> countOfRequests;

    cin >> directorSalary;

    employer** employers;

    employers = new employer *[countOfPersons];

    employers[0] = new employer(1, directorSalary);

    for (int i = 1; i < countOfPersons; i++)
    {
        int salary, Emloyer;
        cin >> salary;
        cin >> Emloyer;
        // Создаём новый элемент в массиве
        employers[i] = new employer(i + 1, salary);

        // добавляем если сотрдников нет
        if (employers[Emloyer - 1]->Emloyee == nullptr)
        {
            employers[Emloyer - 1]->Emloyee = employers[i];
        }
        else
        {
            // добавляем если сотрудников есть, добавляем нового в начало списка смежного
            employers[i] = employers[Emloyer - 1]->Emloyee;
            employers[Emloyer - 1]->Emloyee = employers[i];
        }
    }

    for (int j = 0; j < countOfRequests; j++)
    {
        string request;
        cin >> request;
        if (request == "p")
        {
            int Emloyer, salary;
            cin >> Emloyer;
            cin >> salary;

            // рекурсия
            recursion(employers[Emloyer - 1]->Emloyee, salary);

            // for (int m = countOfPersons - 1; m != 0; m--) {
            //  employer * currentEmployer = employers[m];
            //  if (currentEmployer->id == chiefId) {
            //  continue;
            //  }
            //  while (currentEmployer->Chief != nullptr) {
            //  currentEmployer = currentEmployer->Chief;
            //  if (currentEmployer->id == chiefId) {
            //  employers[m]->salary += salary;
            //  break;
            //  }
            //  }

            //}
        }
        else if (request == "u")
        {
            int id;
            cin >> id;
            cout << employers[id - 1]->salary << endl;
        }
    }

    finish = clock();
    return 0;
}