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

typedef struct lista
{
	char ime_drzave[MAX_LINE_SIZE];
	poz next;
	poz_ root;
}lista;

typedef struct element
{
	char grad[MAX_LINE_SIZE];
	int brStanovnika;
}element;

typedef struct cvor
{
	element el;
	poz_ lijevo;
	poz_ desno;
}cvor;


int citajDatoteku(char[MAX_LINE_SIZE], poz);
poz_ citajDruguDatoteku(char[MAX_LINE_SIZE], poz_);

poz_ sortiraniUnosStablo(poz_, poz_);
int sortiraniUnos(poz, poz);
int gradCompare(element, element);

int ispis(poz, int);
int ispisInorder(poz_, int);

int brisiSve(poz);
int brisiStablo(poz_);


int main()
{
	lista head;
	head.next = NULL;

	int brStanovnika = MIN_BROJ_STANOVNIKA;
	char ime_datoteke[MAX_LINE_SIZE] = { 0 };

	printf("Unesi ime datoteke: ");
	scanf(" %s", ime_datoteke);

	while (citajDatoteku(ime_datoteke, &head) == NEUSPJESNO_OTVARANJE_DATOTEKE)
	{
		printf(" Unesi drugo ime: ");
		scanf(" %s", ime_datoteke);

	}

	ispis(&head,MIN_BROJ_STANOVNIKA);

	while (1)
	{
		printf("\n\nUnesi broj stanovnika (0 za kraj programa): ");
		scanf("%d", &brStanovnika);
		if (brStanovnika == 0)
		{
			break;
		}

		printf("Popis gradova sa vise od %d stanovnika:\n\n", brStanovnika);
		ispis(&head, brStanovnika);
	}

	printf("\n\nKraj programa.");
	brisiSve(&head);

	return 0;
}


int citajDatoteku(char ime_datoteke[MAX_LINE_SIZE], poz head)
{
	FILE* fp = NULL;

	char ime_nove_datoteke[MAX_LINE_SIZE] = { 0 };
	char tempIme[MAX_LINE_SIZE] = { 0 };

	fp = fopen(ime_datoteke, "r");
	
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila!");
		return NEUSPJESNO_OTVARANJE_DATOTEKE;
	}


	while (!feof(fp))
	{
		
		poz tempLista = NULL;

		tempLista = (poz)malloc(sizeof(lista));

		if (tempLista == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NEUSPJESNA_ALOKACIJA_MEMORIJE;
		}

		tempLista->next = NULL;
		tempLista->root = NULL;
		strcpy(tempLista->ime_drzave, " ");


		poz_ root = NULL;

		root = (poz_)malloc(sizeof(cvor));

		if (root == NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NEUSPJESNA_ALOKACIJA_MEMORIJE;
		}

		root->desno = NULL;
		root->lijevo = NULL;

		root->el.brStanovnika = 0;
		strcpy(root->el.grad, " ");



		tempLista->root = root;


		fscanf(fp, "%s %s", tempIme, ime_nove_datoteke);
		strcpy(tempLista->ime_drzave, tempIme);
		tempLista->root = citajDruguDatoteku(ime_nove_datoteke, root);
		sortiraniUnos(head, tempLista);
	}

	fclose(fp);

	return USPJESAN_UNOS;

}
poz_ citajDruguDatoteku(char ime_nove_datoteke[MAX_LINE_SIZE], poz_ root)
{
	FILE* fp2 = NULL;
	poz_ temp = NULL;
	char pom[MAX_LINE_SIZE] = { 0 };

	fp2 = fopen(ime_nove_datoteke, "r");
	if (fp2 == NULL)
	{
		printf("Datoteka se nije otvorila!");
		return NULL;
	}

	fscanf(fp2, " %s %d", pom, &(root->el.brStanovnika));
	strcpy(root->el.grad, pom);

	while (!feof(fp2))
	{
		temp = (poz_)malloc(sizeof(cvor));
		if(temp==NULL)
		{
			printf("Neuspjesna alokacija memorije!");
			return NULL;
		}
		temp->lijevo = NULL;
		temp->desno = NULL;
		strcpy(temp->el.grad, " ");
		temp->el.brStanovnika = 0;

		fscanf(fp2, "%s %d", pom, &(temp->el.brStanovnika));
		strcpy(temp->el.grad, pom);

		root = sortiraniUnosStablo(root, temp);
	}

	fclose(fp2);

	return(root);
}

poz_ sortiraniUnosStablo(poz_ root, poz_ temp)
{

	if (root == NULL)
	{
		return temp;
	}

	int rezultat = gradCompare(root->el, temp->el);

	if (rezultat > 0)
	{
		root->desno = sortiraniUnosStablo(root->desno, temp);
	}

	else if (rezultat < 0)
	{
		root->lijevo = sortiraniUnosStablo(root->lijevo, temp);
	}

	else
	{
		free(temp);
	}

	return root;
}
int sortiraniUnos(poz head, poz lista)
{
	while ((head->next != NULL) && strcmp((head->next->ime_drzave), (lista->ime_drzave)) < 0)
	{
		head = head->next;
	}

	lista->next = head->next;
	head->next = lista;

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
	while (head->next != NULL)
	{
		printf("%s:", head->next->ime_drzave);
		printf("\n");
		ispisInorder(head->next->root, br);
		head = head->next;
		printf("\n\n");
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
	if (root->el.brStanovnika > br)
	{
		printf("\t%s\t%d\n", root->el.grad, root->el.brStanovnika);

	}
	ispisInorder(root->desno, br);

	return USPJESAN_ISPIS;
}

int brisiSve(poz head)
{
	poz temp = NULL;

	while (head->next != NULL)
	{
		brisiStablo(head->next->root);
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

	free(root);

	return USPJESNO_BRISANJE;
}
