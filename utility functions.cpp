
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
