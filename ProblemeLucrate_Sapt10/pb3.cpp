#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

using namespace std;

class ExceptieCustom :public exception
{
public:
	ExceptieCustom (const char* mesaj) :exception(mesaj)
	{ }
};

enum Tip{Apartament=5, Garsoniera=15, Casa=25};
class Locuinta
{
	const int id;
	float suprafata;
	int nrProprietari;
	bool areBalcon;
	string* numeProprietari;
	string oras;
	Tip tip;
	static int nrLocuinte;

public:
	Locuinta() :id(nrLocuinte++)
	{
		this->suprafata = 0;
		this->nrProprietari = 0;
		this->oras = "X";
		this->tip = Casa;
		this->areBalcon = false;
		this->numeProprietari = nullptr;
	}
	Locuinta(float suprafata, string oras, bool areBalcon, Tip tip, int nrProprietari, string* numeProprietari) :id(nrLocuinte++)
	{
		this->suprafata = suprafata;
		this->oras = oras;
		this->areBalcon = areBalcon;
		this->tip = tip;
		this->nrProprietari = nrProprietari;
		this->numeProprietari = new string[this->nrProprietari];
		if (this->numeProprietari != nullptr)
		{
			for (int i = 0; i < this->nrProprietari; i++)
			{
				this->numeProprietari[i] = numeProprietari[i];
			}
		}
		else this->numeProprietari = nullptr;

	}

	friend ostream& operator<<(ostream& out, const Locuinta& l);

	friend istream& operator>>(istream& in, Locuinta& l);

	Locuinta(const Locuinta& copie) :id(++nrLocuinte)
	{
		this->suprafata = copie.suprafata;
		this->oras = copie.oras;
		this->areBalcon = copie.areBalcon;
		this->tip = copie.tip;
		this->nrProprietari = copie.nrProprietari;

		if (copie.numeProprietari != nullptr)
		{
			this->numeProprietari = new string[copie.nrProprietari];
			for (int i = 0; i < copie.nrProprietari; i++)
				this->numeProprietari[i] = copie.numeProprietari[i];
		}
		else
			this->numeProprietari = nullptr;
	}

	//preincrementare
	Locuinta& operator++()
	{
		this->suprafata++;
		return *this;
	}

	//postincrementare
	Locuinta operator++(int)
	{
		Locuinta copie=*this;
		this->suprafata++;

		return copie;
	}

	//index
	string operator[](int index)
	{
		if (index >= 0 && index < this->nrProprietari)
			 return this->numeProprietari[index];
		else
			throw ExceptieCustom("Introdu un index valid!!");


	}

	//<=
	bool operator<=(const Locuinta& l)
	{
		if (this->suprafata <= l.suprafata)
			return true;
		return false;
	}

	//!=
	bool operator!=(int nr)
	{
		if (nr <= 0)
			throw ExceptieCustom("Introdu o suprafata valida!!");
		if (this->suprafata != nr)
			return true;
		return false;
	}
	// *=
	Locuinta& operator*=(const Locuinta& l)
	{
		this->suprafata *= l.suprafata;
		return *this;
	}

	// +
	Locuinta operator+(int nr)
	{
		Locuinta copie = *this;
		if (nr > 0)
		{
			copie.suprafata = copie.suprafata + nr;
			return copie;
		}
		else
			throw ExceptieCustom("Numar introdus gresit!");
	}

	//cast explicit
	explicit operator Tip ()
	{
		return this->tip;
	}

	//functie
	Locuinta& operator()(int pozitie)
	{
		string* copie;
		copie = new string[this->nrProprietari];
		for (int i = 0; i < this->nrProprietari; i++)
		{
			copie[i] = this->numeProprietari[i];
		}
		if (this->numeProprietari != nullptr)
		{
			delete[] this->numeProprietari;
			this->numeProprietari = nullptr;

		}

		int copienrProprietari = this->nrProprietari;
		this->nrProprietari--;
		this->numeProprietari = new string[this->nrProprietari];
		int j = 0;
		
		if (pozitie >= 0 && pozitie < copienrProprietari)
		{
			for (int i = 0; i < copienrProprietari; i++)
			{
				if (i == pozitie && pozitie!=0)
				{
					this->numeProprietari[j] = copie[i + 1];
					j++;
					i++;
				}
				else
					if (i == pozitie && pozitie == 0)
					{
						{
							this->numeProprietari[j] = copie[i + 1];
							j++;
							i++;
						}
					}
					else
					{
						this->numeProprietari[j] = copie[i];
						j++;
					}
			}
		}
		else throw ExceptieCustom("Introdu o pozitie valida!!!");

		return *this;
	}
};

