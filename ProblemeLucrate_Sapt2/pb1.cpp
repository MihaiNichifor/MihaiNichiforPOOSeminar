#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

//stergere element vector de pe o pozitie data de la tastatura

//cu subprogram prin referinta
void stergere_referinta(int *&v, int& dim, int p)
{
	int* vcopie;
	vcopie = new int[dim-1];
	int j = 0;
	for (int i = 0; i < dim; i++)
	{
		if (p != j)
		{
			vcopie[j] = v[i];
			j++;
		}
		else
		{
			vcopie[j] = v[i + 1];
			j++;
			i++;
		}
	}
	dim--;
	v = vcopie;
}
void afisare(int *v, int dim)
{
	for (int i = 0; i < dim; i++)
		cout << endl<< "v[" << i << "]=" << v[i];
}
int main()
{
	int* v;
	int dim = 6;
	v = new int[dim];
	cout << endl << "Introdu elementele vectorului:";
	for (int i = 0; i < dim; i++)
	{
		cout << endl << "v[" << i << "]= ";
		cin >> v[i];
	}

	cout << endl << "Elementele vectorului v sunt: ";
	afisare(v, dim);
	cout << endl<< "Introdu pozitia de pe care doresti sa stergi elementul: ";
	int p;
	cin >> p;
	if (p < 0 || p>5)
	{
		cout << endl << "Din pacate, pozitia nu exista in vector";
		return 0;
	}
	else
	{
		stergere_referinta(v, dim, p);
		cout << endl << "Noul vector este: ";
		afisare(v, dim);
	}
	delete[] v;
	return 0;
}