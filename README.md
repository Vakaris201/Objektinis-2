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
SPARTOS ANALIZE
```
10000
std::vector| 0.0000955  0.0000971  0.0000989  VIDURKIS: 0.0000972
     Vector| 0.0002361  0.0002378  0.0002364  VIDURKIS: 0.0002368
```
```
100000
std::vector| 0.0007214  0.0007328  0.0007481  VIDURKIS: 0.0007341
     Vector| 0.0019603  0.0019655  0.0019742  VIDURKIS: 0.0019667
```
```
1000000
std::vector| 0.0063360  0.0067428  0.0064534  VIDURKIS: 0.0065107
     Vector| 0.0177377  0.0186053  0.0173773  VIDURKIS: 0.0179068
```
```
10000000
std::vector| 0.0717720  0.0660837  0.0660015  VIDURKIS: 0.0679524
     Vector| 0.2280760  0.2284510  0.2289040  VIDURKIS: 0.228477
```
```
100000000
std::vector| 0.659925    0.634871  0.618443   VIDURKIS: 0.637746
     Vector| 1.957130    1.9552    1.93473    VIDURKIS: 1.94902
```