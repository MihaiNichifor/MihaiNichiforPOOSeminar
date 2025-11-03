#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

using namespace std;

enum Tip { Alimentar, Supermarket, MiniMarket, Altfel};

class Magazin
{
	const int id;
	char* denumire;
	string oras;
	Tip tip;
	int nrProduse;
	float Suprafata;
	int PerioadaAnalizata;
	float* ProfitAnual;

public:
	Magazin() :id(0)
	{
		this->denumire = nullptr;
		this->oras = "X";
		this->tip = Altfel;
		this->nrProduse = 0;
		this->Suprafata = 0;
		this->PerioadaAnalizata = 0;
		this->ProfitAnual = nullptr;
	}

	Magazin(int idP, const char* denumire, string oras, Tip tip, int nrProduse, float Suprafata, int PerioadaAnalizata, float* ProfitAnual) :id(++idP)
	 
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->oras = oras;
		this->tip = tip;
		this->nrProduse = nrProduse;
		this->Suprafata = Suprafata;
		this->PerioadaAnalizata = PerioadaAnalizata;
		this->ProfitAnual = new float[this->PerioadaAnalizata];
		for (int i = 0; i < this->PerioadaAnalizata; i++)
			this->ProfitAnual[i] = ProfitAnual[i];

	}

	Magazin(const Magazin& copie) : id(copie.id)
	{
		
		if (copie.denumire != nullptr)
		{
			this->denumire = new char[strlen(copie.denumire) + 1];
			strcpy(this->denumire, copie.denumire);
		}
		else
			this->denumire = nullptr;
		this->oras = copie.oras;
		this->tip = copie.tip;
		this->nrProduse = copie.nrProduse;
		this->Suprafata = copie.Suprafata;
		this->PerioadaAnalizata = copie.PerioadaAnalizata;
		
		if (copie.ProfitAnual != nullptr)
		{
			this->ProfitAnual = new float[copie.PerioadaAnalizata];
			for (int i = 0; i < copie.PerioadaAnalizata; i++)
				this->ProfitAnual[i] = copie.ProfitAnual[i];
		}
		else
			this->ProfitAnual = nullptr;
	}
	void operator=(const Magazin& copie)
	{
		if (this->denumire != nullptr)
		{
			delete[] this->denumire;
			this->denumire = nullptr;
		}
		if (copie.denumire != nullptr)
		{
			this->denumire = new char[strlen(copie.denumire) + 1];
			strcpy(this->denumire, copie.denumire);
		}
		else
			this->denumire = nullptr;
		this->oras = copie.oras;
		this->tip = copie.tip;
		this->nrProduse = copie.nrProduse;
		this->Suprafata = copie.Suprafata;
		this->PerioadaAnalizata = copie.PerioadaAnalizata;
		if (this->ProfitAnual != nullptr)
		{
			delete[] this->ProfitAnual;
			this->ProfitAnual = nullptr;
		}
		if (copie.ProfitAnual != nullptr)
		{
			ProfitAnual = new float[copie.PerioadaAnalizata];
			for (int i = 0; i < copie.PerioadaAnalizata; i++)
				this->ProfitAnual[i] = copie.ProfitAnual[i];
		}
		else
			this->ProfitAnual = nullptr;
	}
	void afisareMagazin()
	{
		cout << this->id << ". Magazinul ";
		if (this->denumire != nullptr)
			cout << this->denumire;
		else
			cout << "-";
		cout << " se afla in orasul " << this->oras << " si este de tip ";
		if (this->tip == 0)
			cout << " alimentar. ";
		if (this->tip == 1)
			cout << " supermarket. ";
		if (this->tip == 2)
			cout << " mini-market. ";
		if (this->tip == 3)
			cout << " altul decat cele mentionate. ";

		cout << " Acesta are un numar de " << this->nrProduse << " produse, o suprafata de " << this->Suprafata << " mp, iar profitul/pierderea pe ultimii "
			<< this->PerioadaAnalizata << " ani este: ";
		for (int i = 0; i < this->PerioadaAnalizata; i++)
		{
			cout << endl << "Profit/Pierdere An " << 2025 - (this->PerioadaAnalizata - i) << ": ";
			cout << this->ProfitAnual[i] << " mii euro";
		}

		cout << endl << endl;
	}


	Magazin(const char* denumire) :id(0) 
	{
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->ProfitAnual = nullptr;
	}

	//afisare magazin, declarat in constructorul cu un singur parametru
	void afisareNumeMagazine()
	{
		if (this->denumire != nullptr)
			cout << this->denumire << " ,";
	}
	

	Magazin(int PerioadaAnalizata, float* ProfitAnual) :id(5)
	{
		this->PerioadaAnalizata = PerioadaAnalizata;
		this->ProfitAnual = new float[this->PerioadaAnalizata];
		for (int i = 0; i < this->PerioadaAnalizata; i++)
			this->ProfitAnual[i] = ProfitAnual[i];
	}
	void afisareProfituri()
	{
		cout << " pe " << this->PerioadaAnalizata << " ani este: ";
		for (int i = 0; i < this->PerioadaAnalizata; i++)
			{
				cout << endl << "An " << 2025 - (this->PerioadaAnalizata - i) << ": ";
				cout << this->ProfitAnual[i] << " mii euro";
			}
	}

	char* getdenumire()
	{
		if (this->denumire != nullptr)
		{
			char* copiedenumire = new char[strlen(this->denumire) + 1];
			strcpy(copiedenumire, this->denumire);
			return copiedenumire;
		}
		else
			return nullptr;
	}
	void setdenumire(const char* denumireNoua)
	{
		if (this->denumire != nullptr)
		{
			delete[] this->denumire;
			this->denumire = nullptr;
		}
		if (denumireNoua != nullptr)
		{
			this->denumire = new char[strlen(denumireNoua) + 1];
			strcpy(this->denumire, denumireNoua);
		}
		else
			this->denumire = nullptr;
			
	}

	int getPerioadaAnaliazata()
	{
		return this->PerioadaAnalizata;
	}
	void setPerioadaAnalizata(int PerioadaNouaAnalizata)
	{
		if(PerioadaAnalizata>0)
			this->PerioadaAnalizata = PerioadaNouaAnalizata;
	}

	float* getProfitAnual()
	{
		float* copieProfit = new float[this->PerioadaAnalizata];
		for (int i = 0; i < this->PerioadaAnalizata; i++)
			copieProfit[i] = this->ProfitAnual[i];

		return copieProfit;
	}
	void setProfitAnual(int PerioadaNouaAnalizata, float* ProfitNouAnual)
	{
		setPerioadaAnalizata(PerioadaNouaAnalizata);
		if (this->ProfitAnual != nullptr)
			delete[] this->ProfitAnual;
		this->ProfitAnual = new float[this->PerioadaAnalizata];
		for (int i = 0; i < this->PerioadaAnalizata; i++)
			this->ProfitAnual[i] = ProfitNouAnual[i];

		delete[] ProfitNouAnual;
	}



	~Magazin()
	{
		if (this->denumire != nullptr)
		{
			delete[] this->denumire;
			this->denumire = nullptr;
		}

		if (this->ProfitAnual != nullptr)
		{
			delete[] this->ProfitAnual;
			this->ProfitAnual = nullptr;
		}
	}
};


