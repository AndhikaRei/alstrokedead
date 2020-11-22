#include "../Header/list_linkedlist.h"
#include "../Header/wahana.h"
#include <stdio.h>
#include <stdlib.h>

int addUpgrade( ListNode **head, Kata data )
{
    ListNode *node = malloc( sizeof( ListNode ) );
    int success = node != NULL;
    if(success){
        node->data = data;
        node->next = NULL;
        ListNode *current=*head;
        if(current==NULL){
            *head = node;
        } else{
            while(current->next!=NULL){
                current=current->next;
            }
            current->next = node;
        }
    }
    return success;
}

void removeUpgrade( ListNode **head )
{
    ListNode* temp = *head;
    *head = temp->next;
    free(temp);
}

void printUpgrades( ListNode **head )
{
    for( ListNode *current =*head; current != NULL; current = current->next ) //Mark pakai NULL
    {
        printKata(current->data);printf("->");
    }
    printf( "%s", "NULL" );
}