#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#include "list_client.h"




int main (int argc, char *argv[])
{

    char file[50];
    char menu;


    if ( argc > 2 )
    {
        printf("Too many arguments\n");
        return 1;
    } else if (argc != 2) {
        printf("File name didn't specify\n");
        puts ("Enter the file name\n");
        gets (file);
    } else {
        printf("File name received '%s'\n", argv[0]);
        strcpy(file, argv[1]);
    }

    // Указатель на начало (голову) списка
    list items = NULL;

    
    // items = read_file (argv[1]);
    items = read_file (file);
    do
    {
       system ("CLS");
       puts ("1. Insert");
       puts ("2. Show");
       puts ("3. Search");
       puts ("4. Delete");
       puts ("5. Exit");
       menu = getchar(); getchar();
       switch (menu)
       {
            case '1': items = new_node (items, input_item()); break;
            case '2': show (items); break;
            case '3': search (items); break;
            case '4': items = delete_node (items);
       }
    }
    while (menu!='5');
    if (write_file (file, items))
        puts ("File saved");
    else
    	puts ("File not saved");
    delete_list (items);
    return 0;
}

// вводим данные об одной позиции
DataType input_item (void)
{
    DataType item;
    puts ("item-Name");
    gets (item.itemName);
    puts ("country-importer");
    gets (item.countryImporter);
    puts ("quantity");
    scanf ("%d", &item.quantity);
	getchar();
    return item;
}

// создание нового узла списка
list new_node (list begin, DataType importItem)
{
    list temp = (list) malloc (sizeof(struct node));
    temp->data = importItem;
    temp->next = begin;
    return temp;
}


// Функция для чтения файла
list read_file (char * filename)
{
    FILE * f;
    DataType item;
    list begin=NULL, cur;
    if ((f = fopen (filename, "rb")) == NULL)
    {
        perror ("Error open file");
        getchar();
        return begin;
    }
    if (fread(&item, sizeof(item), 1, f))
        begin = new_node (NULL, item);
    else
        return NULL;
    cur = begin;
    while (fread(&item, sizeof(item), 1, f))
    {
        cur->next = new_node (NULL, item);
        cur = cur->next;
	}
    fclose(f);
    return begin;
}

// удаление списка
void delete_list (list begin)
{
    list temp = begin;
    while (temp)
    {
        begin = temp->next;
        free (temp);
        temp = begin;
    }
}

// Функция для записи информации в файл
int write_file (char * filename, list begin)
{
    FILE * f;
    if ((f = fopen (filename, "wb")) == NULL)
    {
        perror ("Error create file");
        getchar();
        return 0;
    }
    while (begin)
    {
        if (fwrite (&begin->data, sizeof(DataType), 1, f))
            begin = begin->next;
        else
        	return 0;
    }
    return 1;
}



// Вывод данных на экран
void show (list cur)
{
     int k=0;
     system ("CLS");
     if (cur == NULL)
     {
          puts ("List is empty");
          getchar();
          return;
     }
     puts ("|  N |          item_Name            |   country-importer   | Quantity |");
     puts ("------------------------------------------------------------------------");
     while (cur)
     {
        printf ("|%3d | %-29s |%21s | %8d |\n", ++k, cur->data.itemName,
                 cur->data.countryImporter, cur->data.quantity);
        cur = cur->next;
     }
     puts ("------------------------------------------------------------------------");
     getchar();
}

void search (list cur)
{
     char itemName[50];
     int totalQuantity=0, k=-1;
     DataType item;
     system ("CLS");
     if (cur == NULL)
     {
	    puts ("List is empty");
	    getchar();
	    return;
     }
     puts ("item-name?");
     scanf ("%s",&itemName);
     getchar();
     printf("\n%s %s\n", itemName, "is exported to these countries:");
     while (cur)
     {
        k++;
        if (strcmp (cur->data.itemName, itemName)==0)
        {
           totalQuantity += cur->data.quantity;
           item = cur->data;
            printf("country-importer : %s\n", cur->data.countryImporter);
        }
        cur = cur->next;
     }
     if (totalQuantity == 0) puts ("0 countries");
    printf("\n%s: %d", "Total exported", totalQuantity);
     getchar();
 }

list delete_node (list begin) /*удаление первого элемента*/
{
     struct node * temp;
     if (begin) /*если список не пуст*/
     {
           temp = begin;
           begin = begin->next; /*переставляем указатель на следующий элемент*/
           free (temp); /*первый удаляем*/
           puts ("Deleted");
           getchar();
     }
     return begin;
}
