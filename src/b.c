#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>

#include "b.h"

const int FORK_C1 = 0;	// fork child 1
const int FORK_C2 = 1;	// fork child 2
const int FORK_CC1 = 2; // fork child of child 1
const int FORK_CC2 = 3; // fork child of child 2

struct student_marks *marks_array; // store all the student marks

struct pipe_res
{
	int passed; // number of passed students
	int failed; // number of failed students
	int pid;		// pid of the child process
	int start;	// start index of the array
	int end;		// end index of the array
};

// file descriptor for the pipe
int fd_c1[2];
int fd_c2[2];
int fd_cc1[2];
int fd_cc2[2];

/**
 * @brief Analyze the marks of the students, count passed and failed students
 *
 * @param start starting index of the marks array
 * @param end  ending index of the marks array
 * @param forkedId ID to determine which child process is calling this function
 */
void analyze(int start, int end, int forkedId)
{
	int passed = 0; // number of passed students
	int failed = 0; // number of failed students

	pid_t pid = getpid();

	for (int i = start; i <= end; i++)
	{
		// print the student details
		printf("Process id %d: \t From %d student %s with ", i, pid, marks_array[i].student_index);

		// ignore empty lines
		if (marks_array[i].student_index[0] == '\0')
			continue;

		// calculate total marks
		float total = marks_array[i].assgnmt01_marks + marks_array[i].assgnmt02_marks + marks_array[i].project_marks + marks_array[i].finalExam_marks;
		printf("total marks %.2f is ", total);

		if (total >= 75)
		{
			printf("passed\n");
			passed++;
		}
		else
		{
			printf("failed\n");
			failed++;
		}
	}

	// response
	struct pipe_res res = {passed, failed, pid, start, end};

	int write_res;
	if (forkedId == FORK_C1)
	{
		write_res = write(fd_c1[1], &res, sizeof(res));
	}
	else if (forkedId == FORK_C2)
	{
		write_res = write(fd_c2[1], &res, sizeof(res));
	}
	else if (forkedId == FORK_CC1)
	{
		write_res = write(fd_cc1[1], &res, sizeof(res));
	}
	else if (forkedId == FORK_CC2)
	{
		write_res = write(fd_cc2[1], &res, sizeof(res));
	}

	if (write_res == -1)
	{
		perror("write");
		printf("Error writing to pipe\n");
		exit(EXIT_FAILURE);
	}

	exit(0);
}

void tier1_child(int start, int end, int forkId)
{
	// create sub child processes
	pid_t pid_ccx = fork();

	if (pid_ccx == -1)
	{
		printf("Error creating child processes");
		exit(1);
	}

	int middle = (start + end) / 2;

	if (pid_ccx == 0)
	{
		// cx
		int f = forkId == FORK_C1 ? FORK_CC1 : FORK_CC2;
		analyze(start, middle, f);
	}
	else
	{
		// ccx
		analyze(middle + 1, end, forkId);
	}
}

