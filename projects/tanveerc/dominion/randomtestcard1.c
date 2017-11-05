/*
 * smithy - make sure deck size decreases by three cards
 *		see if player hand increases by 3 cards, 
 *	- stops when 2 treasure cards are revealed
 * 	- all revealed non-treasure cards are discarded
 *	- no treasure cards in deck (end of deck)
 *	- deck is shuffled when needed (at beginning and middle) **
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>

#define TESTCARD "smithy"
#define MAX_RUN 5000

int main() {

	int i, j, l;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed;
    int numPlayers = 2;
    int player = 0;
    int discard = 0;

	int handCountBefore = 0;
	int handCountAfter = 0;
	int deckCountBefore = 0;
	int deckCountAfter = 0;
	int addCards = 0;
	int handError = 0;
	int deckError = 0;

	srand(time(NULL));

	struct gameState G, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	
	for (i = 0; i < MAX_RUN; i++) 
	{	
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
		
		// hand and deck count before test
		handCountBefore = G.handCount[player];
		deckCountBefore = G.deckCount[player];

		// copy the game state to a test case
		memcpy(&testG, &G, sizeof(struct gameState));
		cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
		discard = 1;	// smithy will be discarded from hand
		addCards = 3;	

		// hand and deck count after test
		handCountAfter = testG.handCount[player];
		deckCountAfter = testG.deckCount[player];			
		
		/*************** TEST 1: Player hand increases by +3 cards ***********/
		if (handCountAfter != handCountBefore + addCards - discard)
		{
			handError++;
		}
		
		/*************** TEST 2: Player decreases by -3 cards ***********/
		if (deckCountAfter != deckCountBefore - addCards)
		{
			deckError++;
		}

		// reset variables
		handCountBefore = 0;
		handCountAfter = 0;
		deckCountBefore = 0;
		deckCountAfter = 0;
		
	}

	//print sum of errors for each test type
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);

	// High FAIL rate due to the modified code of Smithy
	printf("TEST RESULTS\n");
	printf("Number of Test Runs: %d \n", MAX_RUN);
	printf("Player hand count failed %d of %d runs\n",handError, MAX_RUN);
	printf("Player deck count failed %d of %d runs\n\n\n",deckError, MAX_RUN);
	return 0;
}

