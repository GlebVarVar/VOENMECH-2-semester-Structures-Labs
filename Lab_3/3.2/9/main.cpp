#include "stdlib.h"
#include "fstream"
#include "iomanip"
#include "io.h"
#include "fcntl.h"
#include "locale"
#include "splayTree.h"
#include "hashMap.h"
#include "stdio.h"
#include "iostream"


using namespace std;


#define SIZE 10000

struct MyKeyHash {
    unsigned long operator()(const int &k) const {
        return k % SIZE;
    }
};

int splayMemory = 0;
int * splayMemoryPointer = &splayMemory;

int main()
{
    // создание дерева
    SplayTree* splayTree = initSplayTree(splayMemoryPointer);
    // создание хеш-таблицы
    HashMap<int, bool, SIZE, MyKeyHash> hashMap;

    ifstream test_numbers, my_keys;
    test_numbers.open("test_numbers.txt");

    if (!test_numbers)
        exit(-1);

    
    // запись ключей в деревья
    long int current_key;


    while (!test_numbers.eof())
    {
        test_numbers >> current_key;


        // добавляем элемент в хеш-таблицу и splay дерево
        hashMap.put(current_key, true);
        insertKey(splayTree, current_key, splayMemoryPointer);

    }
    test_numbers.close();

    my_keys.open("my_100_numbers.txt");

    if (!my_keys)
        exit(-1);

    // переменные нужны для создания статистики о работе поиска и деревьев
    bool isSplayFind, isHashMapFind;
    int comparingSplay, comparingHashMap;
    int sumcomparingSplay, sumcomparingHashMap;
    sumcomparingSplay = sumcomparingHashMap = 0;
    int* pComparingSplay = &comparingSplay;

    std:: cout
        << "   KEY    |      Splay tree     |    Hash map    |  Number of Splay tree comparisons  |   Number of Hash map comparisons  |"
        << endl;
    while (!my_keys.eof())
    {
        my_keys >> current_key;

        // ищем только что считанное число из файла
        isSplayFind = findKey(splayTree, current_key)!=NULL;
        hashMap.get(current_key, isHashMapFind);
        // получаем количество сравнений для одной операции поиска
        
        comparingHashMap = hashMap.getComparing();
        comparingSplay = getComparing();

        cout << setw(9) << current_key << " |";
        cout << setw(20) << isSplayFind << " |";
        cout << setw(15) << isHashMapFind << " |";
        cout << setw(35) << comparingSplay << " |";
        cout << setw(34) << comparingHashMap << " |";
        cout << endl;

        sumcomparingSplay += comparingSplay;
        sumcomparingHashMap += comparingHashMap;

        isSplayFind = false;
        isHashMapFind = false;
        comparingSplay = 0;
        comparingHashMap = 0;
    }
    my_keys.close();

    // считаем среднее арифметическое сравнений на один ключ для каждой структуры
    cout << "Arithmetic Mean of Splay tree Comparisons: " << sumcomparingSplay / 100 << endl;
    cout << "Arithmetic Mean of Hash map Comparisons: " << sumcomparingHashMap / 100 << endl;

    cout << endl;

    // получаем количество выделенной памяти для хранения каждой структуры
    cout << "Dedicated memory for Splay tree: " << splayMemory << endl;
    cout << "Dedicated memory for Hash map: " << hashMap.getTotalMemory() << endl;

    return 0;
}