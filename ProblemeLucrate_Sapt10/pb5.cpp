#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>

using namespace std;

class ExceptieCustom : public exception
{
public:
	ExceptieCustom(const char* mesaj) :exception(mesaj)
	{ }
};

class Serial
{
	const int id;
	char* denumire;
	int nrSezoane;
	int* nrEpisoade;
	int nrVizionari;
	bool ePeNetflix;
	static int nrSeriale;

public:
	Serial() :id(++nrSeriale)
	{
		this->denumire = nullptr;
		this->nrSeriale = 0;
		this->nrEpisoade = nullptr;
		this->nrVizionari = 0;
		bool ePeNetflix = true;
	}
	Serial(const char* denumire, int nrSezoane, int* nrEpisoade, int nrVizionari, bool ePeNetflix) :id(++nrSeriale)
	{
		this->denumire = new char[strlen(denumire) + 1];
		if (this->denumire != nullptr)
		{
			strcpy(this->denumire, denumire);
		}
		else
			this->denumire = nullptr;
		this->nrSezoane = nrSezoane;
		this->nrEpisoade = new int[this->nrSezoane];
		if (this->nrEpisoade != nullptr)
		{
			for (int i = 0; i < this->nrSezoane; i++)
				this->nrEpisoade[i] = nrEpisoade[i];
		}
		else
			this->nrEpisoade = nullptr;
		this->nrVizionari = nrVizionari;
		this->ePeNetflix = ePeNetflix;
	}

	int getnrSezoane()
	{
		return this->nrSezoane;
	}
	void setnrSezoane(int nrNouSezoane)
	{
		this->nrSezoane = nrNouSezoane;
	}
	int* getnrEpisoade()
	{
		int* copie;
		if (this->nrEpisoade != nullptr)
		{
			copie = new int[this->nrSezoane];
			for (int i = 0; i < this->nrSezoane; i++)
				copie[i] = this->nrEpisoade[i];
		}
		else
			copie = nullptr;
		return copie;
	}
	void setnrEpisoade(int nrNouSezoane, int* nrNouEpisoade)
	{
		setnrSezoane(nrNouSezoane);
		if (this->nrEpisoade != nullptr)
		{
			delete[] this->nrEpisoade;
			this->nrEpisoade = nullptr;
		}
		if (nrNouEpisoade != nullptr)
		{
			this->nrEpisoade = new int[nrNouSezoane];
			for (int i = 0; i < nrNouSezoane; i++)
				this->nrEpisoade[i] = nrNouEpisoade[i];
		}
		else
			this->nrEpisoade = nullptr;
	}

	Serial& operator++()
	{
		this->nrVizionari++;
		return *this;
	}

	Serial(const Serial& copie) :id(++nrSeriale)
	{
		if (copie.denumire != nullptr)
		{
			this->denumire = new char[strlen(copie.denumire) + 1];
			strcpy(this->denumire, copie.denumire);
		}
		this->nrSezoane = copie.nrSezoane;
		if (copie.nrEpisoade != nullptr)
		{
			this->nrEpisoade = new int[copie.nrSezoane];
			for (int i = 0; i < copie.nrSezoane; i++)
				this->nrEpisoade[i] = copie.nrEpisoade[i];
		}
		this->nrVizionari = copie.nrVizionari;
		this->ePeNetflix = copie.ePeNetflix;

	}
	Serial& operator++(int)
	{
		Serial copie = *this;
		this->nrVizionari++;
		return copie;
	}

	bool operator!()
	{
		if (!this->ePeNetflix)
			return false;
		return true;
	}
	bool operator<=(int x)
	{
		if (x < 0)
			throw ExceptieCustom("Din pacate ai introdus un numar invalid!!");
		if (this->nrVizionari <= x)
			return true;
		return false;
	}
	Serial& operator+=(int nr)
	{
		if (nr <= 0)
			throw ExceptieCustom("Din pacate ai introdus un numar invalid!!");
		this->nrVizionari += nr;
		return *this;
	}
	Serial operator*(int nr)
	{
		Serial copie = *this;
		copie.nrVizionari=copie.nrVizionari* nr;
		return copie;
	}
	explicit operator bool()
	{
		return this->ePeNetflix;
	}
	Serial& operator[](int index)
	{
		if (index >= 0 && index < this->nrSezoane)
		{
			this->nrEpisoade[index] = 2 * this->nrEpisoade[index];
		}
		else throw ExceptieCustom("Index Gresit!!!!");
		return *this;
	}

	Serial& operator()()
	{
		if (this->nrEpisoade != nullptr)
		{
			for (int i = 0; i < nrSezoane; i++)
				this->nrEpisoade[i] = 2 * this->nrEpisoade[i];
		}
		
		return *this;
	}

