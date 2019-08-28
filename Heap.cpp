
#include "Heap.h"
using namespace std;
using namespace oasis;
  /**
  * Constructor- a Make Heap function
  * creates a new heap from a given array
   * insert every new element and sift up when needed
  */
  Heap::Heap(int n) : clans(dynamicHeap(n)), last_index(0),size(0){}

  /**
  * insert a value to the latest index
   * sifts up the value in the heap
  */
  void Heap::insert(int data,HashTable *table) {
      clans.insert(data,last_index);
      Clan* entered = table->find(data);
      entered->setIndex(last_index);
      siftUp(last_index, table,false);
      last_index++;
  }

  /**
   * recieves a values and index for change
    * change the value and sifts up when needed
   */
  void Heap::decKey(int index, int newClanID,HashTable *table,bool erase){//this is used only for deleted a clan
      clans.set(newClanID,index);
      siftUp(index,table,erase);
  }
  /**
   * does a sift up through the array
  */
  void Heap::siftUp(int nodeIndex,HashTable *table,bool erase){
      int son = nodeIndex;
      int parent = floor(nodeIndex / 2);
      while (son > -1) {
          if (clans.get(son) < clans.get(parent)) {
              int parentId = clans.get(parent);
              Clan* parentClan = table->find(parentId);
              if(!erase){
                  int sonId = clans.get(son);
                  Clan* sonClan = table->find(sonId);
                  clans.swapValues(son, parent);
                  sonClan->setIndex(parent);
              }
              else{
                  clans.swapValues(son, parent);
              }
              parentClan->setIndex(son);
          }else{
              break; // does it matter for complexity??
          }
          son/= 2;
          parent /= 2;
      }
  }
  /**
   * does a sift down through the array
   * starting at the  root
  */
  void Heap::siftDown(HashTable *table){
      int current = 0;
      int right = 1;
      int left = 2;
      while (right < last_index && left < last_index ) {
          int minIndex = clans.get(right) < clans.get(left) ? right : left;
          if (clans.get(current) > clans.get(minIndex)) {
              int currentId = clans.get(current);
              int minIndexId = clans.get(minIndex);
              Clan* currentClan = table->find(currentId);
              currentClan->setIndex(minIndex);
              Clan* minIndexClan = table->find(minIndexId);
              minIndexClan->setIndex(current);
              clans.swapValues(current, minIndex);

          } else {
              return;
          }
          current = minIndex;
          right = current * 2;
          left = current * 2 + 1;
      }
      if(right == last_index-1 && clans.get(current) > clans.get(right)){
          int currentId = clans.get(current);
          int rightId = clans.get(right);
          Clan* currentClan = table->find(currentId);
          currentClan->setIndex(right);
          Clan* rightClan = table->find(rightId);
          rightClan->setIndex(current);
          clans.swapValues(current, right);
      }
  }

  int Heap::get(int index){
      return clans.get(index);
  }
int Heap::getMin(){
    return clans.get(0);
}

  /**
   * deletes the minimum
  */
  void Heap::delMin(HashTable *table){
      last_index--;
      clans.swapValues(0,last_index);
      clans.set(-1,last_index);
      siftDown(table);
  }
  /**
   * removes a value from heap
   * receives an index and removes is from the tree
  */
  void Heap::delIndex(int index,int id,HashTable *table){
      Clan* temp = table->find(id);
      temp->setIndex(-1);
      decKey(index,-1000,table,true);
      delMin(table);
  }
  /**
   * check if heap
  */
  bool Heap::isHeap()
  {
      int counter=0;
      int n=clans.getSize();
      //std::cout << "Size is " << n << ":"<<endl;
      for (int i=0; i<=n; i++)
      {
          //if leaf go to next one
          if(2*i>n-1) continue;

          counter++;
          // std::cout <<clans.get(i) <<", ";
          // If left child is greater, return false
          if ((clans.get(2*i) < clans.get(i) && clans.get(2*i)!=0) ||
                  (i==0 && clans.get(1) < clans.get(0))) {
                  cout << "heap fail at: " << i << endl;
                  return false;
          }
          // If right child is greater, return false
          if ((clans.get(2*i+1) < clans.get(i) && clans.get(2*i+1)!=0) ||
                  (i==0 && clans.get(2) < clans.get(0))) {
              cout << "heap fail at: "<< i<< endl;
              return false;
          }
          //if(i%50==0 && i!=0 ) cout<<endl;
      }
      std::cout<< "heap is correct - ok!" << std::endl;
      return true;
  }

  void Heap::print() {
      for (int i = 0; i < clans.getSize(); i++){
          cout << clans.get(i) << " ";
      }
      cout<<endl;
  }


