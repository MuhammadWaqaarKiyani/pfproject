void loginSystem() {
    int choice;
    do {
        clearScreen();
        printf("=== Login ===\n1. Register\n2. Login\n3. Exit\n");
        choice = safeReadInt("Choice: ");

        switch (choice) {
            case 1: registerUser(); break;
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
