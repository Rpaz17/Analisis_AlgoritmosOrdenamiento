#include "SortsT.hpp"
#include <iostream>
#include <utility>
using namespace std;

long long Sorts::rounds = 0;

// prints "37%" about every 1% of the outer loop (only for big arrays)
void Sorts::progress(int i, int n)
{
    if (n >= 100000 && i % (n / 100) == 0)
        cout << "\r  " << (long long)i * 100 / n << "%" << flush;
}

// ---------------- O(n^2) sorts ----------------
void Sorts::bubbleSort(int arr[], int n)
{
    for (int pass = 0; pass < n - 1; pass++)
    {
        progress(pass, n);
        bool swapped = false;
        for (int j = 0; j < n - 1 - pass; j++)
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        rounds++;
        if (!swapped)
            break; // ordenado
    }
}

void Sorts::selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        progress(i, n);
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j] < arr[min])
                min = j;
        swap(arr[i], arr[min]);
        rounds++;
    }
}

void Sorts::insertionSort(int arr[], int n)
{
    for (int i = 1; i < n; i++)
    {
        progress(i, n);
        int key = arr[i], j = i;
        while (j > 0 && arr[j - 1] > key)
        {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = key;
        rounds++;
    }
}

// ---------------- Merge sort ----------------
void Sorts::mergeSort(int arr[], int n)
{
    int *tmp = new int[n]; // arreglo auxiliar
    mergeSortHelper(arr, tmp, 0, n - 1);
    delete[] tmp;
}

void Sorts::mergeSortHelper(int arr[], int tmp[], int left, int right)
{
    if (left >= right)
        return;
    int mid = left + (right - left) / 2;
    mergeSortHelper(arr, tmp, left, mid);
    mergeSortHelper(arr, tmp, mid + 1, right);
    mergeHalves(arr, tmp, left, mid, right);
}

void Sorts::mergeHalves(int arr[], int tmp[], int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
        tmp[k++] = (arr[j] < arr[i]) ? arr[j++] : arr[i++];
    while (i <= mid)
        tmp[k++] = arr[i++];
    while (j <= right)
        tmp[k++] = arr[j++];
    for (k = left; k <= right; k++)
        arr[k] = tmp[k];
    rounds++; // un solo merge
}

// ---------------- Heap sort ----------------
void Sorts::heapSort(int arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);
    for (int end = n - 1; end > 0; end--)
    {
        swap(arr[0], arr[end]);
        heapify(arr, end, 0);
        rounds++;
    }
}

void Sorts::heapify(int arr[], int n, int root)
{
    while (true)
    {
        int l = 2 * root + 1, largest = root;
        if (l < n && arr[l] > arr[largest])
            largest = l;
        if (l + 1 < n && arr[l + 1] > arr[largest])
            largest = l + 1;
        if (largest == root)
            return;
        swap(arr[root], arr[largest]);
        root = largest;
    }
}

// ---------------- Quick sort ----------------
void Sorts::quickSort(int arr[], int n) { quickSortHelper(arr, 0, n - 1); }

void Sorts::quickSortHelper(int arr[], int left, int right)
{
    if (left >= right)
        return;
    int p = partition(arr, left, right);
    quickSortHelper(arr, left, p - 1);
    quickSortHelper(arr, p + 1, right);
}

int Sorts::partition(int arr[], int left, int right)
{
    swap(arr[left + (right - left) / 2], arr[right]); // middle element as pivot
    int pivot = arr[right], i = left;
    for (int j = left; j < right; j++)
        if (arr[j] < pivot)
            swap(arr[i++], arr[j]);
    swap(arr[i], arr[right]);
    rounds++; // one partition
    return i;
}
