#include <stdio.h>
#include <stdlib.h>
#include "../Header/graph.h"

/* ----- KONSTRUKTOR ----- */
void CreateGraph(infotypePeta X, Graph* G){
    First(*G) = Nil;
    adrPeta P;
    InsertPeta(G,X,&P);
} // membuat graph baru
void InitGraph(Graph* G, char* source){
    FILE *file_graph = fopen(source, "r");
    First(*G) = Nil;
    int a[6];
    while (fscanf(file_graph,"%d",&a[0]) == 1) {
        for (int i = 1; i < 6; i++) {
            fscanf(file_graph,"%d",&a[i]);
        }
        infotypePeta PrecAwal, SuccAwal;
        PrecAwal.room = a[0];
        Absis(PrecAwal.p) = a[1];
        Ordinat(PrecAwal.p) = a[2];
        SuccAwal.room = a[3];
        Absis(SuccAwal.p) = a[4];
        Ordinat(SuccAwal.p) = a[5];
        InsertTerowongan(G,PrecAwal,SuccAwal);
    }
    fclose(file_graph);
} // load graph dari ext

/* ----- MANAJEMEN MEMORI ----- */
adrPeta AlokPetaGraph(infotypePeta X){
    adrPeta P = (adrPeta) malloc(sizeof(Peta));
    if (P != Nil) {
        Id(P) = X;
        Trail(P) = Nil;
        Next(P) = Nil;
    }
    return P;
} // mengembalikan hasil alokasi simpul
void DeAlokPetaGraph(adrPeta P){
    free(P);
} // mengembalikan simpul ke sistem
adrTerowongan AlokSuccPeta(adrPeta P){
    adrTerowongan T = (adrTerowongan) malloc(sizeof(Terowongan));
    if (T != Nil) {
        Succ(T) = P;
        Next(T) = Nil;
    }
    return T;
} // mengembalikan hasil alokasi succ simpul
void DealokSuccPeta(adrTerowongan T){
    free(T);
} // mengembalikan succ simpul ke sistem

/* ----- OPERASI GRAF ----- */
boolean isPetaEqual(adrPeta P, infotypePeta X){
    if (Id(P).room == X.room && Absis(Id(P).p) == Absis(X.p) && Ordinat(Id(P).p) == Ordinat(X.p)) {
        return true;
    }
    else {
        return false;
    }
} // mengembalikan apakah P memiliki Id X
adrPeta SearchPeta(Graph G, infotypePeta X){
    adrPeta P = First(G);
    while (P != Nil) {
        if (isPetaEqual(P,X)) {
            return P;
        }
        else {
            P = Next(P);
        }
    }
    return P;
} // mencari X pada G, return nil jika tiada
adrTerowongan SearchTerowongan(Graph G, infotypePeta prec, infotypePeta succ){
    adrPeta Prec = SearchPeta(G,prec);
    adrTerowongan T = Trail(Prec);
    while (Prec != Nil) {
        if (isPetaEqual(Succ(T),succ)) {
            return T;
        }
        else {
            Prec = Next(Prec);
        }
    }
    return T;
} // mencari succ dari prec pada G, return nil jika tiada
void InsertPeta(Graph* G, infotypePeta X, adrPeta* Pn){
    *Pn = AlokPetaGraph(X);
    adrPeta P = First(*G);
    if (P != Nil) {
        while (Next(P) != Nil) {
            P = Next(P);
        }
        Next(P) = *Pn;
    }
    else {
        First(*G) = *Pn;
    }
} // memasang X ke akhir G
void InsertTerowongan(Graph* G, infotypePeta prec, infotypePeta succ){
    if (SearchTerowongan(*G,prec,succ) == Nil) {
        adrPeta P1 = SearchPeta(*G,prec);
        adrPeta P2 = SearchPeta(*G,succ);
        if (P1 == Nil) {
            InsertPeta(G,prec,&P1);
        }
        if (P2 == Nil) {
            InsertPeta(G,succ,&P2);
        }
        adrTerowongan T = Trail(P1);
        if (T == Nil) {
            Trail(P1) = AlokSuccPeta(P2);
        }
        else {
            while (Next(T) != Nil) {
                T = Next(T);
            }
            Next(Trail(P1)) = AlokSuccPeta(P2);
        }
    }
} // memasang succ ke akhir prec
