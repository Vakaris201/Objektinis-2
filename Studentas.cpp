#include "Studentas.h"

Studentas::Studentas(istream& is) {
    readStudent(is);
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

