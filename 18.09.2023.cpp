#include <iostream>
#include <vector>
#include <mutex>
#include <regex>
using namespace std;

const char* PORUKA = "\n-----------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. METODE KOJE NISU VOID, MORAJU VRACATI NEKU VRIJEDNOST!\n"
"4. ATRIBUTI, NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U, "
"OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE "
"POMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE (KAKO POZIV TAKO I DEFINICIJA)!\n"
"7. NA KRAJU ISPITA SVOJE RJESENJE KOPIRATE U .DOCX FAJL (IMENOVAN BROJEM INDEKSA)!\n"
"8. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"9. NEMOJTE POSTAVLJATI VISUAL STUDIO PROJEKTE, VEC SAMO .DOCX FAJL SA VASIM RJESENJEM!\n"
"10.SVE NEDOZVOLJENE RADNJE TOKOM ISPITA CE BITI SANKCIONISANE!\n"
"11. ZA POTREBE TESTIRANJA, U MAINU, BUDITE SLOBODNI DODATI TESTNIH PODATAKA (POZIVA FUNKCIJA) KOLIKO GOD SMATRATE DA JE POTREBNO!\n"
"12. ZA IZRADU ISPITNOG RJESENJA KORISTITI VISUAL STUDIO 2022!\n"
"13. RJESENJE TESTIRAJTE U OBA MODA (F5 i Ctrl+F5)\n"
"------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Predmet { UIT, PRI, PRII, PRIII, RSI, RSII };
const int MaxBrojRjesenja = 6;
const char* NIJE_VALIDNA = "<VRIJEDNOST_NIJE_VALIDNA>";

ostream& operator<<(ostream& COUT, Predmet& obj) {
    const char* niz[] = { "UIT", "PRI", "PRII", "PRIII", "RSI", "RSII" };
    COUT << niz[obj];
    return COUT;
}

char* GetNizKaraktera(const char* sadrzaj) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    return temp;
}

template<class T1, class T2, int max = 10>
class Kolekcija {
    T1* _elementi1[max];
    T2* _elementi2[max];
    int* _trenutno;
public:
    Kolekcija() {
        _trenutno = new int(0);
    }
    Kolekcija(const Kolekcija& obj) {
        _trenutno = new int(*obj._trenutno);
        for (size_t i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = new T1(*obj._elementi1[i]);
            _elementi2[i] = new T2(*obj._elementi2[i]);
        }
    }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj) {
            for (size_t i = 0; i < *_trenutno; i++) {
                delete _elementi1[i]; _elementi1[i] = nullptr;
                delete _elementi2[i]; _elementi2[i] = nullptr;
            }
            delete _trenutno; _trenutno = nullptr;
            _trenutno = new int(*obj._trenutno);
            for (size_t i = 0; i < *_trenutno; i++)
            {
                _elementi1[i] = new T1(*obj._elementi1[i]);
                _elementi2[i] = new T2(*obj._elementi2[i]);
            }
        }
        return *this;
    }
    

    void AddElement(T1 el1, T2 el2, int lokacija = -1) {
        if (lokacija == -1) {
            if (*_trenutno == max)
                throw exception("pun niz");
            _elementi1[*_trenutno] = new T1(el1);
            _elementi2[*_trenutno] = new T2(el2);
            (*_trenutno)++;
        }
        else {
            _elementi1[*_trenutno] = new T1;
            _elementi2[*_trenutno] = new T2;
            (*_trenutno)++;
            for (size_t i = *_trenutno-1; i >lokacija ; i--)
            {
                *_elementi1[i] = *_elementi1[i - 1];
                *_elementi2[i] = *_elementi2[i - 1];
            }
            *_elementi1[lokacija] = el1;
            *_elementi2[lokacija] = el2;
        }
    }

    Kolekcija* operator()(int from, int to) {
        Kolekcija* op = new Kolekcija();
        if (from < 0 || to >= *_trenutno)
            throw exception("izvan opsega");
        for (size_t i = from; i <= to; i++)
        {
            op->AddElement(*_elementi1[i], *_elementi2[i]);
        }return op;
    }

    T2& operator[](T1 el1) {
        for (size_t i = 0; i < *_trenutno; i++)
        {
            if (*_elementi1[i] == el1)
                return *_elementi2[i];
        }
        throw exception("nema");
    }

    ~Kolekcija() {
        for (size_t i = 0; i < *_trenutno; i++) {
            delete _elementi1[i]; _elementi1[i] = nullptr;
            delete _elementi2[i]; _elementi2[i] = nullptr;
        }
        delete _trenutno; _trenutno = nullptr;
    }
    T1 getElement1(int lokacija)const { return *_elementi1[lokacija]; }
    T2 getElement2(int lokacija)const { return *_elementi2[lokacija]; }
    int getTrenutno() const { return *_trenutno; }
    friend ostream& operator<< (ostream& COUT, Kolekcija& obj) {
        for (size_t i = 0; i < *obj._trenutno; i++)
            COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
        return COUT;
    }
};
class Datum {
    int* _dan, * _mjesec, * _godina;
public:
    Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
        _dan = new int(dan);
        _mjesec = new int(mjesec);
        _godina = new int(godina);
    }
    Datum(const Datum& obj) {
        _dan = new int(*obj._dan);
        _mjesec = new int(*obj._mjesec);
        _godina = new int(*obj._godina);
    }
    Datum& operator=(const Datum& obj) {
        if (this != &obj) {
            delete _dan; _dan = nullptr;
            delete _mjesec; _mjesec = nullptr;
            delete _godina; _godina = nullptr;
            _dan = new int(*obj._dan);
            _mjesec = new int(*obj._mjesec);
            _godina = new int(*obj._godina);
        }
        return *this;
    }

    int getDays() const {
        return *_godina * 365 + *_mjesec * 30 + *_dan;
    }

    friend bool operator==(const Datum& d1, const Datum& d2) {
        return d1.getDays() == d2.getDays();
    }

    friend bool operator!=(const Datum& d1, const Datum& d2) {
        return !(d1 == d2);
    }

    friend bool operator<(const Datum& d1, const Datum& d2) {
        return d1.getDays() < d2.getDays();
    }
    friend bool operator>(const Datum& d1, const Datum& d2) {
        return d1.getDays() > d2.getDays();
    }

    friend int operator-(const Datum& d1, const Datum& d2) {
        return abs(d1.getDays() - d2.getDays());
    }

    ~Datum() {
        delete _dan; _dan = nullptr;
        delete _mjesec; _mjesec = nullptr;
        delete _godina; _godina = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, const Datum& obj) {
        COUT << *obj._dan << "." << *obj._mjesec << "." << *obj._godina;
        return COUT;
    }
};

