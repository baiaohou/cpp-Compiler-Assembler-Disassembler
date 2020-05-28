#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * These are the global variables that you need to populate in the functions below.
 * Please do not change these variables' names or types!
 */
char* function_name;
char* parameter_names[10];
char* variable_names[10];

/*
 * This is the function you need to implement for Part 1.
 * You must NOT change its signature! 
 */

int header_check(char* header){
	// helper fc1: sig check
	
	int sig_nothing_flag = 0;
	int curly_brace_flag = 0;
	
	char* head = malloc(sizeof(char) * (strlen(header)+1));
    head = strcpy(head, header);
	const char s[10] = " ";
	char* token = NULL;
	token = strtok(head, s);
	//printf("[%s]\n", token);  // int (1st)
	
    //free(head); // <--------
    
	if (strcmp(token, "int") == 0 || strcmp(token, "void") == 0) {
		token = strtok(NULL, s);
		//printf("[%s]\n", token); // fun (2nd)
		
		if (strcmp(token, "(") == 0) {
            
            return -1; // 2nd arg cannot be (
        }
		char temp[100];
		strcpy(temp, token);
		if ('0' < temp[0] && temp[0] < '9') return -1; // cannot begin with digit
		
		token = strtok(NULL, s);
		//printf("[%s]\n", token); // ( (3rd)
		if (strcmp(token, "(") != 0) return -1; // must be (
	} else {
		// sig = nothing
		char temp[100];
		strcpy(temp, token);
		if ('0' < temp[0] && temp[0] < '9') return -1; // cannot begin with digit
		
		token = strtok(NULL, s);
		//printf("[%s]\n", token); // ( (2nd)
		if (strcmp(token, "(") != 0) return -1; // must be (
		
		sig_nothing_flag = 100;
		
		////return 100; /////////////////
	}
	
	int loop = 0;
	
	while (token != NULL){
		loop++; // flag
		token = strtok(NULL, s);
		/**
		if (strcpy(token, "{") == 0) {
			curly_brace_flag = 100;
			token = strtok(NULL, s);
			if (token != NULL) return -1;
		}	
		**/
		
		//printf("now is [%s]\n", token); 
		
		// int fun0 ( ) -> legal
		
		if (strcmp(token, ")") == 0 && loop == 1) {
			token = strtok(NULL, s);
			if (token == NULL) break;
			if (strcmp(token, "{") == 0) break;
			return -1;
		}
		
		
		
		if (strcmp(token, "int") != 0) return -1;
		
		token = strtok(NULL, s);
		if (token == NULL) break;
		//printf("now is [%s]\n", token); 
		char temp[100];
		strcpy(temp, token);
		if ('0' < temp[0] && temp[0] < '9') return -1; // cannot begin with digit		
		
		token = strtok(NULL, s);
		if (token == NULL) break;
		if (strcmp(token, ",") == 0 || strcmp(token, ")") == 0) {
			if (strcmp(token, ")") == 0) {
				token = strtok(NULL, s);
				if (token == NULL) break;
				if (strcmp(token, "}")) {
					curly_brace_flag = 100;
					break;
				} else {
					return -1;
				}
			}
			continue;
		} else {
			
			return -1;
		}
	}
	//if (curly_brace_flag != 100) return -1;
	if (sig_nothing_flag == 100) return 100;
	return 1;
}





