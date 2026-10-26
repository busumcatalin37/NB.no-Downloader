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
- nr (numar de identificare)
- marca (tip string)
- vect de 3 valori intregi (km parcursi in ultimele 3 luni)

Fc:
- Constr
- Destr
- Met de tip get si set
- Operator insertor, extractor
- Op atribuire
- Op >= (compara mediile de km a doua masini)

PRELUCR
- cit inf despre masini de la tast
- afisarea tuturor masinilor
- P1: afisarea masinilor cu media km/luna >= o valoare data
- P2: afisarea masinii cu cea mai mare medie km/luna
- P3: afisarea masinilor de o anumita marca

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
    int nr;
    string marca;
    int km[3];

public:
    //constr cu param impliciti (2 in 1)
    masina(int Nr=0, string Marca="Necunoscuta", int *Km=NULL);
    //destr
    ~masina();
    //met tip set
    void setNr(int);
    void setMarca(string);
    void setKm(int *v);
    //met tip get
    int getNr();
    string getMarca();
    int *getKm();
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




masina::masina(int Nr, string Marca, int *Km)
{
    nr = Nr;
    marca = Marca;
    for (int i=0; i<3; i++)
        if (Km != NULL)
            km[i] = Km[i];
        else
            km[i] = 0;
}

masina::~masina()
{
    //km e vector static, nu se face delete
    //cout<<"Destr ptr "<<*this<<endl;
}

void masina::setNr(int n)
{
    nr = n;
}

void masina::setMarca(string s)
{
    marca = s;
}

void masina::setKm(int *v)
{
    for (int i=0; i<3; i++)
        km[i] = v[i];
       // *(km+i) = *(v+i);
}

int masina::getNr()
{
    return nr;
}

string masina::getMarca()
{
    return marca;
}

int * masina::getKm()
{
    return km; //return &km[0];
}

ostream & operator<<(ostream &ies, const masina&m)
{
    ies<<"MASINA "<<m.marca<<  " nr ="<< m.nr<<" a parcurs (km) ";
    for (int i=0; i<3; i++)
        ies <<m.km[i]<<"  ";
    ies<<endl;
    return ies;
}

istream & operator>>(istream & intr, masina & m)
{
    cout<<"\nIntrodu inf despre masina\nNr ="; intr>>m.nr;
    cout<<"Marca ="; intr>>m.marca;
    cout<<"Introdu km parcursi:\n";
    int v[3];
    for (int i=0; i<3; i++){
        cout<<"Luna "<<i+1<<" =";
        intr>>v[i];
    }
    m.setKm(v);
    return intr;
}

masina & masina::operator=(const masina &m)
{
    nr = m.nr;       // this->nr = m.nr;
    marca = m.marca;
    for (int i=0; i<3; i++)
        km[i] = m.km[i];
    return *this;
}

double med(int *a)  //calc si returneaza media celor 3 valori din vect a
{
    double m=0;
    for (int i=0; i<3; i++)
        m += a[i];      //m += *(a+i);
    return m/3;
}

bool masina::operator >= (masina &b)
{
    //compara media ob-lui curent cu media lui b
    double m1=med(this->getKm());
    double m2=med(b.getKm());

    if (m1 >= m2)
        return true;
    else
        return false;
}

//VARIANTA 1
void cit(masina v[], int n)
//void cit(*v, int n)
{
    for (int i=0; i<n; i++){
        cout<<"Astept inf despre masina "<<i+1<<endl;
        cin>>v[i];
        //cin>>*(v+i);
    }
}

void afis(masina v[], int n)
{
    cout<<"\n\nTOATE MASINILE\n";
    for (int i=0; i<n; i++)
        cout<<v[i]<<"MEDIA ="<<med(v[i].getKm())<<endl;
}

//P1
void afisMedie(masina v[], int n, double x)
{
    cout<<"\n\nMASINI CU MEDIA >= "<<x<<endl;
    for (int i=0; i<n; i++)
        if (med(v[i].getKm()) >= x)
            cout<<v[i]<<"MEDIA ="<<med(v[i].getKm())<<endl;
}

//P2
void afisMax(masina v[], int n)
{
    masina max;
    max = v[0];
    for (int i=1; i<n; i++)
        if (v[i] >= max)
            max = v[i];
    cout<<"\n\nMEDIA CEA MAI MARE\n"<<max<<"MEDIA ="<<med(max.getKm())<<endl;
}

//P3
void afisMarca(masina v[], int n, string s)
{
    cout<<"\n\nMASINI "<<s<<endl;
    for (int i=0; i<n; i++)
        if (v[i].getMarca() == s)
            cout<<v[i];
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
        cout<<v[i]<<"MEDIA ="<<med(v[i].getKm())<<endl;
}

//P1
void afisMedieSTL(vector <masina> &v, double x)
{
    cout<<"\n\nMASINI CU MEDIA >= "<<x<<endl;
    for (unsigned int i=0; i<v.size(); i++)
        if (med(v[i].getKm()) >= x)
            cout<<v[i]<<"MEDIA ="<<med(v[i].getKm())<<endl;
}

//P2
void afisMaxSTL(vector <masina> &v)
{
    masina max;
    max = v[0];
    for (unsigned int i=1; i<v.size(); i++)
        if (v[i] >= max)
            max = v[i];
    cout<<"\n\nMEDIA CEA MAI MARE\n"<<max<<"MEDIA ="<<med(max.getKm())<<endl;
}

//P3
void afisMarcaSTL(vector <masina> &v, string s)
{
    cout<<"\n\nMASINI "<<s<<endl;
    for (unsigned int i=0; i<v.size(); i++)
        if (v[i].getMarca() == s)
            cout<<v[i];
}

int main()
{
double x;
string s;
/******
VARIANTA 1
//alocare statica
masina V[100];
int n; //nr masini
cout<<"Nr masini ="; cin>>n;
cit(V, n);
afis(V, n);
cout<<"\nMedia minima ="; cin>>x;
afisMedie(V, n, x);
afisMax(V, n);
cout<<"\nMarca cautata ="; cin>>s;
afisMarca(V, n, s);


//ALOCARE DINAM
masina *a;
int nr;
cout<<"Cate masini?"; cin>>nr;
a = new masina[nr];
cit(a, nr);
afis(a, nr);
cout<<"\nMedia minima ="; cin>>x;
afisMedie(a, nr, x);
afisMax(a, nr);
cout<<"\nMarca cautata ="; cin>>s;
afisMarca(a, nr, s);
delete [] a;
***************/

//VARIANTA 2 - STL
vector <masina> y;

citSTLvect(y);
afisSTLvect(y);

cout<<"\nMedia minima ="; cin>>x;
afisMedieSTL(y, x);

afisMaxSTL(y);

cout<<"\nMarca cautata ="; cin>>s;
afisMarcaSTL(y, s);

return 0;
}
