# Class-repo
Class studento repozitorija

### Class ir struct implimentacijų palyginimas be optimizavimo

#### Struct su vektoriumi

| Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
| ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ |
| studentai_1000     | 0.005        | 0.001       | 0.000        | 0.009    | **0.015**          |
| studentai_10000    | 0.022        | 0.018       | 0.005        | 0.066    | **0.110**          |
| studentai_100000   | 0.203        | 0.235       | 0.047        | 0.623    | **1.106**          |
| studentai_1000000  | 1.996        | 3.073       | 0.513        | 5.796    | **11.574**         |
| studentai_10000000 | 21.078       | 38.997      | 4.927        | 48.976   | **113.979**        |

#### Class

| Failas             | Nuskaitymas | Rikiavimas | Padalijimas | Įrašymas | **Bendras laikas** |
| ------------------ | ------------ | ----------- | ------------ | -------- | ------------------ |
| studentai_1000     |              |             |              |          |                    |
| studentai_10000    |              |             |              |          |                    |
| studentai_100000   |              |             |              |          |                    |
| studentai_1000000  |              |             |              |          |                    |
| studentai_10000000 |              |             |              |          |                    |


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
