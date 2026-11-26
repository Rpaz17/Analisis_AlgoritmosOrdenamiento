#include "TimeMeasurement.hpp"
#include <chrono>

double measureMs(void (*sortFunction)(int[], int), int arr[], int n)
{
    auto start = std::chrono::steady_clock::now();
    sortFunction(arr, n);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(end - start).count();
}
