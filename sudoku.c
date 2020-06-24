#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LINE 11
#define SIZE 9

typedef struct {
    int solved[SIZE][SIZE];
} matrix;

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

int locate(int board[SIZE][SIZE], int *row, int *col){
    for(int i = 0; i < SIZE; i++){
        for(int j = 0; j < SIZE; j++){
            if(board[i][j] == 0){
                row = i;
                col = j;
                return 0;
            }
        }
    }
    return -1;
}

int solve(int board[SIZE][SIZE]){
    int row;
    int col;

    // First we need to find the first available cell
    int located = locate(board, &row, &col);

    if(located == -1){
        return true;
    } else {


    }
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
    solve(board);
    
    // write to file 
    return 0;
}
