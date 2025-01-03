#include "library.h"
#include <stdbool.h> // or #define boolean int
#include <stdio.h>
#include <stdlib.h>
/*Datele angajaților trebuie păstrate în orice companie. Fiecare companie are un angajat cu un ID
unic de angajat, rol de angajat etc. Toate aceste date sunt păstrate într-un sistem de management
al angajaților, unde sunt stocate toate datele despre fiecare angajat, putem prelua, actualiza și
adăuga date la acest sistem. Folosind C putem crea un sistem de management al angajaților care
poate îndeplini toate aceste sarcini, folosind cunoștințe de bază C precum șir, matrice, fișier etc.
Funcționalitatea Sistemului de management al angajaților este:
Realizați tabelul cu angajați.
Inserați intrări noi.
Ștergeți intrările.
Căutați o înregistrare.*/

int main(void) {
    int n;
    scanf("%d", &n); // number of companies
    struct company *companies = malloc(n * sizeof(struct company));
    for (int i = 0; i < n; i++) {
        scanf("%s", companies[i].name); // read company name
        scanf("%d", &companies[i].number_of_employees); // read number of employees
        companies[i].employees = malloc(companies[i].number_of_employees * sizeof(struct employee));
        for (int j = 0; j < companies[i].number_of_employees; j++) {
            int id, salary;
            char name[50], role[50];
            bool is_retired;
            scanf("%d %s %s %d %d", &id, name, role, &salary, &is_retired);
            initialize_employee(&companies[i].employees[j], id, name, role, salary, is_retired);
        }
    }
    // Free allocated memory (not shown here)

    while(true) {
        show_companies(companies, n);
        char command[50];
        scanf("%s", command);
        if (strcmp(command, "close") == 0) {
            return 0;
        }
        if (strcmp(command, "add") == 0) {
            // Add a new company
            n++;
            companies = realloc(companies, n * sizeof(struct company));
            scanf("%s", companies[n - 1].name); // read company name
            scanf("%d", &companies[n - 1].number_of_employees); // read number of employees
            companies[n - 1].employees = malloc(companies[n - 1].number_of_employees * sizeof(struct employee));
            for (int j = 0; j < companies[n - 1].number_of_employees; j++) {
                int id, salary;
                char name[50], role[50];
                bool is_retired;
                scanf("%d %s %s %d %d", &id, name, role, &salary, &is_retired);
                initialize_employee(&companies[n - 1].employees[j], id, name, role, salary, is_retired);
            }
        }
        if (strcmp(command, "show") == 0) {
            // Show employees of a company
            int index;
            scanf("%d", &index);
            for (int i = 0; i < companies[index].number_of_employees; i++) {
                printf("Employee %d: %s\n", i, companies[index].employees[i].name);
            }
        }
    }

}
