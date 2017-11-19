/*********************************
File: randomtestcard2.c 
Testing Card: Steward
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

#define TESTCARD "steward"
#define MAX_RUN 5000


int main(){

   int i, j, l;
   int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
   int seed;
   int numPlayers = 2;
   int player = 0;
   int addCards = 0;
   int discards = 0;

   int handCountBefore = 0;
   int handCountAfter = 0;
   int deckCountBefore = 0;
   int deckCountAfter = 0;
   int coinsBefore = 0;
   int coinsAfter = 0;
   int option1error = 0;
   int option2error = 0;
   int option3error = 0;
   int testAddCard = 0;
   int testCoins = 0;
   int testTrash = 0;

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

      choice1 = (rand() % 3) + 1;
      choice2 = floor(Random() * G.handCount[player]);
      choice2 = floor(Random() * G.handCount[player]);
      while (choice2 == choice3)
	 choice3 = floor(Random() * G.handCount[player]);


      for (j = 0; j < G.handCount[player]; j++) 
	 G.hand[player][j] = floor(Random() * (treasure_map + 1));

      for (j = 0; j < G.discardCount[player]; j++) 
	 G.discard[player][j] = floor(Random() * (treasure_map + 1));

      for (j = 0; j < G.deckCount[player]; j++) 
	 G.deck[player][j] = floor(Random() * (treasure_map + 1));

      // hand and deck count before test
      handCountBefore = G.handCount[player];
      deckCountBefore = G.deckCount[player];
      coinsBefore = G.coins;

      // copy the game state to a test case
      memcpy(&testG, &G, sizeof(struct gameState));
      cardEffect(steward, choice1, choice2, choice3, &testG, handpos, &bonus);

      // hand and deck count after test
      handCountAfter = testG.handCount[player];
      deckCountAfter = testG.deckCount[player];			
      coinsAfter = testG.coins;

      //check player hand increases by 1 (2 adds and 1 discard)
      if (choice1 == 1){
	 testAddCard++;
	 addCards = 2;
	 discards = 1;
	 if ((handCountAfter != handCountBefore + addCards - discards) && (deckCountAfter != deckCountBefore - addCards))
	    option1error++;

      }

      //check number of coins increases by 2
      else if (choice1 == 2) {
	 testCoins++;
	 if (coinsAfter != coinsBefore + 2)
	    option2error++;

      }

      //check player hand decreases by 3 (2 trashed and 1 discard)
      else if (choice1 == 3) {
	 testTrash++;
	 discards = 3;
	 if (handCountAfter != handCountBefore - discards)
	    option3error++;

      }

      // reset variables
      handCountBefore = 0;
      handCountAfter = 0;
      deckCountBefore = 0;
      deckCountAfter = 0;
      coinsBefore = 0;
      coinsAfter = 0;

   }

   //print sum of errors for each test type
   printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

   // High FAIL rate for choice1 = 1, due to the modified code of Steward
   printf("TEST RESULTS\n");
   printf("Number of Test Runs: %d \n", MAX_RUN);
   printf("For Choice1 = 1, Test failed %d of %d runs\n",option1error, testAddCard);
   printf("For Choice1 = 2, Test failed %d of %d runs\n",option2error, testCoins);
   printf("For Choice1 = 3, Test failed %d of %d runs\n\n\n",option3error, testTrash);

   return 0;
}
