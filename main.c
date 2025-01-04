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

    char buffer[10];
    if (fgets(buffer, sizeof(buffer), file) != NULL) {
        num_companies = atoi(buffer);
    }

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
        if (fgets(buffer, sizeof(buffer), file) != NULL) {
            companies[i].number_of_employees = atoi(buffer);
        }
    }

    fclose(file);
}

void initialize_employees() {
    FILE *file = fopen("employees.txt", "r");
    if (file == NULL) {
        perror("Failed to open employees.txt");
        return;
    }

    char buffer[10];
    char name[50], role[50];
    int id, salary, is_retired;



        for(int company_index = 0; company_index < num_companies;company_index++){

        for (int i = 0; i < companies[company_index].number_of_employees; i++) {

            fscanf(file, "%d\n", &id);
            fgets(name, sizeof(name), file);
            name[strcspn(name, "\n")] = 0; // Remove newline character
            fgets(role, sizeof(role), file);
            role[strcspn(role, "\n")] = 0; // Remove newline character
            fscanf(file, "%d\n", &salary);
            fscanf(file, "%d\n", &is_retired);

            struct employee employee;
            employee.id = id;
            strcpy(employee.name, name);
            strcpy(employee.role, role);
            employee.salary = salary;
            employee.is_retired = is_retired;
            companies[company_index].employees[i] = employee; // Initialize employee id

        }



    }

    fclose(file);
}