int parse_function_header(char* header) {
  if (header == NULL) return -1;

  // WRITE THE REST OF THIS FUNCTION!
  
	int a = 1; // legal: return 1;
	a = header_check(header);
	
	//printf("return value is %d\n", a);
	
	if (a == -1) {
		//printf("illegal. 886\n");
		return 0;
	}
	
	
	// get modifible header, name it head
   
    char* head = malloc(sizeof(char) * (strlen(header)+1));
    head = strcpy(head, header);
    
    //printf("[PRINTING:] %s\n", head);
    const char s[10] = " (),{\n";
    char* token = NULL;
    
	
	if (a == 1) {
		
    // get 1st token -- int
    token = strtok(head, s); // token -> "int"
    //printf("[token is] %s\n", token);
    
    // get function name and store it in function_name
    token = strtok(NULL, s);
    //printf("[fc  name] %s\n", token);
    function_name = malloc(sizeof(char)*(strlen(token)+1));
    function_name = strcpy(function_name, token);
    //printf("[fc  name] %s\n", function_name);
		
	} else if (a == 100) {
		
	// get 1st token -- int
    token = strtok(head, s); // token -> "int"

    function_name = malloc(sizeof(char)*(strlen(token)+1));
    function_name = strcpy(function_name, token);
    //printf("[fc  name] %s\n", function_name);
		
		
	} else {
		//free(head);
		return 0;
	}
	
	
    token = strtok(NULL, s);
    //free(head);
    int i = 0;
    while(token != NULL) {
        int cmp = 0;
        cmp = strcmp(token, "int");
        if (cmp == 0) {
            token = strtok(NULL, s);
            continue;
        }
        parameter_names[i] = malloc(sizeof(char)*(strlen(token)+1));
        parameter_names[i] = strcpy(parameter_names[i], token);
        //printf("[para] %d - %s\n", i, parameter_names[i]);
        i++;
        token = strtok(NULL, s);
    }
    
    // implementing the remainings
    for (; i < 10; i++) {
        parameter_names[i] = NULL;
        //printf("[para] %d - %s\n", i, parameter_names[i]);
    }
    //free(head);
  // Be sure to return the correct value.
  return 1;
}




int line_check_semicolon(char* line) {
    char* head = malloc(sizeof(char) * (strlen(line)+1));
    head = strcpy(head, line);
	const char s[10] = " \n";
	char* token = NULL;
	token = strtok(head, s);
	//printf("[%s]\n", token);  // int (1st)
    char* flag = NULL;
  
    while (token != NULL) {
        flag = token;
        token = strtok(NULL, s);
        //printf("[%s]\n", token);  // int (1st)
    }
    //printf("[%s]\n", flag);  // int (1st)
    
	//free(head);
    if (strcmp(flag, ";") != 0) return -1;
    //printf("return value 1\n");
    return 1;
}

int line_begin_int(char* line) {
    //printf("line_begin_int TEST!!!\n");
    char* head = malloc(sizeof(char) * (strlen(line)+1));
    head = strcpy(head, line);
	const char s[10] = " ;\n";
	char* token = NULL;
	token = strtok(head, s);
	//printf("[%s]\n", token);  // int (1st)
    if (strcmp(token, "int") != 0) {
        if (strcmp(token, "return") == 0) return 200;
        return 100;
    }
    
   
    token = strtok(NULL, s);
    //printf("[%s]\n", token);
    if (token == NULL) return -1;
    if (strcmp(token, "void") == 0) return -1;
    
    token = strtok(NULL, s);
    //printf("[%s]\n", token); 
    
    if (token == NULL) return 1;
    if (strcmp(token, ",") != 0) {
        if (strcmp(token, "=") != 0) {
            return -1;
        }
        token = strtok(NULL, s);
        if (token == NULL) return -1;
        if (strcmp(token, ",") == 0) return -1;
        
        token = strtok(NULL, s);
        if (token == NULL) return 1; // int y = 3 ; valid
        if (strcmp(token, "+") != 0) return -1;
        
    }
    return 1;
}

int line_check_return(char* line){
    char* head = malloc(sizeof(char) * (strlen(line)+1));
    head = strcpy(head, line);
	const char s[10] = " ;\n";
    char* token = NULL;
	token = strtok(head, s);
	//printf("[%s]\n", token);  // return (1st)
    
    do {
        token = strtok(NULL, s);
        if (token == NULL) return -1; // return ; no!
        if (strcmp(token, "+") == 0) return -1; // return + 3 ; no!
            
        token = strtok(NULL, s);
        if (token == NULL) return 123; // return 3;  ok! return a; ok!
        
    } while (strcmp(token, "+") == 0);
}

