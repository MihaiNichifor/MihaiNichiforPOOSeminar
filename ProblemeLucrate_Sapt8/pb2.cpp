#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

using namespace std;

class ExceptieMetrou : public exception
{
public:
	ExceptieMetrou(const char* mesajeroare) : exception(mesajeroare)
	{
	}
};


enum Magistrala{M1=1, M2=2, M3=3, M4=4, M5=5};
class MetrouBucuresti
{
	const int id;
	string statie;
	float distantaParcursa;
	Magistrala magistrala;
	char* destinatie;

public:
	static const float DISTANTA_MINIMA;
	MetrouBucuresti() :id(0)
	{
		this->statie = "X";
		this->distantaParcursa = 0;
		this->magistrala = M1;
		this->destinatie = nullptr;
	}

	MetrouBucuresti(int idM, string statie, float distantaParcursa, Magistrala magistrala, const char* destinatie) :id(idM)
	{
		this->statie = statie;
		this->distantaParcursa = distantaParcursa;
		this->magistrala = magistrala;
		this->destinatie = new char[strlen(destinatie)+1];
		strcpy(this->destinatie, destinatie);

		if (this->distantaParcursa < DISTANTA_MINIMA)
			throw ExceptieMetrou("Eroare! Trenul nu poate parcurge o distanta negative");
	}

	void afisare()
	{
		cout << endl << endl;
		cout << this->id << ". In acest moment trenul circula pe M" << this->magistrala << ", se afla la statia " << this->statie;
		cout << ", a parcurs o distanta de " << this->distantaParcursa << " km si circula in directia: ";
		if (this->destinatie != nullptr)
			cout << this->destinatie;
	}

	MetrouBucuresti& operator=(const MetrouBucuresti& m)
	{
		if (this->destinatie != nullptr)
		{
			delete[] this->destinatie;
			this->destinatie = nullptr;
		}
		this->statie = m.statie;
		this->distantaParcursa = m.distantaParcursa;
		this->magistrala = m.magistrala;
		this->destinatie = new char[strlen(m.destinatie) + 1];
		strcpy(this->destinatie, m.destinatie);

		return *this;
	}

	//operator >
	bool operator>(const MetrouBucuresti& m)
	{
		if (this->distantaParcursa > m.distantaParcursa)
			return true;
		return false;
	}

	//operator functie
	Magistrala operator()(string statie)
	{
		if (statie == "Piata Unirii" || statie == "Piata Victoriei")
			return M1;
		return M5;
	}

	char operator[](int index)
	{
		if ((index >= 0) && (index < (strlen(this->destinatie) + 1)))
			return this->destinatie[index];
		else
			throw ExceptieMetrou("Te rog sa introduci un Index Valid!!");
	}
	~MetrouBucuresti()
	{
		if (this->destinatie != nullptr)
		{
			delete[] this->destinatie;
			this->destinatie = nullptr;
		}
	}
	friend void operator<<(ostream& out, const MetrouBucuresti& m);

	explicit operator char*()
	{
		return this->destinatie;
		delete[] this->destinatie;
		this->destinatie = nullptr;
	}
};

void operator<<(ostream& out, const MetrouBucuresti& m)
{
	out << endl << endl;
	out << m.id << ". In acest moment trenul circula pe M" << m.magistrala << ", se afla la statia " << m.statie;
	out << ", a parcurs o distanta de " << m.distantaParcursa << " km si circula in directia: ";
	if (m.destinatie != nullptr)
		cout << m.destinatie;
}

class MetrouScurtat :public MetrouBucuresti
{
private:
	char* destinatieNoua;
public:
	MetrouScurtat() :MetrouBucuresti()
	{
		this->destinatieNoua = nullptr;
	}
	MetrouScurtat(int idM, string statie, float distantaParcursa, Magistrala magistrala, const char* destinatie, const char* destinatieNoua)
		:MetrouBucuresti(idM, statie, distantaParcursa, magistrala, destinatie)
	{
		this->destinatieNoua = new char[strlen(destinatieNoua) + 1];
		strcpy(this->destinatieNoua, destinatieNoua);
	}

	void afisare() 
	{
		cout << endl;
		this->MetrouBucuresti::afisare();
		cout << endl << "Dupa un accident trenul va circula doar pana la statia: ";
		if (this->destinatieNoua != nullptr)
			cout << this->destinatieNoua;

	}

	~MetrouScurtat()
	{
		if (this->destinatieNoua != nullptr)
		{
			delete[] this->destinatieNoua;
			this->destinatieNoua = nullptr;
		}
	}
};
const float MetrouBucuresti::DISTANTA_MINIMA = 0;

class DistantaInterface
{
public: 
	virtual float DistantaTotala(float LungimeMagistrala, int nrCurse) = 0;
};

class DistantaParcursa : public DistantaInterface
{
public:
	float DistantaTotala(float LungimeMagistrala, int nrCurse)
	{
		if (LungimeMagistrala != 0 && nrCurse != 0)
			return LungimeMagistrala * nrCurse;
		else
			throw ExceptieMetrou("Nu putem avea lungime sau numar de curse negative!!");
	}

};




int main()
{
	
	try
	{
		MetrouBucuresti MB1(1, "Piata Romana", -6.4, M2, "Pipera");
	}
	catch (ExceptieMetrou e)
	{
		cout << endl << e.what();
	}

	MetrouBucuresti MB1(1, "Piata Romana", 6.4, M2, "Pipera");
	MB1.afisare();

	MetrouScurtat MB2(2, "Piata Romana", 6.4, M2, "Pipera", "Piata Victoriei");
	MB2.afisare();

	DistantaInterface* distanta = new DistantaParcursa();

	
	try
	{
		cout << endl << "In total metroul a parcurs astazi "<<distanta->DistantaTotala(20.38, 30)<< " km.";
	}
	catch (ExceptieMetrou e)
	{
		cout << endl << e.what();
	}
	
	cout << endl << "Implementare Operator Egal: ";
	MetrouBucuresti MB3;
	MB3 = MB1;
	MB3.afisare();

	MetrouBucuresti MB4(4, "Eroilor", 10, M1, "Gara de Nord-Dristor 2");
	MB4.afisare();
	if (MB4 > MB3)
		cout <<endl<< "Metroul M1 parcurge o distanta mai lunga decat M2";
	else
		cout << endl << "Metroul M2 parcurge o distanta mai lunga decat M1";

	MetrouBucuresti MB5(5, "Piata Unirii", 5, M2, "Pipera");
	MB5.afisare();
	if (MB5("Piata Unirii") == M1)
		cout <<endl<< " Aceasta statie are corespondenta cu Magistrala 1";
	else
		cout <<endl<< " Aceasta statie nu are corespondenta cu Magistrala 1";

	cout<<endl<<"Apelare Operator INDEX: "<<MB5[0];

	cout <<endl<< "Apelare operator <<: " << MB5;

	cout << endl << "Apelare operator cast: " << (char*)(MB5);
}