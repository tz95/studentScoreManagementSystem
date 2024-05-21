#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/student.h"

stuNode *head = NULL;
int idNum = 0;
int stuTotalNum = 0;

stuNode *newStuNode(void) {
    stuNode *node = malloc(STUNODESIZE);
    if (node == NULL) {
        return NULL; // 内存分配失败，返回NULL
    }
    node->data = malloc(STUSIZE);
    if (node->data == NULL) {
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
    stuTotalNum++;
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

void clearNode(void){
    for (int i = stuTotalNum; i; i--)
    {
        delectStuNode(i-1);
    }
    stuTotalNum = 0;
    system("clear");
}

// Merge function to merge two sorted lists
stuNode* merge(stuNode* left, stuNode* right, int (*cmp)(student*, student*)) {
    stuNode dummy;
    stuNode* tail = &dummy;
    dummy.next = head;
    dummy.prev = head;
    
    while (left != head && right != head) {
        if (cmp(left->data, right->data) <= 0) {
            tail->next = left;
            left->prev = tail;
            left = left->next;
        } else {
            tail->next = right;
            right->prev = tail;
            right = right->next;
        }
        tail = tail->next;
    }

    tail->next = (left == head) ? right : left;
    tail->next->prev = tail;
    while (tail->next != head) {
        tail = tail->next;
    }
    tail->next = head;
    head->prev = tail;

    return dummy.next;
}

// Split function to split the list into two halves
void split(stuNode* source, stuNode** front, stuNode** back) {
    stuNode* fast = source->next;
    stuNode* slow = source;

    while (fast != head && fast->next != head) {
        fast = fast->next->next;
        slow = slow->next;
    }

    *front = source;
    *back = slow->next;
    slow->next = head;
    head->prev = slow;
    (*back)->prev = head;
}

// Recursive merge sort function
void mergeSort(stuNode** headRef, int (*cmp)(student*, student*)) {
    stuNode* head = *headRef;
    if (head == NULL || head->next == head) {
        return;
    }

    stuNode* a;
    stuNode* b;
    split(head, &a, &b);
    mergeSort(&a, cmp);
    mergeSort(&b, cmp);

    *headRef = merge(a, b, cmp);
}

// Comparison function for sorting by Chinese score
int cmpChinese(student* a, student* b) {
    return a->chineseScore - b->chineseScore;
}

// Comparison function for sorting by Math score
int cmpMath(student* a, student* b) {
    return a->mathScore - b->mathScore;
}

// Comparison function for sorting by English score
int cmpEnglish(student* a, student* b) {
    return a->englishScore - b->englishScore;
}

// Comparison function for sorting by Total score
int cmpTotal(student* a, student* b) {
    return (a->chineseScore + a->mathScore + a->englishScore) - (b->chineseScore + b->mathScore + b->englishScore);
}

// Function to sort by total score
void sortByTotal() {
    mergeSort(&head->next, cmpTotal);
}

void sortByChinese() {
    mergeSort(&head->next, cmpChinese);
}

void sortByMath() {
    mergeSort(&head->next, cmpMath);
}

void sortByEnglish() {
    mergeSort(&head->next, cmpEnglish);
}