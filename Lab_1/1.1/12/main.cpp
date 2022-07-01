#include "iostream"
#include "string"
#include "fstream"
#include "iomanip"

#include "main.h"
#include "..\..\..\helpFunctions\functions.cpp"

using namespace std;


// Конструктор
template<class T>
List<T>::List() {
    size = 0;
    head = nullptr;
    tail = nullptr;
}

// Деструктор
template <class T>
List<T>::~List() {
    clear();
}


// Методы
// Добавление элемента в конец списка
template <class T>
void List<T>::pushBack(T data) {

    // Если список пустой
    if (head == nullptr) {
        // Создаём первый элемент
        head = tail = new Node<T>(data);
    } 
    else {
        // Ищем последний элемент
        Node<T> *pCur = head;
        while (pCur->pNext != nullptr) {
            pCur = pCur->pNext;
        }
        // Добавляем новый элемент
        pCur->pNext = tail = new Node<T>(data, pCur);
    }
    
    size++;
    
}

// Добавление элемента в начало списка
template <class T>
void List<T>::pushFront(T data) {
    // Если список пустой
    if (head == nullptr) {
        // Создаём первый элемент
        head = tail = new Node<T>(data);
    } 
    else {
        // Создаём новый элемент
        Node<T> *pNew = new Node<T>(data, nullptr, head);
        head->pPrev = pNew;
        // Перемещаем указатель на новый элемент
        head = pNew;
    }

    size++;
}

// Удаление первого элемента
template <class T>
void List<T>::popFront() {
    Node<T> *pCur= head;

    if (head == nullptr) {
        cout << "Empty list..." << endl;
        return;
    } else if (size == 1) {
        head = head->pNext;
        tail = nullptr;
    } else {
        head = head->pNext;
        head->pPrev = nullptr;
    }


    delete pCur;

    size--;
}

// Удаление последнего элемента
template <class T>
void List<T>::popBack() {
    Node<T> *pCur = tail;

    if (head == nullptr) {
        cout << "Empty list..." << endl;
        return;
    } else if (size == 1) {
        head = head->pNext;
        tail = nullptr;
    } else {
        tail = tail->pPrev;
        tail->pNext = nullptr;
    }


    delete pCur;

    size--;
}

// Очистка списка
template <class T>
void List<T>::clear() {

    while (size) {
        popFront();
    }

}

// Вставка элемента в список
template <class T>
void List<T>::insert(T value) {

    // pCur - указатель на элемент, который стоит на месте индекса
    // Мы его обязаны сместить вперед, а на его место поставить новый элемент
    Node<T> *pCur = head;
    while(pCur != nullptr ) {
        if (value.yearRelease <= pCur->data.yearRelease) {
            break;
        }
        pCur = pCur->pNext;
    }
    
    if (pCur ==  nullptr) {   // Если хотим вставить в начало
        pushFront(value);
    } else if (pCur->pPrev ==  nullptr) {   // Если хотим вставить в начало
        pushFront(value);
    }else if (pCur->pNext == nullptr) { // Если хотим вставить в конец
        pushBack(value);
    } else {
        // Создаём указатель на новый элемент
        Node<T> *pNew = new Node<T>(value, pCur->pPrev, pCur); 
        pCur->pPrev->pNext = pNew;
        pCur->pPrev = pNew;
        
    }
    
    size++;
    
}

// Удаление элемента по индексу
template <class T>
void List<T>::remove(Node<T> *pCur) {
    if (pCur->pPrev == nullptr) {              
        popFront();
    } else if (pCur->pNext == nullptr) { 
        popBack();
    } else {
        // pCur - указатель на элемент, который стоит на месте индекса
        pCur->pPrev->pNext = pCur->pNext;
        pCur->pNext->pPrev = pCur->pPrev;

        delete pCur;

        size--; 
    }
}

