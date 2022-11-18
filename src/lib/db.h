#ifndef DB_H
#define DB_H

#include <stdio.h>

struct student_marks
{
  int key;                // key is the index
  char student_index[13]; // EG/XXXX/XXXX
  float assgnmt01_marks;  // 15%
  float assgnmt02_marks;  // 15%
  float project_marks;    // 20%
  float finalExam_marks;  // 50%
};

/**
 * @brief stdout the student details
 *
 * @param student
 */
void print_student(struct student_marks *student);

/**
 * @brief insert a student record into the database
 *
 * @param student
 */
void db_insert(struct student_marks *student);

#endif