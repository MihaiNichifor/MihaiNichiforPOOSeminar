#include <iostream>

#include <string>

using namespace std;

enum TipServicii{IT, Contabilitate, Banca, AlteServicii};

class Firma
{
	string numeFirma;
	int nrAngajati;
	TipServicii tip;
	int PerioadaAnalizata; //analizam profitul pe ani, alegem noi pe cati ani
	float* ProfitAnual;

public:
	Firma()
	{
		this->numeFirma = "X";
		this->nrAngajati = 0;
		this->tip = AlteServicii;
		this->PerioadaAnalizata = 0;
		this->ProfitAnual = nullptr;
	}

	Firma(string numeFirma, int nrAngajati, TipServicii tip, int PerioadaAnalizata, float * ProfitAnual)
	{
		this->numeFirma = numeFirma;
		this->nrAngajati = nrAngajati;
		this->tip = tip;
		this->PerioadaAnalizata = PerioadaAnalizata;
		this->ProfitAnual = new float[this->PerioadaAnalizata];
		for (int i = 0; i < this->PerioadaAnalizata; i++)
			this->ProfitAnual[i] = ProfitAnual[i];
	}

	void afisareFirma()
	{
		cout << endl;
		cout << "Compania " << this->numeFirma << " are un numar de " << this->nrAngajati << " angajati,oferind servicii de ";
		if (this->tip == 0)
			cout << "IT. ";
		if (this->tip == 1)
			cout << "Contabilitate. ";
		if (this->tip == 2)
			cout << "Banking. ";
		if (this->tip == 3)
			cout << "Alt tip decat cele enumerate. ";
		cout << " Profitabilitatea companiei a fost analizata pe o perioada de " << this->PerioadaAnalizata << " ani, raportul in acesti ani fiind de: ";
		for (int i = 0; i < this->PerioadaAnalizata; i++)
		{
			cout << endl;
			cout << "Profit/Pierdere an " << 2025 - (this->PerioadaAnalizata - i)<<": ";
			cout<<this->ProfitAnual[i] << " mii euro";
		}

	}

	int getPerioadaAnalizata()
	{
		return this->PerioadaAnalizata;
	}
	void setPerioadaAnalizata(int PerioadaNouaAnalizata)
	{
		if (PerioadaNouaAnalizata > 4)
			this->PerioadaAnalizata = PerioadaNouaAnalizata;
		else
			throw exception();
	}

	float* getProfitAnual()
	{
		float* copieProfitAnual = new float[this->PerioadaAnalizata];
		for (int i = 0; i < this->PerioadaAnalizata; i++)
		{
			copieProfitAnual[i] = this->ProfitAnual[i];
		}
		return copieProfitAnual;
	}
	void setProfitAnual(float* ProfitNouAnual, int PerioadaNouaAnalizata)
	{
		setPerioadaAnalizata(PerioadaNouaAnalizata);
		if (this->ProfitAnual != nullptr)
			delete[] this->ProfitAnual;
		this->ProfitAnual = new float[this->PerioadaAnalizata];
		for (int i = 0; i < this->PerioadaAnalizata; i++)
			this->ProfitAnual[i] = ProfitNouAnual[i];
		
		delete[] ProfitNouAnual;
	}

	~Firma()
	{
		if (this->ProfitAnual != nullptr)
			delete[] this->ProfitAnual;
	}
};

int main()
{
	Firma NoName;
	NoName.afisareFirma();

	float* PerioadaAnalizataDeloitte = new float[4] {120, -30, 50, 200};
	Firma* Deloitte = new Firma("Deloitte", 400, Contabilitate, 4, PerioadaAnalizataDeloitte);

	Deloitte->afisareFirma();

	

	//Se solicita din partea conducerii raportul pe ultimii 7 ani!!
	//actualizam perioada analizata la 7, cu ajutorul metodelor set si get
	try
	{
		Deloitte->setPerioadaAnalizata(7);
	}
	catch (...)
	{
		cout << endl << endl;
		cout << "S-a cerut extinderea perioadei analizate! Nu se poate micsora numarul de ani!!!";
	}

	cout << endl << endl;
	cout<<" La solicitarea conducerii vom analizta Profitul/Pierderea pe o perioada de "<<Deloitte->getPerioadaAnalizata()<<" ani!";
	//actualizam profitul pe ultimii 7 ani, adica perioada analizata ceruta
	Deloitte->setProfitAnual(new float[7] {80, 150, -100, 120, -30, 50, 200}, 7);

	float* ProfitAnualActualizat = Deloitte->getProfitAnual();
	for (int i = 0; i < Deloitte->getPerioadaAnalizata(); i++)
	{
		cout << endl;
		cout << "Profit/Pierdere an " << 2025 - (Deloitte->getPerioadaAnalizata() - i) << ": ";
		cout << ProfitAnualActualizat[i] << " mii euro";
	}

	delete Deloitte;
	delete[] PerioadaAnalizataDeloitte;
	delete[] ProfitAnualActualizat;
}