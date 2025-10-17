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
		this->nrIngrediente = 0;
	}

	ProdusAlimentar(string denumire, int nrIngrediente) :id(++nrProduseAlimentare)
	{
		this->denumire = denumire;
		this->nrIngrediente=nrIngrediente;
	}
	//metoda de afisare a produselor care contin minim 5 ingrediente
	void ingrediente()
	{
		
			if (this->nrIngrediente >= 5)
				cout << this->denumire<<", ";
	}

};

int ProdusAlimentar::nrProduseAlimentare = 0;

int main()
{

	cout << endl << "Produsele ce contin cel putin 5 ingrediente sunt: ";

	ProdusAlimentar* pizza = new ProdusAlimentar("pizza", 5);
	pizza->ingrediente();
	delete pizza;

	ProdusAlimentar* sushi = new ProdusAlimentar("sushi", 3);
	sushi->ingrediente();
	delete sushi;

	ProdusAlimentar* paste = new ProdusAlimentar("paste", 4);
	paste->ingrediente();
	delete paste;

	ProdusAlimentar* Shaorma = new ProdusAlimentar("shaorma", 8);
	Shaorma->ingrediente();
	delete Shaorma;

	ProdusAlimentar* salata = new ProdusAlimentar("salata", 6);
	salata->ingrediente();
	delete salata;

}