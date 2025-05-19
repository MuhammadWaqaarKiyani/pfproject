hum apke h kon?
void summary() {
    for (int i = 0; i < roommateCount; i++) {
        float total = 0;
        for (int j = 0; j < roommates[i].expenseCount; j++)
            total += roommates[i].expenses[j].amount;
        printf("%s's total: %.2f\n", roommates[i].name, total);
    }
}
