
#include <stdio.h>

#define FILE_NAME "students.dat"

struct Student {
    int id;
    char name[50];
    int age;
    float marks;
};

void addStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\n--- Add Student ---\n");

    printf("Enter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);
    fclose(fp);

    printf("\nStudent added successfully!\n");
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");

    if (fp == NULL) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\n========== STUDENT RECORDS ==========\n");
    printf("%-10s %-25s %-10s %-10s\n",
           "ID", "Name", "Age", "Marks");
    printf("-----------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%-10d %-25s %-10d %-10.2f\n",
               s.id, s.name, s.age, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    int id, found = 0;

    if (fp == NULL) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.id == id) {
            printf("\n--- Student Found ---\n");
            printf("ID    : %d\n", s.id);
            printf("Name  : %s\n", s.name);
            printf("Age   : %d\n", s.age);
            printf("Marks : %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found.\n");

    fclose(fp);
}

void deleteStudent() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    int id, found = 0;

    if (fp == NULL || temp == NULL) {
        printf("\nNo student records found.\n");

        if (fp != NULL)
            fclose(fp);

        if (temp != NULL)
            fclose(temp);

        return;
    }

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.id == id) {
            found = 1;
        } else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent not found.\n");
}

int main() {
    int choice;

    do {
        printf("\n====================================\n");
        printf("       STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");

        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                printf("\nThank you!\n");
                break;

            default:
                printf("\nInvalid choice!\n");
        }

    } while (choice != 5);

    return 0;
}
