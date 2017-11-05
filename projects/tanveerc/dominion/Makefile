CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

randomtest: randomtestadventurer randomtestcard1 randomtestcard2
	$(info /********** REDIRECTING OUTPUTS TO --> .out files **********/)	
	
	./randomtestadventurer &> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out
	gcov -b randomtestadventurer.c >> randomtestadventurer.out 
	
	./randomtestcard1 &> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out
	gcov -b randomtestcard1.c >> randomtestcard1.out
	
	./randomtestcard2 &> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out
	gcov -b randomtestcard2.c >> randomtestcard2.out

randomtestadventurer.out: randomtestadventurer	
	$(info /********** REDIRECTING OUTPUTS TO --> randomtestadventurer.out **********/)
	./randomtestadventurer &> randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	gcov -b randomtestadventurer.c >> randomtestadventurer.out

randomtestcard1.out: randomtestcard1		
	$(info /********** REDIRECTING OUTPUTS TO --> randomtestcard1.out **********/)
	./randomtestcard1 &> randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	gcov -b randomtestcard1.c >> randomtestcard1.out

randomtestcard2.out: randomtestcard2	
	$(info /********** REDIRECTING OUTPUTS TO --> randomtestcard2.out **********/)
	./randomtestcard2 &> randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	gcov -b randomtestcard2.c >> randomtestcard2.out

randomtestadventurer: dominion.o randomtestadventurer.c
	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard1: dominion.o randomtestcard1.c
	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)

randomtestcard2: dominion.o randomtestcard2.c
	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard randomtest

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so *.out randomtestadventurer randomtestcard1 randomtestcard2
