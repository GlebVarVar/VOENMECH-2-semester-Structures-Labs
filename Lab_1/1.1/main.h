#include "string"
using namespace std;

// Данные хранящиеся в элементе связного списка
struct LEGO {
    char title[30];
	int itemNumber;
    int yearRelease;
    int minifigures;
    int parts;
    int price;
    int count;
};


// Элемент связного списка
template<class T>
class Node {
    public:
        Node(T data = T(), Node *pPrev = nullptr, Node *pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
            this->pPrev = pPrev;
        }
        
        T data;
        Node* pPrev, * pNext;

};

// Связный список
template<class T>
class List {
    public:
        List();
        ~List();

        // Методы
        void pushBack(T data);
        void pushFront(T data);
        void popFront();
        void popBack();
        void clear();
        void insert(T value);
        void remove(Node<T> *set);
        void sort();
        void printTable(Node<T> *direction);
        bool isEmpty() {
            if (head == nullptr) {
                cout << "There are no entries..." << endl; system("pause");
            }
             return head == nullptr;
        }

        // геттеры
        int getSize() {return size;};
        int getPointerHead() {return head;};
        int getPointerTail() {return tail;};

        // сеттеры
        void setData(Node<T> *set);

        // перегрузка оператора [] - получение свойства data по индексу
        T& operator[] (const int index);

        // взаимодействие с файлами
        void writeFile(const char* fileName, List<T> &lst);
        void readFile(string fileName, List<T> &lst);

        // взаимодействие с консолью(менюшка)
        void deleteSet();
        void printList();
        void search();
        void editSetInfo();
        void addSet();


    private:

        int size;
        Node<T> *head; 
        Node<T> *tail;
        
};