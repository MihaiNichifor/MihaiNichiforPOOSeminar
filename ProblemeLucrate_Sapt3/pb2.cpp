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
	ProdusAlimentar() :id(nrProduseAlimentare++)
	{
		this->denumire = "default";
		this->pret = 0;
		this->nrIngrediente = 0;
		this->cantitati = nullptr;
	}
	//constructor cu un parametru
	ProdusAlimentar(string denumire) :id(nrProduseAlimentare++)
	{
		this->denumire = denumire;
	}
	void afisare()
	{
		cout << endl << "Produsul cu id-ul " << this->id << " este " << this->denumire<<".";
	}
protected:
};

int ProdusAlimentar::nrProduseAlimentare = 0;


int main()
{

	ProdusAlimentar zero;
	zero.afisare();

	ProdusAlimentar* Spaghete = new ProdusAlimentar("Spaghete");
	Spaghete->afisare();
	delete Spaghete;
}