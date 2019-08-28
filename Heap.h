

#ifndef UNTITLED4_HEAP_H
#define UNTITLED4_HEAP_H

#include <iostream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <math.h>
#include "Clan.h"
#include "dynamicHeap.h"
#include "HashTable.h"
using namespace std;
namespace oasis {
    class Heap {

        dynamicHeap clans;
        int last_index;
        int size;
    public:
        /**
        * Constructor- a Make Heap function
        * creates a new heap from a given array
         * insert every new element and sift up when needed
        */
        Heap(int n);
         /**
         * insert a value to the latest index
          * sifts up the value in the heap
         */
        void insert(int data,HashTable *table);

        /**
         * recieves a values and index for change
          * change the value and sifts up when needed
         */
        void decKey(int index, int newClanID,HashTable *table,bool erase);
        /**
         * does a sift up through the array
        */
        void siftUp(int nodeIndex,HashTable *table,bool erase);
        /**
         * does a sift down through the array
         * starting at the  root
        */
        void siftDown(HashTable *table);

        int get(int index);
        /**
       * returns the minimum
      */
        int getMin();
        /**
         * deletes the minimum
        */
        void delMin(HashTable *table);
        /**
         * removes a value from heap
         * receives an index and removes is from the tree
        */
        void delIndex(int index,int id,HashTable *table);
        /**
         * check if heap
        */
        bool isHeap();

        void print();
        };
}
#endif //UNTITLED4_HEAP_H
