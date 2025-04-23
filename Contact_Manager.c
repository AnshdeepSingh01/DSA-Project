#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Contact {
    char name[50];
    char phone[15];
};

void addContact() {
    struct Contact c;
    FILE *fp = fopen("contacts.txt", "a");

    if (fp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name: ");
    scanf(" %[^\n]", c.name);
    printf("Enter phone number: ");
    scanf(" %[^\n]", c.phone);

    fwrite(&c, sizeof(c), 1, fp);
    fclose(fp);
    printf("Contact added successfully!\n");
}

void viewContacts() {
    struct Contact c;
    FILE *fp = fopen("contacts.txt", "r");

    if (fp == NULL) {
        printf("No contacts found.\n");
        return;
    }

    printf("\n--- Contact List ---\n");
    while (fread(&c, sizeof(c), 1, fp)) {
        printf("Name: %s\nPhone: %s\n\n", c.name, c.phone);
    }

    fclose(fp);
}

void searchContact() {
    struct Contact c;
    char searchName[50];
    int found = 0;

    FILE *fp = fopen("contacts.txt", "r");
    if (fp == NULL) {
        printf("No contacts found.\n");
        return;
    }

    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, searchName) == 0) {
            printf("Contact Found:\nName: %s\nPhone: %s\n", c.name, c.phone);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Contact not found.\n");
    }

    fclose(fp);
}

void deleteContact() {
    struct Contact c;
    char deleteName[50];
    int found = 0;

    FILE *fp = fopen("contacts.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("Enter name to delete: ");
    scanf(" %[^\n]", deleteName);

    while (fread(&c, sizeof(c), 1, fp)) {
        if (strcmp(c.name, deleteName) == 0) {
            found = 1;
            continue;
        }
        fwrite(&c, sizeof(c), 1, temp);
    }

    fclose(fp);
    fclose(temp);
    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (found) {
        printf("Contact deleted successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}

int main() {
    int choice;

    while (1) {
        printf("\n===== Contact Management System =====\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Choose an option (1-5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("Exiting... Goodbye!\n"); exit(0);
            default: printf("Invalid option! Try again.\n");
        }
    }

    return 0;
}
