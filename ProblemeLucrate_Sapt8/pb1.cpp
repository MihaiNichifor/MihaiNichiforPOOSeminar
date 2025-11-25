#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class ExceptieCustom :public exception 
{
public:
	ExceptieCustom(const char* mesaj) :exception(mesaj) {}
};

class Produs
{
private:
	const int id;
	string denumire;
	float pret;
public:
	static const float PRET_MINIM;
	Produs() :id(0), denumire("Laptop"), pret(5000)
	{

	}

	Produs(int idP, string denumireP, float pretP) : id(idP), denumire(denumireP), pret(pretP)
	{
		if (pret < PRET_MINIM)
		{
			throw ExceptieCustom("Pretul este prea mic!");
		}
	}

	~Produs()
	{

	}

	virtual void afisare()
	{
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret: " << this->pret;

	}

	//virtual float getProcentReducere() = 0; 

	virtual float getProcentScumpire() = 0;

};

const float Produs::PRET_MINIM = 1;

class ProdusRedus :public Produs
{
private:
	float procentReducere;

public:
	//are 4 atribute aceasta clasa->mosteneste atributele clasei Produs+atributele noi (ex: intrebare grila)
	ProdusRedus() :Produs(), procentReducere(10) //->initializarea celor 3 atribute din din clasa Produs
	{
	}

	ProdusRedus(int id, string denumire, float pret, float procentReducere) :Produs(id, denumire, pret), procentReducere(procentReducere)
	{
	}

	void afisare()
	{
		cout << endl;
		this->Produs::afisare(); 
		cout << endl << "Procent reducere: " << this->procentReducere;
	}

	float getProcentReducere()
	{
		return this->procentReducere; 
	}
};

class ProdusScumpit: public Produs
{
private:
	float procentScumpire;
public:

	ProdusScumpit() : Produs()
	{
		this->procentScumpire = 0;
	}
	ProdusScumpit(int id, string denumire, float pret, float procentScumpire) :Produs(id, denumire, pret)
	{
		this->procentScumpire = procentScumpire;
	}

	void afisare()
	{
		cout << endl;
		this->Produs::afisare();
		cout <<endl<< "Procent Scumpire: " << this->procentScumpire;
	}

	float getProcentScumpire() 
	{
		return this->procentScumpire;
	}
};


class PlataProdusInterface
{
public:
	virtual string Platit(float sumaCheltuita) = 0;
};

class PlataProdus : public PlataProdusInterface
{
public:
	string Platit(float sumaCheltuita)
	{
		if (sumaCheltuita == 0)
			return "Din pacate nu s-a efectuat plata";

		if(sumaCheltuita>0)
			return "Plata a fost efectuata cu succes";

		if (sumaCheltuita < 0)
			throw ExceptieCustom("Eroare! Introdu te rog un numar pozitiv");
	}
};



void main()
{
	ProdusScumpit iPhone(4, "Iphone 17", 5700, 15);
	iPhone.afisare();
	Produs* vectorProduse[2];
	vectorProduse[0] = new ProdusScumpit(1, "Motorina", 9, 5);
	vectorProduse[1] = new ProdusScumpit(2, "Benzina", 8.5, 4);
	
	for (int i = 0; i < 2; i++)
	{
		vectorProduse[i]->afisare();
		delete vectorProduse[i];
	}


	PlataProdusInterface* operation2 = new PlataProdus();
	try
	{
		cout << endl << operation2->Platit(0);
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}
}

