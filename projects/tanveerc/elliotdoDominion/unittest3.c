 /*****************************
	File: unittest3.c
	Testing function: updateCoins()
	Test1: Test each coin type: copper, silver, gold
	Test2: Test with no treasure cards in hand
	Test3: Test with coin and bonus	
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
   int handNum = 0;
   
	printf("\n\n\n\n---------------- unittest3 ----------------\n\n");
 	printf("----------------Testing Function: updateCoins()----------------\n");
 
  	/******* Test one copper, one silver, one gold *******/
 
 	printf("*******Test1: Gain one copper, one silver, one gold*******\n");
 	initializeGame(2, k, seed, &state);
	
	handNum = numHandCards(&state);
	
	for(i = 0; i  < handNum; i++){
		discardCard(i, player, &state, 0);
	}
	
	assert(numHandCards(&state) == 0);
 	assert(gainCard(copper,&state,2,player) == 0);
 	assert(gainCard(silver,&state,2,player) == 0);
 	assert(gainCard(gold,&state,2,player) == 0);
 	assert(numHandCards(&state) == 3);
 
 	updateCoins(player, &state, bonus);
 	
	//PASS Condition: Total coin value is 6
	if(state.coins == 6)
 	{
 		printf("PASS: Gained one copper, one silver, one gold\n\n\n");
 		
 	}
 	else
 		printf("FAIL: Gained one copper, one silver, one gold\n\n\n");
 
 

 	/******* Test no treasure cards with other cards in hand *******/
 
 	printf("*******Test2: No Treasure Cards in hand *******\n");
 	initializeGame(2, k, seed, &state);
	
	handNum = numHandCards(&state);
	
	for(i = 0; i  < handNum; i++){
		discardCard(i, player, &state, 0);
	}
	
 	assert(numHandCards(&state) == 0);
 	assert(gainCard(council_room,&state,2,player) == 0);
	assert(gainCard(smithy,&state,2,player) == 0);
	assert(gainCard(sea_hag,&state,2,player) == 0);
 	assert(numHandCards(&state) == 3);
 	
 	updateCoins(player, &state, bonus);
 	
	//PASS Condition: Total coin value is 0
	if(state.coins == 0)
 	{
 		printf("PASS: No treasue cards in hand\n\n\n");
 		
 	}
 	else
 		printf("FAIL: No treasue cards in hand\n\n\n"); 
 
 
 
 	/******* Test two silver and bonus of 4 *******/
 
 	printf("*******Test3: Gain Two Silver and Bonus of 4*******\n");
 	initializeGame(2, k, seed, &state);
 	bonus = 4;
 	
	handNum = numHandCards(&state);
	
	for(i = 0; i  < handNum; i++){
		discardCard(i, player, &state, 0);
	}
	
	assert(numHandCards(&state) == 0);
 	assert(gainCard(silver,&state,2,player) == 0);
 	assert(gainCard(silver,&state,2,player) == 0);
 	assert(numHandCards(&state) == 2);

 	updateCoins(player, &state, bonus);
 	
	//PASS Condition: Total coin value is 8
	if(state.coins == 8)
 	{
 		printf("PASS: Gained two silver and bonus of 4\n\n\n");
 		
 	}
 	else
 		printf("FAIL: Gained two silver and bonus of 4\n\n\n"); 
 
 
 	printf("*******Testing updateCoins() Complete!*******\n\n\n");
 	return 0;
 }