int line_check_others(char* line){
    char* head = malloc(sizeof(char) * (strlen(line)+1));
    head = strcpy(head, line);
	const char s[10] = " ;\n";
    char* token = NULL;
	token = strtok(head, s);
	//printf("[%s]\n", token);  // return (1st)
    if (strcmp(token, "=") == 0) return -1;
    
    token = strtok(NULL, s); // '='
    if (strcmp(token, "=") != 0) return -1;
    
    do {
        token = strtok(NULL, s);
        if (token == NULL) return -1; // return ; no!
        if (strcmp(token, "+") == 0) return -1; // return + 3 ; no!
            
        token = strtok(NULL, s);
        if (token == NULL) return 456; // return 3;  ok! return a; ok!
        
    } while (strcmp(token, "+") == 0);
}

/*
 * This is the function you need to implement for Part 1.
 * You must NOT change its signature! 
 */
int parse_line(char* line) {
    
    if (line == NULL) return -1;
    int i = 0;
    for (; i < 10; i++){
        variable_names[i] = NULL;
    }
    
    int flag_semicol = 0;
    flag_semicol = line_check_semicolon(line);
    if (flag_semicol == -1) {
        //printf("no semicolon!\n");
        return 0;
    }
    
    int flag_int = 0;
    flag_int = line_begin_int(line);
    //printf("line_begin_int [return %d]\n", flag_int);
    
    if (flag_int == -1) {
        //printf("syntax error!\n");
        return 0;
    }
    // flag_int = 200: return; = 100: others
    if (flag_int == 200) {
        int flag_return = 0;
        flag_return = line_check_return(line);
        //printf("RETURN TEST [[[[%d]]]]\n", flag_return);
        if (flag_return == 123) return 1; //success, but not continue.
        return 0; //fail
    }
    
    if (flag_int == 100) {
        int flag_others = 0;
        flag_others = line_check_others(line);
        //printf("OTHERS TEST [[[[%d]]]]\n", flag_others);
        if (flag_others == 456) return 1; //success, but not continue
        return 0; //fail        
        
    }
    
    
  // WRITE THE REST OF THIS FUNCTION!
    //printf("Testing line: %s\n", line);
    char* line_str;
    line_str = malloc(sizeof(char) * (strlen(line) + 1));

    line_str = strcpy(line_str, line);
  
    const char s[10] = " ;=+\n";
    char* token = NULL;
    
    // get 1st token 
    token = strtok(line_str, s); 
    if (strcmp(token, "int") != 0) {
        if (strcmp(token, "return") != 0) {
            //printf("Error: first token is not int!\n");
            //free(line_str);
            return 0;   
        }

    }
    token = strtok(NULL, s);
    
    i = 0;
    variable_names[i] = malloc(sizeof(char)*(strlen(token)+1));
    variable_names[i] = strcpy(variable_names[i], token);
    
    i++;
    token = strtok(NULL, s);
     
  
    while (token != NULL) {
        int cmp = 0;
        cmp = strcmp(token, ",");
        while (cmp == 0) {
            token = strtok(NULL, s);
            variable_names[i] = malloc(sizeof(char)*(strlen(token)+1));
            variable_names[i] = strcpy(variable_names[i], token);
            //printf("[var] %d - %s\n", i, variable_names[i]);
            i++;
            break;
        }
        token = strtok(NULL, s);
    }
    
    for (; i < 10; i++){
        variable_names[i] = NULL;
        //printf("[var] %d - %s\n", i, variable_names[i]);
    }
    
    
    free(line_str);
    //printf("Yayyyyyyyyyy\n");
  // Be sure to return the correct value.
  return 1;

}

