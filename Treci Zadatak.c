#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_STRING_LENGTH 1024

#define NOVA_OSOBA {{0},{0},0}

#define NEMA_ELEMENTA_U_LISTI -1
#define DATOTEKA_SE_NIJE_OTVORILA -1
#define MEMORIJA_NEUSPJESNO_ALOCIRANA -1

#define USPJESNO_BRISANJE 0
#define USPJESAN_ISPIS 0
#define USPJESAN_UNOS 0
#define USPJESNO_SORTIRANJE 0


typedef struct osoba {
	char ime[MAX_STRING_LENGTH];
	char prezime[MAX_STRING_LENGTH];
	int godrod;

}osoba;

typedef struct cvor* poz;

typedef struct cvor {
	osoba el;
	poz next;
}cvor;


int ispisIzbornika();

osoba unosOsobe();

int unosP(osoba, poz);
int unosK(osoba, poz);
int unosIspred(osoba, char[], poz);
int unosIza(osoba, char[], poz);
int sortiraniUnos(osoba, poz);

int ispis(poz);

poz trazi(char[], poz);
poz traziP(char[], poz);

int brisi(char[], poz);
int brisiSve(poz);

int citajListuIzDatoteke(char[], poz);
int upisiListuUDatoteku(char[], poz);

int sortirajListu(poz);
int zamjena(poz, poz);


int main()
{
	cvor head;
	head.next = NULL;

	
	char izbor = '1';
	char proizvoljno_prezime[MAX_STRING_LENGTH] = { 0 };
	char ime_datoteke[MAX_STRING_LENGTH] = { 0 };



	while (izbor != '0')
	{
		ispisIzbornika();
		printf("\n\nUnesi slovo: ");
		scanf(" %c", &izbor);
		switch (izbor)
		{
		case 'a':
			unosP(unosOsobe(), &head);
			break;

		case 'b':
			unosK(unosOsobe(), &head);
			break;

		case 'c':
			printf("Unesi prezime osobe ispred koje zelis unit novu osobu: ");
			scanf(" %s", proizvoljno_prezime);
			if (traziP(proizvoljno_prezime, &head) == NULL)
			{
				printf("Ne postoji osoba sa tin prezimenom.");
				break;
			}
			else
			{
				unosIspred(unosOsobe(), proizvoljno_prezime, &head);
				break;
			}

		case 'd':
			printf("Unesi prezime osobe iza koje zelis unit novu osobu: ");
			scanf(" %s", proizvoljno_prezime);
			if (trazi(proizvoljno_prezime, head.next) == NULL)
			{
				printf("Ne postoji osoba sa tin prezimenom.");
				break;
			}
			else
			{
				unosIza(unosOsobe(), proizvoljno_prezime, head.next);
				break;
			}

		case 'e':
			sortiraniUnos(unosOsobe(), &head);
			break;

		case 'f':
			ispis(head.next);
			break;

		case 'g':
			printf("Unesi prezime osobe koju zelis pronac: ");
			scanf(" %s", proizvoljno_prezime);
			printf("Adresa prezimena %s je %p",proizvoljno_prezime, trazi(proizvoljno_prezime, &head));
			break;

		case 'h':
			printf("Unesi prezime osobe koju zelis izbrisat: ");
			scanf(" %s", proizvoljno_prezime);
			brisi(proizvoljno_prezime, &head);
			break;

		case 'i':
			brisiSve(&head);
			break;

		case 'j':
			printf("Unesi ime datoteke iz koje ucitavas listu: ");
			scanf(" %s", ime_datoteke);
			citajListuIzDatoteke(ime_datoteke, &head);
			break;

		case 'k':
			printf("Unesi ime datoteke u koju upisujes studente: ");
			scanf(" %s", ime_datoteke);
			upisiListuUDatoteku(ime_datoteke, head.next);
			break;

		case 'l':
			sortirajListu(head.next);
			printf("Sortirano.");
			break;

		case '0':
			printf("Kraj programa.");
			brisiSve(&head);
			break;

		default:
			printf("Krivi unos.");

		}
	}

	return 0;
}


