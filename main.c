#include "banking_system.h"

account *head = NULL; // To store the head of the linked list

// Function to create a new account
void Create_account(void) {
    account *new_account = (account *)malloc(sizeof(account));
    if (new_account == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    printf("Enter Account Number: ");
    scanf("%u", &new_account->account_number);

    printf("Enter Account Name: ");
    getchar();  // To clear the buffer
    fgets(new_account->account_name, MAX_NAME_LENGTH, stdin);
    new_account->account_name[strcspn(new_account->account_name, "\n")] = 0; // Remove trailing newline

    new_account->account_balance = 0.0;
    new_account->account_transactions_count = 0;

    printf("Enter Contact Number: ");
    fgets(new_account->contact_number, MAX_CONTACT_LENGTH, stdin);
    new_account->contact_number[strcspn(new_account->contact_number, "\n")] = 0;

    new_account->next = head;
    head = new_account;

    printf("Account Created Successfully.\n");
}

// Function to withdraw money
void Withdraw(void) {
    uint32_t account_number;
    double amount;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp != NULL) {
        if (temp->account_number == account_number) {
            printf("Enter amount to withdraw: ");
            scanf("%lf", &amount);

            if (amount > temp->account_balance) {
                printf("Insufficient funds.\n");
                return;
            }

            temp->account_balance -= amount;
            transaction new_transaction = {temp->account_transactions_count + 1, WITHDRAW, amount, "2025-03-20"}; // Simplified date
            temp->transactions[temp->account_transactions_count] = new_transaction;
            temp->account_transactions_count++;

            printf("Withdrawal successful.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Function to deposit money
void Deposit(void) {
    uint32_t account_number;
    double amount;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp != NULL) {
        if (temp->account_number == account_number) {
            printf("Enter amount to deposit: ");
            scanf("%lf", &amount);

            temp->account_balance += amount;
            transaction new_transaction = {temp->account_transactions_count + 1, DEPOSIT, amount, "2025-03-20"};
            temp->transactions[temp->account_transactions_count] = new_transaction;
            temp->account_transactions_count++;

            printf("Deposit successful.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Function to transfer money
void Transfer(void) {
    uint32_t from_account_number, to_account_number;
    double amount;
    printf("Enter From Account Number: ");
    scanf("%u", &from_account_number);
    printf("Enter To Account Number: ");
    scanf("%u", &to_account_number);

    account *from_account = head;
    account *to_account = head;

    while (from_account != NULL) {
        if (from_account->account_number == from_account_number) {
            break;
        }
        from_account = from_account->next;
    }

    while (to_account != NULL) {
        if (to_account->account_number == to_account_number) {
            break;
        }
        to_account = to_account->next;
    }

    if (from_account == NULL || to_account == NULL) {
        printf("One or both accounts not found.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);

    if (amount > from_account->account_balance) {
        printf("Insufficient funds.\n");
        return;
    }

    from_account->account_balance -= amount;
    to_account->account_balance += amount;

    transaction from_transaction = {from_account->account_transactions_count + 1, WITHDRAW, amount, "2025-03-20"};
    from_account->transactions[from_account->account_transactions_count] = from_transaction;
    from_account->account_transactions_count++;

    transaction to_transaction = {to_account->account_transactions_count + 1, DEPOSIT, amount, "2025-03-20"};
    to_account->transactions[to_account->account_transactions_count] = to_transaction;
    to_account->account_transactions_count++;

    printf("Transfer successful.\n");
}

// Function for balance enquiry
void Balance_enquiry(void) {
    uint32_t account_number;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp != NULL) {
        if (temp->account_number == account_number) {
            printf("Account Balance: %.2f\n", temp->account_balance);
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Function to show transaction history (last 5 transactions)
void Transaction_history(void) {
    uint32_t account_number;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp != NULL) {
        if (temp->account_number == account_number) {
            printf("Last 5 Transactions for Account %u:\n", account_number);
            for (int i = temp->account_transactions_count - 1; i >= 0 && i >= temp->account_transactions_count - 5; i--) {
                printf("Transaction ID: %u, Type: %s, Amount: %.2f, Date: %s\n",
                    temp->transactions[i].transaction_id,
                    (temp->transactions[i].type == DEPOSIT ? "Deposit" : "Withdraw"),
                    temp->transactions[i].amount,
                    temp->transactions[i].date);
            }
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Function to save account details to a file
void Save_to_file(void) {
    FILE *file = fopen("accounts.dat", "wb");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    account *temp = head;
    while (temp != NULL) {
        fwrite(temp, sizeof(account), 1, file);
        temp = temp->next;
    }

    fclose(file);
    printf("Account information saved to file.\n");
}

// Function to load account details from a file
void Load_from_file(void) {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        printf("No saved data found.\n");
        return;
    }

    while (1) {
        account *new_account = (account *)malloc(sizeof(account));
        if (fread(new_account, sizeof(account), 1, file) != 1) {
            free(new_account);
            break;
        }
        new_account->next = head;
        head = new_account;
    }

    fclose(file);
    printf("Account information loaded from file.\n");
}

// Function to display all accounts
void Display_all_accounts(void) {
    account *temp = head;
    while (temp != NULL) {
        printf("Account Number: %u, Name: %s, Balance: %.2f, Contact: %s\n",
               temp->account_number, temp->account_name, temp->account_balance, temp->contact_number);
        temp = temp->next;
    }
}

// Function to find and display specific account details
void Find_account(void) {
    uint32_t account_number;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp != NULL) {
        if (temp->account_number == account_number) {
            printf("Account Number: %u, Name: %s, Balance: %.2f, Contact: %s\n",
                   temp->account_number, temp->account_name, temp->account_balance, temp->contact_number);
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

// Function to quit the application
void Quit(void) {
    printf("Exiting the application.\n");
    exit(0);
}

// Function to display the menu
void Display_menu(void) {
    printf("\n------------------MENU---------------------------\n");
    printf("c/C: Create account.\n");
    printf("h/H: Transaction history.\n");
    printf("w/W: Withdraw amount.\n");
    printf("d/D: Deposit amount.\n");
    printf("b/B: Balance enquiry.\n");
    printf("t/T: Transfer money.\n");
    printf("e/E: Display all accounts details.\n");
    printf("s/S: Save the accounts info in file.\n");
    printf("f/F: Find a specific account.\n");
    printf("q/Q: Quit from app.\n");
    printf("Enter your choice: ");
}

int main(void) {
    Load_from_file();

    char choice;
    while (1) {
        Display_menu();
        scanf(" %c", &choice); // Notice the space before %c to avoid reading leftover newline

        switch (choice) {
            case 'c':
            case 'C':
                Create_account();
                break;
            case 'h':
            case 'H':
                Transaction_history();
                break;
            case 'w':
            case 'W':
                Withdraw();
                break;
            case 'd':
            case 'D':
                Deposit();
                break;
            case 'b':
            case 'B':
                Balance_enquiry();
                break;
            case 't':
            case 'T':
                Transfer();
                break;
            case 'e':
            case 'E':
                Display_all_accounts();
                break;
            case 's':
            case 'S':
                Save_to_file();
                break;
            case 'f':
            case 'F':
                Find_account();
                break;
            case 'q':
            case 'Q':
                Save_to_file();
                Quit();
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
