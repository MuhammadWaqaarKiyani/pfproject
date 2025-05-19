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
