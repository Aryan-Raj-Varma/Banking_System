#include "banking_system.h"

account *head = NULL;

void get_current_date(char *buffer, size_t size) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer, size, "%Y-%m-%d", tm_info);
}

void Create_account(void) {
    account *new_account = (account *)malloc(sizeof(account));
    if (!new_account) {
        printf("Memory allocation failed.\n");
        return;
    }

    printf("Enter Account Number: ");
    scanf("%u", &new_account->account_number);
    getchar();

    printf("Enter Account Name: ");
    fgets(new_account->account_name, MAX_NAME_LENGTH, stdin);
    new_account->account_name[strcspn(new_account->account_name, "\n")] = 0;

    new_account->account_balance = 0.0;
    new_account->account_transactions_count = 0;

    printf("Enter Contact Number: ");
    fgets(new_account->contact_number, MAX_CONTACT_LENGTH, stdin);
    new_account->contact_number[strcspn(new_account->contact_number, "\n")] = 0;

    new_account->next = head;
    head = new_account;

    printf("Account Created Successfully.\n");
}

void Withdraw(void) {
    uint32_t account_number;
    double amount;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp) {
        if (temp->account_number == account_number) {
            printf("Enter amount to withdraw: ");
            scanf("%lf", &amount);
            if (amount > temp->account_balance) {
                printf("Insufficient funds.\n");
                return;
            }

            temp->account_balance -= amount;
            if (temp->account_transactions_count < MAX_TRANSACTIONS) {
                char date[20];
                get_current_date(date, sizeof(date));
                transaction t = { temp->account_transactions_count + 1, WITHDRAW, amount, "" };
                strcpy(t.date, date);
                temp->transactions[temp->account_transactions_count++] = t;
            }

            printf("Withdrawal successful.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

void Deposit(void) {
    uint32_t account_number;
    double amount;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp) {
        if (temp->account_number == account_number) {
            printf("Enter amount to deposit: ");
            scanf("%lf", &amount);
            temp->account_balance += amount;

            if (temp->account_transactions_count < MAX_TRANSACTIONS) {
                char date[20];
                get_current_date(date, sizeof(date));
                transaction t = { temp->account_transactions_count + 1, DEPOSIT, amount, "" };
                strcpy(t.date, date);
                temp->transactions[temp->account_transactions_count++] = t;
            }

            printf("Deposit successful.\n");
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

void Transfer(void) {
    uint32_t from, to;
    double amount;
    printf("Enter From Account Number: ");
    scanf("%u", &from);
    printf("Enter To Account Number: ");
    scanf("%u", &to);

    account *from_acc = NULL, *to_acc = NULL, *temp = head;

    while (temp) {
        if (temp->account_number == from) from_acc = temp;
        if (temp->account_number == to) to_acc = temp;
        temp = temp->next;
    }

    if (!from_acc || !to_acc) {
        printf("One or both accounts not found.\n");
        return;
    }

    printf("Enter amount to transfer: ");
    scanf("%lf", &amount);
    if (amount > from_acc->account_balance) {
        printf("Insufficient funds.\n");
        return;
    }

    from_acc->account_balance -= amount;
    to_acc->account_balance += amount;

    char date[20];
    get_current_date(date, sizeof(date));

    if (from_acc->account_transactions_count < MAX_TRANSACTIONS) {
        transaction t1 = { from_acc->account_transactions_count + 1, WITHDRAW, amount, "" };
        strcpy(t1.date, date);
        from_acc->transactions[from_acc->account_transactions_count++] = t1;
    }

    if (to_acc->account_transactions_count < MAX_TRANSACTIONS) {
        transaction t2 = { to_acc->account_transactions_count + 1, DEPOSIT, amount, "" };
        strcpy(t2.date, date);
        to_acc->transactions[to_acc->account_transactions_count++] = t2;
    }

    printf("Transfer successful.\n");
}

void Balance_enquiry(void) {
    uint32_t account_number;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp) {
        if (temp->account_number == account_number) {
            printf("Account Balance: %.2f\n", temp->account_balance);
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

void Transaction_history(void) {
    uint32_t account_number;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp) {
        if (temp->account_number == account_number) {
            printf("Last 5 Transactions for Account %u:\n", account_number);
            int count = temp->account_transactions_count;
            if (count == 0) {
                printf("No transactions found.\n");
                return;
            }
            for (int i = count - 1; i >= 0 && i >= count - 5; i--) {
                const char *type_str = (temp->transactions[i].type == DEPOSIT) ? "Deposit" : "Withdraw";
                printf("ID: %u, Type: %s, Amount: %.2f, Date: %s\n",
                       temp->transactions[i].transaction_id, type_str,
                       temp->transactions[i].amount, temp->transactions[i].date);
            }
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

void Save_to_file(void) {
    FILE *file = fopen("accounts.dat", "wb");
    if (!file) {
        printf("Error opening file.\n");
        return;
    }

    account *temp = head;
    while (temp) {
        fwrite(temp, sizeof(account) - sizeof(account *), 1, file); // skip `next` pointer
        temp = temp->next;
    }

    fclose(file);
    printf("Account information saved to file.\n");
}

void Load_from_file(void) {
    FILE *file = fopen("accounts.dat", "rb");
    if (!file) {
        printf("No saved data found.\n");
        return;
    }

    while (1) {
        account *new_acc = (account *)malloc(sizeof(account));
        if (fread(new_acc, sizeof(account) - sizeof(account *), 1, file) != 1) {
            free(new_acc);
            break;
        }
        new_acc->next = head;
        head = new_acc;
    }

    fclose(file);
    printf("Account information loaded from file.\n");
}

void Display_all_accounts(void) {
    account *temp = head;
    while (temp) {
        printf("Account Number: %u, Name: %s, Balance: %.2f, Contact: %s\n",
               temp->account_number, temp->account_name, temp->account_balance, temp->contact_number);
        temp = temp->next;
    }
}

void Find_account(void) {
    uint32_t account_number;
    printf("Enter Account Number: ");
    scanf("%u", &account_number);

    account *temp = head;
    while (temp) {
        if (temp->account_number == account_number) {
            printf("Account Number: %u, Name: %s, Balance: %.2f, Contact: %s\n",
                   temp->account_number, temp->account_name, temp->account_balance, temp->contact_number);
            return;
        }
        temp = temp->next;
    }
    printf("Account not found.\n");
}

void Free_all_accounts(void) {
    account *temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

void Quit(void) {
    Free_all_accounts();
    printf("Exiting the application.\n");
    exit(0);
}

void Display_menu(void) {
    printf("\n------------------ MENU ------------------------\n");
    printf("c/C: Create account\n");
    printf("h/H: Transaction history\n");
    printf("w/W: Withdraw amount\n");
    printf("d/D: Deposit amount\n");
    printf("b/B: Balance enquiry\n");
    printf("t/T: Transfer money\n");
    printf("e/E: Display all accounts\n");
    printf("s/S: Save account info to file\n");
    printf("f/F: Find account\n");
    printf("q/Q: Quit\n");
    printf("Enter your choice: ");
}

int main(void) {
    Load_from_file();
    char choice;

    while (1) {
        Display_menu();
        scanf(" %c", &choice);

        switch (choice) {
            case 'c': case 'C': Create_account(); break;
            case 'h': case 'H': Transaction_history(); break;
            case 'w': case 'W': Withdraw(); break;
            case 'd': case 'D': Deposit(); break;
            case 'b': case 'B': Balance_enquiry(); break;
            case 't': case 'T': Transfer(); break;
            case 'e': case 'E': Display_all_accounts(); break;
            case 's': case 'S': Save_to_file(); break;
            case 'f': case 'F': Find_account(); break;
            case 'q': case 'Q': Save_to_file(); Quit(); break;
            default: printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
