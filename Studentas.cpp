#include "Studentas.h"

Studentas::Studentas(istream& is) {
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

double Studentas::galBalas(double (*strategija)(vector<int>&)) {
    if (paz_.empty()) {
        return egzam_ * 0.6;
    }
    else {
        return strategija(paz_) * 0.4 + egzam_ * 0.6;
    }
}

void Studentas::skaiciuotiRez(double (*strategija)(vector<int>&)) {
    rez_ = galBalas(strategija);
}

istream& Studentas::readStudent(istream& is) {
    paz_.clear();
    egzam_ = 0.0;
    rez_ = 0.0;
    if (!(is >> vardas_ >> pavarde_))
        return is;
    int val;
    while (is >> val)
        paz_.push_back(val);

    if (!paz_.empty()) {
        egzam_ = paz_.back();
        paz_.pop_back();
    }
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