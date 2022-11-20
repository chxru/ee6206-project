#include <stdlib.h>
#include <stdio.h>

#include "lib/db.h"
#include "a.h"

int handleEdit();
int handleInsert();
int handleSearch();

void handlePartA()
{
  int choice;
  printf("1. Edit \n");
  printf("2. Insert \n");
  printf("3. Search \n");
  printf("Enter your choice: ");

  scanf("%d", &choice);

  switch (choice)
  {
  case 1:
    handleEdit();
    break;
  case 2:
    handleInsert();
    break;
  case 3:
    handleSearch();
    break;
  default:
    printf("Invalid choice \n");
  }
}

int handleEdit()
{
  printf("Edit");

  return 0;
}

int handleInsert()
{
  struct student_marks *student = (struct student_marks *)malloc(sizeof(struct student_marks));

  printf("Enter student index number: ");
  scanf("%s", student->student_index);

  printf("Assignment 01 marks: ");
  scanf("%f", &student->assgnmt01_marks);

  printf("Assignment 02 marks: ");
  scanf("%f", &student->assgnmt02_marks);

  printf("Project marks: ");
  scanf("%f", &student->project_marks);

  printf("Final exam marks: ");
  scanf("%f", &student->finalExam_marks);

  db_insert(student);

  print_student(student);

  return 0;
}

int handleSearch()
{
  struct student_marks *student = (struct student_marks *)malloc(sizeof(struct student_marks));

  printf("Enter student index number: ");
  scanf("%s", student->student_index);

  if (db_search(student, NULL) != 0)
  {
    printf("Cannot find student %s \n", student->student_index);
    // student not found
    exit(EXIT_FAILURE);
  }

  print_student(student);

  return 0;
}