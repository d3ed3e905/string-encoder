#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

struct string
{
	char *sir;
	double complexitate;
};

int citire(char *vp[])
{
	int n = 0;
	char sir[52] = {}; //sir auxiliar, utilizat pentru aflarea dimensiunii (pentru alocare)

	while (strcmp(sir, "END\n") != 0)
	{
		fgets(sir, 52, stdin);
		*(vp + n) = (char *)malloc(sizeof(char) * strlen(sir));
		strncpy(vp[n], sir, strlen(sir) - 1);
		++n;
	}
	return n; //returneaza cate numere s-au citit
}

void tip(char *vp[], int n, int *eticheta)
{
	int i, ch = 0, cuv = 0, nr = 0, j, ok;
	// ch = cate caractere sunt
	// cuv = cate cuvinte sunt
	// nr = cate numere sunt
	long int max = 2147483648, min = -2147483648;

	for (i = 0; i < n; i++)
	{
		//pentru siruri de 1 caracter
		if ((strlen(vp[i]) == 1) && (!((vp[i][0] > '0') && (vp[i][0] <= '9'))))
		{
			//CARACTER
			ch++;
			eticheta[i] = 2;
		}
		else if ((strlen(vp[i]) == 1) && (vp[i][0] == '0'))
		{
			//zero = CUVANT
			cuv++;
			eticheta[i] = 1;
		}
		else
		{
			if ((strlen(vp[i]) == 1) && ((vp[i][0] > '0') && (vp[i][0] <= '9')))
			{
				//NUMAR de o singura cifra, diferit de zero
				nr++;
				eticheta[i] = 3;
			}
			else
				//pentru siruri de peste 1 caracter
				if (strlen(vp[i]) > 1)
			{
				ok = 1;
				for (j = 0; j < strlen(vp[i]); j++)
					if (vp[i][j] == '0')
					{
						ok = 0;
						break;
					}
				if (ok == 0)
				{
					//daca gaseste cifra zero ==> CUVANT
					cuv++;
					eticheta[i] = 1;
				}
				else
				{
					ok = 1;
					for (j = 1; j < strlen(vp[i]); j++)
						if (!((vp[i][j] > '0') && (vp[i][j] <= '9')))
						{
							ok = 0;
							break;
						}
					//daca ok==1 ==> de la j=1, toate caracterele sunt cifre
					if ((ok == 1) &&
						((vp[i][0] == '-') || ((vp[i][0] > '0') && (vp[i][j] <= '9'))))
					{
						if ((atoi(vp[i]) >= min) && (atoi(vp[i]) <= max))
						{
							nr++;
							eticheta[i] = 3;
						}
						else
						{
							cuv++;
							eticheta[i] = 1;
						}
					}
					else
					{
						cuv++;
						eticheta[i] = 1;
					}
				}
			}
		}
	}
	printf("%d %d %d\n", cuv, ch, nr); //afisare mesaj dupa TASK 1
}

void strrev(char *x)
{
	//inverseaza secventa din cuvant
	int i, j;
	char aux;

	for (i = 0, j = strlen(x) - 1; i < j; i++, j--)
	{
		aux = x[i];
		x[i] = x[j];
		x[j] = aux;
	}
}

int cuvant_cu_cifre(char *v)
{
	int j, ok = 0;

	for (j = 0; j < strlen(v); j++)
		if ((v[j] >= '0') && (v[j] <= '9'))
		{
			ok = 1;
			break;
		}
	if (ok == 0)
		return 0; // nu contine cifre
	else
		return 1; //contine cifre
}

int divizor(char *y)
{ //gaseste cel mai mare divizor
	int j, d, l;

	d = 1;
	l = strlen(y);
	for (j = 1; j < l; j++)
		if ((l % j == 0) && (j > d))
			d = j;
	return d;
}

void cuvant(char *x)
{ //prelucreaza cuvantul
	char aux[52];
	int d;

	d = divizor(x);
	strncpy(aux, x, d);
	aux[d] = '\0';
	if (cuvant_cu_cifre(x) == 0)
	{
		strcpy(x, x + d);
		strcat(x, aux);
	}
	else
	{
		strcpy(x, x + d);
		strrev(x);
		strcat(x, aux);
	}
}

