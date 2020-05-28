#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#include "find_symbols.c"
//#include "symbol_table.c"


// Be sure not to change these function prototypes!

extern int get_offset(char*, int*);
extern int populate_symbol_table(char*);
extern int parse_function_header(char*);
extern int parse_line(char*);
extern int add_symbol(char*, int);

/*
 * THIS IS THE STARTER CODE FOR PART 3
 */

int good = 0;
int line_number = 1;

int main(int argc, char* argv[]) {
 
    printf("Welcome\n");
    if (argc < 2) {
        printf("Usage: compiler [input file]\n");
        exit(1);
    }

    char* filename = argv[1];
    
    // cast *output* as new file name
    // remove .c, and add .lc4
    char* copy = malloc(sizeof(char)*strlen(filename)+1);
    copy = strcpy(copy, filename);
    char* output = NULL;
    output = strtok(copy, ".");
    strcat(output, ".lc4");
     
    FILE *test = fopen(filename, "r");
    if (test == NULL) {
        printf("ERROR - [%s] FILE NOT FOUND.\n", filename);
        return -1;
    }
    // first, try to build the symbol table
    if (populate_symbol_table(filename) == 1) {
        
        // IMPLEMENT PART 3 HERE
        FILE* f = fopen(filename, "r");

        char* temp = NULL;
        temp = malloc(sizeof(char)*100);
        temp = fgets(temp, 100, f); // do not read first line
        //printf("1st  LINE: [%s]\n", temp);
        
        int type;
        // write a file prep
        FILE *fp;
        
        //fp = fopen(output, "w+"); 
        fp = fopen(output, "w+");  // <--------

        do {
            temp = malloc(sizeof(char)*100);
            temp = fgets(temp, 100, f);
            if (temp == NULL) {
                free(temp);
                break;
            } else {
                line_number++;
                //printf("THIS LINE: [%s]\n", temp);
                fputs("\n", fp);

                type = line_define_test1(temp); //[1/2/3/4/-1]
                // if type = 1 OR type = -1, we do nothing
                // DO NOTHING
                if (type == 1 || type == -1) continue;
                
                fputs("; ", fp);
                fputs(temp, fp);
                
                // if type = [2] DECLARATION
                if (type == 2) type2_helper(temp, fp);
                
                // if type = [3] DECLARATION AND INITIALIZATION
                if (type == 3) type3_helper(temp, fp);
                
                // if type = [4] RETURN STATEMENT
                if (type == 4) type4_helper(temp, fp);
                //printf("-----------------------------------\n");
                
                if (good != 0) {
                    printf("ERROR OCCURS IN LINE %d\n", line_number);
                    fclose(fp);
                    remove(output);
                    return -1; // fail
                }
                
            } 
        } while (1);
        fclose(fp);
    } else {
        printf("SYNTAX ERROR IN YOUR C FILE. CANNOT COMPILE.\n");
    }
    
    printf("Program done\n");

  return 0;
}

int line_define_test1(char* temp){
    char* line_str;
    line_str = malloc(sizeof(char)*(strlen(temp)+1));
    line_str = strcpy(line_str, temp);
    const char s[10] = " \n";
    char* token = NULL;
    token = strtok(line_str, s);
    //printf("token %s\n", token);
    
    if (strcmp(token, "return") == 0) {
        //printf("[4] RETURN STATEMENT \n");
        free(line_str);
        return 4;
    }
    
    if (strcmp(token, "}") == 0) {
        //printf("[-1] '}' \n");
        free(line_str);
        return -1;
    }    
    
    while (token != NULL) {
        //printf("Hello\n");
        //free(token);
        //token = malloc(sizeof(char)*100);
        token = strtok(NULL, s);
        //printf("token %s\n", token);
        if (token == NULL) break; 
        
        if (strcmp(token, "=") == 0) {
            //printf("has '=', goto next test \n");
            free(line_str);
            return line_define_test2(temp); // Goto next test
        }    
        //printf("emm\n");
    }
    //printf("[1] SIMPLE DECLARATION \n");
    free(line_str);
    return 1;
}

