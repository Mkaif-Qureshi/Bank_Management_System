// structures.h

#ifndef STRUCTURES_H
#define STRUCTURES_H

struct customer {
    long int accountNumber;
    char name[30];
    float balance;
    char password[15];
};

struct admin {
    long int adminId;
    char password[15];
};

#endif
