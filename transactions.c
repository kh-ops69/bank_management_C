#include <stdio.h>
#include <stdlib.h>

#define SIZE 10
int stack[SIZE];

int push(int);
int pop(int);
void display(int);

int main(){
    int ch;
    int head = -1;
    while(1){
        printf("\nTransaction operations: \n");
        printf("1.Insert new transaction\n2.Delete previous transaction\n3.Display list of transactions\n4.Exit");
        printf("\nEnter your choice:");
        scanf("%d", &ch);
        switch(ch){
            case 1: head = push(head);
            break;
            case 2: head = pop(head);
            break;
            case 3:
                display(head);
                break;
            case 4: exit(0);
            default: printf("Invalid choice, please enter again:");
            break;
        }
    }
}

int push(int head){
    int item;
    if (head==(SIZE-1)){
        printf("Stack is full");
        return head;
    }
    printf("Enter transaction amount to be pushed: ");
    scanf("%d", &item);
    stack[++head] = item;
    printf("%d transaction item has been successfully pushed\n", item);
    return head;
}

int pop(int head){
    if(head == -1){
        printf("Nothing to be deleted from transaction list: \n");
        return head;
    }
    printf("%d topmost transaction successfully popped", stack[head]);
    head--;
    return head;
}

void display(int head){
    if(head==-1){
        printf("nothing to display");
    }
    int i;
    for(i = head; i>=0; i--){
        printf("%d->", stack[i]);
    }
}