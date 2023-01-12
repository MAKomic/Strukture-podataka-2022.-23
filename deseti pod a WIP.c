#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LINE_SIZE 1024

#define NEUSPJESNA_OTVARANJE_DATOTEKE -1

typedef struct lista* poz;
typedef struct cvor* poz_;

typedef struct lista
{
	element el;
	poz next;
	poz_ root;
}lista;

typedef struct cvor
{
	element2 el2;
	poz_ lijevo;
	poz_ desno
}cvor;

typedef struct element
{
	char ime_drzave[MAX_LINE_SIZE];
	char ime_nove_datoteke[MAX_LINE_SIZE];
}element;

typedef struct element2
{
	char grad[MAX_LINE_SIZE];
	int brStanovnika;
}element2;

int citajDatoteku(char[MAX_LINE_SIZE], poz);
poz_ citajDruguDatoteku(char[MAX_LINE_SIZE]);
int sortiraniUnosStablo(poz_, poz_);
int gradCompare(element2, element2);

int main()
{
	lista head;
	head.next = NULL;


	char ime_datoteke[MAX_LINE_SIZE] = { 0 };

	printf("Unesi ime datoteke: ");
	scanf(" %s", ime_datoteke);


	return 0;
}

int citajDatoteku(char ime_datoteke[MAX_LINE_SIZE], poz head)
{
	FILE* fp = NULL;
	element temp;

	fp = fopen(ime_datoteke, "r");
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila!");
		return NEUSPJESNA_OTVARANJE_DATOTEKE;
	}
	while (!feof(fp))
	{
		fscanf(fp, " %s %s", temp.ime_drzave, temp.ime_nove_datoteke);
		poz_ temp=citajDruguDatoteku(temp.ime_nove_datoteke);
		sortiraniUnos(head,ime_drzave)
	}

}

poz_ citajDruguDatoteku(char ime_nove_datoteke[MAX_LINE_SIZE])
{
	FILE* fp2 = NULL;
	poz_ temp = NULL;
	temp = (poz_)malloc(sizeof(cvor));
	temp->lijevo = NULL;
	temp->desno = NULL;
	element2 el2;
	//ovo ispod triba dinamicki alocirat da se moze pobrisat
	cvor root;
	fp2 = fopen(ime_nove_datoteke, "r");
	root.desno = NULL;
	root.lijevo = NULL;
	if (fp2 == NULL)
	{
		printf("Datoteka se nije otvorila!");
		return NEUSPJESNA_OTVARANJE_DATOTEKE;
	}

	while (!feof(fp2))
	{
		fscanf(fp2, " %s,%d", temp->el2.grad, temp->el2.brStanovnika);

		sortiraniUnosStablo(&root, temp);
	}
}

int sortiraniUnosStablo(poz_ p, poz_ q)
{

	if (p == NULL)
	{
		return q;
	}

	int rezultat = gradCompare(p->el2, q->el2);

	if (gradCompare(p,q)
	{
		p->desno = unos(p->desno, q);
	}

	else if (p->el > q->el)
	{
		p->livo = unos(p->livo, q);
	}

	else
	{
		free(q);
	}

	return p;
}

int gradCompare(element2 c1, element2 c2) 
{
	int rezultat = 0;
	rezultat = c1.brStanovnika - c2.brStanovnika;
	if (rezultat == 0)
	{
		rezultat = strcmp(c1.grad, c2.grad);
	}

	return rezultat;
}
