#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Calcola la somma binaria in colonna di due numeri interi mediante lo scorrimento binario.
//Considera anche il riporto dei bit più significativi.
int binary_sum_shift(int a, int b)
{
	int bit_length = sizeof(int) * 8;//Numero di bit per il tipo int.
	int sum_reversed = 0;//Somma rovesciata.
	int sum = 0;//Somma.
	int carry_over = 0;//Riporto.

	for (int i = 0; i < bit_length; i++, a>>= 1, b >>= 1)
	{
		//Bit meno significante di a e b.
		int LSBa = a & 1;
		int LSBb = b & 1;
		int bit_sum = LSBa + LSBb;//Somma dei due bit meno significanti.

		if (bit_sum == 2)
		{
			//Imposto il primo bit uguale al riporto.
			sum_reversed = (sum_reversed << 1) | carry_over;
			carry_over = 1;//Imposto il riporto a 1 per la somma successiva.
		}
		else
		{
			if (bit_sum + carry_over == 2)
			{
				//Imposto il primo bit a 0.
				sum_reversed = (sum_reversed << 1);
				carry_over = 1;//Imposto il riporto a 1 per la somma successiva.
			}
			else
			{
				//Importo il primo bit come somma dei bit dei due numeri più l'eventuale riporto.
				sum_reversed = (sum_reversed << 1) | (bit_sum + carry_over);
				carry_over = 0;//Azzero il riporto.
			}
		}
	}

	for (int i = 0; i < bit_length; i++, sum_reversed >>= 1)
	{
		//Rovescio la somma.
		sum = (sum << 1) | (sum_reversed & 1);
	}

	return sum;//Ritorno la somma.
}

//Ritorna il numero minimo di bit per rappresentare il numero.
int bit_length(int number)
{
	int i;//Contatore per il numero di bit.
	for (i = 0; number > 0; number /= 2, i++);//Finchè è divisibile per due aumento il contatore.
	return i;//Ritorno il numero di bit.
}

//Ritorna la base elevata all'esponente, entrambe intere.
int power(int b, int e)
{
	int p = 1;//Potenza.
	for (; e > 0; e--, p *= b);//Moltiplico per la base per sè stessa finchè l'esponente è maggiore di zero.
	return p;//Ritorno il valore della potenza ottenuta.
}

//Fattorizza il numero in binario, impostando anche la lunghezza dell'array contenente le cifre binarie.
int *factorize(int number, int *length)
{
	*length = bit_length(number);//Lunghezza in bit del numero.
	int *binary_digits = (int *)malloc(sizeof(int)* (*length));//Creo l'array che conterrà le cifre binarie del numero.
	//Imposto nell'array le cifre binarie ottenute dalla resto del numero per due e divido successivamente il numero per due.
	for (int i = 0; number > 0; binary_digits[i] = (number % 2), number /= 2, i++);
	return binary_digits;//Ritorno l'array contenente le cifre binarie.
}

//Converte un numero in binario in base decimale.
int defactorize(int *bits, int length)
{
	int number = 0;//Numero convertito da base 2 a base decimale.
	//Moltiplico ogni cifra binaria per la relativa potenza di due a esponente decrescente.
	for (int i = 0, e = length - 1; e > 0; number += bits[i] * power(2, e), e--, i++);
	return number;//Ritorno il numero convertito.
}

//Ritorna il massimo tra due interi.
int max(int a, int b)
{
	return a > b ? a : b;
}

//Ritorna il minimo tra due interi.
int min(int a, int b)
{
	return a < b ? a : b;
}

//Inverte l'array facendo perno sull'elemento centrale.
void reverse(int *a, int length)
{
	//Non considero la posizione centrale per array di dimensioni dispari.
	//Nel caso di array di dimensioni pari effettuo tutti gli swap.
	for (int i = 0; i < (length / 2); i++)
	{
		int temp = a[i];//Variabile temporanea.
		//Effettuo lo swap dei valori.
		a[i] = a[length - i - 1];
		a[length - i - 1] = temp;
	}
}

//Visualizza l'array.
void print_array(int *array, int length)
{
	for (int i = 0; i < length; i++)
	{
		printf("%d", array[i]);
	}
	
	printf("\r\n");
}

