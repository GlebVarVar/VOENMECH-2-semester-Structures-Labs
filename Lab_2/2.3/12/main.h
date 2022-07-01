#include "iostream"
#include "fstream"
#include "string"
#include "chrono"
#include "string_view"
#include "charconv"
#include "iomanip"
#include "algorithm"



#include "..\..\..\helpFunctions\functions.cpp"


using namespace std;



// стркуктура хранения списков смежности
struct Row {
    
    struct Node {
        int vertice;
        int total;
        int tax;
        int weight;
    };

    int countElements; // количетсво элементов в списке
    struct Node * pointerToArrayOfNodes; // указатель на массив "списка смежности"
    Row(int countElements) {
        this->countElements = countElements;
        this->pointerToArrayOfNodes = new Node[countElements];
    }
};
