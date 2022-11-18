#include <stdlib.h>
#include <errno.h>

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

void print_student(struct student_marks *student)
{
  printf("\
    Student Index: %s\
    Assignment 01: %.2f\
    Assignment 02: %.2f\
    Project: %.2f\
    Final Exam: %.2f\n",
         student->student_index,
         student->assgnmt01_marks,
         student->assgnmt02_marks,
         student->project_marks,
         student->finalExam_marks);
}