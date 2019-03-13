#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <dos.h>
#include <windows.h>


#define true  1;
#define false 0;
#define FREE_MOVES 3;


COORD coord = {0, 0}; // this is global variable
int row, col;      // this is global variable
int num;            // this is global variable
int **puzzle;       // this is global variable

/*function to make gotoxy work*/
void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

/*function to print the puzzle */
void disp(int **arrays, int row, int col) {
    int i, j;
    num = row * col;
// int charpos=32;
//gotoxy(15,5);
    system("COLOR 7c");
    printf("\n************PUZZLE GAME ******************\n");
    printf("\n");
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (arrays[i][j] == 0) {
                printf(" ");
            } else {
                printf("%d", arrays[i][j]);
            }

            printf("\t");
        }

        puts("");
        printf("\n");
    }
    printf("************PUZZLE GAME ******************\n");
}

/*function to check if the arrange puzzle is equal with the desire puzzle*/
int Isdone(int **puzzle1, int **puzzle2) {
    int lala = 0;
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (puzzle1[i][j] == puzzle2[i][j]) {
                lala++;
            }
        }
    }
    if (lala == num) { return 1; }
    else return 0;
}

/*function to see read the element in the puzzle to make the value not to repeat again*/
int inside(int **arrays, int row, int col, int tmp) {
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (arrays[i][j] == tmp)
                return 1;
        }
    }
    return 0;
}

/*function to swap horizontal left*/
void swapleft(int **array, int row, int col) {
    int b;
    int i = 0, j = 0;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++) {
            if (j != 0 && i != row)
                if (array[i][j] == 0) {
                    b = array[i][j];
                    array[i][j] = array[i][j - 1];
                    array[i][j - 1] = b;
                };
        }
};


/*function to swap vertical down*/
void swapdown(int **arra, int row, int col) {
    int tp = 0;
    int i = 0, j = 0;
    for (i = 0; i < row; i++)
        for (j = 0; j < col; j++) {
            if (i != 0 && i != col)
                if (arra[i][j] == 0) {
                    tp = arra[i][j];
                    arra[i][j] = arra[i - 1][j];
                    arra[i - 1][j] = tp;
                };

        }

}

/*function to swap horizontal right*/
void swapright(int **arry, int row, int col) {
    int tr;
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (arry[i][j] == 0) {
                if (j == (col - 1)) {
                    printf("not possible move");
                } else {
                    tr = arry[i][j];
                    arry[i][j] = arry[i][j + 1];
                    arry[i][j + 1] = tr;
                    goto endlo;
                }
            }
        }
    }
    endlo:
    printf(".");
}

/*function to swap vertical up*/
void swapup(int **arr, int row, int col) {
    int c = 0;
    int i = 0, j = 0;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            if (arr[i][j] == 0) {
                if (i == (row - 1)) {
                    printf("not possible");
                } else {
                    c = arr[i][j];
                    arr[i][j] = arr[i + 1][j];
                    arr[i + 1][j] = c;
                    goto endloop;
                }
            }
        }
    }
    endloop:
    printf(".");

}

void swapValue(int prevRow, int prevCol) {
    int prevValue, curValue;

    /* getCurrent Swap Value */
    prevValue = puzzle[prevRow][prevCol];
    curValue = puzzle[row][col];

    /* Swap it, Simply !! */
    puzzle[prevRow][prevCol] = curValue;
    puzzle[row][col] = prevValue;

    /* Draw Puzzle Box */
    // disp(puzzle,row,col);
}

struct record {
    char name[30];
    int score;
    struct record *next;
};

void Add(struct record **head, char *n, int s) {
    struct record *tmp;
    tmp = (struct record *) malloc(sizeof(struct record));
    tmp->score = s;
    strcpy(tmp->name, n);

    tmp->next = *head;
    *head = tmp;

}


void print_list(struct record *head) {
    struct record *tmp = head;

    while (tmp != NULL) {
        printf("%s  %d\n", tmp->name, tmp->score);
        tmp = tmp->next;
    }
}


void main() {

    char decid;
    do {
        system("cls");
        char arrowKey;
        int k = 0, temp = 0;
        srand(time(NULL));
//int x=3,y=3;
        int **puzzle;
        int **puzzlechecher;     /*duplicate of a puzzle in order */
        int chkinner = 1;
        int i = 0, j = 0, num = 0;
        char name[30];
        FILE *fp1;
        struct record *head;
        int a = 99998989;
        char b[30];
        head = NULL;
        int ret = 0;

        printf("************PUZZLE GAME ******************\n");
        printf("enter your name :");
        gets(name);

        do {
            printf("\nthe row and col must be equal and not less than 3 or greater than 6\n");
            printf("Enter the order of the puzzle : ");
            system("COLOR fc");

            scanf("%d %d", &row, &col); /*enter the  order of  puzzle*/
            system("cls");
        } while ((row != col) || (col < 3) || (col > 6));

/*Allocating a 2D array */
        puzzle = (int **) malloc(row * sizeof(int *));
        for (i = 0; i < row; i++) {
            puzzle[i] = (int *) malloc(col * sizeof(int *));
        };

/*setting up a 2D array for the duplicate puzzle*/
        puzzlechecher = (int **) malloc(row * sizeof(int *));
        for (i = 0; i < row; i++) {
            puzzlechecher[i] = (int *) malloc(col * sizeof(int *));
        };

        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                puzzlechecher[i][j] = chkinner;
                chkinner++;
                puzzlechecher[row - 1][col - 1] = 00;
            }
        }

        num = row * col;

        for (i = 0; i < row; i++)
            for (j = 0; j < col; j++)
                puzzle[i][j] = 0;
