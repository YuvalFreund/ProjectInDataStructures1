/****************************************************************************/
/*                                                                          */
/* This file contains the interface functions                               */
/* you should use for the wet ex 2                                          */
/*                                                                          */
/****************************************************************************/

/****************************************************************************/
/*                                                                          */
/* File Name : library2.cpp                                                 */
/*                                                                          */
/****************************************************************************/
#include "library2.h"
#include "Oasis.h"
using namespace oasis;
/* Required Interface for the Data Structure
* -----------------------------------------*/

void* init(int n, int *clanIDs){
    if(n<2 || clanIDs == NULL)
        return NULL;
    try{
        Oasis * DS = new Oasis(n,clanIDs);
        return (void*)DS;
    }catch (...){
        return NULL;
    }
}

StatusType addClan(void *DS, int clanID){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->addClan(clanID);
}

StatusType addPlayer(void *DS, int playerID, int score, int clan){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->addPlayer(playerID,score,clan);
}

StatusType clanFight(void *DS, int clan1, int clan2, int k1, int k2){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->clanFight(clan1,clan2,k1,k2);
}

StatusType getMinClan(void *DS, int *clan){
    if(DS == NULL)
        return INVALID_INPUT;
    return ((Oasis *)DS)->getMinClan(clan);

}

/* Description:   Quits and deletes the database.
*                DS should be set to NULL.
* Input:         DS - A pointer to the data structure.
* Output:        None.
* Return Values: None.
*/
void quit(void** DS){
    if(DS!=NULL && *DS!=NULL){
        delete (Oasis*)*DS;
        *DS = NULL;
    }
}