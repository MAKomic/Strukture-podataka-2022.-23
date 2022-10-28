#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING_LENGTH 1024
#define NEMA_ELEMENTA_U_LISTI -1
#define USPJESNO_BRISANJE 0
#define USPJESAN_ISPIS 0
#define USPJESAN_UNOS 0

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

int unosP(osoba, poz);
int ispis(poz);
int unosK(osoba, poz);
poz trazi(char[], poz);
int brisi(char[], poz);
poz traziP(char[], poz);
int unosIza(osoba, char[], poz);
int unosIspred(osoba, char[], poz);
int brisiSve(poz);

int ispisIzbornika();
osoba unosOsobe();

int main()
{
	cvor head;
	head.next = NULL;
	char izbor = '1';
	char proizvoljno_prezime[MAX_STRING_LENGTH] = { 0 };



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
			printf("Unesi prezime osobe koju zelis izbrisat: ");
			scanf("%s", proizvoljno_prezime);
			brisi(proizvoljno_prezime,&head);
			break;

		case 'd':
			printf("Unesi prezime osobe koju zelis pronac: ");
			scanf("%s", proizvoljno_prezime);
			printf(" %p", trazi(proizvoljno_prezime,&head));
			break;

		case 'e':
			brisiSve(&head);
			break;

		case 'f':
			//soritrani unos
			break;

		case 'g':
			ispis(head.next);
			break;

		case 'h':
			printf("Unesi prezime osobe iza koje zelis unit novu osobu: ");
			scanf("%s", proizvoljno_prezime);
			unosIza(unosOsobe(),proizvoljno_prezime, head.next);
			break;

		case 'i':
			printf("Unesi prezime osobe ispred koje zelis unit novu osobu: ");
			scanf("%s", proizvoljno_prezime);
			unosIspred(unosOsobe(), proizvoljno_prezime, &head);
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

int unosP(osoba x, poz poz_head)
{
	poz q = NULL;

	q = (poz)malloc(sizeof(cvor));

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

int unosK(osoba x, poz poz_head)
{
	poz q = NULL;

	q = (poz)malloc(sizeof(cvor));

	while (poz_head->next != NULL)
	{
		poz_head = poz_head->next;
	}

	q->el = x;
	poz_head->next = q;
	q->next = NULL;

	return USPJESAN_UNOS;
}

poz trazi(char prez[], poz poz_head)
{
	while (poz_head != NULL && (strcmp(poz_head->el.prezime, prez)) != 0)
	{
		poz_head = poz_head->next;
	}

	return poz_head;
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

		return USPJESNO_BRISANJE;
		free(temp);
	}
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

int unosIza(osoba x, char proizvoljno_prezime[], poz poz_prvog)
{
	poz q = NULL;

	q = (poz)malloc(sizeof(cvor));

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

int unosIspred(osoba x, char proizvoljno_prezime[], poz poz_head)
{
	poz q = NULL;

	q = (poz)malloc(sizeof(cvor));

	poz_head = traziP(proizvoljno_prezime, poz_head);

	if (poz_head->next == NULL)
	{
		printf("Greska! Element ne postoji u vezanoj listi!\n");
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

osoba unosOsobe()
{
	osoba o;
	o.ime[MAX_STRING_LENGTH] = { 0 };
	o.prezime[MAX_STRING_LENGTH] = { 0 };
	o.godrod = 0;

	printf("Unesi ime nove osobe: ");
	scanf("%s", o.ime);

	printf("Unesi prezime nove osobe: ");
	scanf("%s", o.prezime);

	printf("Unesi godinu rodenja nove osobe: ");
	scanf("%d", &(o.godrod));

	return o;
}

int brisiSve(poz poz_head)
{
	while (poz_head->next != NULL)
	{
		brisi(poz_head->next->el.prezime, poz_head);
	}
	return USPJESNO_BRISANJE;
}

int ispisIzbornika()
{
	printf("\n<> <> <> <> <> IZBORNIK <> <> <> <> <>\n\na)Unos na pocetak\nb)Unos na kraj\nc)Izbrisi osobu na osnov prezimena\nd)Trazi osobu na osnov prezimena\ne)Brisi cilu listu\nf)Sortirani unos\ng)Ispis liste\nh)Unos iza\ni)Unos ispred\n\n<> <> <> <> <> <> <> <> <> <> <> <> <> ");
	return USPJESAN_ISPIS;
}
