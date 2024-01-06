#include<stdio.h>
#include<string.h>
#include<conio.h>
struct admin {
    long int adminId;
    char password[15];
};

int main() {
    struct admin a;
    FILE *f;
    char ch;

    f = fopen("ADMIN.DAT", "wb");

    if(f == NULL) {
        printf("Unable to open\n");
    } else {
        printf("\nThis will clear the ADMIN.DAT file and create a new admin!!!");
        printf("\nDo you want to continue? (Y/N): ");
        ch = getche();

        if(ch == 'Y' || ch == 'y') {
            printf("\nEnter Admin Id:");
            scanf("%ld", &a.adminId);
            printf("\nEnter password: ");
            getchar();
            fgets(a.password, sizeof(a.password), stdin);
            if(a.password[strlen(a.password) - 1] == '\n') {
                a.password[strlen(a.password) - 1] = '\0';
            }
            fwrite(&a, sizeof(a), 1, f);
            printf("\nSuccessfully created Admin:");
            printf("\nNote the Details\n\tAdminId:%ld\n\tPassword:%s", a.adminId, a.password);
        }
        else{
            printf("\nAs you wish!");
        }
        fclose(f); // Close the file after writing


        // f = fopen("ADMIN.DAT", "rb");
        // while (fread(&a, sizeof(a), 1, f))
        // {
        //     printf("\n%ld : %s", a.adminId, a.password);
        // }
        
    }
    return 0;
}
