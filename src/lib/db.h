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
 * @brief insert a student record into the database
 *
 * @param student
 */
void db_insert(struct student_marks *student);

#endif