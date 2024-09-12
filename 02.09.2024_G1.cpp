
#include <iostream>
#include <vector>
#include <mutex>
#include <regex>
using namespace std;
const char* PORUKA = "\n------------------------------------------------------------------------------ - \n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVADESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOGZADATKA\n"
"4. ATRIBUTI, NAZIVI METODA (SVE ISTO VAZI I ZA FUNKCIJE), TE BROJ ITIP PARAMETARA MORAJU BITI IDENTICNI "
"ONIMA KOJI SU KORISTENI U TESTNOM CODE - U, OSIM U SLUCAJU DA POSTOJIADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. "
"OSTALE POMOCNE METODE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U METODAMA U KOJIMA JE TO NAZNACENO.\n"
"6. SVE METODE POZVANE U MAIN-U ZADATKA TREBAJU POSTOJATI. UKOLIKONISTE ZADOVOLJNI IMPLEMENTACIJOM "
"POTREBNO JE DA IMPLEMENTIRATE BAREM TIJELO TIH METODA (METODA MOZEBITI PRAZNA), "
"A AKO METODA TREBA VRATITI NEKI PODATAK ONDA MOZETE VRATITI BILO KOJUTJ.ZELJENU VRIJEDNOST ZAHTIJEVANOG TIPA.!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRAJTE U .DOCX FAJL (IMENOVANBROJEM INDEKSA npr.IB150051.docx)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SAVASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11.ZA POTREBE TESTIRANJA, U MAIN-U, BUDITE SLOBODNI DODATI TESTNIHPODATAKA(POZIVA METODA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12.ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022 IRJESENJE TESTIRAJTE U OBA MODA(F5 i Ctrl + F5)!\n"
"13.NA KRAJU ISPITA PROVJERITE DA LI STE RJEŠENJE KOPIRALI U ADEKVATANFOLDER NA FTP SERVERU\n"
"-------------------------------------------------------------------------------\n";
const char* crt = "\n-------------------------------------------\n";
enum Drzava {ENGLESKA, SPANIJA, HOLANDIJA, FRANCUSKA,BOSNA_I_HERCEGOVINA};

ostream& operator<<(ostream& COUT, Drzava obj) {
	const char* niz[] = { "ENGLESKA", "SPANIJA", "HOLANDIJA", "FRANCUSKA", "BOSNA_I_HERCEGOVINA " };
	COUT << niz[obj];
	return COUT;
}

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
	if (sadrzaj == nullptr)return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char* temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	if (dealociraj)
		delete[]sadrzaj;
	return temp;
	
}
template<class T1, class T2, int max>
class Kolekcija {
	T1 _elementi1[max];
	T2 _elementi2[max];
	int* _trenutno;
public:
	Kolekcija() {
		_trenutno = new int(0);
	}
	Kolekcija(const Kolekcija& obj) {
		_trenutno = new int(*obj._trenutno);
		for (size_t i = 0; i < *_trenutno; i++)
		{
			_elementi1[i] = obj._elementi1[i];
			_elementi2[i] = obj._elementi2[i];
		}
	}
	Kolekcija& operator=(const Kolekcija& obj) {
		if (this != &obj) {
			
			delete _trenutno; _trenutno = nullptr;
			_trenutno = new int(*obj._trenutno);
			for (size_t i = 0; i < *_trenutno; i++)
			{
				_elementi1[i] = obj._elementi1[i];
				_elementi2[i] = obj._elementi2[i];
			}
		}
		return*this;
	}
	void AddElement(T1 el1, T2 el2) {
		if (*_trenutno == max)
			throw exception("izvan opsega");
		_elementi1[*_trenutno] = el1;
		_elementi2[*_trenutno] = el2;
		(*_trenutno)++;
	}

	Kolekcija InsertAt(T1 el1,T2 el2,int lokacija) {
		
		(*_trenutno)++;
		for (size_t i = *_trenutno - 1; i > lokacija; i--)
		{
			_elementi1[i] = _elementi1[i - 1];
			_elementi2[i] = _elementi2[i - 1];
		}
		_elementi1[lokacija] = el1;
		_elementi2[lokacija] = el2;
		return *this;
	}

