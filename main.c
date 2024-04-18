#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TASK_LENGTH 500
void add_task(const char *);
void list_tasks();
void remove_task(int);

/**
 * The function `add_task` appends a new task to a file named "tasks.txt".
 *
 * @param task A pointer to a constant character array representing the task to be added to the
 * "tasks.txt" file.
 */
void add_task(const char *task)
{
    FILE *file = fopen("tasks.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%s\n", task);
        fclose(file);
    }
    else
    {
        printf("Failed to open file.\n");
    }
}

/**
 * The function `list_tasks` reads and displays tasks from a file named "tasks.txt".
 */
void list_tasks()
{
    FILE *file = fopen("tasks.txt", "r");
    if (file != NULL)
    {
        char task[MAX_TASK_LENGTH];
        int index = 1;
        while (fgets(task, sizeof(task), file) != NULL)
        {
            printf("%d. %s", index++, task);
        }
        fclose(file);
    }
    else
    {
        printf("No tasks found.\n");
    }
}

/**
 * The function `remove_task` removes a task from a file based on the given index.
 *
 * @param index The `index` parameter in the `remove_task` function represents the position of the task
 * that needs to be removed from the list of tasks. The tasks are read from a file named "tasks.txt",
 * and the task at the specified index will be removed from the file.
 */
void remove_task(int index)
{
    FILE *file = fopen("tasks.txt", "r");
    if (file != NULL)
    {
        FILE *temp_file = fopen("temp.txt", "w");
        if (temp_file != NULL)
        {
            char task[MAX_TASK_LENGTH];
            int current_index = 1;
            while (fgets(task, sizeof(task), file) != NULL)
            {
                if (current_index != index)
                {
                    fputs(task, temp_file);
                }
                current_index++;
            }
            fclose(temp_file);
            fclose(file);
            remove("tasks.txt");
            rename("temp.txt", "tasks.txt");
            printf("Task removed successfully.\n");
        }
        else
        {
            printf("Failed to create temporary file.\n");
            fclose(file);
        }
    }
    else
    {
        printf("No tasks found.\n");
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: [executable] [option]\n", argv[0]);
        printf("Options:\n");
        printf("-a <task> : Add a new task\n");
        printf("-l        : List all tasks\n");
        printf("-r <index>: Remove a task by index\n");
        printf("--------------------------------------------\n");
        printf("Examples:\n");
        printf("./main -a \"Buy groceries\"\n");
        printf("./main -l\n");
        printf("./main -r 1\n");
        return 1;
    }

    if (strcmp(argv[1], "-a") == 0 && argc == 3)
    {
        add_task(argv[2]);
    }
    else if (strcmp(argv[1], "-l") == 0)
    {
        list_tasks();
    }
    else if (strcmp(argv[1], "-r") == 0 && argc == 3)
    {
        int index = atoi(argv[2]);
        remove_task(index);
    }
    else
    {
        printf("Invalid option or insufficient arguments.\n");
        return 1;
    }

    return 0;
}
