#ifndef FUNKCIJOS_H
#define FUNKCIJOS_H

#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <string>
#include <stdexcept>

using std::vector;
using std::deque;
using std::list;
using std::string;
using std::cin;
using std::cout;
using std::endl;

struct studentas {
    string vardas;
    string pavarde;
    vector<int> paz;
    int egzam;
    double rez;
};

void clearInput();
void vidurkis(studentas &S);
void mediana(studentas &S);
void rusiavimas(vector<studentas> &A, int sort_choice);
void rusiavimas(deque<studentas> &A, int sort_choice);
void rusiavimas(list<studentas> &A, int sort_choice);
void outputas(vector<studentas> &A, int stud_skaicius, double test_time, string filename);
void outputas(deque<studentas> &A, int stud_skaicius, double test_time, string filename);
void outputas(list<studentas> &A, int stud_skaicius, double test_time, string filename);
string raide_choice(string prompt1);
string getWordInput(string prompt1, string prompt2);
void print(std::ostream& os, int pasirinkimas, vector<studentas>& A, int stud_skaicius);
void print(std::ostream& os, int pasirinkimas, deque<studentas>& A, int stud_skaicius);
void print(std::ostream& os, int pasirinkimas, list<studentas>& A, int stud_skaicius);
void failu_generavimas(string filename);


template <typename T>
bool compare(T &a,T &b) {
    return a < b;
}

template <typename T, int Arg1 = INT_MIN, int Arg2 = INT_MAX>
T getInput(string prompt1, string prompt2) {
    T input;
    while(true) {
        try {
            cout << prompt1;
            cin >> input;
            if(cin.fail() || input < Arg1 || input > Arg2) {
                throw std::runtime_error(prompt2);
            }
            return input;
        }
        catch(std::exception& e) {
            clearInput();
            cout << e.what() << endl;
            continue;
        }
    }
}

#endif