// Сортировка списка
template <class T>
void List<T>::sort() {
    Node<T> *pStart = head;
    for (int j = 0; j < size; j++) {
        pStart = head;
        for(int i = 0; i < j; i++) {
            pStart = pStart->pNext;
        }

        Node<T> *pMax = pStart;
        Node<T> *pCur = pStart;
        while (pCur) {
            if (pCur->data.yearRelease >= pMax->data.yearRelease) {
                pMax = pCur;
            }
            pCur = pCur->pNext;
        }
        pushFront(pMax->data);
        remove(pMax);

    }
    
}

// перегрузка оператора [] для доступа к элементам списка
template<class T>
T& List<T>::operator[] (const int index) {
    // Ищем нужный элемент
    Node<T> *pCur = head; // временный указатель
    for (int i = 0; i < index; i++) {
        pCur = pCur->pNext;
    }

    return pCur->data;
}


// функци для записи данных в бинарный файл
template<class T>
void List<T>::writeFile(const char* fileName, List<T> &lst) {
    
    ofstream file("newFile", ios::out | ios::binary);
    Node<T> *pCur = lst.head;
    while (pCur != nullptr) {
        file.write((char*)&pCur->data, sizeof(T));
        pCur = pCur->pNext;
    }
    file.close();
    std::remove(fileName); 
    rename("newFile", fileName); 
}


// функция доя чтения бинарного файла
template<class T>
void List<T>::readFile(string fileName, List<T> &lst) {

    ifstream file(fileName, ios::in | ios::binary);
    if(file.is_open()) {
        file.seekg(0, file.end);
        int length = (int)file.tellg();
        file.seekg(0, file.beg);

        while (file.tellg() < length) {
            T data;
            file.read((char*)&data, sizeof(T));
            lst.pushBack(data);
        }
    }

    file.close();
}

// Добавление элемента в список
template<class T>
void List<T>::addSet() {
    T newSet;
    
    // Ввод данных
    {cout << "Set title:\n"; cin.getline(newSet.title, 30);   
    cout << "Set number:\n"; newSet.itemNumber = getVariant(100000);
    cout << "Set year release:\n"; newSet.yearRelease = getVariant(2022);
    cout << "minifigures count:\n"; newSet.minifigures = getVariant(50);
    cout << "Parts count:\n"; newSet.parts = getVariant(20000);
    cout << "Price:\n";  newSet.price = getVariant(1000000);
    cout << "Sets count:\n"; newSet.count = getVariant(10000);
    cout << "Is your set released under the Star Wars franchise?\n1- Yes\n2 -No\n>"; newSet.type = getVariant(2);
    if (newSet.type == 1) {
        cout << "Set ROI of the set\n"; newSet.variation.ROI = getVariant(1000);
    } else {
        cout << "Set consumer age:\n"; cin.getline(newSet.variation.age, 10);
    }}
    
    

    insert(newSet);
}

// Печать списка на консоль
template<class T>
void List<T>::printList() {
    
    if (isEmpty()) { return;}

    int variant = 0;

    do {
        system("cls");
        string menu[] = {
            "Choose list visualization:",
            "1. Print all sets from the beggining",
            "2. Print all sets from the end"};

        printMenu(menu, 3);
        exitMenu(3);

        variant = getVariant(3);
        system("cls");
       
        switch (variant) {
            case 1:
                printTable(head);
                break;
            
            case 2:
                printTable(tail);
                break;
                
            default:
                break;
        }

    } while (variant != 3);
}

