#include <iostream>

#include <string>

using namespace std;

enum TipMaterie{CibInf, Statistica, Matematica, Altceva};

class Materie
{
	const int id;
	string denumire;
	float nrCredite;
	int nrStudenti;
	int* noteStudenti;
	TipMaterie tip;
	static int nrMaterii;

public:
	
	Materie() :id(++nrMaterii)
	{
		this->denumire = "X";
		this->nrCredite = 0;
		this->nrStudenti = 0;
		this->tip = Altceva;
		this->noteStudenti = nullptr;
	}

	Materie(const Materie& copie) :id(nrMaterii)
	{
		this->denumire = copie.denumire;
		this->nrCredite = copie.nrCredite;
		this->tip = copie.tip;
		this->nrStudenti = copie.nrStudenti;
		if (copie.noteStudenti != nullptr)
		{
			this->noteStudenti = new int[copie.nrStudenti];
			for (int i = 0; i < copie.nrStudenti; i++)
				this->noteStudenti[i] = copie.noteStudenti[i];
		}
		else
			this->noteStudenti = nullptr;
	}
	void operator=(const Materie& copie)
	{
		this->denumire = copie.denumire;
		this->nrCredite = copie.nrCredite;
		this->tip = copie.tip;
		this->nrStudenti = copie.nrStudenti;
		if (this->noteStudenti != nullptr)
		{
			delete[] this->noteStudenti;
			this->noteStudenti = nullptr;
		}
		if (copie.noteStudenti != nullptr)
		{
			this->noteStudenti = new int[copie.nrStudenti];
			for (int i = 0; i < this->nrStudenti; i++)
				this->noteStudenti[i] = copie.noteStudenti[i];
		}
		else
			this->noteStudenti = nullptr;
	}
	Materie(string denumire) :id(++nrMaterii)
	{
		this->denumire = denumire;
	}
	void afisareM()
	{
		cout <<endl<< " O materie care se va invata in cadrul facultatii CSIE este: " << this->denumire;
		cout << endl;
	}
	
	Materie(string denumire, float nrCredite, TipMaterie tip, int nrStudenti, int* noteStudenti) :id(++nrMaterii)
	{
		this->denumire = denumire;
		this->nrCredite = nrCredite;
		this->tip = tip;
		this->nrStudenti = nrStudenti;
		this->noteStudenti = new int[this->nrStudenti];
		for (int i = 0; i < this->nrStudenti; i++)
			this->noteStudenti[i] = noteStudenti[i];
	}

	void afisareMaterie()
	{
		cout << endl;
		cout << this->id << ". Materia " << this->denumire << " are un numar de " << this->nrCredite << " credite, se incadreaza in categoria ";
		if (this->tip == 0)
			cout << "Cibernetica sau Informatica economica ";
		if (this->tip == 1)
			cout << "Statistica ";
		if (this->tip == 2)
			cout << "Matematica ";
		if (this->tip == 3)
			cout << "Alta categorie ";
			
		cout<< " ,iar daca luam un numar de " << this->nrStudenti << " studenti observam ca acestia au obtinut notele: ";
		for (int i = 0; i < this->nrStudenti; i++)
			cout << this->noteStudenti[i] << " ";
		cout << endl;
	}

	int getnrStudenti()
	{
		return this->nrStudenti;
	}
	void setnrStudenti(int nrNouStudenti)
	{
		this->nrStudenti = nrNouStudenti;
	}

	int* getnoteStudenti()
	{
		int* copie;
		if (this->noteStudenti!= nullptr)
		{
			copie = new int[this->nrStudenti];
			for (int i = 0; i < this->nrStudenti; i++)
				copie[i] = this->noteStudenti[i];
			return copie;
		}
		else
			return nullptr;
		
	}
	void setnoteStudenti(int nrNouStudenti, int* noteNoiStudenti)
	{
		setnrStudenti(nrNouStudenti);
		if (this->noteStudenti != nullptr)
		{
			delete[] this->noteStudenti;
			this->noteStudenti = nullptr;
		}
		if (noteNoiStudenti != nullptr)
		{
			this->noteStudenti = new int[this->nrStudenti];
			for (int i = 0; i < this->nrStudenti; i++)
				this->noteStudenti[i] = noteNoiStudenti[i];
		}
		else
			this->noteStudenti = nullptr;

		delete[] noteNoiStudenti;

	}

	void adaugareNotaStudent(int notaNouStudent)
	{
		int copienrStudenti;
		copienrStudenti = this->nrStudenti;
		int* copienoteStudenti = new int[copienrStudenti];
		for (int i = 0; i < copienrStudenti; i++)
			copienoteStudenti[i] = this->noteStudenti[i];
		
		this->nrStudenti++;
		if (this->noteStudenti != nullptr)
		{
			delete[] this->noteStudenti;
			this->noteStudenti = nullptr;
		}
		this->noteStudenti = new int[this->nrStudenti];
		for (int i = 0; i < this->nrStudenti - 1; i++)
		{
			this->noteStudenti[i] = copienoteStudenti[i];
			cout << this->noteStudenti[i] << " ";
		}

		this->noteStudenti[this->nrStudenti-1] = notaNouStudent;
		cout << this->noteStudenti[this->nrStudenti-1];

		delete[] copienoteStudenti;
		

		
	}

	~Materie()
	{
		if (this->noteStudenti != nullptr)
		{
			delete[] this->noteStudenti;
			this->noteStudenti = nullptr;
		}
	}
};

int Materie::nrMaterii = 0;

int main()
{
	Materie m1("POO");
	m1.afisareM();
	Materie m4;
	m4.afisareMaterie();

	Materie* m2;
	int* notem2 = new int[4] {7, 10, 5, 3};
	m2 = new Materie("Analiza Matematica", 5, Matematica, 4, notem2);
	m2->afisareMaterie();
	int* noteNoim2 = new int[7] {7, 10, 5, 3, 9, 4, 8};
	m2->setnrStudenti(7);
	cout << " Vom vedea notele a " << m2->getnrStudenti() << " studenti: ";
	m2->setnoteStudenti(7, noteNoim2);
	for (int i = 0; i < m2->getnrStudenti(); i++)
		cout << m2->getnoteStudenti()[i] << " ";

	


	Materie m3(*m2); //daca as folosi m4 imi iau eroare, deoarece tre sa definesc obiect nou pt constructorul de copiere
	m3.afisareMaterie();

	
	m4 = *m2; //folosesc obiect deja existent pt operator egal
	m4.afisareMaterie();

	cout << endl << endl << "S-a introdus un nou student. Lista de note este: ";
	m2->adaugareNotaStudent(8);
	delete m2;

	
}