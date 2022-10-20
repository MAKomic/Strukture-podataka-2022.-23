#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define MAX_FILE_NAME 1024
#define MAX_NAME_AND_SURNAME 1024
#define MAX_ROW_SIZE 1024
#define MAX_NUMBER_OF_POINTS 100

typedef struct Student {
	char Name[MAX_NAME_AND_SURNAME];
	char Surname[MAX_NAME_AND_SURNAME];
	int NumberOfPoints;
}Student;

int CountF(char* filename)
{
	int CountStudents = 0;
	char buffer[MAX_ROW_SIZE] = { 0 };
	FILE* f = NULL;

	f = fopen(filename, "r");

	if (f == NULL)
	{
		printf("Error! File failed to launch./The file is empty.");
	}

	while (!feof(f))
	{
		fgets(buffer, MAX_ROW_SIZE, f);
		if (strcmp("\n", buffer) != 0)
			CountStudents++;
	}

	fclose(f);
	return CountStudents;
}

void InputAndOutputOfData(int CountStudents, char* filename)
{
	Student* student;
	FILE* f;
	float AvarageNumberOfPoints = 0;

	student = (Student*)malloc(sizeof(Student) * CountStudents);

	f = fopen(filename, "r");

	for (int i = 0; i < CountStudents; i++)
	{
		fscanf(f, "%s %s %d", student[i].Name, student[i].Surname, &student[i].NumberOfPoints);
	}

	for (int i = 0; i < CountStudents; i++)
	{
		AvarageNumberOfPoints = 0;
		printf("%s %s %d\n", student[i].Name, student[i].Surname, student[i].NumberOfPoints);
		AvarageNumberOfPoints = student[i].NumberOfPoints / (float)MAX_NUMBER_OF_POINTS * 100;
		printf("The avarage number of points is:%f\n", AvarageNumberOfPoints);
	}
}

void main()
{
	int CountStudents = 0;
	char buffer[MAX_ROW_SIZE] = { 0 };
	FILE* f = NULL;
	char filename[MAX_FILE_NAME];

	printf("Input the name of the file:\n");
	scanf("%s", filename);

	CountStudents = CountF(filename);
	InputAndOutputOfData(CountStudents, filename);
}