/*na odredjeno pitanje kandidat je duzan postaviti vise odgovora/rjesenja od kojih ce svako biti ocijenjeno*/
class Pitanje {
    char* _sadrzaj;
    //int se odnosi na ocjenu u opsegu  1 – 5, a Datum na datum kada je odgovor/rjesenje ocijenjeno
    Kolekcija<int, Datum*, MaxBrojRjesenja> _ocjeneRjesenja;
public:
    Pitanje(const char* sadrzaj = "") {
        _sadrzaj = GetNizKaraktera(sadrzaj);
        
    }
    Pitanje(const Pitanje& obj) {
        _sadrzaj = GetNizKaraktera(obj._sadrzaj);
        _ocjeneRjesenja = obj._ocjeneRjesenja;
    }
    Pitanje& operator=(const Pitanje& obj) {
        if (this != &obj) {
            delete[] _sadrzaj; _sadrzaj = nullptr;
            _sadrzaj = GetNizKaraktera(obj._sadrzaj);
            _ocjeneRjesenja = obj._ocjeneRjesenja;
        }
        return *this;
    }
    
    float ProsjekPitanje()const {
        float sum = 0.0f;
        if(_ocjeneRjesenja.getTrenutno() == 0)
            return 0;
        for (size_t i = 0; i < _ocjeneRjesenja.getTrenutno(); i++)
        {
            sum += _ocjeneRjesenja.getElement1(i);
        }
        return sum / _ocjeneRjesenja.getTrenutno();
    }

    friend bool operator==(const Pitanje& p1, const Pitanje& p2) {
        if (strcmp(p1._sadrzaj, p2._sadrzaj) != 0)
            return false;
        if(p1._ocjeneRjesenja.getTrenutno()!=p2._ocjeneRjesenja.getTrenutno())
            return false;
        for (size_t i = 0; i < p1._ocjeneRjesenja.getTrenutno(); i++)
        {
            if (p1._ocjeneRjesenja.getElement1(i) != p2._ocjeneRjesenja.getElement1(i) ||
                *p1._ocjeneRjesenja.getElement2(i) != *p2._ocjeneRjesenja.getElement2(i))
                return false;
        }
        return true;
    }
    friend bool operator!=(const Pitanje& p1, const Pitanje& p2) {
        return !(p1 == p2);
    }

