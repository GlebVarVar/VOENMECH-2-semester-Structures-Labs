### Вариант 12

Граф представляется двумя способами:
1) матрицей смежности или весов 
2) списками смежности 

Для каждого представления требуется написать отдельную программу решения задачи, используя
алгоритм, наиболее подходящий для используемой структуры хранения. 

Для тестирования программ требуется создать файлы с описанием графа одним способом (только матрицей или только списками), обе программы должны уметь заполнять структуры хранения, считывая файлы, как содержащие
матрицы смежности, так и содержащие списки смежных вершин. 

При выборе структур хранения руководствоваться требованием разумной экономии
памяти.


В системе двусторонних дорог за проезд каждой дороги взимается
некоторая пошлина. Найти путь из города А в город В с минимальной
величиной S+P, где S – сумма длин дорог пути, а P – сумма пошлин
проезжаемых дорог. А и В вводятся с клавиатуры. На среднем и повышенном
уровнях сложности помимо найденного пути вывести отдельно S и P.

0;0 1;2 1;3
1;2 0;0 2;4  
1;3 2;4 0;0  
 
 
1;2 
1 - растояние
2 - пошлина


2;1;2 3;1;3
1;1;2 3;2;4  
1;1;3 2;2;4

2;1;3
2 - вершина
1 - растояние
3 - пошлина