//
//  main.cpp
//  Assignment 3.2
//
//  Created by Vincent Liang on 10/24/19.
//  Copied/Learned how to record time on sort function through:
//  https://www.geeksforgeeks.org/measure-execution-time-function-cpp/
// All the sorting algorithms are based off zybooks sorting


#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <chrono>

int Partition(int numbers[], int i, int k) {
    int l = 0;
    int h = 0;
    int midpoint = 0;
    int pivot = 0;
    int temp = 0;
    bool done = false;
      
      // Pick middle element as pivot
    midpoint = i + (k - i) / 2;
    pivot = numbers[midpoint];
      
    l = i;
    h = k;
      
    while (!done) {
         
        // Increment l while numbers[l] < pivot
        while (numbers[l] < pivot) {
            ++l;
        }
         
        // Decrement h while pivot < numbers[h]
        while (pivot < numbers[h]) {
            --h;
        }
         
        // If there are zero or one elements remaining,
        // all numbers are partitioned. Return h
        if (l >= h) {
            done = true;
        }
        else if (done == false) {
        // Swap numbers[l] and numbers[h],
        // update l and h
            temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;
            
            ++l;
            --h;
         }
      }
      
    return h;
}

void QuickSort(int arr[], int i, int k) {
    int j = 0;
    //j is the last element of the lower partition
    
    if( i>= k) {
        return;
    }
    j = Partition( arr, i, k);
    QuickSort(arr, i, j);
    QuickSort(arr, j+1, k);
}

void trickleDown(int nodeIndex, int arr[], int size) {
    int childIndex = nodeIndex * 2 + 1;
    
    
    while(childIndex < size) {
        int currentPr = arr[nodeIndex];
        
        int maxPr = currentPr;
        int maxIndex = -1;
        
        if(arr[childIndex] > maxPr) {
            maxPr = arr[childIndex];
            maxIndex = childIndex;
        }
        
        if(childIndex + 1 < size) {
            if(arr[childIndex + 1]  > maxPr) {
                maxPr = arr[childIndex + 1];
                maxIndex = childIndex + 1;
            }
        }
        
        if(maxPr == currentPr) {
            return;
        }
        
        else {
            int temp = arr[nodeIndex];
            arr[nodeIndex] = arr[maxIndex];
            arr[maxIndex] = temp;
            nodeIndex = maxIndex;
            childIndex = 2 * nodeIndex +1;
        }
    }
}

void HeapSort(int numbers[], int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        trickleDown(i, numbers, size);
    }
    for (int i = size - 1; i > 0; i--) {
        int temp = numbers[0];
        numbers[0] = numbers[i];
        numbers[i] = temp;
        trickleDown(0, numbers, i);
    }
}

void Merge(int numbers[], int i, int j, int k) {
    int mergedSize = k - i + 1;               // Size of merged partition
    int mergePos = 0;                          // Position to insert merged number
    int leftPos = 0;                           // Position of elements in left partition
    int rightPos = 0;                          // Position of elements in right partition
    int *mergedNumbers = new int[mergedSize];   // Dynamically allocates temporary array
                                          // for merged numbers
    
    leftPos = i;                           // Initialize left partition position
    rightPos = j + 1;                      // Initialize right partition position
    
    // Add smallest element from left or right partition to merged numbers
    while (leftPos <= j && rightPos <= k) {
       if (numbers[leftPos] <= numbers[rightPos]) {
           mergedNumbers[mergePos] = numbers[leftPos];
           ++leftPos;
       }
       else {
           mergedNumbers[mergePos] = numbers[rightPos];
           ++rightPos;
          
       }
        ++mergePos;
    }
    
    // If left partition is not empty, add remaining elements to merged numbers
    while (leftPos <= j) {
        mergedNumbers[mergePos] = numbers[leftPos];
        ++leftPos;
        ++mergePos;
    }
    
    // If right partition is not empty, add remaining elements to merged numbers
    while (rightPos <= k) {
        mergedNumbers[mergePos] = numbers[rightPos];
        ++rightPos;
        ++mergePos;
    }
    
    // Copy merge number back to numbers
    for (mergePos = 0; mergePos < mergedSize; ++mergePos) {
        numbers[i + mergePos] = mergedNumbers[mergePos];
    }
}
void MergeSort(int numbers[], int i, int k) {
    int j = 0;
   
   if (i < k) {
       j = (i + k) / 2;  // Find the midpoint in the partition
      
      // Recursively sort left and right partitions
       MergeSort(numbers, i, j);
       MergeSort(numbers, j + 1, k);
      
      // Merge left and right partition in sorted order
       Merge(numbers, i, j, k);
   }
}

using namespace std;

void Test(int size, char sort) {
    
    srand((unsigned)time(0));
    int arr[size];
    long time[30];
    unsigned long sum = 0;
    for (int j=0; j<30; ++j) {
        
        for(int i=0; i<size; ++i){
            arr[i] = (rand()%10000);
        }
        
        //
        //HeapSort(arr, size);
        auto start = std::chrono::high_resolution_clock::now();
        if(sort == 'm') {
            MergeSort(arr, 0, size-1);
        }
        else if(sort == 'q') {
            QuickSort(arr, 0, size-1);
        }
        else if(sort == 'h') {
            HeapSort(arr, size);
        }
        else {
            return;
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        time[j] = duration.count();
        
    }
    
    for (int k = 0; k < 30; ++k) {
        sum = sum + time[k];
    }
    sum = sum/30;
    cout << "The average runtime of ";
    if (sort == 'm') {
        cout << "mergesort ";
    }
    else if (sort == 'q') {
        cout << "quicksort ";
    }
    else if (sort == 'h') {
        cout << "heapsort ";
    }
    cout << "on an array of size " <<
    size << " is: " << sum << " microseconds" << endl << endl;
}



int main() {

    // q for quicksort, h for heapsort, m for mergesort
    Test(10,'q');
    Test(100,'q');
    Test(1000,'q');
    Test(10000,'q');
    Test(100000,'q');
    Test(1000000,'q');
    Test(10,'m');
    Test(100,'m');
    Test(1000,'m');
    Test(10000,'m');
    Test(100000,'m');
    Test(1000000,'m');
    Test(10,'h');
    Test(100,'h');
    Test(1000,'h');
    Test(10000,'h');
    Test(100000,'h');
    Test(1000000,'h');
    return 0;
}