void handlePartB()
{
	/*
	 * Since there isn't strict instructions on how to handle this part,
	 * here is the procedure followed in this part
	 *
	 * 1. Main process read the data.csv and save each line as an array
	 * 2. Split all data into 4 parts
	 * 3. Create 4 child processes, and pass start and end index of each part to each child
	 * 4. Child process will do the analysis and return the result to main process
	 */

	// initiate the marks array
	marks_array = malloc(100 * sizeof *marks_array);

	// read the data.csv
	FILE *fp = fopen("data.csv", "r");
	if (fp == NULL)
	{
		perror("data.csv");
		printf("Error opening file data.csv. %d", errno);
		exit(1);
	}

	int count = 0;	 // total count of records
	char line[1024]; // temp buffer to read each line
	while (fgets(line, 1024, fp))
	{
		// resize the array if needed
		if (count % 100 == 0)
		{
			marks_array = realloc(marks_array, (count + 100) * sizeof *marks_array);
		}

		char *token = strtok(line, ",");
		strcpy(marks_array[count].student_index, token);

		token = strtok(NULL, ",");
		marks_array[count].assgnmt01_marks = atof(token);

		token = strtok(NULL, ",");
		marks_array[count].assgnmt02_marks = atof(token);

		token = strtok(NULL, ",");
		marks_array[count].project_marks = atof(token);

		token = strtok(NULL, ",");
		marks_array[count].finalExam_marks = atof(token);

		count++;
	}

	// if the file is empty
	if (count == 0)
	{
		printf("data.csv is empty");
		exit(1);
	}

	// close the file
	if (fclose(fp) == EOF)
	{
		perror("data.csv");
		printf("Error closing file data.csv. %d", errno);
		exit(1);
	}

	// resize the array to the actual size
	marks_array = realloc(marks_array, count * sizeof *marks_array);

	int start = 0;
	int middle = count / 2;
	int end = count;

	// create pipes
	if (pipe(fd_c1) == -1 || pipe(fd_c2) == -1 || pipe(fd_cc1) == -1 || pipe(fd_cc2) == -1)
	{
		perror("pipe");
		printf("Error creating pipes. %d", errno);
		exit(1);
	}

	// create child processes
	pid_t pid_c1 = fork();
	pid_t pid_c2 = fork();

	if (pid_c1 == -1 || pid_c2 == -1)
	{
		perror("fork");
		printf("Error creating child processes. %d", errno);
		exit(1);
	}

	// c1
	if (pid_c1 == 0 && pid_c2 != 0)
	{
		printf("Passing %d to %d to c1, pid_c1 %d pid_c2 %d \n", start, middle, pid_c1, pid_c2);
		tier1_child(start, middle, FORK_C1);
	}

	// c2
	if (pid_c2 == 0 && pid_c1 != 0)
	{
		printf("Passing %d to %d to c2, pid_c1 %d pid_c2 %d \n", middle + 1, end, pid_c1, pid_c2);
		tier1_child(middle + 1, end, FORK_C2);
	}

	// read the results from the pipes
	struct pipe_res res_c1, res_c2, res_cc1, res_cc2;

	if (read(fd_c1[0], &res_c1, sizeof(res_c1)) == -1)
	{
		perror("read");
		printf("Error reading from pipe 1. %d", errno);
		exit(1);
	}

	if (read(fd_c2[0], &res_c2, sizeof(res_c2)) == -1)
	{
		perror("read");
		printf("Error reading from pipe 2. %d", errno);
		exit(1);
	}

	if (read(fd_cc1[0], &res_cc1, sizeof(res_cc1)) == -1)
	{
		perror("read");
		printf("Error reading from pipe 3. %d", errno);
		exit(1);
	}

	if (read(fd_cc2[0], &res_cc2, sizeof(res_cc2)) == -1)
	{
		perror("read");
		printf("Error reading from pipe 4. %d", errno);
		exit(1);
	}

	// print the results
	printf("result c1: \t %d passed, %d failed, pid %d, start %d, end %d \n", res_c1.passed, res_c1.failed, res_c1.pid, res_c1.start, res_c1.end);
	printf("result c2: \t %d passed, %d failed, pid %d, start %d, end %d \n", res_c2.passed, res_c2.failed, res_c2.pid, res_c2.start, res_c2.end);
	printf("result cc1: \t %d passed, %d failed, pid %d, start %d, end %d \n", res_cc1.passed, res_cc1.failed, res_cc1.pid, res_cc1.start, res_cc1.end);
	printf("result cc2: \t %d passed, %d failed, pid %d, start %d, end %d \n", res_cc2.passed, res_cc2.failed, res_cc2.pid, res_cc2.start, res_cc2.end);

	int passed = res_c1.passed + res_c2.passed + res_cc1.passed + res_cc2.passed;
	int failed = res_c1.failed + res_c2.failed + res_cc1.failed + res_cc2.failed;

	printf("\n\n Total passed: %d,\n Total failed: %d \n", passed, failed);

	// release the memory
	free(marks_array);
}