
#ifndef UNTITLED4_DYNAMICHEAP_H
#define UNTITLED4_DYNAMICHEAP_H


#include <iostream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <math.h>
using namespace std;
namespace oasis {

    class dynamicHeap{
        int* array;
        int size;
        int num_elements;
    public:
        /**
       * Constructor
       * set an array of size initial_size
       */
        dynamicHeap(int initial_size):size(initial_size),num_elements(0){
            array = new int[size];
            for(int i=0;i<size;i++){
                array[i] = -1;
            }
        }
        /**
      * Copy cont'
      * copies an array
      */
        dynamicHeap(const dynamicHeap& orig){
            int temp = size;
            size = orig.size;
            num_elements = orig.num_elements;
            array = new int[size];
            for(int j=0;j<size;j++)
                array[j] = -1;
            for(int i=0;i<temp;i++){
                array[i]=orig.array[i];
            }
            for(int j=temp;j<size;j++)
                array[j] = -1;
        }
        /**
      * D'tor
      * delets an array
      */
        ~dynamicHeap(){
            delete[] array;
        }
        /**
     * insert - inserts an element of type T to array
         * if amount of elements > 1/2 size - resize the array X2
     */
        void insert(int value, int index){
            if(index > size-1){
                throw DynamicHeapOutOfBounds();
            }
            num_elements++;
            array[index] = value;
            if(size < 2*num_elements){
                this->resize(2*size);
            }
        }

        /**
      * get - inserts an element of type T to array
          * if amount of elements > 1/2 size - resize the array X2
      */
        int get (int index){
            if(index > size-1){
                throw DynamicHeapOutOfBounds();
            }
            return array[index];
        }
        /**
        * getNumElements - returns current num of elements in array
        */
        int getNumElements()const{
            return num_elements;
        }
        /**
        * getSize - returns size of array
        */
        int getSize()const{
            return size;
        }

        /**
        * swap values - returns size of array
        */
        void swapValues(int index1, int index2) {
            int value1 = get(index1);
            int value2 = get(index2);
            set(value1,index2);
            set(value2,index1);
        }
        /**
        * set the value T to index
        */
        void set(int value, int index){
            if(index > size-1){
                throw DynamicHeapOutOfBounds();
            }

            array[index] = value;
        }


        /**
        * resize - inserts an element of type T to array
            * if amount of elements > 1/2 size - resize the array X2
        */
        void resize(int new_size){
            int* temp;
            temp = new int[new_size];
            for(int i=0;i<size;i++){
                temp[i] = array[i];
            }
            for(int i=size;i<new_size;i++){
                temp[i] = -1;
            }
            int* toDelete = array;
            array = temp;
            delete[] toDelete;
            size = new_size;
        }

        void display() const{
            for(int i=0;i<size;i++)
                cout<<array[i]<<",";
        }
        class DynamicHeapOutOfBounds : public std::exception{};
    };
}

#endif //UNTITLED4_DYNAMICHEAP_H
