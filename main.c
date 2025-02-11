#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

int menu_input(void);
void x_or_o(char *player_letter, char *computer_letter);
void display_menu(void);
void reset_board(char board[3][3]);
void print_board(char board[3][3]);
void player_move(char board[3][3], char *player_letter);
int check_winner(char board[3][3]);
void computer_move(char board[3][3], char *computer_letter);
int is_empty(char board[3][3], int row, int column);
int ask_row(void);
int ask_column(void);
void clear_buffer(void);
void print_winner(char winner);
void pvrnd(void);
void pvp(void);

int main(void)
{
	char board[3][3];
	reset_board(board);
	display_menu();
	int mode = menu_input();	

	switch(mode)
	{
		case 1:
			pvp();
		case 2:
			pvrnd();
	}

	return 0;
}

void x_or_o(char *player1_letter, char *player2_letter)
{
	int scanf_return;
	do
	{
		printf("X or O?\n");

		scanf_return = scanf(" %c", player1_letter);

		*player1_letter = toupper(*player1_letter); // dealing with case-sensitivity

		if (scanf_return != 1 || (*player1_letter != 'X'  && *player1_letter != 'O'))
		{
			// here we do && because basically if one of them is true (the player picked O or X) then it would just exit the loop
			printf("Invalid input. Please choose X or O\n");
		}
	}
	while(scanf_return != 1 || (*player1_letter != 'X'  && *player1_letter != 'O'));
	
	if (*player1_letter == 'X')
	{
		*player2_letter = 'O';
	}
	
	else
	{
		*player2_letter = 'X';
	}
	return;
}

void reset_board(char board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			board[i][j] = ' ';
		}
	}
	return;
}

void print_board(char board[3][3])
{
	printf("-------------------------\n");
	printf("|       |       |       |\n");
	
	printf("|   %c   |   %c   |   %c   |\n", board[0][0], board[0][1], board[0][2]);
	printf("|       |       |       |\n");
	printf("-------------------------\n");
	printf("|       |       |       |\n");
	
	printf("|   %c   |   %c   |   %c   |\n", board[1][0], board[1][1], board[1][2]);
	printf("|       |       |       |\n");
	printf("-------------------------\n");
	printf("|       |       |       |\n");
	
	printf("|   %c   |   %c   |   %c   |\n", board[2][0], board[2][1], board[2][2]);
	printf("|       |       |       |\n");
	printf("-------------------------\n");
	
	return;
}

void player_move(char board[3][3], char *player_letter)
{
	// asking for input
	int row = ask_row();
	int column = ask_column();

	// checking if the spot is occupied or not	
	// "-1" before row and column to turn the number provided by the player into a valid index
	while (is_empty(board, row-1, column-1) == 1) // as long as the provided spot is occupied
	{
		printf("\nthat spot is already occupied!\n\n");
		row = ask_row();
		column = ask_column();
	}
	board[row-1][column-1] = *player_letter;
}

int check_winner(char board[3][3])
{
	for (int i = 0; i < 3; i++)
	{
		// checking if one of them isn't a space is because we are making sure we don't accidently treat spaces as a spot for one of the players

		//checking rows
		if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
		{
			print_winner((board[i][0] == 'X') ? 'X' : 'O');
		}
	
		
		//checking columns
		if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
		{
			print_winner((board[0][i] == 'X') ? 'X' : 'O');
		}
	}	

		//checking diagonally
		
		if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
		{
			print_winner((board[0][0] == 'X') ? 'X' : 'O');
		}
		
		
		else if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
		{
			print_winner((board[0][2] == 'X') ? 'X' : 'O');
		}
	
	// if there is no winner the return value is -1
	return -1;
		
}

void computer_move(char board[3][3], char *computer_letter)
{
	int row;
	int column;
	
	do
	{
		// "rand() %3" would generate a number between 0 and 2 which is a valid range of indexes in the board
		row = rand() % 3;
		column = rand() % 3;
	}while(is_empty(board, row, column) == 1);
	
	board[row][column] = *computer_letter;
	return;
}

int is_empty(char board[3][3], int row, int column)
{
	if (board[row][column] == ' ')
	{
		return 0; // it is empty
	}
	
	else
	{
		return 1; // it is not empty
	}
}

int ask_row(void)
{
	int row;
	int scanf_return;
	do
	{
		
		printf("Row(1-3) : ");
		//clear_buffer(); // clearing buffer here causes a problem, basically it makes the user need to press enter multiple times
		scanf_return = scanf("%d", &row);

		if (scanf_return != 1)
		{
			printf("\n\ninvalid input.\n\n");
			clear_buffer();
		}

		else if (row < 1 || row > 3)
		{
			printf("Enter a number from 1 to 3\n\n");
		}
		
	}while(scanf_return != 1 || row < 1 || row > 3);
	
	return row;
	
}

