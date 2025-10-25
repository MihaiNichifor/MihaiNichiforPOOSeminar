#include<iostream>
#include<string>

using namespace std;

enum Tip { BIO = 7, DE_BAZA = 3, NORMAL = 5 };
class ProdusAlimentar {
private:
	const int id;
	float pret;
	string denumire;
	int nrIngrediente;
	float* cantitati;
	Tip tip;
	static int nrProduseAlimentare;
public:
	//constructor default//fara parametri
	ProdusAlimentar() :id(++nrProduseAlimentare) {
		this->denumire = "Produs default";
		this->pret = 0;
		this->nrIngrediente = 0;
		this->cantitati = nullptr;
		this->tip = NORMAL;
	}

	ProdusAlimentar(string denumire, float pret, int nrIngrediente, float* cantitatiIngrediente, Tip tip) :id(++nrProduseAlimentare) {
		this->denumire = denumire;
		this->pret = pret;
		this->nrIngrediente = nrIngrediente;
		this->cantitati = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->cantitati[i] = cantitatiIngrediente[i];
		}
		this->tip = tip;

		delete[] cantitatiIngrediente;
	}

	void afisareProdusAlimentar() {
		cout << endl << this->id << ". Produsul alimentar " << this->denumire << " costa " << this->pret << " lei, este de tipul ";
		if (this->tip == NORMAL)
			cout << "NORMAL";
		else
			if (this->tip == 7)
				cout << "BIO";
			else
				if (this->tip == DE_BAZA)
					cout << "DE_BAZA";
		cout << " si contine " << this->nrIngrediente << " ingrediente: ";
		if (this->cantitati != nullptr) {
			for (int i = 0; i < this->nrIngrediente - 1; i++) {
				cout << this->cantitati[i] << " grame, ";
			}
			cout << this->cantitati[this->nrIngrediente - 1] << " grame.";
		}
	}

	//definim get si set pentru nrIngrdiente
	//acest getnrIngrediente va returna un int, deoarece vb nrIngrediente e de tipul int(tipul atributului din clasa)
	//avantajul metodei get e ca imi da acces la atributul respectiv, fiind in zona private get->imi da acces la valoarea atributului nrIngrediente
	int getnrIngrediente()
	{
		return this->nrIngrediente;
	}

	//metodele set sunt de tip void
	//set actualizeaza si modifica valori
	void setnrIngrediente(int nrIngredienteNou)
	{
		if (nrIngredienteNou > 0)
		{
			this->nrIngrediente = nrIngredienteNou;
		}
		else
		{
			//aloc o exceptie
			//throw exception();
			//throw 404;
			throw "Valoare negativa"; //in caz ca dau setNrIngrediente(-2) in main si imi va da exceptie, eroare de executie

			//La examen alegem o situatie din astea, de preferat thwor exception
		}
	}

	//get si set pentru pointeri
	float* getCantitati()
	{
		//return this->cantitati; --> afiseaza corect, dar nu fac asa pt ca permit accesul la aceasta adresa din exterior
		//facem deep copy, adica copie alocata la o zona de memorie noua
		float* copieCantitati = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) //sau pot sa fac i<this->getNrIngrediente ca imi returneaza nrIngrediente
		{
			copieCantitati[i] = this->cantitati[i];
		}
		return copieCantitati;

		//practic asa nu i permit utilizatorului sa acceseze aceeasi zona de memorie, am definit una noua in heap
		//daca utilizatorul sterge imi raman zona de memorie initiala
	}

	//o situatie unde putem avea si 2 parametrii, deoarece tre sa actualizez si dimensiunea
	void setCantitati(float* cantitatiNoi, int nrIngredienteNou)
	{
		setnrIngrediente(nrIngredienteNou); //setam noua dimensiune
		if (this->cantitati != nullptr)
		{
			delete[] this->cantitati; //practic intai dezaloc vectorul initial, ala din main cu newfloat[3]...
		}
		//aici fac alocarea de memorie pe vectorul existent, nu fac unul nou
		this->cantitati = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) //sau pot sa fac i<this->getNrIngrediente ca imi returneaza nrIngrediente
		{
			this->cantitati[i] = cantitatiNoi[i];
		}

		delete[] cantitatiNoi;
	}

	//Pasi:
	//1)verific daca vectorul de cantitati avea valori inainte, daca DA->DEZALOCAM
	//2)setez noua dimensiune a vectoruluj
	//3)aloc memorie pt noul vector si copiez valorile din vectorul primit ca parametru
	//4)dezaloc din vectorul primit ca parametru
	~ProdusAlimentar() {
		if (this->cantitati != nullptr) {
			delete[] this->cantitati;
		}
	}
};

int ProdusAlimentar::nrProduseAlimentare = 0;

void main() {
	ProdusAlimentar pizza;
	//pizza.pret = 30;

	pizza.afisareProdusAlimentar();
	float* cantitati = new float[3] {100, 200, 300};
	ProdusAlimentar* sushi = new ProdusAlimentar("sushi", 100, 3, cantitati, BIO);

	sushi->afisareProdusAlimentar();
	try {
		sushi->setnrIngrediente(2); //nringrediente va ramane tot 3, in loc de 4. //totusi imi afiseaza toate cele 4 cantitati ca am apelat setCantitati care transforma nrIngrdiente in 4
	}
	catch (const char* mesaj) {
		cout << endl << mesaj;
	}
	catch (int cod) {
		cout << endl << cod;
	}

	//acesta e un catch generic, pot prinde orice exceptie in el
	catch (...)
	{
		cout << endl << "Valoare negativa sau 0!";
	}
	//pot avea un singur bloc try, dar mai multe catch

	cout << endl << "Noul numar de ingrediente pt sushi este: " << sushi->getnrIngrediente();

	sushi->setCantitati(new float[4] {700, 300, 450, 100}, 4); //actualizam vectorul de cantitati
	//nu mai dezaloc primul float* cantitati, ca am dezalocat in set, si daca nu foloseam set tot nu-l dezalocam, deoarece era dezalocat in destructor

	float* cantitatiActuale = sushi->getCantitati();

	for (int i = 0; i < sushi->getnrIngrediente(); i++)
	{
		cout << endl << "Cantitati[" << i << "]: " << cantitatiActuale[i] << " grame. ";
	}

	delete[] cantitatiActuale;
	delete sushi;

}