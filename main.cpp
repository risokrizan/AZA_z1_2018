// uloha1.c -- Richard Križan, 26.3.2018 14:30
#pragma pack(1)
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define INF 2147483647
typedef struct QItem {
    int vrchol;
    struct QItem *parent;
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
bool visited[22500][11][11];
int zac_x = -1, zac_y = -1, ciel_x = -1, ciel_y = -1;
int koniec=0;
Q *q;

void vloz_queue(Q *q, int vrchol, struct QItem *parent) {
    QI *novy = (QI *) malloc(sizeof(QI));
    novy->vrchol = vrchol;
    novy->parent = parent;
    novy->dalsi = NULL;
    if (q->posledny == NULL) {
        q->posledny = novy;
        q->prvy = novy;
    } else {
        q->posledny->dalsi = novy;
        q->posledny = novy;
    }
}

QI * vyber_queue(Q *q) {

    if (q->prvy == NULL)
        return NULL;

    QI *novy = q->prvy;
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

int na_Druhu(int a) {
    return a * a;
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

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            //printf("%d",map[i][j]);

            if (map[i][j] == 0)
                //x
                printf("X");
            if (map[i][j] == 1)
                //" "
                printf(" ");
            if (map[i][j] == 2)
                //"o"
                printf("o");

        }
        printf("\n");
    }
}
void vycisti_mapu(int m, int n) {

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            map[i][j] == -1;
        }
    }
}
void davaj (int newy, int newx, QI *aktualnyVrchol) {

    QI *fin;
        int adjVertex = newy*n+newx;
        if (visited[adjVertex][(adjVertex/n-aktualnyVrchol->vrchol/n) + 5][(adjVertex%n-aktualnyVrchol->vrchol%n) + 5] == false){
            visited[adjVertex][(adjVertex/n-aktualnyVrchol->vrchol/n) + 5][(adjVertex%n-aktualnyVrchol->vrchol%n) + 5] = true;
            if (adjVertex == ciel_y * n + ciel_x) {
                fin = aktualnyVrchol;
                map[ciel_y][ciel_x] = 2;
                while (fin != NULL) {
                    map[fin->vrchol / n][fin->vrchol % n] = 2;
                    //printf("%d\n",fin->vrchol);
                    fin = fin->parent;
                }

                koniec = 1;
            }
            else {
                //printf("ADJ%d AKT%d\n",adjVertex,aktualnyVrchol->vrchol);
                vloz_queue(q, adjVertex, aktualnyVrchol);
            }
        }


}
void zisti_susedov(QI *aktVrchol) {

   // Susedia *prvy = NULL;

    int predch_y = 0;
    int predch_x = 0;
    int akt_y = aktVrchol->vrchol / n;
    int akt_x = aktVrchol->vrchol % n;
    if (aktVrchol->parent!=NULL) {
        predch_y = aktVrchol->parent->vrchol / n;
        predch_x = aktVrchol->parent->vrchol % n;
    }
    int posun_x = akt_x - predch_x;
    int posun_y = akt_y - predch_y;
    int susedia_x = akt_x + posun_x;
    int susedia_y = akt_y + posun_y;
    int vys_x;
    int vys_y;


    //pridajSuseda(&prvy, akt_y * n + akt_x, predchvrchol);

    //severozpad
    if ((na_Druhu((susedia_y - 1) - akt_y) + na_Druhu((susedia_x - 1) - akt_x)) < 26)
        if (susedia_y - 1 >= 0 && susedia_x - 1 >= 0)
            if (map[susedia_y - 1][susedia_x - 1] == 1)
            {
                vys_y = susedia_y - 1;
                vys_x = susedia_x - 1;
                davaj(vys_y,vys_x,aktVrchol);
            }
    //sever
    if ((na_Druhu((susedia_y - 1) - akt_y) + na_Druhu((susedia_x) - akt_x)) < 26)
        if (susedia_y - 1 >= 0)
            if (map[susedia_y - 1][susedia_x] == 1)
            {
                vys_y = susedia_y - 1;
                vys_x = susedia_x;
                davaj(vys_y,vys_x,aktVrchol);
            }
    //severovychod
    if ((na_Druhu((susedia_y - 1) - akt_y) + na_Druhu((susedia_x + 1) - akt_x)) < 26)
        if (susedia_y - 1 >= 0 && susedia_x + 1 < n)
            if (map[susedia_y - 1][susedia_x + 1] == 1)
            {
                vys_y = susedia_y - 1;
                vys_x = susedia_x + 1;
                davaj(vys_y,vys_x,aktVrchol);
            }
    //zapad
    if ((na_Druhu((susedia_y) - akt_y) + na_Druhu((susedia_x - 1) - akt_x)) < 26)
        if (susedia_x - 1 >= 0)
            if (map[susedia_y][susedia_x - 1] == 1)
            {
                vys_y = susedia_y;
                vys_x = susedia_x -1;
                davaj(vys_y,vys_x,aktVrchol);
            }
    //rovnaka pozicia
    if ((na_Druhu((susedia_y) - akt_y) + na_Druhu((susedia_x) - akt_x)) < 26)
        if (map[susedia_y][susedia_x] == 1)
        {
            vys_y = susedia_y;
            vys_x = susedia_x;
            davaj(vys_y,vys_x,aktVrchol);
        }
    //vychod
    if ((na_Druhu((susedia_y) - akt_y) + na_Druhu((susedia_x + 1) - akt_x)) < 26)
        if (susedia_x + 1 < n)
            if (map[susedia_y][susedia_x + 1] == 1)
            {
                vys_y = susedia_y;
                vys_x = susedia_x +1;
                davaj(vys_y,vys_x,aktVrchol);
            }
    //juhozapad
    if ((na_Druhu((susedia_y + 1) - akt_y) + na_Druhu((susedia_x - 1) - akt_x)) < 26)
        if (susedia_y + 1 < m && susedia_x - 1 >= 0)
            if (map[susedia_y + 1][susedia_x - 1] == 1)
            {
                vys_y = susedia_y +1;
                vys_x = susedia_x -1;
                davaj(vys_y,vys_x,aktVrchol);
            }
    //juh
    if ((na_Druhu((susedia_y + 1) - akt_y) + na_Druhu((susedia_x) - akt_x)) < 26)
        if (susedia_y + 1 < m)
            if (map[susedia_y + 1][susedia_x] == 1)
            {
                vys_y = susedia_y +1;
                vys_x = susedia_x;
                davaj(vys_y,vys_x,aktVrchol);
            }
    //juhovychod
    if ((na_Druhu((susedia_y + 1) - akt_y) + na_Druhu((susedia_x + 1) - akt_x)) < 26)
        if (susedia_y + 1 < m && susedia_x + 1 < n)
            if (map[susedia_y + 1][susedia_x + 1] == 1)
            {
                vys_y = susedia_y +1;
                vys_x = susedia_x +1;
                davaj(vys_y,vys_x,aktVrchol);
            }

}


