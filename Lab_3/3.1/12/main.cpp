#include <iostream>
#include <random>
#include <fstream>
#include <math.h>
#include <time.h>
#include <vector>
#include <algorithm>
#define N 100000

using namespace std;

long long int counter =0, counterHelp = 0;

// Количество памяти
int memory_StraightInsertion=0,
    memory_ShellSort=0,
    memory_tim_sort=0,
    memory_NaturalMergeSort=0;

void StraightInsertion (int *a, int n);  
void ShellSort (int *a, int n) ;           
void tim_sort(int * a, int n);
void NaturalMergeSort(int *a, int n);

void writeFromFile(string file,int n);
void writeDown(string file,int n);

int p[N];

clock_t start, finish;

string TEST_NUMBERS = "test_numbers.txt";
string KEYS_10 = "10key.txt";
string KEYS_100 = "100key.txt";
string KEYS_500 = "500key.txt";
string KEYS_1000 = "1000key.txt";


int main() {

    void (*f[4])(int *, int) = {
        StraightInsertion,
        ShellSort,
        tim_sort,
        NaturalMergeSort
    };

    //system("pause");
    ///Основная часть
    cout << "\t\t\t\t\t\t\t\t\tMAIN" << endl;
    cout << endl;

        for (int j=0; j<4; j++)                                     //Для каждого алгоритма
        {
            if(j==0) cout << "\t\t\t\t\t\t\t\t\tStraightInsertion" <<endl;
            else if (j==1) cout << "\t\t\t\t\t\t\t\t\Shell" <<endl;
            else if (j==2) cout << "\t\t\t\t\t\t\t\t\Timsort" <<endl;
            else if (j==3) cout << "\t\t\t\t\t\t\t\t\tNaturalMergeSort" <<endl;

            cout << "----------------------------------" << endl;
            int ii = 10000;
            while(ii <= 100000) {                 //Разные N 
                cout << "\t\t\t\t\t\t\t\t\t|" << ii << "|" <<endl;
                for (int i=0;i<3;i++)                               //Разной упорядочности
                {
                    switch(i)
                    {
                        case 0: writeFromFile(TEST_NUMBERS,ii); cout << "Random: " <<endl; break; //Рандомный порядок из файла
                        case 1: cout << "Up: " <<endl; break; //Значения из файла отсортированные по возрастанию
                        case 2: writeDown(TEST_NUMBERS,ii); cout << "Down: " <<endl;    //Значения из файла отсортированные по убыванию
                    }
                    counterHelp = counter = 0;
                    f[j](p,ii);
                    cout <<"counterHelp: "<< counterHelp<<" counterMain: "<< counter << " time: " << (double)(finish-start) / CLOCKS_PER_SEC << "s" << endl ;
                    cout << endl;
                }
                cout << "----------------------------------" << endl;

                switch (ii) {
                    case 10000: ii = 30000; break;
                    case 30000: ii = 70000; break;
                    case 70000: ii = 100000; break; 
                    case 100000: ii = 200000; break;
                }
            }

            

        }

    cout << "memory_StraightInsertion: " << memory_StraightInsertion << endl << "memory_ShellSort: " << memory_ShellSort << endl;
    cout << "memory_tim_sort: " << memory_tim_sort << endl << "memory_NaturalMergeSort: " << memory_NaturalMergeSort << endl;
    system("pause");
    cout << endl;
    cout << "\t\t\t\t\t\t\t\t\tADVANCED" << endl;
    cout << endl;

    ///На повышенный
    {
    //Все аналогично базовой части за исключением набора значений(кол-во повторяющихся элементов)
        for (int j=0; j<4; j++)
        {
            if(j==0) cout << "\t\t\t\t\t\t\t\t\tStraightInsertion" <<endl;
            else if (j==1) cout << "\t\t\t\t\t\t\t\t\Shell" <<endl;
            else if (j==2) cout << "\t\t\t\t\t\t\t\t\Timsort" <<endl;
            else if (j==3) cout << "\t\t\t\t\t\t\t\t\tNaturalMergeSort" <<endl;

            cout << "----------------------------------" << endl;
            int ii = 10000;
            while(ii <= 100000) {
                cout << "\t\t\t\t\t\t\t\t\t|" << ii << "|" <<endl;
                for(int t=0;t<4;t++)
                {
                    string file;
                    switch(t){
                        case 0: file = KEYS_10; break;
                        case 1: file = KEYS_100; break;
                        case 2: file = KEYS_500; break;
                        case 3: file = KEYS_1000;
                    }

                    cout << "\t" << file << endl;

                    for (int i=0;i<3;i++)
                    {

                        switch(i){
                            case 0: writeFromFile(file,ii); cout << "Random: " <<endl; break;
                            case 1: cout << "Up: " <<endl; break;
                            case 2: writeDown(file,ii); cout << "Down: " <<endl;
                        }
                        counterHelp= counter = 0;
                        f[j](p,ii);
                        cout <<"per: "<< counterHelp<<" main: "<< counter << " time: " << (double)(finish-start) / CLOCKS_PER_SEC <<endl;
                        cout << endl;
                    }
                    cout << "----------------------------------" << endl;
                }

                switch (ii) {
                    case 10000: ii = 30000; break;
                    case 30000: ii = 70000; break;
                    case 70000: ii = 100000; break; 
                    case 100000: ii = 200000; break;
                }
            }
        }
    }
    return 0;
}

