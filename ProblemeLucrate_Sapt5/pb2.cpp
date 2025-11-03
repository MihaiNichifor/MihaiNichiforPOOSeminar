#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

using namespace std;

enum TipTren{IC, IR, RE, Privat};

class Tren
{
	const int id;
	string statiePlecare;
	char* statieSosire;
	TipTren tip;
	int nrVagoane;
	float pretCalatorie;
	int* locuriVagon;

public:
	Tren() :id(0)
	{
		this->statiePlecare = "X";
		this->statieSosire = nullptr;
		this->tip = Privat;
		this->nrVagoane = 0;
		this->pretCalatorie = 0;
		this->locuriVagon = nullptr;
	}
	Tren(int idC, string statiePlecare,const char* statieSosire) :id(++idC)
	{
		this->statiePlecare = statiePlecare;
		this->statieSosire = new char[strlen(statieSosire) + 1];
		strcpy(this->statieSosire, statieSosire);

	}
	void afisareRuta()
	{
		cout << "Trenul cu id " << this->id << " circula pe ruta " << this->statiePlecare << "-" << this->statieSosire << ".";
	}

	Tren(int idC, string statiePlecare,const char* statieSosire, TipTren tip, int nrVagoane, float pretCalatorie, int* locuriVagon) :id(++idC)
	{
		this->statiePlecare = statiePlecare;
		this->statieSosire = new char[strlen(statieSosire) + 1];
		strcpy(this->statieSosire, statieSosire);
		this->tip = tip;
		this->pretCalatorie = pretCalatorie;
		this->nrVagoane = nrVagoane;
		this->locuriVagon = new int[this->nrVagoane];
		for (int i = 0; i < this->nrVagoane; i++)
			this->locuriVagon[i] = locuriVagon[i];

	}
	void afisareTren()
	{
		cout << endl << endl;
		cout << " Trenul cu ID " << this->id << " de tip ";
		if (this->tip == 0)
			cout << "IC ";
		if (this->tip == 1)
			cout << "IR ";
		if (this->tip == 2)
			cout << "RE ";
		if (this->tip == 3)
			cout << "Privat ";
		cout << " pleaca din statia " << this->statiePlecare << " ,cirucla in directia ";
		if (this->statieSosire != nullptr)
			cout << this->statieSosire; 
		else
			cout << "Y";
		cout << " ,calatoria costa ";
		cout << this->pretCalatorie << " lei, iar trenul are " << this->nrVagoane << " vagoane cu un numar disponibil de locuri: ";
		for (int i = 0; i < this->nrVagoane; i++)
		{
			cout << endl << "Vagon " << i+1 << ": " << this->locuriVagon[i] << " locuri";
		}
	}

