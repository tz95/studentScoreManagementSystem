#include <stdio.h>
#include "../include/menu.h"
#include "../include/operation.h"

void printMenu(void){
    printf("1.新增\n"
           "2.删除\n"
           "3.更改\n"
           "4.查找\n"
           "5.读取\n"
           "6.保存\n"
           "7.排序\n"
           "8.显示\n"
           "AnyKey.退出\n");
    printf("请输入所需操作的值:");
}

void selectMenu(int n){
    switch (n)
    {
    case 1:
        addStu();
        break;

    case 2:
        delectStu();
        break;

    case 3:
        changeStu();
        break;

    case 4:
        // searchStu();
        break;
    
    case 5:
        // loadStu();
        break;
    
    case 6:
        // saveStu();
        break;
    
    case 7:
        // sortStu();
        break;
    
    case 8:
        showStu();
        break;
    default:
        exit(0);
        break;
    }
}