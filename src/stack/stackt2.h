/* File : stackt2.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef stackt_H
#define stackt_H

#include "../boolean.h"
#include "../mesinkata/mesinkar.h"
#include "../mesinkata/mesinkata.h"
#include <stdio.h>

#define Stack_Nil -1
#define MaxEl_Stack 10
/* Nil adalah stack dengan elemen kosong . */

typedef Kata infotype;
typedef int address;   /* indeks tabel */

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  infotype T[MaxEl_Stack]; /* tabel penyimpan elemen */
  address TOP;  /* alamat TOP: elemen puncak */
} Stack;
/* Definisi stack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai Stack T[0]..T[MaxEl_Stack-1] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]
#define InfoTopKata(S) (S).T[(S).TOP].TabKata
#define InfoTopLength(S) (S).T[(S).TOP].Length

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty (Stack *S);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl_Stack */
/* jadi indeksnya antara 0.. MaxEl_Stack */
/* Ciri stack kosong : TOP bernilai Nil */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFull (Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, infotype X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, infotype* X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

/* ************ Operasi lain Stack ************ */

void Reverse(Stack *S);
/* Memutar balikkan isi stack */
/*	I.S.  S tidak kosong dan terdefinisi */
/*	F.S.	Isi dari S terbalik urutannya */


void PrintStack(Stack S);
/*	I.S. S tidak kosong dan terdefinisi */
/*	F.S. Seluruh isi S dicetak */

void AkuisisiBuy(infotype S, int* N, char benda[100]);
void AkuisisiBuild(infotype S, int* buildX, int* buildY, int* buildMap, char bangunan[100]);
void AkuisisiBuyV2(infotype S, int* Nbenda, Kata* benda);
void AkuisisiBuildV2(infotype S, int* buildX, int* buildY, int* buildMap, Kata* bangunan, int* sizeX, int* sizeY);
void AkuisisiUpgrade(Kata K, char *idWahana, Kata *Nama_Upgrade);
#endif
