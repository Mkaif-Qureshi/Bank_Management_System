#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include "structures.h"

// ANSI color codes for text color
#define RED_COLOR   "\033[0;31m"
#define GREEN_COLOR "\033[0;32m"
#define YELLOW_COLOR "\033[0;33m"
#define BLUE_COLOR  "\033[0;34m"
#define RESET_COLOR "\033[0m"

// Function prototypes
void adminOperations();
void customerOperations();

int main() {
    char choice;


    while (1) {
        printf("\n%sWhich profile do you want to enter?\n\t%s Enter %s1%s for Admin\n\t Enter %s2%s for Customer\n\t Enter %s0%s to exit the system:",
            BLUE_COLOR, RESET_COLOR, YELLOW_COLOR, RESET_COLOR, YELLOW_COLOR, RESET_COLOR, RED_COLOR, RESET_COLOR);
        fflush(stdin);
        choice = getche();
        printf("\n");
        switch (choice) {
            case '1':
                adminOperations();
                break;
            case '2':
                customerOperations();
                break;
            case '0':
                printf("\n%sExiting the system!%s", RED_COLOR, RESET_COLOR);
                exit(1);
            default:
                printf("%sInvalid choice%s\n Try again!!!", RED_COLOR, RESET_COLOR);
                break;
        }
    }
}