int line_define_test2(char* temp){
    char* line_str;
    line_str = malloc(sizeof(char)*(strlen(temp)+1));
    line_str = strcpy(line_str, temp);
    const char s[10] = " \n";
    char* token = NULL;
    
    token = strtok(line_str, s);
    if (strcmp(token, "int") == 0) {
        //printf("[3] DECLARATION AND INITIALIZATION \n");
        free(line_str);
        return 3;
    }
    
    while (token != NULL) {
        token = strtok(NULL, s);
        if (token == NULL) break;
        if (strcmp(token, "int") == 0) {
            //printf("[3] DECLARATION AND INITIALIZATION \n");
            free(line_str);
            return 3;
        }    
    }
    //printf("[2] DECLARATION \n");
    free(line_str);
    return 2;
}

int type2_helper(char* temp, FILE* fp){
    char* line_str;
    line_str = malloc(sizeof(char)*(strlen(temp)+1));
    line_str = strcpy(line_str, temp);
    const char s[10] = " +=;\n";
    char* token = NULL;
    
    // 1st var
    token = strtok(line_str, s); 
    char* lhs = malloc(sizeof(char)*(strlen(token)+1));
    lhs = strcpy(lhs, token);
    //printf("lhs var: [%s]\n", lhs);
    
    // right-hand-side vars
    int count = 0;
    //fputs("; ", fp);
    //fputs(temp, fp);
    
    ////
    do {
        
        token = strtok(NULL, s);
        if (token == NULL) break;
        //printf("token:[%s]", token);
        int offset = -1000;
        char number[5];
        number[0] = 0;
        number[1] = 0;
        number[2] = 0;
        int mark = -1000;
        
        
        if (strcmp(token, "0") == 0) {
            mark = 0;            
        }    
        //const char *str = "12345"; 
        char* just = malloc(sizeof(char)*strlen(token)+1);
        just = strcpy(just, token);
        int ret = 10000; 
        sscanf(just, "%d", &ret); 
        if (ret != 0 && ret < 1000) mark = 0;
        //printf("\nThe value of ret : [%s]-[%d]\n", token, ret); 
                
        
        
        if (strcmp(token, "0") == 0) {
            number[0] = '0';
            mark = 0;
        } else if (strcmp(token, "1") == 0) {
            number[0] = '1';
            mark = 0;
        } else if (strcmp(token, "2") == 0) {
            number[0] = '2';
            mark = 0;
        } else if (strcmp(token, "3") == 0) {
            number[0] = '3';
            mark = 0;
        } else if (strcmp(token, "4") == 0) {
            number[0] = '4';
            mark = 0;
        } else if (strcmp(token, "5") == 0) {
            number[0] = '5';
            mark = 0;
        } else if (strcmp(token, "6") == 0) {
            number[0] = '6';
            mark = 0;
        } else if (strcmp(token, "7") == 0) {
            number[0] = '7';
            mark = 0;
        } else if (strcmp(token, "8") == 0) {
            number[0] = '8';  
            mark = 0;
        } else if (strcmp(token, "9") == 0) {
            number[0] = '9';
            mark = 0;
        } else if (strcmp(token, "10") == 0) {
            number[0] = '1';
            number[1] = '0';
            mark = 0;
        } else if (strcmp(token, "11") == 0) {
            number[0] = '1';
            number[1] = '1';
            mark = 0;
        } else if (strcmp(token, "12") == 0) {
            number[0] = '1';
            number[1] = '2';
            mark = 0;
        } else if (strcmp(token, "13") == 0) {
            number[0] = '1';
            number[1] = '3';
            mark = 0;
        } else if (strcmp(token, "14") == 0) {
            number[0] = '1';
            number[1] = '4';
            mark = 0;
        } else if (strcmp(token, "15") == 0) {
            number[0] = '1';
            number[1] = '5';
            mark = 0;
        } else {
            //printf("#####it's a letter / big num #####\n");
        }
        
        
        
        if (mark == 0) { // indicating this is a number
            //printf("#####TRUE: this is a number#####\n");
            // AND R0, R0, #0
            fputs("AND ", fp);
            fputs("R", fp);
            char snum[5];
            snum[0] = count + 48;
            snum[1] = 0;    
            ////printf("test!\n");
            //printf("\n[baiaohou]The value of token : [%s]\n", token); 
            fputs(snum, fp);//snum <-------
            
           // printf("test!\n");
            fputs(", ", fp);
            fputs("R", fp);
            fputs(snum, fp);//snum <-------
            fputs(", ", fp);
            fputs("#0", fp);
            fputs("\n", fp);             
            
            // ADD R0, R0, #<value>
            fputs("ADD ", fp);
            fputs("R", fp);
            snum[0] = count + 48;
            snum[1] = 0;     
            fputs(snum, fp);//snum <-------
            fputs(", ", fp);
            fputs("R", fp);
            fputs(snum, fp);//snum <-------
            fputs(", ", fp);
            fputs("#", fp);
            fputs(token, fp); // gai,<___-
            fputs("\n", fp);                
           
            count++;
            continue;
        }
                
               
        if (get_offset(token, &offset) == 0) {
            // fail. no such token
            //free(token);
            //printf("token free!\n", offset);
            free(lhs);
            printf("[%s] was not in the symbol table!\n", token);
            good++;
            //printf("RETURN -1!!!\n");
            return -1;
        }
        //printf("offset is [%d]\n", offset);
        
        
        fputs("LDR ", fp);
        fputs("R", fp);
        char snum[5];
        snum[0] = count + 48;
        snum[1] = 0;     
        fputs(snum, fp);//snum <-------
        fputs(", ", fp);
        fputs("FP, ", fp);
        fputs("#", fp);
        if (offset < 0) {
            snum[0] = '-';
            snum[1] = (0 - offset) + 48;
            
            snum[2] = 0;
        } else {
            snum[0] = offset + 48;
            snum[1] = 0;
        }
        fputs(snum, fp);//snum <-------
        fputs("\n", fp);
        
        count++;
        
    } while (1);
    
    
    //printf("count is %d\n", count);
    
    /////inplement
    count--;
    
    
    while (count > 0) {
        char a[5];
        a[0] = count + 48 - 1;
        a[1] = 0;  
        char b[5];
        b[0] = count + 48;
        b[1] = 0;   
        fputs("ADD ", fp);
        fputs("R", fp);
        fputs(a, fp);
        fputs(", ", fp);
        fputs("R", fp);
        fputs(a, fp);
        fputs(", ", fp);
        fputs("R", fp);
        fputs(b, fp);
        fputs("\n", fp);
        count--;
    }
    
    ///
    
    
    fputs("STR ", fp);
    fputs("R0, FP, #", fp);
    char snum[5];
    int offset = -1000;
    int ppp = -1000;
    ppp = get_offset(lhs, &offset);
            if (ppp == 0) {
            // fail. no such token
            //free(token);
            //printf("token free!\n", offset);
            //free(lhs);
            printf("[%s] was not in the symbol table!\n", lhs);
            good++;
            //printf("RETURN -1!!!\n");
            return -1;
        }
    
    if (offset < 0) {
            snum[0] = '-';
            snum[1] = (0 - offset) + 48;
            
            snum[2] = 0;
        } else {
            snum[0] = offset + 48;
            snum[1] = 0;
    }
    
    fputs(snum, fp);
    fputs("\n", fp);
    //printf("jieshula\n");
    return 0;
    
}

