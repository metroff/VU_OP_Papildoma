# VU Papildoma užduotis
### Programa skirta teksto failų apdorojimui. Pagrindinės funkcijos:
- Suskaičiuoja kiek kartų tam tikras žodis pasikartoja tekste ir išveda tai į lentele.
- Sukuria žodžių ir eilučių cross-reference lentelę.
- Suranda visas nuorodas (URL) ir išveda į atskirą failą.

## Naudojimosi instrukcija

Paleidus programą, komandinėje eilutėje reikės:

* Įrašyti teksto failo pavadinimą.
* Pasirinkti žodžių įrašymo tipą.

## Programos pavyzdys

1. Įrašomas tekstinio failo pavadinimas.
```shell
>> Irasykite failo pavadinima: text.txt
```
2. Pasirenkamas žodžių įrašymo tipas.
```shell
>> Keisti raides i mazasias?  (y/n): y
```

Programa apdoroja tekstinį failą ir pateikia tris naujus failus:

## word_table failas
```
Word                  Count
--------------------------------
a                     	52
about                 	7
according             	5
act                   	4
adopted               	2
after                 	19
again                 	5
against               	5
agreement             	3
agreements            	2
ak                    	2
all                   	2
```
Čia pateikiami visi žodžiai, kurie pasikartojo daugiau nei vieną kartą, taip pat jų pasikartojimų kiekis.

## cross_reference failas
```
Word                 	  1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  17  18  19  20  21  22  23  24  25  26  27  28  29  30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45  46  47  48  49  50  51  52  53  54  55  56  57  58  59  60  61  62  63  64  65  66  67  68  69  70  71  72  73  74  75  76  77  78  79  80  81  82  83  84  85  86  87  88  89  90  91  92  93  94  95  96  97  98  99 100 101 102 103 104 105 106 107 108 109 110 111 112 113 114 
a                    	      *       *       *                       *       *               *       *           *               *                   *                                           *   *                   *               *                                               *       *   *           *       *                           *               *           *       *                                   *       *                   *           *       *       * 
about                	      *                                                                                                                                   *                               *                                                                                                               *                           *                                   * 
according            	      *       *                               *                                                                                                                                                                   *                                                                       * 
act                  	                                                                                                                                                                                                                                  *           *                                                                       *                                                                                               * 
adopted              	                                                                                                                                                                                                                                  *                                                                                   * 
after                	                                              *                       *       *                                               *                                                                   *               *                                               *       *               *                   *       *               *       *                   *                           *                       * 
again                	                                                                                                                                                                                                  *                                                               *                                                                                                                   *               * 
against              	                                                                                                                                                                                                                                                                  *                                                                                       *       *                   *                                                                       * 
agreement            	                                                                                                                                                                                                                                                                          * 
agreements           	                                                                                                                                                                                                                                                                                                                                                                                                                                                                      * 
```
Čia pateikiami visi žodžiai, kurie pasikartojo daugiau nei vieną kartą, bei eilutės numeris, kuriame yra žodis.

## urls failas
```
https://en.wikipedia.org/wiki/Vilnius
http://www.vu.lt
github.com/metroff/VU_OP_Papildoma
randomlink.com
www.delfi.lt
```
Čia pateikiami visos tekste rastos nuorodos.

## Įdiegimo instrukcija

1. Iš [Releases](https://github.com/metroff/VU_OP_Papildoma/releases) aplanko parsisiųskite vieną iš programos versijų ir ją išsiarchyvuokite.
2. Susikompiliuoti `main.cpp` failą naudojant įrankius, kurie palaiko **C++11**.
    - Naudojant g++ įrankį (Linux aplinkoje):
    ```
    g++ -std=c++11 main.cpp -o main && ./main
    ```
3. Pasileisti sukompiliuotą failą.