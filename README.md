Laboratorijska vježba 1

Dama

http://en.wikipedia.org/wiki/English_draughts

Potrebno je dovršiti  funkcije koje će omogućiti
igranje dame protiv računala (računalo će za sada
igrati slučajne poteze). Za sada će se implementirati
pojednostavljena pravila. Kôd je na stranicama
kolegija.

Pravila igre su:
1) Igrači naizmjenice igraju po jedan potez jednom od
figura (prvi igra crni).
2) Potez može biti:
a. Pomicanje figure na dijagonalno susjedno i slobodno
polje. Za sada isključivo dijagonalno-naprijed.
b. Preskakanje protivničke figure na dijagonalnom
susjednom polju, ako je iduće polje slobodno.
Preskočena figura je „pojedena“ i uklanja se sa ploče.
Za sada ćemo višestruko preskakanje zanemariti.
3) Figure koje dođu do zadnjeg reda se više ne mogu
micati.
4) Igra završava kada igrač koji je na redu ne može
igrati sa nijednom figurom.
5) Pobjednik je igrač koji je ostao sa više figura na
ploči.



Laboratorijska vježba 4

Dama - nastavak

Iterative deepening

Slično kao i kod Puzzle kôda, potrebno je da se tijekom
pretrage pamti linija najboljih poteza. Ovdje je najbolje
označiti zadnji potez niza poteza sa -1 (npr. u from_r
članu Move strukture).
Uz to je potrebno dodati funkciju iterDeep() koja će
poziva dorađeni minmax() sa  dubinom od 1 do 7 i nakon
svakog poziva ispisati najbolju liniju poteza (sa
vrijednošću dobivenom od minmax i brojem pretraženih
pozicija).

Funkcije će imati zaglavlja:

int iterDeep(Position *pos, Move *bm);

int minmax(Position *pos, Move *line, int d, int *nodes);