	Kolekcija RemoveRange(int from, int to) {
		if (from<0 || to >= *_trenutno || from>to)
			throw exception("izvan opsega niza");
		Kolekcija op;
		int pozicija = to - from + 1;

		for (size_t i = from; i <= to; i++)
		{
			op.AddElement(_elementi1[i], _elementi2[i]);
		}
		for (size_t i = to + 1; i < *_trenutno; i++)
		{
			_elementi1[i - pozicija] = _elementi1[i];
			_elementi2[i - pozicija] = _elementi2[i];
		}
		for (size_t i = *_trenutno - pozicija; i < *_trenutno; i++)
		{
			_elementi1[i] = NULL;
			_elementi2[i] = NULL;
		}
		*_trenutno -= pozicija;
		return op;

	}

	
	~Kolekcija() {
		delete _trenutno; _trenutno = nullptr;
	}
	T1& getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2& getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() const { return *_trenutno; }
	friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
		for (size_t i = 0; i < *obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) <<
			endl;
		return COUT;
	}
};
class Vrijeme {
	int* _sat, * _minuta, * _sekunda;
public:
	Vrijeme(int sat = 10, int minuta = 0, int sekunda = 0) {
		_sat = new int(sat);
		_minuta = new int(minuta);
		_sekunda = new int(sekunda);
	}
	Vrijeme(const Vrijeme& obj) {
		_sat = new int(*obj._sat);
		_minuta = new int(*obj._minuta);
		_sekunda = new int(*obj._sekunda);
	}
	Vrijeme& operator=(const Vrijeme& obj) {
		if (this != &obj) {
			delete _sat; _sat = nullptr;
			delete _minuta; _minuta = nullptr;
			delete _sekunda; _sekunda = nullptr;
			_sat = new int(*obj._sat);
			_minuta = new int(*obj._minuta);
			_sekunda = new int(*obj._sekunda);
		}
		return *this;
	}

	int GetV()const {
		return (*_sat) * 3600 + (*_minuta) * 60 + *_sekunda;
	}

	friend bool operator==(const Vrijeme& v1, const Vrijeme& v2) {
		return v1.GetV() == v2.GetV();
	}

	friend bool operator!=(const Vrijeme& v1, const Vrijeme& v2) {
		return !(v1 == v2);
	}

	friend bool operator<(const Vrijeme& v1, const Vrijeme& v2) {
		return v1.GetV() < v2.GetV();
	}
	friend bool operator>(const Vrijeme& v1, const Vrijeme& v2) {
		return v1.GetV() > v2.GetV();
	}
	friend bool operator<=(const Vrijeme& v1, const Vrijeme& v2) {
		return v1.GetV() <= v2.GetV();
	}
	friend bool operator>=(const Vrijeme& v1, const Vrijeme& v2) {
		return v1.GetV() >= v2.GetV();
	}
	~Vrijeme() {
		delete _sat; _sat = nullptr;
		delete _minuta; _minuta = nullptr;
		delete _sekunda; _sekunda = nullptr;
	}
	friend ostream& operator<< (ostream& COUT, const Vrijeme& obj) {
		COUT << *obj._sat << ":" << *obj._minuta << ":" <<*obj._sekunda;
		return COUT;
	}
};
class Pogodak {
	Vrijeme* _vrijemePogotka;
	char* _napomena;
public:
	Pogodak(Vrijeme vrijeme, const char* napomena) {
		_napomena = GetNizKaraktera(napomena);
		_vrijemePogotka = new Vrijeme(vrijeme);
	}
	Pogodak(const Pogodak& obj) {
		_napomena = GetNizKaraktera(obj._napomena);
		_vrijemePogotka = new Vrijeme(*obj._vrijemePogotka);
	}
	Pogodak& operator=(const Pogodak& obj) {
		if (this != &obj) {
			delete[] _napomena; _napomena = nullptr;
			delete _vrijemePogotka; _vrijemePogotka = nullptr;
			_napomena = GetNizKaraktera(obj._napomena);
			_vrijemePogotka = new Vrijeme(*obj._vrijemePogotka);
		}
		return *this;
	}
	friend bool operator==(const Pogodak& p1, const Pogodak& p2) {
		if (*p1._vrijemePogotka != *p2._vrijemePogotka)
			return false;
		if (strcmp(p1._napomena, p2._napomena) != 0)
			return false;
		return true;
	}

	friend bool operator!=(const Pogodak& p1, const Pogodak& p2) {
		return !(p1 == p2);
	}


