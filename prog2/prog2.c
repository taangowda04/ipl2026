#include <stdio.h>
#include <string.h>

#define FILENAME "employee.txt"
#define MAX 100

typedef struct
{
    int id;
    char name[50];
    float salary;
} Employee;

void inputdata(Employee e[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter the details of employee %d\n", i + 1);
        printf("Enter id: ");
        scanf("%d", &e[i].id);
        printf("Enter name: ");
        scanf("%49s", e[i].name);
        printf("Enter salary: ");
        scanf("%f", &e[i].salary);
    }
}

void storedata(Employee e[], int n, const char *filename)
{
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error in opening the file.\n");
        return;
    }

    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%d %s %.2f\n", e[i].id, e[i].name, e[i].salary);
    }

    fclose(fp);
}

int createindex(const char *filename, long pos[])
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error in opening the file.\n");
        return 0;
    }

    int count = 0;
    char line[200];

    while (count < MAX && fgets(line, sizeof(line), fp) != NULL)
    {
        pos[count] = ftell(fp) - (long)strlen(line);
        count++;
    }

    fclose(fp);
    return count;
}

void displayRecord(const char *filename, long position)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error in opening the file.\n");
        return;
    }

    Employee e;
    fseek(fp, position, SEEK_SET);

    if (fscanf(fp, "%d %49s %f", &e.id, e.name, &e.salary) == 3)
    {
        printf("\nEmployee details at given position:\n");
        printf("ID: %d\n", e.id);
        printf("Name: %s\n", e.name);
        printf("Salary: %.2f\n", e.salary);
    }
    else
    {
        printf("Record not found.\n");
    }

    fclose(fp);
}

int main()
{
    Employee e[MAX];
    long pos[MAX];
    int n, m, total;

    printf("Enter the number of employees: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number!\n");
        return 0;
    }

    inputdata(e, n);
    storedata(e, n, FILENAME);

    total = createindex(FILENAME, pos);

    printf("\nEnter the record number to display: ");
    scanf("%d", &m);

    if (m < 1 || m > total)
    {
        printf("Invalid record number!\n");
        return 0;
    }

    displayRecord(FILENAME, pos[m - 1]);
    return 0;
}