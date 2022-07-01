#include <stdio.h>
#include <stdlib.h>
#include <locale>
#include <fstream>
#include "randomizeTree.h"
#include <iostream>
#include <io.h>
#include <fcntl.h>

#define SplayTree struct splayTree
#define Node struct node

using namespace std;

int glogal_i=0, first_memory=0;

// BinTree routine
Node {
    int key;
    Node* left, * right, * parent;
};

Node* makeNode(Node* parent, int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    first_memory +=(sizeof(Node) + sizeof(node));
    node->left = node->right = NULL;
    node->parent = parent;
    node->key = key;
    return node;
}

Node* addNode(Node* cur, int key) {
    if(cur->key == key)
        return cur;

    Node* tmp;

    if(cur->key > key) {
        if(cur->left)
            tmp = addNode(cur->left, key);
        else
            tmp = cur->left = makeNode(cur, key);
    }
    else {
        if(cur->right)
            tmp = addNode(cur->right, key);
        else
            tmp = cur->right = makeNode(cur, key);
    }

    return tmp;
}

void del_tree (Node *node)
{
	if (node->left) del_tree (node->left);
	if (node->right) del_tree (node->right);
	free (node);
}

void print_sim (Node *node, int tbl)
{
	if (node->right) print_sim (node->right, tbl+5);
	printf ("%*d\n", tbl, node->key);
	if (node->left) print_sim (node->left, tbl+5);
}

int first_keys = 0, forOneKey;
Node* findNode(Node* cur, Node** prev, int key) {
    forOneKey = 0;
    while(cur) {
        ++first_keys;
        if(++forOneKey && cur->key == key)
        {
            return cur;
        }
        else {
            *prev = cur;
            ++forOneKey;
            cur = (cur->key > key ? cur->left : cur->right);
        }
    }
    return NULL;
}

Node* removeNode(Node** treeRoot, Node* node) {
    Node* prev, * higherClosest, * p, * ch, * removedNode;
    prev = higherClosest = p = ch = NULL;

    if(node->left && node->right) {
        higherClosest = findNode(node, &prev, node->key+1);
        if(!higherClosest) {
            higherClosest = prev;
            p = prev->parent;
        } else {
            p = prev;
        }
        node->key = higherClosest->key;

        if(higherClosest == p->left)
            p->left = higherClosest->right;
        else
            p->right = higherClosest->right;

        if(higherClosest->right)
            higherClosest->right->parent = p;

        removedNode = higherClosest;
    } else {
        p = node->parent;
        ch = node->left ? node->left : node->right;
        if(!p)
            *treeRoot = ch;
        else {
            if(p->left == node)
                p->left = ch;
            else
                p->right = ch;
        }
        if(ch)
            ch->parent = p;

        removedNode = node;
    }

    free(removedNode);
    return p;
}

void chainGrandParent(Node* gp, Node* p, Node* ch) {
    if(gp->left == p)
        gp->left = ch;
    else
        gp->right = ch;
}

// returns new subtree root
Node* rotateRight(Node** treeRoot, Node* r) {
    Node* ch = r->left;

    r->left = ch->right;
    if(ch->right)
        ch->right->parent = r;
    ch->parent = r->parent;

    if(r->parent)
        chainGrandParent(r->parent, r, ch);
    else
        *treeRoot = ch;

    ch->right = r; r->parent = ch;

    return ch;
}
Node* rotateLeft(Node** treeRoot, Node* r) {
    Node* ch = r->right;

    r->right = ch->left;
    if(ch->left)
        ch->left->parent = r;
    ch->parent = r->parent;

    if(r->parent)
        chainGrandParent(r->parent, r, ch);
    else
        *treeRoot = ch;

    ch->left = r; r->parent = ch;

    return ch;
}

// SplayTree operations
SplayTree {
    Node* root;
};

SplayTree* initSplayTree() {
    SplayTree* st = (SplayTree*)malloc(sizeof(SplayTree));
    first_memory += sizeof(SplayTree) + sizeof(st);
    st->root = NULL;

    return st;
}

int isZigZag(Node* cur) {
    Node* p = cur->parent, * gp = p->parent;

    return (p->right == cur && gp->left == p) ||
           (p->left == cur && gp->right == p);
}

void zigZag(Node** treeRoot, Node* cur) {
    Node* p = cur->parent;
    if(p->right == cur && p->parent->left == p)
        rotateRight(treeRoot, rotateLeft(treeRoot, p) -> parent);
    else
        rotateLeft(treeRoot, rotateRight(treeRoot, p) -> parent);
}
void zigZig(Node** treeRoot, Node* cur) {
    Node* p = cur->parent;
    if(p->left == cur && p->parent->left == p)
        rotateRight(treeRoot, rotateRight(treeRoot, p->parent));
    else
        rotateLeft(treeRoot, rotateLeft(treeRoot, p->parent));
}
void zig(Node** treeRoot, Node* cur) {
    Node* p = cur->parent;
    if(p->left == cur)
        rotateRight(treeRoot, p);
    else
        rotateLeft(treeRoot, p);
}

Node* splay(Node** root, Node* cur) {
    if(!cur)
        return NULL;

    while(cur->parent) {
        if(cur->parent->parent)
            if(isZigZag(cur))
                zigZag(root, cur);
            else
                zigZig(root, cur);
        else
            zig(root, cur);
    }
     return cur;
}

Node* insertKey(SplayTree* tree, int key) {
    if(!tree->root)
        tree->root = makeNode(NULL, key);
     return splay(&tree->root, addNode(tree->root, key));
}



int main(void) {

    srand(time(0));
    setlocale(LC_ALL,"");


    ifstream in;
    in.open("test_numbers.txt");
    ifstream KEYS_100("my_100_numbers.txt");
    int key;
    in >> key;
    int keys = 0;
    randomizeTree second(key);
    
    
    int some=0;
        while(!in.eof())
        {
            in >> key;

            second.insert(key);
            some+=sizeof(element);
            // insertKey(first, key);
        }
        in.close();

    int second_keys = 0;
    int fromKeys;
    cout << "key\t" << "    splay" << "  randomize\t" << "sravnenia splay\t\t" << "sravnenia randomize" <<  endl;
    for(;glogal_i<100;glogal_i++)
    {
        KEYS_100 >> fromKeys;
        // bool flag = findKey(first,fromKeys)!=NULL;

        cout << fromKeys << " \t" << 0 << "\t" << second.find(fromKeys)<<"\t"<< forOneKey  << "\t\t\t" << second.sravnenia <<  endl;
        

        second_keys+=second.sravnenia;
    }
    cout << endl;

    cout << "splay) avg for first_keys:" << first_keys/100 <<endl;
    cout << "random) avg for second_keys:" << second_keys/100 <<endl;

    cout << "splay memory: " << first_memory << endl;
    cout << "random memory: " << some << endl << endl;

    cout<< "sizeof(Node): " << sizeof(Node) << "\nsizeof(int): " << sizeof(int) << "\nsizeof(Node*): " << sizeof(Node*);
    return 0;
}
