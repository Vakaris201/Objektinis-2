#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <iomanip>

using std::string;
using std::vector;
using std::istream;
using std::ostream;
using std::sort;
using std::move;
using std::endl;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;

double mediana(vector<double> paz);
double vidurkis(vector<double> paz);

class Studentas {
private:
    string vardas_;
    string pavarde_;
    vector<double> paz_;
    double egzam_;
    double rez_;

public:
    Studentas() : egzam_(0.0), rez_(0.0) {}
    Studentas(istream& is);
    
    inline string vardas() const { return vardas_; }
    inline string pavarde() const { return pavarde_; }
    inline double egzam() const { return egzam_; }
    inline double rez() const { return rez_; }
    inline const vector<double>& paz() const { return paz_; }
    double galBalas(double (*)(vector<double>) = mediana) const;
    void skaiciuotiRez(double (*)(vector<double>) = mediana);
    istream& readStudent(istream& is);
    
    ~Studentas() = default;
};

bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b); 
bool comparePagalRez(const Studentas& a, const Studentas& b); 

void rusiavimas(vector<Studentas>& A, int sort_choice);
void print(ostream& os, int pasirinkimas, const vector<Studentas>& A, int stud_skaicius);
void outputas(vector<Studentas> &A, int stud_skaicius, double test_time, string filename);


#endif 