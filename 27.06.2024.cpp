#include <iostream>
#include <mutex>
#include <regex>
#include <vector>
using namespace std;

const char* PORUKA = "\n-------------------------------------------------------------------------------\n"
"0. PROVJERITE DA LI PREUZETI ZADACI PRIPADAJU VASOJ GRUPI (G1/G2)\n"
"1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR\n"
"2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA CE BITI OZNACENO KAO TM\n"
"3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA\n"
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
"-------------------------------------------------------------------------------\n";

const char* crt = "\n-------------------------------------------\n";
enum Karakteristike { NARUDZBA, KVALITET, PAKOVANJE, ISPORUKA };

char* GetNizKaraktera(const char* sadrzaj, bool dealociraj = false) {
    if (sadrzaj == nullptr)return nullptr;
    int vel = strlen(sadrzaj) + 1;
    char* temp = new char[vel];
    strcpy_s(temp, vel, sadrzaj);
    if (dealociraj)
        delete[]sadrzaj;
    return temp;
}

ostream& operator<<(ostream& COUT, Karakteristike obj) {
    const char* niz[] = { "NARUDZBA", "KVALITET", "PAKOVANJE", "ISPORUKA" };
    COUT << niz[obj];
    return COUT;
}



template<class T1, class T2>
class Parovi {
    T1* _elementi1;
    T2* _elementi2;
    int* _trenutno;
    bool _omoguciDupliranje;
public:
    Parovi(bool omoguciDupliranje = true) {
        _omoguciDupliranje = omoguciDupliranje;
        _trenutno = new int(0);
        _elementi1 = nullptr;
        _elementi2 = nullptr;
    }
    Parovi(const Parovi& obj) {
        _trenutno = new int(*obj._trenutno);
        _omoguciDupliranje = obj._omoguciDupliranje;
        _elementi1 = new T1[*_trenutno];
        _elementi2 = new T2[*_trenutno];
        for (size_t i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = obj._elementi1[i];
            _elementi2[i] = obj._elementi2[i];
        }
    }
    Parovi& operator=(const Parovi& obj) {
        if (this != &obj) {
            delete[] _elementi1; _elementi1 = nullptr;
            delete[] _elementi2; _elementi2 = nullptr;
            delete _trenutno; _trenutno = nullptr;
            _trenutno = new int(*obj._trenutno);
            _omoguciDupliranje = obj._omoguciDupliranje;
            _elementi1 = new T1[*_trenutno];
            _elementi2 = new T2[*_trenutno];
            for (size_t i = 0; i < *_trenutno; i++)
            {
                _elementi1[i] = obj._elementi1[i];
                _elementi2[i] = obj._elementi2[i];
            }

        }
        return *this;
    }

    void AddElement(T1 el1, T2 el2) {
        if (!_omoguciDupliranje) {
            for (size_t i = 0; i < *_trenutno; i++)
            {
                if (_elementi1[i] == el1 && _elementi2[i] == el2)
                    throw exception("ne moze");
            }
        }
        T1* temp1 = _elementi1;
        T2* temp2 = _elementi2;


        _elementi1 = new T1[*_trenutno + 1];
        _elementi2 = new T2[*_trenutno + 1];

        for (size_t i = 0; i < *_trenutno; i++)
        {
            _elementi1[i] = temp1[i];
            _elementi2[i] = temp2[i];
        }
        _elementi1[*_trenutno] = el1;
        _elementi2[*_trenutno] = el2;
        (*_trenutno)++;
        delete[]temp1;
        delete[]temp2;


    }
    
    Parovi operator()(int from, int to, bool akcija = false) {
        Parovi op;
        if (from < 0 || to >= *_trenutno)
            throw exception("izvan opsega");
        if (akcija == true) {
            for (size_t i = to; i >= from; i--)
            {
                op.AddElement(_elementi1[i], _elementi2[i]);
            }
        }
        else {
            for (size_t i = from; i <=to ; i++)
            {
                op.AddElement(_elementi1[i], _elementi2[i]);
            }
        }
        return op;
    }



