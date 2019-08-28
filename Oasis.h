#ifndef WET2_OASIS_H
#define WET2_OASIS_H

#include "AVLDegreeTree.h"
#include "Heap.h"
#include "HashTable.h"
#include "Clan.h"
#include "library2.h"
namespace oasis {

    class Oasis {
    public:

            /**
       * Oasis definition
       */
        Heap clanHeap;
        HashTable clanHashTable;
        AVLDegreeTree<int> playerTree;
        /**
         * Constructor
         * sets clan's heap and hash to hold the clan's in the system. if failed returns NULL;
         */
        Oasis(int n, int* clan_ID);


        /**
       * addPlayer
       * @param player's id
       * @param player's initial score
       * @param clan's id to insert
       * @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
       */
        StatusType addPlayer(int player_id, int initial_score,int clan);

        /**
       * addClan
       * @param clan's id
       * @returns SUCCESS,FAILURE,INVALID_INPUT,ALLOCATION_ERROR
       */
        StatusType addClan(int clan_id);

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
        StatusType clanFight(int clan_id1,int clan_id2,int k1,int k2);

            /**
         * getMinClan
         * @param clan's id
             * returns the lower id of an unconquered clan
         * @returns SUCCESS,FAILURE,INVALID_INPUT
         */
        StatusType getMinClan(int *clan_id);

            /**
       * quit
       * @param clan's id
           * returns the lower id of an unconquered clan
       * @returns SUCCESS,FAILURE,INVALID_INPUT
       */
        void quit();
        ~Oasis();

        void display();
    };
}


#endif //WET2_OASIS_H
