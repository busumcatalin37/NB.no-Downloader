/*
TEMA LAB3
APLICATIE: Alegeti-va un tip de date - implementat cu ajutorul unei clase - cu
min 3 atribute (date membre) - de ex, clasa persoana, clasa autoturism, clasa
apartament, clasa excursie, clasa tren, clasa biblioteca, etc.) si prelucrari
asupra datelor de acest tip:
- Citirea tuturor datelor (intr-un vector clasic/STL)
- Afisarea tuturor datelor (intr-un vector clasic/STL)
- Fc de tip set/get
- Operator insertor/extractor
- Trei prelucrari asupa datelor memorate

Am ales clasa apartament cu atributele:
- zona (cartierul, tip string)
- nrCamere
- suprafata (in mp)
- pret (in euro)

Datele se memoreaza intr-un vector STL.
Prelucrari:
1) afisarea apartamentelor cu un numar dat de camere
2) afisarea celui mai ieftin apartament
3) calculul pretului mediu pe metru patrat
Programul are un meniu din care se aleg operatiile.
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class apartament{
    string zona;
    int nrCamere;
    double suprafata;
    double pret;

public:
    apartament();
    apartament(string z, int nc, double s, double p);
    ~apartament();

    void setZona(string z);
    void setNrCamere(int nc);
    void setSuprafata(double s);
    void setPret(double p);

    string getZona();
    int getNrCamere();
    double getSuprafata();
    double getPret();

    friend ostream & operator<<(ostream &out, const apartament &a);
    friend istream & operator>>(istream &in, apartament &a);
};

apartament::apartament()
{
    zona = "-";
    nrCamere = 0;
    suprafata = 0;
    pret = 0;
}

apartament::apartament(string z, int nc, double s, double p)
{
    zona = z;
    nrCamere = nc;
    suprafata = s;
    pret = p;
}

apartament::~apartament()
{
}

void apartament::setZona(string z)
{
    zona = z;
}

void apartament::setNrCamere(int nc)
{
    nrCamere = nc;
}

void apartament::setSuprafata(double s)
{
    suprafata = s;
}

void apartament::setPret(double p)
{
    pret = p;
}

string apartament::getZona()
{
    return zona;
}

int apartament::getNrCamere()
{
    return nrCamere;
}

double apartament::getSuprafata()
{
    return suprafata;
}

double apartament::getPret()
{
    return pret;
}

ostream & operator<<(ostream &out, const apartament &a)
{
    out<<"Apartament in zona "<<a.zona<<", "<<a.nrCamere<<" camere, "
       <<a.suprafata<<" mp, "<<a.pret<<" euro"<<endl;
    return out;
}

istream & operator>>(istream &in, apartament &a)
{
    cout<<"Zona: "; in>>a.zona;
    cout<<"Nr camere: "; in>>a.nrCamere;
    cout<<"Suprafata (mp): "; in>>a.suprafata;
    cout<<"Pret (euro): "; in>>a.pret;
    return in;
}

void citire(vector <apartament> &v)
{
    int n;
    apartament a;
    cout<<"Cate apartamente? "; cin>>n;
    for (int i=0; i<n; i++){
        cout<<"\nApartamentul "<<i+1<<endl;
        cin>>a;
        v.push_back(a);
    }
}

void afisare(vector <apartament> &v)
{
    if (v.size() == 0){
        cout<<"Nu exista apartamente.\n";
        return;
    }
    for (unsigned int i=0; i<v.size(); i++)
        cout<<i+1<<". "<<v[i];
}

//prelucrarea 1
void afisareCamere(vector <apartament> &v, int nc)
{
    int gasit = 0;
    for (unsigned int i=0; i<v.size(); i++)
        if (v[i].getNrCamere() == nc){
            cout<<v[i];
            gasit = 1;
        }
    if (gasit == 0)
        cout<<"Nu exista apartamente cu "<<nc<<" camere.\n";
}

//prelucrarea 2
void celMaiIeftin(vector <apartament> &v)
{
    if (v.size() == 0){
        cout<<"Nu exista apartamente.\n";
        return;
    }
    int poz = 0;
    for (unsigned int i=1; i<v.size(); i++)
        if (v[i].getPret() < v[poz].getPret())
            poz = i;
    cout<<"Cel mai ieftin: "<<v[poz];
}

//prelucrarea 3
double pretMediuMp(vector <apartament> &v)
{
    double sumaPret = 0, sumaMp = 0;
    for (unsigned int i=0; i<v.size(); i++){
        sumaPret += v[i].getPret();
        sumaMp += v[i].getSuprafata();
    }
    if (sumaMp == 0)
        return 0;
    return sumaPret / sumaMp;
}

int main()
{
    vector <apartament> v;
    int opt, nc;

    do{
        cout<<"\n--- MENIU ---\n";
        cout<<"1. Citire apartamente\n";
        cout<<"2. Afisare apartamente\n";
        cout<<"3. Apartamente cu un nr dat de camere\n";
        cout<<"4. Cel mai ieftin apartament\n";
        cout<<"5. Pretul mediu pe mp\n";
        cout<<"6. Modificare pret primul apartament (set/get)\n";
        cout<<"0. Iesire\n";
        cout<<"Optiunea: "; cin>>opt;

        switch(opt){
        case 1:
            citire(v);
            break;
        case 2:
            afisare(v);
            break;
        case 3:
            cout<<"Nr camere: "; cin>>nc;
            afisareCamere(v, nc);
            break;
        case 4:
            celMaiIeftin(v);
            break;
        case 5:
            cout<<"Pret mediu: "<<pretMediuMp(v)<<" euro/mp\n";
            break;
        case 6:
            if (v.size() > 0){
                double p;
                cout<<"Pret actual: "<<v[0].getPret()<<endl;
                cout<<"Pret nou: "; cin>>p;
                v[0].setPret(p);
                cout<<v[0];
            }
            else
                cout<<"Nu exista apartamente.\n";
            break;
        case 0:
            break;
        default:
            cout<<"Optiune gresita!\n";
        }
    }while(opt != 0);

    return 0;
}
