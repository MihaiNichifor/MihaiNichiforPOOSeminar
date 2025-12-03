#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class ExceptieCustom : public exception
{
public:
	ExceptieCustom(const char* mesaj) :exception(mesaj){}
};

enum Pozitie{Portar=1, Fundas=4, Mijlocas=10, Atacant=9, Patron=100};
class Fotbalist
{
private:
	string nume;
	int nrTricou;
	Pozitie pozitie;
	float salariu;

public:
	Fotbalist()
	{
		this->nume = "X";
		this->nrTricou = 0;
		this->pozitie = Portar;
		this->salariu = 0;

	}

	Fotbalist(string nume, int nrTricou, Pozitie pozitie, float salariu)
	{
		this->nume = nume;
		this->nrTricou = nrTricou;
		this->pozitie = pozitie;
		this-> salariu = salariu;
	}

	string getnume()
	{
		return this->nume;
	}
	int getnrTricou()
	{
		return this->nrTricou;
	}
	Pozitie getpozitie()
	{
		return this->pozitie;
	}
	float getsalariu()
	{
		return this->salariu;
	}
};

class Echipa
{
	Fotbalist* fotbalisti;
	int nrFotbalisti;
	string denumire;
public:
	Echipa()
	{
		this->nrFotbalisti = 0;
		this->fotbalisti = nullptr;
		this->denumire = "???";
	}

	Echipa(string denumire, int nrFotbalisti, string* nume, int* nrTricou, Pozitie* pozitie, float* salariu)
	{
		this->denumire = denumire;
		this->nrFotbalisti = nrFotbalisti;
		this->fotbalisti = new Fotbalist[nrFotbalisti];
		if (this->fotbalisti != nullptr)
		{
			for (int i = 0; i < this->nrFotbalisti; i++)
			{
				this->fotbalisti[i] = Fotbalist(nume[i], nrTricou[i], pozitie[i], salariu[i]);
			}
		}
	}

	Echipa(const Echipa& e)
	{
		this->denumire = e.denumire;
		this->nrFotbalisti = e.nrFotbalisti;
		if (e.fotbalisti != nullptr)
		{
			this->fotbalisti = new Fotbalist[e.nrFotbalisti];
			for (int i = 0; i < e.nrFotbalisti; i++)
				this->fotbalisti[i] = e.fotbalisti[i];

		}
	}
	friend ostream& operator<<(ostream &out, const Echipa& e);

	~Echipa()
	{
		if (this->fotbalisti != nullptr)
		{
			delete[] this->fotbalisti;
			this->fotbalisti = nullptr;
		}
	}
};

ostream& operator<<(ostream& out, const Echipa& e)
{
	out <<endl<< "Echipa: "<<e.denumire<<"--->"<<e.nrFotbalisti<<" fotbalisti: ";
	if (e.fotbalisti != nullptr)
	{
		for (int i = 0; i < e.nrFotbalisti; i++)
		{
			out << endl << "  ->";
			out << "Nume: "<<e.fotbalisti[i].getnume();
			out << endl<<"    NrTricou: " << e.fotbalisti[i].getnrTricou();
			out << endl<<"    Salariu: " << e.fotbalisti[i].getsalariu()<<" mii euro;";
			out << endl<<"    ";
			if(e.fotbalisti[i].getpozitie() == 1)
				out << "Post: Portar";
			if (e.fotbalisti[i].getpozitie() == 4)
				out << "Post: Fundas";
			if (e.fotbalisti[i].getpozitie() == 10)
				out << "Post: Mijlocas";
			if (e.fotbalisti[i].getpozitie() == 9)
				out << "Post: Atacant";
			if (e.fotbalisti[i].getpozitie() == 100)
				out << "Post: Patron";
			out << endl;
		}

		return out;
	}
}

int main()
{
	string* numeE1 = new string[6]{ "Stefan Tarnovanu", "Florinel Coman", "Darius Olaru", "Daniel Birligea", "Siyabonga Ngezana", "Gigi Becali" };
	int* nrTricouE1 = new int[6] {12, 7, 27, 9, 30, 0};
	Pozitie* pozitiiE1 = new Pozitie[6]{ Portar, Atacant, Mijlocas, Atacant, Fundas, Patron };
	float* salariiE1 = new float[6] {15.000, 30.000, 35.000, 40.0000, 17.000, 10};
	Echipa E1("FCSB", 6, numeE1, nrTricouE1, pozitiiE1, salariiE1);;
	cout << E1;

	delete[] numeE1;
	delete[] nrTricouE1;
	delete[] pozitiiE1;
	delete[] salariiE1;

}