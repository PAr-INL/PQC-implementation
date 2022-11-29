#include <stdlib.h>
#include <stdio.h>

#define q 3329
#define n 256
#define np 9 // np correspond to n'

int *BytesToBits(int *bytes, int nbytes)
{
	// Convert bytes to bits
	// nbytes l
	// Return an array of 8l bits
	int nbits = 8 * nbytes;

	// On crée le tableau dans lequel on va mettre le résultat. On reverra un pointeur vers celui-ci en sortie
	int *bits;
	bits = (int *)malloc(nbits * sizeof(int));

	int i;

	// 2**(i mod 8)
	int puissance2 = 1;

	for (i = 0; i < nbits; i++)
	{
		bits[i] = bytes[i / 8] / puissance2 % 2;

		if (i % 8 == 7)
		{
			puissance2 = 1;
		}
		else
		{
			puissance2 = puissance2 * 2;
		}
	}

	return bits;
}

int *BitsToBytes(int *bits, int nbits)
{
	// Return an array of 8l bits
	int nbytes = nbits / 8;

	int *bytes;
	bytes = (int *)malloc(nbytes * sizeof(int));

	int i;
	int j;

	for (i = 0; i < nbytes; i++)
	{
		bytes[i] = 0;
		int puissance2 = 1;
		for (j = 0; i < 8; j++)
		{
			bytes[i] = bytes[i] + bits[i * 8 + j] * puissance2;
			puissance2 = puissance2 * 2;
		}
	}

	return bytes;
}

int *CBD2(int *B)
{
	int eta = 2;

	int *betas = BytesToBits(B, 64 * eta);

	int a, b;

	// On crée le tableau dans lequel on va mettre le résultat. On reverra un pointeur vers celui-ci en sortie
	int *fs;
	fs = (int *)malloc(256 * sizeof(int));

	int i;
	for (i = 0; i <= 255; i++)
	{
		a = 0;
		b = 0;
		int j;
		for (j = 0; j < eta - 1; j++)
		{
			a = a + betas[2 * i * eta + j];
			b = b + betas[2 * i * eta + eta + j];
		}
		fs[i] = a - b;
	}

	return fs;
}

int *decode_l(int *B, int l)
{
	// l est un paramètre de la fonction decode
	int tailleB = 256 * l;
	int *beta = BytesToBits(B, tailleB);

	// Le résultat est un polynôme F de degré 255

	// On crée le tableau dans lequel on va mettre le résultat. On reverra un pointeur vers celui-ci en sortie
	int *F;
	F = (int *)malloc(256 * sizeof(int));

	for (int i = 0; i <= 255; i++)
	{
		F[i] = 0;
		int deuxpuissancej = 1;
		for (int j = 0; j <= l - 1; j++)
		{
			// Le problème de i pointeur est du à la fonction BytesToBits qui renvoie un espèce de pointeur qui ne fonctionne pas vraiment.
			F[i] = F[i] + beta[i * l + j] * deuxpuissancej;
			deuxpuissancej = 2 * deuxpuissancej;
		}
	}
	return F;
}

int *encode_l(int *F, int l)
{
	int beta[256 * l];

	for (int i = 0; i <= 255; i++)
	{
		F[i] = 0;
		int deuxpuissancej = 1;
		for (int j = 0; j <= l - 1; j++)
		{
			// Le problème de i pointeur est du à la fonction BytesToBits qui renvoie un espèce de pointeur qui ne fonctionne pas vraiment.
			beta[i * l + j] = (F[i] % (2 * deuxpuissancej)) / deuxpuissancej;
			deuxpuissancej = 2 * deuxpuissancej;
		}
	}
	// Est-ce qu'on renvoie bien la liste des bytes ?

	return BitsToBytes(beta, 256 * l);
}

int main()
{
	int test[8] = {1, 2, 3, 4, 5, 6, 7, 8};

	int *betas = BytesToBits(test, 8);

	int loop;

	for (loop = 0; loop < 10; loop++)
	{
		printf("%d ", test[loop]);
	}

	for (loop = 0; loop < 10; loop++)
	{
		printf("%d ", betas[loop]);
	}

	return 0;
}