#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct importItem
{
    char itemName[30];
    char countryImporter[18];
    int quantity;
} item;



int main ()
{
    // struct importItem item;
    // struct importItem item={"hi there", "hi there", 1};
    // input itemName in item.itemName
    scanf("%s", item.itemName);
    printf("%s\n", item.itemName);
    

    return 0;
} 