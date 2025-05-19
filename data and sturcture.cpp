typedef struct hehe{
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
