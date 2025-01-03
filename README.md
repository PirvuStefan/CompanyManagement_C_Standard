## Company Management Program

This project is a simple company management system written in C. 
It allows you to manage companies and their employees, including adding new companies and displaying information about existing companies and their employees.

## Features 🔌

Add new companies and their employees.
Display a list of registered companies.
Show detailed information about the employees of a specific company.
Show only non-retired employees of a specific company.

## Files

main.c: The main source code file containing the implementation of the company management system.
companies.txt: A file containing the list of companies.
companies_number_of_employees.txt: A file containing the number of employees for each company.
employees.txt: A file containing the details of employees.

## How to Use

Compile the code:  
gcc -o company_management main.c

Run the program:  
./company_management

## Commands: 

help: Display the list of available commands.
add: Add a new company and its employees.
show <index>: Show the employees of the company at the specified index.
show-r <index>: Show only non-retired employees of the company at the specified index.
show-l: Show the list of all registered companies.
close: Close the program.

## License

This is done strictly for a college project.
If it was not obvious, this project is licensed under the MIT License.You can do whatever you want with it, modify it, distribute it.
