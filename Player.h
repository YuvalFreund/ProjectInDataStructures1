
#ifndef WET2_PLAYER_H
#define WET2_PLAYER_H

#include <iostream>

namespace oasis{
    class Player{
    public:
            int id;
            int score;
            Player(int id,int score):id(id),score(score){}

            Player& operator=(Player player2){
                this->score = player2.score;
                this->id = player2.id;
                return *this;
            }
            bool operator==(Player player2){
                return (player2.id == id && player2.score == score);
            }

            bool operator>(Player player2){
                if(this->score > player2.score)return true;
                if(this->score == player2.score && this->id < player2.id)return true;
                return false;
            }

            bool operator<(Player player2){
                if(!(*this == player2) && !(*this > player2))return true;
                return false;
            }
        ~Player(){}
    };
    inline std::ostream& operator<<(std::ostream& os, Player& player){
         os << player.score << std::endl;
       return os;
    }
}

#endif //WET2_PLAYER_H
