#include<iostream>
#include<string>

using namespace std;
enum Tip { BIO = 7, DE_BAZA = 3, NORMAL = 5 };

class ProdusAlimentar {
private:
	const int id;
	float pret;
	string denumire;
	Tip tip;
	int nrIngrediente;
	float* cantitati;
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

	ProdusAlimentar(const ProdusAlimentar& copie) :id(++nrProduseAlimentare) {
		this->pret = copie.pret;
		this->denumire = copie.denumire;
		this->tip = copie.tip;
		this->nrIngrediente = copie.nrIngrediente;

		if (copie.cantitati != nullptr) {
			this->cantitati = new float[copie.nrIngrediente];
			for (int i = 0; i < copie.nrIngrediente; i++) {
				this->cantitati[i] = copie.cantitati[i];
			}
		}
		else {
			this->cantitati = nullptr;
		}
	}

	void operator=(const ProdusAlimentar& copie) {
		this->denumire = copie.denumire;
		this->pret = copie.pret;
		this->tip = copie.tip;
		this->nrIngrediente = copie.nrIngrediente;

		if (this->cantitati != nullptr) {
			delete[] this->cantitati;
			this->cantitati = nullptr;
		}

		if (copie.cantitati != nullptr) {
			this->cantitati = new float[copie.nrIngrediente];
			for (int i = 0; i < copie.nrIngrediente; i++) {
				this->cantitati[i] = copie.cantitati[i];
			}
		}
		else {
			this->cantitati = nullptr;
		}
		//return *this;
	}

	void afisareProdusAlimentar() {
		cout << endl << this->id << ". Produsul alimentar " << this->denumire << " costa " << this->pret << " lei, este de tipul ";
		if (this->tip == NORMAL) cout << "NORMAL";
		if (this->tip == BIO) cout << "BIO";
		if (this->tip == DE_BAZA) cout << "DE_BAZA";
		cout << " si contine " << this->nrIngrediente << " ingrediente: ";
		if (this->cantitati != nullptr) {
			for (int i = 0; i < this->nrIngrediente - 1; i++) {
				cout << this->cantitati[i] << " grame, ";
			}
			cout << this->cantitati[this->nrIngrediente - 1] << " grame.";
		}
	}

	

	~ProdusAlimentar() {
		if (this->cantitati != nullptr) {
			delete[] this->cantitati;
		}
	}

	void operator+=(float pretDeAdunat) {
		this->pret += pretDeAdunat;
	}

	bool operator>(const ProdusAlimentar& pa) {
		return this->pret > pa.pret;
	}

	bool operator>=(int x) const
	{
		if (this->nrIngrediente >= x)
			return true;
		return false;
	}
	bool operator<=(int x) const
	{
		if (this->pret <= x)
			return true;
		return false;
	}
	//operatorul negatie
	bool operator!()
	{
		return this->pret > 0;
	}

	//operatorul functie de calculare a mediei cantitatilor
	float operator()(int nrCantitati)
	{
		float s = 0, ma=0;
		for (int i = 0; i < this->nrIngrediente; i++)
			s += this->cantitati[i];
		if (this->nrIngrediente != 0)
			ma = s / this->nrIngrediente;

		return ma;
	}

	//operator index
	float& operator[](int index)
	{
		if (index >= 0 && index < this->nrIngrediente)
		{
			return this->cantitati[index];
		}
		else
			throw exception();
	}

	//operator << / operator de afisare
	friend void operator<<(ostream& out, ProdusAlimentar prod) //nu am acces la this in private
	{
		out << endl << "Opretaor de afisare: ";
		out << endl << "Id: " << prod.id;
		out << endl << "Denumire: " << prod.denumire;
		out << endl << "Pret: " << prod.pret;
		out << endl << "Tip: ";
		if (prod.tip == NORMAL) out << "NORMAL";
		if (prod.tip == BIO) out << "BIO";
		if (prod.tip == DE_BAZA) out << "DE_BAZA";
		out << endl << "Nr ingrediente: " << prod.nrIngrediente;

		if (prod.cantitati != nullptr)
		{
			out << endl << "Cantitati: ";
			for (int i = 0; i < prod.nrIngrediente - 1; i++) {
				cout << prod.cantitati[i] << " grame, ";
			}
			cout << prod.cantitati[prod.nrIngrediente - 1] << " grame.";
		}
	}

