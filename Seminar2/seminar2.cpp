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
void stergere(int** vector, int* dim, int poz) //dimensiunea nu poate fi transmisa prin valoare, deoarece o modificam, scade; prima *->vector alocat dinamica, iar a doua *->vectorul e transmir prin pointer//daca am diferenta de o steluta de la apel la main atunci vectorul e transmis prin pointer
{
	int* vectorCopie = new int[*dim - 1]; //nu pot pune dim-1, deoarece e adresa-1, eu trebuie sa iau valoarea, adica folosesc DEREFERENTIERE, adica iau valoarea din adresa, deci *dim-1
	int j = 0;
	for (int i = 0; i < *dim; i++)
	{
		if (j != poz)
		{
			vectorCopie[j] = (*vector)[i]; //din nou dereferentiere, ca vb vector e transmisa prin paramterii, deci (*vector)[i]->cand averm paranteze drepte punem si d alea rotunde
			j++;
		}
		else
		{
			vectorCopie[j] = (*vector)[i + 1];
			j++;
			i++;
		}
	}

	delete[] * vector; //dezaloc vectorul ca nu mai am nevoie de el
	(*dim)--; //punem () sa fim siguri ca prioritizam dereferntierea
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

	//in c++ avem transmiterea prin valoare, prin referinta si prin pointer!!!
	//daca implementez prin valoare si modific una din variabile, atunci cand ma intorc in main sunt nemodificate (Dezavantaj la valoare)

	//avantajul transmiterii prin valoare este la afisare
	//la toate functiile de afisare folosim transmitere prin valoare
	//daca modificam parametrul pe parcursul functiei, avem transmitere fie prin referinta fie prin pointer
	cout << endl << "Pozitia pe care se afla maxium este: " << pozMax(vector, dim);

	stergere(&vector, &dim, 4);
	afisareVector(vector, dim);

}