#define q 3329
#define n 256
#define np 9 // np correspond to n'

struct Rq
{
	int tab[n];
};

int BytesToBits(int *bytes, int nbytes)
{
	// Convert bytes to bits
	// nbytes l
	// Return an array of 8l bits
	int nbits = 8 * nbytes;
	int bits[nbits];

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

	return *bits;
}

int CBD2(int *B, int *res)
{
	int eta = 2;
	int betas[512 * eta - 1];
	*betas = BytesToBits(B, 64 * eta);

	int a, b;

	int fs[256];

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

	return *fs;
}

int decode_l(int *B, int l)
{
	// l est un paramètre de la fonction decode
	int tailleB = 256 * l;
	int beta = BytesToBits(B, tailleB);

	// Le résultat est un polynôme F de degré 255
	int F[256];
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
}

int encode_l(int *F)
{
	int beta[];

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
	// Est-ce qu'on renvoit bien la liste des bytes ?
	return BitsToBytes(beta, 256 * l);
}