#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "structures.h"


// ANSI color codes for text color
#define RED_COLOR     "\033[0;31m"
#define GREEN_COLOR   "\033[0;32m"
#define YELLOW_COLOR  "\033[0;33m"
#define BLUE_COLOR    "\033[0;34m"
#define CYAN_COLOR    "\033[0;36m"
#define MAGENTA_COLOR "\033[0;35m"
#define RESET_COLOR   "\033[0m"

int isNumeric(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return 0; // Not a number
        }
        str++;
    }
    return 1; // Numeric
}

void customerOperations() {
    FILE *fc;

    struct customer c;

    char choice, passInput[15];
    long int input;
    int found = 0;
    fc = fopen("CUSTOMER.DAT", "rb+");

    printf("\n%s---Welcome to Customer Login---%s\n", BLUE_COLOR, RESET_COLOR);
    printf("\nEnter your Account no:");
    fflush(stdin);
    scanf("%ld", &input);

    while (fread(&c, sizeof(c), 1, fc) == 1)
    {
        if(input == c.accountNumber){
            printf("\nEnter password: ");
            fflush(stdin);
            scanf("%s", passInput);
            
            if(strcmp(passInput, c.password) == 0){
                printf("\n%sSuccessfully Logged in!%s\n", GREEN_COLOR, RESET_COLOR);
                while (1)
                {
                    printf("\n\t1. Check Account\n\t2. Update details\n\t3. Withdraw\n\t4. Deposit\n\t0. Log out\n");
                    printf("\n\tEnter choice: ");
                    fflush(stdin);
                    choice = getche();
                    printf("\n");
                    switch (choice)
                    {
                        case '1':
                            printf("\n%sAccount Details:%s", MAGENTA_COLOR, RESET_COLOR);
                            printf("\nAccount Number: %ld", c.accountNumber);
                            printf("\nName: %s", c.name);
                            printf("\nBalance: %.2f", c.balance);
                            printf("\n");
                            break;
                        
                        case '2':
                            printf("\n%sUpdating Customer Details%s\n", CYAN_COLOR, RESET_COLOR);
                            printf("Enter new name: ");
                            scanf("%s", c.name);
                            printf("Enter new password: ");
                            scanf("%s", c.password);

                            fseek(fc, -sizeof(c), SEEK_CUR);
                            fwrite(&c, sizeof(c), 1, fc);
                            printf("\n%sCustomer details updated successfully%s\n", GREEN_COLOR, RESET_COLOR);
                            break;

                        case '3':
                            printf("\n%sWithdraw from Account%s\n", CYAN_COLOR, RESET_COLOR);
                            char withdrawAmountStr[20];
                            float withdrawAmount;

                            printf("Enter amount to withdraw: ");
                            scanf("%s", withdrawAmountStr);

                            if (!isNumeric(withdrawAmountStr)) {
                                printf("\n%sInvalid input for withdrawal%s\n", RED_COLOR, RESET_COLOR);
                                break;
                            }

                            withdrawAmount = atof(withdrawAmountStr);

                            if (withdrawAmount > c.balance || withdrawAmount <= 0) {
                                printf("\n%sInvalid amount or insufficient balance%s\n", RED_COLOR, RESET_COLOR);
                            } else {
                                c.balance -= withdrawAmount;
                                fseek(fc, -sizeof(c), SEEK_CUR);
                                fwrite(&c, sizeof(c), 1, fc);
                                printf("\n%sWithdrawal successful%s\n", GREEN_COLOR, RESET_COLOR);
                            }
                            break;

                        case '4':
                            printf("\n%sDeposit to Account%s\n", CYAN_COLOR, RESET_COLOR);
                            char depositAmountStr[20];
                            float depositAmount;

                            printf("Enter amount to deposit: ");
                            scanf("%s", depositAmountStr);

                            if (!isNumeric(depositAmountStr)) {
                                printf("\n%sInvalid input for deposit%s\n", RED_COLOR, RESET_COLOR);
                                break;
                            }

                            depositAmount = atof(depositAmountStr);

                            if (depositAmount <= 0) {
                                printf("\n%sInvalid deposit amount%s\n", RED_COLOR, RESET_COLOR);
                            } else {
                                c.balance += depositAmount;
                                fseek(fc, -sizeof(c), SEEK_CUR);
                                fwrite(&c, sizeof(c), 1, fc);
                                printf("\n%sDeposit successful%s\n", GREEN_COLOR, RESET_COLOR);
                            }
                            break;

                        case '0':
                            printf("\n%sLogged out.%s\n", RED_COLOR, RESET_COLOR);
                            fclose(fc);
                            return;

                        default:
                            printf("\n%sInvalid choice!%s\n", RED_COLOR, RESET_COLOR);
                            break;
                    }
                }
            }
        }
    }
}
