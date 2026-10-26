/*
Sa se defineasca tipul de date masina cu atributele (date membre):
- nr (numar masina)
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
- afisarea masinilor
- afisarea masinilor cu media km >= o valoare data
- afisarea masinii cu media km cea mai mare
- afisarea masinilor de o anumita marca

MODURI DE LUCRU
1) vect clasic
2) STL (vector STL)
*/


#include <iostream>
#include <vector>
using namespace std;

class masina{
//dat membre, IMPLICIT private
    int nr;
    string marca;
    int km[3];

public:
    //constr cu param impliciti
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
    return km;
}

ostream & operator<<(ostream &ies, const masina&m)
{
    ies<<"MASINA "<<m.marca<<" nr ="<<m.nr<<" km: ";
    for (int i=0; i<3; i++)
        ies<<m.km[i]<<"  ";
    ies<<endl;
    return ies;
}

istream & operator>>(istream & intr, masina & m)
{
    cout<<"\nNr ="; intr>>m.nr;
    cout<<"Marca ="; intr>>m.marca;
    cout<<"Introdu km pe 3 luni:\n";
    for (int i=0; i<3; i++){
        cout<<"Luna "<<i+1<<" =";
        intr>>m.km[i];
    }
    return intr;
}

masina & masina::operator=(const masina &m)
{
    nr = m.nr;
    marca = m.marca;
    for (int i=0; i<3; i++)
        km[i] = m.km[i];
    return *this;
}

double med(int *a)  //media celor 3 valori
{
    double m=0;
    for (int i=0; i<3; i++)
        m += a[i];
    return m/3;
}

bool masina::operator >= (masina &b)
{
    if (med(this->getKm()) >= med(b.getKm()))
        return true;
    else
        return false;
}

//VARIANTA 1
void cit(masina v[], int n)
{
    for (int i=0; i<n; i++){
        cout<<"Masina "<<i+1<<endl;
        cin>>v[i];
    }
}

void afis(masina v[], int n)
{
    for (int i=0; i<n; i++)
        cout<<v[i];
}

//VARIANTA 2
void citSTLvect(vector <masina> &v)
{
    int n;
    cout<<"Cate masini?"; cin>>n;
    masina a;
    for (int i=0; i<n; i++){
        cin>>a;
        v.push_back(a);
    }
}

void afisSTLvect(vector <masina> &v)
{
    for (unsigned int i=0; i<v.size(); i++)
        cout<<v[i]<<"MEDIA ="<<med(v[i].getKm())<<endl;
}

void afisMedie(vector <masina> &v, double x)
{
    for (unsigned int i=0; i<v.size(); i++)
        if (med(v[i].getKm()) >= x)
            cout<<v[i];
}

void afisMax(vector <masina> &v)
{
    masina max;
    max = v[0];
    for (unsigned int i=1; i<v.size(); i++)
        if (v[i] >= max)
            max = v[i];
    cout<<max;
}

void afisMarca(vector <masina> &v, string s)
{
    for (unsigned int i=0; i<v.size(); i++)
        if (v[i].getMarca() == s)
            cout<<v[i];
}

int main()
{
/******
VARIANTA 1
masina V[100];
int n;
cout<<"Nr masini ="; cin>>n;
cit(V, n);
afis(V, n);
***************/

//VARIANTA 2 - STL
vector <masina> x;
double m;
string s;

citSTLvect(x);

cout<<"\n\nMASINI\n";
afisSTLvect(x);

cout<<"\nMedia minima ="; cin>>m;
cout<<"\nMASINI CU MEDIA >= "<<m<<endl;
afisMedie(x, m);

cout<<"\nMASINA CU MEDIA CEA MAI MARE\n";
afisMax(x);

cout<<"\nMarca ="; cin>>s;
cout<<"\nMASINI "<<s<<endl;
afisMarca(x, s);

return 0;
}
