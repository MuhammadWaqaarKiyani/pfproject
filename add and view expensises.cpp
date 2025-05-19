
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
