#include <stdio.h>
#include <stdlib.h>

#define FILENAME "stu.dat"
#define TFILENAME "tstu.dat"
#define MAX 100

typedef struct
{
    int id;
    char name[50];
    float marks;
} Student;

void inputdata(Student s[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("Enter the details of student %d\n", i + 1);

        printf("Enter id: ");
        scanf("%d", &s[i].id);

        printf("Enter name: ");
        scanf("%49s", s[i].name);

        printf("Enter marks: ");
        scanf("%f", &s[i].marks);

        if (s[i].marks < 0 || s[i].marks > 100)
        {
            s[i].marks = 0;
        }
    }
}

void storedata(Student s[], int n, const char *filename)
{
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("Error opening file for writing.\n");
        return;
    }

    fwrite(s, sizeof(Student), n, fp);
    fclose(fp);
}

void display_mth_record(const char *filename, int m)
{
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Error opening file for reading.\n");
        return;
    }

    Student s;
    fseek(fp, (m - 1) * sizeof(Student), SEEK_SET);

    if (fread(&s, sizeof(Student), 1, fp) != 1)
    {
        printf("Record not found.\n");
        fclose(fp);
        return;
    }

    printf("\nStudent details of record %d:\n", m);
    printf("ID: %d | Name: %s | Marks: %.2f\n", s.id, s.name, s.marks);

    fclose(fp);
}

void deleterecord(const char *filename, int n)
{
    FILE *fp = fopen(filename, "rb");
    FILE *tfp = fopen(TFILENAME, "wb");

    if (fp == NULL || tfp == NULL)
    {
        printf("Error opening file.\n");
        if (fp) fclose(fp);
        if (tfp) fclose(tfp);
        return;
    }

    Student s;
    int count = 0;

    while (fread(&s, sizeof(Student), 1, fp) == 1)
    {
        count++;
        if (count != n)
        {
            fwrite(&s, sizeof(Student), 1, tfp);
        }
    }

    fclose(fp);
    fclose(tfp);

    remove(filename);
    rename(TFILENAME, filename);

    printf("Record %d deleted successfully.\n", n);
}

int main()
{
    int n, m, a;
    Student s1[MAX];

    printf("Enter the number of students: ");
    scanf("%d", &n);

    if (n <= 0 || n > MAX)
    {
        printf("Invalid number!\n");
        return 0;
    }

    inputdata(s1, n);
    storedata(s1, n, FILENAME);

    printf("\nEnter the mth student to be printed: ");
    scanf("%d", &m);
    display_mth_record(FILENAME, m);

    printf("\nEnter the record number to be deleted: ");
    scanf("%d", &a);
    deleterecord(FILENAME, a);

    return 0;
}