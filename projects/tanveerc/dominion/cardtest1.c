/*****************************
File: cardtest1.c
Testing card: smithy
Test1: Test Player hand increases by 3 cards	
 ******************************/
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>


#define TESTCARD "smithy"

int main() {
   int discarded = 1;
   int handpos = 0;    
   int seed = 1000;
   int numPlayers = 2;
   int player = 0;
   int handCountBefore;
   int handCountAfter;
   int deckCountBefore;
   int deckCountAfter;
   int bonus = 0;
   int card = 8;

   struct gameState G, testG;
   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

   // initialize a game state and player cards
   initializeGame(numPlayers, k, seed, &G);

   printf("\n\n\n\n---------------- cardtest1 ----------------\n\n");

   printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

   /*************** TEST 1: Player gets +3 cards ***********/
   printf("*******TEST 1: Player gets +3 cards *******\n");

   // copy the game state to a test case
   memcpy(&testG, &G, sizeof(struct gameState));
   player = testG.whoseTurn;

   //printf("Number of cards in HAND is %d \n", numHandCards(&testG));

   // player gains smithy card
   assert(numHandCards(&testG) == 5);
   assert(gainCard(smithy,&testG,2,player) == 0);
   assert(numHandCards(&testG) == 6);

   //handpos = testG.handCount[player] - 1;

   // store number of cards in hand and deck before and after smithy played
   handCountBefore = testG.handCount[player];
   deckCountBefore = testG.deckCount[player];

   cardEffect(smithy, 0, 0, 0, &testG, handpos, &bonus);

   deckCountAfter = testG.deckCount[player];
   handCountAfter = testG.handCount[player];

   endTurn(&testG);

   //PASS Condition: If hand increases by 2(3 additions and 1 discard) card AND deck decreases by 3 cards
   if((handCountAfter == (handCountBefore + 3 - 1)) && (deckCountAfter == deckCountBefore - 3))
   {
      printf("PASS: Player gets +3 cards\n");
   }
   else
   {	
      printf("FAIL: Player gets +3 cards\n"); 
   }


   printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);


   return 0;
}