// вывод данных в виде таблицы
template<class T>
void List<T>::printTable (Node<T> *direction) {
    int variant = 0;
    int N = 0;
    
    int total = 0;
    Node<T> *pCur = direction;

    do {
        int c = 0;

        system("cls");
        
        cout << "|  N  |       Set title        | Set Number | Year release | Minifigures | Parts count |  Price  |  Count  | ROI/Consumer age |" << endl;
        cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
        while (c != 5 && pCur != nullptr) {
            cout << "|" << setw(4) << ++N << " | ";
            cout << setw(22) << pCur->data.title << " | ";
            cout << setw(10) << pCur->data.itemNumber << " | ";
            cout << setw(12) << pCur->data.yearRelease << " | ";
            cout << setw(11) << pCur->data.minifigures << " | ";
            cout << setw(11) << pCur->data.parts << " | ";
            cout << setw(7) << pCur->data.price << " | ";
            cout << setw(7) << pCur->data.count << " | " ;
            if (pCur->data.type == 1) {
                cout << setw(15) << pCur->data.variation.ROI << "% | " << endl;
            } else {
                cout << setw(16) << pCur->data.variation.age << " | " << endl;
            }

            if (direction == head) {
                pCur = pCur->pNext;
            } else {
                pCur = pCur->pPrev;
            }
            c++;
        }
        total += c;
        cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    
        string menu[] = {
            "1. Forward",
            "2. Back"};

        printMenu(menu, 2);
        exitMenu(3);

        variant = getVariant(3);


        switch (variant) {
            case 1:
                if (total == size) {
                    N = total = 0;
                    pCur = direction;
                    break;
                }         
                break;
            
            case 2:
                if (total == size) {
                    N = total =0;
                    pCur = direction;
                    break;
                }
                break;
                
            default:
                break;
        }
        
    } while(variant != 3);
}
        

// Изменение данных элемента
template<class T>
void List<T>::editSetInfo () {
    if (isEmpty()) { return;}
    do {
        cout << "Enter set number: ";
        int number = getVariant(100000);
        Node<T> *pCur = head;
        while (pCur != nullptr) {
            if (pCur->data.itemNumber == number) {
                setData(pCur);
                return;

            }
            pCur = pCur->pNext;
        } 
        cout << "Set not found" << endl;
        cout << "1. exit" << endl;
        cout << "2. try again" << endl;
        int variant = getVariant(2);
        if (variant == 1) {
            return;
        }
        system("cls"); // очищаем экран
    } while(true);
}

// Сеттер данных с меню
template<class T>
void List<T>::setData(Node<T> *pCur) {
    

    int variant = 0;
    int N = 0;
    do {
        system("cls");
        // вывод элемента
        {
            cout << "|  N  |       Set title        | Set Number | Year release | Minifigures | Parts count |  Price  |  Count  | ROI/Consumer age |" << endl;
            cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
            cout << "|" << setw(4) << ++N << " | ";
            cout << setw(22) << pCur->data.title << " | ";
            cout << setw(10) << pCur->data.itemNumber << " | ";
            cout << setw(12) << pCur->data.yearRelease << " | ";
            cout << setw(11) << pCur->data.minifigures << " | ";
            cout << setw(11) << pCur->data.parts << " | ";
            cout << setw(7) << pCur->data.price << " | ";
            cout << setw(7) << pCur->data.count << " | " ;
            if (pCur->data.type == 1) {
                cout << setw(15) << pCur->data.variation.ROI << "% | " << endl;
            } else {
                cout << setw(16) << pCur->data.variation.age << " | " << endl;
            }
            cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
            
        }
        string variation;
        if(pCur->data.type == 1) {
            string variation = "8. Star Wars variation";
        } else {
            string variation = "8. ROI variation";
        }
         
        string menu[] = {
            "Choose set data to change:",
            "1. Title",
            "2. Set number",
            "3. Year release",
            "4. Minifig count",
            "5. Parts count",
            "6. Set price",
            "7. Sets count",
            variation,
            };

        printMenu(menu, 9);
        exitMenu(9);

        variant = getVariant(9);
        system("cls");
        cout << "Enter new value: ";
        switch (variant)
        {
            case 1:
                cin.getline(pCur->data.title, 30); break;
            case 2:
                pCur->data.itemNumber = getVariant(100000); break;
            case 3:
                pCur->data.yearRelease = getVariant(2022); break;
            case 4:
                pCur->data.minifigures = getVariant(50); break;
            case 5:
                pCur->data.parts = getVariant(20000); break;
            case 6:
                pCur->data.price = getVariant(1000000); break;
            case 7:
                pCur->data.count = getVariant(10000); break;
            case 8:
                if (pCur->data.type == 1) {
                    pCur->data.variation.ROI = getVariant(1000);
                } else {
                    cin.getline(pCur->data.variation.age, 10);
                }
                break;
        }


        
    } while (variant != 9);
    
    
    
}


