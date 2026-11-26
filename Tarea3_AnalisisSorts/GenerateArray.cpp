#include "GenerateArray.hpp"
#include <random>

void generateArray(int arr[], int n, unsigned seed)
{
    std::mt19937 gen(seed); // misma seed es mismo arreglo
    std::uniform_int_distribution<int> dist(0, 1000000000);
    for (int i = 0; i < n; i++)
        arr[i] = dist(gen);
}
