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

	//daca nu am avea astribut static. ii dam 0 in loc de nrProduseAlimentar, apoi il dam ca parametru in constructor (int idP)-de ex iar apoi la fel :id(idP)
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

	//constructor de copiere
	ProdusAlimentar(const ProdusAlimentar& copie) :id(++nrProduseAlimentare) //ca sa avem acelasi id punem copie.nrProduseAlimentare
		//doar preluam date, nu modificam obiectul, de aceea const, &->referinta->copiem toate atributele lui/primim o copie
	{
		this->pret = copie.pret;
		this->denumire = copie.denumire;
		this->tip = copie.tip;
		this->nrIngrediente = copie.nrIngrediente;

		if (copie.cantitati != nullptr) //pointerul this reflecta adresa unui nou obiect, iar obiectul copie este unul deja existen in main
		{
			this->cantitati = new float[copie.nrIngrediente];
			for (int i = 0; i < copie.nrIngrediente; i++)
				this->cantitati[i] = copie.cantitati[i];
		}
		else

		{
			this->cantitati = nullptr;
		}

	}

	//implementam operatorul egal
	void operator=(const ProdusAlimentar& copie) //o diferenta:aici nu abordam constantele-nu le modificam/nu le initializam
	{
		this->denumire = copie.denumire;
		this->nrIngrediente = copie.nrIngrediente;
		this->pret = copie.pret;
		this->tip = copie.tip;

		if (this->cantitati != nullptr)
		{
			delete[] this->cantitati; //eliminam vectorul deja initializat pe alt constructor
			this->cantitati = nullptr;

		}

		if (copie.cantitati != nullptr)
		{
			this->cantitati = new float[copie.nrIngrediente];
			for (int i = 0; i < copie.nrIngrediente; i++)
				this->cantitati[i] = copie.cantitati[i];
		}
		else
		{
			this->cantitati = nullptr;
		}

		
	}

	//modificare pret pizza-POLIMORFISM
	void operator+=(float pretDeAdunat)
	{
		this->pret += pretDeAdunat;
	}

	bool operator>(const ProdusAlimentar pa)
	{
		return this->pret > pa.pret;
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

	//get si set pentru nrIngrediente
	int getNrIngrediente() {
		return this->nrIngrediente;
	}

	void setNrIngrediente(int nrIngredienteNou) {
		if (nrIngredienteNou > 0)
		{
			this->nrIngrediente = nrIngredienteNou;
		}
		else {
			//throw exception();
			//throw 404;
			throw "Valoare negativa";
		}
	}

	//get si set pentru pointeri
	float* getCantitati() {
		//return this->cantitati; - asa nu
		float* copieCantitati = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			copieCantitati[i] = this->cantitati[i];
		}

		return copieCantitati;
	}

	void setCantitati(float* cantitatiNoi, int nrIngredienteNou) {
		setNrIngrediente(nrIngredienteNou);

		if (this->cantitati != nullptr) {
			delete[] this->cantitati;
		}
		this->cantitati = new float[this->nrIngrediente];
		for (int i = 0; i < this->nrIngrediente; i++) {
			this->cantitati[i] = cantitatiNoi[i];
		}

		delete[] cantitatiNoi;
	}

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
	float* cantitati = new float[3] {100, 200, 300}; //nu i dadeam delete, deoarece aveam deep copy. daca il dezalocam iar in main, crapa
	ProdusAlimentar* sushi = new ProdusAlimentar("sushi", 100, 3, cantitati, BIO);

	sushi->afisareProdusAlimentar();

	//ProdusAlimentar produs = *sushi; //facem derefernetiere, pt a putea extrage valoare de la adresa
	ProdusAlimentar produs(*sushi);
	produs.afisareProdusAlimentar();

	pizza = *sushi;
	pizza.afisareProdusAlimentar();

	pizza += 7;

	pizza.afisareProdusAlimentar();
	//diferente: id (vom avea id-ul lui sushi+1)
	//          -vectorul de cantitati al obiectului produs fata de obiectu sushi se afla la alta adresa in heap

	if (produs > pizza)
		cout << endl << " Produsul sushi are pretul mai mare!";
	else
		cout << endl << " Produsul pizza are pretul mai mare!";


	delete sushi;

	//constructorul de copiere ne ajuta sa copeim informatiile dintr un obiect existent intr unul nou

	//La OPERATORUL EGAL copiem (proprietatile) tot intr-un obiect existent, la constructorul de copiere setez un obiect nou-DIFERENTA-dpdv teoretic
	//la constructor initalizez constantele, la operatorul EGAL nu le modific-dpdv al implementarii
}