// Удаление элемента
template<class T>
void List<T>::deleteSet() {
    if (isEmpty()) { return;}
    do {

        cout << "Enter set number: ";
        int number = getVariant(100000);
        Node<T> *pCur = head;
        while (pCur != nullptr) {
            if (pCur->data.itemNumber == number) {
                remove(pCur);
                cout << "Set deleted" << endl;
                system("pause");
                return;

            }
            pCur = pCur->pNext;
        }
        cout << "Set not found" << endl;
        cout << "1. exit" << endl;
        cout << "2. try again" << endl;
        int variant = getVariant(2);
        if (variant == 1) {
            return;
        }
        system("cls"); // очищаем экран
    } while (true);
     

}


// Поиск элемента
template<class T>
void List<T>::search() {
    if (isEmpty()) { return;}
    do {
        cout << "Enter year release: ";
        int year = getVariant(2022);
        system("cls"); // очищаем экран
        int flag = 1;
        int N = 0;
        Node<T> *pCur = head;
        while (pCur != nullptr) {
            if (pCur->data.yearRelease == year) {
                if (flag == 1) {
                    cout << "|  N  |       Set title        | Set Number | Year release | Minifigures | Parts count |  Price  |  Count  | ROI/Consumer age |" << endl;
                    cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl;
                }
                flag = 0;
                
                cout << "|" << setw(4) << ++N << " | ";
                cout << setw(22) << pCur->data.title << " | ";
                cout << setw(10) << pCur->data.itemNumber << " | ";
                cout << setw(12) << pCur->data.yearRelease << " | ";
                cout << setw(11) << pCur->data.minifigures << " | ";
                cout << setw(11) << pCur->data.parts << " | ";
                cout << setw(7) << pCur->data.price << " | ";
                cout << setw(7) << pCur->data.count << " | ";
                if (pCur->data.type == 1) {
                    cout << setw(15) << pCur->data.variation.ROI << "% | " << endl;
                } else {
                    cout << setw(16) << pCur->data.variation.age << " | " << endl;
                }
            }
            pCur = pCur->pNext;
        }
        if (flag == 0) {
             cout << "-------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
            system("pause");
            
            return; 
        }
        

        cout << "Sets not found" << endl;
        cout << "1. exit" << endl;
        cout << "2. try again" << endl;
        int variant = getVariant(2);
        if (variant == 1) {
            return;
        }
        system("cls"); // очищаем экран
    } while (true);
} 

int main(int argc, char* argv[])
{

    // Чтение агрументов командной строки
    string fileName;
    {
    if (argc == 2)
        fileName.assign(argv[1]); // получаем имя файла из командной строки
    else if (argc == 1) {
        cout << "Enter fileName bin*:\n";
        getline(cin, fileName);
    } else {
        cout << "Too many arguments :(\n";
        return 1;
    }
    }
    List<LEGO> lst;


    LEGO newSet; 
    
    // Чтение из файла
    lst.readFile(fileName, lst);

    int variant = 0;
    do {
        system("cls");
        string menu[] = {
            "1. Add set",
            "2. Edit set information",
            "3. Print list",
            "4. Delete set",
            "5. Clear list",
            "6. Search"};

        printMenu(menu, 6);
        exitMenu(7);

        variant = getVariant(7);
        system("cls");

        switch (variant) {
            case 1:
                lst.addSet(); break; 
            case 2:
                lst.editSetInfo(); break;
            case 3:
                lst.printList(); break;
            case 4:
                lst.deleteSet(); break;
            case 5:
                lst.clear(); break;
            case 6:
                lst.search(); break;
                 
            default:
                break;
        }
    } while (variant != 7);


    // Запись в файл
    lst.writeFile(fileName.c_str(), lst);

    return 0;
}