// прямые вставки
void StraightInsertion (int *arr, int sizeOfArray) {
    
    // cout << memory_StraightInsertion << endl;

    start = clock();
    int i, j, currentKey;
    if(sizeOfArray==100000)memory_StraightInsertion += (3*sizeof(int));

    for ( counterHelp++, i = 1; i < sizeOfArray; i++, counterHelp++) {

    	currentKey = arr[i];
		counter++;

    	for (j = i, counterHelp++; j && currentKey < arr[j-1]; j--, counterHelp++) { /* находим место вставки, попутно сдвигая элементы */
    		arr[j] = arr[j-1];
			counter++;
		}
    	arr[j] = currentKey;
		counter++;
		
    }
    finish = clock();
}

// shell
void ShellSort(int* massive, int n) {
/*шаг задается формулой h[t]=1, h[m]=2h[m+1]+1; t=log2(n)-1*/
    start = clock();

    const int t = (int)(log(n) / log(2) - 1); 
    int i, j, k, m, x;
    int* h = (int*)malloc(t * sizeof(int)); h[t - 1] = 1; counterHelp++;

    for (m = t - 2, counterHelp++; m >= 0; m--, counterHelp++) {
        h[m] = h[m + 1] * 2 + 1; counterHelp++;
    }
    if(n==100000)memory_ShellSort += (6*sizeof(int) + t * sizeof(int));
    for (counterHelp++, m = 0; m < t; m++, counterHelp++) {/*последовательно перебираем все расстояния*/
    
        k = h[m]; counterHelp++;
        for (counterHelp++, i = k; i < n; i++, counterHelp++) {/*до конца цикла метод вставки с учетом шага h[m]*/
        
            x = massive[i]; j = i - k; counterHelp++; counter++;

            while (j >= 0 && x < massive[j]) {
            
                massive[j + k] = massive[j]; j -= k;
                counterHelp++; counter++;
            }
            massive[j + k] = x;counter++;
        }
    }
    free(h);
    finish = clock();
}

// естественное слияние
void NaturalMergeSort(int *a, int n)
{
    
    int split;                   /* индекс, по которому делим массив */
    int last, end, i, *p=a, *tmp; counterHelp++;
    char flag = 0, sorted = 0; counterHelp+=2;
    int pos1, pos2, pos3;
    if(n==100000)memory_NaturalMergeSort += (n*sizeof(int) + sizeof(last)*7 + sizeof(p));
    tmp = (int*) malloc (n*sizeof(int)); counterHelp++;
    do {               /* если есть более 1 элемента */
  
        end = n; pos2 = pos3 = 0; counterHelp+=3;
        do {
        
            p += pos2; end = n - pos3; counterHelp+=2;
            for (split=1, counterHelp++; split < end && p[split-1] <= p[split]; split++, counterHelp++); /*первая серия*/
            if (split == n) {
                sorted = 1 ; counterHelp++; break;
            }
            pos1 = 0; pos2 = split; counterHelp+=2;
            while ( pos1 < split && pos2 < end ) {	/*идет слияние, пока есть хоть один элемент в каждой серии*/
            
                if (p[pos1] < p[pos2]) {
                    tmp[pos3++] = p[pos1++]; counter++; counterHelp+=2;
                } else {
                    tmp[pos3++] = p[pos2++]; counter++; counterHelp+=2;
                    if (p[pos2] < p[pos2-1]) break;
                }
            }
            /* одна последовательность закончилась - копировать остаток другой в конец буфера */
            while ( pos2 < end && tmp[pos3-1]<=p[pos2] )  {
                tmp[pos3++] = p[pos2++]; counter++; counterHelp+=2;
            } 			 /* пока вторая последовательность не пуста */
                
            while ( pos1 < split )   {
                	/* пока первая последовательность не пуста */
                tmp[pos3++] = p[pos1++]; counter++; counterHelp+=2;
            }	
        } while (pos3 < n );

        if (sorted) break;

        p = tmp;  counterHelp++;
        tmp = a; counterHelp++;
        a = p; counterHelp++;
        flag = !flag; counterHelp++;

    } while (split < n);

    if (flag) {
        for (pos1 = 0, counterHelp++; pos1 < n; pos1++, counterHelp++) {
            tmp[pos1] = a[pos1]; counter++;
        }
            
        free (a);
    }
    else
        free (tmp);
}


