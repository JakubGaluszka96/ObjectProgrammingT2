#include <iostream>
#include <fstream>

using namespace std;
//klasa wirtualna
class budynek {
public:
    float CenaZaWynajem;
//metoda wirtualna
    void Wynajmij(){
    cout << "Budynek ksiegarni wynajeto."<<endl;
    }
protected:
private:

};
//klasa wirtualna
class artykul {
public:
    float CenaKup, CenaSprzedaj;
    getCenaKup(){ //getter 1
    return CenaKup;
    }
    getCenaSprzedaj(){ //getter 2
    return CenaSprzedaj;
    }
    //metoda 1 //setter
    void ZmienCeneKup(float cena){
    this->CenaKup=cena;
    cout << "Zmieniono cene kupna artykulu."<<endl;
    }
    //metoda 2 //setter
    void ZmienCeneSprzedaj(float cena){
    this->CenaSprzedaj=cena;
    cout << "Zmieniono cene sprzedazy artykulu."<<endl;
    }
    //metoda 3 //setter
    void WyswietlCeny(){
    cout << "Cena kupna: " << getCenaKup() <<endl;
    cout << "Cena sprzedazy: " << getCenaSprzedaj() << endl;
    }
protected:
private:
};
//klasa standardowa 1
class ksiazka: public artykul { //dziedzicznie z klasy artykul
public:
    string tytul;
    int IloscTomow;
//metoda 4
~ksiazka(){
cout << "Ksiazke: " << this->tytul <<" zniszczono"<< endl;
}

ksiazka(){ //konstruktor domyslny
this->tytul="Domyslna";
this->CenaKup=0;
this->CenaSprzedaj=0;
this->IloscTomow=1;
}
//polimorfizm
ksiazka(string tytul, int IloscTomow, float CenaKup, float CenaSprzedaj){ //konstruktor 2
this->tytul=tytul; //przyslonienie zmiennych
this->CenaKup=CenaKup; //przyslonienie zmiennych
this->CenaSprzedaj=CenaSprzedaj; //przyslonienie zmiennych
this->IloscTomow=IloscTomow; //przyslonienie zmiennych
}
//konstruktor kopiujacy
ksiazka(ksiazka &x) {
tytul=x.tytul;
IloscTomow=x.IloscTomow;
CenaKup=x.CenaKup;
CenaSprzedaj=x.CenaSprzedaj;
cout << "Stworzono druga taka sama ksiazke."<<endl;
}
//setter
void ZmienTytul(string tytul){
this->tytul=tytul;
}
};
//klasa standardowa 2
class sklep: public budynek{ //dziedziczenie z klasy budynek
public:
    float przychody=0.0, wydatki=0.0, saldo=0.0;
//metoda
void sprzedaj(ksiazka& nazwa){
    cout<< "Sprzedano artykul." << endl;
    this->przychody=this->przychody+nazwa.CenaSprzedaj;
    this->saldo=this->saldo+nazwa.CenaSprzedaj;
}
//metoda
void kup(ksiazka& nazwa){
    cout<< "Zakupiono artykul." << endl;
    this->wydatki=this->wydatki+nazwa.CenaKup;
    this->saldo=this->saldo-nazwa.CenaKup;
//    this->IloscKsiazek=IloscKsiazek+1;
}
};
//klasa standardowa 3
class ksiegarnia: public ksiazka, public sklep{
public:

