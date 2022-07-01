#include "stdlib.h"
#include "fstream"
#include "rbTree.h"
#include "randomTree.h"




int main() {
    // создание деревьев
    RBTree rbTree;
    
    ifstream test_numbers, my_keys;
    test_numbers.open("test_numbers.txt");


    if (!test_numbers)
        exit(-1);

    // запись ключей в деревья
    long int current_key;
    int totalMemRand = 0;
    test_numbers >> current_key;
    randomizeTree randomTree(current_key);
    rbTree.insert(current_key);
    while (!test_numbers.eof()) {
        test_numbers >> current_key;
        totalMemRand += sizeof(element);
        rbTree.insert(current_key);
        randomTree.insert(current_key);
    }
    test_numbers.close();


    cout << "rb tree root: " << rbTree.getRoot()->data << endl;
    cout << "random tree root: " << randomTree.root->key << endl;

    my_keys.open("my_100_numbers.txt");

    if (!my_keys)
        exit(-1);


    // переменные нужны для создания статистики о работе поиска и деревьев
    bool isRedBlackFind;
    bool isRandomFind;
    int comparingRedBlack;
    int comparingRandom;
    int sumComparingRedBlack;
    int sumComparingRandom;
    sumComparingRedBlack =  0;
    sumComparingRandom = 0;
  
    cout
            << "   KEY    |      Red-Black tree     |    randomTree    |  Number of RB tree comparisons  |   Number of Random tree comparisons  |"
            << endl;
    while (!my_keys.eof()) {
        my_keys >> current_key;

        // ищем только что считанное число из файла
        isRedBlackFind = rbTree.searchTree(current_key)->data == current_key;
        isRandomFind = randomTree.find(current_key);
        // получаем количество сравнений для одной операции поиска
        comparingRedBlack = rbTree.getComparing();
        comparingRandom = randomTree.getComparing();




        cout << setw(9) << current_key << " |";
        cout << setw(24) << isRedBlackFind << " |";
        cout << setw(17) << isRandomFind << " |";
        cout << setw(32) << comparingRedBlack << " |";
        cout << setw(37) << comparingRandom << " |";
        cout << endl;

        sumComparingRedBlack += comparingRedBlack;
        sumComparingRandom += comparingRandom;

        isRedBlackFind = false;
        isRandomFind = false;
        comparingRedBlack = 0;
        comparingRandom = 0;
    }
    my_keys.close();

    // считаем среднее арифметическое сравнений на один ключ для каждой структуры
    cout << "Arithmetic Mean of Red-Black Tree Comparisons: " << sumComparingRedBlack / 100 << endl;
    cout << "Arithmetic Mean of Random Tree Comparisons: " << sumComparingRandom / 100 << endl;
    

    cout<<endl;

    // получаем количество выделенной памяти для хранения каждой структуры
    cout << "Dedicated memory for red-black tree: " << rbTree.getTotalMemory() << endl;
    cout << "Dedicated memory for Random tree: " << totalMemRand << endl;

    return 0;
}