    bool AddOcjena(Datum& d, int ocjena) {
        int trenutno = _ocjeneRjesenja.getTrenutno();
        if (trenutno > 0) {
            Datum zadnji = *_ocjeneRjesenja.getElement2(trenutno - 1);
            if (d < zadnji)
                return false;
            if (d - zadnji < 3)
                return false;
        }
        _ocjeneRjesenja.AddElement(ocjena, new Datum(d));
        return true;
    }

    ~Pitanje() {
        delete[] _sadrzaj; _sadrzaj = nullptr;
    }
    char* GetSadrzaj() { return _sadrzaj; }
    Kolekcija<int, Datum*, MaxBrojRjesenja> GetOcjene() const { return _ocjeneRjesenja; }


    friend ostream& operator<<(ostream& COUT, const Pitanje& obj) {
        COUT << "sadrzaj: " << obj._sadrzaj << endl;
        COUT << "pitanje i ocjena: " << endl;
        for (size_t i = 0; i < obj._ocjeneRjesenja.getTrenutno(); i++)
        {
            COUT << obj._ocjeneRjesenja.getElement1(i) << "-->" << *obj._ocjeneRjesenja.getElement2(i) << endl;
        }
        COUT << "Porjek; " << obj.ProsjekPitanje() << endl;
        return COUT;
    }

};

class Ispit {
    Predmet* _predmet;
    vector<Pitanje> _pitanjaOdgovori;
public:
    Ispit(Predmet predmet = UIT) {
        _predmet = new Predmet(predmet);
    }
    
    Ispit(const Ispit& obj) {
        _predmet = new Predmet(*obj._predmet);
        _pitanjaOdgovori = obj._pitanjaOdgovori;
    }
    Ispit& operator=(const Ispit& obj) {
        if (this != &obj) {
            delete _predmet; _predmet = nullptr;
            _predmet = new Predmet(*obj._predmet);
            _pitanjaOdgovori = obj._pitanjaOdgovori;
        }
        return *this;
   }

    float ProsjekIspit()const {
        float sum = 0.0f;
        if (_pitanjaOdgovori.size() == 0)
            return 0;
        for (size_t i = 0; i < _pitanjaOdgovori.size(); i++)
        {
            sum += _pitanjaOdgovori[i].ProsjekPitanje();
        }
        return sum / _pitanjaOdgovori.size();
    }
    
    friend bool operator==(const Ispit& i1, const Ispit& i2) {
        if (*i1._predmet != *i2._predmet)
            return false;
        if (i1._pitanjaOdgovori.size() != i2._pitanjaOdgovori.size())
            return false;
        for (size_t i = 0; i < i1._pitanjaOdgovori.size(); i++)
        {
            if (i1._pitanjaOdgovori[i] != i2._pitanjaOdgovori[i])return false;
        }
        return true;
    }
    friend bool operator!=(const Ispit& i1, const Ispit& i2) {
        return !(i1 == i2);
    }


    ~Ispit() {
        delete _predmet; _predmet = nullptr;
    }
    vector<Pitanje>& GetPitanjaOdgovore() { return _pitanjaOdgovori; }
    Predmet GetPredmet() { return *_predmet; }
    friend ostream& operator<< (ostream& COUT, const Ispit& obj) {
        COUT << *obj._predmet << endl;
        for (size_t i = 0; i < obj._pitanjaOdgovori.size(); i++)
            COUT << obj._pitanjaOdgovori[i];
        return COUT;
    }

};
///*
    //za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
    //-   najmanje 7 znakova
    //-   velika i mala slova
    //-   najmanje jedan broj
    //-   najmanje jedan specijalni znak

    //za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    //validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    //postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    //*/


