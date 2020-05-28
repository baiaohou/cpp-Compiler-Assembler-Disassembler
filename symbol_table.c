#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "find_symbols.c"

// Please do not change these!
extern char* function_name;
extern char* parameter_names[10];
extern char* variable_names[10];
extern int parse_function_header(char*);
extern int parse_line(char*);

typedef struct Node node;
struct Node{
    char* symbol;
    int offset;
    node* next;
};

node* symbol_table = NULL;

/*
 * THIS IS THE STARTER CODE FOR PART 2
 */

int add_symbol(char* symbol, int offset) {
  // IMPLEMENT THIS IN STEP 1
    if (symbol == NULL || strlen(symbol) == 0) return -1;
    
    // if symbol_table is empty, first initilize a node
    if (symbol_table == NULL) {
        symbol_table = malloc(sizeof(node));
        symbol_table->symbol = malloc(sizeof(strlen(symbol)+1));
        strcpy(symbol_table->symbol, symbol);
        symbol_table->offset = offset;
        symbol_table->next = NULL;
        return 1; // success
    }
    
    node* fl = NULL;
    fl = symbol_table;
    
    do {
        if (strcmp(symbol, fl->symbol) == 0) {
            //printf("hey\n");
            return 0;
        }
        fl = fl->next;
    } while (fl != NULL);
    
    

    
    // if symbol_table is not empty, find the next and add the new data
    
    node* flag = NULL;
    flag = symbol_table;

    while (flag->next != NULL) {
        
        flag = flag->next;
        
    }
    
    // new node
    node* new = malloc(sizeof(node));
    new->symbol = malloc(sizeof(strlen(symbol)+1));
    strcpy(new->symbol, symbol);
    new->offset = offset;
    new->next = NULL;
    
        
    // point current next to new
    flag->next = new;
    
    
    
    //test
    node* test = symbol_table;
    do {
        //printf("Now:\n[%s]\n", test->symbol);
        //printf("[%d]\n", test->offset);
        //printf("[%p]\n", test->next);
        test = test->next;
    } while (test != NULL);
    
    
    
    return 1; // success
}

int get_offset(char* symbol, int* offset) {
  // IMPLEMENT THIS IN STEP 1
    if (symbol == NULL || strlen(symbol) == 0 || offset == NULL) return -1;
  
    node* flag = symbol_table;
    
    while (flag != NULL) {
        //printf("[%s]\n", flag->symbol);
        if (strcmp(flag->symbol, symbol) == 0) {
            *offset = flag->offset;
            return 1; // success
        }
        
        flag = flag->next;
    }
   
    return 0; // no such symbol
}

void clear() {
  // IMPLEMENT THIS IN STEP 1
    
    node* node = NULL;
    while (symbol_table != NULL) {
        node = symbol_table;
        if (node->symbol != NULL) {
            free(node->symbol);
            //printf("freed label string\n");
        }

        symbol_table = node->next;
        free(node);
        //printf("freed 1 node\n");
    }
    //printf("[%s]!\n", symbol_table);
    //printf("cleaned!\n");
	return ;
    
    
    /**
    
    while (symbol_table != NULL) {
        node* flag = symbol_table;
        
        do {
           test = flag;
           flag = flag->next; 
        } while (flag != NULL);
        
        
        printf("oho!\n");
    }
    
    
    **/
}

int populate_symbol_table(char* filename) {
  // IMPLEMENT THIS IN STEP 2
    if (filename == NULL) return -1;
    FILE *f = fopen(filename, "r");
    if (f == NULL) return -1;
    
    char* temp = NULL;
    temp = malloc(sizeof(char)*100);
    temp = fgets(temp, 100, f);
    //printf("[%s]\n", temp);
    parse_function_header(temp);
    //printf("testing[%s]\n", parameter_names[0]);
    //printf("testing[%s]\n", parameter_names[1]);
    //printf("testing[%d]\n", parameter_names[2]);
    free(temp);
    
    int i = 0;
    int j = 4; // initilize offset = +4
    for (; i < 10; i++) {
        if (parameter_names[i] != NULL) {
            int p = 0;
			p = add_symbol(parameter_names[i], j);
			if (p != 1) return -1; // error in populating symbol_table
            j++;
        }
    }
    
    
    //printf("aloha\n");
        
    
    j = 0; // initilize offset = 0
    do {
        temp = malloc(sizeof(char)*100);
        temp = fgets(temp, 100, f);
        //printf("[%s]\n", temp);   
        if (temp == NULL) {
            free(temp);
            break;
        } else {
            // cleaning variable_names table
            for (i = 0; i < 10; i++) {
                if (variable_names[i] != NULL) free(variable_names[i]);
            }  
            
            parse_line(temp);
            free(temp);
            for (i = 0; i < 10; i++) {
                if (variable_names[i] != NULL) {
                    int q = 0;
					q = add_symbol(variable_names[i], j);
					if (q != 1) return -1; // error in populating symbol_table
                    j--;
                }
            }
        }
 
    } while (1);
    
    
    /**
    printf("nihao!!!\n");
    printf("[%s]", symbol_table->symbol);
    printf("[%d]\n", symbol_table->offset);
    //printf("[%s]\n", symbol_table->next);
    printf("[%s]", symbol_table->next->symbol);
    printf("[%d]\n", symbol_table->next->offset);  
    //printf("[%s]\n", symbol_table->next->next);
    //
    printf("[%s]", symbol_table->next->next->symbol);
    printf("[%d]\n", symbol_table->next->next->offset);
    printf("[%s]", symbol_table->next->next->next->symbol);
    printf("[%d]\n", symbol_table->next->next->next->offset);       
    printf("[%s]", symbol_table->next->next->next->next->symbol);
    printf("[%d]\n", symbol_table->next->next->next->next->offset);       
    printf("[%s]", symbol_table->next->next->next->next->next->symbol);
    printf("[%d]\n", symbol_table->next->next->next->next->next->offset); 
    **/
 

    
    for (i = 0; i < 10; i++) {
        if (variable_names[i] != NULL) free(variable_names[i]);
    }  

    
    fclose(f);
    return 1;
}
