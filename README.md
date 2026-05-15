PALEIDIMO INSTRUKCIJA
1) Atidarykite terminal projekto kataloge.
2) Sugeneruokite build failus i build aplanka:
```
cmake -S . -B build
```
3) Sukompiliuokite programa:
```
cmake --build build
```
4) Ieikite i build aplanka:
```
cd build
```
5) Ieikite i debug aplanka:
```
cd debug
```
6) Paleiskite norima programa:
```
./main
```
arba
```
./testai
```

NAUDOJIMOSI INSTRUKCIJA 
1. Darbo eiga / Naudojimas

Programa paklaus: "Ar noretumet skaityti duomenis is failo? (t/n)"
Jei atsakote `t`, bus paprašyta nurodyti failo pavadinimą. Programa perskaitys visus įrašus ir apdoros rezultatus.

2. Jei atsakote `n`, matysite meniu:
```
1 - ranka: vėliau bus prašoma vardo, pavardės ir pažymių
2 - generuoti tik pažymius: programa sugeneruos nurodytą kiekį pažymių
3 - generuoti studentų vardus, pavardes ir pažymius
4 - baigti darbą
5 - failo generavimas: programa paklaus kiek įrašų faile norėtumėte, ir sukurs failus pavadinimais <skaicius>.txt
```
3. Po duomenų surinkimo programa prašys pasirinkti, kaip skaičiuoti galutinį balą:
```
1 - vidurkis
2 - mediana
```
4. Programa paklaus ar norite atskirti vargsiukus nuo kietiaku (`t/n`). Jei taip, galimi skaidymo metodai:
```
1 - du nauji konteineriai
2 - vienas naujas konteineris 
3 - efektyvus darbas su konteineriais 
```
5. Rušiavimo pasirinkimai:
```
1 - pagal vardą
2 - pagal pavardę
3 - pagal galutinį balą.
```
6. Išvedimas
```
1 - į ekraną
2 - į failą (rezultatai.txt)
Jei pasirenkate atskyrimo funkcionalumą, rezultatai bus rašomi į vargsiukai.txt ir kietiakai.txt
```
RELEASE APRAŠAS
1. v1.1
```
Šioje versijoje programa buvo refaktorinta iš Studentas struktūros i klasę.
```
2. v1.2
```
Šioje versijoje buvo realizuoti ir įgyvendinti visi "Rule of five" bei įvesties/išvesties operatoriai.
Taip pat buvo realizuoti unit testai patikrinti visus metodus.
```
3. v1.5
```
Šioje versijoje buvo realizuota bazinė klasė Zmogus ir klasė Studentas tapo išvestine.
Zmogus klasėje taip pat realizuoti ir įgyvendinti visi "Rule of five" metodai.
įvesties/išvesties operatoriai tapo friend.
Visi metodai buvo patikrinti unit testais.
```
4. v2.0
```
Šioje versijoje buvo sukurta programos dokumentacija.
Unit testai pakeičiami į google testus.
Atnaujinamas cmakelists file'as naujam programos release'ui su veikiančiais testais.
```