void caracter(char *v, char sir[])
{
	int index[3000] = {0}, i, j, n, min, max;
	char aux[200];
	char *x = strdup(v);

	aux[0] = '\0';
	n = strlen(x);
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (x[i] == x[j])
				index[i]++; //retine numarul de aparitii al fiecarui caracter
	min = index[0];
	max = index[0];
	for (i = 1; i < n; i++)
	{
		if (index[i] > max)
			max = index[i]; //gasire nr maxim de aparitii
		if (index[i] < min)
			min = index[i]; //gasire nr minim de aparitii
	}
	//concatenare caracter cu nr MAX de aparitii la mesajul final
	for (i = 0; i < n; i++)
		if (max == index[i])
		{
			strncpy(aux, x + i, 1);
			aux[1] = '\0';
			strcat(v, aux);
			break;
		}
	//concatenare caracter la mesajul final
	strcat(v, sir);
	//concatenare caracter cu nr MIN de aparitii la mesajul final
	for (i = 0; i < n; i++)
		if (min == index[i])
		{
			strncpy(aux, x + i, 1);
			aux[1] = '\0';
			strcat(v, aux);
			break;
		}
	free(x); //dezalocare memorie pentru x;
}

void numar_maxim(long int nr, int l, char *final)
{
	//calculare numar maxim obtinut prin rotatia cifrelor lui (nr)
	int i, cifra;
	long int max, a;
	char string[13];

	max = nr;
	for (i = 1; i < l; i++)
	{
		a = pow(10, l - 1);
		cifra = nr / a;
		nr = (nr % a) * 10 + cifra;
		if (max < nr)
			max = nr;
	}
	sprintf(string, "%ld", max); //transformare din numar in sir de caractere
	strcat(final, string);		 //concatenare la mesajul final
}

void numar_minim(long int nr, int l, char *final)
{
	//calculare numar minim obtinut prin rotatia cifrelor lui (nr)
	int i, cifra;
	long int min, a;
	char string[13];

	min = nr;
	for (i = 1; i < l; i++)
	{
		a = pow(10, l - 1);
		cifra = nr / a;
		nr = (nr % a) * 10 + cifra;
		if (nr < min)
			min = nr;
	}
	sprintf(string, "%ld", min); //transformare din numar in sir de caractere
	strcat(final, string);		 //concatenare la mesajul final
}

void prelucrare(int n, int eticheta[], char *vp[], char *final)
{
	//prelucrarea sirurilor in functie de eticheta[]
	int i, l;
	long int nr;

	for (i = 0; i < n; i++)
	{
		char sir[52];
		strcpy(sir, vp[i]);
		switch (eticheta[i])
		{
		case 1:
			cuvant(sir); //daca e cuvant
			strcat(final, sir);
			break;
		case 2:
			caracter(final, sir); //daca e caracter
			break;
		case 3:
			if (sir[0] != '-')
			{ //daca e numar pozitiv
				l = strlen(sir);
				nr = atoi(sir);
				numar_maxim(nr, l, final);
			}
			else
			{ //daca e numar negativ
				l = strlen(sir) - 1;
				nr = atoi(sir + 1);
				numar_minim(nr, l, final);
			};
			break;
		}
	}
}

void alocare(struct string *p, char *final, int nr_siruri, int ultim)
{
	//alocare dinamica
	int i, l;

	l = strlen(final) / nr_siruri + 1;
	for (i = 0; i < nr_siruri - 1; i++)
	{
		p[i].sir = (char *)malloc(l);
	}
	//alocare pentru ultimul sir
	i = nr_siruri - 1;
	p[i].sir = (char *)malloc(ultim + 1);
}

