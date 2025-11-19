# Studentų Rūšiavimo Sistema — v1.2  
*C++ OOP projektas su „Rule of Three“ ir perkrautais operatoriais*

---

## Aprašymas
 
Dabartinėje versijoje `Studentas` yra pilnai įgyvendintos **class** funkcijos:

- Pilnai įgyvendinta **Rule of Three**
- Pridėti perkrauti įvesties/išvesties operatoriai
- Aiškiai apibrėžti getter/setter metodai
- Skaitymas iš vartotojo ir failo
- Strategijos metodas galutinio balo skaičiavimui (vidurkis / mediana)
- Darbas su dideliais duomenų failais: skaidymas, rūšiavimas, rašymas į failą

---

# Studentas klasė

## Rule of Three

| Metodas | Paskirtis |
|--------|-----------|
| `Studentas(const Studentas& other)` | Kuria naują objekto kopiją |
| `Studentas& operator=(const Studentas& other)` | Priskiria vieno objekto reikšmes kitam |
| `~Studentas()` | Destruktorius |


---

## Perkrauti operatoriai

### operator >>
Leidžia skaityti studentą iš:

- vartotojo (`std::cin`)
- failo (`std::ifstream`)

### operator <<  
Leidžia:

- išvesti studentą į ekraną
- išvesti studentą į failą (`std::ofstream`)

---

# Įvesties režimai

### 1. Rankinė įvestis  
Vartotojas įveda:

- vardą  
- pavardę  
- pažymius (su galimybe nurodyti kiek / įvesti nežinant kiek)  
- egzamino pažymį  

### 2. Automatinė pažymių generacija  
Sistema sugeneruoja:

- atsitiktinius namų darbų pažymius  
- atsitiktinį egzamino rezultatą  

### 3. Skaitymas iš failo  

Vardas1 Pavarde1 1 1 1 8 4 4
Vardas2 Pavarde2 1 4 8 8 9 4

Pirmi skaičiai - nd pažymiai, paskutinis skaičius – egzaminas.

![Įvesties foto](images/Ivestis.png)

---

# 📤 Išvestis

Programoje galima išvesti studentus:

- į terminalą
- į failus: `kietiakiai_X.txt`, `vargsiukai_X.txt`

Išvesties formatas:

![Išvesties foto](images/Isvestis.png)


# v1.2 testavimo rezultatai

| Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
|--------------------|-------------|------------|-------------|----------|---------------------|
| studentai_100000   | 1.759 s     | 0.085 s    | 0.028 s     | 0.738 s  | **2.610 s**         |
| studentai_1000000  | 17.687 s    | 1.038 s    | 0.303 s     | 6.910 s  | **25.938 s**        |

![Rezultatai](images/Test_v12.png)
