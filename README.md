ĮGYVENDINTA:

1. REALIZUOTA BAZINĖ KLASĖ Zmogus

     Sukurta nauja bazinė klasė Zmogus - Person.h

2. REALIZUOTI VISI "RULE OF FIVE" OPERATORIAI
   
     Destruktorius
     ```
          virtual ~Zmogus() {};
     ```
     Copy konstruktorius 
     ```
          Zmogus(const Zmogus& other) 
          : vardas_(other.vardas_), pavarde_(other.pavarde_) {};
     ```
     Move konstruktorius
     ```  
          Zmogus(Zmogus&& other) noexcept
          : vardas_(move(other.vardas_)), pavarde_(move(other.pavarde_)) {};
     ```
     Copy assignment operatorius 
     ```
          Zmogus& operator=(const Zmogus& other) {
          if(this == &other) return *this;
          vardas_ = other.vardas_;
          pavarde_ = other.pavarde_;
          return *this;
     } 
     ```
     Move assignment operatorius
     ```  
          Zmogus& operator=(Zmogus&& other) noexcept {
          if(this == &other) return *this;
          vardas_ = move(other.vardas_);
          pavarde_ = move(other.pavarde_);
          return *this;
     }
     ```
3. STUDENTO KLASĖS PAKITIMAI

     Derived klasė
     ```
               class Studentas : public Zmogus 
     ```
     Private duomenys
     ```
          private:
               vector<int> paz_;
               double egzam_;
               double rez_;
     ```
     Default konstruktorius
     ```
          Studentas::Studentas() : Zmogus("Test", "Test") {
               paz_ = { 0 };
               egzam_ = 0;
               skaiciuotiRez();
          }
     ```
     Parametrizuotas konstruktorius
     ```
          Studentas::Studentas(string vardas, string pavarde, vector<int> paz, double egzam) : Zmogus(vardas, pavarde) {
               paz_ = paz;
               egzam_ = egzam;
               skaiciuotiRez();
          }
     ```
     Skaitymas
     ```
          Studentas::Studentas(istream& is) : Zmogus() {
               readStudent(is);
          }
     ```
     Print funkcija Studentas klasėje 
     ```
          void print(ostream& os, int pasirinkimas, const vector<Studentas>& A, int stud_skaicius) {
               os << left << setw(15) << "Vardas" << setw(20) << "Pavarde";
               (pasirinkimas == 1)? os << setw(10) << "Galutinis (Vid.)" << endl : os << setw(10) << "Galutinis (Med.)" << endl;

               for (int i = 0; i < stud_skaicius; i++) {
                    os << A[i] << endl;
               }
          }  
     ```
     Destruktorius 
     ``` 
          Studentas::~Studentas() {}
     ```
    Copy konstruktorius   
     ```
          Studentas::Studentas(const Studentas& other) : Zmogus(other) {
               paz_ = other.paz_;
               egzam_ = other.egzam_;
               rez_ = other.rez_;
          }
     ```
     Move konstruktorius 
     ```
          Studentas::Studentas(Studentas&& other) noexcept : Zmogus(move(other)) {
               paz_ = move(other.paz_);
               egzam_ = other.egzam_;
               rez_ = other.rez_;
               other.egzam_ = 0.0;
               other.rez_ = 0.0;
          }
     ```
     Copy assignment operatorius 
     ```
          Studentas& Studentas::operator=(const Studentas& other) { // copy assignment
               if(this == &other) return *this;
               Zmogus::operator=(other);
               paz_ = other.paz_;
               egzam_ = other.egzam_;
               rez_ = other.rez_;
               return *this;
          }
     ```
     Move assignment operatorius
     ```
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
     ```
4. ĮVESTIES/IŠVESTIES OPERATORIAI

Įvesties operatorius: - nukeliamas į Person.h
```
     friend istream& operator>>(istream& is, Zmogus& z) {
          return z.readStudent(is);
     }
```
Išvesties operatorius:
```
     friend ostream& operator<<(ostream& os, const Zmogus& z) {
          z.print(os); 
          return os;
     }
```
5. VISI METODAI IŠTESTUOTI IR TESTAVIMO ATVEJAI SĖKMINGI

TESTUOJAMI:
```
    1. Default konstruktorius
    2. Parametrizuotas konstruktorius
    3. Copy konstruktorius
    4. Move konstruktorius
    5. Copy assignment operatorius
    6. Move assignment operatorius
    7. Destruktorius
    8. Get'eriai
    9. Įvesties/išvesties operatoriai
```
![test2](https://github.com/Vakaris201/Objektinis-2/blob/v1.2/nuotraukos/test2.png)
![test](https://github.com/Vakaris201/Objektinis-2/blob/v1.2/nuotraukos/test.png)



