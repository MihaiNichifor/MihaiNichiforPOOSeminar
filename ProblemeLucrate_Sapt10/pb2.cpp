#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

using namespace std;

class ExceptieCustom : public exception
{
public:
	ExceptieCustom(const char* mesaj): exception(mesaj)
	{ }
};

class Joc
{
	const int id;
	char* denumire;
	int vechime;
	int* utilizatoriAnuali;
	float pret;
	static int nrJocuri;

public:
	Joc() :id(0)
	{
		this->denumire = nullptr;
		this->pret = 0;
		this->vechime = 9;
		this->utilizatoriAnuali = nullptr;
	}

	Joc(const char* denumire, float pret, int vechime, int* utilizatoriAnuali) :id(++nrJocuri)
	{
		this->denumire = new char[strlen(denumire) + 1];
		if (this->denumire != nullptr)
		{
			strcpy(this->denumire, denumire);
		}
		else
			this->denumire = nullptr;

		if (pret >= 0)
			this->pret = pret;
		else
			throw ExceptieCustom("Nu putem avea pret negativ!");

		
		this->vechime = vechime;
		this->utilizatoriAnuali = new int[this->vechime];
		if (this->utilizatoriAnuali != nullptr)
		{
			for (int i = 0; i < vechime; i++)
				this->utilizatoriAnuali[i] = utilizatoriAnuali[i];
		}
		else
			this->utilizatoriAnuali = nullptr;
		
	}
	~Joc()
	{
		if (this->denumire != nullptr)
		{
			delete[] this->denumire;
			this->denumire = nullptr;
		}
		if (this->utilizatoriAnuali != nullptr)
		{
			delete[] this->utilizatoriAnuali;
			this->utilizatoriAnuali = nullptr;
		}
	}

	char* getdenumire()
	{
		char* copie;
		if (this->denumire != nullptr)
		{
			copie = new char[strlen(denumire) + 1];
			strcpy(copie, denumire);

			return copie;
		}
		else
			return nullptr;
	}
	Joc& operator=(const Joc& j)
	{
		if (this->denumire != nullptr)
		{
			delete[] this->denumire;
			this->denumire = nullptr;
		}

		if (this->utilizatoriAnuali != nullptr)
		{
			delete[] this->utilizatoriAnuali;
			this->utilizatoriAnuali = nullptr;
		}

		this->denumire = new char[strlen(j.denumire) + 1];
		strcpy(this->denumire, j.denumire);

		this->pret = j.pret;
		this->vechime = j.vechime;
		this->utilizatoriAnuali = new int[j.vechime];
		for (int i = 0; i < j.vechime; i++)
		{
			this->utilizatoriAnuali[i] = j.utilizatoriAnuali[i];
		}

		return *this;
	}

	bool operator>=(int vechime)
	{
		if (vechime > 25 && vechime<0)
			throw ExceptieCustom("Nu exista sau sunt invalide jocurile dinainte de secolul 21 s	au din viitor!!!");
		if (this->vechime >= vechime)
			return true;
		return false;
	}

	bool operator==(float pret)
	{
		if(pret<0)
			throw ExceptieCustom("Introdu te rog un pret valid!!");
		if (this->pret == pret)
			return true;
		return false;
	}
	
	bool operator!()
	{
		if (!this->pret)
			return true;
		return false;
	}
	friend ostream& operator<<(ostream& out, const Joc& j);

	friend istream& operator>>(istream& in, Joc& j);

	//preincrementare
	Joc& operator++()
	{
		this->pret++;
		return *this;
	}

	float getpret()
	{
		return this->pret;
	}

	//CONCLUZIE->LA PREINCREMENTARE pun REFERINTA, deoarece modific
	// obiectul inainte de a-l returna pe cand la POSTINCREMENTARE,
	// intai returnez si dupa modific, deci obiectul ramane pe LOC

	Joc(const Joc& copie) :id(++nrJocuri)
	{
		if (copie.denumire != nullptr)
		{
			this->denumire = new char[strlen(copie.denumire) + 1];
			strcpy(this->denumire, copie.denumire);
		}
		else
			this->denumire = nullptr;

		this->pret = copie.pret;
		this->vechime = copie.vechime;


		if (copie.utilizatoriAnuali != nullptr)
		{
			this->utilizatoriAnuali = new int[copie.vechime];
			for (int i = 0; i < copie.vechime; i++)
			{
				this->utilizatoriAnuali[i] = copie.utilizatoriAnuali[i];
			}
		}
		else
			this->utilizatoriAnuali = nullptr;
		
	}

	//postincrementare
	Joc operator++(int)
	{
		Joc copiere = *this;;
		this->pret++;

		return copiere;
	}

	//operator functie care mai adauga utilizatori pentru mai multi ani
	Joc& operator()(int nrAni, int *utilizatoriNoi)
	{
		int* copie=nullptr;
		
		if (this->utilizatoriAnuali != nullptr)
		{
			copie = new int[this->vechime];
			for (int i = 0; i < this->vechime; i++)
			{
				copie[i] = this->utilizatoriAnuali[i];
			}
		}
		delete[] this->utilizatoriAnuali;
		int vechimeInitiala=this->vechime;
		this->vechime = this->vechime + nrAni;
		this->utilizatoriAnuali = new int[this->vechime];
		for (int i = 0; i < vechimeInitiala; i++)
		{
			this->utilizatoriAnuali[i] = copie[i];
		}

		for (int i = 0; i < nrAni; i++)
		{
			this->utilizatoriAnuali[vechimeInitiala + i] = utilizatoriNoi[i];
		}

		delete[] copie;

		return *this;
	}

