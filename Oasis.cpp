#include "Oasis.h"
#include <iostream>
using namespace oasis;


class compare_players{
public:
    int operator()(int player1,int player2){
        if(player1 == player2)return 0;
        else if(player1 > player2) return 1;
        else return 2;
    }
};

class insert_hash{
public:
    void operator()(List list,Clan value){
        list.insert(value);
    }
};

class insert_heap{
public:
    void operator()(Clan* clan1,Clan* clan2){
        clan1 = clan2;
    }
};


        /**
         * Constructor
         * sets clan's heap and hash to hold the clan's in the system. if failed returns NULL;
         */
Oasis::Oasis(int n, int* clan_ID):clanHeap(n),clanHashTable(n),playerTree(){
    for (int i=0;i<n; i++){
        Clan inserted(clan_ID[i]);
        clanHashTable.add(clan_ID[i],inserted);
        clanHeap.insert(clan_ID[i],&clanHashTable);
    }
}


/**
* addPlayer
* @param player's id
* @param player's initial score
* @param clan's id to insert
* @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
*/
StatusType Oasis::addPlayer(int player_id, int initial_score,int clan_id){
    if(this == NULL || clan_id < 0 || player_id < 0 || initial_score < 0){
        return INVALID_INPUT;
    }
    try {
        Clan *temp = clanHashTable.find(clan_id);
        if(temp == NULL){
            return FAILURE;
        }
        playerTree.insert(player_id,compare_players());
        temp->addPlayer(player_id,initial_score);
    }catch(const std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* addClan
* @param clan's id
* @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
*/
StatusType Oasis::addClan(int clan_id){
    if(this == NULL || clan_id < 0){
        return INVALID_INPUT;
    }
    try {
        if(clanHashTable.find(clan_id)!=NULL)
            return FAILURE;
        Clan clan(clan_id);
        clanHashTable.add(clan_id,clan);
        clanHeap.insert(clan_id,&clanHashTable);
    }catch(const std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* clanFight
* @param clan's id1
* @param clan's id2
* @param k1 - number of players from clan1
* @param k2 - number of players from clan2
* Clans are fighting, when the winner is the one with the bigger sum of grades
 * if equal - clan with lower id wins
* @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
*/
StatusType Oasis::clanFight(int clan_id1,int clan_id2,int k1,int k2){
    if(this == NULL || clan_id1 < 0 || clan_id2 < 0 || k1 <= 0 || k2 <= 0){
        return INVALID_INPUT;
    }
    try {
        Clan* clan1 = clanHashTable.find(clan_id1);
        Clan* clan2 = clanHashTable.find(clan_id2);
        if(clan1 == NULL || clan2 == NULL)
            return FAILURE;
        if(!clan1->checkFIght() || !clan2->checkFIght() || clan1 == clan2)
            return FAILURE;
        if(clan1->getNumPlayers() < k1 || clan2->getNumPlayers() < k2)
            return FAILURE;
        int power1 = clan1->getPowerOfK(k1);
        int power2 = clan2->getPowerOfK(k2);
        if(power1 > power2 || (power1 == power2 && clan1->getId() < clan2->getId())){
            int index2 = clan2->getIndex();
            clan2->cancelFIght();
            clanHeap.delIndex(index2,clan_id2,&clanHashTable);
        }
         if(power2 > power1 || (power1 == power2 && clan1->getId() > clan2->getId())){
             int index1 = clan1->getIndex();
             clan1->cancelFIght();
             clanHeap.delIndex(index1,clan_id1,&clanHashTable);
        }
    }catch(const std::bad_alloc&){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* getMinClan
* @param clan's id
 * returns the lower id of an unconquered clan
* @returns SUCCESS,FAILURE,INVALID_INPUT
*/
StatusType Oasis::getMinClan(int *clan_id){
    if(this == NULL || clan_id == NULL){
        return INVALID_INPUT;
    }
    try {
        *clan_id = clanHeap.getMin();
    }catch(...){
        return FAILURE;
    }
    return SUCCESS;
}

/**
* quit
* @param clan's id
* returns the lower id of an unconquered clan
* @returns SUCCESS,FAILURE,INVALID_INPUT
*/
void Oasis::quit(){}
Oasis::~Oasis(){
    clanHashTable.deleteTrees();
}

void Oasis::display(){
    clanHeap.print();
    clanHashTable.print();
    playerTree.display();
}