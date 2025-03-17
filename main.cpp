#include <iostream>
#include<vector>
#include<fstream>
using namespace std;

class Statia {
    string nume;
    int timpAsteptare; // timp mediu de așteptare în secunde

public:
    Statia(const string& nume, int timpAsteptare) { // constructor initializare
        this->nume = nume;
        this->timpAsteptare = timpAsteptare;
    }

    friend ostream& operator<<(ostream& os, const Statia& statie) {
        os << "Statia: " << statie.nume << " | Timp asteptare: " << statie.timpAsteptare << " sec";
        return os;
    }

    int getTimpAsteptare() { // getter
        return timpAsteptare;
    }
    string getNume() { // getter
        return nume;
    }
};

class Tren {
    string id;
    int capacitate;
    int viteza; // în km/h

public:
    Tren() {
        id = "Unknown";
        capacitate = 0;
        viteza = 0;
    }

    Tren(const string& id, int capacitate, int viteza) {
        this->id = id;
        this->capacitate = capacitate;
        this->viteza = viteza;
    }

    friend ostream& operator<<(ostream& os, const Tren& tren) {
        os << "Tren ID: " << tren.id << " | Capacitate: " << tren.capacitate
           << " | Viteza: " << tren.viteza << " km/h";
        return os;
    }

    int getViteza(){
        return viteza;
    }
};

class Traseu {
    vector<Statia> statii;
    Tren tren;

public:
    Traseu(const Tren& tren){
        this->tren=tren;
    }

    // Constructor de copiere
    Traseu(const Traseu& other) {
        this->tren=other.tren;
        this->statii=other.statii;
    }

    // Operator= de copiere
    Traseu& operator=(const Traseu& other) {
        if (this != &other) {
            tren = other.tren;
            statii = other.statii;
        }
        return *this;
    }

    // Destructor
    ~Traseu() {}

    void adaugaStatia(const Statia& statie) {
        statii.push_back(statie);
    }

    double calculeazaTimpTotal(){
        double timp = 0;
        for (auto& s : statii) {
            timp += s.getTimpAsteptare();
        }
        return timp;
    }

    friend ostream& operator<<(ostream& os, const Traseu& traseu) {
        os << "Traseu pentru " << traseu.tren << "\nStatii:\n";
        for (const auto& s : traseu.statii) {
            os << "- " << s << "\n";
        }
        return os;
    }
};

class ReteaMetrou {
private:
    vector<Traseu> trasee;
public:
    void adaugaTraseu(const Traseu& traseu) {
        trasee.push_back(traseu);
    }

    void afisareTrasee() const {
        for (const auto& traseu : trasee) {
            cout << traseu << "\n";
        }
    }
};

int main() {
    // Creare rețea de metrou
    ReteaMetrou retea;

    // Creare trenuri
    Tren tren1("M1", 300, 80);
    Tren tren2("M2", 400, 90);

    // Creare traseu
    Traseu traseu1(tren2);
    traseu1.adaugaStatia(Statia("Piata Unirii", 30));
    traseu1.adaugaStatia(Statia("Universitate", 25));
    traseu1.adaugaStatia(Statia("Victoriei", 35));

    // Adăugare traseu în rețea
    retea.adaugaTraseu(traseu1);

    // Afisare informații despre rețea
    cout << "Lista traseelor de metrou:\n";
    retea.afisareTrasee();

    return 0;
}