#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_DESC_SIZE 100

typedef struct Task {
    int taskId;
    char taskDesc[MAX_DESC_SIZE];
    struct Task* next;
} TASK;

TASK* pendingQueueFront = NULL;
TASK* pendingQueueRear = NULL;
TASK* completedTasksList = NULL;
TASK* draftTasksStack = NULL;

TASK* createNewTask(int taskId, char* taskDesc);
TASK* createTaskWithInput();

void addToCompletedTasks(TASK* newTask);
TASK* removeFromCompletedTasksById(int taskId);
void displayAllCompletedTasks();

void enqueuePendingTask(TASK* newTask);
TASK* dequeuePendingTask();
void displayAllPendingTasks();

void pushDraftTask(TASK* newTask);
TASK* popDraftTask();
void displayAllDraftTasks();

void showMenu();

int main() {
    int userChoice;
    printf("################# TASK MANAGEMENT SYSTEM #################\n");

    do {
        showMenu();
        printf("Choose an option: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1: {
                TASK* newTask = createTaskWithInput();
                enqueuePendingTask(newTask);
                break;
            }
            case 2: {
                displayAllPendingTasks();
                break;
            }
            case 3: {
                TASK* firstTask = dequeuePendingTask();
                if (firstTask != NULL) {
                    addToCompletedTasks(firstTask);
                }
                break;
            }
            case 4: {
                displayAllCompletedTasks();
                break;
            }
            case 5: {
                int taskId;
                printf("Enter Task ID (number): ");
                scanf("%d", &taskId);

                TASK* task = removeFromCompletedTasksById(taskId);
                if (task != NULL) {
                    pushDraftTask(task);
                }
                break;
            }
            case 6: {
                displayAllDraftTasks();
                break;
            }
            case 7: {
                TASK* lastTask = popDraftTask();
                if (lastTask != NULL) {
                    enqueuePendingTask(lastTask);
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
    } while (userChoice != 0);

    printf("################# SYSTEM SHUT DOWN #################\n");
    return 0;
}

TASK* createNewTask(int taskId, char* taskDesc) {
    TASK* newTask = (TASK*) malloc(sizeof(TASK));
    newTask->taskId = taskId;
    strcpy(newTask->taskDesc, taskDesc);
    newTask->next = NULL;
    return newTask;
}

TASK* createTaskWithInput() {
    int taskId;
    char taskDesc[MAX_DESC_SIZE];

    printf("Enter Task ID (number): ");
    scanf("%d", &taskId);

    getchar();
    printf("Enter Task Description (string): ");
    fgets(taskDesc, MAX_DESC_SIZE, stdin);
    taskDesc[strcspn(taskDesc, "\n")] = '\0';

    return createNewTask(taskId, taskDesc);
}

void addToCompletedTasks(TASK* newTask) {
    printf("Adding Task to Completed Tasks List\n");
    newTask->next = completedTasksList;
    completedTasksList = newTask;
}

TASK* removeFromCompletedTasksById(int taskId) {
    printf("Removing Task from Completed Tasks List\n");
    TASK* current = completedTasksList;
    TASK* previous = NULL;

    while (current != NULL && current->taskId != taskId) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Task with ID %d not found.\n", taskId);
        return NULL;
    }

    if (previous == NULL) {
        completedTasksList = current->next;
    } else {
        previous->next = current->next;
    }

    return current;
}

void displayAllCompletedTasks() {
    printf("Displaying All Completed Tasks\n");
    TASK* current = completedTasksList;
    while (current != NULL) {
        printf("ID: %d, Description: %s\n", current->taskId, current->taskDesc);
        current = current->next;
    }
}

void enqueuePendingTask(TASK* newTask) {
    printf("Enqueuing Task to Pending Tasks Queue\n");
    if (pendingQueueRear == NULL) {
        pendingQueueFront = pendingQueueRear = newTask;
    } else {
        pendingQueueRear->next = newTask;
        pendingQueueRear = newTask;
    }
}

TASK* dequeuePendingTask() {
    printf("Dequeuing Task from Pending Tasks Queue\n");
    if (pendingQueueFront == NULL) {
        printf("No tasks in pending queue.\n");
        return NULL;
    }

    TASK* temp = pendingQueueFront;
    pendingQueueFront = pendingQueueFront->next;

    if (pendingQueueFront == NULL) {
        pendingQueueRear = NULL;
    }

    return temp;
}

void displayAllPendingTasks() {
    printf("Displaying All Pending Tasks\n");
    TASK* current = pendingQueueFront;
    while (current != NULL) {
        printf("ID: %d, Description: %s\n", current->taskId, current->taskDesc);
        current = current->next;
    }
}

// STACK
void pushDraftTask(TASK* newTask) {
    printf("Pushing Task to Draft Tasks Stack\n");
    newTask->next = draftTasksStack;
    draftTasksStack = newTask;
}

TASK* popDraftTask() {
    printf("Popping Task from Draft Tasks Stack\n");
    if (draftTasksStack == NULL) {
        printf("No tasks in draft stack.\n");
        return NULL;
    }

    TASK* temp = draftTasksStack;
    draftTasksStack = draftTasksStack->next;
    return temp;
}

void displayAllDraftTasks() {
    printf("Displaying All Draft Tasks\n");
    TASK* current = draftTasksStack;
    while (current != NULL) {
        printf("ID: %d, Description: %s\n", current->taskId, current->taskDesc);
        current = current->next;
    }
}

void showMenu() {
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
