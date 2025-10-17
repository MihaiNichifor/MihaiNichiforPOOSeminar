#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class ProdusAlimentar
{
private:
	float pret;
	const int id;
	string denumire;
	int nrIngrediente;
	float* cantitati;
	static int nrProduseAlimentare;

public:
	ProdusAlimentar() :id(++nrProduseAlimentare)
	{
		this->denumire = "Default";
		this->pret = 0;
		this->nrIngrediente = 0;
		this->cantitati = nullptr;
	}

	ProdusAlimentar(string denumire, float pret, int nrIngrediente, float* cantitatiIngrediente) :id(++nrProduseAlimentare)
	{
		this->denumire = denumire;
		this->pret = pret;
		this->nrIngrediente = nrIngrediente;
		this->cantitati = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++)
		{
			this->cantitati[i] = cantitatiIngrediente[i];
		}

		delete[] cantitatiIngrediente;
	}
	void afisare()
	{
		cout << endl << this->id << ". Produsul " << this->denumire << " costa " << this->pret << " lei si contine "
			<< this->nrIngrediente << " ingrediente, cantitatile lor fiind de: ";
		if (this->cantitati != nullptr)
		{
			for (int i = 0; i < this->nrIngrediente - 1; i++)
				cout << cantitati[i] << " grame, ";

			cout << this->cantitati[nrIngrediente - 1] << " grame.";
		}
	}

	~ProdusAlimentar()
	{
		if (this->cantitati != nullptr)
			delete[] this->cantitati;
	}
protected:

};

int ProdusAlimentar::nrProduseAlimentare = 0;

int main()
{
	ProdusAlimentar zero;
	zero.afisare(); //aici afisez defaultul daca nu dau valori
	
	float* cantitati1 = new float[2] {50, 150};
	ProdusAlimentar* pizza = new ProdusAlimentar("pizza", 43, 2, cantitati1);
	pizza->afisare();
	delete pizza;

	float* cantitati2 = new float[3] {80, 100, 200};
	ProdusAlimentar* sushi = new ProdusAlimentar("sushi", 40, 3, cantitati2);
	sushi->afisare();
	delete sushi;
}