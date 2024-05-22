#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/student.h"

stuNode *head = NULL;
int idNum = 0;
int stuTotalNum = 0;

stuNode *newStuNode(void) {
    stuNode *node = malloc(STUNODESIZE);
    return node;
}
stuNode *newHeadNode(void) {
    stuNode *node = newStuNode();
    if (node == NULL) return NULL;
    node->data = malloc(STUSIZE);
    if (node->data == NULL) {
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
    stuTotalNum++;
    idNum++;
    return node;
}

void delectStuNode(int id){
    stuNode *p = searchById(id);
    if (p == NULL)
    {
        printf("删除失败，不存在的学生\n");
        return;
    }
    p->prev->next = p->next;
    p->next->prev = p->prev;
    free(p->data);
    free(p);
    stuTotalNum--;
    printf("删除成功\n");
}

stuNode *searchById(int id){
    stuNode *left = head->next,*right = head->prev;
    if (left == NULL && right == NULL)
        return NULL;
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

stuNode *searchByName(char* name,void (*f)(stuNode *)){
    for (stuNode *l = head->next;l != head;l=l->next)
    {
        if (strcmp(name,l->data->name)==0)
        {
            f(l);
        }
    }
    return NULL;
}

void changeStudent(stuNode *node,char *name,int ch,int math,int en){
    student *stu = node->data;
    strcpy(stu->name,name);
    stu->chineseScore = ch;
    stu->mathScore = math;
    stu->englishScore = en;
    printf("更改成功!\n\n");
}

void clearNode(stuNode *node){
    if (node != NULL)
    {
        free(node);
    }
}

void clearHeadAllNode(void){
    stuNode *node = head->prev;
    while (node->prev != head)
    {
        head->prev = head->prev->prev;
        free(node->data);
        free(node);
        node = head->prev;
    }
    stuTotalNum = 0;
    idNum = 0;
    system("clear");
}

stuNode *sortMerge(stuNode *node,int condi){
    if (node == NULL || node->next == NULL) return node;
    stuNode *slow = node,*fast = node->next;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    stuNode *nextNode = slow->next;
    slow->next = NULL;
    stuNode *m1 = sortMerge(node,condi);
    stuNode *m2 = sortMerge(nextNode,condi);
    stuNode *dummy = newStuNode();
    stuNode *preNode = dummy;
    while (m1 || m2)
    {
        if(condi == 1){
            if (m1 != NULL && (m2 == NULL || m1->data->chineseScore <= m2->data->chineseScore))
            {
                preNode->next = m1;
                m1 = m1->next;
            }else if (m2 != NULL && (m1 == NULL || m1->data->chineseScore > m2->data->chineseScore))
            {
                preNode->next = m2;
                m2 = m2->next;
            }
            preNode = preNode->next;
        }else if(condi == 2){
            if (m1 != NULL && (m2 == NULL || m1->data->mathScore <= m2->data->mathScore))
            {
                preNode->next = m1;
                m1 = m1->next;
            }else if (m2 != NULL && (m1 == NULL || m1->data->mathScore > m2->data->mathScore))
            {
                preNode->next = m2;
                m2 = m2->next;
            }
            preNode = preNode->next;
        }else if(condi == 3){
            if (m1 != NULL && (m2 == NULL || m1->data->englishScore <= m2->data->englishScore))
            {
                preNode->next = m1;
                m1 = m1->next;
            }else if (m2 != NULL && (m1 == NULL || m1->data->englishScore > m2->data->englishScore))
            {
                preNode->next = m2;
                m2 = m2->next;
            }
            preNode = preNode->next;
        }else{
            if (m1 != NULL && (m2 == NULL || STUNODETOTAL(m1) <= STUNODETOTAL(m2)))
            {
                preNode->next = m1;
                m1 = m1->next;
            }else if (m2 != NULL && (m1 == NULL || STUNODETOTAL(m1) > STUNODETOTAL(m2)))
            {
                preNode->next = m2;
                m2 = m2->next;
            }
            preNode = preNode->next;
        }
    }
    preNode->next = NULL;
    return dummy;
}

void EOFclose(){
    exit(EOF);
}