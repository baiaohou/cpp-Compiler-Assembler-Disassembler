#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Use this file for writing tests for your functions for Part 2.
 * 
 * Please do not add a "main" function to symbol_table.c; you should only define it here.
 * 
 * Although this file will not be considered for grading, please submit it so 
 * that we know how you tested your code.
 */


extern int add_symbol(char*, int);
extern int get_offset(char*, int*);
extern void clear();

/*
 * These are prototypes/declarations for functions being defined below.
 */
void test_add_symbol(char*, int, int);
void test_get_offset(char*, int);
void test_get_offset_not_in_table(char*);

/*
 * Modify this function as you test out your code.
 */
int main() {

  /*
   * Basic functionality for add_symbol
   */


  printf("Calling add_symbol(\"dog\", 1)\n"); // add a symbol
  /*
   * Here's an example of a test for add_symbol
   * The first argument is the symbol to pass to the add_symbol function
   * The second argument is the offset to pass to the add_symbol function
   * The third argument is the expected return value from the function
   * Note that this test does not actually inspect that the symbol/offset are added,
   * just that the return value is correct.
   */
  test_add_symbol("dog", 1, 1);

  printf("Calling add_symbol(\"cat\", 2)\n"); // add another symbol
  test_add_symbol("cat", 2, 1);
    
  printf("Calling add_symbol(\"dog\", 3)\n"); // try to add a symbol that already exists
  test_add_symbol("dog", 3, 0);
    


  /*
   * Basic functionality for get_offset
   */
  printf("Calling get_offset(\"cat\")\n"); // get offset for a symbol that is in table
  /*
   * Here's an example of a test for get_offset in which the symbol is in the table
   * The first argument is the symbol to pass to the get_offset function
   * The second argument is the expected value to which the offset should be set
   * The test also checks that the return value is 1, indicating that this was successful
   */
  test_get_offset("cat", 2);

  printf("Calling get_offset(\"banana\")\n"); // get offset for a symbol that is not in table
  /*
   * Here's an example of a test for get_offset in which the symbol is not in the table
   * The argument is the symbol to pass to the get_offset function
   * The test checks that the return value is 0 and that the offset parameter is not modified
   */
  test_get_offset_not_in_table("banana");
  
  clear();
  return 0;
}


void test_add_symbol(char* symbol, int offset, int expected_return) {
  int ret = add_symbol(symbol, offset);
  if (ret == expected_return) printf("Correctly returned %d.\n", expected_return);
  else printf("ERROR! add_symbol should have returned %d but returned %d\n", expected_return, ret);
}

void test_get_offset(char* symbol, int expected_offset) {
  int offset = -1000;
  int ret = get_offset(symbol, &offset);
  int expected_return = 1;
  if (ret == expected_return) printf("Correctly returned %d.\n", expected_return);
  else printf("ERROR! get_offset should have returned %d but returned %d\n", expected_return, ret);

  if (offset == expected_offset) printf("Correctly set offset to %d.\n", expected_offset);
  else if (offset == -1000) printf("ERROR! get_offset should have set offset to %d but did not change it.\n", expected_offset);
  else printf("ERROR! get_offset should have set offset to %d but set it to %d\n", expected_offset, offset);

}

void test_get_offset_not_in_table(char* symbol) {
  int offset = -1000;
  int ret = get_offset(symbol, &offset);
  int expected_return = 0;
  if (ret == expected_return) printf("Correctly returned %d.\n", expected_return);
  else printf("ERROR! get_offset should have returned %d but returned %d\n", expected_return, ret);

  if (offset == -1000) printf("Correctly did not set offset.\n");
  else printf("ERROR! get_offset should not have set offset but set it to %d\n", offset);

}