bool ValidirajLozinku(string lozinka) {
    return regex_search(lozinka, regex("(?=.{7,})(?=.*[A-Z]{1,})(?=.*[a-z]{1,})(?=.*[0-9]{1,})(?=.*\\W{1,})"));
}
class Korisnik {
protected:
    char* _imePrezime;
    string _emailAdresa;
    string _lozinka;
    bool _aktivan;
public:
    Korisnik(const char* imePrezime, string emailAdresa, string lozinka)
    {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _lozinka = ValidirajLozinku(lozinka) ? lozinka : NIJE_VALIDNA;
        _aktivan = true;
    }
    Korisnik(const Korisnik& obj) {
        _imePrezime = GetNizKaraktera(obj._imePrezime);
        _emailAdresa = obj._emailAdresa;
        _lozinka = obj._lozinka;
        _aktivan = obj._aktivan;
   }
    Korisnik& operator=(const Korisnik& obj) {
        if (this != &obj) {
            delete[] _imePrezime; _imePrezime = nullptr;
            _imePrezime = GetNizKaraktera(obj._imePrezime);
            _emailAdresa = obj._emailAdresa;
            _lozinka = obj._lozinka;
            _aktivan = obj._aktivan;
        }
        return *this;
    }
    
    


    virtual ~Korisnik() { delete[] _imePrezime; _imePrezime = nullptr; }
    string GetEmail() { return _emailAdresa; }
    string GetLozinka() { return _lozinka; }
    char* GetImePrezime() { return _imePrezime; }
    bool GetAktivan() { return _aktivan; }
    void SetAktivan(bool aktivan) { _aktivan = aktivan; }
    virtual void Info() = 0;

    friend ostream& operator<<(ostream& COUT, const Korisnik& obj) {
        COUT << "ime i prezime: " << obj._imePrezime << endl;
        COUT << "email :" << obj._emailAdresa << endl;
        COUT << "lozinka: " << obj._lozinka << endl;
        if (obj._aktivan == true)
            COUT << "aktivan" << endl;
        else
            COUT << "nije aktivan" << endl;
        return COUT;
    }


};
mutex lo;
class Kandidat:public Korisnik {
    vector<Ispit*> _polozeniPredmeti;


    //FROM:info@kursevi.ba
   //TO: emailKorisnika

   //Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
   //za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
   //Pozdrav.

   //EDUTeam.

   //slanje email poruka implemenitrati koristeci zasebne thread-ove na nacin da se jedna poruka salje svako 2 sekunde.
   //*/


    void PosaljiMail(int ocjena,Pitanje pitanje) {
        
        if (!GetAktivan())
            return;
        lo.lock();
        cout << "FROM:info@kursevi.ba" << endl;
        cout << "TO: " << GetEmail() << endl;
        cout << "Postovani " << GetImePrezime() << " evidentirana vam je ocjena " << ocjena << "za odgovor na pitanje " << pitanje.GetSadrzaj() << endl;
        cout << "Dosadasnji uspjeh (prosjek ocjena) za pitanje " << pitanje.GetSadrzaj() << " iznosi" << pitanje.ProsjekPitanje() << endl;
        cout << "Ukupni uspjeh " << GetUkupno() << endl;
        cout << "Pozdrav" << endl;
        cout << "  //EDUTeam." << endl;
        lo.unlock();
    }


public:
    Kandidat(const char* imePrezime, string emailAdresa, string lozinka):Korisnik(imePrezime,emailAdresa,lozinka) {
        for (size_t i = 0; i <=MaxBrojRjesenja ; i++)
        {
            _polozeniPredmeti.push_back(new Ispit(Predmet(i)));
        }
    }
    Kandidat(const Kandidat& obj) :Korisnik(obj) {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
        {
            _polozeniPredmeti.push_back(new Ispit(*obj._polozeniPredmeti[i]));
        }
    }
    Kandidat& operator=(const Kandidat& obj) {
        if (this != &obj) {
            for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
                delete _polozeniPredmeti[i], _polozeniPredmeti[i] = nullptr;
            for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            {
                _polozeniPredmeti.push_back(new Ispit(*obj._polozeniPredmeti[i]));
            }
        }
        return *this;
    }
    

    bool AddPitanje(Predmet predmet, Pitanje pitanje) {
        for (size_t i = 0; i < _polozeniPredmeti[predmet]->GetPitanjaOdgovore().size(); i++)
        {
            if (_polozeniPredmeti[predmet]->GetPitanjaOdgovore()[i] == pitanje)
                return false;
        }
        if (predmet > 1) {
            if (_polozeniPredmeti[predmet - 1]->GetPitanjaOdgovore().size() < 3)
                return false;
            if (_polozeniPredmeti[predmet - 1]->ProsjekIspit() <= 3.5f)
                return false;
        }
        _polozeniPredmeti[predmet]->GetPitanjaOdgovore().push_back(pitanje);
        
        
        if (GetAktivan()) {
            for (size_t i = 0; i < pitanje.GetOcjene().getTrenutno(); i++)
            {
                thread tred(&Kandidat::PosaljiMail, this, pitanje.GetOcjene().getElement1(i), pitanje);
                tred.join();
            }
        }
        return true;
    }


