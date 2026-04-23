#include "Studentas.h"
#include "Konstantos.h"

Studentas::Studentas(istream& is) {
    readStudent(is);
}

double mediana(std::vector<double> paz) {
    double mediana;
    if (paz.empty()) {
        return 0;
    }
    std::sort(paz.begin(), paz.end());
    if (paz.size() % 2 == 0) {
        mediana = (paz[paz.size() / 2 - 1] + paz[paz.size() / 2]) / 2.0;
    }
    else {
        mediana = paz[paz.size() / 2];
    }
    return mediana;
}

double vidurkis(std::vector<double> paz) {
    if (paz.empty()) {
        return 0;
    }
    double sum = 0;
    for (int j = 0; j < paz.size(); j++) {
        sum += paz[j];
    }
    return sum / paz.size();
}

double Studentas::galBalas(double (*strategija)(vector<double>)) const {
    if (paz_.empty()) {
        return egzam_ * EGZAM_kof;
    }
    else {
        return strategija(paz_) * ND_kof + egzam_ * EGZAM_kof;
    }
}

void Studentas::skaiciuotiRez(double (*strategija)(vector<double>)) {
    rez_ = galBalas(strategija);
}

istream& Studentas::readStudent(istream& is) {
    paz_.clear();
    egzam_ = 0.0;
    rez_ = 0.0;
    if (!(is >> vardas_ >> pavarde_))
        return is;

    vector<double> visi;
    double val;
    while (is >> val)
        visi.push_back(val);

    if (!visi.empty()) {
        egzam_ = visi.back();
        visi.pop_back();
        paz_ = move(visi);
    }
    skaiciuotiRez();
    is.clear();
    return is;
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
        os << left << setw(15) << A[i].vardas() << left << setw(20) << A[i].pavarde();
        os << setw(10) << fixed << setprecision(2) << A[i].rez() << endl;
    }
}