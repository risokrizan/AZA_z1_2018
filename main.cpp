// uloha1.c -- Richard Križan, 26.3.2018 14:30

#include <stdio.h>
#include <stdlib.h>

typedef struct QItem {
    int vrchol;
    struct QItem *dalsi;
} QI;


typedef struct Queue {
    QI *prvy;
    QI *posledny;
} Q;

typedef struct Neighbours {
    int vrchol;
    struct Neighbours *dalsi;
} Susedia;

int map[150][150];
int n, m;
int visited[22500];
int zac_x = -1, zac_y = -1, ciel_x = -1, ciel_y = -1;

void vloz_queue(Q *q, int vrchol) {
    QI *novy = (QI *) malloc(sizeof(QI));
    novy->vrchol = vrchol;
    novy->dalsi = NULL;

    if (q->posledny == NULL) {
        q->posledny = novy;
        q->prvy = novy;
    } else {
        q->posledny->dalsi = novy;
        q->posledny = novy;
    }
}

int vyber_queue(Q *q) {

    if (q->prvy == NULL)
        return -1;

    int novy = q->prvy->vrchol;
    q->prvy = q->prvy->dalsi;

    if (q->prvy == NULL || q->posledny == NULL) {
        q->prvy = NULL;
        q->posledny = NULL;
    }

    return novy;
}

void mozneIst(Susedia **prvy) {
    Susedia *akt = *prvy;
    printf("Mozne ist do: ");
    while (!(akt == NULL)) {
        printf(" %d ", akt->vrchol);
        akt = akt->dalsi;
    }
    printf("\n");
}


void pridajSuseda(Susedia **prvy, int vrchol) {

    Susedia *novy = (Susedia *) malloc(sizeof(Susedia));

    Susedia *akt = *prvy;

    novy->vrchol = vrchol;
    novy->dalsi = NULL;

    if (*prvy == NULL) {
        *prvy = novy;
    } else {
        while (!(akt->dalsi == NULL))
            akt = akt->dalsi;
        akt->dalsi = novy;
    }

}

void priprav_mapu(int m, int n) {
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (j == 0)
                scanf("\n");
            char a;
            scanf("%c", &a);
            if (a == '.') {
                map[i][j] = 1;
            } else if (a == 'X') {
                map[i][j] = 0;
            }
        }

    }
}

void vypis_mapu(int m, int n) {

    printf("\n");
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (map[i][j] == 0)
                printf("X");
            if (map[i][j] == 1)
                printf(" ");
            if (map[i][j] == 2)
                printf("o");
        }
        printf("\n");
    }
}

Susedia *zisti_susedov(int aktVrchol, int predchvrchol) {

    Susedia *prvy = NULL;


    int akt_y = aktVrchol / n;
    int akt_x = aktVrchol % n;
    int predch_y = predchvrchol / n;
    int predch_x = predchvrchol % n;
    int posun_x = akt_x - predch_x;
    int posun_y = akt_y - predch_y;
    int susedia_x = akt_x + posun_x;
    int susedia_y = akt_y + posun_y;

    //rovnaka pozicia
    if (map[susedia_y][susedia_x] == 1)
        pridajSuseda(&prvy, susedia_y * n + susedia_x);
    //vychod
    if (susedia_x + 1 < n)
        if (map[susedia_y][susedia_x + 1] == 1)
            pridajSuseda(&prvy, (susedia_y) * n + (susedia_x + 1));
    //severovychod
    if (susedia_y - 1 > 0 && susedia_x + 1 < n)
        if (map[susedia_y - 1][susedia_x + 1] == 1)
            pridajSuseda(&prvy, (susedia_y - 1) * n + (susedia_x + 1));
    //juhovychod
    if (susedia_y + 1 < m && susedia_x + 1 < n)
        if (map[susedia_y + 1][susedia_x + 1] == 1)
            pridajSuseda(&prvy, (susedia_y + 1) * n + (susedia_x + 1));
    //sever
    if (susedia_y - 1 > 0)
        if (map[susedia_y - 1][susedia_x] == 1)
            pridajSuseda(&prvy, (susedia_y - 1) * n + susedia_x);
    //severozpad
    if (susedia_y - 1 > 0 && susedia_x - 1 > 0)
        if (map[susedia_y - 1][susedia_x - 1] == 1)
            pridajSuseda(&prvy, (susedia_y - 1) * n + (susedia_x - 1));
    //zapad
    if (susedia_x - 1 > 0)
        if (map[susedia_y][susedia_x - 1] == 1)
            pridajSuseda(&prvy, (susedia_y) * n + (susedia_x - 1));
    //juhozapad
    if (susedia_y + 1 < m && susedia_x - 1 > 0)
        if (map[susedia_y + 1][susedia_x - 1] == 1)
            pridajSuseda(&prvy, (susedia_y + 1) * n + (susedia_x - 1));
    //juh
    if (susedia_y + 1 < m)
        if (map[susedia_y + 1][susedia_x] == 1)
            pridajSuseda(&prvy, (susedia_y + 1) * n + (susedia_x));


    return prvy;
}

void bfs(int pocVrchol, Q *q) {


    int predchVrchol = pocVrchol;
    int aktualnyVrchol = pocVrchol;
    visited[pocVrchol] = 1;
    vloz_queue(q, pocVrchol);

    while (!q->posledny == NULL) {
        predchVrchol = aktualnyVrchol;
        aktualnyVrchol = vyber_queue(q);
        printf("Visited %d\n", aktualnyVrchol);
        map[aktualnyVrchol / n][aktualnyVrchol % n] = 2;
        if (aktualnyVrchol == ciel_y * n + ciel_x)
            break;

        //zisti susedov
        Susedia *temp = zisti_susedov(aktualnyVrchol, predchVrchol);

        mozneIst(&temp);

        while (temp != NULL) {
            int adjVertex = temp->vrchol;

            if (visited[adjVertex] == 0) {
                visited[adjVertex] = 1;
                vloz_queue(q, adjVertex);
            }
            temp = temp->dalsi;
        }
    }
}


int main() {

    int pocet_podvstupov = 0;
    scanf("%d\n", &pocet_podvstupov);
    for (int vstup = 0; vstup < pocet_podvstupov; vstup++) {
        //nacitaj
        scanf("%d %d\n", &m, &n); //m-pocet riadkov n-pocet stlpcov
        scanf("%d %d\n", &zac_y, &zac_x);
        scanf("%d %d\n", &ciel_y, &ciel_x);
        //priprav mapu
        priprav_mapu(m, n);
        //vytvor queue
        Q *q = (Q *) malloc(sizeof(Q));
        q->prvy = NULL;
        q->posledny = NULL;
        bfs((zac_y * m) + zac_x, q);

        vypis_mapu(m, n);

    }
    // sem napis svoje riesenie

    return 0;
}