#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

//pt test-constante, vb statice, operatori, try catch

enum Tip{Terestru, Acvatic, Pasare};
class Zoo
{
	const int id;
	char* denumireAnimal;
	Tip tip;
	float greutate;
	static int nrAnimale;

public:
	Zoo() :id(++nrAnimale)
	{
		this->denumireAnimal = nullptr;
		this->tip = Terestru;
		this->greutate = 0;
	}
	Zoo(const char* denumireAnimal, Tip tip, float greutate) :id(++nrAnimale)
	{
		this->denumireAnimal = new char[strlen(denumireAnimal) + 1];

		if (this->denumireAnimal != nullptr)
		{
			strcpy(this->denumireAnimal, denumireAnimal);
		}
		this->tip = tip;
		this->greutate = greutate;
	}

	//exemplu supraincarcare operator <=
	bool operator<=(float g)
	{
		if (g <= 0)
			throw exception();
		if (this->greutate <= g)
			return true;
		return false;
	}
	~Zoo()
	{
		if (this->denumireAnimal != nullptr)
		{
			delete[] this->denumireAnimal;
			this->denumireAnimal = nullptr;
		}
	}

	//supraincarcare operator == in afara clasei
	friend bool operator==(float g, const Zoo& z);

	//Operator=
	Zoo& operator=(const Zoo& z)
	{
		if (this->denumireAnimal != nullptr)
		{
			delete[] this->denumireAnimal;
			this->denumireAnimal = nullptr;
		}
		if (z.denumireAnimal != nullptr)
		{
			this->denumireAnimal = new char[strlen(z.denumireAnimal) + 1];
			strcpy(this->denumireAnimal, z.denumireAnimal);
		}

		this->tip = z.tip;
		this->greutate = z.greutate;

		return *this;
	}

	//Operator-=
	Zoo& operator-=(double g)
	{
		if (g < 0)
			throw exception();
		this->greutate -= g;

		return *this;
	}

	//Supraincarcare operator pre-incrementare
	Zoo& operator++()
	{
		this->greutate++;
		return *this;
	}

	Zoo(const Zoo& copie) :id(++nrAnimale)
	{
		this->greutate = copie.greutate;
		this->tip = copie.tip;

		if (copie.denumireAnimal != nullptr)
		{
			this->denumireAnimal = new char[strlen(copie.denumireAnimal) + 1];
			strcpy(this->denumireAnimal, copie.denumireAnimal);
		}
		else
			this->denumireAnimal = nullptr;
	}
	Zoo operator++(int)
	{
		Zoo copie = *this;
		this->greutate++;

		return copie;
	}

	//operator negatie
	bool operator!()
	{
		return this->greutate > 0;
	}

	//operator index
	Zoo& operator[](int index)
	{
		if (index > 0 && index < strlen(this->denumireAnimal) + 1)
		{
			cout << "Caracterul " << index << " din numele animalului este " << this->denumireAnimal[index];
		}
		else
			throw exception();
	}

	//operator cast explicit
	explicit operator char* ()
	{
		return this->denumireAnimal;
	}

	//operator functie care schiba denumirea animalului
	Zoo& operator()(const char* denumireNoua)
	{
		if (this->denumireAnimal != nullptr)
		{
			delete[] this->denumireAnimal;
			this->denumireAnimal = nullptr;
		}

		this->denumireAnimal = new char[strlen(denumireNoua) + 1];
		strcpy(this->denumireAnimal, denumireNoua);

		return *this;
	}

	//supraincarcare operator*
	
	Zoo& operator*(float g)
	{
		this->greutate=this->greutate* g;

		return *this;
	}
	//operator de afisare definit global

	friend ostream& operator<<(ostream& out, const Zoo& z);
	//operator de citire definit global

