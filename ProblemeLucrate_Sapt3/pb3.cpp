#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class Masina
{
	string marca;
	string culoare;
	int anFabricatie;
	double pret;
	int* varsteproprietari;
	int nrproprietari;
public:
	Masina()
	{
		this->marca = "fara marca";
		this->culoare = "fara culoare";
		this->anFabricatie = 0;
		this->pret = 0;
		this->nrproprietari = 0;
		this->varsteproprietari = nullptr;
	}
	Masina(string marca, string culoare, int anFabricatie, double pret, int nrproprietari, int* varsteproprietari)
	{
		this->marca = marca;
		this->culoare = culoare;
		this->anFabricatie = anFabricatie;
		this->pret = pret;
		this->nrproprietari = nrproprietari;
		this->varsteproprietari = new int[this->nrproprietari];
		for (int i = 0; i < this->nrproprietari; i++)
			this->varsteproprietari[i] = varsteproprietari[i];
	}
	void afisareToateCaracteristicile()
	{
		cout << endl << "Masina din brand-ul " << this->marca << " are culoarea " << this->culoare << " ,a fost fabricata in anul "
			<< this->anFabricatie << ", costa " << this->pret << " euro si a avut " << this->nrproprietari
			<< " proprietari, acestia avand varstele de : ";
		for (int i = 0; i < this->nrproprietari; i++)
		{
			if (i != this->nrproprietari - 1)
				cout << this->varsteproprietari[i] << " ani, ";
			else
				cout << this->varsteproprietari[i] << " ani.";
		}
	}
	Masina(string marca, int anFabricatie)
	{
		this->marca = marca;
		this->anFabricatie = anFabricatie;
	}
	void vechime()
	{
		if (this->anFabricatie < 2018)
			cout << endl << "Aceasta masina " << this->marca << " este veche.";
		else
			cout << endl << "Aceasta masina " << this->marca << " este noua.";

	}
	Masina(string marca, int nrproprietari, int* varsteproprietari)
	{
		this->marca = marca;
		this->nrproprietari = nrproprietari;
		this->varsteproprietari = new int[this->nrproprietari];
		for (int i = 0; i < this->nrproprietari; i++)
			this->varsteproprietari[i] = varsteproprietari[i];
	}
	void nouProprietar()
	{
		cout << "Masina din marca " << this->marca << " a fost vanduta si are un nou proprietar acesta fiind cel de-al "
		<< this->nrproprietari <<"-lea avand varsta de " << this->varsteproprietari[nrproprietari-1] << " ani. ";
	}
	
	~Masina()
	{
		if (this->varsteproprietari != nullptr)
			delete[] this->varsteproprietari;
	}
};


int main()
{
	//apelare metoda afisarii tuturor caracteristicilor
	int* VarsteProprietari1 = new int[4] {44, 50, 23, 60};
	Masina* Skoda = new Masina("Skoda", "Negru", 2015, 10000, 4, VarsteProprietari1);
	Skoda->afisareToateCaracteristicile();
	delete Skoda;
	cout << endl << endl << endl;


	//2 apeluri pt metoda vechime
	cout << endl;
	cout << "----------------------VECHIME---------------------" << endl;
	Masina* m1 = new Masina("Peugeot", 2016);
	m1->vechime();
	delete m1;

	Masina* m2 = new Masina("Audi", 2023);
	m2->vechime();
	delete m2;

	cout << endl << endl << endl;

	//
	cout << endl;
	cout << "----------------------PROPRIETARI---------------------" << endl;
	int* VarsteProprietari3 = new int[4] {32, 40, 25, 38};
	Masina* m3 = new Masina("BMW", 4, VarsteProprietari3);
	m3->nouProprietar();
	delete m3;
}