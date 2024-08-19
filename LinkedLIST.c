#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* next;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to print the list
void printList(struct Node* head) {
    struct Node* curr = head;
    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }
    printf("\n");
}

// Function to add a value at the end of the list
void addValueAtEnd(struct Node** head, int value) {
    if (*head == NULL) {
        *head = createNode(value);
        return;
    }

    struct Node* curr = *head;
    while (curr->next != NULL) {
        curr = curr->next;
    }

    curr->next = createNode(value);
}

// Function to add a value at a certain position
void addValueAtPosition(struct Node** head, int value, int position) {
    struct Node* newNode = createNode(value);

    if (position == 1) {
        newNode->next = *head;
        *head = newNode;
        return;
    }

    struct Node* curr = *head;
    for (int i = 1; i < position - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("Position out of bounds\n");
        return;
    }

    newNode->next = curr->next;
    curr->next = newNode;
}

// Function to remove a node at a certain position
void removeValueAtPosition(struct Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    struct Node* temp = *head;

    if (position == 1) {
        *head = temp->next;
        free(temp);
        return;
    }

    struct Node* curr = *head;
    for (int i = 1; i < position - 1 && curr != NULL; i++) {
        curr = curr->next;
    }

    if (curr == NULL || curr->next == NULL) {
        printf("Position out of bounds\n");
        return;
    }

    temp = curr->next;
    curr->next = temp->next;
    free(temp);
}

// Function to search for an element
void searchElement(struct Node* head, int value) {
    struct Node* curr = head;
    int position = 1;
    
    while (curr != NULL && curr->data != value) {
        curr = curr->next;
        position++;
    }

    if (curr != NULL && curr->data == value) {
        printf("Element is present at position: %d\n", position);
    } else {
        printf("Element is not present\n");
    }
}

// Function to sort the list
void sortList(struct Node* head) {
    struct Node* i;
    struct Node* j;
    
    if (head == NULL) return;

    for (i = head; i->next != NULL; i = i->next) {
        for (j = i->next; j != NULL; j = j->next) {
            if (i->data > j->data) {
                int temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
}

int main() {
    struct Node* head = NULL;
    int flag = 1, choice, value, position;

    while (flag) {
        printf("****************************\n");
        printf("Enter 1 : To add value in the list at the end.\n");
        printf("Enter 2 : To add value in the list at a certain position.\n");
        printf("Enter 3 : To remove value from a position.\n");
        printf("Enter 4 : To search an element.\n");
        printf("Enter 5 : To sort the list.\n");
        printf("Enter 6 : To exit and print the final list.\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the data: ");
                scanf("%d", &value);
                addValueAtEnd(&head, value);
                printList(head);
                break;

            case 2:
                printf("Enter the data: ");
                scanf("%d", &value);
                printf("Enter the position: ");
                scanf("%d", &position);
                addValueAtPosition(&head, value, position);
                printList(head);
                break;

            case 3:
                printf("Enter the position to remove: ");
                scanf("%d", &position);
                removeValueAtPosition(&head, position);
                printList(head);
                break;

            case 4:
                printf("Enter the element to search: ");
                scanf("%d", &value);
                searchElement(head, value);
                break;

            case 5:
                sortList(head);
                printList(head);
                break;

            case 6:
                printf("Final list: ");
                printList(head);
                flag = 0;
                break;

            default:
                printf("Wrong input!\n");
        }
    }

    return 0;
}
