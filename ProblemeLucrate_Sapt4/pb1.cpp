#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

using namespace std;

enum Tip{BIO, DE_BAZA,NORMAL};

class ProdusAlimentar
{
private:
	const int id;
	float pret;
	string denumire;
	int nrIngrediente;
	float* cantitati;
	Tip tip;
	static int nrProduseAlimentare;


public:
	ProdusAlimentar() :id(++nrProduseAlimentare)
	{
		this->denumire = "Default";
		this->pret = 0;
		this->nrIngrediente = 0;
		this->cantitati = nullptr;
		this->tip = NORMAL;
	}

	ProdusAlimentar(string denumire, float pret, int nrIngrediente, float *cantitati, Tip tip) :id(++nrProduseAlimentare)
	{
		this->denumire = denumire;
		this->pret = pret;
		this->nrIngrediente = nrIngrediente;
		this->cantitati = new float[nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++)
			this->cantitati[i] = cantitati[i];
		this->tip = tip;

		delete[] cantitati;
	}

	void afisareProdusAlimentar()
	{
		cout << this->id << ". " << " Acest produs se numeste " << this->denumire << " ,costa " << this->pret << " lei,este de tipul ";
		if (this->tip == 0)
			cout << "BIO";
		if (this->tip == 1)
			cout << "DE_BAZA";
		if (this->tip == 2)
			cout << "NORMAL";
		cout << ", contine " << this->nrIngrediente << " ingrediente, acestea avand cantitatile de: ";
		for (int i = 0; i < this->nrIngrediente; i++)
			cout << this->cantitati[i] << " grame, ";
	}

	string getdenumire()
	{
		return this->denumire;
	}
	void setdenumire(string denumireNoua)
	{
		this->denumire = denumireNoua;
	}

	float getpret()
	{
		return this->pret;
	}
	void setpret(float pretNou)
	{
		if (pretNou > 0)
			this->pret = pretNou;
		else
			throw exception();
	}

	int getnrIngrediente()
	{
		return this->nrIngrediente;
	}
	void setnrIngrediente(int nrIngredienteNou)
	{
		if (nrIngredienteNou > 0)
		{
			this->nrIngrediente = nrIngredienteNou;
		}
		else
		{
			throw exception();
		}
	}

	Tip gettip()
	{
		return this->tip;
	}
	void settip(Tip tipNou)
	{
		if (tipNou == 0 || tipNou == 1 || tipNou == 2)
			this->tip = tipNou;
		else
			throw exception();
	}

	float* getCantitati()
	{
		float* copieCantitati = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++)
			copieCantitati[i] = this->cantitati[i];
		return copieCantitati;
	}
	void setCantitati(float* cantitatiNoi, int nrIngredienteNou)
	{
		setnrIngrediente(nrIngredienteNou);
		if (this->cantitati != nullptr)
			delete[] this->cantitati;
		this->cantitati = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++)
			this->cantitati[i] = cantitatiNoi[i];


		delete[] cantitatiNoi;
	}

	~ProdusAlimentar()
	{
		if (this->cantitati != nullptr)
			delete[] this->cantitati;
	}

};

int ProdusAlimentar::nrProduseAlimentare = 0;


int main()
{
	ProdusAlimentar zero;
	zero.afisareProdusAlimentar();

	float* cantitati1 = new float [3] {100, 200, 300};
	ProdusAlimentar* sushi = new ProdusAlimentar("sushi", 40, 3, cantitati1, BIO);

	sushi->afisareProdusAlimentar();
	
	cout << endl<< "Schimba acest produs, te rog!";

	sushi->setdenumire("Paste");
	try {
		sushi->setpret(30);
	}
	catch (...)
	{
		cout << endl<< "ERORARE!! Nu putem avea pret negativ!!!";
	}

		sushi->settip(NORMAL);

	try {
		sushi->setnrIngrediente(4);
	}
	catch (...)
	{
		cout << endl<< "ERORARE! Nu putem avea sub 0 ingerdiente intr-un aliment!";
	}

	

	cout << endl << " Noul aliment este " << sushi->getdenumire() << " avand un pret de " << sushi->getpret() << " lei este de tipul ";
	if (sushi->gettip() == 0)
		cout << " BIO ";
	if (sushi->gettip() == 1)
		cout << "De baza ";
	if (sushi->gettip() == 2)
		cout << "Normal ";
	cout << ",are un numar de "<<sushi->getnrIngrediente()<<" ingrediente, cantitatile acestora fiind: ";

	sushi->setCantitati(new float [4] {250, 160, 330, 700}, 4);
	float* cantitatiNoi = sushi->getCantitati();
	for (int i = 0; i < sushi->getnrIngrediente(); i++)
		cout << cantitatiNoi[i] << " grame, ";

	delete[] cantitatiNoi;
	delete sushi;
}