int ispisIzbornika()
{
	printf("\n<> <> <> <> <> IZBORNIK <> <> <> <> <>\n\na)Unos na pocetak\nb)Unos na kraj\nc)Unos ispred\nd)Unos iza\ne)Sortirani unos\n\nf)Ispis liste\n\ng)Trazi osobu po prezimenu\nh)Izbrisi osobu po prezimenu\ni)Brisi cilu listu\n\nj)Ucitaj listu iz datoteke\nk)Upisi listu u datoteku\n\nl)Sortiraj listu\n\n0)Kraj programa\n\n<> <> <> <> <> <> <> <> <> <> <> <> <> ");
	return USPJESAN_ISPIS;
}

osoba unosOsobe()
{
	osoba o = NOVA_OSOBA;

	printf("Unesi ime nove osobe: ");
	scanf("%s", o.ime);

	printf("Unesi prezime nove osobe: ");
	scanf("%s", o.prezime);

	printf("Unesi godinu rodenja nove osobe: ");
	scanf("%d", &(o.godrod));

	return o;
}

int unosP(osoba x, poz poz_head)
{
	poz q = NULL;
	q = (poz)malloc(sizeof(cvor));
	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija.");
		return MEMORIJA_NEUSPJESNO_ALOCIRANA;
	}

	q->el = x;
	q->next = poz_head->next;
	poz_head->next = q;

	return USPJESAN_UNOS;
}

int unosK(osoba x, poz poz_head)
{
	poz q = NULL;
	q = (poz)malloc(sizeof(cvor));
	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija.");
		return MEMORIJA_NEUSPJESNO_ALOCIRANA;
	}

	while (poz_head->next != NULL)
	{
		poz_head = poz_head->next;
	}

	q->el = x;
	poz_head->next = q;
	q->next = NULL;

	return USPJESAN_UNOS;
}

int unosIspred(osoba x, char proizvoljno_prezime[], poz poz_head)
{
	poz q = NULL;
	q = (poz)malloc(sizeof(cvor));
	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija.");
		return MEMORIJA_NEUSPJESNO_ALOCIRANA;
	}

	poz_head = traziP(proizvoljno_prezime, poz_head);

	if (poz_head == NULL)
	{
		printf("Greska! Element ne postoji u vezanoj listi.\n");
		return NEMA_ELEMENTA_U_LISTI;
	}

	else
	{
		q->el = x;
		q->next = poz_head->next;
		poz_head->next = q;

		return USPJESAN_UNOS;
	}

}

int unosIza(osoba x, char proizvoljno_prezime[], poz poz_prvog)
{
	poz q = NULL;
	q = (poz)malloc(sizeof(cvor));
	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija.");
		return MEMORIJA_NEUSPJESNO_ALOCIRANA;
	}

	poz_prvog = trazi(proizvoljno_prezime, poz_prvog);

	if (poz_prvog == NULL)
	{
		printf("Greska! Element ne postoji u vezanoj listi!\n");
		return NEMA_ELEMENTA_U_LISTI;
	}

	else
	{
		q->el = x;
		q->next = poz_prvog->next;
		poz_prvog->next = q;
		return USPJESAN_UNOS;
	}
}

int sortiraniUnos(osoba x, poz poz_head)
{
	poz q = NULL;
	q = (poz)malloc(sizeof(cvor));
	if (q == NULL)
	{
		printf("Neuspjesno alocirana memorija.");
		return MEMORIJA_NEUSPJESNO_ALOCIRANA;
	}

	while (poz_head->next != NULL && (strcmp(poz_head->next->el.prezime, x.prezime) < 0))
	{
		poz_head = poz_head->next;
	}

	while (poz_head->next!=NULL && strcmp(poz_head->next->el.prezime, x.prezime) == 0)
	{
		if (poz_head->next != NULL && (strcmp(poz_head->next->el.ime, x.ime) < 0))
		{
			poz_head = poz_head->next;
		}
		else
		{
			break;
		}
	}

	q->el = x;
	q->next = poz_head->next;
	poz_head->next = q;

	return USPJESAN_UNOS;
}

