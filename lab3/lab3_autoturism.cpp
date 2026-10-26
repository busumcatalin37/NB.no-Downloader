/*
================================================================================
 TEMA LAB3
================================================================================
 APLICATIE: Alegeti-va un tip de date - implementat cu ajutorul unei clase - cu
 min 3 atribute (date membre) - de ex. clasa persoana, clasa autoturism, clasa
 apartament, clasa excursie, clasa tren, clasa biblioteca etc. - si prelucrari
 asupra datelor de acest tip:
   - Citirea tuturor datelor (intr-un vector clasic/STL)
   - Afisarea tuturor datelor (intr-un vector clasic/STL)
   - Fc de tip set/get
   - Operator insertor/extractor
   - Trei prelucrari asupra datelor memorate
 Veti folosi pentru prelucrari functii.

--------------------------------------------------------------------------------
 TEMA ALEASA: clasa AUTOTURISM
--------------------------------------------------------------------------------
 Se considera clasa Autoturism cu atributele:
   - marca           (string)
   - model           (string)
   - anFabricatie    (int)
   - pret            (double, in euro)
   - kilometraj      (int)

 Datele a n autoturisme se memoreaza intr-un vector STL (vector<Autoturism>).
 Se cer:
   1. Citirea datelor celor n autoturisme (cu operatorul extractor >>).
   2. Afisarea datelor tuturor autoturismelor (cu operatorul insertor <<).
   3. Functii set/get pentru toate atributele.
   4. Prelucrari:
      P1. Afisarea autoturismelor unei marci date si calculul pretului mediu
          al acestora.
      P2. Determinarea celui mai ieftin autoturism fabricat dupa un an dat
          (inclusiv acel an).
      P3. Sortarea autoturismelor crescator dupa pret si, la pret egal,
          crescator dupa kilometraj; afisarea vectorului sortat.
================================================================================
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Autoturism
{
private:
    string marca;
    string model;
    int anFabricatie;
    double pret;
    int kilometraj;

public:
    // constructori
    Autoturism() : marca(""), model(""), anFabricatie(0), pret(0), kilometraj(0) {}
    Autoturism(string ma, string mo, int an, double p, int km)
        : marca(ma), model(mo), anFabricatie(an), pret(p), kilometraj(km) {}

    // functii de tip get
    string getMarca() const { return marca; }
    string getModel() const { return model; }
    int getAnFabricatie() const { return anFabricatie; }
    double getPret() const { return pret; }
    int getKilometraj() const { return kilometraj; }

    // functii de tip set
    void setMarca(string ma) { marca = ma; }
    void setModel(string mo) { model = mo; }
    void setAnFabricatie(int an) { if (an > 1885) anFabricatie = an; }
    void setPret(double p) { if (p >= 0) pret = p; }
    void setKilometraj(int km) { if (km >= 0) kilometraj = km; }

    // operator extractor (citire)
    friend istream& operator>>(istream& in, Autoturism& a);
    // operator insertor (afisare)
    friend ostream& operator<<(ostream& out, const Autoturism& a);
};

istream& operator>>(istream& in, Autoturism& a)
{
    cout << "  Marca: ";            in >> a.marca;
    cout << "  Model: ";            in >> a.model;
    cout << "  An fabricatie: ";    in >> a.anFabricatie;
    cout << "  Pret (euro): ";      in >> a.pret;
    cout << "  Kilometraj: ";       in >> a.kilometraj;
    return in;
}

ostream& operator<<(ostream& out, const Autoturism& a)
{
    out << left << setw(12) << a.marca
        << setw(12) << a.model
        << right << setw(6) << a.anFabricatie
        << setw(12) << fixed << setprecision(2) << a.pret
        << setw(10) << a.kilometraj;
    return out;
}

// ---------------------------------------------------------------------------
// Functii pentru citire / afisare
// ---------------------------------------------------------------------------

void citireVector(vector<Autoturism>& v)
{
    int n;
    cout << "Numar de autoturisme: ";
    cin >> n;
    v.clear();
    for (int i = 0; i < n; i++)
    {
        Autoturism a;
        cout << "Autoturismul " << i + 1 << ":\n";
        cin >> a;
        v.push_back(a);
    }
}

void afisareCap()
{
    cout << left << setw(4) << "Nr"
         << setw(12) << "Marca" << setw(12) << "Model"
         << right << setw(6) << "An" << setw(12) << "Pret"
         << setw(10) << "Km" << "\n";
    cout << string(56, '-') << "\n";
}

void afisareVector(const vector<Autoturism>& v)
{
    if (v.empty())
    {
        cout << "Nu exista autoturisme.\n";
        return;
    }
    afisareCap();
    for (size_t i = 0; i < v.size(); i++)
        cout << left << setw(4) << i + 1 << v[i] << "\n";
}

// ---------------------------------------------------------------------------
// P1. Autoturismele unei marci date + pretul mediu al acestora
// ---------------------------------------------------------------------------
double pretMediuMarca(const vector<Autoturism>& v, const string& marca)
{
    double suma = 0;
    int nr = 0;
    for (size_t i = 0; i < v.size(); i++)
        if (v[i].getMarca() == marca)
        {
            if (nr == 0) afisareCap();
            cout << left << setw(4) << nr + 1 << v[i] << "\n";
            suma += v[i].getPret();
            nr++;
        }
    if (nr == 0)
        return -1;          // nu exista autoturisme de marca respectiva
    return suma / nr;
}

// ---------------------------------------------------------------------------
// P2. Cel mai ieftin autoturism fabricat incepand cu un an dat
//     Returneaza pozitia in vector sau -1 daca nu exista.
// ---------------------------------------------------------------------------
int celMaiIeftinDupaAn(const vector<Autoturism>& v, int an)
{
    int poz = -1;
    for (size_t i = 0; i < v.size(); i++)
        if (v[i].getAnFabricatie() >= an)
            if (poz == -1 || v[i].getPret() < v[poz].getPret())
                poz = (int)i;
    return poz;
}

// ---------------------------------------------------------------------------
// P3. Sortare crescatoare dupa pret, la pret egal dupa kilometraj
// ---------------------------------------------------------------------------
bool comparaPretKm(const Autoturism& a, const Autoturism& b)
{
    if (a.getPret() != b.getPret())
        return a.getPret() < b.getPret();
    return a.getKilometraj() < b.getKilometraj();
}

void sortarePret(vector<Autoturism>& v)
{
    sort(v.begin(), v.end(), comparaPretKm);
}

// ---------------------------------------------------------------------------
// Program principal - meniu
// ---------------------------------------------------------------------------
int main()
{
    vector<Autoturism> v;
    int opt;

    do
    {
        cout << "\n========== MENIU ==========\n";
        cout << "1. Citire autoturisme\n";
        cout << "2. Afisare autoturisme\n";
        cout << "3. Modificare pret (set/get)\n";
        cout << "4. P1 - Autoturismele unei marci si pretul mediu\n";
        cout << "5. P2 - Cel mai ieftin autoturism fabricat dupa un an dat\n";
        cout << "6. P3 - Sortare dupa pret (si kilometraj)\n";
        cout << "0. Iesire\n";
        cout << "Optiune: ";
        if (!(cin >> opt)) break;

        switch (opt)
        {
        case 1:
            citireVector(v);
            break;

        case 2:
            afisareVector(v);
            break;

        case 3:
        {
            // exemplu de utilizare a functiilor set/get
            int k;
            double p;
            cout << "Numarul de ordine al autoturismului (1.." << v.size() << "): ";
            cin >> k;
            if (k < 1 || k > (int)v.size())
            {
                cout << "Pozitie invalida.\n";
                break;
            }
            cout << v[k - 1].getMarca() << " " << v[k - 1].getModel()
                 << " are pretul actual " << v[k - 1].getPret() << " euro.\n";
            cout << "Pret nou: ";
            cin >> p;
            v[k - 1].setPret(p);
            cout << "Pretul a devenit " << v[k - 1].getPret() << " euro.\n";
            break;
        }

        case 4:
        {
            string marca;
            cout << "Marca cautata: ";
            cin >> marca;
            double m = pretMediuMarca(v, marca);
            if (m < 0)
                cout << "Nu exista autoturisme marca " << marca << ".\n";
            else
                cout << "Pretul mediu pentru marca " << marca << ": "
                     << fixed << setprecision(2) << m << " euro\n";
            break;
        }

        case 5:
        {
            int an;
            cout << "Anul minim de fabricatie: ";
            cin >> an;
            int poz = celMaiIeftinDupaAn(v, an);
            if (poz == -1)
                cout << "Nu exista autoturisme fabricate din " << an << " incoace.\n";
            else
            {
                cout << "Cel mai ieftin autoturism fabricat din " << an << " incoace:\n";
                afisareCap();
                cout << left << setw(4) << poz + 1 << v[poz] << "\n";
            }
            break;
        }

        case 6:
            sortarePret(v);
            cout << "Autoturismele sortate dupa pret:\n";
            afisareVector(v);
            break;

        case 0:
            cout << "La revedere!\n";
            break;

        default:
            cout << "Optiune invalida.\n";
        }
    } while (opt != 0);

    return 0;
}