	~Pogodak() {
		delete[] _napomena; _napomena = nullptr;
		delete _vrijemePogotka; _vrijemePogotka = nullptr;
	}
	Vrijeme GetVrijemePogotka() { return *_vrijemePogotka; }
	char* GetNapomena() { return _napomena; }
	friend ostream& operator<< (ostream& COUT, const Pogodak& obj) {
		COUT << *obj._vrijemePogotka << " -> " << obj._napomena;
		return COUT;
		
	}
};

char* GenerisiID(const char* imePrezime, int broj) {
	
	
	const char* spacePtr = strchr(imePrezime, ' ');
	char firstLetter = toupper(imePrezime[0]);
	char lastLetter = spacePtr != nullptr ? toupper(spacePtr[1]) : '\0';

	
	char reversedNumber[5] = { 0 }; // Maksimalno 4 cifre + null terminator
	int index = 0;
	while (broj > 0 && index < 4) {
		reversedNumber[index++] = (broj % 10) + '0'; // Dodaj cifre u obrnuto
		broj /= 10;
	}
	reversedNumber[index] = '\0'; 

	
	char* id = new char[8]; // Maksimalno 7 karaktera + null terminator

	
	int numDigits = strlen(reversedNumber);
	if (numDigits == 1) {
		snprintf(id, 8, "%c000%c%s", firstLetter, lastLetter, reversedNumber);
	}
	else if (numDigits == 2) {
		snprintf(id, 8, "%c00%c%s", firstLetter, lastLetter, reversedNumber);
	}
	else if (numDigits == 3) {
		snprintf(id, 8, "%c0%c%s", firstLetter, lastLetter, reversedNumber);
	}
	else {
		// Ovo ne bi trebalo da se desi, ali samo za svaki slučaj
		snprintf(id, 8, "%c%c%s", firstLetter, lastLetter, reversedNumber);
	}

	return id;
}

int brojCifara(const string& str) {
	int brojac = 0;
	for (int i = 0; i < str.length(); ++i) {
		if (isdigit(str[i])) {
			brojac++;
		}
	}
	return brojac;
}

bool ValidirajID(string ID) {
	return regex_match(ID, regex("[A-Z][0]{0,4}[A-Z][0-9]{1,4}"))&& brojCifara(ID)==4;
}


class Igrac {
	static int _id;
	char* _ID; // za inicijalizaciju _ID-a iskoristiti funkcijuGenerisiID tj.atributa _imePrezime(inicijala imena i prezimena) i statickog clana _id
	char* _imePrezime;
	vector<Pogodak*> _pogoci;
public:
	Igrac(const char* imePrezime) {
		_imePrezime = GetNizKaraktera(imePrezime);
		_ID = GenerisiID(_imePrezime,_id++);
	}

	Igrac(const Igrac& obj) {
		_imePrezime = GetNizKaraktera(obj._imePrezime);
		_ID = GetNizKaraktera(obj._ID);
		for (size_t i = 0; i < _pogoci.size(); i++)
		{
			_pogoci.push_back(new Pogodak(*obj._pogoci[i]));
		}
	}
	Igrac& operator=(const Igrac& obj) {
		if (this != &obj) {
			delete[]_ID; _ID = nullptr;
			delete[]_imePrezime; _imePrezime = nullptr;
			for (size_t i = 0; i < _pogoci.size(); i++) {
				delete _pogoci[i];
				_pogoci[i] = nullptr;
			}
			_imePrezime = GetNizKaraktera(obj._imePrezime);
			_ID = GetNizKaraktera(obj._ID);
			for (size_t i = 0; i < _pogoci.size(); i++)
			{
				_pogoci.push_back(new Pogodak(*obj._pogoci[i]));
			}
		}
		return *this;
	}

	friend bool operator==(const Igrac& i1, const Igrac& i2) {
		return strcmp(i1._ID, i2._ID) == 0;
	}

	friend bool operator!=(const Igrac& i1, const Igrac& i2) {
		return !(i1 == i2);
	}
	bool AddGol(Pogodak pogodak) {
		for (size_t i = 0; i < _pogoci.size(); i++)
		{
			if (strcmp(_pogoci[i]->GetNapomena(), pogodak.GetNapomena()) == 0)
				return false;
		}
		_pogoci.push_back(new Pogodak(pogodak));
		return true;

	}


