#ifndef UNTITLED4_LIST_H
#define UNTITLED4_LIST_H


#include <vector>
#include <math.h>
#include "Clan.h"
using namespace std;
namespace oasis {
    class List {
    public:

        class list_Node {
        public:
            Clan data;
            list_Node *next;

            list_Node(Clan data) : data(data), next(NULL) {}
        };

        list_Node *head;

        class dataDoesntExist : public std::exception {};

        class listAlreadyExists : public std::exception {};

        List() {
            head = NULL;
        }

        /**
         * insert checks all node for the new data
         * if found, throws exception
         * else, push it in te head
         */
        void insert(Clan newData) {
            list_Node *inserted = new list_Node(newData);
            if (head == NULL) {
                head = inserted;
                return;
            }
            list_Node *temp = head;
            while (temp != NULL) {
                if (temp->data == newData) {
                    delete inserted;
                    throw listAlreadyExists();
                }
                temp = temp->next;
            }
            inserted->next = head;
            head = inserted;
        }
        List operator&=(List& other){
            list_Node* otherNode = other.head;
            while(otherNode!=NULL){
                Clan enter = otherNode->data;
                insert(enter);
                otherNode=otherNode->next;
            }
            return *this;
        }
        ~List() {
            list_Node *temp;
            while (head != NULL) {
                temp = head->next;
                delete (head);
                head = temp;
            }
        }

        /**
        * extract gets the power of K players
        * getID takes the id of a clan
        * return is the power of K strongest players
        */
        Clan *getData(int id) {
            list_Node *temp = head;
            while (temp != NULL) {
                if (temp->data.getId() == id) {
                    return &temp->data;
                }
                temp = temp->next;
            }
            return NULL;
        }

        void removeHead() {
            if (head == NULL) return;
            list_Node *saver = head;
            head = head->next;
            delete (saver);
        }

        Clan *getFirst() {
            if (head != NULL)
                return &head->data;
            return NULL;
        };
        void print(){
            list_Node *temp = head;
            while (temp != NULL) {
                temp->data.print();
                cout<<",";
                temp = temp->next;
            }
        }
    };
}
#endif //UNTITLED4_LIST_H
