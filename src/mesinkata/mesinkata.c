#include "../boolean.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include <stdlib.h>
#include <stdio.h>

#define NMax 100
#define BLANK ' '

boolean EndKata = false;
Kata CKata;

void IgnoreBlank()
{
    while (CC == BLANK)
    {
        ADV();
    }
}
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang 
   F.S. : CC ≠ BLANK atau CC = MARK */

void STARTKATA(char *namafile)
{
    START(namafile);
    IgnoreBlank();
    if (CC == MARK)
    {
        EndKata = true;
    }
    else /* CC != MARK */
    {
        EndKata = false;
        SalinKata();
    }
}
/* I.S. : CC sembarang 
   F.S. : EndKata = true, dan CC = MARK; 
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */

void STARTKATAHANDLEBUY()
{
    STARTBUY();
    IgnoreBlank();
    if (CC == NEWLINE)
    {
        printf("Newline terbaca");
        EndKata = true;
    }
    else /* CC != MARK */
    {
        EndKata = false;
        SalinKata();
    }
}

void ADVKATA()
{
    IgnoreBlank();
    if (CC == MARK)
    {
        EndKata = true;
    }
    else /* CC != MARK */
    {
        SalinKata();
        IgnoreBlank();
    }
}
/* I.S. : CC adalah karakter pertama kata yang akan diakuisisi 
   F.S. : CKata adalah kata terakhir yang sudah diakuisisi, 
          CC adalah karakter pertama dari kata berikutnya, mungkin MARK
          Jika CC = MARK, EndKata = true.          
   Proses : Akuisisi kata menggunakan procedure SalinKata */

void ADVBUYKATA()
{
    IgnoreBlank();
    if (CC == NEWLINE)
    {
        EndKata = true;
    }
    else /* CC != MARK */
    {
        SalinKata();
        IgnoreBlank();
    }
}

void SalinKata()
{
    int i = 0;
    while ((CC != MARK) && (CC != BLANK) && (i < NMax))
    {
        CKata.TabKata[i] = CC;
        ADV();
        i++;
    } /* CC = MARK or CC = BLANK */
    CKata.Length = i;
}
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi; 
          CC = BLANK atau CC = MARK; 
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */

boolean IsKataSama (Kata K1, Kata K2){
   int i=0;
   if(K1.Length!=K2.Length){
      return false;
   } else{
        Kata K1_Low = lowerCaseKata(K1); Kata K2_Low = lowerCaseKata(K2);
        while(i<K1.Length){
            if(K1_Low.TabKata[i]!=K2_Low.TabKata[i]){
                return false;
            }
            i++;
        }
        return true;
   }
}

Kata KataConcat(Kata K1, Kata K2){
    for(int i=K1.Length;i<K1.Length+K2.Length;i++){
        K1.TabKata[i] = K2.TabKata[i-K1.Length];
    }
    // strncat(K1.TabKata,K2.TabKata,K2.Length);
    K1.Length = K1.Length + K2.Length;
    return K1;
}

Kata copyKata(Kata in) {
    Kata out;
    out.Length = in.Length;
    for(int i = 0; i < in.Length; i++) {
        out.TabKata[i] = in.TabKata[i];
    }
    return out;
}

void printKata(Kata in) {
    for(int i = 0; i < in.Length; i++) {
        printf("%c", in.TabKata[i]);
    }
}

Kata lowerCaseKata(Kata in){
    Kata out;
    for(int i = 0; i < in.Length; i++){
        int asciiValue = (int)in.TabKata[i];
        if(asciiValue>=65 && asciiValue<=90){
            out.TabKata[i] = (char)asciiValue+32;
        } else{
            out.TabKata[i] = (char)asciiValue;
        }
    }
    out.Length = in.Length;
    return out;
}

int KataToInt(Kata in){
    int hasil=0;
    for(int i = 0; i < in.Length; i++){
        hasil = hasil * 10;
        hasil = hasil + (int)in.TabKata[i]-48;
    }
    return hasil;
}
  
// void IntToKataRei(int in, Kata* Nilai) {
//     char StringNilai[100];
//     sprintf(StringNilai, "%d", in);
//     (*Nilai).Length=0; strcpy((*Nilai).TabKata,"");
//     int len = 1;
//     while (in / 10 != 0) {
//         len = len +1 ;
//         in = in /10 ;
//     }
//     (*Nilai).Length = len;
    
//     for (int i = 0 ; i < len ; i++){
//         (*Nilai).TabKata[i] = StringNilai[i];
//     }
// }

Kata IntToKata(int in){
    int inLen=in; int len=0;
    Kata out;
    int countDigits=0;
    if(in==0){
        out.TabKata[0]='0';out.Length=1;
        return out;
    }
    while(inLen!=0){
        inLen /= 10;
        len++;
    }
    while(in!=0){
        int ascii = (in % 10)+48;
        out.TabKata[len-countDigits-1] = (char)ascii;
        countDigits++;
        in = in / 10;
    }
    out.Length=countDigits;
    return out;
}