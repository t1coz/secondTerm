#include <stdlib.h>
#include "lists.h"
//operations simple list
list* addToHeadSimpleList(list* head, int x){
    list* newNode;
    newNode = (list*)malloc(sizeof(list));
    if(newNode){
        newNode->data = x;
        newNode->next = head;
        head = newNode;
    }
    return head;
}

//sorts
void swap(list *ptr1, list *ptr2){
    list* buf = ptr2->next;
    ptr2->next = ptr1;
    ptr1->next = buf;
}
int sizeOfList(list* head){
    int count = 0;
    while(head){
        count++;
        head = head->next;
    }
    return count;
}
list* retP(list *head, size_t index){
    list* tempIterator = head;
    while (index && tempIterator){
        tempIterator = tempIterator->next;
        index--;
    }
    return tempIterator;
}
list* BubbleListSort(list *head){
    for (size_t i = 0; i < sizeOfList(head)-1; i++){
        for (size_t j = 0; j < sizeOfList(head) - i - 1; ++j){
            if(retP(head, j)->data > retP(head, j+1)->data){
                list *buf = retP(head, j-1);
                list *ptr1 = retP(head, j);
                list *ptr2 = retP(head, j+1);
                swap(ptr1, ptr2);
                if(ptr1 == head){
                    head = ptr2;
                }else{
                    buf->next = ptr2;
                }
            }
        }
    }
    return head;
}
list* insertionSort(list* head){
    for (size_t i = 0; i < sizeOfList(head); i++){
        for (size_t j = i; j > 0 && (retP(head, j-1)->data > retP(head, j)->data); j--) {
            list* prev = retP(head, j-1);
            list* current = retP(head, j);
            if(prev == current){
                swap(prev, current);
                head = current;
            }else{
                list* prev2 = retP(head, j-2);
                swap(prev, current);
                prev2->next = current;
            }
        }
    }
    return head;
}
list* shellSort(list* head){
    size_t step = sizeOfList(head)/2;
    while(step>=1){
        for (size_t i = step; i < sizeOfList(head); ++i) {
            size_t j = i;
            while ((j>=step)&&(retP(head, j-step)->data > retP(head, j)->data)){
                list* ptr1 = retP(head, j-step);
                list* ptr2 = retP(head, j);
                if(ptr1->next == ptr2){
                    list* buffer3 = retP(head, j-step-1);
                    swap(ptr1, ptr2);
                    if(ptr1 == head){
                        head = ptr2;
                    }else{
                        buffer3->next = ptr2;
                    }
                }else if (ptr1->next != ptr2){
                    list* buffer1 = retP(head, j-step+1);
                    list* buffer2 = retP(head, j-1);
                    list* buffer3 = retP(head, j-step-1);
                    ptr1->next = ptr2->next;
                    ptr2->next = buffer1;
                    buffer2->next = ptr1;
                    if(ptr1 == head){
                        head = ptr2;
                    }else{
                        buffer3->next = ptr2;
                    }
                }
                j-=step;
            }
        }
        step/=2;
    }
    return head;
}

//rings 2d
ringTwo* deleteAny(ringTwo* ring){
    ringTwo *ring1, *ring2;
    char info[50];
    if(!ring) {
        printf("there is no ring");
        return ring;
    }
    ring1 = ring;
    puts("inf? - ");
    scanf("%s", info);
    do {
        if (strcmp(ring1->inf,info)){
            ring1 = ring1->next;
        }else{
            ring2 = ring1->next;
            ring2->prev = ring1->prev;
            ring2 = ring1->prev;
            ring2->next = ring1->next;
            if((ring1 == ring) && (ring->prev != ring))
                ring = ring1->next;
            free(ring1);
            return ring;
        }
    } while (ring1!=ring);
    return ring;
}