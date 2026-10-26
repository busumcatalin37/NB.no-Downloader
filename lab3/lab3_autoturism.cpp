/*
TEMA LAB3
APLICATIE: Alegeti-va un tip de date - implementat cu ajutorul unei clase - cu
min 3 atribute (date membre) - de ex, clasa persoana, clasa autoturism, clasa
apartament, clasa excursie, clasa tren, clasa biblioteca, etc.) si prelucrari
asupra datelor de acest tip:
-	Citirea tuturor datelor (intr-un vector clasic/STL)
-	Afisarea tuturor datelor (intr-un vector clasic/STL)
-	Fc de tip set/get
-	Operator insertor/extractor
-	Trei prelucrari asupa datelor memorate
Veti folosi ptr prelucrari functii.

------------------------------------------------------------------------------
TEMA ALEASA

Sa se defineasca tipul de date auto (autoturism) cu atributele (date membre):
- marca (tip string)
- model (tip string)
- an (anul fabricatiei)
- pret (in euro)
- km (kilometrajul)

Fc:
- Constr (cu param impliciti)
- Destr
- Met de tip get si set
- Operator insertor, extractor
- Op atribuire
- Op < (compara preturile a doua autoturisme)

PRELUCR
- cit inf despre autoturisme de la tast
- afisarea tuturor autoturismelor
- P1: afisarea autoturismelor unei marci date si a pretului mediu al acestora
- P2: afisarea celui mai ieftin autoturism fabricat incepand cu un an dat
- P3: sortarea autoturismelor crescator dupa pret si afisarea lor

MODURI DE LUCRU
1) vect clasic (alocare statica / dinamica)
2) STL (vector STL)
*/


#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class autoturism{
//dat membre, IMPLICIT private
    string marca;
    string model;
    int an;
    double pret;
    int km;

public:
    //constr cu param impliciti (2 in 1)
    autoturism(string Marca="Necunoscuta", string Model="Necunoscut",
               int An=2000, double Pret=0, int Km=0);
    //destr
    ~autoturism();
    //met tip set
    void setMarca(string);
    void setModel(string);
    void setAn(int);
    void setPret(double);
    void setKm(int);
    //met tip get
    string getMarca() const;
    string getModel() const;
    int getAn() const;
    double getPret() const;
    int getKm() const;
    //op insertor
    friend ostream & operator<<(ostream &, const autoturism &);
    //op extractor
    friend istream & operator>>(istream &, autoturism &);
    //op atribuire
    autoturism & operator=(const autoturism &);
    //op < (prin metoda) - compara preturile
    bool operator<(const autoturism &) const;
};


autoturism::autoturism(string Marca, string Model, int An, double Pret, int Km)
{
    marca = Marca;
    model = Model;
    an = An;
    pret = Pret;
    km = Km;
}

autoturism::~autoturism()
{
    //nu exista memorie alocata dinamic in clasa, nu avem ce elibera
    //cout<<"Destr ptr "<<*this<<endl;
}

void autoturism::setMarca(string s)
{
    marca = s;
}

void autoturism::setModel(string s)
{
    model = s;
}

void autoturism::setAn(int a)
{
    an = a;
}

void autoturism::setPret(double p)
{
    if (p >= 0)
        pret = p;
}

void autoturism::setKm(int k)
{
    if (k >= 0)
        km = k;
}

string autoturism::getMarca() const
{
    return marca;
}

string autoturism::getModel() const
{
    return model;
}

int autoturism::getAn() const
{
    return an;
}

double autoturism::getPret() const
{
    return pret;
}

int autoturism::getKm() const
{
    return km;
}

ostream & operator<<(ostream &ies, const autoturism &a)
{
    ies<<"AUTO "<<a.marca<<" "<<a.model<<", an "<<a.an
       <<", pret "<<a.pret<<" euro, "<<a.km<<" km";
    return ies;
}

istream & operator>>(istream &intr, autoturism &a)
{
    cout<<"Marca ="; intr>>a.marca;
    cout<<"Model ="; intr>>a.model;
    cout<<"An ="; intr>>a.an;
    cout<<"Pret ="; intr>>a.pret;
    cout<<"Km ="; intr>>a.km;
    return intr;
}

autoturism & autoturism::operator=(const autoturism &a)
{
    if (this != &a){        //evitam atribuirea x = x
        marca = a.marca;    // this->marca = a.marca;
        model = a.model;
        an = a.an;
        pret = a.pret;
        km = a.km;
    }
    return *this;
}

bool autoturism::operator<(const autoturism &b) const
{
    //compara pretul ob-lui curent cu pretul lui b
    return pret < b.pret;
}


//VARIANTA 1 - vect clasic
void cit(autoturism v[], int n)
{
    for (int i=0; i<n; i++){
        cout<<"\nAstept inf despre autoturismul "<<i+1<<endl;
        cin>>v[i];
        //cin>>*(v+i);
    }
}

void afis(autoturism v[], int n)
{
    for (int i=0; i<n; i++)
        cout<<i+1<<". "<<v[i]<<endl;
}

