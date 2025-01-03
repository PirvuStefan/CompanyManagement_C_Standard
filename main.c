#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct employee {
    int id;
    char name[50];
    char role[50];
    int salary;
    int is_retired;
};

struct company {
    char name[50];
    int number_of_employees;
    struct employee employees[1001];
};

int num_companies;
struct company companies[1001];

void initialize_companies() {
    FILE *file = fopen("companies.txt", "r");
    if (file == NULL) {
        perror("Failed to open companies.txt");
        return;
    }

    fscanf(file, "%d", &num_companies);

    for (int i = 0; i < num_companies; i++) {
        fscanf(file, "%s", companies[i].name);
    }

    fclose(file);

    file = fopen("companies_number_of_employees.txt", "r");
    if (file == NULL) {
        perror("Failed to open companies_number_of_employees.txt");
        return;
    }

    for (int i = 0; i < num_companies; i++) {
       fscanf(file, "%d", &companies[i].number_of_employees);
    }

    fclose(file);
}

void initialize_employees() {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        perror("Failed to open employees.txt");
        return;
    }

    int company_index, id, salary;
    char name[50], role[50];
    int is_retired;

    while (fscanf(file, "%d", &company_index) != EOF) {
        for (int i = 0; i < companies[company_index].number_of_employees; i++) {
            fscanf(file, "%d", &id);
            fscanf(file, "%s", name);
            fscanf(file, "%s", role);
            fscanf(file, "%d", &salary);
            fscanf(file, "%d", &is_retired);

            struct employee employee;
            employee.id = id;
            strcpy(employee.name, name);
            strcpy(employee.role, role);
            employee.salary = salary;
            employee.is_retired = is_retired;
            companies[company_index].employees[i] = employee;
        }
    }

    fclose(file);
}

void show_companies() {
    int n = num_companies;
    if (n == 0) {
        printf("There are no companies registered at the moment.\n");
        printf("Type any letter in the terminal to add a new company.\n");
        return;
    }
    printf("The following companies are registered:\n");
    for (int i = 0; i < n; i++) {
        printf("Company: %s\n", companies[i].name);
    }
    printf("Type add in the terminal to add a new company.\n");
    printf("Type show and the number associated with the company to see the employees of that company (indexing from 0).\n");
    printf("Type 'close' to close the program.\n");
}

int main(void) {
    printf("dfafafa");
    initialize_companies();
    initialize_employees();
    show_companies();
    return 0;
}