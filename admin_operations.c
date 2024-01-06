#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#include "structures.h"


// ANSI color codes for text color
#define RED_COLOR     "\033[0;31m"
#define GREEN_COLOR   "\033[0;32m"
#define YELLOW_COLOR  "\033[0;33m"
#define BLUE_COLOR    "\033[0;34m"
#define CYAN_COLOR    "\033[0;36m"
#define MAGENTA_COLOR "\033[0;35m"
#define RESET_COLOR   "\033[0m"



void adminOperations() {
    FILE *fa, *ft, *fc;

    struct admin a;
    struct customer c;

    char choice, passInput[15];
    long int input;
    int found = 0;

    fa = fopen("ADMIN.DAT", "rb+");
    fc = fopen("CUSTOMER.DAT", "rb+");

    if (fa != NULL && fc != NULL) {
        printf("\n%s---Welcome to Admin Login---%s\n", BLUE_COLOR, RESET_COLOR);
        printf("\nEnter Admin ID:");
        fflush(stdin);
        scanf("%ld", &input);

        while (fread(&a, sizeof(a), 1, fa) == 1) {
            if (a.adminId == input) {
                found = 1;
                printf("\nEnter password for %ld admin: ", a.adminId);
                scanf("%s", passInput);

                if (strcmp(a.password, passInput) == 0) {
                    printf("\n%sSuccessfully Logged in!%s\n", GREEN_COLOR, RESET_COLOR);
                    while (1) {
                        printf("\n\t1. Admin List\n\t2. Create admin\n\t3. Update password\n\t4. Delete admin\n\t5. Customer List\n\t6. Add customer\n\t7. Modify customer\n\t8. Delete Customer\n\t9. Dashboard\n\t0. Log out\n");
                        printf("\n\tEnter choice: ");
                        fflush(stdin);
                        choice = getche();
                        printf("\n");
                        switch (choice) {
                            case '1':
                                rewind(fa);
                                printf("\n%sADMIN ID   | PASSWORD\n", MAGENTA_COLOR);
                                printf("=====================");
                                while (fread(&a, sizeof(a), 1, fa) == 1) {
                                    printf("\n%-10ld | %-s", a.adminId, a.password);
                                }
                                printf("\n%s", RESET_COLOR);
                                fseek(fa, 0, SEEK_END); 
                            break;
                            case '2':
                                found = 0;
                                fseek(fa, 0, SEEK_SET);
                                printf("\nEnter Admin Id(Number only):");
                                scanf("%ld", &input);

                                while (fread(&a, sizeof(a), 1, fa) == 1) {
                                    if (a.adminId == input) {
                                        printf("\n%sAdmin Id already present!%s", RED_COLOR, RESET_COLOR);
                                        found = 1;
                                        break;
                                    }
                                }
                                
                                if (found == 0) {
                                    fseek(fa, 0, SEEK_END);
                                    a.adminId = input;
                                    printf("\nEnter password: ");
                                    scanf("%s", a.password);
                                    fwrite(&a, sizeof(a), 1, fa);
                                    printf("\n%sSuccessfully created Admin!\nNote the Details\n\tAdminId:%ld\n\tPassword:%s%s\n", GREEN_COLOR, a.adminId, a.password, RESET_COLOR);
                                }
                            break;

                            case '3':
                                // Functionality for Update password
                                rewind(fa);
                                printf("\nEnter Admin Id to modify: ");
                                scanf("%ld", &input);
                                while (fread(&a, sizeof(a), 1, fa) == 1) {
                                    if (a.adminId == input) {
                                        printf("Enter new password: ");
                                        scanf("%s", a.password);
                                        fseek(fa, -sizeof(a), SEEK_CUR);
                                        fwrite(&a, sizeof(a), 1, fa);
                                        printf("%sSuccessfully updated password for admin %ld%s\n", GREEN_COLOR, a.adminId, RESET_COLOR);
                                        break;
                                    }
                                }
                                break;
                                
                            case '4':
                                rewind(fa);
                                printf("\nEnter Admin Id to delete: ");
                                scanf("%ld", &input);

                                ft = fopen("TEMP.DAT", "wb+");
                                if (ft == NULL) {
                                    printf("%sError creating temporary file!%s\n", RED_COLOR, RESET_COLOR);
                                    break;
                                }

                                found = 0;
                                while (fread(&a, sizeof(a), 1, fa) == 1) {
                                    if (a.adminId != input) {
                                        fwrite(&a, sizeof(a), 1, ft);
                                    } else {
                                        found = 1;
                                    }
                                }

                                fclose(ft);
                                fclose(fa);  

                                if (found) {
                                    remove("ADMIN.DAT");
                                    rename("TEMP.DAT", "ADMIN.DAT");
                                    fa = fopen("ADMIN.DAT", "rb+");
                                    printf("%sAdmin deleted successfully!%s\n", GREEN_COLOR, RESET_COLOR);
                                } else {
                                    printf("Admin not found!\n");
                                    remove("TEMP.DAT");  
                                }
                                break;

                            case '5':
                                rewind(fc);
                                printf("\n%sACCOUNT NO.  | NAME                       | BALANCE | PASSWORD\n", MAGENTA_COLOR);
                                printf("==============================================================\n");
                                while (fread(&c, sizeof(c), 1, fc) == 1) {
                                    printf("%-12ld | %-26s | %-7.2f | %-s\n", c.accountNumber, c.name, c.balance, c.password);
                                }
                                printf("\n%s", RESET_COLOR);
                                fseek(fc, 0, SEEK_END); 
                                break;
                            case '6':
                                rewind(fc);
                                printf("\nEnter a new Account number: ");
                                fflush(stdin);
                                scanf("%ld", &input);
                                found = 0;
                                while (fread(&c, sizeof(c), 1, fc) == 1) {
                                    if (c.accountNumber == input) {
                                        printf("\n%sAccount number already exists!%s\n", RED_COLOR, RESET_COLOR);
                                        found = 1;
                                        break;
                                    }
                                }
                                if (found == 0) {
                                    fseek(fc, 0, SEEK_END);
                                    c.accountNumber = input;
                                    printf("\nEnter name and password for account %ld: ", input);
                                    scanf("%s %s", c.name, c.password);
                                    c.balance = 1000.0;
                                    fwrite(&c, sizeof(c), 1, fc);
                                    printf("%sCustomer added successfully%s\n", GREEN_COLOR, RESET_COLOR);
                                }
                                break;


                            case '7':
                                // Functionality for Modify customer
                                rewind(fc);
                                printf("\nEnter Account Number to modify: ");
                                scanf("%ld", &input);
                                found = 0;
                                while (fread(&c, sizeof(c), 1, fc) == 1) {
                                    if (c.accountNumber == input) {
                                        printf("\nEnter new name and password for account %ld: ", input);
                                        scanf("%s %s", c.name, c.password);
                                        fseek(fc, -sizeof(c), SEEK_CUR);
                                        fwrite(&c, sizeof(c), 1, fc);
                                        printf("%sSuccessfully modified customer details for account %ld%s\n", GREEN_COLOR, input, RESET_COLOR);
                                        found = 1;
                                        break;
                                    }
                                }
                                if (!found) {
                                    printf("\n%sCustomer with entered account number not found%s\n", RED_COLOR, RESET_COLOR);
                                }
                                break;

                            case '8':
                                // Functionality for Delete Customer
                                rewind(fc);
                                printf("\nEnter Account Number to delete: ");
                                scanf("%ld", &input);

                                ft = fopen("TEMP_CUSTOMER.DAT", "wb+");
                                if (ft == NULL) {
                                    printf("%sError creating temporary file!%s\n", RED_COLOR, RESET_COLOR);
                                    break;
                                }

                                found = 0;
                                while (fread(&c, sizeof(c), 1, fc) == 1) {
                                    if (c.accountNumber != input) {
                                        fwrite(&c, sizeof(c), 1, ft);
                                    } else {
                                        found = 1;
                                    }
                                }

                                fclose(ft);
                                fclose(fc);

                                if (found) {
                                    remove("CUSTOMER.DAT");
                                    rename("TEMP_CUSTOMER.DAT", "CUSTOMER.DAT");
                                    fc = fopen("CUSTOMER.DAT", "rb+");
                                    printf("%sCustomer deleted successfully!%s\n", GREEN_COLOR, RESET_COLOR);
                                } else {
                                    printf("\n%sCustomer with account number %ld not found%s\n", RED_COLOR, input, RESET_COLOR);
                                    remove("TEMP_CUSTOMER.DAT");  
                                }
                                break;
                            
                            case '9':
                                printf("\n%s---Dashboard---%s\n", CYAN_COLOR, RESET_COLOR);
                                int adminCount = 0, customerCount = 0;

                                rewind(fa);
                                while (fread(&a, sizeof(a), 1, fa) == 1) {
                                    adminCount++;
                                }

                                rewind(fc);
                                while (fread(&c, sizeof(c), 1, fc) == 1) {
                                    customerCount++;
                                }

                                printf("Total Admins: %d\n", adminCount);
                                printf("Total Customers: %d\n", customerCount);

                                // Average Balance of Customers
                                rewind(fc);
                                double totalBalance = 0.0;
                                int totalCustomers = 0;

                                while (fread(&c, sizeof(c), 1, fc) == 1) {
                                    totalBalance += c.balance;
                                    totalCustomers++;
                                }

                                if (totalCustomers > 0) {
                                    double averageBalance = totalBalance / totalCustomers;
                                    printf("Average Customer Balance: %.2f\n", averageBalance);
                                } else {
                                    printf("No customers found!\n");
                                }

                                // Admins with Weak Passwords
                                rewind(fa);
                                int weakPasswordCount = 0;
                                while (fread(&a, sizeof(a), 1, fa) == 1) {
                                    if (strlen(a.password) < 6) {
                                        weakPasswordCount++;
                                    }
                                }

                                printf("Admins with Weak Passwords: %d\n", weakPasswordCount);

                                // Customers with Large Balances
                                rewind(fc);
                                double largeBalanceThreshold = 10000.0;
                                int largeBalanceCustomers = 0;

                                while (fread(&c, sizeof(c), 1, fc) == 1) {
                                    if (c.balance > largeBalanceThreshold) {
                                        largeBalanceCustomers++;
                                    }
                                }

                                printf("Customers with Large Balances (> $%.2f): %d\n", largeBalanceThreshold, largeBalanceCustomers);
                                break;


                            case '0':
                                printf("\n%sLogged out.%s\n", RED_COLOR, RESET_COLOR);
                                fclose(fa);
                                return;

                            default:
                                printf("\n%sInvalid choice!%s\n", RED_COLOR, RESET_COLOR);
                                break;
                        }
                    }
                } else {
                    printf("\n%sWrong password!%s\n", RED_COLOR, RESET_COLOR);
                }
            }
        }
        if (!found) {
            printf("\n%sNo Admin found%s\n", RED_COLOR, RESET_COLOR);
        }
        fclose(fa);
    } else {
        printf("%sFile could not be opened.%s\n", RED_COLOR, RESET_COLOR);
    }
}
