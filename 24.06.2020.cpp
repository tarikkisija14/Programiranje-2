#include <iostream>
#include <vector>
#include <mutex>
#include <regex>
using namespace std;



const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO RE\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
"4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORISTENI U TESTNOM CODE-U,\n"
"\tOSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE\n"
"\tPOMOCNE FUNKCIJE MOZETE IMENOVATI I DODAVATI PO ZELJI.\n"
"5. IZUZETAK BACITE SAMO U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.\n"
"6. FUNKCIJE KOJE NE IMPLEMENTIRATE TREBAJU BITI OBRISANE!\n"
"7. RJESENJA ZADATKA POSTAVITE NA FTP SERVER U ODGOVARAJUCI FOLDER!\n"
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum eRazred { PRVI = 1, DRUGI, TRECI, CETVRTI };

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    if (dealociraj)
        delete[]sadrzaj;
    return temp;
}
template<class T1, class T2>
class Kolekcija {
    T1* _elementi1;
    T2* _elementi2;
    int _trenutno;
    bool _omoguciDupliranje;
public:
    Kolekcija(bool omoguciDupliranje = true) {
        _elementi1 = nullptr;
        _elementi2 = nullptr;
        _trenutno = 0;
        _omoguciDupliranje = omoguciDupliranje;
    }
    Kolekcija(const Kolekcija& obj) {
        _trenutno = obj._trenutno;
        _omoguciDupliranje = obj._omoguciDupliranje;
        _elementi1 = new T1[_trenutno];
        _elementi2 = new T2[_trenutno];
        for (size_t i = 0; i < _trenutno; i++)
        {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }
   }
    Kolekcija& operator=(const Kolekcija& obj) {
        if (this != &obj) {

            delete[]_elementi1; _elementi1 = nullptr;
            delete[]_elementi2; _elementi2 = nullptr;
            _trenutno = obj._trenutno;
            _omoguciDupliranje = obj._omoguciDupliranje;
            _elementi1 = new T1[_trenutno];
            _elementi2 = new T2[_trenutno];
            for (size_t i = 0; i < _trenutno; i++)
            {
                _elementi1[i] = obj._elementi1[i];
                _elementi2[i] = obj._elementi2[i];
            }
        }
        return *this;
    }
    
    void AddElement(T1 el1, T2 el2) {
        if (!_omoguciDupliranje) {
            for (size_t i = 0; i < _trenutno; i++)
            {
                if (_elementi1[i] == el1 && _elementi2[i] == el2)
                    throw exception("nemoguce dupliranje");
            }
        }

        T1* temp1 = _elementi1;
        T2* temp2 = _elementi2;

        _elementi1 = new T1[_trenutno + 1];
        _elementi2 = new T2[_trenutno + 1];

        for (size_t i = 0; i < _trenutno; i++)
        {
            _elementi1[i] = temp1[i];
            _elementi2[i] = temp2[i];
        }
        _elementi1[_trenutno] = el1;
        _elementi2[_trenutno] = el2;
        _trenutno++;
        delete[]temp1;
        delete[]temp2;

    }
    
    Kolekcija operator()(int from, int to) {
        if (from<0 || to>_trenutno || from > to)
            throw exception("izvan opsega");

        Kolekcija op;
        for (size_t i = from; i <=to ; i++)
        {
            op.AddElement(_elementi1[i], _elementi2[i]);
        }
        return op;
    }
    
