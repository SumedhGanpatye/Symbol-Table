// Created by Sumedh Ganpatye Date 15/03 19:49 
//completed 15/03 23:01  approx 4 hours

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define HASH_SIZE 101
#define BUFFER_SIZE 10

typedef struct Symbol_Node_Tag
{
    struct Symbol_Node_Tag *symbol_next;
    char name[BUFFER_SIZE];
    int value;
} Symbol_Node;

typedef struct Scope_Node_Tag
{
    struct Scope_Node_Tag *next;
    Symbol_Node *hash_arr[HASH_SIZE];
} Scope_Node;

Symbol_Node *Create_New_Symbol(char var[], int value)
{
    //name and its value
    Symbol_Node *new_symbol = (Symbol_Node *)malloc(sizeof(Symbol_Node));
    strcpy(new_symbol->name, var);
    new_symbol->value = value;
    new_symbol->symbol_next = NULL;
    return new_symbol;
}

int getKey(char var[])
{
    int h = 0;
    for (int i = 0; i < strlen(var); i++)
    {
        h = h + var[i] * (i + 1);
    }
    return h % HASH_SIZE;
}

Scope_Node *Create_New_Scope(Scope_Node **curr_scope)
{
    // new link in liked list node i.e scope
    Scope_Node *new_Scope = (Scope_Node *)malloc(sizeof(Scope_Node));
    for (int i = 0; i < HASH_SIZE; i++)
    {
        new_Scope->hash_arr[i] = NULL;
    }
    new_Scope->next = (*curr_scope);
    (*curr_scope) = new_Scope;

    return (*curr_scope);
}

void just_assign(Scope_Node *curr_scope, char var[], int value)
{
    int key = getKey(var);

    Symbol_Node *new_symbol = Create_New_Symbol(var, value);
    Symbol_Node *temp = curr_scope->hash_arr[key];
    if (temp != NULL)
    {
        while (temp->symbol_next != NULL)
        {
            temp = temp->symbol_next;
        }
        temp->symbol_next = new_symbol;
    }
    else
    {
        curr_scope->hash_arr[key] = new_symbol;
    }
}

Scope_Node *delete_curr_scope(Scope_Node **curr_scope)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        Symbol_Node *temp = (*curr_scope)->hash_arr[i];
        while (temp != NULL)
        {
            Symbol_Node *next = temp->symbol_next;
            free(temp);
            temp = next;
        }
    }
    Scope_Node *del = (*curr_scope);
    (*curr_scope) = (*curr_scope)->next;
    del->next = NULL;
    free(del);
    return (*curr_scope);
}

void print(Scope_Node *curr_scope, char var[])
{
    Scope_Node *temp_scope = curr_scope;
    int found = 0;
    int key = getKey(var);
    while (temp_scope != NULL && !found)
    {
        Symbol_Node *temp_symb = temp_scope->hash_arr[key];
        while (temp_symb != NULL && !found)
        {
            if (strcmp(temp_symb->name, var) == 0)
            {
                printf("%s = %d found\n", temp_symb->name, temp_symb->value);
                found = 1;
            }
            temp_symb = temp_symb->symbol_next;
        }
        temp_scope = temp_scope->next;
    }
    if (!found)
    {
        printf("%s is not present in program\n", var);
    }
    return;
}

int main() 
{
    Scope_Node *curr_scope = NULL;
    FILE *fp = fopen("symboltable_input.txt", "r");
    char ch[BUFFER_SIZE];
    int value;
    while (fscanf(fp, "%s", ch) == 1)
    {
        // printf("file input %s\t", ch);
        if (strcmp(ch, "begin") == 0)
        {
            printf("Creating new hash\n");
            curr_scope = Create_New_Scope(&curr_scope);
        }
        else if (strcmp(ch, "assign") == 0)
        {
            fscanf(fp, "%s", ch);
            fscanf(fp, "%d", &value);
            just_assign(curr_scope, ch, value);
        }
        else if (strcmp(ch, "print") == 0)
        {
            fscanf(fp, "%s", ch);
            print(curr_scope, ch);
        }
        else if (strcmp(ch, "end") == 0)
        {
            printf("deleting curr hash\n");
            curr_scope = delete_curr_scope(&curr_scope);
        }
    }
    fclose(fp);

    return 0;
}