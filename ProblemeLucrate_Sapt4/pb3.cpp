#include <iostream>
#include <string>

using namespace std;

//tipuri necesare pt clasa-enum (sedan, SUV, Hatchback, Coupe}, const int id, nrMasini, anFabricatie,
// pret, marca, nr Proprietari, *varste proprietari
enum Caroserie{Sedan, SUV, Hatchback, Coupe};

class Masina 
{
	const int id;
	static int nrMasini;
	int anFabricatie;
	float pret;
	string marca;
	int nrProprietari;
	int* varsteProprietari;
	Caroserie caroserie;

public:
	Masina() :id(++nrMasini)
	{
		this->marca = "Default";
		this->anFabricatie = 0;
		this->pret = 0;
		this->nrProprietari = 0;
		this->caroserie = Sedan;
		this->varsteProprietari = nullptr;
	}

	Masina(string marca, int anFabricatie, float pret, int nrProprietari, int* varsteProprietari, Caroserie caroserie) :id(++nrMasini)
	{
		this->marca = marca;
		this->anFabricatie = anFabricatie;
		this->pret = pret;
		this->caroserie = caroserie;
		this->nrProprietari = nrProprietari;
		this->varsteProprietari = new int[this->nrProprietari];
		for (int i = 0; i < this->nrProprietari; i++)
			this->varsteProprietari[i] = varsteProprietari[i];
	}
	void afisareProprietari(string marca, int nrProprietari, int* varsteProprietari, Caroserie caroserie)
	{
		cout << this->id << ". Masina din marca " << this->marca << " de tip " << this->caroserie << " are un nou proprietar, acesta fiind al ";
		cout << this->nrProprietari << "-lea, iar lista cu varstele tuturor proprietarilor a devenit: ";
		for (int i = 0; i < this->nrProprietari; i++)
			cout << this->varsteProprietari[i] << " ";
	}

	//adaugare nou proprietar, si varsta acestuia cu metodele get si set

	int getnrProprietari()
	{
		return this->nrProprietari;
	}
	void setnrProprietari(int nrNouProprietari)
	{
		if (nrNouProprietari > 1)
			this->nrProprietari = nrNouProprietari;
		else
			throw exception();
	}

	int* getvarsteProprietari()
	{
		int* copievarsteProprietari = new int[this->nrProprietari];
		for (int i = 0; i < this->nrProprietari; i++)
		{
			copievarsteProprietari[i] = this->varsteProprietari[i];
		}
		return copievarsteProprietari;
	}
	void setvarsteProprietari(int* varsteNoiProprietari, int nrNouProprietari)
	{
		setnrProprietari(nrNouProprietari);
		if (this->varsteProprietari != nullptr)
			delete[] this->varsteProprietari;

		this->varsteProprietari = new int[this->nrProprietari];

		for(int i=0;i<this->nrProprietari;i++)
			this->varsteProprietari[i] = varsteNoiProprietari[i];

		delete[] varsteNoiProprietari;
	}

	~Masina()
	{
		if (this->varsteProprietari != nullptr)
			delete[] this->varsteProprietari;
	}
};

int Masina::nrMasini = 0;

int main()
{
	

	int* varsteProprietari1 = new int[3] {30, 40, 50};
	Masina* m1 = new Masina("Audi A4", 2020, 40000, 3, varsteProprietari1, Sedan);

	try {
		m1->setnrProprietari(4);
	}
	catch (...)
	{
		cout << "Eroare! Daca masina a fost cumparata de o noua persoana, aceasta nu poate fi primul proprietar sau un numar de maxim 0!";
	}

	//actualizam vectorul de varsteproprietari, inainte de afisare
	int *varsteNoiProprietari=m1->getvarsteProprietari();
	m1->setvarsteProprietari(new int[4]{30,40,50,55}, 4);
	m1->afisareProprietari("Audi A4", 4, varsteNoiProprietari, Sedan);

	delete[] varsteProprietari1;
	delete[] varsteNoiProprietari;
	delete m1;
}
