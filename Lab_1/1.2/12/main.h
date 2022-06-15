#include "iostream"
#include "stdlib.h"
#include "time.h"
#include "cstdlib"

#include "..\..\..\helpFunctions\functions.cpp"


using namespace std;

typedef int DataType;



// deque(дек) - double ended queue
class Deque {
    public:
        int size;
        int maxlength;

        virtual int Empty (void) = 0; //проверка на пустоту
        virtual int Full (void) = 0; //проверка на полноту заполнения

        virtual void pushBack(DataType) = 0; // добавление элемента в начало дека
        virtual void pushFront(DataType) = 0; // добавление элемента в конец дека

        virtual DataType getFront (void) = 0; // неразрушающее чтение элемента c начала дека
        virtual DataType getBack (void) = 0; // неразрушающее чтение элемента c конца дека

        
        virtual DataType popBack (void) = 0; // удаление эоемента с конца дека
        virtual DataType popFront (void) = 0; // удаление эоемента с начала дека

        virtual ~Deque();
};


class List: public Deque
{
    
    struct Node {
        Node(DataType data = DataType(), Node *pPrev = nullptr, Node *pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }

        DataType data;
        Node * pNext, * pPrev;
    } *head, *tail; //индексы головы и хвоста

    public:

        List (int length = 10);
        ~List ();

        int Empty (void) override;
        int Full (void) override;

        void pushBack(DataType) override;
        void pushFront(DataType) override;

        DataType getFront (void) override;
        DataType getBack (void) override;

        DataType popBack (void) override;
        DataType popFront (void) override;
        
};


class Vector: public Deque
{
    int head, tail; //индексы головы и хвоста
    
    DataType *data; //массив для хранения элементов
    public:

        Vector(int maxlength=10);
        ~Vector();

        int Empty (void) override;
        int Full (void) override;

        void pushBack(DataType) override;
        void pushFront(DataType) override;

        DataType getFront (void) override;
        DataType getBack (void) override;

        DataType popBack (void) override;
        DataType popFront (void) override;

};


// Конструкторы
List::List(int length) {
    this->head = tail = NULL;
    this->maxlength = length;
    this->size = 0;
}

Vector::Vector(int length) {
    this->maxlength = length;
    this->data = new DataType[this->maxlength];

    this->head = 0;
    this->tail = maxlength - 1;
    this->size = 0;
}

// Деструкторы
Deque::~Deque(){}

List::~List () {
    Node * temp = head;
    while (head) {
        temp = head;
        head = head->pNext;
        delete temp;
    }
}

Vector::~Vector()
{
   delete[] this->data;
}

// Проверка на пустоту
int List::Empty() {
    return this->head == NULL;
}

int Vector::Empty() {
    return (this->tail + 1 ) % maxlength == this->head;
}


// Проверка на полноту заполнения
int List::Full() {
    return this->size == this->maxlength;
}

int Vector::Full() {
    return ( this->tail + 2 ) % maxlength == this->head;
}


// Добавление элемента в начало дека
void List::pushFront(DataType item) {
    if (Full()) {
        cout << "deque is full :(" << endl;
        return;
    }
    if (Empty()) {
        // Создаём первый элемент
        head = tail = new Node(item);
    } 
    else {
        // Создаём новый элемент
        Node *pNew = new Node(item, nullptr, head);
        head->pPrev = pNew;
        // Перемещаем указатель на новый элемент
        head = pNew;
    }

    this->size++;
}

void Vector:: pushFront(DataType item) {
    if (Full()) {
        cout << "deque is full :(" << endl;
        return;
    } else {
        int value;
        // for (int i = this->size ; i != 0 ; i--) {
        //     value = this->data[i - 1];
        //     this->data[i] = value;
        // }
        // this->data[0] = item;

        this->head = this->head ? this->head - 1 : maxlength - 1;
        this->data[this->head] = item;
    }
    
    
    
    this->size++;
}


// Добавление элемента в конец дека
void List::pushBack(DataType data) {
    if (Full()) {
        cout << "deque is full :(" << endl;
        return;
    }
    if (Empty()) {
        head = tail = new Node(data);
    } else {
        tail->pNext = new Node(data, tail, nullptr);;
        tail = tail->pNext;
    }
    this->size++;
}

void Vector::pushBack(DataType item) {
    if (Full()) {
        cout << "deque is full :(" << endl;
        return;
    }
    // this->data[size] = data;
    this->tail = ( this->tail + 1 ) % maxlength;
    this->data[this-> tail] = item;
    this->size++;
}


// Неразрушающее чтение элемента c начала дека
DataType List::getFront() {
    if (Empty()) {
        cout << "deque is empty :(" << endl;
        return 0;
    }
    return head->data;
}

DataType Vector::getFront() {
    if (Empty()) {
        cout << "deque is empty :(" << endl;
        return 0;
    }
    return this->data[this->head];
}


// Неразрушающее чтение элемента c конца дека
DataType List::getBack() {
    if (Empty()) {
        cout << "deque is empty :(" << endl;
        return 0;
    }
    return tail->data;
}

DataType Vector::getBack() {
    if (Empty()) {
        cout << "deque is empty :(" << endl;
        return 0;
    }
    return this->data[this->tail];
}


// Удаление эоемента с конца дека
DataType List::popBack() {
    Node *temp = tail;
    DataType tempData;

    if (Empty()) {
        cout << "deque is empty :(" << endl;
        return 0;
    } else if (size == 1) {
        tempData = tail->data;

        head = head->pNext;
        tail = nullptr;
    } else {
        tempData = tail->data;

        tail = tail->pPrev;
        tail->pNext = nullptr;
    }

    delete temp;
    size--;

    return tempData;
}

DataType Vector::popBack() {
    if (Empty()) {
        cout << "deque is empty :(" << endl;
        return 0;
    }
    // size--;
    // return data[size];
    DataType temp = tail;
    this->tail = this->tail ? this->tail - 1 : maxlength - 1;
    size--;
    return this->data[temp];
}


// Удаление элемента с начала дека
DataType List::popFront() {
    Node *temp= head;
    DataType tempData;

    if (Empty()) {
        cout << "deque is empty :(" << endl;
        return 0;
    } else if (size == 1) {
        tempData = head->data;

        head = head->pNext;
        tail = nullptr;
    } else {
        tempData = head->data;

        head = head->pNext;
        head->pPrev = nullptr;
    }


    delete temp;

    size--;
    return tempData;
}

DataType Vector::popFront() {
    if (Empty()) {
        cout << "deque is empty :(" << endl;
        return 0;
    }

    // DataType tempData = data[head];

    // int value;
    // for (int i = this->head + 1; i != size ; i++) {
    //     value = this->data[i];
    //     this->data[i-1] = value;
    // }
    
    // size--;
    // return tempData;

    DataType temp = this->head;
    this->head = (this->head + 1) % maxlength;
    size--;
    return this->data[temp];
}