    ~Parovi() {
        delete[] _elementi1; _elementi1 = nullptr;
        delete[] _elementi2; _elementi2 = nullptr;
        delete _trenutno; _trenutno = nullptr;
    }
    T1& getElement1(int lokacija)const { return _elementi1[lokacija]; }
    T2& getElement2(int lokacija)const { return _elementi2[lokacija]; }
    int getTrenutno() const { return *_trenutno; }
    int getOmoguciDupliranje() { return _omoguciDupliranje; }
    friend ostream& operator<< (ostream& COUT, const Parovi& obj) {
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
    friend bool operator<=(Datum d1, Datum& d2) {
        return d1.getDays() <= d2.getDays();
    }
    friend bool operator>=(Datum d1, Datum d2) {
        return d1.getDays() >= d2.getDays();
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


class ZadovoljstvoKupca {
    int _ocjena; //za svaku kupovinu kupac moze ostaviti jednu ocjenu
    //uz ocjenu, kupci mogu komentarisati svaku od karakteristika proizvoda.
    //onemoguciti dupliranje karakteristika tj. svaka karakteristika se moze komentarisati samo jednom...u suprotnom baciti objekat tipa exception
    Parovi<Karakteristike*, const char*>* _komentariKarakteristika;
public:
    ZadovoljstvoKupca(int ocjena = 0) {
        _ocjena = ocjena;
        _komentariKarakteristika = new
            Parovi<Karakteristike*, const char*>(false);
    }
    ZadovoljstvoKupca(ZadovoljstvoKupca& obj) {
        _ocjena = obj._ocjena;
        _komentariKarakteristika= new
            Parovi<Karakteristike*, const char*>(*obj._komentariKarakteristika);
    }
    
    ZadovoljstvoKupca& operator=(ZadovoljstvoKupca& obj) {
        if (this != &obj) {
            delete _komentariKarakteristika; _komentariKarakteristika = nullptr;
            _ocjena = obj._ocjena;
            _komentariKarakteristika = new
                Parovi<Karakteristike*, const char*>(*obj._komentariKarakteristika);
        }
        return *this;
    }

    friend bool operator==(const ZadovoljstvoKupca& z1, const ZadovoljstvoKupca& z2) {
        if (z1._ocjena != z2._ocjena)
            return false;
        if (z1._komentariKarakteristika->getTrenutno() != z2._komentariKarakteristika->getTrenutno())
            return false;
        for (size_t i = 0; i < z1._komentariKarakteristika->getTrenutno(); i++)
        {
            if (z1._komentariKarakteristika->getElement1(i) != z2._komentariKarakteristika->getElement1(i) ||
                z1._komentariKarakteristika->getElement2(i) != z2._komentariKarakteristika->getElement2(i))
                return false;
        }
        return true;
    }
    friend bool operator!=(const ZadovoljstvoKupca& z1, const ZadovoljstvoKupca& z2) {
        return !(z1 == z2);
    }

    void DodajKomentarKarakteristike(Karakteristike k, const char* komentar) {
        for (size_t i = 0; i < _komentariKarakteristika->getTrenutno(); i++)
        {
            if (*_komentariKarakteristika->getElement1(i) == k)
                throw exception("vec dodan");
        }
        _komentariKarakteristika->AddElement(new Karakteristike(k), komentar);
    }

    int GetOcjena() { return _ocjena; }
    Parovi<Karakteristike*, const char*>* GetKomentareKarakteristika() { return _komentariKarakteristika; }
    ~ZadovoljstvoKupca()
    {
        delete _komentariKarakteristika; _komentariKarakteristika = nullptr;
    }

    friend ostream& operator<<(ostream& COUT, const ZadovoljstvoKupca& obj) {
        COUT << "ocjena: " << obj._ocjena << endl;
        COUT << "Komentari: " << endl;
        for (size_t i = 0; i < obj._komentariKarakteristika->getTrenutno(); i++)
        {
            COUT << *obj._komentariKarakteristika->getElement1(i) << "-->" << obj._komentariKarakteristika->getElement2(i) << endl;
        }
        return COUT;
    }


};

class Osoba {
protected:
    char* _imePrezime;
    Datum _datumRodjenja;
public:
    Osoba(const char* imePrezime = "", Datum datumRodjenja = Datum()) : _datumRodjenja(datumRodjenja) {
        _imePrezime = GetNizKaraktera(imePrezime);
    }
    Osoba(const Osoba& obj) {
        _imePrezime = GetNizKaraktera(obj._imePrezime);
        _datumRodjenja = obj._datumRodjenja;
    }
    Osoba& operator=(const Osoba& obj) {
        if (this != &obj) {
            delete[] _imePrezime; _imePrezime = nullptr;
            _imePrezime = GetNizKaraktera(obj._imePrezime);
            _datumRodjenja = obj._datumRodjenja;
        }
        return *this;
    }


    
    virtual~Osoba() {
        delete[] _imePrezime; _imePrezime = nullptr;
    }
    char* GetImePrezime() { return _imePrezime; }
    Datum& GetDatumRodjenja() { return _datumRodjenja; }

    virtual void Info() = 0;
    friend ostream& operator<< (ostream& COUT, const Osoba& obj) {
        COUT << obj._imePrezime << " " << obj._datumRodjenja << endl;
        return COUT;
    }
};
mutex lo;
class Kupac:public Osoba {
    char* _emailAdresa;
    //float se odnosi na iznos racuna za odredjenu kupovinu
    Parovi<float, ZadovoljstvoKupca>* _kupovine;
    vector<int> _bodovi; // bodovi sakupljeni tokom kupovine, svakih potrosenih 10KM donosi po 1 bod.

    /*prilikom svake kupovine, ukoliko je kupac ostvario vise od 5 bodova, potrebno je, u zasebnom thread-u (nakon 3 sekunde), poslati email sa sljedecim sadrzajem:

     To: denis@fit.ba;
     Subject: Osvareni bodovi

     Postovani,

     Prilikom posljednje kupovine ste ostvarili 8 bodova, tako da trenutno vas ukupan broj bodova iznosi 20.

     Zahvaljujemo vam na kupovini.
     Puno pozdrava
*/

    void PosaljiMail(int bodovi) {
        lo.lock();
        cout << "TO: " << GetEmail() << endl;
        cout << "Subject: Osvareni bodovi" << endl << endl;
        cout << "Postovani," << endl << endl;
        cout << "Prilikom posljednje kupovine ste ostvarili " << bodovi << " bodova" << " tako da trenutno vas ukupan broj bodova iznosi " << GetBodoviUkupno() << endl<<endl;
        cout << "Zahvaljujemo vam na kupovini." << endl;
        cout << "Puno pozdrava" << endl;
        lo.unlock();
    }

public:
    Kupac(const char* imePrezime = "", Datum datumRodjenja = Datum(), const char* emailAdresa = ""):Osoba(imePrezime,datumRodjenja) {
        _emailAdresa = GetNizKaraktera(emailAdresa);
        _kupovine = new Parovi<float, ZadovoljstvoKupca>(false);
    }
    Kupac(const Kupac& obj) :Osoba(obj) {
        _emailAdresa = GetNizKaraktera(obj._emailAdresa);
        _kupovine = new  Parovi<float, ZadovoljstvoKupca>(*obj._kupovine);
        _bodovi = obj._bodovi;
   }
    
    Kupac& operator=(const Kupac& obj) {
        if (this != &obj) {
            (Osoba&)(*this) = obj;
            delete[] _emailAdresa; _emailAdresa = nullptr;
            delete _kupovine; _kupovine = nullptr;
            _emailAdresa = GetNizKaraktera(obj._emailAdresa);
            _kupovine = new  Parovi<float, ZadovoljstvoKupca>(*obj._kupovine);
            _bodovi = obj._bodovi;
        }
        return *this;

    }


    void DodajKupovinu(int novac, ZadovoljstvoKupca zadovoljstvo) {
        if (novac > 10)
            _bodovi.push_back(novac / 10);
        if ((novac / 10) > 8) {
            this_thread::sleep_for(chrono::seconds(3));
            thread tred(&Kupac::PosaljiMail, this, novac / 10);
            tred.join();
        }

        _kupovine->AddElement(novac, zadovoljstvo);
    }
    


    Parovi<Karakteristike, const char*>GetKupovineByKomentar(const char* komentar) {
        Parovi<Karakteristike, const char*>op;
        for (int i = 0; i < _kupovine->getTrenutno(); i++)
        {
            for (size_t j = 0; j < _kupovine->getElement2(i).GetKomentareKarakteristika()->getTrenutno(); j++)
            {
                if (strstr(_kupovine->getElement2(i).GetKomentareKarakteristika()->getElement2(j), komentar) != nullptr)
                    op.AddElement(*_kupovine->getElement2(i).GetKomentareKarakteristika()->getElement1(j), _kupovine->getElement2(i).GetKomentareKarakteristika()->getElement2(j));
            }
        }
        return op;
    }


    ~Kupac()
    {
        delete[] _emailAdresa; _emailAdresa = nullptr;
        delete _kupovine; _kupovine = nullptr;
    }
    char* GetEmail() { return _emailAdresa; }
    Parovi<float, ZadovoljstvoKupca>& GetKupovine() { return *_kupovine; }
    vector<int> GetBodovi() { return _bodovi; }
    int GetBodoviUkupno() {
        int ukupno = 0;
        for (size_t i = 0; i < _bodovi.size(); i++) ukupno += _bodovi[i];
        return ukupno;
    }

    friend ostream& operator<< (ostream& COUT, const Kupac& obj) {
        COUT << crt << obj._imePrezime << " " << obj._datumRodjenja << " " << obj._emailAdresa << " " << endl;
        COUT << "KUPOVINE -> " << crt;
        for (size_t i = 0; i < obj._kupovine->getTrenutno(); i++)
            COUT << "Iznos racuna: " << obj._kupovine->getElement1(i) << "KM, zadovoljstvo kupca: " << obj._kupovine->getElement2(i) << crt;
        COUT << "BODOVI -> ";
        for (size_t i = 0; i < obj._bodovi.size(); i++)
            COUT << obj._bodovi[i] << ", ";
        COUT << crt;
        return COUT;
    }
    void Info() {
        cout << *this;
    }

};

const char* GetOdgovorNaPrvoPitanje() {
    cout << "Pitanje -> Pojasnite pojam reprezentacije tipa podatka?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}
const char* GetOdgovorNaDrugoPitanje() {
    cout << "Pitanje -> Navedite i ukratko opisite ulogu ios modova koji se koriste pri rada sa fajlovima?\n";
    return "Odgovor -> OVDJE UNESITE VAS ODGOVOR";
}

void main() {

    cout << PORUKA;
    cin.get();

    cout << GetOdgovorNaPrvoPitanje() << endl;
    cin.get();
    cout << GetOdgovorNaDrugoPitanje() << endl;
    cin.get();

    const int ParoviTestSize = 9;

    Parovi<int, int> Parovi1(false);
    for (int i = 0; i < ParoviTestSize - 1; i++)
        Parovi1.AddElement(i, i);//dodaje vrijednosti u Parovi

    try {
        //ukoliko nije dozvoljeno dupliranje elemenata (provjeravaju se T1 ili T2), metoda AddElement treba baciti izuzetak tipa exception
        Parovi1.AddElement(3, 3);
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }
    Parovi1.AddElement(9, 9);

    cout << Parovi1 << crt;

    /*
    metoda prihvata indekse lokacije, te vraća elemente koji se u kolekciji parova nalaze
    na proslijedjenim lokacijama (ukljucujuci i te lokacije)
    */
    Parovi<int, int> Parovi2 = Parovi1(2, 5);
    /*clanovi objekta Parovi2 bi trebali biti:
    2 2
    3 3
    4 4
    5 5
    */
    cout << Parovi2 << crt;
    Parovi<int, int> Parovi3 = Parovi1(2, 5, true);
    /*ukoliko se posalje treci parametar koji oznacava potrebu
    za obrnutim redoslijedom vracenih parova, clanovi objekta Parovi3 bi trebali biti:
    5 5
    4 4
    3 3
    2 2
    */
    cout << Parovi3 << crt;

    Parovi3 = Parovi2;
    cout << Parovi3 << crt;


    const int maxKupaca = 3;
    Osoba* kupci[maxKupaca];
    kupci[0] = new Kupac("Denis Music", Datum(12, 1, 1980), "denis@fit.ba");
    kupci[1] = new Kupac("Jasmin Azemovic", Datum(12, 2, 1980), "jasmin@fit.ba");
    kupci[2] = new Kupac("Adel Handzic", Datum(12, 3, 1980), "adel@edu.fit.ba");

    ZadovoljstvoKupca zadovoljstvoKupca(7);
    zadovoljstvoKupca.DodajKomentarKarakteristike(NARUDZBA, "Nismo mogli odabrati sve potrebne opcije");
    zadovoljstvoKupca.DodajKomentarKarakteristike(KVALITET, "Kvalitet je ocekivan");

    try {
        //karakteristika kvaliteta je vec komentarisana, pa je potrebno baciti izuzetak
        zadovoljstvoKupca.DodajKomentarKarakteristike(KVALITET, "Kvalitet je ocekivan");
    }
    catch (exception& err) {
        cout << err.what() << crt;
    }

    zadovoljstvoKupca.DodajKomentarKarakteristike(PAKOVANJE, "Pakovanje je bilo osteceno");
    zadovoljstvoKupca.DodajKomentarKarakteristike(ISPORUKA, "Mada su najavili da ce proizvod biti isporucen u roku od 2 dana, cekali smo 5 dana");
    cout << zadovoljstvoKupca << crt;

    Kupac* denis = dynamic_cast<Kupac*>(kupci[0]);
    /*za svakih 10KM kupcu se dodaje 1 bod, pa ce tako kupovina od 128KM kupcu donijeti 12 bodova*/
    denis->DodajKupovinu(128, zadovoljstvoKupca);
    cout << "Ukupno bodova -> " << denis->GetBodoviUkupno();//12 bodova


    ZadovoljstvoKupca zadovoljstvoKupca2(4);
    zadovoljstvoKupca2.DodajKomentarKarakteristike(KVALITET, "Jako lose, proizvod ostecen");
    denis->DodajKupovinu(81, zadovoljstvoKupca2);

    cout << "Ukupno bodova -> " << denis->GetBodoviUkupno();//20 bodova

    /*prilikom svake kupovine, ukoliko je kupac ostvario vise od 5 bodova, potrebno je, u zasebnom thread-u (nakon 3 sekunde), poslati email sa sljedecim sadrzajem:

      To: denis@fit.ba;
      Subject: Osvareni bodovi

      Postovani,

      Prilikom posljednje kupovine ste ostvarili 8 bodova, tako da trenutno vas ukupan broj bodova iznosi 20.

      Zahvaljujemo vam na kupovini.
      Puno pozdrava
 */


 //ispisuje sve podatke o kupcu i njegovim kupovinama.

    denis->Info();
    /* Primjer ispisa:
         -------------------------------------------
         Denis Music 12.1.1980 denis@fit.ba
         KUPOVINE ->
         -------------------------------------------
         Iznos racuna: 128KM, zadovoljstvo kupca: 7
                   NARUDZBA - Nismo mogli odabrati sve potrebne opcije
                   KVALITET - Kvalitet je ocekivan
                   PAKOVANJE - Pakovanje je bilo osteceno
                   ISPORUKA - Mada su najavili da ce proizvod biti isporucen u roku od 2 dana, cekali smo 5 dana
         -------------------------------------------
         Iznos racuna: 81KM, zadovoljstvo kupca: 4
                   KVALITET - Jako lose, proizvod ostecen
         -------------------------------------------
         BODOVI -> 12, 8,
         -------------------------------------------
  */

  //metoda GetKupovineByKomentar treba da pronadje i vrati sve karakteristike proizvoda i komentare kupaca koji sadrze vrijednost proslijedjenog parametra
    Parovi<Karakteristike, const char*> osteceniProizvodi = denis->GetKupovineByKomentar("ostecen");
    cout << crt << "Rezultat pretrage -> " << crt << osteceniProizvodi << crt;

    /*Ocekivani ispis:
         -------------------------------------------
         Rezultat pretrage ->
         -------------------------------------------
         PAKOVANJE Pakovanje je bio osteceno
         KVALITET Jako lose, proizvod ostecen
         -------------------------------------------
    */

    for (size_t i = 0; i < maxKupaca; i++)
        delete kupci[i], kupci[i] = nullptr;

    cin.get();
    system("pause>0");
}