ostream& operator<<(ostream& out, const Locuinta& l)
{
	out << endl;
	out << "Id: " << l.id;
	out << endl << "Oras: " << l.oras;
	out << endl << "Suprafata: " << l.suprafata<<" mp";
	out << endl << "Tip Locuinta: ";
	if (l.tip == 5)
		out << "Aparatament ";
	if (l.tip == 15)
		out << "Garsoniera ";
	if (l.tip == 25)
		out << "Casa ";
	out << endl << "Are Balcon? ";
	if (l.areBalcon == true)
		out << "DA";
	else
		out << "NU";
	out << endl << "Nr Proprietari: " << l.nrProprietari;
	out << endl << "Nume Proprietari: ";

	if (l.numeProprietari != nullptr)
	{
		for (int i = 0; i < l.nrProprietari; i++)
			out << l.numeProprietari[i] << " ";
	}
	else
		out << " ";

	return out;
}

istream& operator>>(istream& in, Locuinta& l)
{
	cout << endl << endl;
	cout << "Introduceti: ";
	cout << endl << "Suprafata: ";
	in >> l.suprafata;
	cout << endl << "Oras: ";
	in >> l.oras;
	cout << endl << "Are Balcon?(0-nu, 1-da) ";
	in >> l.areBalcon;
	int nr;
	cout << endl << "Tip Locuinta: (5-apartament, 15-garsoniera, 25-casa)";
	in >> nr;
	if (nr == 5)
		l.tip = Apartament;
	if (nr == 15)
		l.tip = Garsoniera;
	if (nr == 25)
		l.tip = Casa;
	cout << endl << "Nr proprietari: ";
	in >> l.nrProprietari;
	cout << endl << "Nume Proprietari: ";
	if (l.numeProprietari != nullptr)
	{
		delete[] l.numeProprietari;
		l.numeProprietari = nullptr;
	}
	l.numeProprietari = new string[l.nrProprietari];
	for (int i = 0; i < l.nrProprietari; i++)
		in >> l.numeProprietari[i];

	return in;
}

int Locuinta::nrLocuinte = 0;

int main()
{
	string* proprietariL1 = new string[2]{"Coman", "Birligea"};
	Locuinta L1(90, "Bucuresti", true, Apartament, 2, proprietariL1);
	cout << L1;

	/*cin >> L1;
	cout << L1;*/

	Locuinta L2=++L1;
	Locuinta L3=L1++;

	cout <<endl<< "Preincrementare: " << endl << "  L1: " <<L1<< endl << "  L2:"<<L2;
	cout <<endl<< "Postincrementare: " << endl << "   L1: " << L1 << endl << "   L3:" << L3;

	try 
	{
		cout << endl << endl << "Proprietarul numarul 2 este " << L1[-5];
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}

	string* proprietariL4 = new string[3]{ "Ronaldo", "Messi", "Mbappe"};
	Locuinta L4(250, "Paris", true, Casa, 3, proprietariL4);
	cout << endl << endl;
	cout << L4;

	cout << endl << endl;
	if (L4 <= L1)
		cout << "Suprafata inferioara pt L4";
	else
		cout << "Suprafata superioara pt L4";

	cout << endl << endl;
	try
	{
		if (L4 != -250)
			cout << "suprafata gresita";
		else
			cout << "Suprafata corecta";
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}

	L3 *= L4;
	cout << endl << endl << L3;

	try 
	{
		L4 + 0;
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}
	cout << endl << L4+15;

	Tip L5 = (Tip)L1;
	cout <<endl<<"Cod TIP: "<< L5;

	cout <<endl<<endl<< "Stergere un proprietar:";
	cout << endl << endl << L4(1);
}