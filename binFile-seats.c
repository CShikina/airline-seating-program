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
    bool isOccupied;
}seat[ROW][COL];

typedef struct plane plane;

void readFile(FILE *fp){                            // Reads from file
    for (int i=0; i<ROW; i++){
        fread(seat[i], sizeof(plane), COL, fp);
    }
}
void writeToMemory(FILE *fp){                       // Writes to file (per row)
    fseek(fp, 0, SEEK_SET);
    for (int i=0; i<ROW; i++){
        fwrite(seat[i], sizeof(plane), COL, fp);
    }
}
int charToInt(char n){                              // Converts char to int
    return n - 'A';
}
int isFull(){                                       // Returns 1 if seats are full
    FILE *fp = fopen("plane.txt", "rb");
    readFile(fp);

    for (int i=0; i<ROW; i++){
        for (int j=0; j<COL; j++){
            if (seat[i][j].isOccupied == false) return 0;
        }
    }
    return 1;
}

// Menus
void createFile(){                                  // Creates new file and initializes struct
    system("cls");
    FILE *fp = fopen("plane.txt", "wb");

    // Initialize seats
    for (int i=0; i<ROW; i++){
        for (int j=0; j<COL; j++){
            seat[i][j].row = i + 1;
            seat[i][j].col = 'A' + j;
            seat[i][j].isOccupied = false;
        }
        fwrite(seat[i], sizeof(plane), COL, fp);
    }

    fclose(fp);
    printf("File successfully created. You may proceed to reservation now.");
}
void displaySeat(){                                 // Display seat availability
    FILE *fp = fopen("plane.txt", "rb");
    readFile(fp);

    // Print struct
    system("cls");
    printf("Seat Availability: \n");
    for (int i=0; i<ROW; i++){
        for (int j=0; j<COL; j++){
            if (seat[i][j].isOccupied){
                printf("X\t");
            }
            else {
                printf("%d%c\t", seat[i][j].row, seat[i][j].col);
            }
        }
        printf("\n");
    }
    
    if (isFull() == 1) {printf("\nAirplane is full.");}

    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}
void reserveSeat(){                                 // Assigns seat
    FILE *fp = fopen("plane.txt", "rb+");
    readFile(fp);

    // Reserve seat
    system("cls");
    if (isFull() == 0){
        char colTemp;
        int rowTemp;
        printf("Enter desired seat: ");
        scanf("%d%c", &rowTemp, &colTemp);
        colTemp = toupper(colTemp);

            while (seat[rowTemp-1][charToInt(colTemp)].isOccupied){
                printf("\nSeat is already occupied. Please choose another.\n");
                printf(">> ");
                scanf("%d%c", &rowTemp, &colTemp);
                colTemp = toupper(colTemp);
            }
            
            seat[rowTemp-1][charToInt(colTemp)].isOccupied = true;
            writeToMemory(fp);
            printf("Action completed.");
    }
    else {printf("Airplane is full.");}

    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}
void changeSeat(){                                  // Reassigns seat                        
    FILE *fp = fopen("plane.txt", "rb+");

    readFile(fp);

    system("cls");

    if (isFull() == 0){
        int rowTemp, colTemp2;
        char colTemp;
        printf("Current seat: ");
        scanf("%d%c", &rowTemp, &colTemp);
        colTemp2 = charToInt(toupper(colTemp));

        while (!seat[rowTemp-1][colTemp2].isOccupied){
            printf("Current seat is not yet booked. Please enter correct seat.\n");
            printf(">> ");
            scanf("%d%c", &rowTemp, &colTemp);
            colTemp2 = charToInt(toupper(colTemp));
        }

        seat[rowTemp-1][colTemp2].isOccupied = false;
        printf("Desired seat: ");
        scanf("%d%c", &rowTemp, &colTemp);
        colTemp2 = charToInt(toupper(colTemp));

        while (seat[rowTemp-1][colTemp2].isOccupied){
            printf("Desired seat is occupied. Please choose another.\n");
            printf(">> ");
            scanf("%d%c", &rowTemp, &colTemp);
            colTemp2 = charToInt(toupper(colTemp));
        }

        seat[rowTemp-1][colTemp2].isOccupied = true;
        printf("\nAction completed.");
        }
    else {printf("Airplane is full.");}

    writeToMemory(fp);
    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}
void cancelSeat(){                                  // Frees a seat
    FILE *fp = fopen("plane.txt", "rb+");
    readFile(fp);

    system("cls");
    char colTemp;
    int rowTemp;
    
    printf("Enter which seat to free up: ");
    scanf("%d%c", &rowTemp, &colTemp);
    colTemp = toupper(colTemp);

    if (seat[rowTemp-1][charToInt(colTemp)].isOccupied){
        seat[rowTemp-1][charToInt(colTemp)].isOccupied = false;
        printf("\nAction completed. Seat is now available.");
    }
    else {
        printf("\nNo one has reserved this seat yet.");
    }

    writeToMemory(fp);
    fclose(fp);
    printf("\n\nPress any key to continue...");
    getch();
}

int main(){
    int choice=0;

    FILE *fp = fopen("plane.txt", "rb");
    if (fp == NULL){
        printf("No seat file found. Creating a new file.\n");
        createFile();
    }

    do {
        system("cls");
        if (isFull()) {
            printf("Status: Airplane is full.\n\n");
        }
        else {
            printf("Status: Airplane has available seats.\n\n");
        }
        printf("Choose an operation: \n");
        printf("1. Create new file (Reset).\n");
        printf("2. View seat availability\n");
        printf("3. Reserve a seat\n");
        printf("4. Change seats\n");
        printf("5. Cancel a seat\n");
        printf("6. Exit program\n");
        printf(">> ");
        scanf("%d", &choice);

        switch (choice){
            case 1:
                createFile();
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
                changeSeat();
                break;
            case 5:
                cancelSeat();
                break;
            case 6:
                printf("\nProgram terminated.");
                break;
            default:
                printf("\nInvalid input.");
                printf("\n\nPress any key to continue...");
                getch();
                break;
        }
    }while (choice != 6);
    fclose(fp);
}