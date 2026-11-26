#pragma once

class Sorts
{
public:
    static long long rounds; // partiociones y merges de los ultimos sorts

    static void bubbleSort(int arr[], int n);
    static void selectionSort(int arr[], int n);
    static void insertionSort(int arr[], int n);
    static void mergeSort(int arr[], int n);
    static void heapSort(int arr[], int n);
    static void quickSort(int arr[], int n);

private:
    static void progress(int i, int n); // va dando porcentaje de los arreglos mas grandes

    // merge
    static void mergeSortHelper(int arr[], int tmp[], int left, int right);
    static void mergeHalves(int arr[], int tmp[], int left, int mid, int right);
    // quick
    static void quickSortHelper(int arr[], int left, int right);
    static int partition(int arr[], int left, int right);
    // heap
    static void heapify(int arr[], int n, int root);
};