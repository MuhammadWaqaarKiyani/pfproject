
void inputRoommates() {
    roommateCount = safeReadInt("Number of roommates (max 10): ");
    if (roommateCount > MAX_ROOMMATES) roommateCount = MAX_ROOMMATES;

    for (int i = 0; i < roommateCount; i++) {
        printf("Name of roommate %d: ", i + 1);
        scanf(" %[^\n]", roommates[i].name);
        roommates[i].expenseCount = 0;
    }
}
