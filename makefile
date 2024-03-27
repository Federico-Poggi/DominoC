OPTIONS=-O3 -DNDEBUG -Wall -Wextra -w
# 
all:build/dominoC
# 
debug:OPTION=-O0 -DNDEBUG -Wall -Wextra -w
debug:build/dominoC

build/dominoC: build/check.o build/domino.o build/ai.o build/mod1.o build/modAI.o tools/main.c
		gcc ${OPTIONS} src/domino.c src/ai.c src/mod1.c src/modAI.c src/check.c tools/main.c -o build/dominoC -I include/ 

build/check.o: src/check.c include/check.h include/domino.h
			gcc ${OPTIONS} -c src/check.c -o build/check.o -I include/

build/domino.o: src/domino.c include/domino.h
		gcc ${OPTIONS} -c src/domino.c -o build/domino.o -I include/

build/mod1.o: src/mod1.c build/domino.o build/check.o include/domino.h include/check.h
	gcc ${OPTIONS} -c src/mod1.c -o build/mod1.o -I include/

build/ai.o: src/ai.c include/ai.h include/check.h include/domino.h
	gcc ${OPTIONS} -c src/ai.c -o build/ai.o -I include/

build/modAI.o:src/modAI.c build/domino.o build/check.o build/ai.o include/domino.h include/check.h include/ai.h
	gcc ${OPTIONS} -c src/modAI.c -o build/modAI.o -I include/
 
clean: 
	rm -rf build/*.o build/dominoC