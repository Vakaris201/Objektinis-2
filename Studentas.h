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

double mediana(vector<int>& paz);
double vidurkis(vector<int>& paz);

class Studentas {
private:
    string vardas_;
    string pavarde_;
    vector<int> paz_;
    double egzam_;
    double rez_;

public:
    Studentas() : egzam_(0.0), rez_(0.0) {}
    Studentas(istream& is);
    
    inline string vardas() const { return vardas_; }
    inline string pavarde() const { return pavarde_; }
    inline double egzam() const { return egzam_; }
    inline double rez() const { return rez_; }
    inline const vector<int>& paz() const { return paz_; }
    double galBalas(double (*)(vector<int>&) = mediana);
    void skaiciuotiRez(double (*)(vector<int>&) = mediana);
    istream& readStudent(istream& is);
    
    ~Studentas();                                      // destructor
    Studentas(const Studentas& other);                 // copy constructor
    Studentas(Studentas&& other) noexcept;             // move constructor
    Studentas& operator=(const Studentas& other);      // copy assignment
    Studentas& operator=(Studentas&& other) noexcept;  // move assignment

};

bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b); 
bool comparePagalRez(const Studentas& a, const Studentas& b); 

void rusiavimas(vector<Studentas>& A, int sort_choice);
void print(ostream& os, int pasirinkimas, const vector<Studentas>& A, int stud_skaicius);
void outputas(vector<Studentas> &A, int stud_skaicius, double test_time, string filename);

#endif 