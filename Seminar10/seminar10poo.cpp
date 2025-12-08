#define _CRT_SECURE_NO_WARNINGS

#include <iostream>

#include <string>
#include <fstream> //pentru FISIERE

using namespace std;

class Banca
{
private:
	string denumire = "Necunoscut";
	char* locatie = nullptr;
	int nrAngajati = 0;
	bool areProfit = true;

public:
	Banca()
	{

	}
	Banca(string denumire, const char* locatie, int nrAngajati, bool areProfit)
	{
		this->areProfit = areProfit;
		this->denumire = denumire;
		this->nrAngajati = nrAngajati;
		this->locatie = new char[strlen(locatie) + 1];
		strcpy(this->locatie, locatie);
	}

	~Banca()
	{
		if (this->locatie != nullptr)
		{
			delete[] this->locatie;
			this->locatie = nullptr;
		}
	}

	friend void operator<<(ostream& out, Banca b)
	{
		out << endl << "Nr angajati: " << b.nrAngajati;
		out << endl << "Denumire: " << b.denumire;
		out << endl << (b.areProfit ? "Are profit" : "Nu are profit");
		//operator ternar-conditie ? scenariu pozitiv : ramura else

		if (b.locatie != nullptr)
		{
			out <<endl<< "Locatie: " << b.locatie;
		}
		else
			out << "Locatie default";

	}

	friend void operator<<(fstream& outFile, Banca b)
	{
		outFile << b.nrAngajati <<endl;
		outFile << b.denumire<<endl;
		outFile << b.areProfit<<endl;
		outFile << b.locatie << endl;
		//operator ternar-conditie ? scenariu pozitiv : ramura else

	}

	friend void operator>>(ifstream& inFile, Banca& b)
	{
		inFile >> b.nrAngajati;
		inFile >> b.denumire;
		inFile >> b.areProfit;

		if (b.locatie != nullptr)
		{
			delete[] b.locatie;
			b.locatie = nullptr;
		}

		char buffer[100];
		inFile >> buffer;

		b.locatie = new char[strlen(buffer) + 1];
		strcpy(b.locatie, buffer);
		
	}

};


void main()
{
	Banca BCR("BCR", "Piata Romana", 15, true);

	//Salvarea in fisier
	fstream fileStream("Banca.txt", ios::out);
	fileStream << BCR;
	fileStream.close();

	//cout << BCR;

	Banca BCRCopie;
	cout << BCRCopie;
	ifstream inputFileStream("Banca.txt", ios::in);
	inputFileStream >> BCRCopie; 
	inputFileStream.close();

	cout << BCRCopie;

}