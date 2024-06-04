#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESCRIPTION_SIZE 100

typedef struct Task {
    int id;
    char description[MAX_DESCRIPTION_SIZE];
    struct Task* prox;
} TASK;

// Estruturas globais para fila, lista e pilha
TASK* pendingQueueFront = NULL;
TASK* pendingQueueRear = NULL;
TASK* completedList = NULL;
TASK* draftStack = NULL;

// CONSTRUCTOR
TASK* createTask(int id, char* description);
TASK* createTaskByScanf();

// LIST
void addToCompletedList(TASK* newTask);
TASK* removeFromCompletedListByItsId(int id);
void seeAllCompletedList();

// QUEUE
void putToPendingQueue(TASK* newTask);
TASK* getFromPendingQueue();
void seeAllPendingQueue();

// STACK
void pushToDraftStack(TASK* newTask);
TASK* popFromDraftStack();
void seeAllDraftStack();

// MENU
void displayMenu();

int main() {
    int choice;
    printf("################# TASK MANAGER SYSTEM #################\n");

    do {
        displayMenu();
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // CREATE A TASK, THEN ADD TO PENDING QUEUE
                TASK* newTask = createTaskByScanf();
                putToPendingQueue(newTask);
                break;
            }
            case 2: {
                // SEE ALL TASKS FROM PENDING QUEUE
                seeAllPendingQueue();
                break;
            }
            case 3: {
                // COMPLETE FIRST PENDING TASK
                TASK* firstTask = getFromPendingQueue();
                if (firstTask != NULL) {
                    addToCompletedList(firstTask);
                }
                break;
            }
            case 4: {
                // SEE ALL TASKS FROM COMPLETED LIST
                seeAllCompletedList();
                break;
            }
            case 5: {
                // SET COMPLETED TASK TO DRAFT
                int id;
                printf("Enter Task ID (number): ");
                scanf("%d", &id);

                TASK* task = removeFromCompletedListByItsId(id);
                if (task != NULL) {
                    pushToDraftStack(task);
                }
                break;
            }
            case 6: {
                // SEE ALL TASKS FROM DRAFT STACK
                seeAllDraftStack();
                break;
            }
            case 7: {
                // SET LAST DRAFT AS PENDING TASK
                TASK* lastTask = popFromDraftStack();
                if (lastTask != NULL) {
                    putToPendingQueue(lastTask);
                }
                break;
            }
            case 0: {
                printf("Exiting program\n");
                break;
            }
            default: {
                printf("Invalid choice\n");
                break;
            }
        }
    } while (choice != 0);

    printf("################# SYSTEM SHUT DOWN #################\n");
    return 0;
}

// CONSTRUCTOR
TASK* createTask(int id, char* description) {
    TASK* newTask = (TASK*) malloc(sizeof(TASK));
    newTask->id = id;
    strcpy(newTask->description, description);
    newTask->prox = NULL;
    return newTask;
}

TASK* createTaskByScanf() {
    int id;
    char description[MAX_DESCRIPTION_SIZE];

    printf("Enter Task ID (number): ");
    scanf("%d", &id);

    getchar(); // To consume newline character left by scanf
    printf("Enter Task Description (string): ");
    fgets(description, MAX_DESCRIPTION_SIZE, stdin);
    description[strcspn(description, "\n")] = '\0'; // Remove newline character

    return createTask(id, description);
}

// LIST
void addToCompletedList(TASK* newTask) {
    printf("Adding Task to Completed List\n");
    newTask->prox = completedList;
    completedList = newTask;
}

TASK* removeFromCompletedListByItsId(int id) {
    printf("Removing Task from Completed List\n");
    TASK* current = completedList;
    TASK* previous = NULL;

    while (current != NULL && current->id != id) {
        previous = current;
        current = current->prox;
    }

    if (current == NULL) {
        printf("Task with ID %d not found.\n", id);
        return NULL;
    }

    if (previous == NULL) {
        completedList = current->prox;
    } else {
        previous->prox = current->prox;
    }

    return current;
}

void seeAllCompletedList() {
    printf("Printing All Completed List\n");
    TASK* current = completedList;
    while (current != NULL) {
        printf("ID: %d, Description: %s\n", current->id, current->description);
        current = current->prox;
    }
}

// QUEUE
void putToPendingQueue(TASK* newTask) {
    printf("Putting Task to Pending Queue\n");
    if (pendingQueueRear == NULL) {
        pendingQueueFront = pendingQueueRear = newTask;
    } else {
        pendingQueueRear->prox = newTask;
        pendingQueueRear = newTask;
    }
}

TASK* getFromPendingQueue() {
    printf("Getting Task from Pending Queue\n");
    if (pendingQueueFront == NULL) {
        printf("No tasks in pending queue.\n");
        return NULL;
    }

    TASK* temp = pendingQueueFront;
    pendingQueueFront = pendingQueueFront->prox;

    if (pendingQueueFront == NULL) {
        pendingQueueRear = NULL;
    }

    return temp;
}

void seeAllPendingQueue() {
    printf("Printing All Pending Queue\n");
    TASK* current = pendingQueueFront;
    while (current != NULL) {
        printf("ID: %d, Description: %s\n", current->id, current->description);
        current = current->prox;
    }
}

// STACK
void pushToDraftStack(TASK* newTask) {
    printf("Pushing Task to Draft Stack\n");
    newTask->prox = draftStack;
    draftStack = newTask;
}

TASK* popFromDraftStack() {
    printf("Popping Task from Draft Stack\n");
    if (draftStack == NULL) {
        printf("No tasks in draft stack.\n");
        return NULL;
    }

    TASK* temp = draftStack;
    draftStack = draftStack->prox;
    return temp;
}

void seeAllDraftStack() {
    printf("Printing All Draft Stack\n");
    TASK* current = draftStack;
    while (current != NULL) {
        printf("ID: %d, Description: %s\n", current->id, current->description);
        current = current->prox;
    }
}

// MENU
void displayMenu() {
    printf("\nMenu:\n");
    printf("1 - Create New Pending Task\n");
    printf("2 - See All Pending Tasks\n");
    printf("3 - Complete First Pending Task\n");
    printf("4 - See All Completed Tasks\n");
    printf("5 - Set Completed Task as Draft by its ID\n");
    printf("6 - See All Draft Tasks\n");
    printf("7 - Set Last Draft Task as Pending Task\n");
    printf("0 - Exit\n");
}