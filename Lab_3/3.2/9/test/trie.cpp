#include <stdio.h>
#include <stdlib.h>
#define N 10

struct node
{
	char eok;
	struct node *p[10];
};

typedef struct node node;

node *make_node()
{
	int i;
	node *nd = (node *)malloc(sizeof(node));
	nd->eok = 0;
	for (i = 0; i < N; i++)
		nd->p[i] = NULL;
	return nd;
}

node *insert_key(node *trie, char *key)
{
	if (trie == NULL)
		trie = make_node();
	if (*key >= '0' && *key <= '9')										/*текущую цифру*/
		trie->p[*key - '0'] = insert_key(trie->p[*key - '0'], key + 1); /*добавляем в дерево и продолжаем строить*/
	else
		trie->eok = 1; /*ключ кончился - устанавливаем признак конца ключа*/
	return trie;
}

int find_key(node *trie, char *key)
{
	if (trie == NULL) /*если узел не обнаружен, то ключ не найден*/
		return 0;
	if (*key >= '0' && *key <= '9')
		return find_key(trie->p[*key - '0'], key + 1); /*пока не конец ключа продолжаем поиск*/
	if (trie->eok)									   /* если кончился ключ и в узле установлен признак конца ключа, то значение найдено */
		return 1;
	return 0;
}

node *remove_key(node *trie, char *key)
{
	int i;
	if (*key >= '0' && *key <= '9')
		if (trie->p[*key - '0'] != NULL)
			trie->p[*key - '0'] = remove_key(trie->p[*key - '0'], key + 1);
		else
			return trie;
	else
		trie->eok = 0;
	for (i = 0; i < N; i++)
		if (trie->p[i] != NULL)
			return trie;
	if (!trie->eok)
	{
		free(trie);
		trie = NULL;
	}
	return trie;
}

node *delete_trie(node *trie)
{
	int i;
	for (i = 0; i < N; i++)
		if (trie->p[i] != NULL)
			trie->p[i] = delete_trie(trie->p[i]);
	free(trie);
	return NULL;
}

int main()
{
	node *trie = make_node();
	int menu;
	char key[11]; /* максимум десятизначное число */
	do
	{
		system("cls");
		puts("1 - Insert key");
		puts("2 - Delete key");
		puts("3 - Find the key");
		puts("0 - Exit");
		scanf("%d%*c", &menu);
		if (menu < 0 || menu > 3)
			continue;
		else if (!menu)
			break;
		puts("Enter key");
		scanf("%s", key);
		switch (menu)
		{
		case 1:
			trie = insert_key(trie, key);
			break;
		case 2:
			trie = remove_key(trie, key);
			break;
		case 3:
			if (find_key(trie, key))
				puts("found");
			else
				puts("not found");
			system("pause");
		}
	} while (menu);
	delete_trie(trie);
	system("pause");
	return 0;
}