	~Igrac() {
		delete[]_ID; _ID = nullptr;
		delete[]_imePrezime; _imePrezime = nullptr;
		for (size_t i = 0; i < _pogoci.size(); i++) {
			delete _pogoci[i];
			_pogoci[i] = nullptr;
		}
	}
	char* GetImePrezime() { return _imePrezime; }
	char* GetID() { return _ID; }
	vector<Pogodak*>& GetPogoci() { return _pogoci; }
	friend ostream& operator<< (ostream& COUT, Igrac& obj) {
		COUT << *obj._ID << " -> " << obj._imePrezime;
		for (size_t i = 0; i < obj._pogoci.size(); i++)
			cout << *obj._pogoci[i] << endl;
		return COUT;
	}
};
int Igrac::_id = 1;


class Reprezentacija {
	Drzava _drzava;
	vector<Igrac> _igraci;
public:
	Reprezentacija(Drzava drzava = BOSNA_I_HERCEGOVINA) {
		_drzava = drzava;
	}

	Reprezentacija(const Reprezentacija& obj) {
		_drzava = obj._drzava;
		_igraci = obj._igraci;
	}
	Reprezentacija& operator=(const Reprezentacija& obj) {
		if (this != &obj) {
			_drzava = obj._drzava;
			_igraci = obj._igraci;
		}
		return *this;
	}
	friend bool operator==(Reprezentacija& r1, Reprezentacija& r2) {
		if (r1._drzava != r2._drzava)
			return false;
		if (r1._igraci.size() != r2._igraci.size())
			return false;
		for (size_t i = 0; i < r1._igraci.size(); i++)
		{
			if (r1._igraci[i] != r2._igraci[i])
				return false;
		}
		return true;
	}
	friend bool operator!=(Reprezentacija& r1, Reprezentacija& r2) {
		return !(r1 == r2);
	}

	vector<Igrac>GetStrijelci() {
		vector<Igrac>Ronaldo;
		for (size_t i = 0; i < _igraci.size(); i++)
		{
			for (size_t j = 0; j < _igraci[i].GetPogoci().size(); j++)
			{
				Ronaldo.push_back(_igraci[i]);
			}
		}return Ronaldo;
	}

	void AddIgrac(Igrac igrac) {
		for (size_t i = 0; i < _igraci.size(); i++)
		{
			if (strcmp(_igraci[i].GetID(), igrac.GetID()) == 0)
				throw exception("igrac vec dodan");
		}
		_igraci.push_back(igrac);
	}
	int GetBrojPogodaka() {
		int brojac = 0;
		for (int i = 0; i < _igraci.size(); i++)
		{
			brojac += _igraci[i].GetPogoci().size();
		}
		return brojac;
	}
	

	Drzava GetDrzava() { return _drzava; }
	vector<Igrac>& GetIgraci() { return _igraci; }

	friend ostream& operator<<(ostream& COUT, Reprezentacija& obj) {
		COUT << "drzava: " << obj._drzava << endl;
		COUT << "igraci: " << endl;
		for (size_t i = 0; i < obj._igraci.size(); i++)
		{
			COUT << obj._igraci[i] << endl;
		}
		return COUT;
	}

};




mutex lo;
class Prventstvo {
	Kolekcija<Reprezentacija, Reprezentacija, 20> _utakmice;

	void PosaljiMail(Pogodak pogodak, const char* pretraga) {
		lo.lock();
		cout << "TO: ";
		for (size_t i = 0; i < _utakmice.getTrenutno(); i++)
		{
			for (size_t j = 0; j < _utakmice.getElement1(i).GetIgraci().size(); j++)
			{
				cout << _utakmice.getElement1(i).GetIgraci()[j].GetID() << "@euro2024.com" << " , ";

			}
			for (size_t k = 0; k < _utakmice.getElement2(i).GetIgraci().size(); k++)
			{
				cout << _utakmice.getElement1(i).GetIgraci()[k].GetID() << "@euro2024.com";

			}
		}
		cout << endl;
		cout << "From: info@euro2024.com" << endl;
		cout << "Subject: Informacija" << endl;
		cout << "Postovani, " << endl;
		cout << "U " << pogodak.GetVrijemePogotka() << " sati,igrac " << pretraga << " je zabiljezio svoj " << pogodak.GetNapomena() << "na ovoj utakmici" << endl;
		cout << "Trenutni rezultat je : " << endl;
		for (size_t i = 0; i < _utakmice.getTrenutno(); i++)
		{
			cout << _utakmice.getElement1(i).GetDrzava() << " " << _utakmice.getElement1(i).GetBrojPogodaka() << " : " << _utakmice.getElement2(i).GetBrojPogodaka() << " " << _utakmice.getElement2(i).GetDrzava() << endl;
		}
		cout << "Puno srece u nastavku susreta." << endl;
		cout << "Neka bolji tim pobijedi." << endl;
		cout << crt;

		lo.unlock();
	}

public:
	Prventstvo() {}
	Prventstvo(const Prventstvo& obj) {
		_utakmice = obj._utakmice;
	}
	Prventstvo& operator=(const Prventstvo& obj) {
		if (this != &obj) {
			_utakmice = obj._utakmice;
		}
		return *this;
	}
	
