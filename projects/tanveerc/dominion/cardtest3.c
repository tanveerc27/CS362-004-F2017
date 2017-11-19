 /*****************************
	File: cardtest3.c
	Testing card: village
	Test1: Test player gains 2 cards in hand
	Test2: Test player action increases by 2
 ******************************/
 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdio.h>
 #include "rngs.h"
 #include <stdlib.h>
 #include <assert.h>
 #include <math.h>
 #include <string.h>
 
 
 #define TESTCARD "village"
 
 int main() {
     int handPos = 0;
     int seed = 1000;
     int numPlayers = 2;
     int player = 0;
     int handCountBefore;
     int handCountAfter;
	 int deckCountBefore;
	 int deckCountAfter;
     int numActBefore;
     int numActAfter;
     int bonus = 0;
     
 	struct gameState G, testG;
 	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
 			sea_hag, tribute, smithy, council_room};
 
 	// initialize a game state and player cards
 	initializeGame(numPlayers, k, seed, &G);
 
 	printf("\n\n\n---------------- cardtest3 ----------------\n\n");
 
 
 	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
 
 	/*************** TEST 1: Player gets +1 card ***********/
 	printf("*******TEST 1: Player gets +1 card *******\n");
 
 	// copy the game state to a test case and assign player to variable
 	memcpy(&testG, &G, sizeof(struct gameState));
 	player = testG.whoseTurn;
 
 	// give the player a village card
 	assert(numHandCards(&testG) == 5);
 	assert(gainCard(village,&testG,2,player) == 0);
 	assert(numHandCards(&testG) == 6);
 
 	// store number of cards in hand and deck before and after village played
 	handCountBefore = testG.handCount[player];
 	deckCountBefore = testG.deckCount[player];
	
	cardEffect(village, 0, 0, 0, &testG, handPos, &bonus);
 	
	deckCountAfter = testG.deckCount[player];
	handCountAfter = testG.handCount[player];
 
 	endTurn(&testG);
 
	//PASS Condition: Hand is unchanged (1 additions and 1 discard) AND deck decreases by 1 cards
 	if((handCountAfter == (handCountBefore + 1 - 1)) && (deckCountAfter == deckCountBefore - 1))
 	{
 		printf("PASS: Player gets +1 cards\n\n");
 	}
 	else
		printf("FAIL: Player gets +1 cards\n\n"); 
 

 
 	/*************** TEST 2: Player gains +2 actions ***********/
 	printf("*******TEST 2: Player gains +2 actions *******\n");
 
 	// copy the game state to a test case and assign player to variable
 	memcpy(&testG, &G, sizeof(struct gameState));
 	player = testG.whoseTurn;	
 
 	// give the player a village card
 	assert(numHandCards(&testG) == 5);
 	assert(gainCard(village,&testG,2,player) == 0);
 	assert(numHandCards(&testG) == 6);
 
 	// record number of actions before and after village is played
 	numActBefore = testG.numActions;
 	cardEffect(village, 0, 0, 0, &testG, handPos, &bonus);
 	numActAfter = testG.numActions;
 
 	// end current turn
 	endTurn(&testG);
 
 	//PASS Condition: Action increases by 1 (2 addition and 1 used)
 	if(numActAfter == (numActBefore + 2 - 1))
 	{
 		printf("PASS: Player gains +2 actions\n\n");
 	}
 	else
 		printf("FAIL: Player gains +2 actions\n\n");
 
 
 	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
 
 
 	return 0;
 }
 