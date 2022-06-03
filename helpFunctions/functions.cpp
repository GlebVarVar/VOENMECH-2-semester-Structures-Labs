#include "iostream"
#include "string"
// #include "vector"


using namespace std;


// выход из меню
void exitMenu(int exitNumber) {
    cout << string ( 25,  '-' ) << endl;
    cout << exitNumber << ". Exit" << endl <<  endl;
    cout << "> ";
} 

// функция для выбора меню
int getVariant(int count) {

    int var;
    cin.clear();
    string s; // строка для считывания введённых данных
    getline(cin, s); // считываем строку
    // пока ввод некорректен, сообщаем об этом и просим повторить его
    while (sscanf(s.c_str(), "%d", &var) != 1 || var < 1 || var > count) {
        if (s.size() != 0) {
            cout << "Incorrect input. Try again: "; // выводим сообщение об ошибке
            getline(cin, s); // считываем строку повторно
        } else {
            var = getVariant(count);
            if (var >= 1 || var <= count) {
                break;
            }
        }
    }

    return var;
}

// функция для вывода меню
void printMenu(string list[], int size) {
    // выводим меню
    for (int i = 0; i < size; i++) {
        cout << list[i] << endl;
    }
    
}