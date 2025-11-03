#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

using namespace std;

enum Continent{Europa, Asia, America, AltContinent};

class Tara {
	const int id;
	char* denumire;
	Continent continent;
	float suprafata;
	int nrOrase;
	string* numeOras;

public:
	Tara() :id(0)
	{
		this->denumire = nullptr;
		this->continent = AltContinent;
		this->suprafata = 0;
		this->nrOrase = 0;
		this->numeOras = nullptr;
	}

	Tara(int idT, const char* denumire, Continent continent) :id(++idT)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->continent = continent;

		this->suprafata = 0;
		this->nrOrase = 0;
		this->numeOras = nullptr;
	}

	Tara(int idT, const char* denumire, Continent continent, float suprafata, int nrOrase, string* numeOras) :id(++idT)
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->continent = continent;
		this->suprafata = suprafata;
		this->nrOrase = nrOrase;
		this->numeOras = new string[this->nrOrase];
		for (int i = 0; i < nrOrase; i++)
			this->numeOras[i] = numeOras[i];
	}
	void afisare()
	{
		cout << endl << endl;
		cout << this->id << " . Statul ";
		if (this->denumire != nullptr)
			cout << this->denumire;
		else
			cout << "X ";
		cout << " se afla pe continentul ";
		if (this->continent == 0)
			cout << "Europa ";
		if (this->continent == 1)
			cout << "Asia ";
		if (this->continent == 2)
			cout << "America ";
		if (this->continent == 3)
			cout << "altul decat cele mentionate ";
		cout << " are o suprafata de " << this->suprafata << " mii kmp, are un numar de " << this->nrOrase << " orase mari, acestea fiind: ";
		for (int i = 0; i < this->nrOrase; i++)
			cout << numeOras[i] << " ";


	}
	Tara(const Tara& copie) :id(1000)
	{
		if (copie.denumire != nullptr)
		{
			this->denumire = new char[strlen(copie.denumire) + 1];
			strcpy(this->denumire, copie.denumire);
		}
		else
			this->denumire = nullptr;
		this->continent = copie.continent;
		this->suprafata = copie.suprafata;
		this->nrOrase = copie.nrOrase;
		if (copie.numeOras != nullptr)
		{
			this->numeOras = new string[copie.nrOrase];
			for (int i = 0; i < copie.nrOrase; i++)
				this->numeOras[i] = copie.numeOras[i];
		}
		else
			this->numeOras = nullptr;
	}
	void operator=(const Tara& copie)
	{
		if (this->denumire != nullptr)
		{
			delete[] this->denumire;
			this->denumire = nullptr;
		}
		if (copie.denumire != nullptr)
		{
			this->denumire = new char[strlen(copie.denumire) + 1];
			strcpy(this->denumire, copie.denumire);
		}
		this->continent = copie.continent;
		this->suprafata = copie.suprafata;
		this->nrOrase = copie.nrOrase;
		if (this->numeOras != nullptr)
		{
			delete[] this->numeOras;
			this->numeOras = nullptr;
		}
		if (copie.numeOras != nullptr)
		{
			this->numeOras = new string[copie.nrOrase];
			for (int i = 0; i < copie.nrOrase; i++)
				this->numeOras[i] = copie.numeOras[i];
		}
	}
	int getnrOrase()
	{
		return this->nrOrase;
	}
	void setnrOrase(int nrNouOrase)
	{
		if (nrNouOrase > 0)
			this->nrOrase = nrNouOrase;
		else
			throw exception();
	}
	
	string* getnumeOrase()
	{
		string* copie;
		if (this->numeOras != nullptr)
		{
			copie = new string[this->nrOrase];
			for (int i = 0; i < this->nrOrase; i++)
				copie[i] = numeOras[i];
			return copie;
		}
		else return nullptr;
	}
	void setnumeOrase(int nrNouOrase, string* numeNouOras)
	{
		setnrOrase(nrNouOrase);
		if (this->numeOras != nullptr)
		{
			delete[] numeOras;
			this->numeOras = nullptr;
		}
		if (numeNouOras != nullptr)
		{
			this->numeOras = new string[nrNouOrase];
			for (int i = 0; i < getnrOrase(); i++)
				this->numeOras[i] = numeNouOras[i];
		}
		else
			this->numeOras = nullptr;
	}
	~Tara()
	{
		if (this->denumire != nullptr)
		{
			delete[] this->denumire;
			this->denumire = nullptr;
		}
		if (this->numeOras != nullptr)
		{
			delete[] this->numeOras;
			this->numeOras = nullptr;
		}
	}
};

int main()
{
	Tara t1;
	t1.afisare();

	Tara t2(1, "Romania", Europa);
	t2.afisare();

	string* orase3 = new string[5]{ "Bucuresti", "Cluj-Napoca", "Timisoara", "Brasov", "Iasi" };
	Tara t3(2, "Romania", Europa, 239, 5, orase3);
	t3.afisare();

	cout << endl << endl;
	t3.setnrOrase(8);
	string* oraseNoi3 = new string[8]{ "Craiova", "Ploiesti", "Constanta", "Alba-Iulia", "Hunedoara", "Arad", "Vaslui", "Galati" };
	cout << " Vom afisa alte " << t3.getnrOrase() << " orase: ";
	t3.setnumeOrase(8, oraseNoi3);
	for (int i = 0; i < t3.getnrOrase(); i++)
		cout << t3.getnumeOrase()[i] << " ";

	Tara t4(t3);
	t4.afisare();
	cout << "Se schimba id-ul, la 1000 de exemplu cum am pus eu la constructor.";

	t1 = t3;
	t1.afisare();
	cout << "Se pastreaza id-ul de la t1, adica 0!!";
}