#ifndef PROIECT_PCLP_SISTEM_BANCAR_LIBRARY_H
#define PROIECT_PCLP_SISTEM_BANCAR_LIBRARY_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void hello(void);

struct employee {
    int id;
    char name[50];
    char role[50];
    int salary;
    bool is_retired;
};

struct company {
    char name[50];
    int number_of_employees;
    struct employee *employees;
};

bool is_retired(struct employee *employee) {
    return employee->is_retired;
}

void initialize_companies(struct company **companies, int *num_companies) {
    FILE *file = fopen("companies.txt", "r");
    if (file == NULL) {
        perror("Failed to open companies.txt");
        return;
    }

    fscanf(file, "%d", num_companies);
    *companies = (struct company *)malloc(*num_companies * sizeof(struct company));

    for (int i = 0; i < *num_companies; i++) {
        fscanf(file, "%s", (*companies)[i].name);
    }

    fclose(file);

    file = fopen("companies_number_of_employees", "r");
    if (file == NULL) {
        perror("Failed to open companies_number_of_employees");
        return;
    }

    for (int i = 0; i < *num_companies; i++) {
       fscanf(file, "%d", &(*companies)[i].number_of_employees);
       // (*companies)[i].employees = NULL;
    }

    fclose(file);
}

void initialize_employee(struct employee *employee, int id, const char *name, const char *role, int salary, bool is_retired) {
    employee->id = id;
    strncpy(employee->name, name, sizeof(employee->name) - 1);
    employee->name[sizeof(employee->name) - 1] = '\0';
    strncpy(employee->role, role, sizeof(employee->role) - 1);
    employee->role[sizeof(employee->role) - 1] = '\0';
    employee->salary = salary;
    employee->is_retired = is_retired;
}

void show_companies(struct company *companies, int n) {

    if(n == 1) {
        printf("There are no companies registered at the moment.\n");
        printf("Type any letter in the terminal to add a new company.\n");
        return;
    }
    printf("The following companies are registered:\n");
    for (int i = 0; i < n; i++) {
        printf("Company: %s\n", companies[i].name);
    }
    printf("Type add in the terminal to add a new company.\n");
    printf("Type show and the number associated with the company to see the employees of that company ( indexing from 0 ).\n");
    printf("Type 'close' to close the program.\n");
}

#endif //PROIECT_PCLP_SISTEM_BANCAR_LIBRARY_H