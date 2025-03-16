// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include<random>
#define ll long long 
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
    int key,j;
    for( int i = 1 ; i < data.size() ; i++ ){
        key = data[i];
        j = i - 1;
        while( data[j] > key && j >= 0 ){
            data[ j+1 ] = data[j];
            j--;
        }
        data[ j+1 ] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    QuickSortSubVector(data, 0, data.size() - 1, f);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    if( low < high ){
        int q;
        if( flag == 0 ){
            q = Partition( data , low , high );   
        }else{
            q = RandomizedPartition( data , low , high );
        }
        QuickSortSubVector( data , low , q-1 , flag );
        QuickSortSubVector( data , q+1 , high , flag ); 
    }
    // Hint : recursively call itself
    //        Partition function is needed
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
}
int SortTool::RandomizedPartition(vector<int>& data, int low, int high){
    // Function : RQS's Partition the vector 
    // Exercise : Please complete the function
    int seed = time(0);
    int rsrand( seed );
    int r = rand();
    swap( data[ low + r % ( high - low + 1) ] , data[high] );

    int num = data[high];
    int j = low - 1;
    for( int i = low ; i < high ; i++ ){
        if( data[i] <= num ){
            j++;
            swap( data[i] , data[j] );    
        }
        
    }
    swap( data[j+1] , data[high] );
    return j+1 ;
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    int num = data[high];
    int j = low - 1;
    for( int i = low ; i < high ; i++ ){
        if( data[i] <= num ){
            j++;
            swap( data[i] , data[j] );    
        }
        
    }
    swap( data[j+1] , data[high] );
    return j+1 ;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    int mid;
    if( low < high ){
        mid = ( low + high ) / 2;
        MergeSortSubVector( data , low , mid );
        MergeSortSubVector( data , mid+1 , high );
        Merge( data , low , mid , 0 , high );
    }
    // Hint : recursively call itself
    //        Merge function is needed
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1, int middle2, int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int a1 = middle1 - low + 1;
    int a2 = high - middle1;
    int* p1 = new int[a1];
    int* p2 = new int[a2];
    for(int i = 0 ; i < a1 ; i++ ){
        p1[i] = data[ low + i ];
    }
    for(int i = 0 ; i < a2 ; i++ ){
        p2[i] = data[ high - a2 + i + 1 ];
    }
    int c1 = 0;
    int c2 = 0;
    for( int t = low ; t <= high ; t++ ){
        if( c1 == a1 ){
            data[t] = p2[c2];
            c2++;
        }else if( c2 == a2 ){
            data[t] = p1[c1];
            c1++;
        }else if( p1[c1] < p2[c2] ){
            data[t] = p1[c1];
            c1++;
        }else{
            data[t] = p2[c2];
            c2++;
        }
    }
    delete p1;
    delete p2;
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int left = 2 * root + 1;
    int right = 2 * root + 2;
    int small = root;
    if( left < heapSize && data[left] > data[root] ){
        small = left;
    }
    if( right < heapSize && data[right] > data[small] ){
        small = right;
    }
    if( small != root ){
        swap( data[root] , data[small] );
        MaxHeapify( data , small );
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for( int i = heapSize / 2 ; i >= 0 ; i-- ){
        MaxHeapify( data , i );
    }
}
