#ifndef STUDENTAS_H
#define STUDENTAS_H

#include <iostream>
#include <string>
#include <vector>
#include "Vector.h"
#include <algorithm>
#include <stdexcept>
#include <numeric>
#include <iomanip>
#include "Person.h"

using std::string;
//using std::vector;
template<typename T>
using vector = Vector<T>;
using std::istream;
using std::ostream;
using std::sort;
using std::move;
using std::endl;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::stringstream;
using std::ws;

double mediana(vector<int>& paz);
double vidurkis(vector<int>& paz);


class Studentas : public Zmogus {
private:
    vector<int> paz_;
    double egzam_;
    double rez_;

public:
    Studentas();  // default constructor
    Studentas(string vardas, string pavarde, vector<int> paz, double egzam);  // parameterized constructor
    Studentas(istream& is);

    double egzam() const { return egzam_; }
    double rez() const { return rez_; }
    const vector<int>& paz() const { return paz_; }

    double galBalas() const override;
    void print(ostream& os) const override;
    
    double galBalas(double (*)(vector<int>&) = mediana) const;
    void skaiciuotiRez(double (*)(vector<int>&) = mediana);
    
    ~Studentas() override;                             // destructor
    Studentas(const Studentas& other);                 // copy constructor
    Studentas(Studentas&& other) noexcept;             // move constructor
    Studentas& operator=(const Studentas& other);      // copy assignment
    Studentas& operator=(Studentas&& other) noexcept;  // move assignment
    istream& readStudent(istream& is) override;
    
    string test_eilute();
};

bool compare(const Studentas& a, const Studentas& b);
bool comparePagalPavarde(const Studentas& a, const Studentas& b); 
bool comparePagalRez(const Studentas& a, const Studentas& b); 

void rusiavimas(vector<Studentas>& A, int sort_choice);
void print(ostream& os, int pasirinkimas, const vector<Studentas>& A, int stud_skaicius);
void outputas(vector<Studentas> &A, int stud_skaicius, double test_time, string filename);

#endif 