////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//Author:.......Adam Powell                                                      \\
//UCF ID:.......1917289                                                           \\
//Course:.......COP3502c CS1                                                       \\
//Assignment:...Lab 2: DMA w/ Structs & File I/O                                    \\
//Date:.........1/20/2020                                                            \\
//<<??{{OO~~88}}??>>\\//<<??{{OO~~88}}??>>\\//<<??{{OO~~88}}??>>\\//<<??{{OO~~88}}??>>\\
////////////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>


struct student {
	char lastName[51];
	int* quizzes;
	int finalE;
	int assign;
	int total;

} typedef student; //single student structure

student* readData(FILE* in, int* numStudents, int* numQuizes); //Funtion Prototype

int main() {

	student* students; //array of student structs
	FILE* fp;
	FILE* outFile;
	int numStudents;
	int numQuizes;
	int s, j;

	fp = fopen("input.txt", "r");

	students = readData(fp, &numStudents, &numQuizes);

	for (int s = 0; s < numStudents; s++) {
		printf("(%s, %d)\n", (students + s)->lastName, students[s].total); //different code technique for practice
	}
	fclose(fp);

	/////////////////Selects Highest Performing Student\\\\\\\\\\\\\\\\\\

	printf("\nStudetn with highest grade: ");
	int max_finalGrade = 0;
	int max_finalGrade_index = 0;

	for (s = 0; s < numStudents; s++) {
		if (students[s].total > max_finalGrade) {
			max_finalGrade = students[s].total;
			max_finalGrade_index = s;
		}
	}

	printf("%s, %d", students[max_finalGrade_index].lastName, 
					 students[max_finalGrade_index].total);

	//////////PRINT TO TEXT FILE\\\\\\\\\\\-===>>>>
	outFile = fopen("output.txt", "w");
	fprintf(outFile, "Top Student:\t\t%s\nAssignment:\t\t\t%d\nQuiz 1:\t\t\t    %d\nQuiz 2:\t\t\t    %d\nFinal Exam:\t\t\t%d\nTotal Score:\t\t%d\n",
					students[max_finalGrade_index].lastName, students[max_finalGrade_index].assign,
					students[max_finalGrade_index].quizzes[0], students[max_finalGrade_index].quizzes[1],
					students[max_finalGrade_index].finalE, students[max_finalGrade_index].total);

	fclose(outFile); //Saves and Closes File

	for (s = 0; s < numStudents; s++)   //Frees up memory after program is finished.
		free(students[s].quizzes);
	free(students);

	return 0;
}// end of main()


student* readData(FILE* in, int* numStudents, int* numQuizes) {

	int s, q; //used to traverse the student and quiz for loops.

	fscanf(in,"%d %d", numStudents, numQuizes);

	student* students = (student*)malloc(sizeof(student) * *numStudents);  //allocates memory for array of students.

	for (s = 0; s < *numStudents; s++) {	//for loop to traverse through each student in list.
		students[s].quizzes = (int*)malloc(sizeof(int) * *numQuizes);	//allocates memory for num quizes.
		students[s].total = 0;

		/////////////Scanning Data In From Input File\\\\\\\\\\\\\\

		fscanf(in, "%s %d", &students[s].lastName, &students[s].assign);

		for (q = 0; q < *numQuizes; q++) {					//cycles through amount of quizzes and stores values for each student.
			fscanf(in, "%d", &students[s].quizzes[q]);
			students[s].total += (int)students[s].quizzes[q];//add in each quiz
		}

		fscanf(in, "%d", &students[s].finalE);
		students[s].total += students[s].assign + students[s].finalE; //stores assignment and final exam scores lastly.

	}
	printf("Test:%s %d %d", students[0].lastName, students[0].quizzes, students[0].total); //test output to console.

	return students;

}   //end of readData();