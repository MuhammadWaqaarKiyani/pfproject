
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
