 /*****************************
	File: cardtest2.c
	Testing card: adventurer
	Test1: Test two treasure card added to player hand
	Test2: Test tressure cards in deck decreased by 2
 ******************************/
 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdio.h>
 #include "rngs.h"
 #include <stdlib.h>
 #include <assert.h>
 #include <math.h>
 #include <string.h>
 
 
 #define TESTCARD "adventurer"
 
 int main() {
 
     int i;
     int handPos = 0;
     int seed = 1000;
     int numPlayers = 2;
     int player = 0;
     int numBefore;
     int numAfter;
     int coinsBefore;
     int coinsAfter;
     int deckCount = 0;
     int card = 0;
     int bonus = 0;
	 int treasureCardsBefore = 0;
	 int treasureCardsAfter = 0;
	
	
 	struct gameState G, testG, oldG;
 	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
 			sea_hag, gardens, smithy, council_room};
 
 	// initialize a game state and player cards
 	initializeGame(numPlayers, k, seed, &G);
 
 
 	printf("\n\n\n---------------- cardtest2 ----------------\n\n");
 
 	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
 
 	/*************** TEST 1: Two treasure cards are added to hand***********/
 	printf("*******TEST 1: Two treasure cards are added to hand*******\n");
 
 	// copy the game state to a test case
 	memcpy(&testG, &G, sizeof(struct gameState));
 	player = testG.whoseTurn;
	
	// player gains smithy card
 	assert(numHandCards(&testG) == 5);
 	assert(gainCard(adventurer,&testG,2,player) == 0);
 	assert(numHandCards(&testG) == 6);
	

	for(i = 0; i < numHandCards(&testG); i++){
		if (testG.hand[player][i] == copper)	treasureCardsBefore++;
		else if (testG.hand[player][i] == silver)	treasureCardsBefore++;
		else if (testG.hand[player][i] == gold)	treasureCardsBefore++;
	}

 	// give player an adventurer card and play it
 	cardEffect(adventurer, 0, 0, 0, &testG, handPos, &bonus);
 
	for(i = 0; i < numHandCards(&testG); i++){
		if (testG.hand[player][i] == copper)	treasureCardsAfter++;
		else if (testG.hand[player][i] == silver)	treasureCardsAfter++;
		else if (testG.hand[player][i] == gold)	treasureCardsAfter++;
	}

 	endTurn(&testG);
	
	//PASS Condition: Treasure cards in hand increases by 2
	if (treasureCardsAfter == treasureCardsBefore + 2)
	{
 		printf("PASS: Two treasure cards are added\n\n\n");
 	}
	else
		printf("FAIL: Two treasure cards are added\n\n\n");
	
	
	
	/*************** TEST 2: No. of treasure card in deck decreased by 2 ***********/
 	printf("*******TEST 2: No. of treasure card in deck decreased by 2 *******\n");

	// initialize a game state and player cards
 	initializeGame(numPlayers, k, seed, &G);
 	treasureCardsBefore = 0;
	treasureCardsAfter = 0;
	
	// copy the game state to a test case
 	memcpy(&testG, &G, sizeof(struct gameState));
 	player = testG.whoseTurn;
	
	// player gains adventurer card
 	assert(numHandCards(&testG) == 5);
 	assert(gainCard(adventurer,&testG,2,player) == 0);
 	assert(numHandCards(&testG) == 6);
	
	for(i = 0; i < testG.deckCount[player]; i++){
		if (testG.deck[player][i] == copper)	treasureCardsBefore++;
		else if (testG.deck[player][i] == silver)	treasureCardsBefore++;
		else if (testG.deck[player][i] == gold)	treasureCardsBefore++;
	}
	
	// adventurer card played
 	cardEffect(adventurer, 0, 0, 0, &testG, handPos, &bonus);
 
	for(i = 0; i < testG.deckCount[player]; i++){
		if (testG.deck[player][i] == copper)	treasureCardsAfter++;
		else if (testG.deck[player][i] == silver)	treasureCardsAfter++;
		else if (testG.deck[player][i] == gold)	treasureCardsAfter++;
	}
	
	endTurn(&testG);
	
	//PASS Condition: Treasure card in deck decreases by 2
	if (treasureCardsAfter == treasureCardsBefore - 2)
	{
 		printf("PASS: No. of treasure cards in deck decreased by 2 \n\n");
 	}
	else
		printf("FAIL: No. of treasure cards in deck decreased by 2 \n\n");
	
	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
	
	return 0;
}