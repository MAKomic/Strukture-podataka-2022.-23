#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_LINE_SIZE 1024
#define BROJ_ELEMENATA 10

#define NEUSPJESNA_ALOKACIJA -1


#define USPJESAN_ISPIS 1
#define USPJESAN_UNOS 1
#define USPJESNO_BRISANJE 1

typedef struct cvor* poz;
typedef struct red* poz_;

typedef struct cvor {
	int el;
	poz livo;
	poz desno;
}cvor;

typedef struct red {
	poz clan;
	poz_ next;
}red;

poz insert(poz, poz);
int replace(poz, poz_, poz_, int*);

int suma_podstabla(poz, poz_, int*);

int upisiUDatoteku(char[MAX_LINE_SIZE], poz, poz, poz_);

int printLevel(poz, poz_);
int printInorder(poz, poz_);

int dodajNaKraj(poz_, poz);
poz skiniSaPocetka(poz_);

int brisiSve(poz);
int brisiRed(poz_);


int main()
{
	srand(time(0));

	cvor root;
	poz poz_root = &root;
	root.livo = NULL;
	root.desno = NULL;

	cvor root2;
	poz poz_root2 = &root2;
	root2.livo = NULL;
	root2.desno = NULL;

	int i = 0;
	int suma = 0;
	int tempBroj = 0;
	int listaElemenata[] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };

	char ime_datoteke[MAX_LINE_SIZE];

	poz q = NULL;

	red head;
	red head2;
	red head3;
	head.next = NULL;
	head2.next = NULL;
	head3.next = NULL;

	root.el = listaElemenata[0];


	printf("Zadani brojevi su:\n");
	for (i = 0; i < BROJ_ELEMENATA; i++)
	{
		printf("%d ", listaElemenata[i]);
	}

	for (i = 1; i < BROJ_ELEMENATA; i++)
	{
		q = (poz)malloc(sizeof(cvor));
		q->livo = NULL;
		q->desno = NULL;
		if (q == NULL)
		{
			printf("Neuspjesna alokacija.");
			return NEUSPJESNA_ALOKACIJA;
		}
		(q->el) = listaElemenata[i];

		poz_root = insert(poz_root, q);
	}

	printf("\n\nNjihov levelOrder ispis:\n");
	printLevel(poz_root, &head);

	replace(&root, &head3, &head2, &suma);
	printf("\n\nLevelOrder nakon promjene: \n");
	printLevel(poz_root, &head);

	printf("\n\n\n\nSlucajni brojevi su: \n");

	for (i = 0; i < BROJ_ELEMENATA; i++)
	{	
		tempBroj = (rand() % 78 + 12);
		printf("%d ", tempBroj);
		listaElemenata[i] = tempBroj;
	}

	root2.el = listaElemenata[0];

	for (i = 1; i < BROJ_ELEMENATA; i++)
	{
		q = (poz)malloc(sizeof(cvor));
		q->livo = NULL;
		q->desno = NULL;
		if (q == NULL)
		{
			printf("Neuspjesna alokacija.");
			return NEUSPJESNA_ALOKACIJA;
		}
		(q->el) = listaElemenata[i];

		poz_root2 = insert(poz_root2, q);
	}

	printf("\n\nNjihov levelOrder ispis:\n");
	printLevel(poz_root2, &head);

	replace(&root2, &head3, &head2, &suma);
	printf("\n\nLevelOrder nakon promjene: \n");
	printLevel(poz_root2, &head);

	printf("\n\nUnesi ime datoteke koju zelis stvorit: ");
	scanf(" %s", ime_datoteke);

	if ((upisiUDatoteku(ime_datoteke, poz_root, poz_root2, &head)) == USPJESAN_UNOS)
	{
		printf("\nUspjesan unos!\n\n");
	}
	
	/*
	brisiSve(poz_root);
	brisiSve(poz_root2);

	brisiRed(&head);
	brisiRed(&head2);
	brisiRed(&head3);
	*/
	
	return 0;
}