// Timsort
typedef struct {
  int *beg; /* адрес начала последовательности */
  int len; /* длина последовательности */
}segment;

/* вычисление длины последовательности в зависимости от N*/
/* ответ должен быть в диапазоне (32,64]*/
int get_min_size (int n) {
  int r = 0; counterHelp++;
  if (n==100000) memory_tim_sort += sizeof(r);
  while (n >= 64) {
    n >>= 1; counterHelp++;
    r |= n & 1; counterHelp++;
  }
  return n + r;
}

/*разворот массива*/
void reverse (int *a, int n) {
    int i, j, tmp;
    for (i=0, j=n-1, counterHelp+=2; i<j; i++, j--, counterHelp+=2) {
        if (a[i]!=a[j]) {
            tmp = a[i]; counter++; 
            a[i] = a[j]; counter++; 
            a[j] = tmp; counter++; 
        }
    }
        
}

/* сортировкa вставками */
void insertion_sort(int *a, int n, int i) {/*адрес начала массива, его размер, размер уже упорядоченной части*/

    int j, x;
    for (; i<n; ++i, counterHelp++) {
        x = a[i]; counter++; 
        for (j=i, counterHelp++; j && a[j-1]>x; --j, counterHelp++) {
            a[j] = a[j-1]; counter++; 
        }
            
        a[j]=x; counter++; 
    }
}
/*слияние с предварительным копированием во вспомогательный массив более короткой последовательности*/
void merge_copy_less (segment * seg) {
    int *a = seg[0].beg; /*адрес начала первой из сливаемых последовательностей*/
    int split = seg[0].len; /*длина первой последовательности*/
    int n = split + seg[1].len; /*длина результирующей последовательности*/
    int pos1=0;	/* текущая позиция чтения из первой последовательности a[0]...a[split] */
    int pos2=split;	/*текущая позиция чтения из второй последовательности a[split]...a[n]*/
    int pos3=0;  /*текущая позиция записи в результирующей последовательности*/
    int *temp;
    counterHelp+=6;
    if (seg[0].len < seg[1].len) {
        temp = (int*)malloc(sizeof(int)*split);
        /*копируем первую последовательность во вспомогательный массив*/
        for (pos1 = 0, counterHelp++; pos1 < split; pos1++, counterHelp++) {
            temp[pos1] = a[pos1]; counter++; 
        }
            
        pos1 = 0;
        while (pos1 < split && pos2 < n) {	/*идет слияние, пока есть хоть один элемент в каждой последовательности*/
            if (temp[pos1] <= a[pos2]) {
                a[pos3++] = temp[pos1++]; counterHelp+=2; counter++; 
            } else {
                a[pos3++] = a[pos2++]; counterHelp+=2; counter++; 
            }
                
        }
        /* одна последовательность закончилась - копировать остаток другой в конец буфера */
        /* даже если вторая последовательность не пуста, она уже на месте */
        while (pos1 < split)  {
            	/* пока первая последовательность не пуста */
            a[pos3++] = temp[pos1++]; counter++;  counterHelp+=2;
        }	
    } else {
        temp = (int*)malloc(sizeof(int)*seg[1].len);
        /*копируем вторую последовательность во вспомогательный массив*/
        for (pos1 = 0, pos2 = split, counterHelp+=2; pos2 < n; ) {
            temp[pos1++] = a[pos2++]; counter++;  counterHelp+=2;
        }
            
        /*в этом случае слияние производится справа налево*/
        pos1 = split-1; pos2 = seg[1].len-1; pos3 = n-1; counterHelp+=3;
        while (pos1 >= 0 && pos2 >= 0) { 	/*идет слияние, пока есть хоть один элемент в каждой последовательности*/
            if (temp[pos2] > a[pos1]) {
                a[pos3--] = temp[pos2--]; counter++;  counterHelp+=2;
            } else {
                a[pos3--] = a[pos1--]; counter++;  counterHelp+=2;
            }
                
        }
        /* одна последовательность закончилась - копировать остаток другой в конец буфера */
        /* даже если первая последовательность не пуста, она уже на месте */
        while (pos2 >= 0) {  		/* пока вторая последовательность не пуста */
            a[pos3--] = temp[pos2--]; counter++;  counterHelp+=2;
        }
    }
    free (temp);
    seg[0].len = n; counterHelp++;/*фиксируем длину полученной последовательности в стеке*/ 
}

