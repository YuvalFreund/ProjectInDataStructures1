
#ifndef UNTITLED4_CLAN_H
#define UNTITLED4_CLAN_H

#include "AVLPlayerTree.h"
#include <iostream>
#include "Player.h"
namespace oasis{
        /**
        * clan definition and functions
        */
        class Clan {
            class compareScore {
            public:
                int operator()(Player num1, Player num2) {
                    if (num1 == num2)return 0;
                    else if (num1 > num2)return 1;
                    else return 2;
                }
            };

            class playersFunction {
            public:
                int operator()(int player1, int player2) const {
                    return player1 + player2;
                };
            };
            bool fightFlag;// true for "can fight", false for "can't fight"
            int heapIndex;
            int CLANID;
            int numPlayers;
            AVLPlayerTree *players;
        public:


            class ClanInvalidArgs : public std::exception { };

            /**
             * constructor for clan
             */
            Clan(int CLANID) : fightFlag(true), heapIndex(0), CLANID(CLANID), numPlayers(0) {
                if (CLANID < 0) {
                    throw ClanInvalidArgs();
                }
                players = new AVLPlayerTree();
            }
            /**
           *  copy constructor for clan
           */
            Clan(const Clan& c){
                this->heapIndex= c.heapIndex;
                this->fightFlag = c.fightFlag;
                this->CLANID = c.CLANID;
                this->numPlayers = c.numPlayers;
                this->players = c.players;
            }
            /**
            * adding a player to the player tree
            */
            void addPlayer(int player,int score) {
                Player p(player,score);
                players->insert(p, compareScore());
                numPlayers++;
            }

            int getNumPlayers() {
                return numPlayers;
            }
            int getId() {
                return CLANID;
            }
            void setId(int newClanID) {
                 CLANID=newClanID;
            }
            int getIndex() {
                return heapIndex;
            }
            void setIndex(int newIndex) {
                heapIndex = newIndex;
            }
            void destroyTree(){
                delete players;
            }
            /**
            * checking if clan can fight or not
             */
            bool checkFIght() {
                return fightFlag;
            }
            /**
            * checking if clan can fight or not
             */
            void cancelFIght() {
                fightFlag = false;
            }
            void print(){
                cout<<getId();
                players->display();
            }

            /**
            * gets the K powerful players
            */
            int getPowerOfK(int K) {
                return players->Kth_biggest_sum(K, playersFunction(), compareScore());
            }
            bool operator < (const Clan &c) {
                return CLANID < c.CLANID;
            }
            bool operator > (const Clan &c) {
                return CLANID > c.CLANID;
            }
            bool operator==(const Clan &c) {
                return CLANID == c.CLANID;
            }
            ~Clan(){
            }
        };
//    std::ostream& operator<<(std::ostream& os, Clan& clan){
   //     os << clan.getId() << endl;
     //   return os;
    //}

    class swapIndexes{
    public:
        void operator()(Clan* c1, Clan* c2){
            int temp = c1->getIndex();
            c1->setIndex(c2->getIndex());
            c2->setIndex(temp);
        }
    };


}



#endif //UNTITLED4_CLAN_H
