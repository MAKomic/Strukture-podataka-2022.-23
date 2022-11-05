#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define	MAX_BROJ_BODOVA (50)
#define USPJESAN_ISPIS (1)

struct student {
	char ime[MAX_LINE];
	char prezime[MAX_LINE];
	int bodovi=0;
};
typedef struct student student;

int countStudentsFromFile(char* filename);
student* putStudentsInList(char* filename, int count);
float relativanBrojBodova(int bodovi);
int ispisStudenata(student* listaStudenata, int count);

int main()
{
	char filename[MAX_FILE_NAME] = { 0 };

	printf("Unesi ime datoteke: ");
	scanf(" %s", filename);

	printf("Broj studenata u datoteci %s je %d\n", filename, countStudentsFromFile(filename));
	ispisStudenata(putStudentsInList(filename, countStudentsFromFile(filename)), countStudentsFromFile(filename));


	return 0;
}

int countStudentsFromFile(char* filename)
{
	FILE* fp = NULL;
	int count = 0;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila!\r\n");
		return FILE_DIDNT_OPEN_ERROR;
	}
	
	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);
		if (strcmp("\n", buffer) != 0)
		{
			count++;
		}
	}
	
	fclose(fp);
	return count;
}

student* putStudentsInList(char* filename,int count)
{
	FILE* fp = NULL;
	FILE* fp1 = NULL;
	int i = 0;
	char buffer[MAX_LINE] = { 0 };
	student* listaStudenata = NULL;
	
	listaStudenata = (student*)malloc(count*sizeof(student));
	
	fp = fopen(filename, "r");
	fp1 = fopen(filename, "r");
	if (fp == NULL || fp1 == NULL)
	{
		printf("Datoteka se nije otvorila!\r\n");
		return FILE_DIDNT_OPEN_ERROR;

	}
	
	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE, fp);
		if (strcmp("\n", buffer) != 0)
		{
			fscanf(fp1, "%s %s %d", (listaStudenata + i)->ime, (listaStudenata + i)->prezime, &(listaStudenata[i]).bodovi);
			i++;
		}
		else
		{
			fgets(buffer, MAX_LINE, fp1);
		}
	}
	
	fclose(fp);
	fclose(fp1);
	return listaStudenata;

}

int ispisStudenata(student* listaStudenata,int count)
{
	int i = 0;
	printf("IME\tPREZIME\tBODOVI\tRELATIVNI BODOVI\n");
	for (i = 0; i < count; i++)
	{
		printf("%s\t%s\t%d\t%f\n", (listaStudenata + i)->ime, (listaStudenata + i)->prezime, (listaStudenata + i)->bodovi, relativanBrojBodova((listaStudenata + i)->bodovi));
	}

	return USPJESAN_ISPIS;
}

float relativanBrojBodova(int bodovi)
{
	return(float(bodovi) / MAX_BROJ_BODOVA * 100.0);
}