int ispis(poz poz_prvog)
{
	while (poz_prvog != NULL)
	{
		printf("%s %s %d\n", poz_prvog->el.ime, poz_prvog->el.prezime, poz_prvog->el.godrod);
		poz_prvog = poz_prvog->next;
	}
	return USPJESAN_ISPIS;
}

poz trazi(char prez[], poz poz_head)
{
	while (poz_head != NULL && (strcmp(poz_head->el.prezime, prez)) != 0)
	{
		poz_head = poz_head->next;
	}

	return poz_head;
}

poz traziP(char prez[], poz poz_head)
{
	poz pret = NULL;
	pret = poz_head;
	poz_head = poz_head->next;

	while (poz_head != NULL && (strcmp(poz_head->el.prezime, prez)) != 0)
	{
		pret = pret->next;
		poz_head = poz_head->next;
	}

	if (poz_head == NULL)
	{
		return NULL;
	}

	else
	{
		return pret;
	}
}

int brisi(char prez[], poz poz_head)
{
	poz prev = NULL, temp = NULL;
	prev = traziP(prez, poz_head);

	if (prev == NULL)
	{
		printf("Nema ga!");
		return NEMA_ELEMENTA_U_LISTI;
	}

	else
	{
		temp = prev->next;
		prev->next = temp->next;

		free(temp);
		return USPJESNO_BRISANJE;
	}
}

int brisiSve(poz poz_head)
{
	while (poz_head->next != NULL)
	{
		brisi(poz_head->next->el.prezime, poz_head);
	}
	return USPJESNO_BRISANJE;
}

int citajListuIzDatoteke(char ime_datoteke[], poz poz_head)
{
	FILE* fp = NULL;
	osoba o = NOVA_OSOBA;

	fp = fopen(ime_datoteke, "r");
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila.");
		return DATOTEKA_SE_NIJE_OTVORILA;
	}

	while (!feof(fp))
	{
		fscanf(fp, "%s %s %d", o.ime, o.prezime, &(o.godrod));
		sortiraniUnos(o, poz_head);
	}

	fclose(fp);
	return USPJESAN_UNOS;
}

int upisiListuUDatoteku(char ime_datoteke[], poz poz_prvog)
{
	FILE* fp = NULL;

	fp = fopen(ime_datoteke, "w");
	if (fp == NULL)
	{
		printf("Datoteka se nije otvorila.");
		return DATOTEKA_SE_NIJE_OTVORILA;
	}

	while (poz_prvog != NULL)
	{
		fprintf(fp, "%s %s %d\n", poz_prvog->el.ime, poz_prvog->el.prezime, poz_prvog->el.godrod);
		poz_prvog = poz_prvog->next;
	}

	fclose(fp);
	return USPJESAN_UNOS;
}

int sortirajListu(poz poz_prvog)
{
	poz kraj_nesortirane_liste = NULL, stacionarna_adresa_prvog = poz_prvog;

	while (stacionarna_adresa_prvog != kraj_nesortirane_liste)
	{
		while (poz_prvog->next != kraj_nesortirane_liste)
		{
			if (strcmp(poz_prvog->el.prezime, poz_prvog->next->el.prezime) == 0)
			{
				if (strcmp(poz_prvog->el.ime, poz_prvog->next->el.ime) > 0)
				{
					zamjena(poz_prvog, poz_prvog->next);
				}
			}
			else if (strcmp(poz_prvog->el.prezime, poz_prvog->next->el.prezime) > 0)
			{
				zamjena(poz_prvog, poz_prvog->next);
			}
			poz_prvog = poz_prvog->next;
		}
		kraj_nesortirane_liste = poz_prvog;
		poz_prvog = stacionarna_adresa_prvog;
	}

	return USPJESNO_SORTIRANJE;
}

int zamjena(poz trenutni, poz iduci)
{
	osoba temp = NOVA_OSOBA;

	temp = trenutni->el;
	trenutni->el = iduci->el;
	iduci->el = temp;

	return USPJESNO_SORTIRANJE;
}
