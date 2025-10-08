#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

using namespace std;

void afisareVector(int* vector, int dim)
{
	for (int i = 0; i < dim; i++)
	{
		cout << endl << "Vector[" << i << "]= " << vector[i];
	}
}

//vom transmite parametrii prin valoare, deoarece nu modificam nimic,  ramane acelasi vector, aceeasi dimeniune

int pozMax(int* vector, int dimensiune)
{
	int p = 0;
	for (int i = 1; i < dimensiune; i++)
	{
		if (vector[p] < vector[i])
			p = i;
	}
	return p;
}

//functie de sterge de element de pe pozitie data
void stergere(int** vector, int* dim, int poz) 
{
	int* vectorCopie = new int[*dim - 1]; 
	int j = 0;
	for (int i = 0; i < *dim; i++)
	{
		if (j != poz)
		{
			vectorCopie[j] = (*vector)[i]; 
			j++;
		}
		else
		{
			vectorCopie[j] = (*vector)[i + 1];
			j++;
		}
	}

	delete[] * vector; 
	(*dim)--; 
	*vector = vectorCopie;
}
void main()
{
	char* nume;
	char sirCaractere[20];

	/*cout << endl << "Citim de la tastatura: ";
	cin.getline(sirCaractere, 20);

	cout << endl << "Sirul citit este: "<<sirCaractere;
	cin.getline(sirCaractere, 20);

	//definim un buffer

	char buffer[20];
	cout << endl << "Numele este: ";
	cin >> buffer;
	nume = new char[strlen(buffer) + 1];
	strcpy_s(nume, strlen(buffer) + 1, buffer);

	cout << endl << "Numele citit este: " << nume;
	*/


	//delete[] nume;
	//buffer->(sir caractere cu dim fixa), vb in care vom stoca pt un moment un sir de caractere

	//vectori
	int* vector;
	int dim = 5;

	vector = new int[dim];
	for (int i = 0; i < dim; i++)
	{
		cout << endl << "Vector[" << i << "]= ";
		cin >> vector[i];
	}
	afisareVector(vector, dim);

	cout << endl << "Pozitia pe care se afla maxium este: " << pozMax(vector, dim);
	int p;
	cout << endl << " Alege o pozitie de pe care sa stergem elementul ";
	cin >> p;
	cout << endl << "Elementul de pe pozitia " << p << " a fost sters "<<" Noul vector este ";
	stergere(&vector, &dim, p);
	afisareVector(vector, dim);

}