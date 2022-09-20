#include "iostream"
#include "fstream"


// [10000000; 100000000)

using namespace std;

// create function that generates 100 random numbers from 10000000 to 100000000 and save them to file
void create100numbers() {
    ifstream test_numbers;
    long int current_key;
    ofstream file, testKeyFrom;
    file.open("my_100_numbers.txt");
    testKeyFrom.open("files.txt");
    test_numbers.open("test_numbers.txt");
    long int number;
    for (int i = 0; i < 46; i++) {
        
        
        // generate random number from 10000000 to  100000000
        number = rand() % 100000000 * rand() % 10000000  + rand() % 10 * 10000000;
        if (number < 10000000) {
            number += 10000000;
        }
        
        file << number << endl;
        

    }
    for (int j =0; j < 50; j++) {
        test_numbers >> current_key;
        file << current_key << endl;
    }
    
    
    file.close();
}



int main() {

    
    create100numbers();

    return 0;
}

