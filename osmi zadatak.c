#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>

#define USPJESAN_UNOS 1
#define USPJESAN_ISPIS 1
#define USPJESNO_BRISANJE 1
#define POSTOJI_ROOT 1

#define NEUSPJESNA_ALOKACIJA -1
#define NE_POSTOJI_ROOT -1


typedef struct cvor* poz;
typedef struct red* poz_;

typedef struct cvor{
	int el;
	poz livo;
	poz desno;
}cvor;

typedef struct red {
	poz clan;
	poz_ next;
}red;

int ispisIzbornika();

poz unos(poz, poz);

int printInorder(poz);
int printPreorder(poz);
int printPostorder(poz);
int printLevel(poz, poz_);

poz brisi(poz, int);
poz nadiNajveci(poz);
poz nadiNajmanji(poz);

poz trazi(poz,int);

int brisiSve(poz);
int brisiRed(poz_);

int dodajNaKraj(poz_, poz);
poz skiniSaPocetka(poz_);

int main()
{
	cvor root;
	poz poz_root = &root;
	root.livo = NULL;
	root.desno = NULL;
	int kontorla_roota = NE_POSTOJI_ROOT;

	poz q = NULL;

	red head;
	head.next = NULL;

	char naredba = '1';
	int tempBr = 0;

	while (naredba != '0')
	{
		ispisIzbornika();

		printf("\nUnesi slovo: ");
		scanf(" %c", &naredba);

		switch (naredba)
		{

		case 'a':

			if (kontorla_roota == NE_POSTOJI_ROOT)
			{
				printf("Unesi novi element: ");
				scanf(" %d", &tempBr);

				root.el = tempBr;
				kontorla_roota = POSTOJI_ROOT;
			}

			else 
			{
				q = (poz)malloc(sizeof(cvor));
				q->livo = NULL;
				q->desno = NULL;
				if (q == NULL)
				{
					printf("Neuspjesna alokacija.");
					break;
				}
				printf("Unesi novi element: ");
				scanf(" %d", &(q->el));

				poz_root = unos(poz_root, q);
			}

			break;

		case 'b':

			printInorder(poz_root);

			break;

		case 'c':

			printPreorder(poz_root);

			break;

		case 'd':

			printPostorder(poz_root);

			break;

		case 'e':

			printLevel(poz_root, &head);
			brisiSve(poz_root);

			break;

		case 'f':

			printf("Unesi element koji zelis pobrisat: ");
			scanf("%d", &tempBr);

			poz_root = brisi(poz_root, tempBr);

			break;

		case 'g':

			printf("Unesi element koji zelis pronac: ");
			scanf(" %d", &tempBr);

			trazi(poz_root, tempBr);

			break;

		case '0':

			brisiSve(poz_root);
			brisiRed(&head);

			break;

		default:

			printf("\nKrivi unos!\n");
		}

	}

	return 0;
}

int ispisIzbornika()
{
	printf("\n<> <> <> <> <> IZBORNIK <> <> <> <> <>\n\na)Unesi element\nb)inorder\nc)preorder\nd)postorder\ne)levelorder\nf)brisi\ng)pretrazi\n\n0)Kraj programa\n\n<> <> <> <> <> <> <> <> <> <> <> <> <> ");
	return USPJESAN_ISPIS;
}

poz unos(poz p, poz q)
{
	if (p == NULL)
	{
		return q;
	}

	if (p->el < q->el)
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


int printInorder(poz p)
{
	if (p == NULL)
	{
		return USPJESAN_ISPIS;
	}

	printInorder(p->livo);
	printf(" %d", p->el);
	printInorder(p->desno);

	return USPJESAN_ISPIS;
}

int printPreorder(poz p)
{
	if (p == NULL)
	{
		return USPJESAN_ISPIS;
	}

	printf(" %d", p->el);
	printPreorder(p->livo);
	printPreorder(p->desno);

	return USPJESAN_ISPIS;
}

int printPostorder(poz p)
{
	if (p == NULL)
	{
		return USPJESAN_ISPIS;
	}

	printPostorder(p->livo);
	printPostorder(p->desno);
	printf(" %d", p->el);

	return USPJESAN_ISPIS;
}

int printLevel(poz p, poz_ head)
{
	while (p != NULL)
	{
		printf(" %d", p->el);

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


poz brisi(poz p, int br)
{
	if (p == NULL)
	{
		return NULL;
	}

	if (p->el < br)
	{
		p->desno = brisi(p->desno, br);
	}

	else if (p->el > br)
	{
		p->livo = brisi(p->livo, br);
	}

	else
	{
		if (p->livo) 
		{
			poz temp = nadiNajveci(p->livo);
			p->el = temp->el;
			p->livo = brisi(p->livo, temp->el);
		}

		else if (p->desno)
		{
			poz temp = nadiNajmanji(p->desno);
			p->el = temp->el;
			p->desno = brisi(p->livo, temp->el);
		}

		else
		{
			free(p);
			return NULL;
		}
	}

	return p;
}

poz nadiNajmanji(poz p)
{
	while (p->livo)
	{
		p = p->livo;
	}

	return p;
}

poz nadiNajveci(poz p)
{
	while (p->desno)
	{
		p = p->desno;
	}

	return p;
}


poz trazi(poz p, int br)
{
	while (p!=NULL && p->el != br)
	{
		if ((p->el) > br)
		{
			p = p->livo;
		}

		else
		{
			p = p->desno;
		}
	}

	if (p == NULL)
	{
		printf("Trazeni broj ne postoji u stablu.");
		return p;
	}

	else
	{
		printf("Adresa trazenog elementa je %p", p);
		return p;
	}
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


	if(root->desno!=NULL)
	{
		brisiSve(root->desno);
	}

	free(root);

	return USPJESNO_BRISANJE;

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