/*Loop to allocate random elements to 2D array */
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                while (puzzle[i][j] == 0)
                    for (k = 0; k < 10; k++) {
                        temp = rand() % num + 1;
                        int check = inside(puzzle, row, col, temp);
                        if (check != 1) {                 /*not to repeat a number twice*/
                            puzzle[i][j] = temp;
                        }
                    }
            }
        }

/*loop to set the last element of the puzzle to 0*/
        for (i = 0; i < row; i++)
            for (j = 0; j < col; j++) {
                if (puzzle[i][j] == num) {
                    puzzle[i][j] = 00;
                } else;
            }

        int moves;
        moves = 0;
        system("cls");
        printf("************PUZZLE GAME ******************\n");
        printf("press 'a' to move left 'd' to move right 'w' to move up 'x' to move down and 'n' to exit the game ");
        disp(puzzle, row, col);

        while ((arrowKey = getch()) != 'n') {


            switch (arrowKey) {
                case 'a':
                    moves++;
                    swapleft(puzzle, row, col);
                    system("cls");
                    disp(puzzle, row, col);
                    if (Isdone(puzzle, puzzlechecher) == 1) {
                        system("cls");
                        printf("CONGRATULATION YOU WON");
                        goto last;
                    } else //printf("you are not done");
                        break;
                case 'w':
                    moves++;
                    swapdown(puzzle, row, col);
                    system("cls");
                    disp(puzzle, row, col);
                    if (Isdone(puzzle, puzzlechecher) == 1) {
                        system("cls");
                        printf("CONGRATULATION YOU WON");
                        goto last;
                    } else //printf("you are not done");
                        break;
                case 'd':
                    moves++;
                    swapright(puzzle, row, col);
                    system("cls");
                    disp(puzzle, row, col);
                    if (Isdone(puzzle, puzzlechecher) == 1) {
                        system("cls");
                        printf("CONGRATULATION YOU WON");
                        goto last;
                    } else //printf("you are not done");
                        break;
                case 'x':
                    moves++;
                    swapup(puzzle, row, col);
                    system("cls");
                    disp(puzzle, row, col);
                    if (Isdone(puzzle, puzzlechecher) == 1) {
                        system("cls");
                        printf("CONGRATULATION YOU WON");
                        goto last;
                    } else //printf("you are not done");
                        break;
                default:
                    if (Isdone(puzzle, puzzlechecher) == 1) {
                        printf("CONGRATULATION YOU WON\n");
                        goto last;
                    } else {//printf("you are not done");
                        system("cls");
                        disp(puzzle, row, col);

                    }
                    break;

            }

        }

        last:


        switch (row) {
            case 3:
                fp1 = fopen("test.txt", "a");
                fclose(fp1);
                break;
            case 4:
                fp1 = fopen("test4.txt", "a");
                fclose(fp1);
                break;
            case 5:
                fp1 = fopen("test5.txt", "a");
                fclose(fp1);
                break;
            case 6:
                fp1 = fopen("test6.txt", "a");
                fclose(fp1);
                break;
            default:
                break;
        }


        switch (row) {

            case 3:
                fp1 = fopen("test.txt", "r");
                if (!fp1) {
                    printf("file not gotten");
                }
                while (1) {
                    if ((ret = fscanf(fp1, "%s %d", b, &a)) == EOF)
                        break;
                    Add(&head, b, a);
                }
                fclose(fp1);
                break;
            case 4:
                fp1 = fopen("test4.txt", "r");

                if (!fp1) { printf("file not gotten"); }
                while (1) {
                    if ((ret = fscanf(fp1, "%s %d", b, &a)) == EOF)
                        break;
                    Add(&head, b, a);
                }
                fclose(fp1);
                break;
            case 5:
                fp1 = fopen("test5.txt", "r");
                if (!fp1) { printf("file not gotten"); }
                while (1) {
                    if ((ret = fscanf(fp1, "%s %d", b, &a)) == EOF)
                        break;
                    Add(&head, b, a);
                }
                fclose(fp1);
                break;

            case 6:
                fp1 = fopen("test6.txt", "r");
                if (!fp1) { printf("file not gotten"); }
                while (1) {
                    if ((ret = fscanf(fp1, "%s %d", b, &a)) == EOF)
                        break;
                    Add(&head, b, a);
                }
                fclose(fp1);
                break;

            default :
                break;
        }

        if (Isdone(puzzle, puzzlechecher) == 1) {
            printf("\nyou made %d moves\n", moves);
            goto cont;

        }


//printf("%d\n",a);

        printf("You exit from game:LAZY YOU\n");

        cont:

        if ((Isdone(puzzle, puzzlechecher) == 1) && (moves < a)) {
            printf("a new record for dimension %d is reach \n ", row);
            FILE *fp;


            switch (col) {
                case 3:
                    fp = fopen("test.txt", "a");
                    break;
                case 4:
                    fp = fopen("test4.txt", "a");
                    break;
                case 5:
                    fp = fopen("test5.txt", "a");
                    break;
                case 6:
                    fp = fopen("test6.txt", "a");
                    break;
                default :
                    break;

            }

            fprintf(fp, "%s %d\n", name, moves);

            fclose(fp);
            print_list(head);
            printf("\n%s %d", name, moves);
        } else;

        printf("Thanks for playing my game\n");

        print_list(head);
        printf("****press y to play again and anykey to exit****");
        decid = getch();
    } while (decid == 'y');
    return 0;
}
