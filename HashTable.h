
#ifndef WET2_HASHTABLE_H
#define WET2_HASHTABLE_H

#include <iostream>
#include <cstdio>
#include <sstream>
#include "List.h"
#include "Clan.h"
#include "dynamicHash.h"

using namespace std;
namespace oasis {
    class HashTable {
    public:
        /**
 * Function definition
 */
        class function {
        public:
            int size;

            function(int size) : size(size) {}

            int operator()(int x) {
                if(x==0)return 0;
                return x % size;
            }

            void reSize(int newSize) {
                size = newSize;
            }
            int getSize(){
                return size;
            }
        };

        /**
         * Hash definition
         * array - dynamic array of certain size, holding 1/4 to 1/2 of element amount as lists
         * using size modulo to insert values, we achieve O(1) estimated complexity
         */
        dynamicHash array;
        function hashFunc;

        explicit HashTable(int size) : array(size), hashFunc(size) {}

        Clan* find(int id) {
            return array.get(hashFunc(id))->getData(id);
        }
        void add(int id, Clan newClan){
            int clansInHash;
            array.get(hashFunc(id))->insert(newClan);///insert Clan to list
            array.increment_elements(&clansInHash);///increment number of elements in array
            if (clansInHash == hashFunc.size) {
                hashFunc.reSize(clansInHash*2);
                reHash(clansInHash*2,clansInHash);
            }
        }
        void reHash(int new_size, int old_size){
            dynamicHash newArray(new_size);
            int listIndex;
            for (int i = 0; i < old_size; i++) {
                while (array.get(i)->getFirst()) {
                    Clan temp(*array.get(i)->getFirst());
                    listIndex = hashFunc(temp.getId());
                    List *newList = newArray.get(listIndex);
                    newList->insert(temp);
                    array.get(i)->removeHead();
                }
            }
            array = newArray;
        }
        void deleteTrees() {
            for (int i = 0; i < array.getSize() ; i++) {
                while (array.get(i)->getFirst()) {
                    array.get(i)->getFirst()->destroyTree();
                    array.get(i)->removeHead();
                }
            }
        }
        ~HashTable() {}
        void print() {
            for (int i = 0; i < hashFunc.getSize(); i++) {
                    if(array.get(i)->getFirst()==NULL){
                        cout<<"List "<<i<<" is Empty"<<endl;
                        continue;
                    }
                cout<<"List "<<i<<" contains: "; array.get(i)->print();cout<<endl;
                }
            cout<<endl;
            }
    };
}
#endif //WET2_HASHTABLE_H
