#ifndef DB_H
#define DB_H

#include <stdio.h>

#include "student.h"

/**
 * @brief stdout the student details
 *
 * @param student
 */
void print_student(struct student_marks *student);

/**
 * @brief edit a record in database
 *
 * @param student student_marks struct with the student index
 * @return int 0 if success, -1 if not found
 */
int db_edit(struct student_marks *student);

/**
 * @brief insert a student record into the database
 *
 * @param student
 */
void db_insert(struct student_marks *student);

/**
 * @brief search for a student record in the database
 *
 * @param student pointer to the found student_marks struct
 * @param position fd position of the found student_marks struct
 * @return int 0 if found, -1 if not found
 */
int db_search(struct student_marks *student, int *position);

#endif