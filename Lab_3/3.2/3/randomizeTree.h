#ifndef RANDOMIZETREE_H_INCLUDED
#define RANDOMIZETREE_H_INCLUDED

struct element // структура для представления узлов дерева
{
    int key;
    int size;
    element* left;
    element* right;
    element(int k) { key = k; left = right = 0; size = 1; }
};

class randomizeTree{
    public:
    element *root;
    int sravnenia;

    randomizeTree(int _root) {
    this->root = new element(_root);
}

element* insert(int);
    bool find(int k);
    void remove(int k);

};

#endif // RANDOMIZETREE_H_INCLUDED