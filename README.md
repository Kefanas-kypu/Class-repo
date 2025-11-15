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

#### Struct versija (vector)

| Optimizavimas | Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** | .exe dydis |
|-------------- | ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ | ----------- |
| -O1           | studentai_100000   |              |             |              |          |                    |             |
| -O1           | studentai_1000000  |              |             |              |          |                    |             |
| -O2           | studentai_100000   |              |             |              |          |                    |             |
| -O2           | studentai_1000000  |              |             |              |          |                    |             |
| -O3           | studentai_100000   |              |             |              |          |                    |             |
| -O3           | studentai_1000000  |              |             |              |          |                    |             |

#### Class versija (vector)

| Optimizavimas | Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** | .exe dydis |
|-------------- | ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ | ----------- |
| -O1           | studentai_100000   |              |             |              |          |                    |             |
| -O1           | studentai_1000000  |              |             |              |          |                    |             |
| -O2           | studentai_100000   |              |             |              |          |                    |             |
| -O2           | studentai_1000000  |              |             |              |          |                    |             |
| -O3           | studentai_100000   |              |             |              |          |                    |             |
| -O3           | studentai_1000000  |              |             |              |          |                    |             |