	void AddUtakmicu(Reprezentacija r1, Reprezentacija r2) {
		for (size_t i = 0; i < _utakmice.getTrenutno(); i++)
		{
			if (_utakmice.getElement1(i) == r1 && _utakmice.getElement2(i) == r2 || _utakmice.getElement1(i) == r2 && _utakmice.getElement2(i) == r1)
				throw exception("utakmica vec odigrana");

		}
		_utakmice.AddElement(r1, r2);
	}
	
	bool AddPogodak(Drzava d1, Drzava d2, const char* pretraga, Pogodak pogodak) {
		for (size_t i = 0; i < _utakmice.getTrenutno(); i++)
		{
			for (size_t j = 0; j < _utakmice.getElement1(i).GetIgraci().size(); j++)
			{
				auto& igraci = _utakmice.getElement1(i).GetIgraci()[j];
				if (strcmp(igraci.GetID(), pretraga) == 0 || strcmp(igraci.GetImePrezime(), pretraga) == 0) {
					if (igraci.AddGol(pogodak)) {
						thread tred(&Prventstvo::PosaljiMail, this, pogodak, pretraga);
						tred.join();
						return true;
					}
					
				}
				
			}
		}
		for (size_t i = 0; i < _utakmice.getTrenutno(); i++)
		{
			for (size_t j = 0; j < _utakmice.getElement2(i).GetIgraci().size(); j++)
			{
				auto& igraci = _utakmice.getElement2(i).GetIgraci()[j];
				if (strcmp(igraci.GetID(), pretraga) == 0 || strcmp(igraci.GetImePrezime(), pretraga) == 0) {
					if (igraci.AddGol(pogodak)) {
						thread tred(&Prventstvo::PosaljiMail, this, pogodak, pretraga);
						tred.join();
						return true;
					}

				}
				
			}
		}
		return false;
	}

	friend ostream& operator<<(ostream& COUT, Prventstvo& obj) {

		COUT << crt;
		for (size_t i = 0; i < obj._utakmice.getTrenutno(); i++) {
			COUT << obj._utakmice.getElement1(i).GetDrzava() << " " << obj._utakmice.getElement1(i).GetBrojPogodaka() << " : " << obj._utakmice.getElement2(i).GetBrojPogodaka() << " " << obj._utakmice.getElement2(i).GetDrzava() << endl;
		}
		COUT << crt;

		COUT << "strijelci za tim BiH: " << endl;
		for (size_t i = 0; i < obj._utakmice.getTrenutno(); i++)
		{
			for (size_t j = 0; j < obj._utakmice.getElement1(i).GetStrijelci().size(); j++)
			{
				COUT << obj._utakmice.getElement1(i).GetStrijelci()[j].GetImePrezime() << endl;
			}
		}
		COUT << endl;
		COUT << "strijelci za tim ENG: " << endl;
		for (size_t i = 0; i < obj._utakmice.getTrenutno(); i++)
		{
			for (size_t j = 0; j < obj._utakmice.getElement2(i).GetStrijelci().size(); j++)
			{
				COUT << obj._utakmice.getElement2(i).GetStrijelci()[j].GetImePrezime() << endl;
			}
		}
		return COUT;
	}

	
	vector<Igrac*>operator()(int broj) {
		vector<Igrac*> op;
		for (size_t i = 0; i < _utakmice.getTrenutno(); i++) {
			auto& repka1 = _utakmice.getElement1(i);
			auto& repka2 = _utakmice.getElement2(i);

			for (size_t j = 0; j < repka1.GetIgraci().size(); j++) {
				if (repka1.GetIgraci()[j].GetPogoci().size() >= broj) {
					op.push_back(new Igrac(repka1.GetIgraci()[j]));
				}
			}
			for (size_t j = 0; j < repka2.GetIgraci().size(); j++) {
				if (repka2.GetIgraci()[j].GetPogoci().size() >= broj) {
					op.push_back(new Igrac(repka1.GetIgraci()[j]));
				}
			}

		}
		return op;
	}




