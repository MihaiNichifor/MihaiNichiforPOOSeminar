#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>

using namespace std;

enum NivelEchipa{Profesionist, SemiProfesionist, Amator, Altceva};

class Echipa
{
	const int id;
	char* numeEchipa;
	string tara;
	NivelEchipa nivel;
	int nrAniAnalizati;
	float* SumeCheltuite;
	int anInfiintare;
	static int nrEchipe;

public:
	Echipa() :id(nrEchipe++)
	{
		this->numeEchipa = nullptr;
		this->tara = "X";
		this->nivel = Amator;
		this->nrAniAnalizati = 0;
		this->SumeCheltuite = nullptr;
		this->anInfiintare = 0;
	}
	Echipa(NivelEchipa nivel) :id(nrEchipe)
	{
		this->nivel = nivel;

		this->numeEchipa = nullptr;
		this->tara = "X";
		this->nrAniAnalizati = 0;
		this->SumeCheltuite = nullptr;
		this->anInfiintare = 0;
	}
	

	Echipa(const char* numeEchipa, int anInfiintare) :id(nrEchipe)
	{
		this->numeEchipa = new char[strlen(numeEchipa) + 1];
		strcpy(this->numeEchipa, numeEchipa);
		this->anInfiintare = anInfiintare;

		this->tara = "X";
		this->nivel = Amator;
		this->nrAniAnalizati = 0;
		this->SumeCheltuite = nullptr;

	}
	
	Echipa(const char* numeEchipa, string tara, NivelEchipa nivel, int anInfiintare, int nrAniAnalizati, float* sumeCheltuite) :id(++nrEchipe)
	{
		this->numeEchipa = new char[strlen(numeEchipa) + 1];
		strcpy(this->numeEchipa, numeEchipa);
		this->tara = tara;
		this->nivel = nivel;
		this->anInfiintare = anInfiintare;
		this->nrAniAnalizati = nrAniAnalizati;
		this->SumeCheltuite = new float[this->nrAniAnalizati];
		for (int i = 0; i < this->nrAniAnalizati; i++)
			this->SumeCheltuite[i] = sumeCheltuite[i];
	}
	void afisareEchipa()
	{
		cout << endl << endl;
		cout << this->id << " . Echipa ";
		if (this->numeEchipa != nullptr)
			cout << this->numeEchipa;
		else
			cout << "X";
		cout << " este din " << this->tara << " se afla la nivel ";
		if (this->nivel == 0)
			cout << "Profesionst, ";
		if (this->nivel == 1)
			cout << "Semi-Profesionist, ";
		if (this->nivel == 2)
			cout << "Amator, ";
		if (this->nivel == 3)
			cout << "Necunoscut, ";
		cout << " s-a infiinat in anul " << this->anInfiintare << " ,iar sumele cheltuite pe transferuri in ultimii " << this->nrAniAnalizati << " ani este: ";
		for (int i = 0; i < this->nrAniAnalizati; i++)
		{
			cout << endl << "An " << 2025 - (this->nrAniAnalizati - i) << ": ";
			cout << this->SumeCheltuite[i]<<" mil euro;";
		}

		
	}

	char* getnumeEchipa()
	{
		char* copie;
		copie = new char[strlen(this->numeEchipa) + 1];
		if (this->numeEchipa != nullptr)
		{
			strcpy(copie, this->numeEchipa);
			return copie;
		}
		else
			return nullptr;
	}
	void setnumeEchipa(const char* numeNouEchipa)
	{
		if (this->numeEchipa != nullptr)
		{
			delete[] this->numeEchipa;
			this->numeEchipa = nullptr;
		}
		if (numeNouEchipa != nullptr)
		{
			this->numeEchipa = new char[strlen(numeNouEchipa) + 1];
			strcpy(this->numeEchipa, numeNouEchipa);
		}
		else this->numeEchipa = nullptr;
	}

	int getnrAniAnalizati()
	{
		return this->nrAniAnalizati;
	}
	void setnrAniAnalizati(int nrNouAniAnalizati)
	{
		if (this->nrAniAnalizati > 0)
			this->nrAniAnalizati = nrNouAniAnalizati;
		else
			throw exception();
	}

	float* getsumeCheltuite()
	{
		float* copie;
		if (this->SumeCheltuite != nullptr)
		{
			copie = new float[this->nrAniAnalizati];
			return copie;
		}
		else
			return nullptr;
	}
	void setsumeCheltuite(int nrNouAniAnalizati, float* sumeNoiCheltuite)
	{
		setnrAniAnalizati(nrNouAniAnalizati);
		if (this->SumeCheltuite != nullptr)
		{
			delete[] this->SumeCheltuite;
			this->SumeCheltuite = nullptr;
		}
		if (sumeNoiCheltuite != nullptr)
		{
			this->SumeCheltuite = new float[nrNouAniAnalizati];
			for (int i = 0; i < this->getnrAniAnalizati(); i++)
				this->SumeCheltuite[i] = sumeNoiCheltuite[i];
		}
		else
			this->SumeCheltuite = nullptr;

		delete[] sumeNoiCheltuite;
	}

