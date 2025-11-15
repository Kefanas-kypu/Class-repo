# Class-repo
Class studento repozitorija

### Class ir struct implimentacijų palyginimas be optimizavimo

#### Struct su vektoriumi

| Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
| ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ |
| studentai_100000   | 0.203        | 0.235       | 0.047        | 0.623    | **1.106**          |
| studentai_1000000  | 1.996        | 3.073       | 0.513        | 5.796    | **11.574**         |


#### Class

| Failas           | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
|------------------|-------------|------------|-------------|----------|---------------------|
| studentai_100000 | 1.8058 s    | 0.4484 s   | 0.0518 s    | 0.7406 s | **3.0464 s**        |
| studentai_1000000| 18.1778 s   | 5.8564 s   | 0.6142 s    | 6.1636 s | **30.8118 s**       |


### Optimizavimo flag'ų palyginimas

#### Class versija (vector)


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

### Struct versija (vector)

