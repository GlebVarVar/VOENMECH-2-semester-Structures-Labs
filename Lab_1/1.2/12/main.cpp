#include "main.h"

template <class T>
void testDeque(T *);
void printDeque(Deque *);
int chooseSize();
int isPrimeNumber(DataType);

int main() {
    

    int variant = 0;
    do {
        system("cls");
        string menu[] = {
            "Select storage structure!",
            "1. Vector inplementation",
            "2. List inplementation"};

        printMenu(menu, 3);
        exitMenu(3);

        variant = getVariant(3);
        system("cls");

        
        

        switch (variant) {
            case 1: {
                int size = chooseSize();
                Vector *deque = new Vector(size);
                testDeque(deque);

                break;
            }
                
            case 2: {
                int size = chooseSize();
                List *deque = new List(size); 
                testDeque(deque);

                break;
            }
        }

        
    } while (variant != 3);


    return 0;
}

template <class T>
void testDeque(T *deque) {
    


    // тестироваение методов дека
    {
        // cout << deque->Empty() << endl;
        // cout << deque->Full() << endl;
        // deque->pushFront(1);
        // deque->pushFront(2);
        // cout << deque->Empty() << endl;
        // cout << deque->Full() << endl;
        // deque->pushBack(3);
        // cout << deque->getBack() << endl;
        // cout << deque->getFront() << endl;
    }
    
    // заполнение дека элементами
    {
        srand(time(NULL));
        while (!deque->Full()) {
            int randNumber = 1 + rand();

            deque->pushFront(randNumber);
        }

    }
    
    
    
    // удаление простых чисел из дека
    int sizeDeque = deque->size;
    T *dequeHelp = new T(sizeDeque);
    DataType array[sizeDeque];
    for (int i = 0; i < sizeDeque; i++) {
        array[i] = deque->getFront();
        
        if (!isPrimeNumber(array[i])) {
            dequeHelp->pushBack(array[i]);
        }

        deque->popFront();
    }
    for (int i = 0; i < sizeDeque; i++) {
        deque->pushBack(array[i]);
    }
    

    T *dequeSorted = new T(dequeHelp->size);
    

    // неудачная попытка сортировки
    {
        // int sizeDeque = deque->size;
        // DataType array[sizeDeque];
        // for (int i = 0; i < sizeDeque; i++) {
        //     array[i] = deque->getFront();
        //     deque->popFront();
        // }
        // for (int i = 0; i < sizeDeque; i++) {
        //     for (int j = 0; j < sizeDeque; j++) {
        //         if (array[i] > array[j]) {
        //             dequeSorted->pushBack(array[i]);
        //             array[i] = array[j];
        //         }
        //     }
        // }
        // for (int i = 0; i < sizeDeque; i++) {
        //     deque->pushBack(array[i]);
        // }
    }
    // Неудачная попытка сортировки
    {
            // for (int l = 0; l < dequeHelp->size + 1; l++) {
            //     printDeque(dequeHelp);
            //     int newSize = dequeHelp->size;
            //     dequeSorted->pushFront(dequeHelp->getFront());
            //     dequeHelp->popFront();
            //     for(int j = 1; j < newSize; j++) {
            //         if (dequeHelp->getFront() > dequeSorted->getBack()) {
            //             dequeSorted->pushBack(dequeHelp->getFront());
            //             dequeHelp->popFront();
            //         } else if(dequeHelp->getBack() > dequeSorted->getBack()){
            //             dequeSorted->pushBack(dequeHelp->getBack());
            //             dequeHelp->popBack(); 
            //         } else if(dequeHelp->getFront() < dequeSorted->getFront()){  
            //             dequeSorted->pushFront(dequeHelp->getFront());
            //             dequeHelp->popFront(); 
            //         } else if(dequeHelp->getBack() < dequeSorted->getFront()){
            //             dequeSorted->pushFront(dequeHelp->getBack());
            //             dequeHelp->popBack(); 
            //         } else {
            //             dequeSorted->pushFront(dequeHelp->getFront());
            //             dequeHelp->popFront();
            //         }
                    
            //     }
            //     cout << "elem " << dequeSorted->size << endl;
            //     for(int m = 0; m < newSize; m++) {
                    
            //         dequeHelp->pushBack(dequeSorted->getFront());
            //         dequeSorted->popFront();
            //     }
            //     printDeque(dequeHelp);
            //     system("pause");
            // }
            
            // system("pause");
        }
    
    // сортировка дека в порядке убывания
    {
        DataType array2[dequeHelp->size];
        int arrSize = 0;
        DataType temp;
        int sizeDeq = dequeHelp->size;
        

        for (int l = 0; l < sizeDeq; l++) {
            temp = 0;
            for(int j = 0; j < sizeDeq - l; j++) {

                if (dequeHelp->getFront() >= temp) {
                    temp = dequeHelp->getFront();  
                } 
                dequeSorted->pushBack(dequeHelp->getFront());
                dequeHelp->popFront();
            }
            array2[arrSize++] = temp;
            int flag = 0;
            for (int m = 0; m < sizeDeq - l; m++) {

                if (dequeSorted->getFront() == temp && flag == 0) {
                    dequeSorted->popFront();
                    flag = 1;
                } else {
                    dequeHelp->pushBack(dequeSorted->getFront());
                    dequeSorted->popFront();
                }
            }

        }

        // Присвоение деку значений из массива 
        for (int n = 0; n < arrSize; n++) {
            dequeSorted->pushBack(array2[n]);
        }
        
    }



    int variant;
    do {
        system("cls");
        string menu[] = {
            "What you want to do with deque?",
            "1. Print start deque",
            "2. Print sorted deque"};

        printMenu(menu, 3);
        exitMenu(3);

        variant = getVariant(3);
        system("cls");


        switch (variant) {
            case 1: {
                printDeque(deque);
                break;
            }
                
            case 2: {
                printDeque(dequeSorted);
                break;
            }
        }
    } while (variant != 3);
    

}

// выбор размера дека
int chooseSize() {
    cout << "Enter deck size(from 1 to 100)" << endl << "> ";
    int size = getVariant(100);

    return size;
}

// вывод дека
void printDeque(Deque *deque) {
    system("cls"); // очищаем экран

    int sizeDeque = deque->size;
    DataType array[sizeDeque];
    
    for (int i = 0; i < sizeDeque; i++) {
        array[i] = deque->getFront();
        cout << "Node# " << i + 1 << ": " << array[i] << endl;
        deque->popFront();
    }
    for (int i = 0; i < sizeDeque; i++) {
        deque->pushBack(array[i]);
    }
    
    system("pause");
}


DataType isPrimeNumber(DataType number) {
    bool isPrime = true;
    for(int i = 2; i <= number / 2; ++i) {
        if(number % i == 0) { isPrime = false; break; }
    }
    return isPrime;
}