	//operator index->dublare nr utilizatori dintr-un an dat
	Joc& operator[](int index)
	{
		if (index > 0 && index < this->vechime)
		{
			this->utilizatoriAnuali[index] = 2 * this->utilizatoriAnuali[index];
		}
		else
			throw ExceptieCustom("Introdu un index valid!!!");

		return *this;
	}


	Joc& operator+=(float pretDeAdaugat)
	{ 
		if (pretDeAdaugat < 0)
			throw ExceptieCustom("Introdu o valoare pozitiva!!");
		
		this->pret += pretDeAdaugat;

		return *this;
	}

	Joc operator-(const Joc &j)
	{
		Joc copie = *this;
		copie.pret=copie.pret - j.pret;

		return copie;
	}

	float operator/(int nr)
	{
		if (nr)
			return this->pret / nr;
		else
			throw ExceptieCustom("Nu putem imparti la 0!!!");
	}

	explicit operator int()
	{
		return this->vechime;
	}
};

ostream& operator<<(ostream& out, const Joc& j)
{
	out << endl;
	out << "Id: " << j.id;
	if(j.denumire!=nullptr)
		out << endl << "Denumire Joc: " << j.denumire;
	else
		out << endl << "Denumire Joc: " << "X";

	out << endl << "Pret: " << j.pret;
	out << endl << "Vechime: " << j.vechime;
	if (j.utilizatoriAnuali != nullptr)
	{
		out << endl << "Numar Utilizatori anuali: ";
		for (int i = 0; i < j.vechime; i++)
			out << endl << "	An " << 2025 - j.vechime + i <<": "<< j.utilizatoriAnuali[i] << " utilizatori ";
	}
	else
		out << endl << "Numar Utilizatori anuali: ";


	return out;
}

istream& operator>>(istream& in, Joc& j)
{
	if (j.denumire != nullptr)
	{
		delete[] j.denumire;
		j.denumire = nullptr;
	}
	if (j.utilizatoriAnuali != nullptr)
	{
		delete[] j.utilizatoriAnuali;
		j.utilizatoriAnuali = nullptr;
	}
	cout << endl << "Introduceti urmatoarele: ";
	char buffer[100];
	cout << endl << "Denumire: ";
	in >> buffer;
	j.denumire = new char[strlen(buffer) + 1];
	strcpy(j.denumire, buffer);

	cout << endl << "Pret: ";
	in >> j.pret;
	cout << endl << "Vechime: ";
	in >> j.vechime;

	cout << endl << "Nr Utilizatori Anuali: ";
	j.utilizatoriAnuali = new int[j.vechime];
	for (int i = 0; i < j.vechime; i++)
	{
		cout << endl << "	An " << 2025 - j.vechime + i << ": ";
		in >> j.utilizatoriAnuali[i];
	}

	return in;
}

int Joc::nrJocuri = 0;

int main()
{
	int *utilizatoriJoc1 = new int[5] {20, 40, 75, 67, 30};

	try
	{
		Joc joc1("Clash Royale", 0, 5, utilizatoriJoc1);
		cout << joc1;
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}
	Joc joc1("Clash Royale", 0, 5, utilizatoriJoc1);

	/*cin >> joc1;
	cout << joc1;*/

	Joc joc2;
	joc2 = joc1;

	cout << joc2;


	try
	{
		if (joc1 >= 10)
			cout <<endl<< "Joc Vechi!";
		else
			cout <<endl<< "Joc Nou!";
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}

	try
	{
		if (joc1 == 20)
			cout <<endl<< "Pretul este de 20 de lei";
		else
			cout <<endl<< "Pretul nu este de 20 de lei";

	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}

	cout << endl << endl;
	if (!joc1)
		cout << "Joc gratuit! ";
	else
		cout << "Jocul costa bani!!";


	Joc joc3;
	joc3 = ++joc1;
	cout <<endl<<"Pret: Preincrementare "<<joc3.getdenumire()<<": "<< joc3.getpret();

	Joc joc4=joc1++;
	cout <<endl<<"Pret: Postincrementare "<<joc4.getdenumire()<<": "<< joc4.getpret();

	cout << endl << endl;
	int* utilizatoriNoiJoc1 = new int[3] {30, 40, 70};
	joc1(3, utilizatoriNoiJoc1);

	cout << joc1;

	joc1[3];
	cout << endl << endl << joc1;

	joc1 += 50;
	cout << endl << endl;

	cout <<"Pret nou "<<joc1.getdenumire()<<": "<< joc1.getpret() << " lei";

	joc1=joc1 - joc3;
	cout << endl<<"Scadere pret joc 1 cu pret joc 3 prin operator-: "<<joc1.getpret() << " lei";

	int joc5 = (int)joc1;
	cout << endl << endl << "Vechime: "<<joc5<<" ani";

	try 
	{
		joc1 / 0;
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}
	cout<<endl<<"Pretul impartit la 10: "<<joc1 / 10 << " lei!";
}