poz insert(poz p, poz q)
{
	if (p == NULL)
	{
		return q;
	}

	if (p->el > q->el)
	{
		p->desno = insert(p->desno, q);
	}

	else if (p->el <= q->el)
	{
		p->livo = insert(p->livo, q);
	}

	return p;
}
int replace(poz p, poz_ head3, poz_ head2, int* suma)
{
	while (p != NULL)
	{
		*suma = 0;
		suma_podstabla(p, head2, suma);
		p->el = ((*suma) - (p->el));

		if (p->livo != NULL)
		{
			dodajNaKraj(head3, p->livo);
		}

		if (p->desno != NULL)
		{
			dodajNaKraj(head3, p->desno);
		}

		p = skiniSaPocetka(head3);

	}

	return USPJESAN_ISPIS;
}

int suma_podstabla(poz p, poz_ head, int* suma)
{
	while (p != NULL)
	{
		(*suma) += p->el;

		if (p->livo != NULL)
		{
			dodajNaKraj(head, p->livo);
		}

		if (p->desno != NULL)
		{
			dodajNaKraj(head, p->desno);
		}

		p = skiniSaPocetka(head);

	}

	return USPJESAN_ISPIS;
}

int upisiUDatoteku(char ime_datoteke[MAX_LINE_SIZE], poz poz_root, poz poz_root2, poz_ head)
{
	int i = 0;
	FILE* fp = NULL;
	fp = fopen(ime_datoteke, "w");
	if (fp == NULL)
	{
		printf("Neuspjesna alokacija.");
		return NEUSPJESNA_ALOKACIJA;
	}

	printInorder(poz_root, head);

	for (i = 0; i < BROJ_ELEMENATA; i++)
	{
		fprintf(fp, " %d", (skiniSaPocetka(head)->el));
	}

	fprintf(fp, "\n");

	printInorder(poz_root2, head);
	for (i = 0; i < BROJ_ELEMENATA; i++)
	{
		fprintf(fp, " %d", (skiniSaPocetka(head)->el));
	}

	fclose(fp);
	return USPJESAN_UNOS;
}

int printLevel(poz p, poz_ head)
{
	while (p != NULL)
	{
		printf("%d ", p->el);

		if (p->livo != NULL)
		{
			dodajNaKraj(head, p->livo);
		}

		if (p->desno != NULL)
		{
			dodajNaKraj(head, p->desno);
		}

		p = skiniSaPocetka(head);

	}

	return USPJESAN_ISPIS;
}
int printInorder(poz p, poz_ head)
{
	if (p == NULL)
	{
		return USPJESAN_ISPIS;
	}

	printInorder(p->livo, head);
	dodajNaKraj(head, p);
	printInorder(p->desno, head);

	return USPJESAN_ISPIS;
}

poz skiniSaPocetka(poz_ head)
{
	if (head->next == NULL)
	{
		return NULL;
	}

	else
	{
		poz_ temp = NULL;
		temp = head->next;
		head->next = temp->next;
		return (temp->clan);
	}
}
int dodajNaKraj(poz_ head, poz p)
{
	poz_ q = NULL;
	q = (poz_)malloc(sizeof(red));
	if (q == NULL)
	{
		printf("Neusjpjesna alokacija.");
		return NEUSPJESNA_ALOKACIJA;
	}

	while (head->next != NULL)
	{
		head = head->next;
	}

	q->clan = p;
	head->next = q;
	q->next = NULL;

	return USPJESAN_UNOS;
}

int brisiSve(poz root)
{
	if (root == NULL)
	{
		return USPJESNO_BRISANJE;
	}

	else if (root->livo != NULL)
	{
		brisiSve(root->livo);
	}


	if (root->desno != NULL)
	{
		brisiSve(root->desno);
	}

	free(root);

	return USPJESNO_BRISANJE;

}
int brisiRed(poz_ head)
{
	poz_ temp = NULL;
	while (head->next != NULL)
	{
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}

	return USPJESNO_BRISANJE;
}
