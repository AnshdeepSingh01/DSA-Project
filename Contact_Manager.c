#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[15];
    struct Contact* next;
};

struct Contact* head = NULL;

void addContact() {
    struct Contact* newContact = (struct Contact*)malloc(sizeof(struct Contact));
    printf("Enter name: ");
    scanf(" %[^\n]", newContact->name);
    printf("Enter phone: ");
    scanf(" %[^\n]", newContact->phone);
    newContact->next = head;
    head = newContact;
    printf("Contact added!\n");
}

void viewContacts() {
    struct Contact* current = head;
    if (!current) {
        printf("No contacts to display.\n");
        return;
    }
    printf("\n--- Contact List ---\n");
    while (current) {
        printf("Name: %s\nPhone: %s\n\n", current->name, current->phone);
        current = current->next;
    }
}

void searchContact() {
    char searchName[50];
    printf("Enter name to search: ");
    scanf(" %[^\n]", searchName);
    struct Contact* current = head;
    while (current) {
        if (strcmp(current->name, searchName) == 0) {
            printf("Contact Found:\nName: %s\nPhone: %s\n", current->name, current->phone);
            return;
        }
        current = current->next;
    }
    printf("Contact not found.\n");
}

void deleteContact() {
    char deleteName[50];
    printf("Enter name to delete: ");
    scanf(" %[^\n]", deleteName);
    struct Contact *current = head, *prev = NULL;

    while (current) {
        if (strcmp(current->name, deleteName) == 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Contact deleted.\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Contact not found.\n");
}

int main() {
    int choice;
    while (1) {
        printf("\n===== Contact Management System (Linked List) =====\n");
        printf("1. Add Contact\n");
        printf("2. View Contacts\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: addContact(); break;
            case 2: viewContacts(); break;
            case 3: searchContact(); break;
            case 4: deleteContact(); break;
            case 5: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}