# Symbol Table Implementation

## Overview
This project is an implementation of a simple symbol table using a hash table and scope management in C. The symbol table supports basic operations like creating new scopes, assigning values to variables, and printing the values of variables. The project consists of a single C file and an input file for testing.

## Features
- **Create New Scope:** Allows the creation of a new scope.
- **Assign Values:** Assigns values to variables within the current scope.
- **Print Values:** Prints the value of a specified variable, searching through all active scopes.
- **Delete Scope:** Deletes the current scope and frees associated memory.

## Files
- `symboltable.c`: The main implementation of the symbol table.
- `symboltable_input.txt`: Input file used for testing the symbol table implementation.

## Functions

### Symbol Table Functions

1. **`Symbol_Node *Create_New_Symbol(char var[], int value)`**
   - Creates a new symbol node with the given variable name and value.
   
2. **`int getKey(char var[])`**
   - Generates a hash key for the given variable name.
   
3. **`Scope_Node *Create_New_Scope(Scope_Node **curr_scope)`**
   - Creates a new scope and links it to the current scope.
   
4. **`void just_assign(Scope_Node *curr_scope, char var[], int value)`**
   - Assigns a value to a variable within the current scope.
   
5. **`Scope_Node *delete_curr_scope(Scope_Node **curr_scope)`**
   - Deletes the current scope and frees the associated memory.
   
6. **`void print(Scope_Node *curr_scope, char var[])`**
   - Prints the value of the specified variable, searching through all active scopes.

## Input File Format
The `symboltable_input.txt` file contains a series of commands to manipulate the symbol table. The supported commands are:

- `begin`: Creates a new scope.
- `assign <variable> <value>`: Assigns a value to a variable.
- `print <variable>`: Prints the value of the specified variable.
- `end`: Deletes the current scope.

### Example Input File (`symboltable_input.txt`)

```plaintext
begin 
    assign a 1
    assign b 2
    begin
        assign a 3
        assign c 4
        print b
        begin
            assign c 5
            print b
            print a
            print c
        end
        print a
        print c
    end
    print a
end
```

## Author
Sumedh Ganpatye
