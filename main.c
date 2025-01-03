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
int id[1001];



void initialize_companies() {
    FILE *file = fopen("companies.txt", "r");
    if (file == NULL) {
        perror("Failed to open companies.txt");
        return;
    }

    scanf("%d", &num_companies);




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
        if (company_index < 0 || company_index >= num_companies) {
            fprintf(stderr, "Invalid company index\n");
            continue;
        }
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
        printf("Type add in the terminal to add a new company.\n");
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

void add_company() {
    char name[50];
    printf("\nType the name of the company you want to add:\n");
    scanf("%s", name);
    strcpy(companies[num_companies].name, name);
    companies[num_companies].number_of_employees = 0;
    printf("\nType how many employees you want to add to the company:\n");
    int number_of_employees;
    scanf("%d", &number_of_employees);
    companies[num_companies].number_of_employees = number_of_employees;
    printf("\nType the employees of the company ( names ):\n");
    for (int i = 0; i < number_of_employees; i++) {
        char name[50];
        scanf("%s", name);
        strcpy(companies[num_companies].employees[i].name, name);
    }
    printf("Type the roles of the employees:\n");
    for (int i = 0; i < number_of_employees; i++) {
        char role[50];
        scanf("%s", role);
        strcpy(companies[num_companies].employees[i].role, role);
    }
    printf("Type the salaries of the employees:\n");
    for (int i = 0; i < number_of_employees; i++) {
        int salary;
        scanf("%d", &salary);
        companies[num_companies].employees[i].salary = salary;
    }
    printf("Type if the employees are retired or not ( 1 for retired, 0 for not retired ):\n");
    for (int i = 0; i < number_of_employees; i++) {
        int is_retired;
        scanf("%d", &is_retired);
        companies[num_companies].employees[i].is_retired = is_retired;
    }

    num_companies++;
    printf("Company %s added successfully.\n", name);
}

int main(void) {

    while(true) {
        initialize_companies();
        initialize_employees();
        show_companies();
        char command[50];
        scanf("%s", command);
        if(command == "close")
            return 0;
        if(command == "add")
            add_company();



    }

}