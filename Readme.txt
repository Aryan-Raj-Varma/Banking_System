===========================================
      C BANKING SYSTEM USING LINKED LIST
===========================================

Project Title:
--------------
Banking System in C using Linked Lists and File I/O

Description:
------------
This project implements a simple command-line banking system in C. It supports basic operations such as:
- Creating accounts
- Depositing and withdrawing money
- Transferring funds
- Viewing balance and transaction history
- Saving/loading account information to/from a file

All account data is stored using a singly linked list. Each account maintains a transaction log of up to 100 transactions. Data persistence is handled using binary file I/O.

Features:
---------
1. Create a new account with:
   - Account Number
   - Name
   - Contact Number

2. Deposit money

3. Withdraw money (only if sufficient balance exists)

4. Transfer funds between accounts

5. Balance enquiry

6. View last 5 transactions for an account

7. Display all accounts

8. Save data to a binary file (`accounts.dat`)

9. Load existing data on program start

10. Find specific account by account number

How to Compile:
---------------
Make sure all files are in the same directory:
- `main.c`
- `banking_system.h`

To compile:
$make 
To Run:
$./bank
