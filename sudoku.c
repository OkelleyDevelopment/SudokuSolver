#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE 11
#define SIZE 9

void displayBoard(int board[SIZE][SIZE]){
    printf("\n");
    for(int i = 0; i < SIZE; i++){
        if(i % 3 == 0 && i != 0){
            printf("------------------------\n");
        }
        for(int j = 0; j < SIZE; j++){
            if(j % 3 == 0 && j != 0){
                printf(" | ");
            }

            if(j == 8){
                printf("%d\n", board[i][j]);
            } else {
                printf("%d ", board[i][j]);
            }
        }
    }
    printf("\n");
}

int read_file(int board[SIZE][SIZE], char *path){
    FILE *file;
    file = fopen(path, "r");

    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            int result = 0;
            fscanf(file, "%d", &result);
            board[i][j] = result;
        }
    }

    fclose(file);
    //displayBoard(board);
    return 0;
}

void write_to_file(int board[SIZE][SIZE], char *path){
    FILE *file;
    file = fopen(path, "w+");

    for(int i = 0; i < SIZE; i++){
        if(i % 3 == 0 && i != 0){
            fprintf(file, "------------------------\n");
        }
        for(int j = 0; j < SIZE; j++){
            if(j % 3 == 0 && j != 0){
                fprintf(file, " | ");
            }

            if(j == 8){
                fprintf(file, "%d\n", board[i][j]);
            } else {
                fprintf(file, "%d ", board[i][j]);
            }
        }
    }
    fprintf(file, "\n");
}



bool locate(int board[SIZE][SIZE], int *row, int *col){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(board[i][j] == 0){
                *row = i;
                *col = j;
                return true;
            }
        }
    }
    return false;
}

bool validate(int board[SIZE][SIZE], int num, int *row, int *col){
    // Check the row
    for(int i = 0; i < SIZE; i++){
        if(board[*row][i] == num && *col != num){
            return false;
        }
    }

    // Check the column
    for(int i = 0; i < SIZE; i++){
        if(board[i][*col] == num && *row != num){
            return false;
        }
    }

    // Get the position in the matrix
    int x = *row - (*row % 3);
    int y = *col - (*col % 3);
    int i, j;
    for(i = x; i <= x + 2; i++){
        for(j = y; j <= y + 2; j++){
            if(board[i][j] == num){
                return false;
            }
        }
    }
    return true;
}

int solve(int board[SIZE][SIZE]){
    int row;
    int col;

    // First we need to find the first available cell
    bool located = locate(board, &row, &col);

    if(located == false){
        return true;
    } 

    // Now that we have the next open cell
    // we need to fill in the digit 
    for(int i = 1; i < 10; i++){
        //printf("Iteration ===> %d\n", i);
        if(validate(board, i, &row, &col) == true){
            // if its valid we set the current cell
            // to the current value
            board[row][col] = i;

            if (solve(board) == true){
                return true;
            }
            
            // This allows us to reset the board or
            // "backtrack" if the current iteration 
            // provided no result
            board[row][col] = 0;
        }
    }
    // Return false for an unsovlable
    // board
    return false;
}



int main(int argc,  char *argv[]){
    char *in_file = NULL;
    char *out_file = NULL;

	if(argc != 3){
		printf("Usage: ./Struct_sort inputFile outputFile\n");
		exit(1);
	}
	in_file = argv[1];
	if(in_file == NULL){
		fprintf(stderr, "ERROR: couldn't open %s for reading\n", argv[1]);
		exit(1);
	}
    out_file = argv[2];
	if(out_file == NULL){
		fprintf(stderr, "ERROR: couldn't open %s for writing\n", argv[2]);
		exit(1);
	}

    printf("\nWelcome to the C Sudoku Solver\n");
    
    int board[SIZE][SIZE];
    
    read_file(board, in_file);
    
    displayBoard(board);
    
    // Backtracking time 
    if(solve(board)){
        printf("Solution found!\n");
        displayBoard(board);    
        write_to_file(board, out_file);
    } else {
        printf("Solution not found!");
    }
       return 0;
}
