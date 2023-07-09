#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_EMAIL_LENGTH 50
#define MAX_PASSWORD_LENGTH 20

struct User
{
    char name[MAX_NAME_LENGTH];
    char email[MAX_EMAIL_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

void registerUser(struct User *user)
{
    printf("Enter name: ");
    fgets(user->name, MAX_NAME_LENGTH, stdin);
    user->name[strcspn(user->name, "\n")] = '\0';

    printf("Enter email: ");
    fgets(user->email, MAX_EMAIL_LENGTH, stdin);
    user->email[strcspn(user->email, "\n")] = '\0';

    printf("Enter password: ");
    fgets(user->password, MAX_PASSWORD_LENGTH, stdin);
    user->password[strcspn(user->password, "\n")] = '\0';
}

void saveUserToFile(const struct User *user)
{
    FILE *file = fopen("users.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    fprintf(file, "%s,%s,%s\n", user->name, user->email, user->password);
    fclose(file);
}

void loadUsersFromFile(struct User *users, int *numUsers)
{
    FILE *file = fopen("users.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    *numUsers = 0;
    char line[MAX_NAME_LENGTH + MAX_EMAIL_LENGTH + MAX_PASSWORD_LENGTH + 3];

    while (fgets(line, sizeof(line), file))
    {
        line[strcspn(line, "\n")] = '\0';

        char *name = strtok(line, ",");
        char *email = strtok(NULL, ",");
        char *password = strtok(NULL, ",");

        struct User newUser;
        strcpy(newUser.name, name);
        strcpy(newUser.email, email);
        strcpy(newUser.password, password);

        users[*numUsers] = newUser;
        (*numUsers)++;
    }

    fclose(file);
}

void displayUsers(const struct User *users, int numUsers)
{
    printf("Registered Users:\n");
    for (int i = 0; i < numUsers; i++)
    {
        printf("Name: %s, Email: %s, Password: %s\n", users[i].name, users[i].email, users[i].password);
    }
}

int main()
{
    struct User users[100];
    int numUsers = 0;

    int choice;
    printf("Cyber Management System\n");

    while (1)
    {
        printf("\n1. Register User\n");
        printf("2. Display Users\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
        {
            struct User newUser;
            registerUser(&newUser);
            saveUserToFile(&newUser);
            printf("User registered successfully.\n");
            break;
        }
        case 2:
            loadUsersFromFile(users, &numUsers);
            displayUsers(users, numUsers);
            break;
        case 3:
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
