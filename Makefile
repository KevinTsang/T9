%.o: %.c
	gcc -g -Wall -std=c11 -o $@ -c $<

t9: t9.o trie.o list.o
	gcc -g -Wall -o t9 $^

.PHONY: clean
clean:
	rm *.o t9
