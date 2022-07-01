#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "randomizeTree.h"

using namespace std;

int getsize(element* p) // обертка для поля size, работает с пустыми деревьями (t=NULL)
{
	if( !p ) return 0;
	return p->size;
}

void fixsize(element* p) // установление корректного размера дерева
{
	p->size = getsize(p->left)+getsize(p->right)+1;
}

element* rotateright(element* p) // правый поворот вокруг узла p
{
	element* q = p->left;
	if( !q ) return p;
	p->left = q->right;
	q->right = p;
	q->size = p->size;
	fixsize(p);
	return q;
}

element* rotateleft(element* q) // левый поворот вокруг узла q
{
	element* p = q->right;
	if( !p ) return q;
	q->right = p->left;
	p->left = q;
	p->size = q->size;
	fixsize(q);
	return p;
}

element* insertroot(element* p, int k) // вставка нового узла с ключом k в корень дерева p
{
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

element* join(element* p, element* q) // объединение двух деревьев
{
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

element* _insert(element* p, int k) // рандомизированная вставка нового узла с ключом k в дерево p
{
	if( !p ) return new element(k);
	if( rand()%(p->size+1)==0 )
    {
        p = insertroot(p,k);
        return p;
    }

	if( p->key>k )
		p->left = _insert(p->left,k);
	else
		p->right = _insert(p->right,k);
    fixsize(p);
	return p;
}

element* randomizeTree::insert(int k) // рандомизированная вставка нового узла с ключом k в дерево p
{
	return this->root = _insert(this->root,k);
}

int Main_second = 0;
element* _find(element* p, int k) // поиск ключа k в дереве p
{
    if( ++Main_second && !p ) return 0;
    if( ++Main_second && k == p->key )
        return p;
    if( ++Main_second && k < p->key )
        return _find(p->left,k);
    else
        return _find(p->right,k);
}

bool randomizeTree::find(int k) // поиск ключа k в дереве p
{
    bool flag = _find(this->root,k) != NULL;
    this->sravnenia=Main_second;
    Main_second=0;
    return flag;
}

element* _remove(element* p, int k) // удаление из дерева p первого найденного узла с ключом k
{
	if( !p ) return p;
	if( p->key==k )
	{
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

void randomizeTree::remove(int k) // удаление из дерева p первого найденного узла с ключом k
{
	_remove(this->root,k);
}
