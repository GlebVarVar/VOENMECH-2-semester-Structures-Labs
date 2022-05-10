

// Объявления структуры
struct importItem
{
    char itemName[30];
    char countryImporter[18];
    int quantity;
};

// Создание Элиаса(Псевдонима) для структуры (ImportItem)
typedef struct importItem DataType;


// Объявление структуры
struct node
{
    DataType data;
    struct node * next;
};

// Создание Элиаса(Псевдонима) для структуры(Node)
typedef struct node * list;



DataType input_item (void);
list read_file (char * filename);
list new_node (list, DataType);
int write_file (char * filename, list);
void delete_list (list);
void edit (list);
void show (list);
void search (list begin);
list delete_node (list);
// int argc, char * argv[]