#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

char* setup_game_board(unsigned height, unsigned width);
int make_move(char* board, unsigned columns, unsigned mRow, 
	unsigned mColumn, char orientation, char player);
char* get_line(FILE* file, unsigned maxchar);
unsigned count_integers(char* input);
unsigned slen(const char* input);
int check_game_over(char* board);
int check_complete(char* board, unsigned column, unsigned place);
void play_game(unsigned height, unsigned width, 
	unsigned playerCount, FILE* load);
int all_numbers(char* line);
int all_zeros_or_ones(char* line); 
unsigned load_game (char* board, FILE* data, unsigned arrayRow, 
	unsigned arrayColumn, unsigned row, unsigned column, 
	unsigned playerCount); 
void save_game (FILE* save, char* board, unsigned pCounter, unsigned height, 
	unsigned width);

/*main(int argc, char* argv[])
**		-main function of the game.
**		responsible for checking arguments on invoke
**		exit program on error
**		return 0 and exit program on game completion
**
**
**
**
**
*/
int main(int argc, char* argv[]) {
    unsigned height, width, playerCount;
    FILE* load = NULL;
    if((argc < 4) || (argc > 5)) {
	fprintf(stderr, "Usage: boxes height width playercount [filename]\n");
	exit(1);
    }
    if(argc == 5) {
	load = fopen(argv[4], "r");
	if (load == NULL) {
	    fprintf(stderr, "Invalid grid file\n");
	    exit(4);
	}
    }
    if((slen(argv[1]) < 4) && all_numbers(argv[1])) {
	height = atoi(argv[1]);
	if(height < 2) {
	    fprintf(stderr, "Invalid grid dimensions\n");
	    exit(2);
	}
    } else {
	fprintf(stderr, "Invalid grid dimensions\n");
	exit(2);
    }
    if((slen(argv[2]) < 4) && all_numbers(argv[2])) {
	width = atoi(argv[2]);
	if(width < 2) {
	    fprintf(stderr, "Invalid grid dimensions\n");
	    exit(2);	
	}
    } else {
	fprintf(stderr, "Invalid grid dimensions\n");
	exit(2);
    }
    if(all_numbers(argv[3])) {
	playerCount = atoi(argv[3]);
	if((playerCount > 100) || (playerCount < 2)) {
	    fprintf(stderr, "Invalid player count\n");
	    exit(3);
	}
    } else {
	fprintf(stderr, "Invalid player count\n");
        exit(3);
    }
    play_game(height, width, playerCount, load);
    return 0;
}
/*play_game(unsigned height, unsigned width, unsigned playerCount, FILE* load)
**		-function for gameplay.
**		returns nothing and prompt the correct user for move.
**
**
**
**
*/
void play_game(unsigned height, unsigned width, unsigned playerCount, 
	FILE* load) {
    int flush, replayState, i, j, k, l, m, n = 0, o = 1;
    unsigned rows, columns, numCounter, mRow, mColumn; 
    unsigned pCounter, winningCount = 0;
    char* board; 
    char* input;
    char* winnerList;
    char orientation, player = 'A';
    FILE* rawInput; 
    FILE* save;
    int squareCount[100];

    winnerList = (char*)malloc(sizeof(char) * playerCount + 1);
    rows = height * 2 + 1;
    columns = width * 2 + 2;
    board = setup_game_board(rows, columns);
    if (load != NULL) {
	pCounter = load_game(board, load, rows, columns, 
		height, width, playerCount);
	fclose(load);
    } else {
	pCounter = 0;
    }
    printf("%s", board);
    while (!check_game_over(board)) {
	if(feof(stdin)) {
	    fprintf(stderr, "End of user input\n");
	    exit(6);
	} else {
	    rawInput = stdin;
	}
	printf("%c> ", player + pCounter);
	input = get_line(rawInput, BUFFER_SIZE);
	if(slen(input) == BUFFER_SIZE) {
	    while((flush = getchar()) != '\n' && flush != EOF);
	}
	if ((input[0] == 'w') && input[1] == ' ') {
	    input += 2;
	    save = fopen(input, "w");
	    if (save == NULL) {
		fprintf(stderr, "Can not open file for write\n");
		continue;
	    } else {
		save_game(save, board, pCounter, height, width);
		fclose(save);
		fprintf(stderr, "Save complete\n");
		continue;
	    }
	}
	numCounter = count_integers(input);
	mRow = atoi(input);
	input = input + numCounter;
	if(input[0] != ' ') {
	    continue;
	}
	input++;
	numCounter = count_integers(input);
	mColumn = atoi(input);
	input = input + numCounter;
	if((input[0] != ' ') || (input[2] != '\0')) {
	    continue;
	}
	if(input[1] == 'v') {
	    orientation = input[1];
	} else if(input[1] == 'h') {
	    orientation = input[1];
	} else {
	    continue;
	}
	replayState = make_move(board, columns, mRow, mColumn, 
		orientation, player + pCounter);
	if(replayState == 0) {
	    continue;
	} else if(replayState == 2) {
	    pCounter--;
	}
	if(pCounter < (playerCount - 1)) {
	    pCounter++;
	} else {
	    pCounter = 0;
	}
	printf("%s", board);
    }
    for(i = 0; i < playerCount; i++) {
	squareCount[i] = 0;
    }
    for(j = 0; j < slen(board); j++) {
	k = board[j] - 'A';
	if((k >= 0) && (k < playerCount)) {
	    squareCount[k]++;
	}
    }
    for(l = 0; l < (playerCount); l++) {
	if(squareCount[l] > winningCount) {
	    winningCount = squareCount[l];
	}
    }
    for(m = 0; m < playerCount; m++) {
	if(squareCount[m] == winningCount) {
	    winnerList[n] = ('A' + m);
	    n++;
	}
    }
    winnerList[n] = '\0';
    printf("Winner(s): %c", winnerList[0]);
    while(winnerList[o] != '\0') {
	printf(", %c", winnerList[o]);
	o++;
    }
    printf("\n");
}

