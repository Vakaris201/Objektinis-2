#ifndef ZMOGUS_H
#define ZMOGUS_H

#include <iostream>
#include <string>

using std::string;
using std::istream;
using std::ostream;

class Zmogus {
protected:
    string vardas_;
    string pavarde_;

public:
    Zmogus() : vardas_(), pavarde_() {};
    Zmogus(string vardas, string pavarde) : vardas_(vardas), pavarde_(pavarde) {}

    virtual string vardas() const { return vardas_;  }
    virtual string pavarde() const { return pavarde_; }

    virtual double galBalas() const = 0;
    virtual istream& readStudent(istream& is) = 0;
    virtual void print(ostream& os) const = 0;


    friend istream& operator>>(istream& is, Zmogus& z) {
        return z.readStudent(is);
    }
    friend ostream& operator<<(ostream& os, const Zmogus& z) {
        z.print(os); 
        return os;
    }
};

#endif