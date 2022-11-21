#ifndef DB_H
#define DB_H

#include <stdio.h>

#include "student.h"

/**
 * @brief edit a student in the database
 *
 * @param student
 */
void db_edit(struct student_marks *student);

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
 * @return int 0 if found, -1 if not found
 */
int db_search(struct student_marks *student);

#endif