void impartire(struct string *p, char *final, int nr_siruri, int ultim)
{
	//imparte sirul "final" in (nr_siruri) siruri, pe care le adauga in structura
	int i, j = 0, lungime = 0, N = 0;

	lungime = strlen(final);
	N = (int)lungime / nr_siruri;
	for (i = 0; i < nr_siruri; i++)
	{
		if (j < (lungime - ultim))
		{
			p[i].sir[0] = '\0';
			strncpy(p[i].sir, final + j, N);
			p[i].sir[N + 1] = '\0';
			j = j + N;
		}
		else
			break;
	}
	//ultimul sir:
	i = nr_siruri - 1;
	p[i].sir[0] = '\0';
	j = lungime - ultim;
	strncpy(p[i].sir, final + j, ultim);
	p[i].sir[ultim + 1] = '\0';
}

void complex(struct string *p, int nr_siruri)
{
	//determina complexitatea fiecarui sir
	int i, j, suma, l;

	for (i = 0; i < nr_siruri; i++)
	{
		suma = 0;
		l = strlen(p[i].sir);
		for (j = 0; j < l; j++)
			suma = suma + (p[i].sir[j]);
		p[i].complexitate = (double)suma / (l);
	}
}

void descrescator(struct string *p, int nr_siruri)
{
	int i, j;
	double aux_complexitate;
	char aux_sir[200];

	for (i = 0; i < nr_siruri - 1; i++)
		for (j = i + 1; j < nr_siruri; j++)
			if ((p[i].complexitate < p[j].complexitate) ||
				((p[i].complexitate == p[j].complexitate) && (strcmp(p[i].sir, p[j].sir) > 0)))
			{
				//inversare complexitati
				aux_complexitate = p[i].complexitate;
				p[i].complexitate = p[j].complexitate;
				p[j].complexitate = aux_complexitate;
				//inversare siruri
				aux_sir[0] = '\0';
				strcpy(aux_sir, p[i].sir);
				strcpy(p[i].sir, p[j].sir);
				strcpy(p[j].sir, aux_sir);
			}
}

void reordonare(struct string *p, char *mesaj_final, int nr_siruri)
{
	//concateneaza in finctie de index: 0, n-1, 1, n-2, 2, n-3..
	int i, n;
	n = nr_siruri / 2;
	int suma = 0; //retine numarul de caractere din mesaj_final dupa fiecare concatenare

	for (i = 0; i < n; i++)
	{
		strcat(mesaj_final, p[i].sir);
		strcat(mesaj_final, p[(nr_siruri - 1 - i)].sir);
		suma = suma + strlen(p[i].sir) + strlen(p[(nr_siruri - 1 - i)].sir);
	}
	//daca nr_siruri este impar, afiseaza sirul din mijloc
	if (nr_siruri % 2 == 1)
	{
		strcat(mesaj_final, p[n].sir);
		suma = suma + strlen(p[n].sir);
	}

	mesaj_final[suma + 1] = '\0';
}

int main()
{
	int n = 0, l = 1, N = 0, i = 0, ultim = 0;
	int eticheta[100]; //vector cu valori 1(cuvant), 2(caracter) sau 3(numar)
	char *vp[100];
	char final[1000];

	final[0] = '\0';
	n = citire(vp); //cate siruri (cuvinte+caractere+numere) exista
	tip(vp, n - 2, eticheta);
	prelucrare(n - 2, eticheta, vp, final);
	puts(final); //afisare mesaj dupa TASK 2

	l = strlen(final);
	int nr_sir = atoi(vp[n - 2]); //nr de siruri
	N = l / nr_sir;				  //dimensiunea fiecarui sir din structura
	ultim = N + l % nr_sir;		  //dimensiunea ultimului sir din structura

	struct string v[nr_sir];

	if (nr_sir != 1)
	{
		char mesaj_final[5000];
		mesaj_final[0] = '\0';
		alocare(v, final, nr_sir, ultim);
		nr_sir = atoi(vp[n - 2]);
		impartire(v, final, nr_sir, ultim);
		complex(v, nr_sir);
		descrescator(v, nr_sir);
		reordonare(v, mesaj_final, nr_sir);
		puts(mesaj_final); //afisare mesaj dupa TASK 3
	}
	else
		puts(final); //afisare mesaj dupa TASK 3

	//dezalocare memorie
	for (i = 0; i < nr_sir; i++)
		free(v[i].sir);
	for (i = 0; i < n; i++)
		free(vp[i]);
	fflush(stdin);

	return 0;
}