	friend istream& operator>>(istream& in, Zoo& z);
};
ostream& operator<<(ostream& out, const Zoo& z)
{
	out << endl<< "Id: " << z.id;
	if (z.denumireAnimal != nullptr)
	{
		out << endl << "Animal: " << z.denumireAnimal;
	}
	out << endl << "Tip: ";
	if (z.tip == 0)
		out << "Terestru";
	if (z.tip == 1)
		out << "Acvatic ";
	if (z.tip == 2)
		out << "Pasare ";

	out << endl << "Greutate: " << z.greutate;
	

	return out;
}

istream& operator>>(istream& in, Zoo& z)
{
	if (z.denumireAnimal != nullptr)
	{
		delete[] z.denumireAnimal;
		z.denumireAnimal = nullptr;
	}

	cout << endl << "Introduceti urmatoarele: ";

	char buffer[100];
	cout << endl<<"Denumire: ";
	in >> buffer;
	z.denumireAnimal = new char[strlen(buffer) + 1];
	strcpy(z.denumireAnimal, buffer);

	int tip;
	cout << endl<<"Tip: (0-Terestru 1-Acvatic 2-Pasare)";
	in >> tip;
	if (z.tip == 0)
		z.tip = Terestru;
	if (z.tip == 1)
		z.tip = Acvatic;
	if (z.tip == 2)
		z.tip = Pasare;
;
	cout << endl << "Greutate: ";
		in >> z.greutate;
		if (z.greutate < 0)
			throw exception();

		return in;
}

bool operator==(float idDeComparat, const Zoo& z)
{
	if (idDeComparat < 0)
		throw exception();
	if (z.id == idDeComparat)
		return true;
	return false;
}


int Zoo::nrAnimale = 0;

int main()
{
	Zoo z1("Curcan", Pasare, 80);
	try
	{
		cout << z1;
	}
	catch(...)
	{
		cout << endl<< "Nu putem avea o greutate negativa";
	}
	
	
	/*try
	{
		cin >> z1;
		cout << z1;
	}
	catch (...)
	{
		cout << endl << "Nu putem avea greutate negativa";
	}*/

	Zoo z2;
	z2 = z1;

	cout << z2;

	try
	{
		if (z2 <= -15)
			cout <<endl<< "Greutatea este sub 15kg";
		else
			cout <<endl<< "Greutatea este peste 15kg!";
	}
	catch (...)
	{
		cout <<endl<< "Introdu te rog o greutate de comparat, pozitiva!!";
	}

	try
	{
		if (1 == z1)
			cout << endl << "Acest animal are id egal cu valoarea data";
		else
			cout << endl << "Acest animal nu are id egal cu valoare data";
	}
	catch (...)
	{
		cout << "Introdu un id valid!!";
	}

	cout << endl << "Introduceti o greutate pe care sa o scadeti animalului: ";
	double greutate;
	cin >> greutate;

	try
	{
		z2 -= greutate;
	}
	catch (...)
	{
		cout << "Eroare! Greutatea trebuie sa scada nu sa creasca!!";
	}
	cout << endl<< z2;

	Zoo z3;
	z3 = ++z2;
	cout << endl << "Preincrementare: " <<endl<< "z2: " <<endl<< z2 << endl << "z3: " << endl<<z3;
	Zoo z4;

	
	
	z4 = z1++;
	cout << endl << "Postincrementare: " <<endl<< "z1: " << endl << z1 << endl << "z4: " << endl << z4;

	cout << endl << endl;
	if (!z1)
		cout << "Exista greutate";
	else
		cout << "Nu existe greutate";


	cout << endl << endl;
	try
	{
		z1[4];
	}
	catch (...)
	{
		cout << endl << "Ai depasit numarul de litere al denumirii animalului sau ai introdus o valoare negativa!!!";
	}

	cout << endl << endl;
	char* z5=(char*)z1;
	cout << "Apelare operator cast explicit->conversie din tipul Zoo in char*";
	cout << endl << z5;

	cout << endl << endl;
	z1("Girafa");
	cout << endl << "S-a gresit denumirea animalului de fapt caracteristicile sunt: ";
	cout << z1;

	cout << endl << endl;
	cout << "Greutatea dublata este: ";

	z1*(2);
	cout << z1;
}