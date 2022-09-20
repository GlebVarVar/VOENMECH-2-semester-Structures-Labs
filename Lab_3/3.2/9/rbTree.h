#include "iostream"


using namespace std;

// структура узла красно черного дерева
struct Node {
    
    Node *parent;
    Node *left;
    Node *right;
    int color; // 1 -> красный, 0 -> черный
    int data;
};

typedef Node *NodePtr;

class RBTree {
private:
    NodePtr root;
    NodePtr TNULL;
    int comparing;
    int totalMemory;

    NodePtr searchTreeHelper(NodePtr node, int key) {

        if ((++comparing && (node == TNULL)) || (++comparing && (key == node->data))) {
            return node;
        }
        if (++comparing && (key < node->data)) {
            return searchTreeHelper(node->left, key);
        } else {
            return searchTreeHelper(node->right, key);
        }
        
    }

    // восстановление красно-черного дерева после удаления элемента
    void fixDelete(NodePtr x) {
        NodePtr s;
        while (x != root && x->color == 0) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }

                if (s->left->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->right->color == 0) {
                        s->left->color = 0;
                        s->color = 1;
                        rightRotate(s);
                        s = x->parent->right;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->right->color = 0;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == 1) {
                    s->color = 0;
                    x->parent->color = 1;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }

                if (s->right->color == 0 && s->right->color == 0) {
                    s->color = 1;
                    x = x->parent;
                } else {
                    if (s->left->color == 0) {
                        s->right->color = 0;
                        s->color = 1;
                        leftRotate(s);
                        s = x->parent->left;
                    }

                    s->color = x->parent->color;
                    x->parent->color = 0;
                    s->left->color = 0;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = 0;
    }


    void rbTransplant(NodePtr u, NodePtr v){
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left){
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent;
    }

    void deleteNodeHelper(NodePtr node, int key) {
        // ищем ключ с нужным значением
        NodePtr z = TNULL;
        NodePtr x, y;
        while (node != TNULL){
            if (node->data == key) {
                z = node;
            }

            if (node->data <= key) {
                node = node->right;
            } else {
                node = node->left;
            }
        }

        // если не удалось найти узел
        if (z == TNULL) {
            cout<<"Не удалось найти узел в дереве"<<endl;
            return;
        }

        y = z;
        int y_original_color = y->color;
        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }

            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        delete z;
        if (y_original_color == 0){
            fixDelete(x);
        }
    }

    // правка красно черного дерева
    void fixInsert(NodePtr k){
        NodePtr u;
        // если узел красный
        while (k->parent->color == 1) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left; // получаем дядю
                // если дядя красный то перекрашиваем его
                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else { // иначе делаем правый поворот
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right; // получаем дядю

                if (u->color == 1) {
                    u->color = 0;
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = 0;
                    k->parent->parent->color = 1;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root) {
                break;
            }
        }
        root->color = 0;
    }

public:
    RBTree() {
        TNULL = new Node;
        TNULL->color = 0;
        TNULL->left = nullptr;
        TNULL->right = nullptr;
        root = TNULL;
        comparing = 0;
        totalMemory = 0;
        totalMemory += sizeof(Node) + sizeof(root);
    }


    // поиск узла по ключу
    NodePtr searchTree(int k) {
        return searchTreeHelper(this->root, k);
    }

    // ищем узел с минимальным значением, для этого просто спускаемся влево
    NodePtr minimum(NodePtr node) {
        while (node->left != TNULL) {
            node = node->left;
            
        }
        return node;
    }

    // ищем узел с максимальным значением, для этого просто спускаемся вправо
    NodePtr maximum(NodePtr node) {
        while (node->right != TNULL) {
            node = node->right;
        }
        return node;
    }

    // левый поворот
    void leftRotate(NodePtr x) {
        NodePtr y = x->right;
        x->right = y->left;
        if (y->left != TNULL) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    // правый поворот
    void rightRotate(NodePtr x) {
        NodePtr y = x->left;
        x->left = y->right;
        if (y->right != TNULL) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            this->root = y;
        } else if (x == x->parent->right) {
            x->parent->right = y;
        } else {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }

    // вставка ключа и восстановление требований красно-черного дерева
    void insert(int key) {
        NodePtr node = new Node;
        node->parent = nullptr;
        node->data = key;
        node->left = TNULL;
        node->right = TNULL;
        node->color = 1;

        NodePtr y = nullptr;
        NodePtr x = this->root;

        totalMemory += sizeof(Node);
        

        while (x != TNULL) {
            y = x;
            if (node->data < x->data) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        node->parent = y;
        if (y == nullptr) {
            root = node;
        } else if (node->data < y->data) {
            y->left = node;
        } else {
            y->right = node;
        }

        // если узел корень то просто возвращаем его
        if (node->parent == nullptr){
            node->color = 0;
            return;
        }

        if (node->parent->parent == nullptr) {
            return;
        }

        fixInsert(node);
    }

    NodePtr getRoot(){
        return this->root;
    }

    int getComparing() {
        int i = comparing;
        comparing = 0;
        return i;
    }

    int getTotalMemory(){
        return totalMemory;
    }

    // удаление узла из дерева
    void deleteNode(int data) {
        deleteNodeHelper(this->root, data);
    }

};