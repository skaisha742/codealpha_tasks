
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "account.dat"

// Structure for bank account
struct Account {
    int accountNumber;
    char name[50];
    float balance;
};

// Function to create an account
void createAccount() {
    struct Account acc;
    FILE *file;

    file = fopen(FILE_NAME, "ab");

    if (file == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    printf("\n========== CREATE ACCOUNT ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &acc.accountNumber);

    printf("Enter Account Holder Name: ");
    scanf(" %[^\n]", acc.name);

    printf("Enter Initial Deposit: ");
    scanf("%f", &acc.balance);

    if (acc.balance < 0) {
        printf("\nInitial deposit cannot be negative.\n");
        fclose(file);
        return;
    }

    fwrite(&acc, sizeof(struct Account), 1, file);

    fclose(file);

    printf("\nAccount created successfully!\n");
}

// Function to display balance
void balanceEnquiry() {
    struct Account acc;
    FILE *file;

    int accountNumber;
    int found = 0;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\n========== BALANCE ENQUIRY ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    while (fread(&acc, sizeof(struct Account), 1, file)) {

        if (acc.accountNumber == accountNumber) {

            printf("\nAccount Number : %d\n", acc.accountNumber);
            printf("Account Holder : %s\n", acc.name);
            printf("Balance        : %.2f\n", acc.balance);

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\nAccount not found.\n");
    }

    fclose(file);
}

// Function to deposit money
void deposit() {
    struct Account acc;

    FILE *file;

    int accountNumber;
    float amount;
    int found = 0;

    file = fopen(FILE_NAME, "rb+");

    if (file == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\n========== DEPOSIT ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    printf("Enter Deposit Amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\nDeposit amount must be greater than zero.\n");
        fclose(file);
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, file)) {

        if (acc.accountNumber == accountNumber) {

            acc.balance += amount;

            fseek(file, -sizeof(struct Account), SEEK_CUR);

            fwrite(&acc, sizeof(struct Account), 1, file);

            found = 1;

            printf("\nDeposit successful!\n");
            printf("New Balance: %.2f\n", acc.balance);

            break;
        }
    }

    if (!found) {
        printf("\nAccount not found.\n");
    }

    fclose(file);
}

// Function to withdraw money
void withdraw() {
    struct Account acc;

    FILE *file;

    int accountNumber;
    float amount;
    int found = 0;

    file = fopen(FILE_NAME, "rb+");

    if (file == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\n========== WITHDRAW ==========\n");

    printf("Enter Account Number: ");
    scanf("%d", &accountNumber);

    printf("Enter Withdrawal Amount: ");
    scanf("%f", &amount);

    if (amount <= 0) {
        printf("\nWithdrawal amount must be greater than zero.\n");
        fclose(file);
        return;
    }

    while (fread(&acc, sizeof(struct Account), 1, file)) {

        if (acc.accountNumber == accountNumber) {

            found = 1;

            if (amount > acc.balance) {

                printf("\nInsufficient balance!\n");

            } else {

                acc.balance -= amount;

                fseek(file, -sizeof(struct Account), SEEK_CUR);

                fwrite(&acc, sizeof(struct Account), 1, file);

                printf("\nWithdrawal successful!\n");
                printf("Remaining Balance: %.2f\n", acc.balance);
            }

            break;
        }
    }

    if (!found) {
        printf("\nAccount not found.\n");
    }

    fclose(file);
}

// Function to display all accounts
void displayAccounts() {
    struct Account acc;

    FILE *file;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo accounts found.\n");
        return;
    }

    printf("\n========== ALL ACCOUNTS ==========\n");

    printf("%-15s %-25s %-15s\n",
           "Account No.", "Name", "Balance");

    printf("----------------------------------------------------\n");

    while (fread(&acc, sizeof(struct Account), 1, file)) {

        printf("%-15d %-25s %.2f\n",
               acc.accountNumber,
               acc.name,
               acc.balance);
    }

    fclose(file);
}

// Main function
int main() {

    int choice;

    printf("============================================\n");
    printf("           BANKING MANAGEMENT SYSTEM\n");
    printf("============================================\n");

    do {

        printf("\n\n============== MENU ==============\n");

        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Balance Enquiry\n");
        printf("5. Display All Accounts\n");
        printf("6. Exit\n");

        printf("==================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                createAccount();
                break;

            case 2:
                deposit();
                break;

            case 3:
                withdraw();
                break;

            case 4:
                balanceEnquiry();
                break;

            case 5:
                displayAccounts();
                break;

            case 6:
                printf("\nThank you for using Banking Management System!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 6);

    return 0;
}