/*setup_game_board(unsigned rows, unsigned columns)
**		-create and return a game board with the dimension
**		given by rows and columns arguments.
**
**
**
**
*/
char* setup_game_board(unsigned rows, unsigned columns) {
    unsigned boardSize;
    unsigned i;
    char* board;
    boardSize = (columns) * rows;
    board = (char*)malloc(sizeof(char) * boardSize + 1);
    board[0] = '+';
    for (i = 1; i < boardSize; i++) {
	if ((i + 1) % columns == 0) {
	    board[i] = '\n';
	} else if ((i / columns) % 2 != 0) {
	    board[i] = ' ';	
	} else if (i % 2 == 0) {
	    board[i] = '+';
	} else {
	    board[i] = ' ';
	}
    }
    board[i] = '\0';
    return board;
}

/*make_move(char* board, unsigned columns, unsigned mRow, unsigned mColumn, 
**     char orientation, char player)
**		-Update the board with '-' or '|' based on mRow and mColumn
**		then check the surrounding space for completion 
**		using check_complete.
**		If space is completed update the board with the appropriate 
**		player char.
**		return 0 if board cannot be updated with move indicated by 
**		mRow/mColumn.
**		return 1 if board is updated by '-' or '|'.
**		return 2 if board is updated by player char.
*/
int make_move(char* board, unsigned columns, unsigned mRow, unsigned mColumn, 
	char orientation, char player) {
    unsigned place;
	
    place = mRow * 2 * columns + mColumn * 2;
    if (orientation == 'h') {
	place++;
	if (board[place] != ' ') {
	    return 0;
	} else {
	    board[place] = '-';
	    if((columns > place) && 
		    check_complete(board, columns, place + columns)) {
		board[place + columns] = player;
		return 2;
	    } else if((columns < place) && 
		    check_complete(board, columns, place + columns) && 
		    check_complete(board, columns, place - columns)) {
		board[place + columns] = player;
		board[place - columns] = player;
		return 2;
	    } else if((columns < place) && 
		    check_complete(board, columns, place - columns)) {
       	        board[place - columns] = player;
                return 2;
            } else if(check_complete(board, columns, place + columns)) {
		board[place + columns] = player;
		return 2;
	    }
	    return 1;
	}
    } else if (orientation == 'v') {
	place += columns;
	if (board[place] != ' ') {
	    return 0;
	} else {
	    board[place] = '|';
	    if(check_complete(board, columns, place + 1) && 
		    check_complete(board, columns, place - 1)) {
   	        board[place + 1] = player;
       	        board[place - 1] = player;
                return 2;
            } else if(check_complete(board, columns, place + 1)) {
                board[place + 1] = player;
                return 2;
            } else if(check_complete(board, columns, place - 1)) {
                board[place - 1] = player;
                return 2;
	    }
	    return 1;
	}
    } else {
	return 0;
    }
}

/*slen(const char* str)
**		-return the length of a given string in unsigned
**		integer.
**
**
**
**
*/
unsigned slen(const char* str) {
    unsigned i = 0;
    while(str[i] != '\0') {
	i++;
    }
    return i;
}