	Tren(const Tren& copie) :id(3)
	{
		this->statiePlecare = copie.statiePlecare;
		if (copie.statieSosire != nullptr)
		{
			statieSosire = new char[strlen(copie.statieSosire) + 1];
			strcpy(this->statieSosire, copie.statieSosire);
		}
		this->tip = copie.tip;
		this->pretCalatorie = copie.pretCalatorie;
		this->nrVagoane = copie.nrVagoane;
		if (copie.locuriVagon != nullptr)
		{
			this->locuriVagon = new int[copie.nrVagoane];
			for (int i = 0; i < this->nrVagoane; i++)
				this->locuriVagon[i] = copie.locuriVagon[i];
		}
	}
	void operator=(const Tren& copie)
	{
		this->statiePlecare = copie.statiePlecare;
		if (this->statieSosire != nullptr)
		{
			delete[] statieSosire;
			this->statieSosire = nullptr;
		}
		if (copie.statieSosire != nullptr)
		{
			this->statieSosire = new char[strlen(copie.statieSosire) + 1];
			strcpy(this->statieSosire, copie.statieSosire);

		}
		this->tip = copie.tip;
		this->pretCalatorie = copie.pretCalatorie;
		this->nrVagoane = copie.nrVagoane;
		if (this->locuriVagon != nullptr)
		{
			delete[] this->locuriVagon;
			this->locuriVagon = nullptr;
		}
		if (copie.locuriVagon != nullptr)
		{
			this->locuriVagon = new int[copie.nrVagoane];
			for (int i = 0; i < copie.nrVagoane; i++)
				this->locuriVagon[i] = copie.locuriVagon[i];
		}
		else this->locuriVagon = nullptr;
	}
	char* getstatieSosire()
	{
		char* copie;
		copie = new char[strlen(this->statieSosire) + 1];
		if (this->statieSosire != nullptr)
		{
			strcpy(copie, this->statieSosire);
			return copie;
		}
		else
			return nullptr;
	}
	void setstatieSosire(const char* statieNouaSosire)
	{
		if (this->statieSosire != nullptr)
		{
			delete[] statieSosire;
			statieSosire = nullptr;
		}
		if (statieNouaSosire != nullptr)
		{
			this->statieSosire = new char[strlen(statieNouaSosire) + 1];
			strcpy(this->statieSosire, statieNouaSosire);
		}
		else
			this->statieSosire = nullptr;
	}
	int getnrVagoane()
	{
		return this->nrVagoane;
	}
	void setnrVagoane(int nrNouVagoane)
	{
		if (this->nrVagoane > 0)
			this->nrVagoane = nrNouVagoane;
		else
			throw exception();
	}
	int* getlocuriVagoane()
	{
		int* copieVagon;
		if (this->locuriVagon != nullptr)
		{
			copieVagon = new int[this->nrVagoane];
			for (int i = 0; i < this->nrVagoane; i++)
				copieVagon[i] = this->locuriVagon[i];
			return copieVagon;
		}
		else
			return nullptr;

	}
	void setlocuriVagoane(int nrNouVagoane, int* locuriNoiVagon)
	{
		setnrVagoane(nrNouVagoane);
		if (this->locuriVagon != nullptr)
		{
			delete[] this->locuriVagon;
			locuriVagon = nullptr;
		}
		if (locuriNoiVagon != nullptr)
		{
			this->locuriVagon = new int[this->nrVagoane];
			for (int i = 0; i < this->nrVagoane; i++)
				this->locuriVagon[i] = locuriNoiVagon[i];
		}
		else
			this->locuriVagon = nullptr;

		delete[] locuriNoiVagon;

	}
	~Tren()
	{
		if (this->statieSosire != nullptr)
		{
			delete[] statieSosire;
			statieSosire = nullptr;
		}
		if (this->locuriVagon != nullptr)
		{
			delete[] locuriVagon;
			locuriVagon = nullptr;
		}
	}


};

int main()
{
	Tren t1(0, "Bucuresti", "Brasov");
	t1.afisareRuta();

	cout <<endl<< "In urma lucrarilor trenul va circula doar pana la statia ";
	t1.setstatieSosire("Ploiesti Vest");
	cout<<t1.getstatieSosire();


	int* locuriVagont2 = new int[5] {90, 85, 100, 75, 100};
	Tren t2(1, "Bucuresti", "Constanta", IC, 5, 70, locuriVagont2);
	t2.afisareTren();
	t2.afisareRuta();
	 
	cout << endl << endl;
	Tren t3(t2);
	t3.afisareTren();


	cout << endl << endl;
	Tren t4;
	t4 = t2;
	t4.afisareTren();
	cout << endl << endl;
	t4.afisareRuta();

	t2.setnrVagoane(7);
	cout <<endl<<endl<< " Dupa compunerea/ descompunerea trenului, noul numar de vagoane a devenit " << t2.getnrVagoane()<<" acestea avand un numar disponibil de locuri de: ";
	int* locuriNoiVagont2 = new int[7] {90, 85, 100, 75, 100, 80, 60};
	t2.setlocuriVagoane(7, locuriNoiVagont2);
	for (int i = 0; i < t2.getnrVagoane(); i++)
	{
		cout << endl << "Vagon " << i + 1 << ": " << t2.getlocuriVagoane()[i] << " locuri";
	}

}