	Serial& operator=(Serial& s)
	{
		if (this->denumire != nullptr)
		{
			delete[] this->denumire;
			this->denumire = nullptr;
		}
		if (this->nrEpisoade != nullptr)
		{
			delete[] this->nrEpisoade;
			this->nrEpisoade = nullptr;
		}
		this->denumire = new char[strlen(s.denumire) + 1];
		strcpy(this->denumire, s.denumire);
		this->nrSezoane = s.nrSezoane;
		this->nrEpisoade = new int[s.nrSezoane];
		for (int i = 0; i < s.nrSezoane; i++)
			this->nrEpisoade[i] = s.nrEpisoade[i];
		this->nrVizionari = s.nrVizionari;
		this->ePeNetflix = s.ePeNetflix;

		return *this;
	}
	int getnrVizionari()
	{
		return this->nrVizionari;
	}
	friend ostream& operator<<(ostream& out, Serial& s);

	friend istream& operator>>(istream& in, Serial& s);

	~Serial()
	{
		if (this->nrEpisoade != nullptr)
		{
			delete[] this->nrEpisoade;
			this->nrEpisoade = nullptr;
		}
		if (this->denumire != nullptr)
		{
			delete[] this->denumire;
			this->denumire = nullptr;

		}
	}
};
ostream& operator<<(ostream& out, Serial& s)
{
	out << endl << "Id: " << s.id;
	out << endl << "Denumire: ";
	if (s.denumire != nullptr)
		out << s.denumire;
	else
		out << "X";
	out << endl << "Nr Sezoane: "<<s.nrSezoane;
	out << endl << "Nr Episoade: ";
	if (s.nrEpisoade != nullptr)
	{
		for (int i = 0; i < s.nrSezoane; i++)
			out << s.nrEpisoade[i] << " ";
	}
	out << endl << "Nr vizionari: "<<s.nrVizionari;
	out << endl << "Este pe Netflix? ";
	if (s.ePeNetflix == true)
		out << " DA";
	else
		out << " NU";

	return out;
}

istream& operator>>(istream& in, Serial& s)
{
	cout << endl;
	cout << "Introduceti: ";
	cout << endl << "Nume serial: ";
	char buffer[100];
	if (s.denumire != nullptr)
	{
		delete[] s.denumire;
		s.denumire = nullptr;
	}
	in.getline(buffer, 100);
	s.denumire = new char[strlen(buffer) + 1];
	strcpy(s.denumire, buffer);

	cout << endl << "Nr Sezoane: ";
	in >> s.nrSezoane;
	cout << endl << "Nr Episoade: ";
	if (s.nrEpisoade != nullptr)
	{
		delete[] s.nrEpisoade;
		s.nrEpisoade = nullptr;
	}
	s.nrEpisoade = new int[s.nrSezoane];
	for (int i = 0; i < s.nrSezoane; i++)
		in >> s.nrEpisoade[i];
	cout << endl << "Nr Vizualizari: ";
	in >> s.nrVizionari;
	cout << endl << "E pe Netflix? (0-NU, 1-DA)";
	in >> s.ePeNetflix;

	return in;
	
}
int Serial::nrSeriale = 0;

int main()
{
	int* EpisoadeS1 = new int[2] {9, 8};
	Serial s1("Alice in Borderland", 2, EpisoadeS1, 3000, true);

	cout << s1;

	int* EpisoadeS1Noi = new int[3] {9, 8, 6};
	s1.setnrSezoane(3);
	cout << endl <<endl<< "Nr Nou sezoane: " << s1.getnrSezoane();
	cout << endl << "Nr Nou Episoade: ";
	s1.setnrEpisoade(3, EpisoadeS1Noi);
	for (int i = 0; i < 3; i++)
		cout << s1.getnrEpisoade()[i] << " ";

	/*cin >> s1;
	cout << s1;*/

	Serial s2 = ++s1;
	Serial s3 = s1++;
	cout << endl << endl << "Preincrementare: S1: " << s1.getnrVizionari() << "  S2: " << s2.getnrVizionari();
	cout << endl << endl << "Postincrementare: S1: " << s1.getnrVizionari() << "  S3: " << s3.getnrVizionari();

	cout << endl << endl;
	if (!s1)
		cout << "E pe netflix";
	else
		cout << "Nu e pe netflix;";

	cout << endl << endl;
	try {
		if (s1 <= -5000)
			cout << "Serial nepopular";
		else
			cout << "Serial popular";
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}

	try {
		s1 += 2000;
		cout << endl <<"Nr vizionari dupa apelare operator+="<< s1.getnrVizionari();
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}

	cout <<endl<< (s1*3).getnrVizionari();

	try {
		cout << endl << s1[1];
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}

	cout << endl << s1();

	cout << endl << endl << endl;
	bool s4 = (bool)s1;
	if ((bool)s4 == 1)
		cout << endl << "E pe netflix";
	else
		cout << endl << "Nu e pe netflix";

	Serial s5;
	s5 = s1;
	cout << endl << endl;
	cout << s5;
}