int ask_column(void)
{
	int column;
	int scanf_return;
	do
	{
		
		printf("Column(1-3) : ");
		//clear_buffer(); // clearing buffer here causes a problem, basically it makes the user need to press enter multiple times
		scanf_return = scanf("%d", &column);

		if (scanf_return != 1)
		{ 
			printf("\n\ninvalid input.\n\n");
			clear_buffer();
                }

                else if (column < 1 || column > 3)
                {
                        printf("Enter a number from 1 to 3\n\n");
        	}
		
	}while(scanf_return != 1 || column < 1 || column > 3);
	
	return column;
}

void clear_buffer(void)
{
	while (getchar() != '\n');
	return;
}

void print_winner(char winner)
{
	printf("%c is the winner\n", winner);
	exit(0);
}

void display_menu(void)
{
	printf("\n\n\n");
	
	printf("+_____________+\n");
	printf("|             |\n");
	printf("|             |\n");
	printf("|TIC  TAC  TOE|\n");
	printf("|             |\n");
	printf("+_____________+\n");

	printf("\n\n\n");
	return;
}

int menu_input(void)
{
	printf("Options:\n\n");
	
	printf("1.Player vs Player\n");
	printf("2.Player vs computer (random number generator)\n");

	int choice;
	int scanf_return;
	
	do
	{
		printf("Your choice : ");
		scanf_return = scanf("%d", &choice);

		if (scanf_return != 1)
		{
			clear_buffer();
			printf("\ninvalid input\n");
			printf("try again\n\n");
		}

		else if (choice > 2 || choice < 1)
		{
			printf("\nout of range of choices\n");
			printf("try again\n\n");
		}

	}while(scanf_return != 1 || choice > 2 || choice < 1);

	return choice;
}

void pvrnd(void)
{
	srand(time(NULL)); // seeding the random number generator with the time in which the program runs which is going to be used for computer moves

        char board[3][3];
        char player_letter;
        char computer_letter;

        x_or_o(&player_letter, &computer_letter); // asking the player to pick either X or O

        reset_board(board); // initialising board
        print_board(board);

        printf("player letter : %c\n", player_letter);
        printf("computer letter : %c\n", computer_letter);

        for (int i = 0; i < 2; i++)
        {
                // no need for checking the winner here because the pla    yers can't win with just 2 moves , because the least required moves for a win is 3
                player_move(board, &player_letter);
                print_board(board);

                computer_move(board, &computer_letter);
                print_board(board);
        }

        for (int i = 0; i < 2; i++)
        {
                // here we start checking for wins
                // since now the moves are greater than or equal to 3 which is the least minimum required moves for a win
                player_move(board, &player_letter);
                print_board(board);

                check_winner(board);


                computer_move(board, &computer_letter);
                print_board(board);

                check_winner(board);
        }
        // here it is 100% one move left so there is no need to put it inside a loop
        player_move(board, &player_letter);
        print_board(board);
        if (check_winner(board) == -1) // if no one is a winner
        {
                // then it is a draw

                // it would be silly to make another function just for a draw when it is this simple and it is executed once in the entire code
                printf("it is a TIE\n");
        }
}

void pvp(void)
{
	char board[3][3];
	char player1_letter;
	char player2_letter;
	
        x_or_o(&player1_letter, &player2_letter); // asking the player to pick either X or O

        reset_board(board); // initialising board
        print_board(board);

        printf("player1 letter : %c\n", player1_letter);
        printf("player2 letter : %c\n", player2_letter);

        for (int i = 0; i < 2; i++)
        {
                // no need for checking the winner here because the pla    yers can't win with just 2 moves , because the least required moves for a win is 3
		printf("player 1: ");
                player_move(board, &player1_letter);
                print_board(board);

		printf("player 2: ");
                player_move(board, &player2_letter);
                print_board(board);
        }

        for (int i = 0; i < 2; i++)
        {
                // here we start checking for wins
                // since now the moves are greater than or equal to 3 which is the least minimum required moves for a win
		printf("player 1: ");
                player_move(board, &player1_letter);
                print_board(board);

                check_winner(board);

		printf("player 2: ");
                player_move(board, &player2_letter);
                print_board(board);

                check_winner(board);
        }
        // here it is 100% one move left so there is no need to put it inside a loop
	printf("player 1: ");
        player_move(board, &player1_letter);
        print_board(board);
        if (check_winner(board) == -1) // if no one is a winner
        {
                // then it is a draw

                // it would be silly to make another function just for a draw when it is this simple and it is executed once in the entire code
                printf("it is a TIE\n");
		exit(0);
        }
}