    bool czynne=1;
    //metoda
    void kupKsiazke(ksiazka& nazwa){
        if (czynne == 1) {
    kup(nazwa);
    this->IloscKsiazek=this->IloscKsiazek+1;
    this->SumaTomow=this->SumaTomow+nazwa.IloscTomow;
    }
        else {
    cout << "Ksiegarnia jest zamknieta. Nie mozna nic kupic. Otworz ksiegarnie."<< endl;
    }
    }
    //metoda
    void SprzedajKsiazke(ksiazka& nazwa){
        if (czynne == 1) {
    sprzedaj(nazwa);
    this->IloscKsiazek=this->IloscKsiazek-1;
    this->SumaTomow=this->SumaTomow-nazwa.IloscTomow;
        }
        else{
    cout << "Ksiegarnia jest zamknieta. Nie mozna nic sprzedac. Otworz ksiegarnie."<< endl;
        }
    }
    //setter
    void OtworzKsiegarnie(){
    this->czynne=1;
    cout<< "Otwarto ksiegarnie"<< endl;
    }
    //setter
    void ZamknijKsiegarnie(){
    this->czynne=0;
    cout<< "Zamknieto ksiegarnie, zapraszamy ponownie."<< endl;
    }
    //metoda druku
    void WyswietlStan(){
    if (czynne == 1) {
    cout << "Ksiegarnia jest czynna."<< endl;
    }
    else {
    cout << "Ksiegarnia jest zamknieta."<< endl;
    }
    cout << "W ksiegarni jest: " << IloscKsiazek << " ksiazek o lacznej ilosci: " << SumaTomow<< " tomow." << endl;
    cout << "Przychody: " << przychody << " Wydatki: " << wydatki << " Saldo: " << saldo <<endl;
    }
    //zapis do pliku
    void zapis(){
    ofstream plik("plik.txt", ios_base::app);
    plik << IloscKsiazek << " "<< SumaTomow << " " << przychody << " " << wydatki << " " << saldo << endl;
    plik.close();
    }
    //odczyt z pliku
    void odczyt(){
    ifstream plik;
    plik.open ("plik.txt");
    plik >> IloscKsiazek >> SumaTomow >> przychody >> wydatki >> saldo;
    cout << "W ksiegarni jest: " << IloscKsiazek << " ksiazek o lacznej ilosci: " << SumaTomow<< " tomow." << endl;
    cout << "Przychody: " << przychody << " Wydatki: " << wydatki << " Saldo: " << saldo << "         STAN ODCZYTANO." <<endl;
    plik.close();
    }
    ~ksiegarnia(){
    cout<<"Zamknieto ksiegarnie"<<endl;
    }
    private:
    int IloscKsiazek=0, SumaTomow=0;
};
int main()
{
    ksiazka KA1; //utworzenie instancji ksiazka (KA1)
    KA1.WyswietlCeny(); //wywolanie metody druku
    ksiazka KA2("Mama",3,20.00,30.00); //wywolanie konstruktora 2
    KA2.WyswietlCeny(); //wywolanie metody druku
    KA1.ZmienCeneKup(20.99); //wywolanie settera
    KA1.ZmienCeneSprzedaj(21.99); //wywolanie settera
    KA1.WyswietlCeny(); //wywolanie metody druku
    ksiazka* KA3 = new ksiazka(KA2); //wywolanie konstruktora kopiujacego z dynamicznym przydzialem pamieci
    KA3->tytul = "Mama 2"; //edycja tytulu (bez settera)
    KA3->ZmienTytul("Mama 3"); //edycja tytulu (bez settera)
    KA3->WyswietlCeny(); //wywolanie metody druku
    ksiegarnia* PI = new ksiegarnia; //dynamiczne przydzielenie pamieci dla obkietu typu ksiegarnia
    PI->SprzedajKsiazke(KA2); //metody podczas pracy ksiegarni
    PI->kupKsiazke(KA2);
    PI->WyswietlStan();
    PI->kupKsiazke(KA2);
    PI->WyswietlStan();
    PI->ZamknijKsiegarnie();
    PI->kupKsiazke(KA2);
    PI->zapis(); //zapis do pliku "plik.txt"
    PI->odczyt(); //oczyt z pliku "plik.txt"
    delete PI;
    delete KA3; //zwolnienie pamieci
    cout << "KONIEC PROGRAMU." << endl;
    return 0;
}