    float GetUkupno()const {
        float sum = 0.0f;
        if (_polozeniPredmeti.size() == 0)
            return 0;
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
        {
            sum += _polozeniPredmeti[i]->ProsjekIspit();
        }
        return sum / _polozeniPredmeti.size();
    }

    ~Kandidat() {
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
            delete _polozeniPredmeti[i], _polozeniPredmeti[i] = nullptr;
        cout << crt << "KANDIDAT :: DESTRUKTOR" << crt;
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << (Korisnik&)obj << endl;
        for (size_t i = 0; i < obj._polozeniPredmeti.size(); i++) {
            if (obj._polozeniPredmeti[i]->GetPitanjaOdgovore().size() > 0) {
                COUT << *obj._polozeniPredmeti[i];
            }
            else {
                continue;
            }
        }
            
        return COUT;
    }
    vector<Ispit*>& GetPolozeniPredmeti() { return _polozeniPredmeti; }

    void Info() {
        cout << *this;
    }


    Kolekcija<Pitanje, float>operator()(Datum from, Datum to) {
        Kolekcija<Pitanje, float>op;
        for (size_t i = 0; i < _polozeniPredmeti.size(); i++)
        {
            for (size_t j = 0; j < _polozeniPredmeti[i]->GetPitanjaOdgovore().size(); j++)
            {
                for (size_t k = 0; k < _polozeniPredmeti[i]->GetPitanjaOdgovore()[j].GetOcjene().getTrenutno(); k++)
                {
                    Datum datum = *_polozeniPredmeti[i]->GetPitanjaOdgovore()[j].GetOcjene().getElement2(k);
                    if (datum < from && datum > to) {
                        for (size_t l = 0; l < _polozeniPredmeti[i]->GetPitanjaOdgovore()[j].GetOcjene().getTrenutno(); l++)
                        {
                            if (_polozeniPredmeti[i]->GetPitanjaOdgovore()[j].GetOcjene().getElement1(k) >= 0) {
                                op.AddElement(_polozeniPredmeti[i]->GetPitanjaOdgovore()[j], _polozeniPredmeti[i]->GetPitanjaOdgovore()[j].ProsjekPitanje());
                            }
                        }
                    }
                }
            }
        }
        return op;
    }



};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite STACK i HEAP dio memorije, za šta su namijenjeni, te na koji način se trebaju koristiti (prednosti i nedostaci pojedinih slučajeva).\n";
    return "Odgovor -> Stack je dio memorije namjenjen za lokalne vairjable i paramfetre funkcija stack framove i sl.Prednosgf rada nas tacku je sto je zas n odradjena alokacijamemorije  a mana kolicina memoijr koju stack posjeduje.Heap je memorija koja je u dijelovima koji se zovu pages i sliuzi nam za dinamkcio alociranje memorije koja bi iincae bila modza rpevise drazti na stacku a mana je sto smo mi odgovorni za alokaciju i dealkaciju memoirje";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Pojasnite preduslove za realizaciju polimorfizma, te koje su prednosti njegovog korištenja?\n";
    return "Da bi se ralizovaos polimorfizam potreba je makar q metoda da bude deklarisana sm kljucnom rijeci firtualDa iammo baznu klasu i derived klasu u baznij virudal void info a u derived ovid info override.";
}
void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum   datum19062023(19, 6, 2023),
        datum20062023(20, 6, 2023),
        datum30062023(30, 6, 2023),
        datum05072023(5, 7, 2023);

    int kolekcijaTestSize = 10;

    Kolekcija<int, int> kolekcija1;
    for (int i = 0; i < kolekcijaTestSize - 2; i++)
        kolekcija1.AddElement(i, i);

    cout << kolekcija1 << endl;

    try {
        /*metoda AddElement baca izuzetak u slucaju da se pokusa
        dodati vise od maksimalnog broja elemenata. Ako zelite da testirate
izuzetak, uklonite -2 iz prethodne for petlje*/
        kolekcija1.AddElement(11, 11);
    }
    catch (exception& err) {
        cout << crt << "Greska -> " << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    kolekcija1.AddElement(9, 9, 2);
    /*funkciji AddElement se, kao treci parametar, moze proslijediti i lokacija na koju se dodaju
    nove vrijednosti pri cemu treba zadrzati postojece vrijednosti pomjerene za jedno mjesto unaprijed
    u odnosu na definisanu lokaciju npr. ako unutar kolekcije postoje elementi
    0 0
    1 1
    2 2
    3 3
    nakon dodavanja vrijednosti 9 i 9 na lokaciju 1, sadrzaj kolekcije ce biti sljedeci
    0 0
    9 9
    1 1
    2 2
    3 3
    */

    cout << kolekcija1 << crt;

    Kolekcija<int, int> kolekcija2 = kolekcija1;
    cout << kolekcija1 << crt;

    //na osnovu vrijednosti T1 mijenja vrijednost T2. 
    kolekcija1[9] = 2;
    /* npr.ako unutar kolekcije postoje elementi:
    0 0
    9 9
    1 1
    2 2
    3 3
    nakon promjene vrijednosti sadrzaj kolekcije ce biti sljedeci
    0 0
    9 2
    1 1
    2 2
    3 3
    */

    Kolekcija<int, int>* kolekcija3 = kolekcija1(1, 3);
    /*kolekcija3 treba sadrzavati sve elemente koji se u kolekciji1 nalaze na lokacijama sa proslijedjenim indeksima,
    u ovom primjeru na lokacijama sa indeksom od 1 do 3, npr.ako unutar kolekcije1 postoje elementi:
       0 0
       9 9
       1 1
       2 2
       3 3
       sadrzaj kolekcije3 ce biti sljedeci
       9 9
       1 1
       2 2

       u slucaju da se zahtijevaju lokacije koje ne postoje u kolekciji, funkcija vraca samo one elemente koje postoje
       u zahtijevanom opsegu (bez bacanja izuzetaka).
   */
    cout << *kolekcija3 << endl;
    delete kolekcija3;

    Pitanje sortiranjeNiza("Navedite algoritme za sortiranje clanova niza?"),
        dinamickaMemorija("Navedite pristupe za upravljanje dinamickom memorijom?"),
        visenitnoProgramiranje("Na koji se sve nacin moze koristiti veci broj niti tokom izvrsenja programa?"),
        regex("Navedite par primjera regex validacije podataka?"),
        polimorfizam("Na koji nacin se realizuje polimorfizam?");

    /*svako pitanje moze imati vise ocjena tj. razlicita rjesenja/odgovori se mogu postaviti u vise navrata.
        -   razmak izmedju postavljanja dva rjesenja mora biti najmanje 3 dana
        -   nije dozvoljeno dodati ocjenu sa ranijim datumom u odnosu na vec evidentirane (bez obzira sto je stariji od 3 dana)
    */
    if (sortiranjeNiza.AddOcjena(datum19062023, 1))
        cout << "Ocjena evidentirana!" << endl;
    if (!sortiranjeNiza.AddOcjena(datum20062023, 5))
        cout << "Ocjena NIJE evidentirana!" << endl;
    if (sortiranjeNiza.AddOcjena(datum30062023, 5))
        cout << "Ocjena evidentirana!" << endl;

    if (polimorfizam.AddOcjena(datum19062023, 5))
        cout << "Ocjena evidentirana!" << endl;

    // ispisuje sadrzaj/tekst pitanja, ocjene (zajedno sa datumom) i prosjecnu ocjenu za sve odgovore/rjesenja
    // ukoliko pitanje nema niti jednu ocjenu prosjecna treba biti 0
    cout << sortiranjeNiza << endl;

    if (ValidirajLozinku("john4Do*e"))
        cout << "Lozinka :: OK :)" << crt;
    if (!ValidirajLozinku("john4Doe"))
        cout << "Lozinka :: Specijalni znak?" << crt;
    if (!ValidirajLozinku("jo*4Da"))
        cout << "Lozinka :: 7 znakova?" << crt;
    if (!ValidirajLozinku("4jo-hnoe"))
        cout << "Lozinka :: Veliko slovo?" << crt;
    if (ValidirajLozinku("@john2Doe"))
        cout << "Lozinka :: OK :)" << crt;

    ///*
    //za autentifikaciju svaki korisnik mora posjedovati lozinku koja sadrzi:
    //-   najmanje 7 znakova
    //-   velika i mala slova
    //-   najmanje jedan broj
    //-   najmanje jedan specijalni znak

    //za provjeru validnosti lozinke koristiti globalnu funkciju ValidirajLozinku, a unutar nje regex metode.
    //validacija lozinke se vrsi unutar konstruktora klase Korisnik, a u slucaju da nije validna
    //postaviti je na podrazumijevanu vrijednost: <VRIJEDNOST_NIJE_VALIDNA>
    //*/

    Korisnik* jasmin = new Kandidat("Jasmin Azemovic", "jasmin@kursevi.ba", "j@sm1N*");
    Korisnik* adel = new Kandidat("Adel Handzic", "adel@edu.kursevi.ba", "4Ade1*H");
    Korisnik* lozinkaNijeValidna = new Kandidat("John Doe", "john.doe@google.com", "johndoe");

    /*
    svi odgovori na nivou jednog predmeta (PRI, PRII... ) se evidentiraju unutar istog objekta tipa Ispit tj. pripadajuceg objekta tipa Pitanje,
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih atributa) odgovora na nivou jednog predmeta,
    - dodavanje odgovora za viši predmet ako prethodni predmet nema evidentirana najmanje 3 pitanja ili nema prosjecnu ocjenu svih pitanja vecu od 3.5
    (onemoguciti dodavanje pitanja za PRII ako ne postoje najmanje 3 pitanja za predmet PRI ili njihov prosjek nije veci od 3.5)
    funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */

    //doraditi klase da nacin da omoguce izvrsenje naredne linije koda
    Kandidat* jasminPolaznik = dynamic_cast<Kandidat*>(jasmin);

    if (jasminPolaznik != nullptr) {
        if (jasminPolaznik->AddPitanje(PRI, dinamickaMemorija))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati visenitnoProgramiranje jer ne postoje evidentirana 3 pitanja za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRII, visenitnoProgramiranje))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, visenitnoProgramiranje))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, regex))
            cout << "Pitanje uspjesno dodano!" << crt;
        if (jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje uspjesno dodano!" << crt;
        //ne treba dodati sortiranjeNiza jer je vec dodana za predmet PRI
        if (!jasminPolaznik->AddPitanje(PRI, sortiranjeNiza))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;

        //onemoguciti dodavanje pitanja korisnicima koji nisu aktivni
        jasmin->SetAktivan(false);
        if (!jasminPolaznik->AddPitanje(PRII, polimorfizam))
            cout << "Pitanje NIJE uspjesno dodano!" << crt;

        //ispisuje sve dostupne podatke o kandidatu
        cout << *jasminPolaznik << crt;
    }

    ///*nakon evidentiranja ocjene na bilo kojem odgovoru, AKTIVNOM kandidatu se salje email sa porukom:

    //FROM:info@kursevi.ba
    //TO: emailKorisnika

    //Postovani ime i prezime, evidentirana vam je ocjena X za odgovor na pitanje Y. Dosadasnji uspjeh (prosjek ocjena)
    //za pitanje Y iznosi F, a ukupni uspjeh (prosjek ocjena) na svim predmetima iznosi Z.
    //Pozdrav.

    //EDUTeam.

    //slanje email poruka implemenitrati koristeci zasebne thread-ove na nacin da se jedna poruka salje svako 2 sekunde.
    //*/

    ////osigurati da se u narednim linijama poziva i destruktor klase Kandidat

    Datum ocijenjenOD(19, 6, 2023), ocijenjenDO(1, 7, 2023);
    /*
    koristeci adekvatan operator osigurati pretragu pozitivno ocijenjeni odgovora u okviru pitanja u proslijedjenom vremenskom opsegu OD - DO.
    rezultat pretrage trebaju biti ona pitanja kojima je, u definisanom periodu, najmanje jedan odgovor ocijenjen pozitivno. drugi formalni
    argument tipa float predstavlja prosjecnu ocjenu odgovora na pronadjenom pitanju
    */
    Kolekcija<Pitanje, float> pretraga = (*jasminPolaznik)(ocijenjenOD, ocijenjenDO);
    cout << "U periodu od " << ocijenjenOD << " - " << ocijenjenDO << " ocijenjeno " << pretraga.getTrenutno() << " pitanja." << endl;
    for (size_t i = 0; i < pretraga.getTrenutno(); i++)
        cout << pretraga.getElement1(i) << endl << pretraga.getElement2(i) << crt;

    delete jasmin;
    delete adel;
    delete lozinkaNijeValidna;

    cin.get();
    system("pause>0");
}