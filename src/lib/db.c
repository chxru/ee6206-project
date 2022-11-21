#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "db.h"

void db_edit(struct student_marks *student)
{
  printf("Editing \n");

  FILE *fd;
  fd = fopen("data.csv", "r+");
  if (fd == NULL)
  {
    printf("Failed to initialize database. Error: %d", errno);
    perror("data.csv");
    exit(EXIT_FAILURE);
  }

  char line[1024];
  char *index;

  int position = ftell(fd);
  while (fgets(line, 1024, fd))
  {
    index = strtok(line, ",");
    printf("%d index: %s \n", position, index);

    if (strcmp(index, student->student_index) == 0)
    {
      printf("Found student index: %s \n", index);
      break;
    }

    position = ftell(fd);
  }

  fseek(fd, position, SEEK_SET);
  fprintf(fd, "%s,%05.2f,%05.2f,%05.2f,%05.2f\n",
          student->student_index,
          student->assgnmt01_marks,
          student->assgnmt02_marks,
          student->project_marks,
          student->finalExam_marks);
  fclose(fd);
}

void db_insert(struct student_marks *student)
{
  printf("Inserting\n");

  FILE *fd;
  fd = fopen("data.csv", "a+");
  if (fd == NULL)
  {
    printf("Failed to initialize database. Error: %d", errno);
    perror("data.csv");
    exit(EXIT_FAILURE);
  }

  fprintf(fd, "%s,%05.2f,%05.2f,%05.2f,%05.2f\n",
          student->student_index,
          student->assgnmt01_marks,
          student->assgnmt02_marks,
          student->project_marks,
          student->finalExam_marks);

  if (fclose(fd) != 0)
  {
    printf("Failed to close database. Error: %d", errno);
    perror("data.csv");
    exit(EXIT_FAILURE);
  }
}

int db_search(struct student_marks *student, int *position)
{
  printf("Searching %s... ", student->student_index);

  FILE *fd;
  fd = fopen("data.csv", "a+");
  if (fd == NULL)
  {
    printf("Failed to initialize database. Error: %d", errno);
    perror("data.csv");
    exit(EXIT_FAILURE);
  }

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

      if (fclose(fd) != 0)
      {
        printf("Failed to close database. Error: %d", errno);
        perror("data.csv");
        exit(EXIT_FAILURE);
      }

      return 0;
    }
  }

  printf(" not found!\n");

  if (fclose(fd) != 0)
  {
    printf("Failed to close database. Error: %d", errno);
    perror("data.csv");
    exit(EXIT_FAILURE);
  }

  return -1;
}