#ifndef STUDENT_H
#define STUDENT_H

struct student_marks
{
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

#endif