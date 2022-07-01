#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef int DataType;

class Queue
{
 public:
     int sizE;
   virtual int Empty (void) = 0; //проверка на пустоту
   virtual int Full (void) = 0; //проверка на полноту заполнения
   virtual DataType Front (void) = 0; //неразрушающее чтение элемента
   virtual int EnQueue (DataType) = 0; //добавление элемента в очередь
   virtual DataType DeQueue (void) = 0; //извлечение элемента из очереди
   virtual ~Queue();
};

class List: public Queue
{
   struct element
   {
      DataType data;
      element * next;
   } *front, *rear; //индексы головы и хвоста
   
public:
   List () {front=rear=NULL;}
   ~List ();
   int Empty (void) override;
   int Full (void) override;
   DataType Front (void) override;
   int EnQueue (DataType x) override;
   DataType DeQueue (void) override;

};

class Mas: public Queue
{
   int front, rear; //индексы головы и хвоста
   int maxlength;  //размер массива
   DataType *data; //массив для хранения элементов
 public:
   Mas(int n=10);
   ~Mas();
   int Empty (void) override; //проверка на пустоту
   int Full (void) override; //проверка на полноту заполнения
   DataType Front (void) override; //неразрушающее чтение элемента
   int EnQueue (DataType x) override; //добавление элемента в очередь
   DataType DeQueue (void) override; //извлечение элемента из очереди
};

void Go(Queue *);

int main()
{
    char menu;
    puts("1. Vector implementation");
    puts("2. List implementation");
    menu = getchar(); getchar();
    while(!(menu == '1' || menu == '2'))
    {
        puts("1. Vector implementation");
        puts("2. List implementation");
        menu = getchar(); getchar();
    }
    Queue *p;
    switch(menu)
    {
        case '1':
            {

                p = new Mas;
                break;
            }
        case '2':
            {
                p = new List;
            }
    }
    Go(p);
    delete p;
    return 0;
}

Queue::~Queue()
{
}

Mas::Mas(int n): maxlength(n)
{
   data=new DataType[maxlength];
   front=0;
   rear=maxlength-1;
}

Mas::~Mas()
{
   delete[] data;
}

int Mas::Empty(void)
{
   return (rear+1)%maxlength == front;
}

int Mas::Full(void)
{
   return (rear+2)%maxlength == front;
}

DataType Mas::Front (void)
{
   return data[front];
}

int Mas::EnQueue (DataType x)
{
    this->sizE++;
   if (Full()) return 0;
   rear = (rear+1)%maxlength;
   data[rear] = x;
   return 1;
}

DataType Mas::DeQueue (void)
{
   this->sizE--;
   int temp = front;
   front = (front+1)%maxlength;
   return data[temp];
}

// int List::Empty(void)
// {
//    return front==NULL;
// }

// int List::Full(void)
// {
//     if(front!=NULL)
//     {
//         if (sizE==10)
//         return 1;
//     }
//     return 0;
// }

// DataType List::Front (void)
// {
//    return front->data;
// }

// int List::EnQueue (DataType x)
// {
//     this->sizE++;
//    element * temp = new (std::nothrow) element;
//    if (temp==NULL) return 1;
//    temp->data = x;
//    temp->next = NULL;
//    if (front==NULL)
//       front = rear = temp;
//    else
//    {
//       rear->next = temp;
//       rear = rear->next;
//    }
//    return 1;
// }

// DataType List::DeQueue (void)
// {
//     this->sizE--;
//    DataType temp = front->data;
//    element * tmp = front;
//    front = front->next;
//    delete tmp;
//    return temp;
// }

// List::~List ()
// {
//    element * temp = front;
//    while (front)
//    {
//          temp = front;
//          front = front->next;
//          delete temp;
//    }
// }

void Go(Queue *queuE)
{
    queuE->sizE=0;
    int first=0,second=0;//операторы
    bool firstWork=0,secondWork=0;//Состояние работы операторов 1-работают
    int firstReadyToWork=0,secondReadyToWork=0; // Если 0, то он готов к работе, иначе - занят
    int minuts;
    srand(time(0));
    int hours = 8,numberOfCalls = 0,callsInMinute;
    //numberOfCalls - общее количество звонков в поликлиннику
    //сallsInMinute - сколько звонков пришло за одну минуту
    puts(" Time | First | Second | Calls | Queue | Front | Rejected ");
    puts("----------------------------------------------------------");
    for(hours=8;hours<=19;hours++)
    {
    for(minuts=0;minuts<60;minuts++)
    {
        if(firstWork && firstReadyToWork!=0)firstReadyToWork--;//Если оператор работает, то уменишим оставшееся время разговора с клиентом
        if(firstReadyToWork==0)
            {first = 0;firstWork = 0;}

        if(secondWork && secondReadyToWork!=0)secondReadyToWork--;
        if(secondReadyToWork==0)
            {second = 0;secondWork = 0;}

        callsInMinute = rand()%2;//Определяем сколько звонков моступило за одну минуту
        int j = 0;
        int rejected=0,rejected0=0,rejected1=0;
        while(j<callsInMinute)//Добавляем все поступившие звонки в очередь
        {
            if(!queuE->Full())//Если очередь не пуста, то сразу добавляем звонок в очередь
            {
                queuE->EnQueue(++numberOfCalls);
                j++;//счетчик добавленныйх в очередь звонков за одну минуту
            }
            else//Иначе(если она полная)
            {
                bool flag = 1;
                if(firstReadyToWork==0 && !queuE->Empty())//Проверим не освободился ли первый оператор
                {
                    first = queuE->DeQueue();//Если он освободился, то отдадим ему первый звонок в очереди
                    firstReadyToWork = rand()%3+2;//Определим сколько он будет с ним беседовать
                    firstWork = 1;//Отметим что он начал работать
                    flag = 0;//Чтоб не стработал if на 245 строке
                }
                if(secondReadyToWork==0 && !queuE->Empty())//Проверим не освободился ли второйй оператор
                {
                    second = queuE->DeQueue();
                    secondReadyToWork = rand()%3+2;
                    secondWork = 1;
                    flag = 0;
                }
                if(flag)//Если операторы не освободились
                {
                    ++numberOfCalls;
                    j++;
                    if(rejected == 1) {rejected1 = numberOfCalls;rejected++;}//откажем в обслуживании 2 звонку
                    if(rejected == 0) {rejected0 = numberOfCalls;rejected++;}//откажем в обслуживании 1 звонку

                    //printf("%d mimo\n",numberOfCalls);
                }
            }

        }
        if(firstReadyToWork==0 && !queuE->Empty())
        {
            first = queuE->DeQueue();
            firstReadyToWork = rand()%3+2;
            firstWork = 1;
        }
        if(secondReadyToWork==0 && !queuE->Empty())
        {
            second = queuE->DeQueue();
            secondReadyToWork = rand()%3+2;
            secondWork = 1;
        }
        int dd = 0;//Чей звонок перывый в очереди
        if(!queuE->Empty()){dd = queuE->Front();}

        //Вывод сообщений о работе поликлинники
        printf("%2d:",hours);
        if(minuts<10)
            printf("0");
        printf("%d | %5d | %6d | %5d | %5d | %5d |",minuts,first,second,callsInMinute,queuE->sizE,dd);
        if(rejected0!=0)
            printf(" %d",rejected0);
        if(rejected1!=0)
            printf(" %d",rejected1);
        puts("");
    }
    //system("pause");
    }
}
