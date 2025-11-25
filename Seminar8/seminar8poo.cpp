//Mostenire si Abstractizare
//Mostenire->Clasa de Baza->Clasa Copil
//Clasa copil mosteneste tot ce are clasa parinte

#include <iostream>
#include <string>

using namespace std;

class ExceptieCustom :public exception //sintaxa pt a mosteni atributele si metodele unei alte clase exception->clasa de baza, iar ExceptieCustom e clasa copil, mostenita (derivata)
{
public:
	ExceptieCustom(const char* mesaj) :exception(mesaj) {}
};

class Produs
{
private:
	const int id;
	string denumire;
	float pret;
public:
	static const float PRET_MINIM;
	Produs() :id(0), denumire("Laptop"), pret(5000)
	{

	}

	Produs(int idP, string denumireP, float pretP) : id(idP), denumire(denumireP), pret(pretP)
	{
		if (pret < PRET_MINIM)
		{
			throw ExceptieCustom("Pretul este prea mic!");
		}
	}

	~Produs()
	{

	}

	virtual void afisare()
	{
		cout << endl << "Id: " << this->id;
		cout << endl << "Denumire: " << this->denumire;
		cout << endl << "Pret: " << this->pret;

	}
	//Suprascrierea metodelor acelorasi metode in clasa copil

	//Exemplu->Abstractizare
	virtual float getProcentReducere() = 0; //o clasa abstracata->clasa Produs este o clasa abstracta
	//Clasele abstracte nu pot fi initializate
};

const float Produs::PRET_MINIM = 1;

//ce diferenta as putea avea intr-o clasa produs si o clasa produsredus? atribute in plus  (ex: procent reducere)
class ProdusRedus :public Produs
{
private:
	float procentReducere;

public:
	//are 4 atribute aceasta clasa->mosteneste atributele clasei Produs+atributele noi (ex: intrebare grila)
	ProdusRedus() :Produs(), procentReducere(10) //->initializarea celor 3 atribute din din clasa Produs
	{
	}

	ProdusRedus(int id, string denumire, float pret, float procentReducere) :Produs(id, denumire, pret), procentReducere(procentReducere)
	{
	}

	void afisare()
	{
		cout << endl;
		this->Produs::afisare(); //afisarea din clasa parinte
		cout << endl << "Procent reducere: " << this->procentReducere;
	}

	float getProcentReducere()
	{
		return this->procentReducere; //implementam si aici asta deoarece as avea eroare in main la new ProdusRedus
	}
};


class MathInterface
{
public:
	virtual int adunare(int a, int b) = 0;
	virtual int scadere(int a, int b) = 0;
	virtual int inmultire(int a, int b) = 0;
	virtual int impartire(int a, int b) = 0;
};

//IMPLEMENTARE: MathInterface

class MathOperation : public MathInterface
{
public:
	int adunare(int a, int b)
	{
		return a + b;
	}
	int scadere(int a, int b)
	{
		return a - b;
	}
	int inmultire(int a, int b)
	{
		return a * b;
	}
	int impartire(int a, int b)
	{
		if (b != 0)
			return a / b;
		else
			throw ExceptieCustom("Din pacate nu putem avea impartire la 0!");
	}
};

void main()
{
	//try
	//{
	// Produs frigider(1, "Frigider", 0);
	//}
	//catch (ExceptieCustom e)
	//{
	// cout << endl<< e.what(); //e.what->mesajul pe care l am afisat acolo in throw
	//}

	//Produs frigider(1, "Frigider", 5000);
	//frigider.afisare();

	ProdusRedus laptop(2, "Lapotp", 6000, 10);
	laptop.afisare();

	Produs* vectorProduse[3]; //pointeri la obiecte. nu e vector alocat dinamic

	vectorProduse[0] = new ProdusRedus(1, "Paine", 2, 10); //daca nu bag virtual imi afiseaza obiectele din clasa de baza doar
	vectorProduse[1] = new ProdusRedus(2, "Peste", 15, 8);
	vectorProduse[2] = new ProdusRedus(3, "Portocale", 10, 12);

	for (int i = 0; i < 3; i++)
	{
		vectorProduse[i]->afisare(); //aici apeleaza metoda afisare din clasa ProdusRedus
		delete vectorProduse[i];
	}
	//nu vedem procentul! trebuie sa puntem virtual la void afisare in clasa parinte. In functie de VIRTUAL imi afiseaza fie din clasa de baza, fie din cea copil
	//metodele VIRTUALE sunt un alt mod de a exemplifica POLIMORFISMUL


	MathInterface* operation = new MathOperation();
	cout << endl << operation->adunare(1, 2);
	cout << endl << operation->scadere(10, 7);
	cout << endl << operation->inmultire(5, 6);
	cout << endl << operation->impartire(20, 10);

	try
	{
		operation->impartire(5, 0);
	}
	catch (ExceptieCustom e)
	{
		cout << endl << e.what();
	}
}

//tema->de definit atat metode cat si atribute in zona protected, sa vedem daca le putem folosi
//  ->de definit o interfata

//Abstractizare
//O clasa abstracta este o clasa ce are cel putin o metoda virtuala pura
//Clasa care are doar metode virtuale pure se numeste interfata