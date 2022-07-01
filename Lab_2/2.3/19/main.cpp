#include <iostream>
#include <cstring>
#include "List.h"

#define INF 9999

using namespace std;

struct DataType {
    int node;
    int weight;
};
int Floyd(int **matrix, int numberOfVert);//Алгоритм по заданию
int verticesFromMatrix(FILE *f1);
int verticesFromList(FILE *f1);
int *countInRowFromList(FILE *f1, int *countInRow);
int **listInMatrix(List<DataType> *a, int numberOfVert);
char type_struct(FILE *f1);

int main() {
    char type, user_type, filename[80];
    int n, rez;
    FILE *f1;
    cout << "enter file name .txt" << endl;
    cin >> filename;
    strcat(filename, ".txt");
    if ((f1 = fopen(filename, "r")) == nullptr) {
        perror("File opening error");
        return 1;
    }
    type = type_struct(f1);//Определение типа, заданного в файле
    do {
        cout << "enter structure type" << endl;
        cout << "1.Matrix" << endl;
        cout << "2.Lists" << endl;
        cin >> user_type;
    } while (user_type != '1' && user_type != '2');
    if (type == 0) {
        if (user_type == '1') {
            n = verticesFromMatrix(f1); //Кол-во вершин матрицы
            int **pGR = new int *[n];
            for (int i = 0; i < n; i++) {
                pGR[i] = new int[n];
            }
            cout << "Reading the Edge Weight Matrixр:" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    fscanf(f1, "%d", &pGR[i][j]);
                }
            }
            fclose(f1);
            rez = Floyd(pGR, n);
            cout << "Сумма расстояний до остальных городов минимальна в городе №" << rez << endl;
        } else if (user_type == '2') {
            n = verticesFromMatrix(f1);//Кол-во вершин матрицы
            DataType x{}; //Чтение из файла с матрицей в список смежности весов 55-69
            List<DataType> *a;
            a = new List<DataType>[n];
            cout << "Reading the Edge Weight Matrix:\n";
            int number;
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; j++) {
                    fscanf(f1, "%d", &number);
                    if (number != 0 && number != INF) {
                        x.node = j + 1;
                        x.weight = number;
                        a[i].push_back(x);
                    }
                }
            }
            fclose(f1);
            int **pGR = listInMatrix(a, n);
            rez = Floyd(pGR, n);
            cout << "Сумма расстояний до остальных городов минимальна в городе №" << rez << endl;
        }
    } else {
        if (user_type == '2') {
            n = verticesFromList(f1); //Кол-во вершин в списках смежности
            int *countInRow = new int[n]{}; //Сколько вершин в каждой строке
            countInRow = countInRowFromList(f1, countInRow);
            DataType x{}; //Чтение из файла списка смежности весов 79-88
            List<DataType> *a;
            a = new List<DataType>[n];
            cout << "Reading the Edge Weight Matrix:\n";
            for (int j = 0; j < n; ++j) {
                for (int i = 0; i < countInRow[j]; i++) {
                    fscanf(f1, "%d;%d", &x.node, &x.weight);
                    a[j].push_back(x);
                }
            }
            fclose(f1);
            int **pGR = listInMatrix(a, n);
            rez = Floyd(pGR, n);
            cout << "Сумма расстояний до остальных городов минимальна в городе №" << rez << endl;
        } else if (user_type == '1') {
            n = verticesFromList(f1); //Кол-во вершин в списках смежности
            int *countInRow = new int[n]{};//Сколько узлов списка в каждой строке файла
            countInRow = countInRowFromList(f1, countInRow);
            int **pGR = new int *[n]{}; //Чтение из файла матрицы весов ребер 96-104
            for (int i = 0; i < n; ++i) {
                pGR[i] = new int;
                for (int j = 0; j < n; ++j) {
                    if (i == j)
                        pGR[i][j] = 0;
                    else
                        pGR[i][j] = INF;
                }
            }
            int node;
            int weight;
            cout << "Reading the Edge Weight Matrix:\n";
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < countInRow[i]; j++) {
                    fscanf(f1, "%d;%d", &node, &weight);
                    pGR[i][node - 1] = weight;
                }
            }
            fclose(f1);
            rez = Floyd(pGR, n);
            cout << "The sum of distances to other cities is minimal in the city №" << rez << endl;
        }
    }
    return 0;
}

int verticesFromMatrix(FILE *f1) {
    int c;
    int n = 0;
    cout << "Number of vertices in a graph > ";
    while ((c = fgetc(f1)) != '\n') {
        if (c == ' ')
            n++;
    }
    cout << ++n << endl;
    rewind(f1);
    return n;
}

int verticesFromList(FILE *f1) {
    int c;
    int n = 0;
    cout << "Number of vertices in a graph > ";
    while ((c = fgetc(f1)) != EOF) {
        if (c == '\n') {
            n++;
        }
    }
    cout << ++n << endl;
    rewind(f1);
    return n;
}

int *countInRowFromList(FILE *f1, int *countInRow) {
    int row = 0;
    int c;
    while ((c = fgetc(f1)) != EOF) {
        if (c == ';') {
            countInRow[row]++;
        }
        if (c == '\n' || c == EOF) {
            row++;
        }
    }
    rewind(f1);
    return countInRow;
}

int Floyd(int **matrix, int numberOfVert) {
    float A[numberOfVert][numberOfVert];
    int i, j, k=0, sum=0, min=999999;
    for (i=0; i<numberOfVert; i++)
       for (j=0; j<numberOfVert; j++) {
           A[i][j] = matrix[i][j];
       }
    for (i=0; i<numberOfVert; i++)
       A[i][i] = 0;
    for (k=0; k<numberOfVert; k++)
        for (i=0; i<numberOfVert; i++)
            for (j=0; j<numberOfVert; j++)
                if ( A[i][k] + A[k][j] < A[i][j] ) { /* если путь через k короче */
                    A[i][j] = A[i][k] + A[k][j]; /* запоминаем длину пути */
                }
    for (int i=0; i<numberOfVert; i++) {
        for (int j=0; j<numberOfVert; j++) {
            cout << A[i][j] << " ";
            sum+=A[i][j];
        }
        cout << endl;
        if (sum<min) {
            min = sum;
            k = i;
        }
        sum = 0;
    }
    return k+1;
}

int **listInMatrix(List<DataType> *a, int numberOfVert) {
    int **matrix = new int *[numberOfVert];
    for (int i = 0; i < numberOfVert; i++)
        matrix[i] = new int[numberOfVert]{};
    for (int i = 0; i < numberOfVert; ++i) {
        for (int j = 0; j < numberOfVert; ++j) {
            matrix[i][j] = INF;
            if (i == j) {
                matrix[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < numberOfVert; ++i) {
        int size = a[i].GetSize();
        for (int j = 0; j < size; ++j) {
            int node = a[i][j].node;
            int weight = a[i][j].weight;
            matrix[i][node-1] = weight;
            matrix[node-1][i] = weight;
        }
    }
    return matrix;
}

char type_struct(FILE *f1) {
    int c;
    while ((c = fgetc(f1)) != EOF) {
        if (c == ';') {
            rewind(f1);
            return 1;
        }
    }
    rewind(f1);
    return 0;
}