	Kolekcija<Reprezentacija, Reprezentacija, 20>& GetUtakmice() {
		return _utakmice;
	}
};
const char* GetOdgovorNaPrvoPitanje() {
	cout << "Pitanje -> Pojasnite osnovne preduslove koji moraju biti ispunjeni da bi se realizovao polimorfizam(navesti kratki primjer) ? \n";
		return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

const char* GetOdgovorNaDrugoPitanje() {
	cout << "Pitanje -> Pojasnite razloge koristenja kljucnih rijeciabstract i ciste virtualne metode, te razlike izmedju njih ? \n";
		return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
void main() {
	cout << PORUKA;
	cin.get();
	cout << GetOdgovorNaPrvoPitanje() << endl;
	cin.get();
	cout << GetOdgovorNaDrugoPitanje() << endl;
	cin.get();
	/*
	Globalna funkcija GenerisiID vraca ID igraca na osnovu vrijednosti
   proslijedjenih parametara. Funkcija generise
	ID sa maksimalno 4 cifre, ne racunajuci inicijale tj. prva slova
   imena i prezimena.
	Podrazumijeva se da ce uvijek biti proslijedjene validne
   vrijednosti parametara. Ukoliko se proslijede
	mala pocetna slova imena ili prezimena, potrebno ih je
   konvertovati u velika.
	U okviru generisanog ID-a, proslijedjena cjelobrojna vrijednost
   treba biti u obrnutom redoslijedu cifara.
	*/
	cout << GenerisiID("Denis Music", 3) << endl;//treba vratitiD000M3
	cout << GenerisiID("Jasmin Azemovic", 14) << endl;//treba vratitiJ00A41
	cout << GenerisiID("Goran Skondric", 156) << endl;//treba vratitiG0S651
	cout << GenerisiID("emina junuz", 1798) << endl;//treba vratitiEJ8971

	//Za validaciju ID-a koristiti funkciju ValidirajID koja treba, koristeci regex, osigurati postivanje osnovnih pravila
	//vezanih za format koja su definisana u prethodnom dijelu zadatka.
	if (ValidirajID("D000M3"))
			cout << "ID VALIDAN" << endl;
	if (ValidirajID("J00A41"))
		cout << "ID VALIDAN" << endl;
	if (!ValidirajID("G00S651"))
		cout << "ID NIJE VALIDAN" << endl;
	if (!ValidirajID("Ej8971"))
		cout << "ID NIJE VALIDAN" << endl;
	int kolekcijaTestSize = 9;
	Kolekcija<int, int, 10> kolekcija1;
	for (int i = 0; i < kolekcijaTestSize; i++)
		kolekcija1.AddElement(i, i);//dodaje vrijednosti u kolekciju
	
		
	cout << kolekcija1 << crt;
	/* metoda InsertAt treba da doda vrijednosti prvog i drugog
   parametra na lokaciju koja je definisana trecim parametrom. Povratna
   vrijednost metode
	je objekat (pozivaoc metode, u konkretnom slucaju objekat
   kolekcija1) u okviru koga su, na definisanu lokaciju, dodati
   zahtijevani parametri.
	Nakon izvrsenja metode InsertAt, oba objekta, kolekcija1 i
   kolekcija2, bi trebali posjedovati sljedeci sadrzaj:
	10 10
	0 0
	1 1
	2 2
	* ....
	*/
	Kolekcija<int, int, 10> kolekcija2 = kolekcija1.InsertAt(10, 10,0);
	cout << kolekcija2 << crt;
	/*Metoda RemoveRange prihvata lokacija OD i DO, te u tom opsegu
   uklanja sve elemente iz kolekcije. U slucaju da zahtijevani opseg ne
   postoji u kolekciji
	metoda treba baciti izuzetak. Na kraju, metoda treba da vrati
   pokazivac na novi objekat tipa kolekcija koji sadrzi samo uklonjene
   elemente*/
	Kolekcija<int, int, 10> kolekcija3 = kolekcija1.RemoveRange(1, 3);
	cout << kolekcija3 << endl;
	cout << kolekcija1 << crt;
	/*kolekcija3 bi trebala sadrzavati sljedece elemente:
	0 0
	1 1
	2 2
	dok bi kolekcija1 trebala sadrzavati sljedece elemente:
	10 10
	3 3
	4 4
	......
	*/
	kolekcija1 = kolekcija3;
	cout << kolekcija1;
	Vrijeme
		prviPogodak201633(20, 16, 33),
		drugiPogodak202319(20, 23, 19),
		treciPogodak205108(20, 51, 8),
		cetvrtiPogodak210654(21, 6, 54);
	Igrac denis("Denis Music"), jasmin("Jasmin Azemovic"),
		goran("Goran Skondric"), adil("Adil Joldic");

	

	if (strcmp(denis.GetID(), "D000M1") == 0 && strcmp(jasmin.GetID(), "J000A2") == 0)
		cout << "ID se uspjesno generise!" << endl;
	Pogodak prviPogodak(prviPogodak201633, "podaci o prvom pogotku"),
		drugiPogodak(drugiPogodak202319, "podaci o drugom pogotku"),
		treciPogodak(treciPogodak205108, "podaci o trecem pogotku"),
		cetvrtiPogodak(cetvrtiPogodak210654, "podaci o cetvrtompogotku");
	Reprezentacija BIH(BOSNA_I_HERCEGOVINA), ENG(ENGLESKA);
	BIH.AddIgrac(denis);
	BIH.AddIgrac(jasmin);
	ENG.AddIgrac(goran);
	ENG.AddIgrac(adil);
	try
	{
		BIH.AddIgrac(denis);//onemoguciti dodavanje istih igraca -provjeravati ID
	}
	catch (exception& obj)
	{
		cout << obj.what();
	}
	cout << endl;
	Prventstvo euro2024;
	euro2024.AddUtakmicu(BIH, ENG);
	try
	{
		euro2024.AddUtakmicu(BIH, ENG);//onemoguciti ponovne susretedrzava tokom istog prvenstva
	}
	catch (exception& obj)
	{
		cout << obj.what();
	}
	cout << endl;
	////omoguciti dodavanje pogotka po ID-u ili imenu i prezimenu
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "D000M1",
		prviPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	//onemoguciti dodavanje istih pogodaka
	if (!euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Denis Music", prviPogodak))
		cout << "Pogodak NIJE uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "J000A2",drugiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Jasmin Azemovic", treciPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	if (euro2024.AddPogodak(BOSNA_I_HERCEGOVINA, ENGLESKA, "Goran Skondric", cetvrtiPogodak))
		cout << "Pogodak uspjesno dodat" << endl;
	////nakon svakog evidentiranog pogotka, svim igracima te utakmice(pod pretpostavkom da su validne email adrese sa ID - ovima igraca),
	//	
	////u zasebnom thread-u, poslati email. u razmaku od 2 sekunde, sa sljedecim sadrzajem :
	///*
	//To: D000M1@euro2024.com
	//From: info@euro2024.com
	//Subject: Informacija
	//Postovani,
	//U 20:35:16 sati igrac Jasmin Azemovic je zabiljezio svoj 1
 //  pogodak na ovoj utakmici.
	//Trenutni rezultat je:
	//BOSNA_I_HERCEGOVINA 2 : 0 ENGLESKA
	//Puno srece u nastavku susreta.
	//Neka bolji tim pobijedi.
	//*/
	////ispisuje detaljnije informacije o susretu, kako je navedeno u  narednom ispisu
		cout << euro2024;
	///*
	//-------------------------------------------
	//(3) BOSNA_I_HERCEGOVINA : ENGLESKA (1)
	//-------------------------------------------
	//Denis Music Goran Skondric
	//Jasmin Azemovic
	//Jasmin Azemovic
	//-------------------------------------------
	//*/
	//vraca sve igrace koji su na takmicenju postigli broj pogodaka koji je veci ili jednak proslijedjenoj vrijednosti
		cout << crt;
		
	vector<Igrac*> igraci = euro2024(2);
	for (size_t i = 0; i < igraci.size(); i++)
		cout << igraci[i]->GetImePrezime() << endl;
	
	
	
	cin.get();
	system("pause>0");
}