	friend void operator>>(istream& in, ProdusAlimentar& prod) //actualizez obiect deja existent, deci transmit ProdusAlimentar prin referinta
	{
		//in operatorul >> constantele nu se pot citi de la tastatura
		cout << endl << "Pret: ";
		in >> prod.pret;

		cout << endl << "Denumire: ";
		in >> prod.denumire;

		cout << endl << "Tip: ";
		int tip;
		in >> tip;
		if (tip == 5) prod.tip = NORMAL;
		if (tip == 7) prod.tip = BIO;;
		if (tip == 3) prod.tip = DE_BAZA;

		cout << endl << "Nr ingrediente: ";
		in >> prod.nrIngrediente;

		cout << endl << "Cantitati: ";
		if (prod.cantitati != nullptr)
		{
			delete[] prod.cantitati;
			prod.cantitati = nullptr;
		}

		prod.cantitati = new float[prod.nrIngrediente];
		for (int i = 0; i < prod.nrIngrediente; i++)
		{
			cout << endl << "Cantitatea[" << i << "]: ";
			in >> prod.cantitati[i];
		}

	}

	//postincrementare
	ProdusAlimentar operator++(int) //pun asta ca nu pot avea 2 metode identice, fac o diferentiere, sa stie compilatoru
	{
		//obiectul din stanga nu se modifica, cel din dreapta da
		ProdusAlimentar copie = *this; //copia ar fi pa, iar this ar fi pizza, in main
		this->pret++;

		return copie;
	}

	//preincredementare
	ProdusAlimentar operator++()
	{
		this->pret++;
		return *this; //nu mi mai trebuie copie, ambele se modifica
	}

	//cast explicit
	explicit operator int()
	{
		return this->nrIngrediente;
	}

	//cast explicit->conversie din tipul clasei in tipul string
	explicit operator string ()
	{
		return string("pizza");
	}
};

int ProdusAlimentar::nrProduseAlimentare = 0;

void main() {
	ProdusAlimentar pizza;
	//pizza.pret = 30;

	pizza.afisareProdusAlimentar();
	float* cantitati = new float[3] {10.5, 15.5, 20.7};
	ProdusAlimentar* sushi = new ProdusAlimentar("sushi", 100, 3, cantitati, BIO);

	sushi->afisareProdusAlimentar();

	if (!pizza)
	{
		cout << endl << "Pretul este mai mare decat 0!";
	}
	else
		cout << endl << "Pretul este mai mic sau egal cu 0!";

	//Exemplificare >=
	cout << endl << endl;
	if ((*sushi) >= 3)
	{
		cout << "Produsul are minim 3 ingrediente";
	}
	else
		cout << "Produsul are sub 3 ingrediente";

	cout << endl << endl << "Media cantitatilor produsului este de " << (*sushi)(3);
	cout << endl << endl;

	//Exemplificare <=
	if (pizza <= 50)
		cout << "Aceast produs costa pana in 50 de lei";
	else
		cout << "Acest produs este mai scump de 50 de lei!";

	//Dublare cantitati din obiectul sushi, folosind operatorul index, transmis prin referinta, deoarece vreau sa fac modificari
	//daca as face float operator[](int index) si fac ce e mai jos imi iau eroare
	for(int i=0;i<3;i++)
		cout << endl << "Cantitatile dublate sunt: "<<(*sushi)[i] * 2 << " ";

	
	//cin >> pizza;
	//cout << pizza;
	//IN momentul in care in stanga operatorului nu avem tipul clasei definite

	//pizza are pretul 0
	ProdusAlimentar pa = pizza++; //pa ia pretul 0
	//pizza are pretul 1
	ProdusAlimentar pa2 = ++pizza;
	//pizza are pretul 2;
	//pa are pretul 0;
	//pa2 are pretul 2;
	//se afiseaza nr de ingrediente pt pa2


	cout << pa;
	cout << pa2;

	cout << (int)pa2;

	cout << (int)(pizza);

	cout << endl<<endl<<string(pizza);
	delete sushi;

	//de implementat: >,<,<=,>=,la index modificare, de facut medie etc., la explicit sa transform din obiect in tip de date
}