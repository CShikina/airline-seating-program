#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<ctype.h>
#include<conio.h>
#define ROW 10
#define COL 4

struct plane {
    int row;
    char col;
    bool occupied;
}seat[ROW][COL];

typedef struct plane plane;

int charToInt(char a){              // Converts char to int
    return a - 'A';
}

void readFile(FILE *fp){            // Reads from file
    char n;
    for(int i=0; i<ROW; i++){
        fscanf(fp, "%d", &seat[i][0].row);
        for (int j=0; j<COL; j++){
            fscanf(fp, " %c", &n);
            if (n == 'X'){
                seat[i][j].occupied = true;
            }
            else {
                seat[i][j].occupied = false;
            }
        }
        fgetc(fp);
    }
}

void writeFile(FILE *fp){           // Prints changes to file
    fseek(fp, 0, SEEK_SET);
    for (int i=0; i<ROW; i++){
        fprintf(fp, "%d\t", i+1);
        for (int j=0; j<COL; j++){
            seat[i][j].row = i + 1;
            seat[i][j].col = j + 'A';
            if (seat[i][j].occupied){
                fprintf(fp, "X\t");
            }
            else {
                fprintf(fp, "%c\t", seat[i][j].col);
            }
        }
        fprintf(fp, "\n");
    }
}

int isFull(){                       // Return 1 if seats are full
    for (int i=0; i<ROW; i++){
        for (int j=0; j<COL; j++){
            if (seat[i][j].occupied == false) return 0;
        }
    }
    return 1;
}

// Program Operations
void createFile(){                  // Creates file and initializes seats
    system("cls");

    FILE *fp = fopen("seats.txt", "w");

    // Initialize and print seats
    for (int i=0; i<ROW; i++){
        fprintf(fp, "%d\t", i+1);
        for (int j=0; j<COL; j++){
            seat[i][j].row = i + 1;
            seat[i][j].col = j + 'A';
            seat[i][j].occupied = false;
            fprintf(fp, "%c\t", seat[i][j].col);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}

void displaySeat(){                 // Displays file
    system("cls");
    FILE *fp = fopen("seats.txt", "r");

    // Prints content of file (per line)
    char text[100];
    while (fgets(text, sizeof(text), fp)){
        printf("%s", text);
    }

    if (isFull()){
        printf("\nAirplane is full.");
    }

    printf("\n\nPress any key to continue...");
    getch();
}

void reserveSeat(){                 // Assigns seat
    system("cls");

    FILE *fp = fopen("seats.txt", "r+");
    readFile(fp);

    if (isFull() == 0){
        int rowTemp, colTemp2;
        char colTemp;
        printf("Enter desired seat: ");
        scanf("%d%c", &rowTemp, &colTemp);
        colTemp2 = charToInt(toupper(colTemp));

        while (seat[rowTemp-1][colTemp2].occupied == true){
            printf("\nSeat %d%c is already occupied. Please choose another: ", rowTemp, colTemp);
            scanf("%d%c", &rowTemp, &colTemp);
            colTemp2 = charToInt(toupper(colTemp));
        }

        seat[rowTemp-1][colTemp2].occupied = true;
        printf("Seat %d%c successfully booked.", rowTemp, colTemp);
    }

    else {printf("Airplane is full.");}

    writeFile(fp);
    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}

void cancelSeat(){                  // Cancels seat
    system("cls");

    FILE *fp = fopen("seats.txt", "r+");
    readFile(fp);

    int rowTemp, colTemp2;
    char colTemp;
    printf("Enter which seat to cancel: ");
    scanf("%d%c", &rowTemp, &colTemp);
    colTemp2 = charToInt(toupper(colTemp));

    if (seat[rowTemp-1][colTemp2].occupied == false){
        printf("\nNo one has reserved this seat yet.");
    }

    else {
        seat[rowTemp-1][colTemp2].occupied = false;
        printf("\nSeat %d%c cancelled.", rowTemp, colTemp);
    }

    writeFile(fp);
    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}

void changeSeat(){                  // Changes seat
    system("cls");

    FILE *fp = fopen("seats.txt", "r+");
    readFile(fp);

    if (isFull() == 0){
        int rowTemp, rowTemp2, colTemp1, colTemp2;
        char colTemp;
        printf("Enter current seat: ");
        scanf("%d%c", &rowTemp, &colTemp);
        colTemp1 = charToInt(toupper(colTemp));

        if(seat[rowTemp-1][colTemp1].occupied){
            printf("Enter desired seat: ");
            scanf("%d%c", &rowTemp2, &colTemp);
            colTemp2 = charToInt(toupper(colTemp));

            while(seat[rowTemp2-1][colTemp2].occupied){
                printf("\nDesired seat is occupied. Please choose another: ");
                scanf("%d%c", &rowTemp2, &colTemp);
                colTemp2 = charToInt(toupper(colTemp));
            }

            seat[rowTemp-1][colTemp1].occupied = false;
            seat[rowTemp2-1][colTemp2].occupied = true;
            printf("Seat %d%c confirmed.", rowTemp2, colTemp);
        }

        else {
            printf("\nNo one has booked %d%c seat yet. Press 1 to continue, 0 to cancel.\n", rowTemp, colTemp);
            printf(">> ");
            int choice;
            scanf("%d", &choice);

            switch (choice){
                case 1:
                    printf("Enter desired seat: ");
                    scanf("%d%c", &rowTemp2, &colTemp);
                    colTemp2 = charToInt(toupper(colTemp));

                    while(seat[rowTemp2-1][colTemp2].occupied){
                        printf("\nDesired seat is occupied. Please choose another: ");
                        scanf("%d%c", &rowTemp2, &colTemp);
                        colTemp2 = charToInt(toupper(colTemp));
                    }

                    seat[rowTemp2-1][colTemp2].occupied = true;
                    printf("Seat %d%c confirmed.", rowTemp2, colTemp);
                    break;

                case 0:
                    break;
            }
        }
    }

    else {printf("Airplane is full.");}

    writeFile(fp);
    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}

int main(){
    int choice;

    FILE *fp = fopen("seats.txt", "r");
    if (fp == NULL){        // If file does not exist, createFile() is called
        createFile();
    }

    do {
        system("cls");
        if (isFull()) {printf("Status: Airplane is full.\n\n");}
        else {printf("Status: Airplane has available seats.\n\n");}
        printf("Please select an operation below.\n");
        printf("1. Create file (Reset)\n");
        printf("2. Display seats\n");
        printf("3. Reserve a seat\n");
        printf("4. Cancel a seat\n");
        printf("5. Change seats\n");
        printf("6. Exit program\n");
        printf(">> ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                createFile();
                printf("File created. You may proceed to reservation now.");
                printf("\n\nPress any key to continue...");
                getch();
                break;
            case 2:
                displaySeat();
                break;
            case 3:
                reserveSeat();
                break;
            case 4:
                cancelSeat();
                break;
            case 5:
                changeSeat();
                break;
            case 6:
                break;
            default:
                printf("\nInvalid input.");
                printf("\n\n Press any key to continue...");
                getch();
        }
    }while (choice != 6);
    printf("\nProgram terminated.");
    fclose(fp);
}