//Calcola la somma binaria in colonna di due numeri interi mediante la fattorizzazione.
//Considera anche il riporto dei bit più significativi.
int binary_sum_factorization(int a, int b)
{
	int a_bit_length = 0;//Lunghezza di a in bit.
	int *a_bits = factorize(a, &a_bit_length);//Array contenente le cifre binarie di a.

	int b_bit_length = 0;//Lunghezza di b in bit.
	int *b_bits = factorize(b, &b_bit_length);//Array contenente le cifre binarie di b.

	//Individuo la massima lunghezza binaria tra i due numeri aumentata di uno per un eventuale riporto.
	int max_length = max(a_bit_length, b_bit_length) + 1;
	int min_length = min(a_bit_length, b_bit_length);//Individuo la minima lunghezza binaria tra i due numeri.

	//Istanzio l'array che conterrà l'addizione binaria a lunghezza massima.
	int *sum_bits = (int *)malloc(sizeof(int)* max_length);
	//Inizializzo l'array a zero.
	memset(sum_bits, 0, sizeof(int)* max_length);

	int carry_over = 0;//Riporto della addizione binaria in colonna.

	//Sommo le cifre binarie per la lunghezza minima.
	for (int i = 0; i < min_length; i++)
	{
		//Somma dei bit.
		int bit_sum = a_bits[i] + b_bits[i];

		//Nel caso la somma sia due, cioè i due bit sono entrambi uno.
		if (bit_sum == 2)
		{
			//Nell'array inserisco l'eventuale riporto precedente.
			sum_bits[i] = carry_over;
			carry_over = 1;//Imposto il successivo riporto a 1.
		}
		else
		{
			//Se la somma dei bit e il riporto è due.
			if (bit_sum + carry_over == 2)
			{
				//Nell'array inserisco zero.
				sum_bits[i] = 0;
				carry_over = 1;//Imposto il successivo riporto a 1.
			}
			else
			{
				//Nell'array inserisco la somma dei bit e il riporto.
				sum_bits[i] = bit_sum + carry_over;
				carry_over = 0;//Imposto il successivo riporto a zero.
			}
		}
	}

	//Una volta superata la lunghezza minima, comune a entrambi gli array.
	//Proseguo all'inserimento delle rimanenti cifre binarie dell'array più lungo.
	for (int i = min_length; i < (max_length - 1); i++)
	{
		//Se la lunghezza maggiore corrisponde al primo array.
		if (a_bit_length == (max_length - 1))
		{
			//Se la somma dei bit e il riporto è due.
			if (a_bits[i] + carry_over == 2)
			{
				//Nell'array inserisco zero.
				sum_bits[i] = 0;
				carry_over = 1;//Imposto il successivo riporto a 1.
			}
			else
			{
				//Nell'array inserisco la somma dei bit e il riporto.
				sum_bits[i] = a_bits[i] + carry_over;
				carry_over = 0;//Imposto il successivo riporto a zero.
			}
		}
		else
		{
			//Se la lunghezza maggiore corrisponde al secondo array.
			//Se la somma dei bit e il riporto è due.
			if (b_bits[i] + carry_over == 2)
			{
				//Nell'array inserisco zero.
				sum_bits[i] = 0;
				carry_over = 1;//Imposto il successivo riporto a 1.
			}
			else
			{
				//Nell'array inserisco la somma dei bit e il riporto.
				sum_bits[i] = b_bits[i] + carry_over;
				carry_over = 0;//Imposto il successivo riporto a zero.
			}
		}
	}

	//Nel caso sia rimasto un riporto di overflow.
	if (carry_over)
	{
		//Inserisco il riporto nell'ultima posizione.
		sum_bits[(max_length - 1)] = carry_over;
	}

	//Inverto la somma dei bit per la successiva conversione.
	reverse(sum_bits, max_length);

	//Ritorno la somma convertita in base decimale.
	return defactorize(sum_bits, max_length);
}


int main()
{
	//Eseguo alcuni test di velocità per stabilire quale metodo sia più performante.
	time_t start = time(NULL);
	for (int i = 0; i < 1000000; i++)
	{
		binary_sum_shift(10, 50);
	}
	time_t end = time(NULL);

	printf("Binary sum shift: %f", difftime(end, start));
	printf("\r\n");

	start = time(NULL);
	for (int i = 0; i < 1000000; i++)
	{
		binary_sum_factorization(10, 50);
	}
	end = time(NULL);

	printf("Binary sum factorization: %f", difftime(end, start));
	getchar();

	return 0;
}