void show_companies() {
    if (num_companies == 0) {
        printf("There are no companies registered at the moment.\n");
        printf("Type add in the terminal to add a new company.\n");
        return;
    }
    printf("The following companies are registered:\n");
    for (int i = 0; i < num_companies; i++) {
        printf("Company: %s\n", companies[i].name);
    }

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
    printf("\nType the employees of the company (names):\n");
    for (int i = 0; i < number_of_employees; i++) {
        char name[50];
        scanf("%s", name);
        strcpy(companies[num_companies].employees[i].name, name);
        int test = 100000 + rand() % 900000;
        test = test + rand() % 7;
        test = test + rand() % 11;
        test = test + companies[num_companies].employees[i].name[0];
        // to make true random id ( at least closer than before)
        // flaws: rand() is not truly random, it is pseudo-random
        while(true) {
            int ok = 1;
            for(int j = 0; j < num_companies; j++){
                for(int k = 0; k < companies[j].number_of_employees; k++){
                    if(companies[j].employees[k].id == test){
                        ok = 0;
                        break;
                    }
                }
                if(ok == 0) break;
            }
            if(ok){
            companies[num_companies].employees[i].id = test; // Initialize employee id
                break;
        }
    } // id generation (not perfect)
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
    printf("Type if the employees are retired or not (1 for retired, 0 for not retired):\n");
    for (int i = 0; i < number_of_employees; i++) {
        int is_retired;
        scanf("%d", &is_retired);
        companies[num_companies].employees[i].is_retired = is_retired;
    }
    FILE *file = fopen("companies_number_of_employees.txt", "a");
    if (file == NULL) {
        perror("Failed to open companies_number_of_employees.txt");
        return;
    }
    fprintf(file, "%d", number_of_employees);
    fclose(file);
    num_companies++;

    file = fopen("employees.txt", "a");
    if (file == NULL) {
        perror("Failed to open employees.txt");
        return;
    }
    for (int i = 0; i < number_of_employees; i++) {
        fprintf(file, "%d\n%s\n%s\n%d\n%d\n", companies[num_companies - 1].employees[i].id, companies[num_companies - 1].employees[i].name, companies[num_companies - 1].employees[i].role, companies[num_companies - 1].employees[i].salary, companies[num_companies - 1].employees[i].is_retired);
    }
    fclose(file);
   // file = fopen("companies.txt", "a");
    //fprintf(file, "\n%s", name);
    //fclose(file);
    printf("Company %s added successfully.\n", name);

    file = fopen("companies.txt", "r+");
    fseek(file, 0, SEEK_SET);
    fprintf(file, "%d\n", num_companies);
    fseek(file, 0, SEEK_END);
    fprintf(file, "%s\n", name);
    fclose(file);
}

void commanding(void) {
    printf("Welcome to the company management system!\n");
    printf("Here are the commands you can use:\n\n");
    printf("close - to close the program\n");
    printf("add  - to add a company\n");
    printf("show - to show the employees of a company ( followed by the number associated with the company )\n");
    printf("show-r - to only show the non-retired employees of a company (followed by the index )\n");
    printf("show-l - to show all the companies names\n");
    printf("delete - to delete a company ( followed by the index )\n");

}

void delete_company(int index) {
    if (index < 0 || index >= num_companies) {
        printf("Invalid index.\n");
        return;
    }

    for (int i = index; i < num_companies - 1; i++) {
        companies[i] = companies[i + 1];
    }
    num_companies--;

    // Update the companies.txt file
    FILE *file = fopen("companies.txt", "w");
    if (file == NULL) {
        perror("Failed to open companies.txt");
        return;
    }
    fprintf(file, "%d\n", num_companies);
    for (int i = 0; i < num_companies; i++) {
        fprintf(file, "%s\n", companies[i].name);
    }
    fclose(file);

    // Update the companies_number_of_employees.txt file
    file = fopen("companies_number_of_employees.txt", "w");
    if (file == NULL) {
        perror("Failed to open companies_number_of_employees.txt");
        return;
    }
    for (int i = 0; i < num_companies; i++) {
        fprintf(file, "%d\n", companies[i].number_of_employees);
    }
    fclose(file);

    // Update the employees.txt file
    file = fopen("employees.txt", "w");
    if (file == NULL) {
        perror("Failed to open employees.txt");
        return;
    }
    for (int i = 0; i < num_companies; i++) {
        for (int j = 0; j < companies[i].number_of_employees; j++) {
            fprintf(file, "%d\n%s\n%s\n%d\n%d\n", companies[i].employees[j].id, companies[i].employees[j].name, companies[i].employees[j].role, companies[i].employees[j].salary, companies[i].employees[j].is_retired);
        }
    }
    fclose(file);

    printf("Company deleted successfully.\n");
}
int main(void) {
    initialize_companies();
    initialize_employees();
    //show_companies();
    printf("Type 'help' to see the commands you can use.\n");


    while (true) {
        initialize_companies();
        initialize_employees();
        char command[50];
        scanf("%s", command);
        if (strcmp(command, "close") == 0)
            return 0;
        if(strcmp(command, "help") == 0){
        commanding();
        continue;
        }
        if (strcmp(command, "add") == 0)
            add_company();
        else if(strcmp(command, "show") == 0){
            int index;
            scanf("%d", &index);
            if(index >= num_companies){
                printf("Invalid index.\n");
                continue;
            }
            printf("The employees of the company %s are:\n", companies[index].name);
            for(int i = 0; i < companies[index].number_of_employees; i++){
                printf("Employee %d:\n", i + 1);
                printf("Name: %s\n", companies[index].employees[i].name);
                printf("Role: %s\n", companies[index].employees[i].role);
                printf("Salary: %d\n", companies[index].employees[i].salary);
                if(companies[index].employees[i].is_retired == 1)
                    printf("Retired: Yes\n");
                else
                    printf("Retired: No\n");
            }
        }
        else if(strcmp(command, "show-r") == 0){
            int index;
            scanf("%d", &index);
            if(index >= num_companies){
                printf("Invalid index.\n");
                continue;
            }
            int i;
            for(i = 0; i < companies[index].number_of_employees; i++){
                if(companies[index].employees[i].is_retired == 0) break;
            }
            if(i == companies[index].number_of_employees){
                printf("There are only retired employees in the company %s.\n", companies[index].name);
                continue;
            } // if the loop is not broken, then all the employees are retired
            printf("The employees still active of the company %s are:\n", companies[index].name);
            for(int i = 0; i < companies[index].number_of_employees; i++) {
                if(companies[index].employees[i].is_retired == 0){
                printf("Employee %d:\n", i + 1);
                printf("Name: %s\n", companies[index].employees[i].name);
                printf("Role: %s\n", companies[index].employees[i].role);
                printf("Salary: %d\n", companies[index].employees[i].salary);
            }
            }
        }
        else if(strcmp(command, "show-l") == 0){
            show_companies();
        }
        else if(strcmp(command, "delete") == 0){
            int index;
            scanf("%d", &index);
            delete_company(index);
        }
        else printf("Unknown command. Type 'help' to see the commands you can use.\n");

    }
}