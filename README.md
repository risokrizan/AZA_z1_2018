Plocha je štvorcová sieť obsahujúcu n x m políčok. Každému políčku prislúcha prirodzene dvojica (x,y), kde 0<=x<n a 0<=y<m. Políčka sú dvoch typov: zakázané a povolené. Po políčkach sa pohybuje panáčik. Pre jeho pohyb platia nasledujúce pravidlá. Ak sa zmenilo políčko panáčika v minulom ťahu o (dx1, dy1), v nasledujúcom ťahu sa môže zmeniť o jednu z nasledujúcich hodnôt (dx2,dy2): (dx1-1,dy1-1), (dx1-1,dy1+0), (dx1-1,dy1+1) (dx1+0,dy1-1), (dx1+0,dy1+0), (dx1+0,dy1+1) (dx1+1,dy1-1), (dx1+1,dy1+0), (dx1+1,dy1+1), pričom ale dx2^2+dy2^2<=25. Panáčik nemôže vyjsť mimo plochy ani sa dostať na zakázané políčko.

Panáčik začína v stave ako keby jeho sa v minulom ťahu zmenilo políčko panáčika o (0,0) a cieľom je nájsť najkratšiu cestu zo štartového políčka na cieľové políčko. V prípade, že takýchto ciest bude viac, vyberte takú kde je n-tica (x0, y0, x1, y1, x2, y2, ..., xn, yn) lexikograficky najmenšia, pričom xi a yi sú x-ová (riadok) a y-ová (stlpec) súradnica polohy panáčika po i-tom ťahu.

Formát vstupu:
V prvom riadku vstupu sa nachádza počet podvstupov, za ním nasleduje prázdny riadok.

Následne pre každý podvstup nasleduje:

riadok s dvoma celými číslami x a y udávajúcimi rozmery plochy x=počet riadkov y=počet stĺpcov, x<=150, y<=150,
riadok s dvoma celými číslami xz a yz udávajúcimi počiatočné políčko panáčika, 0<=xz<x, 0<=yz<y,
riadok s dvoma celými číslami xk a yk udávajúcimi koncové políčko panáčika, 0<=xk<x, 0<=yk<y.
Nasleduje x riadkov, pričom každý riadok obsahuje y znakov. Ak je v a-tom riadku a b-tom stĺpci tejto časti na vstupe znak 'X', znamená to, že políčko (a,b) je zakázané. V opačnom prípade je v a-tom riadku a b-tom stĺpci tejto časti na vstupe znak '.', čo znamená, že políčko je povolené. Na záver podvstupu nasleduje prázdny riadok.

Formát výstupu:
Výstup bude postupne obsahovať riešenia pre jednotlivé podvstupy, za každým bude riadok obsahujúci --------------------

Ak podvstup nemá riešenie, vypíše sa No solution

Ak podvstup má riešenie, vypíše sa x riadkov po y znakov, kde v a-tom riadku a b-tom stĺpci je:

znak medzera (' ') ak je políčko (a,b) povolené a panáčik na ňom nebol,
znak o ('o') ak je políčko (a,b) povolené a panáčik na ňom bol,
znak X ('X') ak je políčko (a,b) zakázané.
Pamäťový limit: cca 128 MB
Poznámka: Uvedomte si, že na uloženie polohy a predchádzajúceho pohybu panáčika vám stačí 32 bitov (long).