int type4_helper(char* temp, FILE* fp){
    char* line_str;
    line_str = malloc(sizeof(char)*(strlen(temp)+1));
    line_str = strcpy(line_str, temp);
    const char s[10] = " +=;\n";
    char* token = NULL;
    
    // 'return'
    token = strtok(line_str, s); 
    char* lhs = malloc(sizeof(char)*(strlen(token)+1));
    lhs = strcpy(lhs, token);
    
    // right-hand-side vars
    int count = 0;
    //fputs("; ", fp);
    //fputs(temp, fp);
    ////
    do {
        
        token = strtok(NULL, s);
        if (token == NULL) break;
        //printf("token:[%s]", token);
        int offset = -1000;
        char number[5];
        number[0] = 0;
        number[1] = 0;
        number[2] = 0;
        int mark = -1000;
        
        if (strcmp(token, "0") == 0) {
            mark = 0;            
        }    
        //const char *str = "12345"; 
        char* just = malloc(sizeof(char)*strlen(token)+1);
        just = strcpy(just, token);
        int ret = 10000; 
        sscanf(just, "%d", &ret); 
        if (ret != 0 && ret < 1000) mark = 0;
        //printf("\nThe value of ret : [%s]-[%d]\n", token, ret);        
        
        
        
        if (strcmp(token, "0") == 0) {
            number[0] = '0';
            mark = 0;
        } else if (strcmp(token, "1") == 0) {
            number[0] = '1';
            mark = 0;
        } else if (strcmp(token, "2") == 0) {
            number[0] = '2';
            mark = 0;
        } else if (strcmp(token, "3") == 0) {
            number[0] = '3';
            mark = 0;
        } else if (strcmp(token, "4") == 0) {
            number[0] = '4';
            mark = 0;
        } else if (strcmp(token, "5") == 0) {
            number[0] = '5';
            mark = 0;
        } else if (strcmp(token, "6") == 0) {
            number[0] = '6';
            mark = 0;
        } else if (strcmp(token, "7") == 0) {
            number[0] = '7';
            mark = 0;
        } else if (strcmp(token, "8") == 0) {
            number[0] = '8';  
            mark = 0;
        } else if (strcmp(token, "9") == 0) {
            number[0] = '9';
            mark = 0;
        } else if (strcmp(token, "10") == 0) {
            number[0] = '1';
            number[1] = '0';
            mark = 0;
        } else if (strcmp(token, "11") == 0) {
            number[0] = '1';
            number[1] = '1';
            mark = 0;
        } else if (strcmp(token, "12") == 0) {
            number[0] = '1';
            number[1] = '2';
            mark = 0;
        } else if (strcmp(token, "13") == 0) {
            number[0] = '1';
            number[1] = '3';
            mark = 0;
        } else if (strcmp(token, "14") == 0) {
            number[0] = '1';
            number[1] = '4';
            mark = 0;
        } else if (strcmp(token, "15") == 0) {
            number[0] = '1';
            number[1] = '5';
            mark = 0;
        } else {
            //printf("#####it's a letter#####\n");
        }
        
        if (mark == 0) { // indicating this is a number
            //printf("#####TRUE: this is a number#####\n");
            // AND R0, R0, #0
            fputs("AND ", fp);
            fputs("R", fp);
            char snum[5];
            snum[0] = count + 48;
            snum[1] = 0;     
            fputs(snum, fp);
            fputs(", ", fp);
            fputs("R", fp);
            fputs(snum, fp);
            fputs(", ", fp);
            fputs("#0", fp);
            fputs("\n", fp);             
            
            // ADD R0, R0, #<value>
            fputs("ADD ", fp);
            fputs("R", fp);
            snum[0] = count + 48;
            snum[1] = 0;     
            fputs(snum, fp);
            fputs(", ", fp);
            fputs("R", fp);
            fputs(snum, fp);
            fputs(", ", fp);
            fputs("#", fp);
            fputs(token, fp); // fputs(number, fp);
            fputs("\n", fp);                
           
            count++;
            continue;
        }
                
        
        
        if (get_offset(token, &offset) == 0) {
            // fail. no such token
            //free(token);
            //printf("token free!\n", offset);
            //free(lhs);
            printf("[%s] was not in the symbol table!\n", token);
            good++;
            return -1;
        }
        //printf("offset is [%d]\n", offset);
        
        //printf("[[[[[BEGA!]]]]]\n");
        fputs("LDR ", fp);
        fputs("R", fp);
        char snum[5];
        snum[0] = count + 48;
        snum[1] = 0;     
        fputs(snum, fp);
        fputs(", ", fp);
        fputs("FP, ", fp);
        fputs("#", fp);
        if (offset < 0) {
            snum[0] = '-';
            snum[1] = (0 - offset) + 48;
            
            snum[2] = 0;
        } else {
            snum[0] = offset + 48;
            snum[1] = 0;
        }
        //printf("%s\n", snum);
        fputs(snum, fp);
        fputs("\n", fp);
        
        count++;
        
    } while (1);
    
    
    //printf("count is %d", count);
    
    /////inplement
    count--;
    
    while (count > 0) {
        char a[5];
        a[0] = count + 48 - 1;
        a[1] = 0;  
        char b[5];
        b[0] = count + 48;
        b[1] = 0;   
        fputs("ADD ", fp);
        fputs("R", fp);
        fputs(a, fp);
        fputs(", ", fp);
        fputs("R", fp);
        fputs(a, fp);
        fputs(", ", fp);
        fputs("R", fp);
        fputs(b, fp);
        fputs("\n", fp);
        count--;
    }
    
    fputs("STR R0, FP, #3\n", fp);
    
}