	Echipa(const Echipa& copie) :id(++nrEchipe)
	{
		if (copie.numeEchipa != nullptr)
		{
			this->numeEchipa = new char[strlen(copie.numeEchipa) + 1];
			strcpy(this->numeEchipa, copie.numeEchipa);
		}
		else
			this->numeEchipa = nullptr;
		this->tara = copie.tara;
		this->nivel = copie.nivel;
		this->anInfiintare = copie.anInfiintare;
		this->nrAniAnalizati = copie.nrAniAnalizati;
		if (copie.SumeCheltuite != nullptr)
		{
			this->SumeCheltuite = new float[copie.nrAniAnalizati];
			for (int i = 0; i < copie.nrAniAnalizati; i++)
				this->SumeCheltuite[i] = copie.SumeCheltuite[i];
		}
		else
			this->SumeCheltuite = nullptr;
	}
	void operator=(const Echipa& copie)
	{
		if (this->numeEchipa != nullptr)
		{
			delete[] this->numeEchipa;
			this->numeEchipa = nullptr;
		}
		if (copie.numeEchipa != nullptr)
		{
			this->numeEchipa = new char[strlen(copie.numeEchipa) + 1];
			strcpy(this->numeEchipa, copie.numeEchipa);
		}
		else
			this->numeEchipa = nullptr;
		this->tara = copie.tara;
		this->nivel = copie.nivel;
		this->anInfiintare = copie.anInfiintare;
		this->nrAniAnalizati = copie.nrAniAnalizati;
		if (this->SumeCheltuite != nullptr)
		{
			delete[] this->SumeCheltuite;
			this->SumeCheltuite != nullptr;
		}
		if (copie.SumeCheltuite != nullptr)
		{
			this->SumeCheltuite = new float[copie.nrAniAnalizati];
			for (int i = 0; i < copie.nrAniAnalizati; i++)
				this->SumeCheltuite[i] = copie.SumeCheltuite[i];
		}
		else
			this->SumeCheltuite = nullptr;

	}
	float medieSume()
	{
		float s = 0;
		for (int i = 0; i < this->nrAniAnalizati; i++)
			s += this->SumeCheltuite[i];
		if (this->nrAniAnalizati != 0)
			return s / this->nrAniAnalizati;
	}
	void stergereAn(int AnDeSters)
	{
		int copienrAniAnalizati;
		copienrAniAnalizati = this->nrAniAnalizati;
		float* copiesumeCheltuite;
		copiesumeCheltuite = new float[this->nrAniAnalizati];
		if(this->SumeCheltuite!=nullptr)
			for (int i = 0; i < this->nrAniAnalizati; i++)
				copiesumeCheltuite[i] = this->SumeCheltuite[i];

		delete[] this->SumeCheltuite;
		int j = 0;
		if (copiesumeCheltuite != nullptr)
		{
			this->nrAniAnalizati--;
			this->SumeCheltuite = new float[nrAniAnalizati];
			for (int i = 0; i < copienrAniAnalizati; i++)
			{
				if ((2025 - (nrAniAnalizati-i+1)) == AnDeSters)
				{
					this->SumeCheltuite[i] = copiesumeCheltuite[++j];
					
				}
				else
					this->SumeCheltuite[i] = copiesumeCheltuite[j];
				j++;
			}
		}

		delete[] copiesumeCheltuite;


	}
	~Echipa()
	{
		if (this->numeEchipa != nullptr)
		{
			delete[] this->numeEchipa;
			this->numeEchipa = nullptr;
		}
		if (this->SumeCheltuite != nullptr)
		{
			delete[] this->SumeCheltuite;
			this->SumeCheltuite = nullptr;
		}
	}

	
};

int Echipa::nrEchipe = 0;

int main()
{
	Echipa e1(Profesionist);
	e1.afisareEchipa();
	Echipa e2("Steaua Bucuresti", 1947);
	e2.afisareEchipa();

	float* sumchelt = new float[6] {1.5, 5, 2.5, 2, 5.4, 3.1};
	Echipa e3("Steaua Bucuresti", "Romania", Profesionist, 1947, 6, sumchelt);
	e3.afisareEchipa();


	e3.setnumeEchipa("CFR Cluj");
	e3.setnrAniAnalizati(4);
	cout <<endl<<endl<< " Echipa " << e3.getnumeEchipa() << " a cheltuit pe transferuri in ultimii " << e3.getnrAniAnalizati() << " ani: ";
	float* sumcheltCFRCluj = new float[4] {3.3, 2, 2.1, 1.6};
	for (int i = 0; i < e3.getnrAniAnalizati(); i++)
	{
		cout << endl << "An " << 2025 - (e3.getnrAniAnalizati() - i) << ": ";
		cout << sumcheltCFRCluj[i] << " mil euro;";
	}

	float* sumcheltJuventus = new float[5] {70, 85.5, 60, 30, 101.5};
	Echipa e4("Juventus", "Italia", Profesionist, 1897, 5, sumcheltJuventus );
	e4.afisareEchipa();

	Echipa e5(e4);
	e5.afisareEchipa();
	cout << "S-a schimbat id-ul, a devenit 3, ptc avem constructor de copiere! ";
	//de asemenea ptc am constructor de copiere am fost nevoit sa declar un nou obiect, daca faceam cu e1 luam eroare

	e1 = e4;
	e1.afisareEchipa();
	cout <<endl<< "S-a pastrat id-ul 0 de la e1!! Deci a mers operatorul =";

	cout <<endl<< "Suma medie cheltuita pe transferuri pentru Juventus este: " << e4.medieSume()<<"mil euro";
	
	//aici am putut folosi acelasi obiect
	e4.stergereAn(2023);
	cout <<endl<<endl<< " Dupa stergerea valorii din 2023 situatia arata in felul urmator: ";
	e4.afisareEchipa();


	delete[] sumchelt;
	delete[] sumcheltCFRCluj;
	delete[] sumcheltJuventus;
}