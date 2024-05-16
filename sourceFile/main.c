#include <stdio.h>
#include "../include/menu.h"

int main(void){
    int n;
    do
    {
        printMenu();
        scanf("%d",&n);
        printf("\n");
        selectMenu(n);
    } while (n);
    
    return 0;
}