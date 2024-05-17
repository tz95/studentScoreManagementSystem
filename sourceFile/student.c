#include <stdio.h>
#include <stdlib.h>
#include "../include/student.h"

stuNode *head = NULL;
int idNum = 0;

stuNode *newStuNode(void) {
    stuNode *node = malloc(STUNODESIZE);
    if (node == NULL) {
        return NULL; // 内存分配失败，返回NULL
    }
    node->data = malloc(STUSIZE);
    node->data->name = calloc(10,1);
    if (node->data == NULL || node->data->name == NULL) {
        if (node->data->name == NULL)
            free(node->data);
        free(node); // 释放节点内存
        return NULL; // 内存分配失败，返回NULL
    }
    if (head == NULL) {
        head = malloc(STUNODESIZE);
        head->next = node;
        head->prev = node;
        node->next = head;
        node->prev = head;
    } else {
        node->next = head;
        node->prev = head->prev;
        head->prev->next = node;
        head->prev = node;
    }
    return node;
}

void delectStuNode(int id){
    stuNode *p = searchById(id);
    if (p == NULL)
    {
        printf("删除失败，不存在的学生\n");
        return;
    }
    free(p->data->name);
    free(p->data);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p);
    printf("删除成功\n");
}

stuNode *searchById(int id){
    stuNode *left = head->next,*right = head->prev;
    do
    {
        if (left->data->id == id)
        {
            return left;
        }
        if (right->data->id == id)
        {
            return right;
        }
        left = left->next;
        right = right->prev;
        
    } while (left->prev != right && (left != head && right != head));
    return NULL;
}

stuNode *searchByName(char* name){

}