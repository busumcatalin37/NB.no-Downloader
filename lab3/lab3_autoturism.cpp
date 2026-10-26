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

Sa se defineasca tipul de date masina (autoturism) cu atributele (date membre):
- marca (tip string)
- an (anul fabricatiei)
- pret (in euro)

Fc:
- Constr
- Destr
- Met de tip get si set
- Operator insertor, extractor
- Op atribuire
- Op >= (compara preturile a doua masini)

PRELUCR
- cit inf despre masini de la tast
- afisarea tuturor masinilor
- P1: afisarea masinilor de o anumita marca
- P2: afisarea celei mai scumpe masini
- P3: calculul pretului mediu al masinilor

MODURI DE LUCRU
1) vect clasic
2) STL (vector STL)
*/


#include <iostream>
#include <string>
#include <vector>
using namespace std;

class masina{
//dat membre, IMPLICIT private
    string marca;
    int an;
    double pret;

public:
    //constr cu param impliciti (2 in 1)
    masina(string Marca="Necunoscuta", int An=2000, double Pret=0);
    //destr
    ~masina();
    //met tip set
    void setMarca(string);
    void setAn(int);
    void setPret(double);
    //met tip get
    string getMarca();
    int getAn();
    double getPret();
    //op insertor
    friend ostream & operator<<(ostream &, const masina&);
    //op extractor
    friend istream & operator>>(istream &, masina &);
    //op atrib
    masina & operator=(const masina &);
    //op >=
    //prin metoda
    bool operator >= (masina &);
};




masina::masina(string Marca, int An, double Pret)
{
    marca = Marca;
    an = An;
    pret = Pret;
}

masina::~masina()
{
    //cout<<"Destr ptr "<<marca<<endl;
}

void masina::setMarca(string s)
{
    marca = s;
}

void masina::setAn(int a)
{
    an = a;
}

void masina::setPret(double p)
{
    pret = p;
}

string masina::getMarca()
{
    return marca;
}

int masina::getAn()
{
    return an;
}

double masina::getPret()
{
    return pret;
}

ostream & operator<<(ostream &ies, const masina&m)
{
    ies<<"MASINA "<<m.marca<<" an "<<m.an<<" pret "<<m.pret<<" euro"<<endl;
    return ies;
}

istream & operator>>(istream & intr, masina & m)
{
    cout<<"\nIntrodu inf despre masina\nMarca ="; intr>>m.marca;
    cout<<"An ="; intr>>m.an;
    cout<<"Pret ="; intr>>m.pret;
    return intr;
}

masina & masina::operator=(const masina &m)
{
    marca = m.marca;       // this->marca = m.marca;
    an = m.an;
    pret = m.pret;
    return *this;
}

bool masina::operator >= (masina &b)
{
    //compara pretul ob-lui curent cu pretul lui b
    if (this->getPret() >= b.getPret())
        return true;
    else
        return false;
}

//VARIANTA 1
void cit(masina v[], int n)
{
    for (int i=0; i<n; i++){
        cout<<"Astept inf despre masina "<<i+1<<endl;
        cin>>v[i];
    }
}

void afis(masina v[], int n)
{
    cout<<"\n\nTOATE MASINILE\n";
    for (int i=0; i<n; i++)
        cout<<v[i];
}

//P1
void afisMarca(masina v[], int n, string s)
{
    cout<<"\n\nMASINI "<<s<<endl;
    for (int i=0; i<n; i++)
        if (v[i].getMarca() == s)
            cout<<v[i];
}

//P2
void ceaMaiScumpa(masina v[], int n)
{
    masina max;
    max = v[0];
    for (int i=1; i<n; i++)
        if (v[i] >= max)
            max = v[i];
    cout<<"\n\nCEA MAI SCUMPA\n"<<max;
}

//P3
double pretMediu(masina v[], int n)
{
    double s=0;
    for (int i=0; i<n; i++)
        s += v[i].getPret();
    return s/n;
}

//VARIANTA 2
void citSTLvect(vector <masina> &v)
{
    int n;
    cout<<"Cate masini?"; cin>>n;
    masina a;
    for (int i=0; i<n; i++){
        cout<<"... masina\n";
        cin>>a;
        v.push_back(a);
    }
}

void afisSTLvect(vector <masina> &v)
{
    cout<<"\n\nTOATE MASINILE\n";
    for (unsigned int i=0; i<v.size(); i++)
        cout<<v[i];
}

//P1
void afisMarcaSTL(vector <masina> &v, string s)
{
    cout<<"\n\nMASINI "<<s<<endl;
    for (unsigned int i=0; i<v.size(); i++)
        if (v[i].getMarca() == s)
            cout<<v[i];
}

//P2
void ceaMaiScumpaSTL(vector <masina> &v)
{
    masina max;
    max = v[0];
    for (unsigned int i=1; i<v.size(); i++)
        if (v[i] >= max)
            max = v[i];
    cout<<"\n\nCEA MAI SCUMPA\n"<<max;
}

//P3
double pretMediuSTL(vector <masina> &v)
{
    double s=0;
    for (unsigned int i=0; i<v.size(); i++)
        s += v[i].getPret();
    return s/v.size();
}

int main()
{
/******
VARIANTA 1
masina V[100];
int n; //nr masini
cout<<"Nr masini ="; cin>>n;
cit(V, n);
afis(V, n);

string s;
cout<<"\nMarca cautata ="; cin>>s;
afisMarca(V, n, s);

ceaMaiScumpa(V, n);

cout<<"\nPRET MEDIU ="<<pretMediu(V, n)<<endl;
***************/

//VARIANTA 2 - STL
vector <masina> x;

citSTLvect(x);
afisSTLvect(x);

string s;
cout<<"\nMarca cautata ="; cin>>s;
afisMarcaSTL(x, s);

ceaMaiScumpaSTL(x);

cout<<"\nPRET MEDIU ="<<pretMediuSTL(x)<<endl;

return 0;
}
