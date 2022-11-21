#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "src/a.h"
#include "src/b.h"

int main(int argc, char *argv[])
{
  // if command line argument is given, run part B
  if (argc == 2)
  {
    if (strcmp(argv[1], "b") == 0)
    {
      handlePartB();
    }
    else
    {
      printf("Invalid argument. Only part B is supported\n");
    }

    exit(0);
  }

  printf("EE6206 Mini Project \n");
  printf("Samarakaoon SWKCH - EG/2018/3448\n\n");

  while (1)
  {
    printf("Please select the part to run (A/B): ");
    char part;
    scanf(" %c", &part);

    if (part == 'A' || part == 'a')
    {
      handlePartA();
    }
    else if (part == 'B' || part == 'b')
    {
      handlePartB();
    }
    else
    {
      printf("Invalid input. Please try again.\n");
    }
  }
  return 0;
}
