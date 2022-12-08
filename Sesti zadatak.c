#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_LINE_SIZE 1024

#define DATOTEKA_SE_NIJE_OTVORILA -1
#define NEUSPJESNA_ALOKACIJA -1

#define USPJESAN_UNOS 1
#define USPJESAN_ISPIS 1
#define USPJESNO_BRISANJE 1

#define NOVI_PROIZVOD { { 0 }, 0, 0 }

typedef struct cvor* poz;
typedef struct cvor_* poz_;

typedef struct proizvod {
	char naziv[MAX_LINE_SIZE];
	int kolicina;
	float cijena;
}proizvod;

typedef struct cvor {

	proizvod el;
	poz next;

}cvor;

typedef struct cvor_ {

	char dat[MAX_LINE_SIZE];
	poz lista;
	poz_ next;

}cvor_;


int usporediDatume(char [MAX_LINE_SIZE], char [MAX_LINE_SIZE]);

int pribrojiRedove(char[MAX_LINE_SIZE]);
int ucitajIzDatoteke(char [MAX_LINE_SIZE], poz_);

int sortiraniUnosPoDatumu(poz_, char [MAX_LINE_SIZE],poz);
int sortiraniUnosPoNazivu(proizvod, poz);

int isprintaj(poz_);

int pribrojiURasponu(char[MAX_LINE_SIZE], char[MAX_LINE_SIZE], char[MAX_LINE_SIZE], poz_);

int brisiSve(poz_);


int main()
{
	char tempNaziv[MAX_LINE_SIZE] = { 0 };
	char dat1[MAX_LINE_SIZE] = { 0 };
	char dat2[MAX_LINE_SIZE] = { 0 };
	char ime_datoteke[MAX_LINE_SIZE] = { 0 };
	cvor_ head;
	head.next = NULL;

	printf("Unesi ime datoteke: ");
	scanf(" %s", ime_datoteke);

	if (ucitajIzDatoteke(ime_datoteke, &head) == DATOTEKA_SE_NIJE_OTVORILA)
	{
		return 0;
	}

	isprintaj(&head);
	
	printf("Za kraj programa za ime artikla napisi \"kraj\"\n");

	while (1)
	{
		printf("\nUnesi ime artikla: ");
		scanf(" %s", tempNaziv);

		if (strcmp(tempNaziv, "kraj") == 0)
		{
			brisiSve(&head);
			return 0;
		}

		printf("Unesi prvi datum u obliku YYYY-MM-DD: ");
		scanf(" %s", dat1);

		printf("Unesi drugi datum u obliku YYYY-MM-DD: ");
		scanf(" %s", dat2);

		pribrojiURasponu(dat1, dat2, tempNaziv, &head);
	}
}

int usporediDatume(char datum1[MAX_LINE_SIZE], char datum2[MAX_LINE_SIZE])
{
	int rezultat, god1, god2 , mj1, mj2, dan1, dan2;
	rezultat = god1 = god2 = mj1 = mj2 = dan1 = dan2 = 0;

	sscanf(datum1, "%d-%d-%d", &god1, &mj1, &dan1);
	sscanf(datum2, "%d-%d-%d", &god2, &mj2, &dan2);

	rezultat = god1 - god2;
	if (rezultat == 0)
	{
		rezultat = mj1 - mj2;
		if (rezultat == 0)
		{
			rezultat = dan1 - dan2;
		}
	}

	return rezultat;
}

int pribrojiRedove(char ime_datoteke[MAX_LINE_SIZE])
{
	FILE* fp = NULL;
	int brRedova = 0;
	char buffer[MAX_LINE_SIZE] = { 0 };

	fp = fopen(ime_datoteke, "r");
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila.");
		return DATOTEKA_SE_NIJE_OTVORILA;
	}

	while (!feof(fp))
	{
		fgets(buffer, MAX_LINE_SIZE, fp);
		brRedova++;
	}

	brRedova--;

	return brRedova;
}
int ucitajIzDatoteke(char ime_datoteke[MAX_LINE_SIZE], poz_ head)
{
	int i = 0, j = 0;

	FILE* fp = NULL;
	FILE* fp2 = NULL;

	int brRacuna = pribrojiRedove(ime_datoteke);

	char datumTemp[MAX_LINE_SIZE] = { 0 };
	char ime_druge_datoteke[MAX_LINE_SIZE] = { 0 };
	
	proizvod p = NOVI_PROIZVOD;

	cvor* listaPomocnihCvorova=NULL;

	if (brRacuna == DATOTEKA_SE_NIJE_OTVORILA)
	{
		return DATOTEKA_SE_NIJE_OTVORILA;
	}

	listaPomocnihCvorova = (poz)malloc(sizeof(cvor)*brRacuna);
	for (i = 0; i < brRacuna; i++)
	{
		listaPomocnihCvorova[i].next = NULL;
	}

	fp = fopen(ime_datoteke, "r");
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila!\n");
		return DATOTEKA_SE_NIJE_OTVORILA;
	}

	for(j=0;j<brRacuna-1;j++)
	{
		fgets(ime_druge_datoteke, MAX_LINE_SIZE, fp);
		ime_druge_datoteke[strlen(ime_druge_datoteke) - 1] = '\0';

		fp2 = fopen(ime_druge_datoteke, "r");
		if (fp2 == NULL)
		{
			printf("Datoteka druga se nije otvorila!\n");
			return DATOTEKA_SE_NIJE_OTVORILA;
		}

		fgets(datumTemp, MAX_LINE_SIZE, fp2);

		while (!feof(fp2))
		{
			fscanf(fp2, "%s %d %f", p.naziv, &p.kolicina, &p.cijena);
			sortiraniUnosPoNazivu(p, &listaPomocnihCvorova[j]);

		}
		sortiraniUnosPoDatumu(head, datumTemp, &listaPomocnihCvorova[j]);
	}

	return USPJESAN_UNOS;
}

