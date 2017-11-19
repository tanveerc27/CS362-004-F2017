/*****************************
File: unittest2.c
Testing function: isGameOver()
Test1: Test supply of one victory card finished
Test2: Test three supply piles empty
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
   struct gameState previousState;
   int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,sea_hag, council_room, smithy};

   int seed = 50;

   int i;
   int finishFlag;
   int numPlayers = 2;
   int player = 0;


   printf("\n\n\n---------------- unittest2 ----------------\n\n");

   printf("----------------Testing Function: isGameOver() ----------------\n");

   /******* Test province cards supply finished *******/

   printf("*******Test1: Province cards supply finished *******\n");
   initializeGame(numPlayers, k, seed, &state);
   assert(numHandCards(&state) == 5);

   for(i = 0; i < 8; i++){
      gainCard(province,&state,2,player);
   }

   assert(numHandCards(&state) == 13);

   endTurn(&state);

   finishFlag = isGameOver(&state);

   //PASS Condition: No Province card in supply AND isGameOver() returns 1
   if(state.supplyCount[province] == 0 && finishFlag == 1)
   {
      printf("PASS: Province cards supply finished \n\n\n");

   }
   else
      printf("FAIL: Province cards supply finished\n\n\n"); 


   /******* Test Three supply piles empty *******/

   printf("*******Test2: Three supply piles empty *******\n");
   initializeGame(numPlayers, k, seed, &state);
   finishFlag = 0;

   assert(numHandCards(&state) == 5);
   for(i = 0; i < 10; i++){
      gainCard(embargo,&state,2,player);
      gainCard(smithy,&state,2,player);
      gainCard(mine,&state,2,player);
   }
   assert(numHandCards(&state) == 35);

   endTurn(&state);
   finishFlag = isGameOver(&state);

   int emptyPile = 0;
   for(i = 0; i < 25; i++)
   {
      if (state.supplyCount[i] == 0)
      {
	 emptyPile++;
      }
   }

   //PASS Condition: More than or equal to 3 card piles empty AND isGameOver() returns 1
   if(emptyPile >= 3 && finishFlag == 1)
   {
      printf("PASS: Three supply piles empty\n\n\n");

   }
   else
      printf("FAIL: Three supply piles empty\n\n\n"); 

   printf("*******Testing isGameOver() Complete!*******\n\n\n");

   return 0;
}
