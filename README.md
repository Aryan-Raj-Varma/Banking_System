# Banking_System

Mini Project: BANKING SYSTEM
=============================

Objective:
----------
The goal of this mini project is to build a **Banking Management System** in C with features such as:
- Creating new bank accounts
- Performing transactions like deposit, withdrawal, and transfer
- Viewing account details and transaction history
- Saving and retrieving data persistently using file handling

The system uses **structures** and **linked lists** to store account holder information and transaction history. Data is retained between program executions using **binary file I/O**.

User Interface:
---------------
When the application is executed, the following menu is displayed:

---------------------- MENU --------------------------

c/C: Create account.

h/H: Transaction history (minimum → last 5).

w/W: Withdraw amount.

d/D: Deposit amount.

b/B: Balance enquiry.

t/T: Transfer money.

e/E: Display all account details.

s/S: Save account info to file.

f/F: Find/Search for a specific account.

q/Q: Quit the application.

-------------------------------------------------------

Requirements:
-------------
1. Each account should include the following:
   - `Account_number` (must be unique)
   - `Account_name`
   - `Account_balance`
   - `Account_transactions` (Array of structures)
   - `Account_transactions_count`
   - `Contact_number`

2. `Account_transactions` is a structure containing:
   - `Transaction_ID` (unique, uint32_t)
   - `Type` (enum → WITHDRAW / DEPOSIT)
   - `Amount`
   - `Date`

3. Duplicate **account numbers** must be prevented.
4. Multiple accounts **can have the same name**, but **account numbers must be unique**.
5. Each operation should be handled via a dedicated **user-defined function**.
   Example functions:
   - `Create_account()`
   - `Withdraw()`
   - `Deposit()`
   - `Transfer()`
   - `Save_to_file()`
   - `Load_from_file()`
   - `Find_account()`
   - `Transaction_history()`, etc.

Project Architecture:
---------------------
- Use **structures with pointers** and implement using **Singly Linked List (SLL)**.
- Every function should be implemented in a **separate `.c` file**.
- Use **typedef, enum, union** where applicable.
- Create a **dedicated header file** (`banking_system.h`) to store:
  - Structure definitions
  - Type aliases
  - Enum declarations
  - Function prototypes

Deliverables:
-------------
Submit your project in a folder named using your **student ID**. The folder must include:
1. All **source files (`.c`)**
2. All **header files (`.h`)**
3. A **Makefile** to compile the entire project
4. A `README.txt` file (this file) explaining:
   - Project features
   - File structure
   - How to compile and run the project
5. The program must retain all data (accounts and transactions) between executions using **file handling**.

Project Version 1: (Persistent Storage)
---------------------------------------
- Use file I/O to **store account information** in a binary file (`accounts.dat`)
- On startup, the application must **load existing data**
- On exit, the application must **save all data** back to the file
- Use `fwrite()` and `fread()` for binary file operations

Compilation:
------------
Use the provided Makefile:
```bash
make         # to compile
./bank       # to run the application
make clean   # to remove compiled files
