// week5_task3_student_management_system.c
// Name: Rainers  Surname: Bulgačs  Student ID: 251RDC073
//
// Task 3: Mini-project – Student management system with file persistence
// Week 5 – Files & Modular Programming
// TODO: Implement the functions to load, save, add, and list students.
//
// Build: make lab5   Run: ./bin/week5_task3_student_management_system

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define NAME_LEN 50
#define LINE_LEN 256
#define DATA_FILE "students.txt"

typedef struct Student {
    char name[NAME_LEN];
    int id;
    float gpa;
} Student;

// Function prototypes (do not change these signatures – the autograder calls them directly)
int  load_students(Student arr[], int max);          // returns number of records loaded
int  save_students(const Student arr[], int count);  // 0 on success, -1 on error
void add_student(Student arr[], int *count);
void list_students(const Student arr[], int count);
int  read_line(const char *prompt, char *buf, size_t size);

int main(void) {
    Student students[MAX_STUDENTS];
    int count = 0;
    char input[LINE_LEN];
    int running = 1;

    // TODO: Load existing data: count = load_students(students, MAX_STUDENTS);
    count = load_students(students, MAX_STUDENTS);
    printf("Loaded %d student(s) from %s\n", count, DATA_FILE);
    // (void)students;  // remove this line once you use the array

    while (running) {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");

        int choice;
        if (read_line("Select an option: ", input, sizeof input) != 0) {
            choice = 3;                         // end of input: save and exit instead of looping forever
        } else {
            char *end;
            long value = strtol(input, &end, 10);
            choice = (end != input && *end == '\0') ? (int)value : 0;   // non-numbers become invalid
        }

        switch (choice) {
            case 1:
                // TODO: Call list_students()
                list_students(students, count);
                break;
            case 2:
                // TODO: Call add_student()
                add_student(students, &count);
                break;
            case 3:
                // TODO: Call save_students(). If it fails, print an error message.
                if (save_students(students, count) != 0) {
                    printf("erorr\n");
                }
                printf("Data saved. Goodbye!\n");
                running = 0;
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    }

    return EXIT_SUCCESS;
}

// Provided helper – prints a prompt and reads one line from stdin into buf.
// The trailing newline is removed. Returns 0 on success, -1 on end of input (EOF).
int read_line(const char *prompt, char *buf, size_t size) {
    printf("%s", prompt);
    fflush(stdout);
    if (fgets(buf, (int)size, stdin) == NULL) {
        return -1;
    }
    size_t len = strcspn(buf, "\r\n");
    if (buf[len] == '\0' && len == size - 1) {
        // Line was longer than the buffer: discard the rest of it.
        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    buf[len] = '\0';
    return 0;
}

// TODO: Implement load_students()
// Open DATA_FILE for reading. If it cannot be opened (e.g. first run), return 0.

int load_students(Student arr[], int max) {
    FILE *fp = fopen(DATA_FILE, "r");
    if (fp == NULL) {
        return 0;
    }
// Read the file line by line with fgets(); parse "name,id,gpa" with
    char line[LINE_LEN];
    int i = 0; 
    while (i < max && fgets(line, sizeof line, fp)){
        Student s;
// sscanf(line, "%49[^,],%d,%f", ...) and keep only lines where sscanf returned 3.
        if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3){
            arr[i]=s;
            i++;
        }
    }
    // Stop when max records have been loaded. Close the file and return the number loaded.
    fclose(fp);
    return i;
    // (void)arr; (void)max;  // remove this line when you implement the function
}

// TODO: Implement save_students()


int save_students(const Student arr[], int count) {
    // Open DATA_FILE for writing ("w"), return -1 if fopen() fails.
    FILE *fp = fopen(DATA_FILE, "w"); 
    if (fp == NULL) {
        return -1;
    }
// Write one line per student: fprintf(fp, "%s,%d,%.2f\n", ...). Close the file and return 0.
    for (int i=0; i <count; i++) {
        fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }
    if (fclose(fp) != 0) {
        return -1;
    }
    return 0;
}

// TODO: Implement add_student()
void add_student(Student arr[], int *count) {
// 1. If *count >= MAX_STUDENTS, print "Cannot add more students (limit reached)." and return.
    if (*count >= MAX_STUDENTS) {
        printf ("Cannot add more students (limit reached).\n");
        return;
    }
// 2. Use read_line() to ask "Enter name: ", "Enter ID: " and "Enter GPA: ".
//    If read_line() returns -1 (end of input), just return.
    char name[LINE_LEN];
    char id_str[LINE_LEN];
    char gpa_str[LINE_LEN];

    if (read_line("Enter name: ", name, sizeof name) !=0) return;
    if (read_line("Enter ID: ", id_str, sizeof id_str) !=0) return;
    if (read_line("Enter GPA: ", gpa_str, sizeof gpa_str) !=0) return;

// 3. Validate: name not empty, no ',' in name, ID is an integer, GPA is a number in 0.0–4.0
//    (strtol / strtof are useful). Otherwise print "Invalid input. Student not added." and return.
    if (name[0] == '\0' || strlen(name) >= NAME_LEN || strchr(name, ',') != NULL) {
        printf("Invalid input. Student not added.\n");
        return;
    }
    
    char *end;
    long id = strtol(id_str, &end, 10);
    if (end == id_str || *end != '\0' || (long)(int)id != id) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    float gpa = strtof(gpa_str, &end);
    if (end == gpa_str || *end != '\0' || !(gpa >= 0.0f && gpa <= 4.0f)) {
        printf("Invalid input. Student not added.\n");
        return;
    }



// 4. Store the student at arr[*count], increase *count, print "Student added successfully!"
    snprintf(arr[*count].name, NAME_LEN, "%s", name);
    arr[*count].id = (int)id;
    arr[*count].gpa = gpa;
    (*count)++;

    printf("Student added successfully!\n");


    // (void)arr; (void)count;  // remove this line when you implement the function
}

// TODO: Implement list_students()
// If count is 0 print "No students found."; otherwise print a header and one line per student,
// e.g. printf("%-5d %-20s %.2f\n", id, name, gpa);
void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }
    printf("%-5s %-20s %.2s\n", "id", "name", "gpa");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}
