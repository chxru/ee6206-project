#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "db.h"

void db_edit(struct student_marks *student)
{
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
  int position = ftell(fd); //	this hold the position of the line before matching record
  int found = 0;
  while (fgets(line, 1024, fd))
  {
    index = strtok(line, ",");

    if (strcmp(index, student->student_index) == 0)
    {
      found = 1;

      printf("Found student index: %s \n", index);
      break;
    }

    position = ftell(fd);
    if (position == -1)
    {
      printf("Failed to get position. Error: %d", errno);
      perror("ftell");
      exit(EXIT_FAILURE);
    }
  }

  //	handle student not found case
  if (found == 0)
  {
    printf("Student index not found \n");
    return;
  }

  // reset file pointer to the beginning of the line
  if (fseek(fd, position, SEEK_SET) == -1)
  {
    printf("Failed to seek to position. Error: %d", errno);
    perror("fseek");
    exit(EXIT_FAILURE);
  }

  // overwrite the line with the new data
  int print_res = fprintf(fd, "%s,%05.2f,%05.2f,%05.2f,%05.2f\n",
                          student->student_index,
                          student->assgnmt01_marks,
                          student->assgnmt02_marks,
                          student->project_marks,
                          student->finalExam_marks);

  if (print_res < 0)
  {
    printf("Failed to write to file. Error: %d", errno);
    perror("fprintf");
    exit(EXIT_FAILURE);
  }

  if (fclose(fd) == EOF)
  {
    printf("Failed to close file. Error: %d", errno);
    perror("fclose");
    exit(EXIT_FAILURE);
  }

  printf("Student record updated successfully \n");
}

void db_insert(struct student_marks *student)
{
  FILE *fd;
  fd = fopen("data.csv", "a+");
  if (fd == NULL)
  {
    printf("Failed to initialize database. Error: %d", errno);
    perror("data.csv");
    exit(EXIT_FAILURE);
  }

  int print_res = fprintf(fd, "%s,%05.2f,%05.2f,%05.2f,%05.2f\n",
                          student->student_index,
                          student->assgnmt01_marks,
                          student->assgnmt02_marks,
                          student->project_marks,
                          student->finalExam_marks);

  if (print_res < 0)
  {
    printf("Failed to close file. Error: %d", errno);
    perror("fclose");
    exit(EXIT_FAILURE);
  }

  if (fclose(fd) != 0)
  {
    printf("Failed to close database. Error: %d", errno);
    perror("data.csv");
    exit(EXIT_FAILURE);
  }

  printf("Student record inserted successfully \n");
}

int db_search(struct student_marks *student)
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

      if (fclose(fd) == EOF)
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