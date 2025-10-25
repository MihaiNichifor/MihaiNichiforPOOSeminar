#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

enum Caroserie{Sedan, SUV, Hatchback, Coupe};

class Masina {
	const int id;
	static int nrMasini;
	int anFabricatie;
	float pret;
	string marca;
	int nrProprietari;
	int* varsteProprietari;
	Caroserie caroserie;

public:
	Masina() :id(nrMasini++)
	{
		this->marca = "Default";
		this->anFabricatie = 0;
		this->pret = 0;
		this->nrProprietari = 0;
		this->varsteProprietari = 0;
		this->caroserie = Sedan;
	}

	Masina(string marca, int anFabricatie, float pret, int nrProprietari, int* varsteProprietari, Caroserie caroserie) :id(nrMasini++)
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

	void afisareMasina()
	{
		cout << endl << this->id << "." << " Masina din marca " << this->marca << " are tipul de caroserie ";
		if (this->caroserie == 0)
			cout << "Sedan ";
		if (this->caroserie == 1)
			cout << "SUV ";
		if (this->caroserie == 2)
			cout << "Hatchback ";
		if (this->caroserie == 3)
			cout << "Coupe ";
		cout << " ,s-a fabricat in anul " << this->anFabricatie << " ,costa " << this->pret << " euro si a avut un numar de " << this->nrProprietari <<
			" proprietari, acestia avand varstele de: ";
		for (int i = 0; i < this->nrProprietari; i++)
			cout << this->varsteProprietari[i] << " ani,";
	}
	
	float getPret()
	{
		return this->pret;
	}

	void setPret(float pretNou)
	{
		if (pretNou > 10000)
			this->pret = pretNou;
		else
			throw exception();
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
	Masina zero;
	zero.afisareMasina();

	int* varsteProprietari1 = new int[3] {32, 40, 44};
	Masina* Skoda = new Masina("Skoda Octavia", 2021, 16000, 3, varsteProprietari1, Sedan);
	Skoda->afisareMasina();

	int* varsteProprietari2 = new int[2] {41, 50};
	Masina* Volvo = new Masina("Volvo XC90", 2019, 25000, 2, varsteProprietari2, SUV);
	Volvo->afisareMasina();

	//A trecut un an, iar cele 2 masini s-au depreciat. Scriere get si set pt modificarea preturilor.
	//Mai jos de 10000 euro nu pot costa cele 2 masini

	cout << endl << endl;


	try
	{
		Skoda->setPret(14000);
	}
	catch (...)
	{
		cout << "Pretul este mult prea mic!!";
	}

	cout << "In urma deprecierii noul pret pentru Skoda Octavia a devenit " << Skoda->getPret()<<" euro.";

	try
	{
		Volvo->setPret(21500);
	}
	catch (...)
	{
		cout << "Pretul este mult prea mic!!";
	}

	cout << endl << endl;
	cout << "In urma deprecierii noul pret pentru Volvo XC90 a devenit " << Volvo->getPret() << " euro.";

	
}