    ~Kolekcija() {
        delete[]_elementi1; _elementi1 = nullptr;
        delete[]_elementi2; _elementi2 = nullptr;
    }
    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno()const { return _trenutno; }
    friend ostream& operator<< (ostream& COUT, const Kolekcija& obj) {
        for (size_t i = 0; i < obj._trenutno; i++)
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

    int getDays()const {
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
    friend int operator-(const Datum& d1, const Datum& d2) {
        return abs(d1.getDays() - d2.getDays());
    }
    friend bool operator>(const Datum& d1, const Datum& d2) {
        return d1.getDays() > d2.getDays();
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


class Predmet {
    char* _naziv;
    //int se odnosi na ocjenu u opsegu od 1 – 5, a datum na momenat postizanja ocjene
    Kolekcija<int, Datum> _ocjene;
public:
    Predmet(const char* naziv = "", int ocjena = 0, Datum datum = Datum()) {
        _naziv = GetNizKaraktera(naziv);
        if (ocjena > 0)
            _ocjene.AddElement(ocjena, datum);
    }
    Predmet(const Predmet& obj) {
        _naziv = GetNizKaraktera(obj._naziv);
        _ocjene = obj._ocjene;
    }
    Predmet& operator=(const Predmet& obj) {
        if (this != &obj) {
            delete[] _naziv; _naziv = nullptr;
            _naziv = GetNizKaraktera(obj._naziv);
            _ocjene = obj._ocjene;
        }
        return *this;
    }

    float GetProsjekPredmet()const {
        float sum = 0.0f;
        if (_ocjene.getTrenutno() == 0)
            return 0;
        for (size_t i = 0; i < _ocjene.getTrenutno(); i++)
        {
            sum += _ocjene.getElement1(i);
        }
        return sum / _ocjene.getTrenutno();
    }

    friend bool operator==(const Predmet& p1, const Predmet& p2) {
        if (strcmp(p1._naziv, p2._naziv) != 0)
            return false;
        if (p1._ocjene.getTrenutno() != p2._ocjene.getTrenutno())
            return false;
        for (size_t i = 0; i < p1._ocjene.getTrenutno(); i++)
        {
            if (p1._ocjene.getElement1(i) != p2._ocjene.getElement1(i) ||
                p1._ocjene.getElement2(i) != p2._ocjene.getElement2(i))
                return false;
        }
        return true;
    }
    friend bool operator!=(const Predmet& p1, const Predmet& p2) {
        return !(p1 == p2);
    }

    ~Predmet() {
        delete[] _naziv; _naziv = nullptr;
    }
    void AddOcjena(int ocjena, Datum datum) {
        _ocjene.AddElement(ocjena, datum);
    }
    char* GetNaziv() { return _naziv; }
    Kolekcija<int, Datum>& GetOcjene() { return _ocjene; }
    
    friend ostream& operator<<(ostream& COUT, const Predmet& obj) {
        COUT << "naziv: " << obj._naziv << endl;
        COUT << "Ocjene: " << endl;
        for (size_t i = 0; i < obj._ocjene.getTrenutno(); i++)
        {
            COUT << obj._ocjene.getElement1(i) << "-->" << obj._ocjene.getElement2(i) << endl;
        }
        COUT << "prosjek: " << obj.GetProsjekPredmet() << endl;
        return COUT;
    }


    float ProsjekDana() {
        if (_ocjene.getTrenutno() == 0)
            return 0;
        float sum = 0.0f;
        for (size_t i = 0; i < _ocjene.getTrenutno()-1; i++)
        {
            sum += _ocjene.getElement1(i) - _ocjene.getElement1(i + 1);
        }
        return sum / _ocjene.getTrenutno();
    }


};
class Uspjeh {
    eRazred _razred;
    //string se odnosi na napomenu o polozenom predmetu
    Kolekcija<Predmet, string>* _polozeniPredmeti;
public:
    Uspjeh(eRazred razred = PRVI) {
        _razred = razred;
        _polozeniPredmeti = new Kolekcija<Predmet, string>();
    }
    Uspjeh(const Uspjeh& obj) {
        _razred = obj._razred;
        _polozeniPredmeti = new Kolekcija<Predmet, string>(*obj._polozeniPredmeti);
    }
    Uspjeh& operator=(const Uspjeh& obj) {
        if (this != &obj) {
            delete _polozeniPredmeti; _polozeniPredmeti = nullptr;
            _razred = obj._razred;
            _polozeniPredmeti = new Kolekcija<Predmet, string>(*obj._polozeniPredmeti);
        }
        return *this;
    }
    
    friend bool operator==(const Uspjeh& u1, const Uspjeh& u2) {
        if (u1._razred != u2._razred)
            return false;
        if (u1._polozeniPredmeti->getTrenutno() != u2._polozeniPredmeti->getTrenutno())
            return false;
        for (size_t i = 0; i < u1._polozeniPredmeti->getTrenutno(); i++)
        {
            if (u1._polozeniPredmeti->getElement1(i) != u2._polozeniPredmeti->getElement1(i) ||
                u1._polozeniPredmeti->getElement2(i) != u2._polozeniPredmeti->getElement2(i))
                return false;
        }
        return true;
    }
    friend bool operator!=(const Uspjeh& u1, const Uspjeh& u2) {
        return !(u1 == u2);
    }



    ~Uspjeh() { delete _polozeniPredmeti; _polozeniPredmeti = nullptr; }

    float GetProsjekUspjeh()const {
        float sum = 0.0f;
        if (_polozeniPredmeti->getTrenutno() == 0)
            return 0;
        for (size_t i = 0; i < _polozeniPredmeti->getTrenutno(); i++)
        {
            sum += _polozeniPredmeti->getElement1(i).GetProsjekPredmet();
        }
        return sum / _polozeniPredmeti->getTrenutno();
    }


    Kolekcija<Predmet, string>* GetPredmeti() { return _polozeniPredmeti; }
    eRazred GetERazred() { return _razred; }
    friend ostream& operator<< (ostream& COUT, const Uspjeh& obj) {
        COUT <<"razred"<< obj._razred << endl;
        COUT << "Polozeni predmetiu: " <<  endl;
        for (size_t i = 0; i < obj._polozeniPredmeti->getTrenutno(); i++)
        {
            COUT << obj._polozeniPredmeti->getElement1(i) << "--->" << obj._polozeniPredmeti->getElement2(i) << endl;
        }
        COUT << "prosjek: " << obj.GetProsjekUspjeh() << endl;
        return COUT;
    }
};
/*
   email adresa mora biti u formatu text.text (sa ili bez tacke),
   dok domena moze biti fit.ba ili edu.fit.ba
   nakon institucije (fit ili edu.fit), osim drzavne (.ba), dozvoljene su domene .com i .org.

   za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
   validacija email adrese ce se vrsiti unutar konstruktora klase Kandidat, a u slucaju da nije validna
   postaviti je na defaultnu adresu: notSet@edu.fit.ba
   */
bool ValidirajEmail(string email) {
    return regex_match(email, regex("[a-zA-Z]+\\.?[a-zA-Z]+@(fit.ba|edu.fit.ba|fit.com|edu.fit.com|fit.org|edu.fit.org)"));
}

mutex lo;
class Kandidat {
    char* _imePrezime;
    string _emailAdresa;
    string _brojTelefona;
    vector<Uspjeh> _uspjeh;

    /*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
  FROM:info@fit.ba
  TO: emailKorisnika
  Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
  na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
  Pozdrav.
  FIT Team.
  ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu".
  slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
  */

    void PosaljiMail(eRazred razred) {
        lo.lock();
        cout << "FROM:info@fit.ba" << endl;
        cout << "TO: "<<GetEmail() << endl;
        cout << "Postovani " << GetImePrezime() << "  evidentirali ste uspjeh za " << razred << " razred.Dosadasnji uspjeh (prosjek)  na nivou " << razred << " rarzeda iznosi " << _uspjeh[razred].GetProsjekUspjeh()<<" a ukupni "<<GetUkupno() << endl;
        cout << "Pozdrav." << endl;
        cout << " FIT Team." << endl;
        lo.unlock();
    }

    void PosaljiSMS(eRazred razred) {
        lo.lock();
        cout << "Svaka cast za uspjeh"<< _uspjeh[razred].GetProsjekUspjeh()<< "u "<<razred<< " razredu" << endl;
        lo.unlock();
    }

public:
    Kandidat(const char* imePrezime, string emailAdresa, string brojTelefona) {
        _imePrezime = GetNizKaraktera(imePrezime);
        _emailAdresa = emailAdresa;
        _brojTelefona = brojTelefona;
        for (size_t i = 1; i <=4; i++)
        {
            _uspjeh.push_back(eRazred(i));
        }

    }
    Kandidat(const Kandidat& obj) {
        _imePrezime = GetNizKaraktera(obj._imePrezime);
        _emailAdresa = obj._emailAdresa;
        _brojTelefona = obj._brojTelefona;
        _uspjeh = obj._uspjeh;
    }
    Kandidat& operator=(const Kandidat& obj) {
        if (this != &obj) {
            delete[] _imePrezime; _imePrezime = nullptr;
            _imePrezime = GetNizKaraktera(obj._imePrezime);
            _emailAdresa = obj._emailAdresa;
            _brojTelefona = obj._brojTelefona;
            _uspjeh = obj._uspjeh;
        }
        return *this;
    }
    
    /*
  uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
  tom prilikom onemoguciti:
  - dodavanje istih (moraju biti identicne vrijednosti svih clanova) predmeta na nivou jednog razreda,
  - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
  - dodavanje vise od 5 predmeta na nivou jednog razreda
  razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
  Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
  */
    bool AddPredmet(eRazred razred, Predmet predmet, const char* napomena) {
        

        
        for (size_t i = 0; i < _uspjeh[razred].GetPredmeti()->getTrenutno(); i++) {
           
            if (_uspjeh[razred].GetPredmeti()->getElement1(i) == predmet) {
                
                return false;
            }
        }

        
        if (predmet.GetProsjekPredmet() < 2.5f) {
           
            return false;
        }

        
        size_t trenutno = _uspjeh[razred].GetPredmeti()->getTrenutno();
       
        if (trenutno >= 5) {
          
            return false;
        }

        
        _uspjeh[razred].GetPredmeti()->AddElement(predmet, napomena);
       
        thread tred(&Kandidat::PosaljiMail, *this, razred);
        tred.join();

        for (size_t i = 0; i < _uspjeh[razred].GetPredmeti()->getTrenutno(); i++)
        {
            if (_uspjeh[razred].GetProsjekUspjeh() > 4.5f) {
                thread tredi(&Kandidat::PosaljiSMS, this, razred);
                tredi.join();
            }
        }

        return true;
    }


    float GetUkupno()const {
        float sum = 0.0f;
        if (_uspjeh.size() == 0)
            return false;
        for (size_t i = 0; i < _uspjeh.size(); i++)
        {
            sum += _uspjeh[i].GetProsjekUspjeh();
        }
        return sum / _uspjeh.size();

    }

    Kolekcija<Predmet, float> operator()(Datum d1, Datum d2) {
        Kolekcija<Predmet, float> op;

        for (size_t i = 0; i < _uspjeh.size();i++)
        {
            for (size_t j = 0; j < _uspjeh[i].GetPredmeti()->getTrenutno(); j++)
            {
                for (size_t k = 0; k < _uspjeh[i].GetPredmeti()->getElement1(j).GetOcjene().getElement1(k); k++)
                {
                    Datum datum = _uspjeh[i].GetPredmeti()->getElement1(j).GetOcjene().getElement1(k);
                    if (datum > d1 && datum < d2) {
                        op.AddElement(_uspjeh[i].GetPredmeti()->getElement1(j), _uspjeh[i].GetPredmeti()->getElement1(j).ProsjekDana());
                    }
                }
            }
        }
        return op;
        
    }
    ~Kandidat() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    friend ostream& operator<< (ostream& COUT, Kandidat& obj) {
        COUT << obj._imePrezime << " " << obj._emailAdresa << " " << obj._brojTelefona << endl;
        for (size_t i = 0; i < obj._uspjeh.size(); i++)
            COUT << obj._uspjeh[i];
        return COUT;
    }
    vector<Uspjeh>& GetUspjeh() { return _uspjeh; }
    string GetEmail() { return _emailAdresa; }
    string GetBrojTelefona() { return _brojTelefona; }
    char* GetImePrezime() { return _imePrezime; }

};
const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Na sta se odnosi pojam reprezentacije tipa?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Na koji nacin se moze izbjeci pojavljivanje vise podobjekata bazne klase u slucaju visestrukog nasljedjivanja?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    Datum temp,
        datum19062019(19, 6, 2019),
        datum20062019(20, 6, 2019),
        datum30062019(30, 6, 2019),
        datum05072019(5, 7, 2019);

    int kolekcijaTestSize = 9;
    Kolekcija<int, int> kolekcija1(false);
    for (int i = 0; i <= kolekcijaTestSize; i++)
        kolekcija1.AddElement(i, i);

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 i T2), metoda AddElement baca izuzetak
        kolekcija1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    cout << kolekcija1 << crt;

    /*objekat kolekcija2 ce biti inicijalizovan elementima koji se u objektu kolekcija1 nalaze na lokacijama 1 - 4
    ukljucujuci i te lokacije. u konkretnom primjeru to ce biti parovi sa vrijednostima: 1 1 2 2 3 3 4 4*/
    Kolekcija<int, int> kolekcija2 = kolekcija1(1, 4);
    cout << kolekcija2 << crt;
    try {
        //primjeri u kojima opseg nije validan, te bi funkcija trebala baciti izuzetak
        Kolekcija<int, int> temp1 = kolekcija1(1, 14);//imamo 10 elemenata
        Kolekcija<int, int> temp2 = kolekcija1(-1, 8);//lokacija -1 ne postoji
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    //parametri: nazivPredmeta, prva ocjena, datum
    Predmet Matematika("Matematika", 5, datum19062019),
        Fizika("Fizika", 5, datum20062019),
        Hemija("Hemija", 2, datum30062019),
        Engleski("Engleski", 5, datum05072019);

    Matematika.AddOcjena(3, datum05072019);
    Matematika.AddOcjena(5, datum05072019);

    // ispisuje: naziv predmeta, ocjene (zajedno sa datumom polaganja) i prosjecnu ocjenu na predmetu
    // ukoliko predmet nema niti jednu ocjenu prosjecna treba biti 0
    cout << Matematika << endl;

    if (ValidirajEmail("text.text@edu.fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@edu.fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@fit.ba"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@fit.com"))
        cout << "Email validan" << crt;
    if (ValidirajEmail("texttext@edu.fit.org"))
        cout << "Email validan" << crt;

    /*
    email adresa mora biti u formatu text.text (sa ili bez tacke),
    dok domena moze biti fit.ba ili edu.fit.ba
    nakon institucije (fit ili edu.fit), osim drzavne (.ba), dozvoljene su domene .com i .org.

    za provjeru validnosti email adrese koristiti globalnu funkciju ValidirajEmail, a unutar nje regex metode.
    validacija email adrese ce se vrsiti unutar konstruktora klase Kandidat, a u slucaju da nije validna
    postaviti je na defaultnu adresu: notSet@edu.fit.ba
    */

    Kandidat jasmin("Jasmin Azemovic", "jasmin@fit.ba", "033 281 172");
    Kandidat adel("Adel Handzic", "adel@edu.fit.ba", "033 281 170");
    Kandidat emailNotValid("Ime Prezime", "korisnik@klix.ba", "033 281 170");

    /*
    uspjeh (tokom srednjoskolskog obrazovanja) se dodaje za svaki predmet na nivou razreda.
    tom prilikom onemoguciti:
    - dodavanje istih (moraju biti identicne vrijednosti svih clanova) predmeta na nivou jednog razreda,
    - dodavanje predmeta kod kojih je prosjecna ocjena manja od 2.5
    - dodavanje vise od 5 predmeta na nivou jednog razreda
    razredi (predmeti ili uspjeh) ne moraju biti dodavani sortiranim redoslijedom (npr. prvo se moze dodati uspjeh za II razred, pa onda za I razred i sl.).
    Funkcija vraca true ili false u zavisnosti od (ne)uspjesnost izvrsenja
    */
    if (jasmin.AddPredmet(DRUGI, Fizika, "Napomena 1"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(DRUGI, Hemija, "Napomena 2")) //Hemija ima nizi prosjek od 2.5
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Engleski, "Napomena 3"))
        cout << "Predmet uspjesno dodan!" << crt;
    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 4"))
        cout << "Predmet uspjesno dodan!" << crt;
    //Matematiku je vec dodana u prvom razredu

    if (jasmin.AddPredmet(PRVI, Matematika, "Napomena 5"))
        cout << "Predmet uspjesno dodan!" << crt;


    /*nakon evidentiranja uspjeha na bilo kojem predmetu kandidatu se salje email sa porukom:
    FROM:info@fit.ba
    TO: emailKorisnika
    Postovani ime i prezime, evidentirali ste uspjeh za X razred. Dosadasnji uspjeh (prosjek)
    na nivou X razreda iznosi Y, a ukupni uspjeh u toku skolovanja iznosi Z.
    Pozdrav.
    FIT Team.
    ukoliko je prosjek na nivou tog razreda veci od 4.5 kandidatu se salje SMS sa porukom: "Svaka cast za uspjeh 4.X u X razredu".
    slanje poruka i emailova implemenitrati koristeci zasebne thread-ove.
    */
    cout << jasmin << crt;

    //vraca kolekciju predmeta koji sadrze najmanje jednu ocjenu evidentiranu u periodu izmedju proslijedjenih datuma
    //float se odnosi na prosjecan broj dana izmedju ostvarenih ocjena na predmetu
    Kolekcija<Predmet, float> jasminUspjeh = jasmin(Datum(18, 06, 2019), Datum(21, 06, 2019));
    cout << jasminUspjeh << crt;

    //Uspjeh* uspjeh_Irazred = jasmin[PRVI];//vraca uspjeh kandidata ostvaren u prvom razredu
    //if (uspjeh_Irazred != nullptr)
    //    cout << *uspjeh_Irazred << crt;

    cin.get();
    system("pause>0");
}