#include <iostream>

using namespace std;

class Calatorie
{
private:
	float pret = 0;

public:
	Calatorie()
	{
	}

	Calatorie(float pret)
	{
		this->pret = pret;
	}
	float getpret()
	{
		return this->pret;
	}
	//compunere->has a, a doua clasa contine una sau mai multe obiecte de tipul primei clase
	//mostenire->is a
};

class Vacanta
{
private:
	//1:1
	//Calatorie calatorie;

	//1:m
	Calatorie* calatorii;
	int nrCalatorii;
	string destinatie;

public:
	//pt toti parametrii, fie iau atributele din private
	//Vacanta(int nrCalatorii, Calatorie* calatorii)
	//SAU

	Vacanta(string destinatie, int nrCalatorii, float* preturi)
	{
		this->destinatie = destinatie;
		this->nrCalatorii = nrCalatorii;
		this->calatorii = new Calatorie[nrCalatorii];
		for (int i = 0; i < nrCalatorii; i++)
		{
			this->calatorii[i] = Calatorie(preturi[i]);
		}
	}

	Calatorie& operator[](int index)
	{
		if (index >= 0 && index < this->nrCalatorii)
		{
			return this->calatorii[index];
		}
		else
		{
			throw "Indexu este in afara intervalului!";
		}
	}

	string getDestinatie()
	{
		return this->destinatie;
	}

	Vacanta(const Vacanta& v)
	{
		this->nrCalatorii = v.nrCalatorii;
		this->destinatie = v.destinatie;
		if (v.calatorii != nullptr)
		{
			this->calatorii = new Calatorie[v.nrCalatorii];
			for (int i = 0; i < v.nrCalatorii; i++)
				this->calatorii[i] = v.calatorii[i];
		}
	}

	~Vacanta()
	{
		if (this->calatorii != nullptr)
		{
			delete[] this->calatorii;
			this->calatorii = nullptr;
		}
	}
	
	friend ostream& operator<<(ostream& out, const Vacanta& v);
};

ostream &operator<<(ostream& out, const Vacanta& v)
{
	out << "Afisare cu operator<<: ";
	out << endl << " Preturile celor " << v.nrCalatorii << " calatorii din destinatia " << v.destinatie << " sunt: ";
	if (v.calatorii != nullptr)
	{
		for (int i = 0; i < v.nrCalatorii; i++)
		{
			out << endl << "Calatoria " << i + 1 << ": " << v.calatorii[i].getpret();
		}
	}

	return out;
}


void main()
{
	Vacanta vacanta("Londra", 2, new float[2] {350, 140});
	/*cout << endl << "Pretul primei calatorii din " <<vacanta.getDestinatie() << " este: " << vacanta[0].getpret() << " euro.";

	Vacanta vacanta2 = vacanta;
	cout << endl << endl << "Destinatie: " << vacanta2.getDestinatie();
	cout << endl << endl << "Pret pt a doua calatorie: " << vacanta2[1].getpret() << " euro.";*/

	cout << vacanta;
}
