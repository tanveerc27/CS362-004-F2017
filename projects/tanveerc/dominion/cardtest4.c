 /*****************************
	File: cardtest4.c
	Testing card: steward
	Test1: Test player gains 2 cards in hand
	Test2: Test player gains 2 coins
	Test3: Test two card trahsed from player's hand
 ******************************/
 #include "dominion.h"
 #include "dominion_helpers.h"
 #include <stdio.h>
 #include "rngs.h"
 #include <stdlib.h>
 #include <assert.h>
 #include <math.h>
 #include <string.h>
 
 
 #define TESTCARD "steward"
 
 int main() {
     int i,j;
	 int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0;
     int seed = 1000;
     int numPlayers = 2;
     int player = 0;
     int handCountBefore;
     int handCountAfter;
	 int deckCountBefore;
	 int deckCountAfter;
     int numCoinsBefore;
     int numCoinsAfter;
     int bonus = 0;
     time_t t;
	 
	 srand((unsigned) time(&t));
	 
	 
 	struct gameState G, testG;
 	int k[10] = {adventurer, embargo, village, minion, mine, steward,
 			sea_hag, tribute, smithy, council_room};
 
 	// initialize a game state and player cards
 	initializeGame(numPlayers, k, seed, &G);
 
 	printf("\n\n\n---------------- cardtest4 ----------------\n\n");
 
 
 	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
 
 	/*************** TEST 1: (Choice1 = 1) Player gets +2 card ***********/
 	printf("*******TEST 1: (Choice1 = 1) Player gets +2 card *******\n");
 
 	// copy the game state to a test case and assign player to variable
 	memcpy(&testG, &G, sizeof(struct gameState));
 	player = testG.whoseTurn;
	choice1 = 1;
	
	int temp;
 	// give the player a steward card
 	assert(numHandCards(&testG) == 5);
 	
	//temp = gainCard(steward,&testG,2,player);
	
	//printf("The return from gainCard is %d \n\n\n", temp);
	assert(gainCard(steward,&testG,2,player) == 0);
 	assert(numHandCards(&testG) == 6);
	handPos = testG.handCount[player] - 1;
	
 	// store number of cards in hand and deck before and after steward played
 	handCountBefore = testG.handCount[player];
 	deckCountBefore = testG.deckCount[player];
	
	cardEffect(steward, choice1, choice2, choice3, &testG, handPos, &bonus);
 	
	deckCountAfter = testG.deckCount[player];
	handCountAfter = testG.handCount[player];
 
 	endTurn(&testG);
 
	//PASS Condition: Hand increases by 1 card (2 additions and 1 discard) AND deck decreases by 2 cards
 	if((handCountAfter == (handCountBefore + 2 - 1)) && (deckCountAfter == deckCountBefore - 2))
 	{
 		printf("PASS: Player gets +2 cards\n\n");
 	}
 	else
		printf("FAIL: Player gets +2 cards\n\n"); 
 

 
 	/*************** TEST 2: (Choice1 = 2) Player gets +2 coins ***********/
 	printf("*******TEST 2: (Choice1 = 2) Player gets +2 coins *******\n");
 
 	// copy the game state to a test case and assign player to variable
 	memcpy(&testG, &G, sizeof(struct gameState));
 	player = testG.whoseTurn;	
	choice1 = 2;
 
 	// give the player a village card
 	assert(numHandCards(&testG) == 5);
 	assert(gainCard(steward,&testG,2,player) == 0);
 	assert(numHandCards(&testG) == 6);
	handPos = testG.handCount[player] - 1;
	
 	// record number of actions before and after village is played
 	numCoinsBefore = testG.coins;
 	cardEffect(steward, choice1, choice2, choice3, &testG, handPos, &bonus);
 	numCoinsAfter = testG.coins;
 
 	// end current turn
 	endTurn(&testG);
 
 	//PASS Condition: Number of coins increases by 2
 	if(numCoinsAfter == (numCoinsBefore + 2))
 	{
 		printf("PASS: Player gets +2 coins\n\n");
 	}
 	else
 		printf("FAIL: Player gets +2 coins\n\n");
 
 
	
 	/*************** TEST 3: (Choice1 = 3) Player trashes 2 cards ***********/
 	printf("*******TEST 3: (Choice1 = 3) Player trashes 2 cards *******\n");
 
 	// copy the game state to a test case and assign player to variable
 	memcpy(&testG, &G, sizeof(struct gameState));
 	player = testG.whoseTurn;	
	choice1 = 3;
 
 	// give the player a steward card
 	assert(numHandCards(&testG) == 5);
 	assert(gainCard(steward,&testG,2,player) == 0);
 	assert(numHandCards(&testG) == 6);
	handPos = testG.handCount[player] - 1;
	
	i = rand() % 5;
	j = rand() % 5;
	while (i == j)
		j = rand() % 5;
	
	choice2 = testG.hand[player][i];
	choice3 = testG.hand[player][j];
	
	// store number of cards in hand and deck before and after steward played
 	handCountBefore = testG.handCount[player];
	cardEffect(steward, choice1, choice2, choice3, &testG, handPos, &bonus);
	handCountAfter = testG.handCount[player];

	endTurn(&testG);
 
	//PASS Condition: Hand decreases by 3 cards (2 trashed and 1 discarded)
 	if(handCountAfter == (handCountBefore - 3))
 	{
 		printf("PASS: Player trashed 2 cards\n");
 	}
 	else
		printf("FAIL: Player trashed 2 cards\n"); 
	


	printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTCARD);
 
 
 	return 0;
 }