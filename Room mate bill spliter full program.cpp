
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMMATES 10
#define MAX_EXPENSES 50
#define NAME_LEN 50
#define USER_FILE "users.txt"
#define DATA_FILE "expenses.txt"

typedef struct {
    float amount;
    char description[100];
} Expense;

typedef struct {
    char name[NAME_LEN];
    Expense expenses[MAX_EXPENSES];
    int expenseCount;
} Roommate;

Roommate roommates[MAX_ROOMMATES];
int roommateCount = 0;

// --- Function Declarations ---
void clearScreen();
void pauseScreen();
void welcome();
void loginSystem();
void registerUser();
int login();
int validateUser(const char*, const char*);
void inputRoommates();
void mainMenu();
void addExpense();
void viewExpenses();
void viewRoommateExpenses();
void summary();
void suggestTransactions();
float calculateTotal(Roommate*, int);
int safeReadInt(const char*);

// --- Main ---
int main() {
    welcome();
    loginSystem();
    inputRoommates();
    mainMenu();
    return 0;
}

// --- Login System ---
void loginSystem() {
    int choice;
    do {
        clearScreen();
        printf("=== Login ===\n1. Register\n2. Login\n3. Exit\n");
        choice = safeReadInt("Choice: ");

        switch (choice) {
            case 1: registerUser();
			
			 break;
            case 2: if (login()) return; break;
            case 3: exit(0);
            default: printf("Invalid choice.\n");
        }
        pauseScreen();
    } while (1);
}

void registerUser() {
    FILE *f = fopen(USER_FILE, "a");
    if (!f) { printf("Error opening user file.\n"); return; }

    char user[50], pass[50];
    printf("New username: "); scanf(" %[^\n]", user);
    printf("New password: "); scanf(" %[^\n]", pass);
    fprintf(f, "%s %s\n", user, pass);
    fclose(f);
    printf("User registered.\n");
}

int login() {
    char user[50], pass[50];
    printf("Username: "); scanf(" %[^\n]", user);
    printf("Password: "); scanf(" %[^\n]", pass);
    if (validateUser(user, pass)) {
        printf("Login successful.\n");
        return 1;
    } else {
        printf("Invalid credentials.\n");
        return 0;
    }
}

int validateUser(const char* user, const char* pass) {
    FILE *f = fopen(USER_FILE, "r");
    if (!f) return 0;
    char u[50], p[50];
    while (fscanf(f, "%s %s", u, p) != EOF) {
        if (strcmp(u, user) == 0 && strcmp(p, pass) == 0) {
            fclose(f); return 1;
        }
    }
    fclose(f);
    return 0;
}

// --- Utility ---
void clearScreen() { printf("\n\n"); }
void pauseScreen() { printf("Press Enter..."); getchar(); getchar(); }
int safeReadInt(const char* prompt) {
    int val;
    printf("%s", prompt);
    if (scanf("%d", &val) != 1) {
        printf("Invalid input.\n"); exit(1);
    }
    return val;
}

void welcome() {
    printf("\n=== Roommate Expense Tracker ===\n\n");
}

void inputRoommates() {
    roommateCount = safeReadInt("Number of roommates (max 10): ");
    if (roommateCount > MAX_ROOMMATES) roommateCount = MAX_ROOMMATES;

    for (int i = 0; i < roommateCount; i++) {
        printf("Name of roommate %d: ", i + 1);
        scanf(" %[^\n]", roommates[i].name);
        roommates[i].expenseCount = 0;
    }
}

// --- Menu ---
void mainMenu() {
    int choice;
    do {
        clearScreen();
        printf("\n--- Main Menu ---\n");
        printf("1. Add Expense\n2. View All Expenses\n3. View Single Roommate\n");
        printf("4. Summary\n5. Suggestions\n6. Exit\n");
        choice = safeReadInt("Choice: ");

        switch (choice) {
            case 1: addExpense(); break;
            case 2: viewExpenses(); break;
            case 3: viewRoommateExpenses(); break;
            case 4: summary(); break;
            case 5: suggestTransactions(); break;
            case 6: printf("Goodbye!\n"); return;
            default: printf("Invalid choice.\n");
        }
        pauseScreen();
    } while (1);
}

// --- Core Functions ---
void addExpense() {
    char name[NAME_LEN];
    printf("Enter roommate name: "); scanf(" %[^\n]", name);

    for (int i = 0; i < roommateCount; i++) {
        if (strcmp(name, roommates[i].name) == 0) {
            if (roommates[i].expenseCount >= MAX_EXPENSES) {
                printf("Expense limit reached.\n");
                return;
            }

            Expense *e = &roommates[i].expenses[roommates[i].expenseCount++];
            printf("Description: "); scanf(" %[^\n]", e->description);
            printf("Amount: "); scanf("%f", &e->amount);
            printf("Added expense for %s.\n", name);
            return;
        }
    }
    printf("Roommate not found.\n");
}

void viewExpenses() {
    for (int i = 0; i < roommateCount; i++) {
        printf("\n%s's Expenses:\n", roommates[i].name);
        for (int j = 0; j < roommates[i].expenseCount; j++) {
            printf("  %.2f - %s\n", roommates[i].expenses[j].amount, roommates[i].expenses[j].description);
        }
    }
}

void viewRoommateExpenses() {
    char name[NAME_LEN];
    printf("Enter roommate name: "); scanf(" %[^\n]", name);

    for (int i = 0; i < roommateCount; i++) {
        if (strcmp(name, roommates[i].name) == 0) {
            printf("%s's Expenses:\n", name);
            for (int j = 0; j < roommates[i].expenseCount; j++) {
                printf("  %.2f - %s\n", roommates[i].expenses[j].amount, roommates[i].expenses[j].description);
            }
            return;
        }
    }
    printf("Roommate not found.\n");
}

void summary() {
    for (int i = 0; i < roommateCount; i++) {
        float total = 0;
        for (int j = 0; j < roommates[i].expenseCount; j++)
            total += roommates[i].expenses[j].amount;
        printf("%s's total: %.2f\n", roommates[i].name, total);
    }
}

void suggestTransactions() {
    float total = calculateTotal(roommates, roommateCount);
    float avg = total / roommateCount;
    printf("Total: %.2f | Per person: %.2f\n", total, avg);

    for (int i = 0; i < roommateCount; i++) {
        float personTotal = 0;
        for (int j = 0; j < roommates[i].expenseCount; j++)
            personTotal += roommates[i].expenses[j].amount;

        float diff = personTotal - avg;
        if (diff > 0)
            printf("%s should receive %.2f\n", roommates[i].name, diff);
        else if (diff < 0)
            printf("%s should pay %.2f\n", roommates[i].name, -diff);
        else
            printf("%s is settled.\n", roommates[i].name);
    }
}

float calculateTotal(Roommate *list, int count) {
    float total = 0;
    for (int i = 0; i < count; i++)
        for (int j = 0; j < list[i].expenseCount; j++)
            total += list[i].expenses[j].amount;
    return total;
}
