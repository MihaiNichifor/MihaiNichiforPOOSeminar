#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class Card
{
private:
	float suma;
	string IBAN;

public:
	Card() 
	{
		this->suma = 0;
		this->IBAN ="RO00000000000000";
	}

	Card(float suma, string IBAN)
	{
		this->suma = suma;
		this->IBAN = IBAN;
	}

	float getsuma()
	{
		return this->suma;
	}
	string getIBAN()
	{
		return this->IBAN;
	}

	~Card()
	{
	}
};

//Persoana has a Card
class Persoana
{
private:
	//1:m->o persoana poate avea unu sau mai multe carduri
	Card* carduri;
	string Nume;
	int varsta;
	int nrCarduri;

public:
	Persoana()
	{
		this->Nume = "X";
		this->varsta = 0;
		this->nrCarduri = 0;
		this->carduri = nullptr;
	}
	Persoana(string nume, int varsta, int nrCarduri, float* sume, string* IBANURI)
	{
		this->Nume = nume;
		this->varsta = varsta;
		this->nrCarduri = nrCarduri;
		this->carduri = new Card[nrCarduri];
		{
			for (int i = 0; i < nrCarduri; i++)
			{
				this->carduri[i] = Card(sume[i], IBANURI[i]);
			}
		}
	}

	Persoana(const Persoana& p)
	{
		this->Nume = p.Nume;
		this->varsta = p.varsta;
		this->nrCarduri = p.nrCarduri;
		if (p.carduri != nullptr)
		{
			this->carduri = new Card[p.nrCarduri];
			for (int i = 0; i < p.nrCarduri; i++)
				this->carduri[i] = p.carduri[i];
		}
	}

	~Persoana()
	{
		if (carduri != nullptr)
		{
			delete[] carduri;
			carduri = nullptr;
		}
	}

	bool operator>=(int v)
	{
		if (this->varsta > v)
			return true;
		return false;
	}

	bool operator!()
	{
		if (!this->nrCarduri)
			return false;
		return true;
	}

	//Adaugare varsta
	Persoana& operator+=(int an)
	{
		this->varsta += an; 

			return *this;
	}

	//Calculare total detinut in conturi-cu operator functie
	float operator()(int nrCarduri)
	{
		float s = 0;
		if (this->carduri != nullptr)
		{
			for (int i = 0; i < this->nrCarduri; i++)
			{
				s += this->carduri[i].getsuma();
			}
		}
		return s;
	}

	//pre-decrementare nrCarduri
	Persoana operator--()
	{
		this->nrCarduri--;
		return *this;
	}

	Persoana operator--(int)
	{
		Persoana copie = *this;
		this->nrCarduri--;

		return copie;
	}
	friend ostream& operator<<(ostream& out, const Persoana& p);
	

	
};

ostream& operator<<(ostream& out, const Persoana& p)
{
	out << p.Nume << " are varsta de " << p.varsta << " ani, detine " << p.nrCarduri << " carduri la banca, avand caracteristicile: ";
	if (p.carduri != nullptr)
	{
		for (int i = 0; i < p.nrCarduri; i++)
		{
			out << endl << "Card " << i + 1 << ":";
			out << endl << "    ->IBAN: " << p.carduri[i].getIBAN();
			out << endl << "    ->Suma: " << p.carduri[i].getsuma()<<" lei.";
		}
	}

	return out;
}

void main()
{
	float* sume1;
	sume1 = new float[3] {3129.11, 4500.73, 7.53};
	string* IBANuri1;
	IBANuri1 = new string[3]{ "RO22 RZBR 4050 3332 7711", "RO23 RZBR 8887 4332 4114" , "RO24 RZBR 5552 0012 6767" };

	Persoana p1("Ionescu Andrei", 38, 3, sume1, IBANuri1);
	cout << p1;

	cout << endl << endl;
	float* sume2;
	sume2 = new float[2] {12551.70, 8800.13};
	string* IBANuri2;
	IBANuri2 = new string[2]{ "RO88 RZBR 4676 1112 6767", "RO31 RZBR 4705 0525 2218" };

	Persoana p2("Popescu Maria", 27, 2, sume2, IBANuri2);
	cout << p2;

	cout << endl << endl;
	if (p2 >= 65)
	{
		cout << "Clientul/a este la pensie.";
	}
	else
		cout << "Clientul/a nu este la pensie.";

	cout << endl << endl;
	if (!p1)
	{
		cout << "Aceasta persoana este client la banca.";
	}
	else
		cout << "Aceasta persoana nu este client la banca.";

	cout << endl << endl;
	p1 += 15;
	cout << "Peste 15 ani clientul va avea" << p1;

	cout << endl << endl;
	cout << "Suma totala detinuta de persoana p1 este "<<p1(3)<<" lei.";
}