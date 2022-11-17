#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 1024

#define DATOTEKA_SE_NIJE_OTVORILA -1
#define MEMORIJA_NEUSPJESNO_ALOCIRANA -1
#define NEPRAVILAN_IZRAZ -2

#define USPJESAN_UNOS 1
#define USPJESAN_ISPIS 1

typedef struct cvor* poz;

typedef struct cvor {
	float el;
	poz next;
}cvor;

int citajDatoteku(char[], poz);

int Push(float, poz);
float Pop(poz);


int main()
{
	cvor head;
	head.next = NULL;
	char ime_datoteke[MAX_LINE_SIZE] = { 0 };
	float temp = 0;
	int provjera = 0;

	printf("Unesi ime datoteke: ");
	scanf(" %s", ime_datoteke);

	while (citajDatoteku(ime_datoteke, &head) == DATOTEKA_SE_NIJE_OTVORILA)
	{
		printf("\nNepravilno ime datoteke.\nPonovni unos:");
		scanf(" %s", ime_datoteke);
		provjera = citajDatoteku(ime_datoteke, &head);
	}

	if (provjera == NEPRAVILAN_IZRAZ)
	{
		printf("Nepravilan postfix izraz.");
		return 0;
	}

	temp = Pop(&head);
	printf("\nRjesenje je: %f\n", temp);
	/*
	* ZBOG 40-45
	printf("\nIduci element je %f\n", head.next->el);
	*/

	return 0;
}

int citajDatoteku(char ime_datoteke[], poz head)
{
	FILE* fp = NULL;
	int n = 0, brojacEl = 0;
	char buffer[MAX_LINE_SIZE] = { 0 };
	float temp = 0.0;

	fp = fopen(ime_datoteke, "r");

	if (fp == NULL)
	{
		return DATOTEKA_SE_NIJE_OTVORILA;
	}
	
	while (!feof(fp))
	{
		fscanf(fp, "%s", buffer);

		if ((sscanf(buffer, "%d", &n)) == 1)
		{
			Push((float)n, head);
			brojacEl++;
		}

		else
		{
			switch (buffer[0])
			{
			case '*':
				if (brojacEl < 2)
				{
					return NEPRAVILAN_IZRAZ;
				}
				temp = Pop(head);
				Push(Pop(head) * temp, head);
				brojacEl--;
				break;

			case '+':
				if (brojacEl < 2)
				{
					return NEPRAVILAN_IZRAZ;
				}
				temp = Pop(head);
				Push(Pop(head) + temp, head);
				brojacEl--;
				break;

			case '-':
				if (brojacEl < 2)
				{
					return NEPRAVILAN_IZRAZ;
				}
				temp = Pop(head);
				Push(Pop(head) - temp, head);
				brojacEl--;
				break;

			case '/':
				if (brojacEl < 2)
				{
					return NEPRAVILAN_IZRAZ;
				}
				temp = Pop(head);
				if (temp == 0)
				{
					printf("Ne dili sa 0!\n");
					return NEPRAVILAN_IZRAZ;
				}
				Push(Pop(head) / temp, head);
				brojacEl--;
				break;

			default:
				return NEPRAVILAN_IZRAZ;
			}

		}

	}

	if (brojacEl != 1)
	{
		return NEPRAVILAN_IZRAZ;
	}

	else
	{
		return USPJESAN_UNOS;
	}

}

int Push(float x, poz head)
{
	poz q = NULL;
	q = (poz)malloc(sizeof(cvor));

	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija.");
		return MEMORIJA_NEUSPJESNO_ALOCIRANA;
	}

	q->el = x;
	q->next = head->next;
	head->next = q;

	return USPJESAN_UNOS;
}

float Pop(poz head)
{
	poz temp = NULL;
	float pom = 0.0;
	/*
	if (head->next == NULL)
	{
		printf("\nNepravilan je postfix izraz!");
		exit(1);
	}
	*/

	pom = head->next->el;

	temp = head->next;
	head->next = temp->next;
	free(temp);

	return pom;

}
