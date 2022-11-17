#include <stdio.h>
#include <stdlib.h>

#include "student.h"

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
