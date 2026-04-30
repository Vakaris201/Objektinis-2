#include "Studentas.h"
#include <sstream>

Studentas::Studentas() : Zmogus("Test", "Test") {
    paz_ = { 0 };
    egzam_ = 0;
    skaiciuotiRez();
}

Studentas::Studentas(string vardas, string pavarde, vector<int> paz, double egzam) : Zmogus(vardas, pavarde) {
    paz_ = paz;
    egzam_ = egzam;
    skaiciuotiRez();
}

Studentas::Studentas(istream& is) : Zmogus() {
    readStudent(is);
}

double mediana(std::vector<int>& paz) {
    double med;
    if (paz.empty()) {
        return 0;
    }
    std::sort(paz.begin(), paz.end());
    if (paz.size() % 2 == 0) {
        med = (paz[paz.size() / 2 - 1] + paz[paz.size() / 2]) / 2.0;
    }
    else {
        med = paz[paz.size() / 2];
    }
    return med;
}

double vidurkis(std::vector<int>& paz) {
    if (paz.empty()) {
        return 0;
    }
    double sum = 0;
    for (int j = 0; j < paz.size(); j++) {
        sum += paz[j];
    }
    return sum / paz.size();
}

double Studentas::galBalas() const {
    if (paz_.empty()){
        return egzam_ * 0.6;
    }
    else {    
        vector<int> kopija;
        kopija.reserve(paz_.size());
        for (int pazymys : paz_) {
            kopija.push_back(pazymys);
        }
        return mediana(kopija) * 0.4 + egzam_ * 0.6;
    }
}

double Studentas::galBalas(double (*strategija)(vector<int>&)) const{
    if (paz_.empty()) {
        return egzam_ * 0.6;
    }
    else {
        vector<int> kopija;
        kopija.reserve(paz_.size());
        for (int pazymys : paz_) {
            kopija.push_back(pazymys);
        }
        return strategija(kopija) * 0.4 + egzam_ * 0.6;
    }
}

void Studentas::skaiciuotiRez(double (*strategija)(vector<int>&)) {
    rez_ = galBalas(strategija);
}

istream& Studentas::readStudent(istream& is) {
    paz_.clear();
    egzam_ = 0.0;
    rez_ = 0.0;
    string line;
    if (!getline(is >> ws, line))
        return is;
    stringstream ss(line);
    if (!(ss >> vardas_ >> pavarde_))
        return is;
    int val;
    while (ss >> val) {
        paz_.push_back(val);
    }
    if (!paz_.empty()) {
        egzam_ = paz_.back();
        paz_.pop_back();
    }
    return is;
}

Studentas::~Studentas() {}  // destructor

Studentas::Studentas(const Studentas& other) : Zmogus(other) { // copy constructor
    paz_ = other.paz_;
    egzam_ = other.egzam_;
    rez_ = other.rez_;
}

Studentas::Studentas(Studentas&& other) noexcept : Zmogus(move(other)) {  // move constructor
    paz_ = move(other.paz_);
    egzam_ = other.egzam_;
    rez_ = other.rez_;
    other.egzam_ = 0.0;
    other.rez_ = 0.0;
}
Studentas& Studentas::operator=(const Studentas& other) { // copy assignment
    if(this == &other) return *this;
    Zmogus::operator=(other);
    paz_ = other.paz_;
    egzam_ = other.egzam_;
    rez_ = other.rez_;
    return *this;
}

Studentas& Studentas::operator=(Studentas&& other) noexcept { //  move assignment
    if (this == &other) return *this;
    Zmogus::operator=(move(other));
    paz_ = move(other.paz_);
    egzam_ = other.egzam_;
    rez_ = other.rez_;
    other.egzam_ = 0.0;
    other.rez_ = 0.0;
    return *this;
}

void Studentas::print(ostream& os) const {
    os << left << setw(15) << vardas() << left << setw(20) << pavarde();
    os << setw(10) << fixed << setprecision(2) << rez();
}

bool compare(const Studentas& a, const Studentas& b) {
    return a.vardas() < b.vardas();
}

bool comparePagalPavarde(const Studentas& a, const Studentas& b) {
    return a.pavarde() < b.pavarde();
}

bool comparePagalRez(const Studentas& a, const Studentas& b) {
    return a.rez() > b.rez();
}

void rusiavimas(vector<Studentas>& A, int sort_choice) {
    if (sort_choice == 1) {
        sort(A.begin(), A.end(), compare);
    }
    else if (sort_choice == 2) {
        sort(A.begin(), A.end(), comparePagalPavarde);
    }
    else if (sort_choice == 3) {
        sort(A.begin(), A.end(), comparePagalRez);
    }
}

void print(ostream& os, int pasirinkimas, const vector<Studentas>& A, int stud_skaicius) {
    os << left << setw(15) << "Vardas" << setw(20) << "Pavarde";
    (pasirinkimas == 1)? os << setw(10) << "Galutinis (Vid.)" << endl : os << setw(10) << "Galutinis (Med.)" << endl;

    for (int i = 0; i < stud_skaicius; i++) {
        os << A[i] << endl;
    }
}

string Studentas::test_eilute() {
    string eil;
    eil += vardas_ + " " + pavarde_;
    return eil;
}

