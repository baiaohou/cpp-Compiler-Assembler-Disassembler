#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * Contains test code for Part 2
 */

extern int get_offset(char*, int*);
extern int populate_symbol_table(char*);

void test_offset(char*, int);

int main() {

  char* filename = "sample.c";

  printf("Calling populate_symbol_table(\"%s\")\n", filename);
  populate_symbol_table(filename);

  test_offset("t", -3);
  test_offset("z", -2);
  test_offset("y", -1);
  test_offset("x", -0);
  test_offset("b", 5);
  test_offset("a", 4);
	
	
	clear();
  return 0;
}

void test_offset(char* symbol, int expected_offset) {
  int offset = -1000;
  get_offset(symbol, &offset);

  if (offset == expected_offset) printf("Correctly read offset of %d for %s.\n", expected_offset, symbol);
  else if (offset == -1000) printf("ERROR! get_offset should read offset of %d for %s but did not return a value.\n", expected_offset, symbol);
  else printf("ERROR! get_offset should have read offset of %d for %s but read it as %d\n", expected_offset, symbol, offset);

}

