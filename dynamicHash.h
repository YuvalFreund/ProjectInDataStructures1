

#ifndef UNTITLED4_DYNAMICHASH_H
#define UNTITLED4_DYNAMICHASH_H


#include <iostream>
#include <cstdio>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include "List.h"
#include <math.h>

using namespace std;
namespace oasis {

    class dynamicHash{
        List* array;
        int size;
        int num_elements;
    public:
        /**
       * Constructor
       * set an array of size initial_size
       */
        dynamicHash(int initial_size):size(initial_size),num_elements(0){
            array = new List[size];
            for(int i=0;i<size;i++){
                array[i] = List();
            }
        }
        /**
      * Copy cont'
      * copies an array
      */
        void operator = (dynamicHash& orig){
            delete[] array;
            array = new List[orig.size];
            size = orig.size;
            for(int i=0; i< orig.size;i++){
                while(orig.get(i)->getFirst()!=NULL) {
                    Clan* temp= orig.get(i)->getFirst();
                    array[i].insert(*temp);
                    orig.get(i)->removeHead();
                }
            }
        }
        /**
      * D'tor
      * delets an array
      */
        ~dynamicHash(){
            delete[] array;
        }
        /**
     * insert - inserts an element of type T to array
         * if amount of elements > 1/2 size - resize the array X2
     */
   void insert(Clan newData, int index, int* newSize){
       if(index > size-1){
           throw DynamicHashOutOfBounds();
       }
       num_elements++;
       array[index].insert(newData);
       *newSize = num_elements;
   }
    void deleteArray() {
        delete[] array;
    }
    void increment_elements(int* newSize){
        num_elements++;
        *newSize = num_elements;
    }
        /**
      * get - inserts an element of type T to array
          * if amount of elements > 1/2 size - resize the array X2
      */
        List* get (int index){
            if(index > size-1){
                throw DynamicHashOutOfBounds();
            }
            return &array[index];
        }
        /**
        * getNumElements - returns current num of elements in array
        */
        int getNumElements()const{
            return num_elements;
        }
        void destroy(){
            delete[] array;
        }
        /**
        * getSize - returns size of array
        */
        int getSize()const{
            return size;
        }
        void print() {
            for (int i = 0; i <size; i++) {
                if(array[i].getFirst()==NULL){
                    cout<<"List "<<i<<" is Empty"<<endl;
                    continue;
                }
                cout<<"List "<<i<<" contains: "; array[i].print();cout<<endl;
            }
            cout<<endl;
        }
        class DynamicHashOutOfBounds : public std::exception{};
    };
}

#endif //UNTITLED4_DYNAMICHASH_H