/*get_line(FILE* file, unsigned maxchar)
**		-read from a file pointer and return a string
**		of size maxchar or entire line which ever is
**		shorter.
**
**
**
*/
char* get_line(FILE* file, unsigned maxChar) {
    char* line;
    int i, character;

    line = (char*)malloc((maxChar + 1) * sizeof(char));
    if (file == NULL) {
	printf("File reading failed");
    } else {
	for(i = 0; i < maxChar; i++) {
	    character = fgetc(file);
	    if (((char)character) == '\n') {
		break;
	    } else if (feof(file)) {
		break;
	    }
	    line[i] = character;
	}
    }
    if(slen(line) > 0) {
	line[i] = '\0';
	return line;
    } else {
	line[0] = '\0';
	return line;
    }
}

/*count_integers (char* input) 
**		-return the index of last value between '0' and '9'
**		before the first occurance of a value outside that range.
**
**
**
**
*/
unsigned count_integers (char* input) {
    unsigned count = 0;
    while((input[count] <= '9') && (input[count] >= '0')) {
	count++;
    }
    return count;
}

/*check_complete (char* board, unsigned column, unsigned place)
**		-check the surrounding 4 spaces of index given by place 
**		for existance of '|' or '-' on the game board.
**		return 1 if space indicated by the place index is surrounded.
**		return 0 otherwise.
**
**
*/
int check_complete (char* board, unsigned column, unsigned place) {
    if((board[place + 1] == '|') && (board[place - 1] == '|') && 
	    (board[place - column] == '-') && (board[place + column] == '-')) {
	return 1;
    }
    return 0;
}

/*check_game_over (char* board)
**		-Takes a string representing the board state.
**		 return 1 if the board has been filled up completely 
**		ie(no ' ' char).
**		 return 0 otherwise.
**
**
**
*/
int check_game_over (char* board) {
    int i;
    for(i = 0; i < slen(board); i++) {
	if (board[i] == ' ') {
	    return 0;
	}
    }
    return 1;
}

/*all_numbers(char* line)
** 		-Takes a char* containing a string.
**       return 1 if string only contain value between '0' and '9'.
**       return 0 otherwise.
**
**
**
*/
int all_numbers(char* line) {
    int i;
    for (i = 0; i < slen(line); i++) {
	if(!((line[i] >= '0') && (line[i] <= '9'))) {
	    return 0;
	}
    }
    return 1;
}

/*all_zeros_or_ones(char* line)
**		-Takes a char* containing a string.
**		 return 1 if string only contain '0' or '1'.
**		 return 0 otherwise.
**
**
**
*/
int all_zeros_or_ones(char* line) {
    int i;
    for (i = 0; i < slen(line); i++) {
	if(!((line[i] >= '0') && (line[i] <= '1'))) {
	    return 0;
	}
    }
    return 1;
}

/*load_game (char* board, FILE* data, unsigned arrayRow, unsigned arrayColumn, 
** unsigned row, unsigned column, unsigned playerCount)
**		-Map out a saved gamestate from a given file pointer.
**		 Return an unsigned integer representing the turn player.
**		 exits the program if given file contains illegal input.
**
**
*/
unsigned load_game (char* board, FILE* data, unsigned arrayRow, 
	unsigned arrayColumn, unsigned row, unsigned column, 
	unsigned playerCount) {
    char* line;
    unsigned turnPlayer, integerCount, player, pCounter, i, j, k;
    line = get_line(data, 4);
    if (all_numbers(line)) {
	turnPlayer = atoi(line);
	if ((turnPlayer < 1) || (turnPlayer > playerCount)) {
	    fprintf(stderr, "Error reading grid contents\n");
            exit(5);
	}
	pCounter = turnPlayer - 1;
    } else {
	fprintf(stderr, "Error reading grid contents\n");
        exit(5);
    }
    for (i = 0; i < arrayRow; i++) {
	if (!(i % 2)) {
	    line = get_line(data, column + 1);
	    if ((slen(line) != column) || !all_zeros_or_ones(line)) {
		fprintf(stderr, "Error reading grid contents\n");
		exit(5);
	    }
	    k = 0;
	    for (j = 1 + (i * arrayColumn); 
		    j < (i * arrayColumn) + (column * 2); j += 2) {
		if (line[k] == '0') {
		    k++;
		    continue;
		}
		board[j] = '-';
		k++;
	    }
	} else {
	    line = get_line(data, column + 2);
	    if ((slen(line) != (column + 1)) || !all_zeros_or_ones(line)) {
                fprintf(stderr, "Error reading grid contents\n");
                exit(5);
            }
	    k = 0;
	    for (j = (i * arrayColumn); j < (i * arrayColumn) + (arrayColumn); 
		    j += 2) {
                if (line[k] == '0') {
                    k++;
                    continue;
                }
                board[j] = '|';
		k++;
	    }
	}
    }
    for (i = 1; i < arrayRow; i += 2) {
	line = get_line(data, column * 4 + 1);
	if ((slen(line) > (column * 4 - 1))) {
            fprintf(stderr, "Error reading grid contents\n");
            exit(5);
        }
	for (j = 1; j < arrayColumn; j += 2) {
	    integerCount = count_integers(line);
	    player = atoi(line);
	    if ((player < 0) || (player > playerCount)) {
		fprintf(stderr, "Error reading grid contents\n");
                exit(5);
	    } else if (player != 0) {
		board[j + i * arrayColumn] = 'A' + player - 1;
	    }
	    line = line + integerCount;
	    if (line[0] == ',') {
		line++;
	    } else if ((line[0] == '\0') && (j = (arrayColumn - 2))) {
		continue;
	    } else {
		fprintf(stderr, "Error reading grid contents\n");
	        exit(5);
	    }
	}
    }
    for (i = 0; i < arrayRow * arrayColumn; i += 2) {
	if ((i / arrayColumn) % 2 == 0) {
	    i += (arrayColumn - 2);
	} else {
	    if (board[i] == '\0') {
		break;
	    } else if ((board[i + 1] == '\n')) {
		continue;
	    } else if ((board[i + 1] == ' ') && 
		    (check_complete(board, arrayColumn, (i + 1)))) {
		fprintf(stderr, "Error reading grid contents\n");
                exit(5);
	    } else if ((board[i + 1] != ' ') && 
		    (!(check_complete(board, arrayColumn, (i + 1))))) {
		fprintf(stderr, "Error reading grid contents\n");
                exit(5);
	    }
	}
    }
    return pCounter;
}

