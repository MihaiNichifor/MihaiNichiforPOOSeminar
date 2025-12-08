#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>
#include <cmath>
using namespace std;

enum Tip{Secund, Principal};
class Antrenor
{
	const int id;
	char* nume;
	int Experienta;
	int* nrTrofee; //trofee castigate anual ca antrenor
	string echipaActuala;
	Tip tip;
	static int nrAntrenori;


public:
	Antrenor() :id(++nrAntrenori)
	{
		this->nume = nullptr;
		this->Experienta = 0;
		this->nrTrofee = 0;
		this->echipaActuala = "X";
		this->tip = Principal;
	}

	Antrenor(const char* nume, int Experienta, int* nrTrofee, string echipaActuala, Tip tip) :id(++nrAntrenori)
	{
		this->nume = new char[strlen(nume) + 1];
		if (this->nume != nullptr)
		{
			strcpy(this->nume, nume);
		}
		else
			this->nume = nullptr;
		this->Experienta = Experienta;
		this->tip = tip;
		this->echipaActuala = echipaActuala;
		this->nrTrofee = new int[this->Experienta];
		if (this->nrTrofee != nullptr)
		{
			for (int i = 0; i < this->Experienta; i++)
				this->nrTrofee[i] = nrTrofee[i];
		}
		else
			this->nrTrofee = nullptr;
	}

	friend ostream& operator<<(ostream& out, Antrenor& a);
	friend istream& operator>>(istream& in, Antrenor& a);
	int getExperienta()
	{
		return this->Experienta;

	}
	void setExperienta(int ExperientaNoua)
	{
		if (ExperientaNoua > 0)
			this->Experienta = ExperientaNoua;
		else
			throw exception();
	}

	int* getnrTrofee()
	{
		int* copie;
		if (this->nrTrofee != nullptr)
		{
			copie = new int[this->Experienta];
			for (int i = 0; i < this->Experienta; i++)
				copie[i] = this->nrTrofee[i];

			return copie;
		}
		else
			return nullptr;
	}
	void setnrTrofee(int ExperientaNoua, int* nrNouTrofee)
	{
		setExperienta(ExperientaNoua);
		if (this->nrTrofee != nullptr)
		{
			delete[] this->nrTrofee;
			this->nrTrofee = nullptr;
		}
	
		if (nrNouTrofee != nullptr)
		{
			this->nrTrofee = new int[ExperientaNoua];
			for (int i = 0; i < this->Experienta; i++)
			{
				this->nrTrofee[i] = nrNouTrofee[i];
			}
		}
		else
			this->nrTrofee = nullptr;
	}

	Antrenor& operator++()
	{
		this->Experienta++;
		return *this;
	}

	float operator()(int nrSezoane)
	{
		if (this->Experienta == nrSezoane)
			this->Experienta = nrSezoane;
		else
			throw exception();
		float Medie, AbatereStandard;
		int dif;
		int s = 0;
		int sumadiferente = 0;
		if (this->nrTrofee != nullptr)
		{
			for (int i = 0; i < this->Experienta; i++)
			{
				s += this->nrTrofee[i];
			}
		}
		else
			Medie = 0;

		if (this->Experienta)
		{
			Medie = s / Experienta;
		}
		if (this->nrTrofee != nullptr)
		{
			for (int i = 0; i < this->Experienta; i++)
			{
				dif = (this->nrTrofee[i] - Medie) * (this->nrTrofee[i] - Medie);
				sumadiferente += dif;
			}
		}
		else
			AbatereStandard = 0;
		if (this->Experienta)
		{
			AbatereStandard = sqrt(sumadiferente / Experienta);
		}

		return AbatereStandard;
	}
	Antrenor(const Antrenor& copie) :id(++nrAntrenori)
	{
		if (copie.nume != nullptr)
		{
			this->nume = new char[strlen(copie.nume) + 1];
			strcpy(this->nume, copie.nume);
		}
		else
			this->nume = nullptr;
		this->echipaActuala = copie.echipaActuala;
		this->Experienta = copie.Experienta;
		this->tip = copie.tip;
		if (copie.nrTrofee != nullptr)
		{
			this->nrTrofee = new int[copie.Experienta];
			for (int i = 0; i < copie.Experienta; i++)
				this->nrTrofee[i] = copie.nrTrofee[i];
		}
		else this->nrTrofee = nullptr;
	}
	Antrenor operator++(int)
	{
		Antrenor copie = *this;
		this->Experienta++;

		return copie;
	}

	explicit operator int* ()
	{
		return this->nrTrofee;
	}

