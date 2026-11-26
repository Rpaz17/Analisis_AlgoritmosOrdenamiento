// Una ejecucion = correr una vez un algoritmo en un arreglo.
// Forma de uso:  ./sorts <algoritmo> <n> <prueba-trial>
//   ejemplo.  ./sorts bubble 100000 3

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <vector>
#include "GenerateArray.hpp"
#include "SortsT.hpp"
#include "TimeMeasurement.hpp"
using namespace std;

struct Algo
{
    const char *name;
    void (*fn)(int[], int);
};

int main(int argc, char **argv)
{
    Algo algos[] = {
        {"selection", Sorts::selectionSort}, {"insertion", Sorts::insertionSort}, {"bubble", Sorts::bubbleSort}, {"quick", Sorts::quickSort}, {"heap", Sorts::heapSort}, {"merge", Sorts::mergeSort}};

    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " <selection|insertion|bubble|quick|heap|merge> <n> <trial>\n";
        return 1;
    }
    Algo *algo = nullptr;
    for (Algo &a : algos)
        if (strcmp(a.name, argv[1]) == 0)
            algo = &a;
    if (!algo)
    {
        cerr << "Unknown algorithm: " << argv[1] << "\n";
        return 1;
    }
    int n = atoi(argv[2]);
    int trial = atoi(argv[3]);
    if (n <= 0)
    {
        cerr << "n must be > 0\n";
        return 1;
    }

    vector<int> arr(n); // heap mempry
    generateArray(arr.data(), n, trial);

    Sorts::rounds = 0;
    double ms = measureMs(algo->fn, arr.data(), n);
    if (!is_sorted(arr.begin(), arr.end()))
    {
        cerr << algo->name << " FAILED\n";
        return 1;
    }

    // append una fila al excel del resultado
    ifstream check("results.csv");
    bool isNew = !check.good() || check.peek() == EOF;
    check.close();
    ofstream csv("results.csv", ios::app);
    if (isNew)
        csv << "algorithm,n,trial,time_ms,rounds\n";
    csv << algo->name << ',' << n << ',' << trial << ',' << ms << ',' << Sorts::rounds << endl;

    cout << "\r" << algo->name << " n=" << n << " trial " << trial << ": " << ms << " ms, "
         << Sorts::rounds << " rounds        \n";
}
