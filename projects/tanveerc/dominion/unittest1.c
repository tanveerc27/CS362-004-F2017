/*****************************
File: unittest1.c
Testing function: endTurn()
Test1: Test current player changes to next player upon complete
Test2: Test current player's hand cleared
 ******************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>


int main () {

   struct gameState state;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, council_room, smithy};

   int seed = 50;
   int player;


   printf("---------------- unittest1 ----------------\n\n");

   printf("----------------Testing Function: endTurn() ----------------\n");

   /******* Test Current player changes to next player *******/

   printf("*******Test1: Current player changes to next player *******\n");
   initializeGame(2, k, seed, &state);
   player = whoseTurn(&state);

   assert(numHandCards(&state) == 5);
   assert(gainCard(village,&state,2,player) == 0);
   assert(numHandCards(&state) == 6);

   endTurn(&state);

   //PASS Condition: whoseTurn points from player 0 to player 1
   if(state.whoseTurn == (player + 1))
   {
      printf("PASS: Current player changes to next player\n\n\n");

   }
   else
      printf("FAIL: Current player changes to next player\n\n\n"); 



   /******* Test Current player hand cleared ******/

   printf("*******Test2: Test Current player hand cleared *******\n");
   initializeGame(2, k, seed, &state);
   player = whoseTurn(&state);

   assert(numHandCards(&state) == 5);
   assert(gainCard(village,&state,2,player) == 0);
   assert(gainCard(mine,&state,2,player) == 0);
   assert(numHandCards(&state) == 7);

   endTurn(&state);


   int handEmpty;
   if (state.handCount[player] == 0)
      handEmpty = 1;

   //PASS Condition: Current player's hand is cleared upon completion
   if(handEmpty == 1)
   {
      printf("PASS: Current player hand cleared\n\n\n");

   }
   else
      printf("FAIL: Current player hand cleared\n\n\n"); 


   printf("*******Testing endTurn() Complete!*******\n\n\n");

   return 0;

}