	Antrenor& operator=(Antrenor& a)
	{
		if (this->nume != nullptr)
		{
			delete[] this->nume;
			this->nume = nullptr;
		}
		if (this->nrTrofee != nullptr)
		{
			delete[] this->nrTrofee;
			this->nrTrofee = nullptr;
		}
		if (a.nume != nullptr)
		{
			this->nume = new char[strlen(a.nume) + 1];
			strcpy(this->nume, a.nume);
		}
		this->tip = a.tip;
		this->echipaActuala = a.echipaActuala;
		this->Experienta = a.Experienta;
		this->nrTrofee = new int[a.Experienta];
		if(a.nrTrofee!=nullptr)
			for (int i = 0; i < a.Experienta; i++)
				this->nrTrofee[i] = a.nrTrofee[i];
		
		return *this;
	}
	~Antrenor()
	{
		if (this->nume != nullptr)
		{
			delete[] this->nume;
			this->nume = nullptr;
		}

		if (this->nrTrofee != nullptr)
		{
			delete[] this->nrTrofee;
			this->nrTrofee = nullptr;
		}
	}
};

ostream& operator<<(ostream& out, Antrenor& a)
{
	out << endl << "Id: " << a.id;
	out << endl << "Nume: ";
	if (a.nume != nullptr)
		out << a.nume;
	else
		out << " ";
	out << endl << "Experienta: "<<a.Experienta<<" ani";
	out << endl << "Trofee Anuale: ";
	for (int i = 0; i < a.Experienta; i++)
		out << a.nrTrofee[i] << " ";
	out << endl << "Echipa Actuala: " << a.echipaActuala;
	out << endl << "Tip: ";
	if (a.tip == 0)
		out << "Secund";
	else
		out << "Principal ";

	return out;

}

istream& operator>>(istream& in, Antrenor& a)
{
	cout << endl << "Introduceti urmatoarele: ";
	cout << endl << "Nume: ";
	char buffer[100];
	in.getline(buffer, 100);
	if (a.nume != nullptr)
	{
		delete[] a.nume;
		a.nume = nullptr;
	}
	a.nume = new char[strlen(buffer) + 1];
	strcpy(a.nume, buffer);
	int nr;
	cout << endl << "Tip:(0-Secund, 1-Principal) ";
	cin >> nr;
	if (nr == 0)
		a.tip = Secund;
	else
		a.tip = Principal;
	cout << endl << "Echipa Actuala: ";
	cin >> a.echipaActuala;
	cout << endl << "Ani Experienta: ";
	cin >> a.Experienta;
	cout << endl << "Nr Trofee Anuale: ";
	if (a.nrTrofee != nullptr)
	{
		delete[] a.nrTrofee;
		a.nrTrofee = nullptr;
	}
	a.nrTrofee = new int[a.Experienta];
	if(a.nrTrofee!=nullptr)
		for (int i = 0; i < a.Experienta; i++)
		{
			cin >> a.nrTrofee[i];
		}

	return in;
}
int Antrenor::nrAntrenori = 0;

int main()
{
	int* TrofeeA1 = new int[4] {3, 2, 0, 4};
	Antrenor A1("Gigi Becali", 4, TrofeeA1, "FCSB", Principal);

	cout << A1;

	cout << endl << endl;
	int* TrofeeA11 = new int[6] {3, 2, 0, 4, 7, 8};
	try
	{
		cout << "Experienta Noua: ";
		A1.setExperienta(6);
		cout << A1.getExperienta();
		A1.setnrTrofee(6, TrofeeA11);
		cout << endl;
		for (int i = 0; i < A1.getExperienta(); i++)
			cout << A1.getnrTrofee()[i] << " ";
	}
	catch (...)
	{
		cout << "Numar invalid!!";
	}

	/*cin >> A1;
	cout << A1;*/

	try {
		cout << endl << "Abatere Standard Trofee: " << A1(6);
	}
	catch (...)
	{
		cout << "Introdu numarul corect pt Experienta Antrenorului!!";
	}
	Antrenor A5;
	A5 = A1;
	cout << endl << A5;

	cout << endl << endl;
	int* A4 = (int*)A1;
	for (int i = 0; i < 6; i++)
		cout << (int)A4[i]<<" ";

	Antrenor A2 = ++A1;
	cout << endl << "Experienta PreIncrementata: ";
	cout <<"A2: "<< A2.getExperienta() << "  A1: "<<A1.getExperienta();

	Antrenor A3 = A1++;
	cout << endl << "Experienta PostIncrementata: ";
	cout << "A3: " << A3.getExperienta() << "  A1: " << A1.getExperienta();

	
}