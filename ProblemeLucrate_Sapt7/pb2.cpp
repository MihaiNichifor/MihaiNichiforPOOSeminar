#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

enum Post{Portar, Fundas, Mijlocas, Atacant};
class Fotbalist
{
private:
	const int id;
	char* nume;
	int nrGoluri;
	int nrSezoane;
	int* nrMeciuri;
	Post post;

public:
	Fotbalist() :id(0)
	{
		this->nume = nullptr;
		this->nrGoluri = 0;
		this->nrSezoane = 0;
		this->nrMeciuri = 0;
		this->post = Atacant;
	}
	Fotbalist(int idF, const char* nume, Post post, int nrGoluri, int nrSezoane, int* nrMeciuri) :id(idF)
	{
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->nrGoluri = nrGoluri;
		this->post = post;
		this->nrSezoane = nrSezoane;
		this->nrMeciuri = new int[this->nrSezoane];
		for (int i = 0; i < this->nrSezoane; i++)
			this->nrMeciuri[i] = nrMeciuri[i];
	}
	friend void operator<<(ostream& afisare, const Fotbalist& f)
	{
		cout << endl << endl;
		afisare << f.id << ". Fotbliastul ";
		if (f.nume != nullptr)
			afisare << f.nume;
		else
			afisare << "X";
		afisare << " joaca pe pozitia de ";
		if (f.post == 0) afisare << "Portar";
		if (f.post == 1) afisare << "Fundas";
		if (f.post == 2) afisare << "Mijlocas";
		if (f.post == 3) afisare << "Atacant";
		afisare << " ,a marcat in cariera sa " << f.nrGoluri << " goluri, jucand timp de " << f.nrSezoane << " sezoane, avand un numar de meciuri in fiecare sezon de: ";
		for (int i = 0; i < f.nrSezoane; i++)
			afisare << endl<< "Sezon " << i+1 << ": " << f.nrMeciuri[i];
	}
	friend void operator>>(istream& citire, Fotbalist& f)
	{
		cout <<endl<< "Nume fotbalist: ";
		if (f.nume != nullptr)
		{
			delete[] f.nume;
			f.nume = nullptr;
		}
		char copie[1000];
		cin.getline(copie, 1000);
		f.nume = new char[strlen(copie) + 1];
		strcpy(f.nume, copie);

		int post;
		cout <<endl<< "Post: ";
		citire >> post;
		if (f.post == 0) f.post = Portar;
		if (f.post == 1) f.post = Fundas;
		if (f.post == 2) f.post = Mijlocas;
		if (f.post == 3) f.post = Atacant;
		cout <<endl<< "Goluri: ";
		citire >> f.nrGoluri;
		cout << endl << "Sezoane Jucate: ";
		citire >> f.nrSezoane;
		cout << endl << "Nr meciuri in fiecare sezon: ";
		if (f.nrMeciuri != nullptr)
		{
			delete[] f.nrMeciuri;
			f.nrMeciuri = nullptr;
		}

		f.nrMeciuri = new int[f.nrSezoane];
		for (int i = 0; i < f.nrSezoane; i++)
		{
			cout << "Sezon " << i + 1 << ": ";
				citire >> f.nrMeciuri[i];
		}


	}

	bool operator<=(Fotbalist &f)const 
	{
		if (this->nrGoluri <= f.nrGoluri)
			return true;
		return false;
	}

	void operator*=(int valoareDeMultiplicat)
	{
		this->nrGoluri = valoareDeMultiplicat * this->nrGoluri;
	}

	bool operator!()
	{
		if (!nrSezoane)
			return true;
		return false;
	}

	float operator()(int nrSezoane)
	{
		float s = 0, ma = 0, AbatereStandard=0, dif;
		for (int i = 0; i < this->nrSezoane; i++)
			s += this->nrMeciuri[i];
		if (this->nrSezoane != 0)
			ma = s / this->nrSezoane;
		
		s = 0;
		for (int i = 0; i < this->nrSezoane; i++)
		{
			dif = this->nrMeciuri[i] - ma;
			s += dif*dif;
		}
		AbatereStandard = sqrt(s / this->nrSezoane);

		return AbatereStandard;
	}

	Fotbalist(const Fotbalist& copie) :id(copie.id)
	{
		if (copie.nume != nullptr)
		{
			this->nume = new char[strlen(copie.nume) + 1];
			strcpy(this->nume, copie.nume);
		}
		else
			this->nume = nullptr;
		
		this->nrGoluri = copie.nrGoluri;
		this->nrSezoane = copie.nrSezoane;
		this->post = copie.post;
		if (copie.nrMeciuri != nullptr)
		{
			this->nrMeciuri = new int[copie.nrSezoane];
			for (int i = 0; i < copie.nrSezoane; i++)
			{
				this->nrMeciuri[i] = copie.nrMeciuri[i];
			}
		}
		else
			this->nrMeciuri = nullptr;

	}
	Fotbalist operator++(int)
	{
		Fotbalist copie = *this;
		this->nrGoluri++;

		return copie;
	}

	Fotbalist operator++()
	{
		this->nrGoluri++;
		return *this;
	}

	explicit operator char*()
	{
		return this->nume;
	}
	~Fotbalist()
	{
		if (this->nume != nullptr)
		{
			delete[] nume;
			this->nume = nullptr;
		}
		if (this->nrMeciuri != nullptr)
		{
			delete[] nrMeciuri;
			this->nrMeciuri = nullptr;
		}
	}
};

int main()
{
	Fotbalist f1;
	cout << f1;

	int* nrMeciuri2 = new int[4]{60, 71, 58, 65};
	Fotbalist f2(7, "Cristiano Ronaldo", Atacant, 950, 4, nrMeciuri2);
	cout << f2;

	//cin >> f1;
	//cout << f1;

	/*if (f1 <= f2)
	{
		cout <<endl<< "Darius Olaru are mai putine goluri decat Cristiano Ronaldo";
	}
	else
		cout <<endl<< "Darius Olaru are mai multe goluri decat Cristiano Ronaldo";*/

	f2 *= 3;
	cout <<endl<<endl<< "S-a multiplicat cu 3 numarul de goluri pt Ronaldo. ";
	cout << f2;

	if (!f1)
	{
		cout <<endl<< "Acest fotbalist nu are meciuri la nivel profesionist";
	}
	else
		cout <<endl<< "Acest fotbalist are meciuri inca la nivel profesionist.";

	cout << endl << " Numarul de meciuri jucate in fiecare sezon de Cristiano Ronaldo are o abatere standard de ";
	cout << f2(4)<<" meciuri!";

	Fotbalist f3 = f2++;
	cout <<endl<< "Post-incrementare: " << f3;
	Fotbalist f4 = ++f2;
	cout <<endl<< "Pre-incrementare: " << f4;

	cout << endl << " Operator explicit->conversie in char*: ";
	cout << (char*)(f2);
	delete[] nrMeciuri2;
}