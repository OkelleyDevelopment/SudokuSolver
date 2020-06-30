/**
 * A Sudoku Solver using the backtracking algorithm
 *
 * @author: Nicholas O'Kelley
 *
 * @date: June 23, 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Size of the row and column
#define SIZE 9

/**
 * Function that takes a 2D array and then displays
 * the array in the Sudoku board format
 *
 * @param board - 2D array 
 *
 * @return none
 */
void display_board(int board[SIZE][SIZE]){
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

/**
 * Function that takes a 2D array and a pointer to a file path,
 * and reads in a text file constructing the sudoku board.
 *
 * @param board - 2D array for the board
 *
 * @param path - a pointer to the file path
 *
 * @return int zero once it's done.
 */
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

/**
 * This function takes the 2D array and a file path
 * and writes the solved board to the output file.
 *
 * @param board - the sudoku board
 *
 * @param path - the pointer to the output file path.
 *
 * @return none
 */
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

/**
 * This function finds the next available cell in the
 * sudoku board and then assigns the row and column
 * pointers to the spot in the 2D array. Returning true
 * or false based on if a spot is located.
 *
 * @param board - the sudoku board.
 *
 * @param row - the row index
 *
 * @param col - the column index
 *
 */
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


/**
 * This function checks the validity of the 
 * current number being placed in the cell.
 *
 * @param board -  the sudoku board
 *
 * @param num - the number to be validated
 *
 * @param row - the row index value
 *
 * @param col - the column index value
 *
 * @returns boolean - true or false based on the check
 */
bool is_valid(int board[SIZE][SIZE], int num, int *row, int *col){

    int row_walk;
    // Check the row and column
    for(row_walk = 0; row_walk < SIZE; row_walk++){
        if(board[*row][row_walk] == num || board[row_walk][*col] == num){
            return false;
        }
    }
    
    // check each sub grid
    int col_row_walk;
    for(row_walk = (*row / 3)*3; row_walk < (*row/3)*3 + 3; row_walk++){
        for(col_row_walk = (*col/3)*3; col_row_walk < (*col/3)*3 + 3; col_row_walk++){
            if(!(row_walk == *row && col_row_walk == *col) && 
                    board[row_walk][col_row_walk] == num){
                return false;
            }
        }
    }
    return true;
}

/**
 * The function for to solve the sudoku board using the
 * backtracking algorithm
 *
 * @param board - the board to solve
 */
int solve(int board[SIZE][SIZE]){
    int row;
    int col;

    // First we need to find the first available cell
    bool located = locate(board, &row, &col);

    if(!located){
        return true;
    } 

    // Now that we have the next open cell
    // we need to fill in the digit 
    for(int i = 1; i < 10; i++){
        //printf("Iteration ===> %d\n", i);
        if(is_valid(board, i, &row, &col) == true){
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

/**
 * The main entry point into the program and begins 
 * running the simulaiton to solve the user specified 
 * sudoku board.
 * 
 * @param argc - the count of the arguments passed
 *
 * @param *argv - the array of arguments passed to the program
 */
int main(int argc,  char *argv[]){
    char *in_file = NULL;
    char *out_file = NULL;
    int board[SIZE][SIZE];
	
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
    read_file(board, in_file);
    display_board(board);
    
    if(solve(board)){
        printf("Solution found!\n");
        display_board(board);    
        write_to_file(board, out_file);
    } else {
        printf("Solution not found! File not written.\n");
    }
    return 0;
}
