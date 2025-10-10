//Adaugare element (un nr dat pe pozitii pare)

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

void afisare(int* v, int dim)
{
	int i;
	for (i = 0; i < dim; i++)
		cout << endl << "v[" << i << "]= " << v[i];
}

//fct adaugare element dat de la tastatura pe pozitii pare

//cu transmitere prin pointeri

void adaugare(int** v, int* dim, int nr)
{
	int i, j;
	int* vcopie;
	j = 0;
	vcopie = new int[(*dim)*2
	];
	for (i = 0; i < (*dim)*2; i++)  //v: 4 5 6 7  //vcopie: 3 4 3 5 3 6 3 7
	{
		if (i % 2 == 0)
		{
			vcopie[j] = nr; 
			j++;
		}
		else
		{
			vcopie[j] = (*v)[i/2];
			j++;	
		}
	}
	delete[] *v;
	(*dim)=(*dim)*2;
	*v = vcopie;
}
int main()
{
	int* v;
	int dim;
	cout << endl << "Da-i dimensiunea vectorului: ";
	cin >> dim;
	v = new int[dim];
	cout << endl << "Scrie elementele vectorului: ";
	for (int i = 0; i < dim; i++)
	{
		cout << endl << "v[" << i << "]= ";
		cin >> v[i];
	}
	cout << endl << "Introdu o cifra pe care sa o adaugi pe pozitiile pare din vector: ";
	int nr;
	cin >> nr;
	adaugare(&v, &dim, nr);
	afisare(v, dim);
	delete[] v;
	return 0;
}