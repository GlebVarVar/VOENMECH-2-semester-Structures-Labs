#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>

template<class T>
class List {
public:

    ~List();

    List(); // ��?�?�?�?�?�?��?�?�?

    void push_back(T data); //��?�?����?�? � ��?�?�?�? �?���?��

    void pop_back(); //�?���?��?�? �?��?�?  �? ��?�?�?� �?���?��

    void pop_front(); //�?���?��?�? �?��?�? �? �?��?��?� �?���?��

    void clear_list(); //�?�?��?�?��?�? �?���?�?�

    int GetSize() const { return size; }; //�?��?��?�? �?���?�?�? �?���?��

    T &operator[](int index); //��?�?�?��?�?��� �?��?�?��?�� ��?��?��?��?�?���?��?. �?�?�?�: ��?��?��?.

private:
    class Node { // �?��?�? �?���?��
    public:
        T data; // ���?�?�?�? �? ��?�?���?
        Node *pNext; // �?�����?�?�?�? �?� �?�?�?��?�?�?��? �?��?�?

        Node(T data, Node *pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };

    int size; // �?���?�?�? �?���?��
    Node *head; // �?�����?�?�?�? �?� ��?�?�?��? �?���?��
};

template <class T>
void List<T>::pop_front() {
    Node *temp = head;
    head = head->pNext;
    delete temp;
    size--;
}

template <class T>
List<T>::List() {
    size = 0;
    head = nullptr;
}

template <class T>
void List<T>::push_back(T data) {
    if (head != nullptr) {
        Node *current = this->head;
        while (current->pNext != nullptr) {
            current = current->pNext;
        }
        current->pNext = new Node(data);
    } else {
        head = new Node(data);
    }
    size++;
}

template <class T>
void List<T>::pop_back() {
    if (head == nullptr) {
        std::cout << "List is empty" << std::endl;
    } else if (head->pNext == nullptr) {
        this->pop_front();
    } else {
        Node *current = head;
        Node *precurrent = nullptr;
        while (current->pNext != nullptr) {
            precurrent = current;
            current = current->pNext;
        }
        precurrent->pNext = nullptr;
        delete current;
        size--;
    }
}

template <class T>
void List<T>::clear_list() {
    while (size) {
        pop_front();
    }
}

template <class T>
T &List<T>::operator[](const int index) {
    int counter = 0;
    Node *current = this->head;
    while (current != nullptr) {
        if (counter == index) {
            break;
        }
        current = current->pNext;
        counter++;
    }
    return current->data;
}

template<class T>
List<T>::~List() {
    clear_list();
}

#endif //LIST_HPP