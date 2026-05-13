#include <iostream>
#include <algorithm>
#include <numeric>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <stdexcept>
#include "Funkcijos.h"

using std::cout;
using std::cin;
using std::sort;
using std::vector;
using std::deque;
using std::list;
using std::string;
using std::endl;
using std::left;
using std::setw;
using std::fixed;
using std::setprecision;
using std::chrono::high_resolution_clock;
using std::chrono::duration;
using std::ofstream;

void clearInput() {
    cout << "Neteisinga ivestis. ";
    cin.clear();
    cin.ignore(10000, '\n');
}

void vidurkis(studentas &S) {
    if (S.paz.empty()) {
        S.rez = S.egzam * 0.6;
    }    
    else {
        double sum = 0;
        for(int j = 0; j < S.paz.size(); j++) {
            sum += S.paz[j];
        }
        S.rez = sum / S.paz.size() * 0.4 + S.egzam * 0.6;
    }
}

void mediana(studentas &S) {
    double mediana;
    if (S.paz.empty()) {
        S.rez = S.egzam * 0.6;
    } 
    else {
        sort(S.paz.begin(), S.paz.end());
        if(S.paz.size() % 2 == 0) {
            mediana = (S.paz[S.paz.size() / 2 - 1] + S.paz[S.paz.size() / 2]) / 2.0;
        } 
        else {
            mediana = S.paz[S.paz.size() / 2];
        }
        S.rez = mediana * 0.4 + S.egzam * 0.6;
    }
}

void rusiavimas(vector<studentas> &A, int sort_choice) {
    if(sort_choice == 1) {
        sort(A.begin(), A.end(), [](studentas& a, studentas& b) {
            return compare(a.vardas, b.vardas);
        });
    }
    else if(sort_choice == 2) {
        sort(A.begin(), A.end(), [](studentas& a, studentas& b) {
            return compare(a.pavarde, b.pavarde);
        });
    }
    else {
        sort(A.begin(), A.end(), [](studentas& a, studentas& b) {
            return compare(b.rez, a.rez);
        });
    }
}

void rusiavimas(deque<studentas> &A, int sort_choice) {
    if(sort_choice == 1) {
        sort(A.begin(), A.end(), [](studentas& a, studentas& b) {
            return compare(a.vardas, b.vardas);
        });
    }
    else if(sort_choice == 2) {
        sort(A.begin(), A.end(), [](studentas& a, studentas& b) {
            return compare(a.pavarde, b.pavarde);
        });
    }
    else {
        sort(A.begin(), A.end(), [](studentas& a, studentas& b) {
            return compare(b.rez, a.rez);
        });
    }
}

void rusiavimas(list<studentas> &A, int sort_choice) {
    if(sort_choice == 1) {
        A.sort([](studentas& a, studentas& b) {
            return compare(a.vardas, b.vardas);
        });
    }
    else if(sort_choice == 2) {
        A.sort([](studentas& a, studentas& b) {
            return compare(a.pavarde, b.pavarde);
        });
    }
    else {
        A.sort([](studentas& a, studentas& b) {
            return compare(b.rez, a.rez);
        });
    }
}

string raide_choice(const string& prompt1) {
    string choice;
    while(true) {
        try {
            cin >> choice;
            if(choice != "t" && choice != "T" && choice != "n" && choice != "N") {
                throw std::runtime_error(prompt1);
            }
            return choice;
        }
        catch (std::exception& e) {
            clearInput();
            cout << e.what() << ": ";
            continue;
        }
    }
}

string getWordInput(const string& prompt1, const string& prompt2) {
    string input;
    while(true) {
        try {
            cout << prompt1;
            cin >> input;
            for(char c : input) {
                if(!isalpha(c)) {
                    throw std::runtime_error(prompt2);
                }
            }
            return input;
        }
        catch (std::exception& e) {
            clearInput();
            cout << e.what() << endl;
            continue;
        }
    }
}

void print(std::ostream& os, int pasirinkimas, vector<studentas>& A, int stud_skaicius) {
    os << left << setw(15) << "Vardas" << left << setw(20) << "Pavarde";
    (pasirinkimas == 1)? os << setw(10) << "Galutinis (Vid.)" << endl : os << setw(10) << "Galutinis (Med.)" << endl;
    for(int i = 0; i < stud_skaicius; i++) {
        os << left << setw(15) << A[i].vardas << left << setw(20) << A[i].pavarde;
        os << setw(10) << fixed << setprecision(2) << A[i].rez << endl;
    }
}

void print(std::ostream& os, int pasirinkimas, deque<studentas>& A, int stud_skaicius) {
    os << left << setw(15) << "Vardas" << left << setw(20) << "Pavarde";
    (pasirinkimas == 1)? os << setw(10) << "Galutinis (Vid.)" << endl : os << setw(10) << "Galutinis (Med.)" << endl;
    for(int i = 0; i < stud_skaicius; i++) {
        os << left << setw(15) << A[i].vardas << left << setw(20) << A[i].pavarde;
        os << setw(10) << fixed << setprecision(2) << A[i].rez << endl;
    }
}

void print(std::ostream& os, int pasirinkimas, list<studentas>& A, int stud_skaicius) {
    os << left << setw(15) << "Vardas" << left << setw(20) << "Pavarde";
    (pasirinkimas == 1)? os << setw(10) << "Galutinis (Vid.)" << endl : os << setw(10) << "Galutinis (Med.)" << endl;
    int i = 0;
    for(studentas& s : A) {
        if(i >= stud_skaicius) {
            break;
        }
        os << left << setw(15) << s.vardas << left << setw(20) << s.pavarde;
        os << setw(10) << fixed << setprecision(2) << s.rez << endl;
        i++;
    }
}

void failu_generavimas(const string& filename) {
    int dydis = stoi(filename);
    auto start = high_resolution_clock::now();
    ofstream fout(filename);
    fout << setw(16) << left << "Vardas" << setw(17) << left << "Pavarde" << setw(10) << "ND1" << setw(10) << "ND2" << setw(10) << "ND3" << setw(10) << "ND4" << setw(10) << "ND5" << setw(10) << "Egzaminas" << endl;
    for(int i = 0; i < dydis; i++) {
        fout <<  "Vardas" << setw(10) << left << i + 1 << "Pavarde" << setw(10) << left << i + 1;
        for(int j = 0; j < 5; j++) {
            fout << setw(10) << left << rand() % 10 + 1;
        }
        fout << setw(10) << left << rand() % 10 + 1 << endl;
    }
    fout.close();
    auto end = high_resolution_clock::now();
    duration<double> diff = end - start;
    cout << "Failo generavimo laikas: " << diff.count() << endl;
}