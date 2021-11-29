# PRiR zadania lab 6
Wzór funkcji do całkowania: f(x) = x^2
Przedziały całkowania: 
```cpp
double pocz = 0;
double kon = 2;
```
Funkcja licząca wartość funkcji:
```cpp
double funct(double x)
```
Funkcje reprezentujące metody całkowania:
```cpp
double Trapez(double a, int proc_nr, double krok, int proc_il)
double Prostokat(double a, int proc_nr, double krok)
```
Obliczanie przybliżenia pi:
```cpp
wynik += 4*(pow(-1, proc_nr)/(2*(proc_nr+1)-1));
```
Przekazywanie/odbieranie obliczeń
```cpp
//calka
MPI_Send(&wynikCalkowania, 1, MPI_DOUBLE, proc_nr-1, 7, MPI_COMM_WORLD);
MPI_Recv(&wynikCalkowania, 1, MPI_DOUBLE, proc_nr+1, 7, MPI_COMM_WORLD, &status);
//pi
MPI_Send(&wynik, 1, MPI_DOUBLE, proc_nr+1, 7, MPI_COMM_WORLD);
MPI_Recv(&wynik, 1, MPI_DOUBLE, proc_nr-1, 7, MPI_COMM_WORLD, &status);
```
