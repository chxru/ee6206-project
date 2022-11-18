#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "db.h"

FILE *fd;

/**
 * @brief Initialize the file descriptors
 *
 */
void db_initialize()
{
  printf("Initializing database \n");

  fd = fopen("data.csv", "a+");

  if (fd == NULL)
  {
    printf("Failed to initialize database. Error: %d", errno);
    perror("data.csv");
    exit(EXIT_FAILURE);
  }
}

void db_insert(struct student_marks *student)
{
  printf("Inserting\n");

  if (fd == NULL)
    db_initialize();

  fprintf(fd, "%s,%.2f,%.2f,%.2f,%.2f\n",
          student->student_index,
          student->assgnmt01_marks,
          student->assgnmt02_marks,
          student->project_marks,
          student->finalExam_marks);
}

int db_search(struct student_marks *student, int *position)
{
  // skip search if student index is empty
  if (student->student_index == NULL)
    return -1;

  printf("Searching %s... ", student->student_index);

  if (fd == NULL)
    db_initialize();

  char line[1024];
  char *token;
  char *index;

  while (fgets(line, 1024, fd))
  {
    index = strtok(line, ",");
    if (strcmp(index, student->student_index) == 0)
    {

      printf(" found!\n");

      printf("Student index: %s\n", student->student_index);

      token = strtok(NULL, ",");
      student->assgnmt01_marks = atof(token);
      token = strtok(NULL, ",");
      student->assgnmt02_marks = atof(token);
      token = strtok(NULL, ",");
      student->project_marks = atof(token);
      token = strtok(NULL, ",");
      student->finalExam_marks = atof(token);

      if (position != NULL)
        *position = ftell(fd);

      return 0;
    }
  }

  printf(" not found!\n");

  return -1;
}