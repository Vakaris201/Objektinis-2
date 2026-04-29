ĮGYVENDINTA:

1. REALIZUOTI VISI "RULE OF FIVE" OPERATORIAI
   
   Destruktorius - atlaisvina vektoriaus atmintį
   
        ~Studentas();
   
   Copy konstruktorius - sukuria naują objektą kaip kito objekto kopiją:
       
        Studentas(const Studentas& other);
   
   Move konstruktorius - sukuria naują objektą „pasiimdamas“ duomenis iš kito objekto:
       
        Studentas(Studentas&& other) noexcept
   
   Copy assignment operatorius - priskiria vieno jau egzistuojančio objekto duomenis kitam:

        Studentas& operator=(const Studentas& other); 
   
   Move assignment operatorius - perkelia vieno jau egzistuojančio objekto duomenis kitam:
        
        Studentas& operator=(Studentas&& other) noexcept;
   
2. REALIZUOTI ĮVESTIES/IŠVESTIES OPERATORIAI

Įvesties operatorius:
```
istream& operator>>(istream& is, Studentas& student) {
    return student.readStudent(is);
}
```
Išvesties operatorius:
```
ostream& operator<<(ostream& os, const Studentas& student) {
    os << left << setw(15) << student.vardas() << left << setw(20) << student.pavarde();
    os << setw(10) << fixed << setprecision(2) << student.rez();
    return os;
}
```

ĮVESTIES BŪDAI:

Rankinis įvedimas - Vartotojas rankiniu būdu įveda kiekvieno studento vardą, pavardę, kiekvieną namų darbų pažymį ir egzamino pažymį.<br>
```
Iveskite varda: Vardenis
Iveskite pavarde: Pavardenis
Iveskite 1 semestro pazymi (0 - baigti): 8
Iveskite 2 semestro pazymi (0 - baigti): 9
Iveskite 3 semestro pazymi (0 - baigti): 0
Iveskite egzamino pazymi: 10
```
Automatinis įvedimas - Programa automatiškai sugeneruoja vardą, pavardę (iš Zmones.h vardų sąrašo) ir visus pažymius.<br>
```
zmogus z = gen();
vard  = z.vardas;
pavard = z.pavarde;
```
Įvedimas iš failo - Kiekviena eilutė nuskaitoma iš failo ir perduodama per operator>>.<br>
```
A.reserve(10000000);
stringstream ss;
while(getline(fin, line)) {
    ss.clear();
    ss.str(line);
    Studentas S;
    ss >> S;
    A.push_back(move(S));
}
```
IŠVESTIES BŪDAI:

Į ekraną:
```
print(cout, grade_choice, A, stud_skaicius);
```
Į failą:
```
ofstream fout("rezultatai.txt");
print(fout, grade_choice, A, stud_skaicius);
```
Į 2 failus:
```
ofstream v_fout("vargsiukai.txt");
ofstream k_fout("kietiakai.txt");
print(v_fout, grade_choice, vargsiukai, vargsiukai.size());
print(k_fout, grade_choice, A, A.size());
```
3. REALIZUOTAS IR IŠBANDYTAS TESTAVIMAS, VISI TESTAVIMO ATVEJAI SĖKMINGI

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



