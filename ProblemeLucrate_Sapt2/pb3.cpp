#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

void citire(int* v, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		cout << endl << "v[" << i << "]= ";
		cin >> v[i];
	}
}
void afisare(int* v, int dim)
{
	for (int i = 0; i < dim; i++)
		cout << endl << "v[" << i << "]= " << v[i];
}
//Inversarea elementelor din vector
//transmitere prin referinta
void inversare_elemente(int*& v, int dim)
{
	int i,j=0;
	int *vcopie;
	vcopie = new int[dim];
	for (i = dim - 1; i >= 0; i--)
	{
		vcopie[j] = v[i];
		j++;
	}
	delete[] v;
	v = vcopie;
}
//Stergerea elementelor mai mici decat un nr dat din vector

//transmitere prin pointer
void stergere(int** v, int* dim, int nr)
{
	int i,j=0;
	int* vcopie;
	vcopie = new int[*dim];
	for (i = 0; i < *dim; i++)
	{
		while ((*v)[i] < nr)
			i++;
		vcopie[j] = (*v)[i];
		j++;
	}
	delete[] * v;
	(*dim) = j;
	*v = vcopie;
}
int main()
{
	int* v;
	int dim;
	cout << endl << "Da-i dimensiunea vectorului: ";
	cin >> dim;
	v = new int[dim];
	cout << endl << "Introdu elementele vectorului";
	citire(v, dim);
	cout << endl << "Vectorul inversat este: ";
	inversare_elemente(v, dim);
	afisare(v, dim);
	cout << endl << "Introdu o limita minima pe care o vrei in vector: ";
	int nr;
	cin >> nr;
	inversare_elemente(v, dim);
	stergere(&v, &dim, nr);
	if (dim > 0)
	{
		cout << endl << "Noul vector este: ";
		afisare(v, dim);
	}
	else
		cout << "Toate elementele au fost eliminate";
	delete[] v;
	return 0;
}