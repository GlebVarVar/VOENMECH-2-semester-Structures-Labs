#include "iostream"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <locale>
#include <fstream>


using namespace std;

struct element // структура для представления узлов дерева
{
    element* left;
    element* right;
    int key;
    int size;
    element(int k) { key = k; left = right = 0; size = 1; }
};


class randomizeTree{
    public:
    element *root;
    int comparing = 0;
    int totalMemory = 0;

    int getComparing() {return comparing;}
    int getTotalMemory() {return totalMemory;}

    randomizeTree(int _root) {
    this->root = new element(_root);
}

element* insert(int);
    
    bool find(int k);
    void remove(int k);

};


// обертка для поля size, работает с пустыми деревьями (t=NULL)
int getsize(element* p) { 
	if( !p ) return 0;
	return p->size;
}

// установление корректного размера дерева
void fixsize(element* p) {
	p->size = getsize(p->left)+getsize(p->right)+1;
}




// правый поворот вокруг узла p
element* rotateright(element* p) {

	element* q = p->left;
	if( !q ) return p;
	p->left = q->right;
	q->right = p;
	q->size = p->size;
	fixsize(p);
	return q;
}

// левый поворот вокруг узла q
element* rotateleft(element* q)  {
	element* p = q->right;
	if( !p ) return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	fixsize(q);
	return p;
}





// вставка нового узла с ключом k в корень дерева p
element* insertroot(element* p, int k) {

	if( !p ) return new element(k);
	if( k<p->key )
	{
		p->left = insertroot(p->left,k);
		return rotateright(p);
	}
	else
	{
		p->right = insertroot(p->right,k);
		return rotateleft(p);
	}
}






// объединение двух деревьев
element* join(element* p, element* q) {

	if( !p ) return q;
	if( !q ) return p;
	if( rand()%(p->size+q->size) < p->size )
	{
		p->right = join(p->right,q);
		fixsize(p);
		return p;
	}
	else
	{
		q->left = join(p,q->left);
		fixsize(q);
		return q;
	}
}

// рандомизированная вставка нового узла с ключом k в дерево p
element* _insert(element* p, int k) {

	if( !p ) return new element(k);
	if( rand() % ( p->size + 1 ) == 0 ) {
        p = insertroot(p,k);
        return p;
    }

	if( p->key >k )
		p->left = _insert(p->left,k);
	else
		p->right = _insert(p->right,k);
    fixsize(p);
	return p;
}

// рандомизированная вставка нового узла с ключом k в дерево p
element* randomizeTree::insert(int k) {

	return this->root = _insert(this->root,k);
}

// поиск ключа k в дереве p
int Main_second = 0;
element* _find(element* p, int k) {

    if( ++Main_second && !p ) return 0;
    if( ++Main_second && k == p->key ) return p;
    if( ++Main_second && k < p->key ) {
        return _find(p->left,k);
	} else{
		return _find(p->right,k);
	}
        
}

// поиск ключа k в дереве p
bool randomizeTree::find(int k) {

    bool flag = _find(this->root,k) != NULL;
    this->comparing=Main_second;
    Main_second=0;
    return flag;
}

// удаление из дерева p первого найденного узла с ключом k
element* _remove(element* p, int k) {

	if( !p ) return p;
	if( p->key==k ) {
		element* q = join(p->left,p->right);
		delete p;
		return q;
	}
	else if( k<p->key )
		p->left = _remove(p->left,k);
	else
		p->right = _remove(p->right,k);
	return p;
}

// удаление из дерева p первого найденного узла с ключом k
void randomizeTree::remove(int k) {
	_remove(this->root,k);
}