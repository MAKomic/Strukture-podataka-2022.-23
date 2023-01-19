#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LINE_SIZE 1024
#define MIN_BROJ_STANOVNIKA 500

#define USPJESAN_UNOS 1
#define USPJESAN_ISPIS 1
#define USPJESNO_BRISANJE 1

#define NEUSPJESNO_OTVARANJE_DATOTEKE -1
#define NEUSPJESNA_ALOKACIJA_MEMORIJE -1

typedef struct lista* poz;
typedef struct cvor* poz_;

typedef struct element
{
	char grad[MAX_LINE_SIZE];
	int brStanovnika;
}element;

typedef struct lista
{
	element el;
	poz next;
}lista;

typedef struct cvor
{
	char ime_drzave[MAX_LINE_SIZE];
	poz head;
	poz_ lijevo;
	poz_ desno;
}cvor;


poz_ citajDatoteku(char[MAX_LINE_SIZE], poz_);
int citajDruguDatoteku(char[MAX_LINE_SIZE], poz);

poz_ sortiraniUnosStablo(poz_, poz_);
int sortiraniUnos(poz, poz);
int gradCompare(element, element);

int ispis(poz, int);
int ispisInorder(poz_, int);

int brisiSve(poz);
int brisiStablo(poz_);


int main()
{
	poz_ root = NULL;
	root = (poz_)malloc(sizeof(cvor));
	poz_ root2 = NULL;
	root2 = root;

	root->desno = NULL;
	root->lijevo = NULL;

	int brStanovnika = MIN_BROJ_STANOVNIKA;
	char ime_datoteke[MAX_LINE_SIZE] = { 0 };

	printf("Unesi ime datoteke: ");
	scanf(" %s", ime_datoteke);

	root = citajDatoteku(ime_datoteke, root);
	while (root == NULL)
	{
		printf(" Upisi drugo ime: ");
		scanf(" %s", ime_datoteke);
		root = citajDatoteku(ime_datoteke, root2);
	}

	ispisInorder(root, MIN_BROJ_STANOVNIKA);

	while (1)
	{
		printf("\n\nUnesi broj stanovnika (0 za kraj programa): ");
		scanf("%d", &brStanovnika);
		if (brStanovnika == 0)
		{
			break;
		}

		printf("Popis gradova sa vise od %d stanovnika:\n\n", brStanovnika);
		ispisInorder(root, brStanovnika);
	}

	printf("\n\nKraj programa.");
	brisiStablo(root);

	return 0;
}


poz_ citajDatoteku(char ime_datoteke[MAX_LINE_SIZE], poz_ root)
{
	FILE* fp = NULL;

	char ime_nove_datoteke[MAX_LINE_SIZE] = { 0 };
	char tempIme[MAX_LINE_SIZE] = { 0 };

	fp = fopen(ime_datoteke, "r");

	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila!");
		return NULL;
	}

	poz head = NULL;

	head = (poz)malloc(sizeof(lista));

	if (head == NULL)
	{
		printf("Neuspjesna alokacija memorije!");
		return NULL;
	}

	head->next = NULL;

	head->el.brStanovnika = 0;
	strcpy(head->el.grad, " ");

	fscanf(fp, "%s %s", tempIme, ime_nove_datoteke);
	strcpy(root->ime_drzave, tempIme);
	citajDruguDatoteku(ime_nove_datoteke, head);
	root->head = head;

	while (!feof(fp))
	{
		poz_ tempRoot = NULL;

		tempRoot = (poz_)malloc(sizeof(cvor));

		if (tempRoot == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NULL;
		}

		tempRoot->lijevo = NULL;
		tempRoot->desno = NULL;
		tempRoot->head = NULL;
		strcpy(tempRoot->ime_drzave, " ");

		poz head = NULL;

		head = (poz)malloc(sizeof(lista));

		if (head == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NULL;
		}

		head->next = NULL;

		tempRoot->head = head;


		fscanf(fp, "%s %s", tempIme, ime_nove_datoteke);
		strcpy(tempRoot->ime_drzave, tempIme);
		citajDruguDatoteku(ime_nove_datoteke, head);
		tempRoot->head = head;
		root = sortiraniUnosStablo(root, tempRoot);
	}

	fclose(fp);

	return root;

}
int citajDruguDatoteku(char ime_nove_datoteke[MAX_LINE_SIZE], poz head)
{
	FILE* fp2 = NULL;
	poz temp = NULL;
	char pom[MAX_LINE_SIZE] = { 0 };

	fp2 = fopen(ime_nove_datoteke, "r");
	if (fp2 == NULL)
	{
		printf("Datoteka se nije otvorila!");
		return NULL;
	}

	while (!feof(fp2))
	{
		temp = (poz)malloc(sizeof(lista));
		if (temp == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NULL;
		}
		temp->next = NULL;
		strcpy(temp->el.grad, " ");
		temp->el.brStanovnika = 0;

		fscanf(fp2, "%s %d", pom, &(temp->el.brStanovnika));
		strcpy(temp->el.grad, pom);

		sortiraniUnos(head, temp);
	}

	fclose(fp2);

	return USPJESAN_UNOS;
}

poz_ sortiraniUnosStablo(poz_ root, poz_ temp)
{
	if (root == NULL)
	{
		return temp;
	}

	int rezultat = 0;
	rezultat = strcmp(root->ime_drzave, temp->ime_drzave);

	if (rezultat < 0)
	{
		root->desno = sortiraniUnosStablo(root->desno, temp);
	}

	else if (rezultat > 0)
	{
		root->lijevo = sortiraniUnosStablo(root->lijevo, temp);
	}

	else
	{
		free(temp);
	}

	return root;
}
int sortiraniUnos(poz head, poz temp)
{
	while ((head->next != NULL) && (gradCompare(head->next->el, temp->el) > 0))
	{
		head = head->next;
	}

	temp->next = head->next;
	head->next = temp;

	return USPJESAN_UNOS;
}
int gradCompare(element c1, element c2)
{
	int rezultat = 0;
	rezultat = c1.brStanovnika - c2.brStanovnika;
	if (rezultat == 0)
	{
		rezultat = strcmp(c1.grad, c2.grad);
	}

	return rezultat;
}

int ispis(poz head, int br)
{
	while (head->next != NULL && (head->next->el.brStanovnika > br))
	{
		printf("%s\t%d", head->next->el.grad, head->next->el.brStanovnika);
		printf("\n");
		head = head->next;
	}

	return USPJESAN_ISPIS;
}
int ispisInorder(poz_ root, int br)
{
	if (root == NULL)
	{
		return USPJESAN_ISPIS;
	}

	ispisInorder(root->lijevo, br);
	printf("%s:", root->ime_drzave);
	printf("\n");
	ispis(root->head, br);
	printf("\n\n");
	ispisInorder(root->desno, br);

	return USPJESAN_ISPIS;
}


int brisiSve(poz head)
{
	poz temp = NULL;

	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	return USPJESNO_BRISANJE;
}
int brisiStablo(poz_ root)
{
	if (root == NULL)
	{
		return USPJESNO_BRISANJE;
	}

	else if (root->lijevo != NULL)
	{
		brisiStablo(root->lijevo);
	}

	if (root->desno != NULL)
	{
		brisiStablo(root->desno);
	}

	brisiSve(root->head);
	free(root);

	return USPJESNO_BRISANJE;
}
