 /*****************************
	File: unittest4.c
	Testing function: gainCard()
	Test1: Test specific supply pile empty. Fails to gain card
	Test2: Test add a card to deck
	Test3: Test add a card to hand
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
   int i;
   int player = 0;
   int bonus = 0;
   int handCountBefore;
   int handCountAfter;
   int deckCountBefore;
   int deckCountAfter;
   
   int handNum = 0;
   int toFlag = 0;
   int supplyOver = 0;
   
	printf("\n\n\n\n---------------- unittest4 ----------------\n\n");
 	printf("----------------Testing Function: gainCard() ----------------\n");
 
  	/******* Test Specific supply pile empty. Fail to gain card *******/
 
 	printf("*******Test1: Specific supply pile empty. Fail to gain card *******\n");
 	initializeGame(2, k, seed, &state);
	
	for(i = 0; i  < 10; i++){
		gainCard(smithy, &state, 1, player);
	}
	
	supplyOver = gainCard(smithy, &state, 1, player);
	
	//PASS Condition: gainCard() returns -1, indicating pile is empty
	if(supplyOver == -1)
 	{
 		printf("PASS: Specific supply pile empty. Fail to gain card\n\n\n");
 		
 	}
 	else
 		printf("FAIL: Specific supply pile empty. Fail to gain card\n\n\n"); 
 

 	/******* Test Add card to deck *******/
 
 	printf("*******Test2: Add card to deck *******\n");
 	initializeGame(2, k, seed, &state);
	toFlag = 1;
	
	deckCountBefore = state.deckCount[player];
	
	gainCard(village, &state, toFlag, player);
	
	deckCountAfter = state.deckCount[player];
 	
	//PASS Condition: Deck size increases by 1 AND the card added is village
	if((deckCountAfter == deckCountBefore + 1) && (state.deck[player][deckCountAfter - 1] == village))
 	{
 		printf("PASS: Added card to deck\n\n\n");
 	}
 	else
 		printf("FAIL: Add card to deck\n\n\n"); 
 
 
 
 	/******* Test Add card to hand *******/
 
 	printf("*******Test3: Add card to hand *******\n");
 	initializeGame(2, k, seed, &state);
	toFlag = 2;
	
	handCountBefore = state.handCount[player];
	
	gainCard(adventurer, &state, toFlag, player);
	
	handCountAfter = state.handCount[player];
 	
	//PASS Condition: Hand size increases by 1 AND the card added is adventurer
	if((handCountAfter == handCountBefore + 1) && (state.hand[player][handCountAfter - 1] == adventurer))
 	{
 		printf("PASS: Added card to hand\n\n\n");
 	}
 	else
 		printf("FAIL: Add card to hand\n\n\n"); 
 
 
 	printf("*******Testing gainCard() Complete!*******\n\n\n");
 	return 0;
 }