#include "Sorter.hpp"
#include "Sorter.cpp"
int main()
{
    int arr[] = { 23, 78, 45, 8, 32, 56, 1 };
    int n = sizeof(arr) / sizeof(arr[0]);
    selectionsort(arr, n);
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}