# Class-repo
Class studento repozitorija

### Class ir struct implimentacijų palyginimas be optimizavimo ir su optimizavimu

## Struct analizė

### EXE failo dydžių palyginimas 

| Versija | Flag'as | EXE dydis (KB) |
|--------|---------|----------------|
| struct | -O1     | ~329.6 KB      |
| struct | -O2     | ~321.5 KB      |
| struct | -O3     | ~390.9 KB      |


### Struct su vektoriumi

| Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
| ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ |
| studentai_100000   | 0.203        | 0.235       | 0.047        | 0.623    | **1.106**          |
| studentai_1000000  | 1.996        | 3.073       | 0.513        | 5.796    | **11.574**         |


### Optimizavimas `-O1`

| Failas            | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
|-------------------|-------------|------------|-------------|----------|---------------------|
| studentai_100000  | 0.2046 s    | 0.0398 s   | 0.0390 s    | 0.9118 s | **1.1948 s**        |
| studentai_1000000 | 1.7640 s    | 0.3708 s   | 0.3268 s    | 5.5450 s | **8.0062 s**        |


### Optimizavimas `-O2`

| Failas            | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
|-------------------|-------------|------------|-------------|----------|---------------------|
| studentai_100000  | 0.1972 s    | 0.0456 s   | 0.0414 s    | 0.9398 s | **1.2242 s**        |
| studentai_1000000 | 2.0266 s    | 0.4896 s   | 0.3746 s    | 6.2920 s | **9.1828 s**        |


### Optimizavimas `-O3`

| Failas            | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
|-------------------|-------------|------------|-------------|----------|---------------------|
| studentai_100000  | 0.1692 s    | 0.0360 s   | 0.0424 s    | 0.7458 s | **0.9934 s**        |
| studentai_1000000 | 1.7014 s    | 0.3724 s   | 0.3296 s    | 5.4842 s | **7.8880 s**        |


## Class analizė 

### EXE failo dydžių palyginimas su class

| Versija | Flag'as | EXE dydis (KB) |
|--------|---------|----------------|
| class  | -O1     | ~270.0 KB      |
| class  | -O2     | ~256.5 KB      |
| class  | -O3     | ~343.8 KB      |


### Class su vektoriumi

| Failas           | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
|------------------|-------------|------------|-------------|----------|---------------------|
| studentai_100000 | 1.8058 s    | 0.4484 s   | 0.0518 s    | 0.7406 s | **3.0464 s**        |
| studentai_1000000| 18.1778 s   | 5.8564 s   | 0.6142 s    | 6.1636 s | **30.8118 s**       |


### Optimizavimas: `-O1`

| Failas            | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
|-------------------|-------------|------------|-------------|----------|---------------------|
| studentai_100000  | 1.6896 s    | 0.0608 s   | 0.0250 s    | 0.6552 s | **2.4306 s**        |
| studentai_1000000 | 16.8806 s   | 0.9298 s   | 0.2682 s    | 6.0148 s | **24.0936 s**       |


### Optimizavimas: `-O2`

| Failas            | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
|-------------------|-------------|------------|-------------|----------|---------------------|
| studentai_100000  | 1.6835 s    | 0.0580 s   | 0.0255 s    | 0.6988 s | **2.4653 s**        |
| studentai_1000000 | 17.0110 s   | 0.8783 s   | 0.2998 s    | 6.6080 s | **24.7968 s**       |


### Optimizavimas: `-O3`

| Failas            | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
|-------------------|-------------|------------|-------------|----------|---------------------|
| studentai_100000  | 1.6880 s    | 0.0472 s   | 0.0224 s    | 0.5690 s | **2.3268 s**        |
| studentai_1000000 | 17.0484 s   | 0.8498 s   | 0.2620 s    | 5.5288 s | **23.6886 s**       |


### Optimizavimo flag'ų palyginimas

Struct versija su std::vector yra akivaizdžiai spartesnė už class versiją visuose optimizacijos būduose. Iš optimizavimo flag’ų praktiškai geriausi rezultatai gauti su -O3. Apskritai naudoti optimizacijos būdai yra greitesni už paprastą naudojimą be optimizacijos, nes jie leidžia kompiliatoriui agresyviau optimizuoti kodą ir sumažinti vykdymo laiką, ypač dirbant su dideliais duomenų failais.