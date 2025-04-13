#ifndef BANKING_SYSTEM_H
#define BANKING_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_ACCOUNTS 100
#define MAX_TRANSACTIONS 5
#define MAX_NAME_LENGTH 100
#define MAX_CONTACT_LENGTH 15
#define MAX_TRANSACTION_HISTORY 5

typedef enum {
    DEPOSIT,
    WITHDRAW
} transaction_type;

typedef struct {
    uint32_t transaction_id;
    transaction_type type;
    double amount;
    char date[20];  // Simple string to store date
} transaction;

typedef struct account {
    uint32_t account_number;
    char account_name[MAX_NAME_LENGTH];
    double account_balance;
    uint32_t account_transactions_count;
    transaction transactions[MAX_TRANSACTION_HISTORY];
    char contact_number[MAX_CONTACT_LENGTH];
    struct account *next;
} account;

// Function declarations
void Create_account(void);
void Withdraw(void);
void Deposit(void);
void Transfer(void);
void Balance_enquiry(void);
void Transaction_history(void);
void Save_to_file(void);
void Load_from_file(void);
void Display_all_accounts(void);
void Find_account(void);
void Quit(void);
void Display_menu(void);

#endif /* BANKING_SYSTEM_H */
