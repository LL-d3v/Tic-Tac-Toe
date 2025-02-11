game: main.c
	gcc main.c -o game -Wall -Wextra -Werror

clean:
	rm -f game
