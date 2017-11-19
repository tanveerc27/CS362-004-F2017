/*********************************
File: randomtestadventurer.c 
Testing Card: Adventurer
 *********************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define TESTCARD "adventurer"
#define MAX_RUN 5000


int main(){

   int i, j, l;
   int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
   int seed;
   int numPlayers = 2;
   int player = 0;

   int handTreasureBefore = 0;
   int handTreasureAfter = 0;
   int deckTreasureBefore = 0;
   int deckTreasureAfter = 0;
   int addTreasures = 0;
   int handError = 0;
   int deckError = 0;

   srand(time(NULL));

   struct gameState G, testG;
   int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

   printf("----------------- Testing Card: %s ----------------\n", TESTCARD);

   for (i = 0; i < MAX_RUN; i++){	
      seed = (rand() % 2000) + 1;
      for (l = 0; l < sizeof(struct gameState); l++)
	 ((char*)&G)[l] = floor(Random() * 256);

      // initialize a random game state and random number of cards
      initializeGame(numPlayers, k, seed, &G);

      G.handCount[player] = floor(Random() * MAX_HAND);
      G.deckCount[player] = floor(Random() * MAX_DECK);
      G.discardCount[player] = floor(Random() * MAX_DECK);

      for (j = 0; j < G.handCount[player]; j++) 
	 G.hand[player][j] = floor(Random() * (treasure_map + 1));

      for (j = 0; j < G.discardCount[player]; j++) 
	 G.discard[player][j] = floor(Random() * (treasure_map + 1));

      for (j = 0; j < G.deckCount[player]; j++) 
	 G.deck[player][j] = floor(Random() * (treasure_map + 1));

      // Number of treasure cards in hand before test
      for(j = 0; j < numHandCards(&G); j++){
	 if (G.hand[player][j] == copper)	handTreasureBefore++;
	 else if (G.hand[player][j] == silver)	handTreasureBefore++;
	 else if (G.hand[player][j] == gold)	handTreasureBefore++;
      }

      // number of treasure cards in deck before test
      for(j = 0; j < G.deckCount[player]; j++){
	 if (G.deck[player][j] == copper)	deckTreasureBefore++;
	 else if (G.deck[player][j] == silver)	deckTreasureBefore++;
	 else if (G.deck[player][j] == gold)	deckTreasureBefore++;
      }

      // number of treasure cards to be added to hand AND to be subtracted from deck
      if (deckTreasureBefore == 0)	addTreasures = deckTreasureBefore;
      else if (deckTreasureBefore == 1)	addTreasures = deckTreasureBefore;
      else if (deckTreasureBefore >= 2)	addTreasures = 2;

      // copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));
      cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);

      // number of treasure cards in hand after test
      for(j = 0; j < numHandCards(&testG); j++){
	 if (testG.hand[player][j] == copper)	handTreasureAfter++;
	 else if (testG.hand[player][j] == silver)	handTreasureAfter++;
	 else if (testG.hand[player][j] == gold)	handTreasureAfter++;
      }

      // number of treasure cards in deck after test
      for(j = 0; j < testG.deckCount[player]; j++){
	 if (testG.deck[player][j] == copper)	deckTreasureAfter++;
	 else if (testG.deck[player][j] == silver)	deckTreasureAfter++;
	 else if (testG.deck[player][j] == gold)	deckTreasureAfter++;
      }				

      /*************** TEST 1: Treasure cards added to hand ***********/
      //check treasure cards in hand
      if (handTreasureAfter != handTreasureBefore + addTreasures)
	 handError++;

      /*************** TEST 2: Treasure cards deducted from deck ***********/
      //check treasure cards in deck
      if (deckTreasureAfter != deckTreasureBefore - addTreasures)
	 deckError++;

      // reset variables
      handTreasureBefore = 0;
      handTreasureAfter = 0;
      deckTreasureBefore = 0;
      deckTreasureAfter = 0;
      addTreasures = 0;

   }

   //print sum of errors for each test type
   printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

   // High FAIL rate due to the modified code of Adventurer
   printf("TEST RESULTS\n");
   printf("Number of Test Runs: %d \n", MAX_RUN);
   printf("Player hand count failed %d of %d runs\n",handError, MAX_RUN);
   printf("Player deck count failed %d of %d runs\n\n\n",deckError, MAX_RUN);

   return 0;
}
