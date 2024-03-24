OPTIONS=-O3 -DNDEBUG -Wall -Wextra -w
# 
all:build/dominoC
# 
debug:OPTION=-O0 -DNDEBUG -Wall -Wextra
debug:build/dominoC

build/dominoC: build/check.o build/domino.o build/mod1.o build/modAI.o tools/main.c
		gcc ${OPTIONS} src/domino.c src/mod1.c src/modAI.c src/check.c tools/main.c -o build/dominoC -I include/ 

build/check.o: src/check.c include/check.h include/domino.h
			gcc ${OPTIONS} -c src/check.c -o build/check.o -I include/

build/domino.o: src/domino.c include/domino.h
		gcc ${OPTIONS} -c src/domino.c -o build/domino.o -I include/

build/mod1.o: src/mod1.c build/domino.o build/check.o include/domino.h include/check.h
	gcc ${OPTIONS} -c src/mod1.c -o build/mod1.o -I include/

build/modAI.o:src/modAI.c build/domino.o build/check.o include/domino.h include/check.h
	gcc ${OPTIONS} -c src/modAI.c -o build/modAI.o -I include/
 
clean: 
	rm -rf build/*.o build/dominoC