void bfs(int pocVrchol) {


    QI *aktualnyVrchol;
    vloz_queue(q, pocVrchol,NULL);


    for (int i=0;i < n*m;i++ ){
        for (int j=0;j<11;j++){
            for (int k=0;k<11;k++){
                visited[i][j][k]= false;

            }
        }
    }
    //visited[pocVrchol][5][5] = pocVrchol;
    while ((!q->posledny == NULL) && koniec!=1) {

        aktualnyVrchol = vyber_queue(q);
        //predchVrchol = visited[aktualnyVrchol->vrchol][(aktualnyVrchol->vrchol/n-aktualnyVrchol->posun/n) + 5][(aktualnyVrchol->vrchol%n-aktualnyVrchol->posun%n) + 5];
        //printf("AKT%D\n",aktualnyVrchol->vrchol);

        //zisti susedov
        if (aktualnyVrchol!=NULL)
        zisti_susedov(aktualnyVrchol);

        //mozneIst(&temp);
    }
    if (!koniec)
        printf ("No solution\n");
}



int main() {

    int pocet_podvstupov = 0;
    scanf("%d\n", &pocet_podvstupov);
    for (int vstup = 0; vstup < pocet_podvstupov; vstup++) {
        //nacitaj
        scanf("%d %d\n", &m, &n); //m-pocet riadkov n-pocet stlpcov
        scanf("%d %d\n", &zac_y, &zac_x);
        scanf("%d %d\n", &ciel_y, &ciel_x);
        koniec=0;
        //priprav mapu
        priprav_mapu(m, n);
        //vytvor queue
        q = (Q *) malloc(sizeof(Q));
        q->prvy = NULL;
        q->posledny = NULL;
        bfs((zac_y * m) + zac_x);
        if(koniec)
            vypis_mapu(m, n);
        vycisti_mapu(m,n);
        printf("--------------------\n");
        /*while (q->posledny != NULL)
        {
            vyber_queue(q);
            printf("HMMM");
        }*/

    }
    // sem napis svoje riesenie

    return 0;
}