/*слияние близких по размеру последовательностей*/
int try_merge(segment *seg, int top) {
    int x, y, z;
    while (top>0) {/*пока в стеке больше одного элемента*/
    
        x = seg[top].len; counterHelp++;
        y = seg[top-1].len; counterHelp++;
        z = top>1 ? seg[top-2].len : 0; counterHelp++;
        if (top>1 && z <= x+y) {/*если в стеке не меньше трех элементов и третий сверху маловат*/
        
            if (z < x) {
                merge_copy_less(&seg[top-2]); /*сливаем ZY*/
                seg[top-1] = seg[top]; /*корректируем стек*/ counterHelp++;
            } else {
                merge_copy_less(&seg[top-1]); /*сливаем YX*/
            }
            top--;  /*стало на одну последовательность меньше*/ counterHelp++;
        }
        else
            if (y <= x) {/*если предпоследний не больше последнего*/
            
                merge_copy_less(&seg[top-1]); /*сливаем YX*/
                top--; counterHelp++;
            } else {
                break;
            }
               
    }
    return top;
}

void tim_sort(int * a, int n) {
    start = clock();

    int min_size = get_min_size(n); counterHelp++;
    int size;
    int i, j=0; counterHelp++;
    /*стек координат последовательностей*/
    segment * seg = (segment*) malloc (((n-1)/min_size + 1) * sizeof(segment));counterHelp++;
    int t=-1; /*вершина стека*/ counterHelp++;
    if (n==100000) memory_tim_sort += (sizeof(min_size) + sizeof(size) + sizeof(i) + sizeof(j) + sizeof(t) + ((n-1)/min_size + 1)*sizeof(segment) + sizeof(seg));

    /*формирование упорядоченных последовательностей*/
    for (i=0, counterHelp++; i<n; i+=size, counterHelp++ ) {
        for (j=i+1, counterHelp++; j<n && a[j-1]>=a[j]; j++, counterHelp++); /*поиск обратно упорядоченной последовательности*/
        if (j!=i+1) {
            reverse (a+i, j-i); 
            if (n==100000) memory_tim_sort += sizeof(int)*3;
        }
                     /*переворачиваем найденную обратную последовательность*/
        if (j!=n && j-i<min_size) {
            size = n-i < min_size ? n-i : min_size; counterHelp++;
            if (n==100000) memory_tim_sort += sizeof(int)*2;
            insertion_sort (a+i, size, j-i ); /*адрес начала фрагмента, его размер, размер упорядоченной части*/
            j = i + size; counterHelp++;
        }
        for (; j<n && a[j-1]<=a[j]; j++, counterHelp++); /*ищем конец последовательности, если она не закончилась*/
        /*запоминаем адрес начала и длину последовательности в стеке*/
        seg[++t].beg = a+i; counterHelp++;
        size = seg[t].len = j-i; counterHelp+=2;
        if (n==100000) memory_tim_sort += sizeof(int)*3;
        t = try_merge(seg, t); counterHelp++;
    }
    /*слияние всех оставшихся последовательностей*/
    while (t>0)
    {
        if (n==100000) memory_tim_sort += sizeof(int*)*2 + sizeof(int)*5;
        merge_copy_less(&seg[t-1]); /*сливаем две последние последовательности*/
        t--; /*количество последовательностей уменьшилось*/counterHelp++;
    }
    free(seg);
    finish = clock();
}

void writeFromFile(string fileName,int n)
{
    ifstream file;
    file.open(fileName);
    if(file)
    {
        int t;
        for (int i = 0; i < n; i++) {
            file >> t;            //в t значения очередного числа из второй строчки
            p[i] = t;
        }
        file.close();
    }else
        cout<<"nope";
}

void writeDown(string fileName,int n) {
    for(int i=0;i<n/2;i++) {
        int temp = p[i];
        p[i] = p[n-i-1];
        p[n-i-1] = temp;
    }
}