int sortiraniUnosPoDatumu(poz_ head, char datum[MAX_LINE_SIZE],poz pomocniCvor)
{
	poz_ q = NULL;
	q = (poz_)malloc(sizeof(cvor_));
	
	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija!");
		return NEUSPJESNA_ALOKACIJA;
	}

	while ((head->next != NULL) && (usporediDatume(head->next->dat,datum)<0))
	{
		head = head->next;
	}

	strcpy(q->dat, datum);
	q->lista = pomocniCvor;
	q->next = head->next;
	head->next = q;

	return USPJESAN_UNOS;
}
int sortiraniUnosPoNazivu(proizvod x, poz head)
{
	poz q = NULL;
	q = (poz)malloc(sizeof(cvor));

	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija!");
		return NEUSPJESNA_ALOKACIJA;
	}

	while (head->next != NULL && strcmp(x.naziv, head->next->el.naziv) > 0)
	{
		head = head->next;
	}

	q->el.cijena = x.cijena;
	q->el.kolicina = x.kolicina;
	strcpy(q->el.naziv, x.naziv);

	q->next = head->next;
	head->next = q;

	return USPJESAN_UNOS;
}

int isprintaj(poz_ head)
{
	poz_ temp = head;
	poz temp1 = temp->next->lista;
	while (temp->next != NULL)
	{
		temp1 = temp->next->lista;
		printf("\n\n\nDatum: %s", temp->next->dat);
		while (temp1->next != NULL)
		{
			printf("Ime artikla: %s\n", temp1->next->el.naziv);
			printf("Kolicina artikla: %d\n", temp1->next->el.kolicina);
			printf("Cijena arikla: %.2fkn\n\n", temp1->next->el.cijena);

			temp1 = temp1->next;
		}
		temp = temp->next;
	}

	return USPJESAN_ISPIS;
}

int pribrojiURasponu(char dat1[MAX_LINE_SIZE], char dat2[MAX_LINE_SIZE], char ime[MAX_LINE_SIZE], poz_ head)
{
	int brojArtikala = 0;
	float cijenaArtikala = 0;
	poz_ temp = head;
	poz temp1 = temp->next->lista;

	while (usporediDatume(dat1, temp->next->dat) > 0)
	{
		temp = temp->next;
	}
	while (usporediDatume(dat2, temp->next->dat) >= 0)
	{
		temp1 = temp->next->lista;
		while (temp1->next != NULL)
		{
			if (strcmp(temp1->next->el.naziv, ime) == 0)
			{
				brojArtikala += temp1->next->el.kolicina;
				cijenaArtikala += temp1->next->el.cijena* temp1->next->el.kolicina;
			}
			temp1 = temp1->next;
		}
		temp = temp->next;
	}

	printf("Kolicina artikla %s u unesenom rasponu je: %d\n", ime, brojArtikala);
	printf("Cijena artikla %s u unesenom rasponu je: %.2fkn\n", ime, cijenaArtikala);

	return USPJESAN_ISPIS;
}

int brisiSve(poz_ head)
{
	poz_ temp_ = NULL;
	poz temp = NULL;
	while (head->next != NULL)
	{
		while (head->next->lista->next != NULL)
		{
			temp = head->next->lista->next;
			head->next->lista->next = temp->next;
			free(temp);
		}

		temp_ = head->next;
		head->next = temp_->next;
		free(temp_);
	}

	return USPJESNO_BRISANJE;
}