//P1 - autoturismele unei marci date si pretul lor mediu
void afisMarca(autoturism v[], int n, string marca)
{
    double s=0;
    int nr=0;
    cout<<"\nAutoturisme marca "<<marca<<":\n";
    for (int i=0; i<n; i++)
        if (v[i].getMarca() == marca){
            cout<<v[i]<<endl;
            s += v[i].getPret();
            nr++;
        }
    if (nr == 0)
        cout<<"Nu exista.\n";
    else
        cout<<"PRET MEDIU = "<<s/nr<<" euro\n";
}

//P2 - cel mai ieftin autoturism fabricat incepand cu anul dat
void celMaiIeftin(autoturism v[], int n, int an)
{
    int poz=-1;
    for (int i=0; i<n; i++)
        if (v[i].getAn() >= an)
            if (poz == -1 || v[i] < v[poz])
                poz = i;
    if (poz == -1)
        cout<<"\nNu exista autoturisme fabricate din "<<an<<" incoace.\n";
    else
        cout<<"\nCel mai ieftin din "<<an<<" incoace: "<<v[poz]<<endl;
}

//P3 - sortare crescatoare dupa pret (metoda bulelor, cu op < si op =)
void sortPret(autoturism v[], int n)
{
    autoturism aux;
    for (int i=0; i<n-1; i++)
        for (int j=i+1; j<n; j++)
            if (v[j] < v[i]){
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
}


//VARIANTA 2 - STL
void citSTLvect(vector <autoturism> &v)
{
    int n;
    cout<<"Cate autoturisme? "; cin>>n;
    autoturism a;
    for (int i=0; i<n; i++){
        cout<<"\nAstept inf despre autoturismul "<<i+1<<endl;
        cin>>a;
        v.push_back(a);
    }
}

void afisSTLvect(const vector <autoturism> &v)
{
    for (unsigned int i=0; i<v.size(); i++)
        cout<<i+1<<". "<<v[i]<<endl;
}

//P1 - varianta STL (parcurgere cu iterator)
void afisMarcaSTL(const vector <autoturism> &v, string marca)
{
    double s=0;
    int nr=0;
    cout<<"\nAutoturisme marca "<<marca<<":\n";
    for (vector <autoturism>::const_iterator it=v.begin(); it!=v.end(); it++)
        if (it->getMarca() == marca){
            cout<<*it<<endl;
            s += it->getPret();
            nr++;
        }
    if (nr == 0)
        cout<<"Nu exista.\n";
    else
        cout<<"PRET MEDIU = "<<s/nr<<" euro\n";
}

//P2 - varianta STL
void celMaiIeftinSTL(const vector <autoturism> &v, int an)
{
    int poz=-1;
    for (unsigned int i=0; i<v.size(); i++)
        if (v[i].getAn() >= an)
            if (poz == -1 || v[i] < v[poz])
                poz = i;
    if (poz == -1)
        cout<<"\nNu exista autoturisme fabricate din "<<an<<" incoace.\n";
    else
        cout<<"\nCel mai ieftin din "<<an<<" incoace: "<<v[poz]<<endl;
}

//P3 - varianta STL (alg sort din <algorithm>, foloseste op <)
void sortPretSTL(vector <autoturism> &v)
{
    sort(v.begin(), v.end());
}


int main()
{
/******
VARIANTA 1
//alocare statica
autoturism V[100];
int n; //nr autoturisme
cout<<"Nr autoturisme ="; cin>>n;
cit(V, n);
cout<<"\n\nTOATE AUTOTURISMELE\n";
afis(V, n);

//ALOCARE DINAM
autoturism *a;
int nr;
cout<<"Cate autoturisme? "; cin>>nr;
a = new autoturism[nr];
cit(a, nr);
cout<<"\n\nTOATE AUTOTURISMELE\n";
afis(a, nr);

string m;
cout<<"\nMarca cautata ="; cin>>m;
afisMarca(a, nr, m);

int an;
cout<<"\nAnul minim de fabricatie ="; cin>>an;
celMaiIeftin(a, nr, an);

sortPret(a, nr);
cout<<"\n\nSORTATE DUPA PRET\n";
afis(a, nr);

delete [] a;
***************/

//VARIANTA 2 - STL
vector <autoturism> x;

citSTLvect(x);

cout<<"\n\nTOATE AUTOTURISMELE\n";
afisSTLvect(x);

//exemplu set/get
if (!x.empty()){
    double p;
    cout<<"\nPretul actual al primului autoturism: "<<x[0].getPret()<<" euro";
    cout<<"\nPret nou ="; cin>>p;
    x[0].setPret(p);
    cout<<"Dupa modificare: "<<x[0]<<endl;
}

string m;
cout<<"\nMarca cautata ="; cin>>m;
afisMarcaSTL(x, m);

int an;
cout<<"\nAnul minim de fabricatie ="; cin>>an;
celMaiIeftinSTL(x, an);

sortPretSTL(x);
cout<<"\n\nSORTATE DUPA PRET\n";
afisSTLvect(x);

return 0;
}