int main()
{
	Magazin random;
	random.afisareMagazin();


	float* ProfitAnual6 = new float[6] {500, 200, -50, -150, 30, 350};
	Magazin Lidl(1, "Lidl", "Bucuresti", Supermarket, 753, 3000, 6, ProfitAnual6);
	Lidl.afisareMagazin();
	
	Magazin Lidl2 = Lidl; //constructor de copiere-exemplu
	Lidl.afisareMagazin();

	Magazin Lidl3;
	Lidl3= Lidl; //operator egal-exemplu
	Lidl3.afisareMagazin();

	Lidl.setPerioadaAnalizata(9);
	cout<<"La solicitarea directorului se va analizat profitul pe "<< Lidl.getPerioadaAnaliazata()<<" ani.";
	float* ProfitAnual9 = new float[9] {150, 200, 300, 500, 200, -50, -150, 30, 350};
	Lidl.getProfitAnual();
	for (int i = 0; i < Lidl.getPerioadaAnaliazata(); i++)
	{
		cout << endl << "Profit/Pierdere An " << 2025 - (Lidl.getPerioadaAnaliazata() - i) << ": ";
		cout << ProfitAnual9[i] << " mii euro";
	}

	Lidl.setdenumire("MegaImage");
	char* numeNou=Lidl.getdenumire();
	cout << endl << "De fapt este vorba de magazinul " << numeNou;

	delete[] numeNou;

	
	//delete Lidl;

	//concluzii azi
	//la char* aloc de dimensiune (pun denumirea nu pointeru la denumire)+1
	//mai sus la afisari e doar diferenta unde se afiseaza stack sau heap
	//tre sa pun conditie la char* sa fie diferit de nullpointer pt a-mi afisa constructorul default si sa nu-mi crape
	//la fel ar fi trebuit si la float* sau int* doar ca nu-mi intra in bucla for si de aceea nu mai pun if
	//la operatorul egal pun conditie ca this->atribut!=nullptr si sterg ce e in adresa this->atribut si ii dau nullptr fata de constructorul de copiere unde doar pun conditie pt copie sa fie !=nullptr
	Magazin magazine[2]{ Magazin("Penny"),Magazin("Carrefour") };

	cout <<endl<<endl<< " Magazinele ce se gasesc in orasul Ploiesti sunt: ";
	for (int i = 0; i < 2; i++)
		magazine[i].afisareNumeMagazine();

	float* BilantKaufland=new float[7]{ 300, 200, -100, 500, 800, 450, 239 };
	Magazin Kaufland(7, BilantKaufland);

	cout <<endl<<endl<< "Bilantul magazinului Kaufland";
	Kaufland.afisareProfituri();

	delete[] BilantKaufland;
}