#ifndef LIST_HPP
#define LIST_HPP
#include <iostream>

template<class T>
class List {
public:

    ~List();

    List(); // ò¤ò?ò?ó?ó?ó?ó?ò¤ó?ò?ó?

    void push_back(T data); //ò¶ó?ó?òœò¶ò£ó?ó? ò¶ ò¤ò?ò?ò?ó? ó?ò§ò£ó?ò¤òœ

    void pop_back(); //ó?ò­òœò?ò£ó?ó? ó?òžò?ò?  ó? ò¤ò?ò?ó?òœ ó?ò§ò£ó?ò¤òœ

    void pop_front(); //ó?ò­òœò?ò£ó?ó? ó?òžò?ò? ó? ò?òœó?òœò?òœ ó?ò§ò£ó?ò¤òœ

    void clear_list(); //ò?ó?ò£ó?ó?ò£ó?ó? ó?ò§ò£ó?ò?ò¤

    int GetSize() const { return size; }; //ó?òžò?òœó?ó? ó?òœòžò?ò?ó? ó?ò§ò£ó?ò¤òœ

    T &operator[](int index); //ò§ò?ó?ò?ò¦ó?ó?òžò¤òœ ò?ò§ò?ó?òœó?ò£ò£ ò£ò?ò­ò?ò¤ó?ò£ó?ò?ò¶òœò?ò£ó?. ò?ó?ò?ò­: ò£ò?ò­ò?ò¤ó?.

private:
    class Node { // ó?òžò?ò? ó?ò§ò£ó?ò¤òœ
    public:
        T data; // ò­òœò?ò?ó?ò? ò? ò§ò?ò?òžò­ò?
        Node *pNext; // ó?ò¤òœòžòœó?ò?ò?ó? ò?òœ ó?ò?ò?ò­ó?ó?ó?ò£ò? ó?òžò?ò?

        Node(T data, Node *pNext = nullptr) {
            this->data = data;
            this->pNext = pNext;
        }
    };

    int size; // ó?òœòžò?ò?ó? ó?ò§ò£ó?ò¤òœ
    Node *head; // ó?ò¤òœòžòœó?ò?ò?ó? ò?òœ ò¦ò?ò?ò?ò¶ó? ó?ò§ò£ó?ò¤òœ
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