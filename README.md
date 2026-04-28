ĮGYVENDINTA:

1. Realizuoti visi "Rule of five" operatoriai:
```
    1. Destruktorius - atlaisvina paz_ vektoriu:
        ~Studentas(); 
    2. Copy konstruktorius - sukuria naują objektą kaip kito objekto kopiją:
        Studentas(const Studentas& other);
    3. Move konstruktorius - sukuria naują objektą „pasiimdamas“ resursus iš kito objekto:
        Studentas(Studentas&& other) noexcept;
    4. Copy assignment operatorius - priskiria vieno jau egzistuojančio objekto duomenis kitam:
        Studentas& operator=(const Studentas& other);
    5. Move assignment operatorius - perkelia vieno jau egzistuojančio objekto resursus kitam:
        Studentas& operator=(Studentas&& other) noexcept;
```
2. Realizuoti įvesties/išvesties operatoriai
```
DUOMENŲ ĮVESTIS:
istream& operator>>(istream& is, Studentas& student) { - perduoda duomenis į Studentas klasę per readStudent().
    return student.readStudent(is);
} 
Įvesties būdai:
1. Rankinis įvedimas - duomenys suvedami klaviatūra interaktyviai.
2. Automatinis įvedimas - programa sugeneruoja vardą, pavardę ir pažymius.
3. Įvedimas iš failo - kiekviena eilutė nuskaitoma iš .txt failo ir perduodama per operator>>.

DUOMENŲ IŠVESTIS:
ostream& operator<<(ostream& os, const Studentas& student) { - išveda Studentas objekto duomenis.
    os << left << setw(15) << student.vardas() << left << setw(20) << student.pavarde();
    os << setw(10) << fixed << setprecision(2) << student.rez();
    return os;
}
Išvesties būdai:
1. Į ekraną - naudojamas cout << S; arba print(cout, ...).
2. Į failą - naudojamas fout << S; arba print(fout, ...), kai rezultatai rašomi į .txt failą.
```
3. Realizuotas ir išbandytas testavimas, visi testavimo atvejai sėkmingi
```
TESTUOJAMI:
    1. Default konstruktorius
    2. Parametrizuotas konstruktorius
    3. Copy konstruktorius
    4. Move konstruktorius
    5. Copy assignment operatorius
    6. Move assignment operatorius
    7. Destruktorius
    8. Get'eriai
    9. Įvesties/išvesties operatoriai
![test2](https://github.com/Vakaris201/Objektinis-2/blob/v1.2/nuotraukos/test2.png)
![test](https://github.com/Vakaris201/Objektinis-2/blob/v1.2/nuotraukos/test.png)
```