/*save_game (FILE* save, char* board, unsigned pCounter, unsigned height, 
** 		unsigned width)
**    -Update the file pointer save to contain a string
**	   in the required format for the savefile.	
**
**
**
**
*/
void save_game (FILE* save, char* board, unsigned pCounter, unsigned height, 
	unsigned width) {
    char* boardState;
    char* playerState;
    char playerOccupy[5];
    int squarePosition, i, j, k;
    boardState = (char*)malloc((((width + 1) * 2 + 1) * height + width + 2) * 
	    sizeof(char));
    playerState = (char*)malloc(((width + 1) * height) * sizeof(char));
    k = 0;
    for (i = 0; i < (height * 2 + 1); i++) {
	if (!(i % 2)) {
	    for (j = i * (width * 2 + 2) + 1; j < (i + 1) * (width * 2 + 2); 
		    j += 2) {
		if (board[j] == ' ') {
		    boardState[k] = '0';
		    k++;
		} else if (board[j] == '-') {
		    boardState[k] = '1';
		    k++;
		} else {
		    boardState[k] = board[j];
		    k++;
		}
	    }
	} else {
	    for (j = i * (width * 2 + 2); j <= (i + 1) * (width * 2 + 2); 
		    j += 2) {
                if (board[j] == ' ') {
                    boardState[k] = '0';
                    k++;
                } else if (board[j] == '|') {
                    boardState[k] = '1';
                    k++;
                } else {
		    boardState[k] = '\n';
                    k++;
                }
         
	    }
	}
    }
    boardState[k] = '\0';
    k = 0;
    squarePosition = width * 2 + 3;
    if ((board[squarePosition] == ' ')) {
	playerState[k] = '0';
    } else {
	sprintf(playerOccupy, "%d", ((int)board[squarePosition] - 64));
	strcat(playerState, playerOccupy);
	k += slen((char*)playerOccupy) - 1;
    }
    k++;
    for (squarePosition = (width * 2 + 5); squarePosition < slen(board); 
	    squarePosition += 2) {
	if ((squarePosition - 1) / ((width + 1) * 2) % 2) {
	    if ((board[squarePosition] == '\n') || 
		    (board[squarePosition] == '\0')) {
		playerState[k] = board[squarePosition];
		k++;
		continue;
	    }
	    if ((playerState[k - 1] == '\n')) {
		if ((board[squarePosition] == ' ')) {
		    playerState[k] = '0';
		    k++;
		} else {
		    sprintf(playerOccupy, "%d", 
			    ((int)board[squarePosition] - 64));
    		    strcat(playerState, playerOccupy);
            	    k += slen((char*)playerOccupy);
		}
	    } else if ((board[squarePosition] == ' ')) {
		playerState[k] = ',';
		k++;
		playerState[k] = '0';
		k++;
	    } else {
		sprintf(playerOccupy, "%d", 
			((int)board[squarePosition] - 64));
		playerState[k] = ',';
		k++;
		strcat(playerState, playerOccupy);
		k += slen((char*)playerOccupy);
	    }
	} else {
	    squarePosition += (width * 2);
	}
    }
    fprintf(save, "%d\n%s%s", pCounter + 1, boardState, playerState);
}
