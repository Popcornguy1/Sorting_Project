/****************************************************************************************************************************
Title          :   Sorter.cpp
Auhor          :   Nigel Ferrer
Modified By    :   ** ENTER YOUR NAME **
Description    :   implementation file of an integer array container class that
                   contains implementations of some sorting algorithms
Dependencies   :   Sorter.cpp
****************************************************************************************************************************/

#include "Sorter.hpp"
using namespace std;

Sorter::Sorter(array_type type, size_t array_size, int* arr) : type_(type), SIZE_(array_size), values_(arr)
{
}

/***************************s* Selection Sort ****************************/
template <typename Comparator>
int Sorter::getPosOfMinOrMax(int arr[], int from, int to, const Comparator& comp)
{
    int min_or_max = from;
    for (int i = from + 1; i <= to; i++)
    {
        if (comp(arr[i], arr[min_or_max]))
        {
            min_or_max = i;
        }
    }
    return min_or_max;
}

template <typename Comparator>
int Sorter::selectionSort(int arr[], size_t size, const Comparator& comp)
{ 
    
   
    int first;
    for (first = 0; first < size - 1; first++) {
        int smallest_index = getPosOfMinOrMax(arr, first, size - 1, comp); // well get the value dependinf on the array number order and last value
        if (smallest_index != first) { // if smallest index is the first then there is nothing to move 
            swap(arr[smallest_index], arr[first]); // if true than swap
            selectionCount_++; // keep moving the count up
        }


    }
    return selectionCount_; // will return the count 
   
 
}

/*
    int i, j, min_idx;
    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < size; j++)
            if ((arr[j] < arr[min_idx]))
                min_idx = j;

        swap(arr[min_idx], arr[i]);
    }
    return min_idx;
    */
/************************************************************************/

/**************************** Insertion Sort ****************************/
template <typename Comparator>
int Sorter::insertionSort(int arr[], size_t size, const Comparator& comp)
{
    for (int unsorted = 1; unsorted < size; unsorted++) {
        int current = unsorted; 
        while ((current > 0) &&
            (comp(arr[current], arr[current-1]))) { // compare the current and the last 
            swap(arr[current], arr[current - 1]); // swap if yes
            current--;  // keep moving the count down 
            insertionCount_++; // keeps making the count go up
        }
    
}
    return insertionCount_;// return value 

}
/************************************************************************/

// /****************************** Merge Sort ******************************/
template <typename Comparator>
void Sorter::merge(int arr[], int from, int mid, int to, const Comparator& comp)
{
   

    int tempArray[to-from+1]; // Temporary array

    int first1 = from; 
    int last1 = mid; 
    int first2 = mid + 1; 
    int last2 = to; 
    
    int index = first1; // Next available location in tempArray
    if (comp(0, 1) == true) {
        while ((first1 <= last1) && (first2 <= last2))
        {
            mergeCount_++; 
            // At this point, tempArray[first..index-1] is in order
            if (arr[first1] <= arr[first2])
            {
                tempArray[index] = arr[first1];
                first1++;
            }
            else
            {
                tempArray[index] = arr[first2];
                first2++;
            } // end if
            index++;
        }
    }
    else {
        while ((first1 <= last1) && (first2 <= last2))
        {
            mergeCount_++; 
            // At this point, tempArray[first..index-1] is in order
            if (arr[first1] >= arr[first2])
            {
                tempArray[index] = arr[first1];
                first1++;
            }
            else
            {
                tempArray[index] = arr[first2];
                first2++;
            } // end if
            index++;
        }

    }
        // end while
   // Finish off the first subarray, if necessary
    while (first1 <= last1)
    {
        mergeCount_++; 
        // At this point, tempArray[first..index-1] is in order
        tempArray[index] = arr[first1];
        first1++;
        index++;
    } 
    while (first2 <= last2)
    {
        mergeCount_++; 
        tempArray[index] = arr[first2];
        first2++;
        index++; 
    } // end for
   // Copy the result back into the original array
    for (index = from; index <= to; index++) {
        arr[index] = tempArray[index];

    }
}

template <typename Comparator>
int Sorter::mergeSort(int arr[], int from, int to, const Comparator& comp)
{
    if (from < to) {
        int mid = from+(to-from) / 2;
        mergeSort(arr, from, mid, comp);
        mergeSort(arr, mid + 1, to, comp);
        merge(arr, from, mid, to, comp);
    }
    return mergeCount_;

}
// /************************************************************************/

void Sorter::runSorts(sort_order order)
{

    int selectionValues[SIZE_];
    int insertionValues[SIZE_];
    int mergeValues[SIZE_];

    if (type_ == RANDOM)
    {
        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < SIZE_; i++)
        {
            selectionValues[i] = rand() % 100;
            insertionValues[i] = rand() % 100;
            mergeValues[i] = rand() % 100;
        }
    }

    else
    {
        for (int i = 0; i < SIZE_; i++)
        {
            selectionValues[i] = values_[i];
            insertionValues[i] = values_[i];
            mergeValues[i] = values_[i];
        }
    }

    // Selection Sort Display
    std::cout << "******** Selection Sort ********\nOriginal Array:\n";
    displayArr(selectionValues);
    if (order == INCREASING)
    {
        selectionSort(selectionValues, SIZE_, std::less<int>());
    }
    else
    {
        selectionSort(selectionValues, SIZE_, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(selectionValues);
    std::cout << "\nNumber of swaps: " << selectionCount_ << "\n********************************\n\n";

    // Insertion Sort Display
    std::cout << "\n******** Insertion Sort ********\nOriginal Array:\n";
    displayArr(insertionValues);
    if (order == INCREASING)
    {
        insertionSort(insertionValues, SIZE_, std::less<int>());
    }
    else
    {
        insertionSort(insertionValues, SIZE_, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(insertionValues);
    std::cout << "\nNumber of swaps: " << insertionCount_ << "\n********************************\n\n";

    // Merge Sort Display
    std::cout << "\n********** Merge Sort **********\nOriginal Array:\n";
    displayArr(mergeValues);
    if (order == INCREASING)
    {
        mergeSort(mergeValues, 0, SIZE_ - 1, std::less<int>());
    }
    else
    {
        mergeSort(mergeValues, 0, SIZE_ - 1, std::greater<int>());
    }
    std::cout << "\nSorted Array:\n";
    displayArr(mergeValues);
    std::cout << "\nNumber of comparisons: " << mergeCount_ << "\n********************************\n\n";


}

void Sorter::displayArr(const int array[]) const
{
    for (size_t i = 0; i < SIZE_; i++)
    {
        std::cout << array[i];
        (i < SIZE_ - 1) ? (cout << " ") : (cout << "\n");
    }
}