int type3_helper(char* temp, FILE* fp){
    
    char* line_str;
    line_str = malloc(sizeof(char)*(strlen(temp)+1));
    line_str = strcpy(line_str, temp);
    const char s[10] = ",;\n";
    char* token = NULL;
    
    //fputs("; ", fp);
    //fputs(temp, fp);
    
    // first token
    token = strtok(line_str, s); 
    char* lhs = malloc(sizeof(char)*(strlen(token)+1));
    lhs = strcpy(lhs, token);
    //printf("type3: 1st token is [%s]\n", token);
    
    char* flag;
    flag = malloc(sizeof(char)*(strlen(token)+1));
    flag = strcpy(flag, token);
    
    
    //helper_for_three(flag, fp);
    
    /**
    if (begin_with_int_check(flag) == 100) {
        // first arg begin with int
        // remove 'int' notation
        char* substr = malloc(strlen(flag) - 4);
        strncpy(substr, flag+4, strlen(flag) - 4);
        printf("Original[%s] Cutoff[%s]\n", flag, substr);
        
        // now cutoff is good!
        type2_helper(substr, fp); //<<<<<-----
    } else {
        // now is same as type 2
        // call type 2
        type2_helper(flag, fp); //<<<<<-----
    }
    **/

    
    int countflag = 0;
    
    
    do {
        token = strtok(NULL, s);
        //printf("!!!!!!!!!!!after 2nd - type3: token is [%s]\n", token);
        
        countflag++;
        if (countflag == 1){
            if (helper_for_three(flag, fp) == -1) return -1;
        }
        //printf("[%s]", token);
        if (token == NULL) break;
     //printf("COMINGI+2g4\n\n\n");
        // if token != NULL, do the loading
        // 
        
        if (begin_with_int_check(token) == 100) {
            // first arg begin with int
            // remove 'int' notation
            // 
            //printf("yayyay");
            // 
            char* substr = malloc(strlen(token) - 4);
            strncpy(substr, token+4, strlen(token) - 4);
           // printf("Original[%s] Cutoff[%s]\n", token, substr);
        
            // now cutoff is good!
            
            if (type2_helper(substr, fp) == -1) {
                //free(substr);
                return -1; //<<<<<-----
            }
            //free(substr);
            //printf("yayyay");
        } else {
            // now is same as type 2
            // call type 2
            //printf("miao?\n");
            if (type2_helper(token, fp) == -1) return -1; //<<<<<-----
            //printf("heyhey");
        }    
          
    } while (1);
    
    //printf("Lastly,[%s][%s]\n", token, flag);
    
    
}

int begin_with_int_check(char* temp){
    char* head = malloc(sizeof(char) * (strlen(temp)+1));
    head = strcpy(head, temp);
	const char s[10] = " ;\n";
	char* token = NULL;
	token = strtok(head, s);
	//printf("[%s]\n", token);  // int (1st)
    if (strcmp(token, "int") == 0) {
        //printf("[%s] begin with int\n", temp);
        //free(head);
        return 100;
    }
    //free(head);
    return -1;
}

int helper_for_three(char* flag, FILE* fp){
        if (begin_with_int_check(flag) == 100) {
            // first arg begin with int
            // remove 'int' notation
            char* substr = malloc(strlen(flag) - 4);
            strncpy(substr, flag+4, strlen(flag) - 4);
            //printf("Original[%s] Cutoff[%s]\n", flag, substr);
            //printf("wang?\n");
            // now cutoff is good!
            int pang = type2_helper(substr, fp);
            //printf("pang is [[[%d]]]", pang);//<<<<<-----
            if (pang == -1) {
                //free(substr);
                return -1;
            }
            //free(substr);
        } else {
            // now is same as type 2
            // call type 2
            //printf("kou?\n");
            if (type2_helper(flag, fp) == -1) return -1; //<<<<<-----
        }
}