#include <stdio.h>
#include "structures.h" // Include your structures header file here

int main() {
    FILE *fc;
    struct customer cust;

    // Open the file in binary write mode
    fc = fopen("CUSTOMER.DAT", "wb");
    if (fc == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    // Sample data for five customers
    struct customer sampleCustomers[5] = {
        {1001, "Alice", 1500.0, "pass123"},
        {1002, "Bob", 2500.0, "pass456"},
        {1003, "Charlie", 1800.0, "pass789"},
        {1004, "David", 3000.0, "passabc"},
        {1005, "Eva", 2000.0, "passdef"}
    };

    // Writing five customers to the file
    for (int i = 0; i < 5; i++) {
        fwrite(&sampleCustomers[i], sizeof(struct customer), 1, fc);
    }

    fclose(fc); // Close the file after writing

    printf("Sample customers inserted into CUSTOMER.DAT successfully.\n");
    return 0;
}
