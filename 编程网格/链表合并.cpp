/*
链表合并
题目描述

定义一种单向链表，链表结点LinkNode包含一个整数和一个指向下一个节点的指针。编写下面四个子函数：
1、建立链表: 从标准输入读取数据，并创建链表，返回创建的链表头
LinkNode *CreateLinkList();
2、合并链表：参数是两个链表的头指针，返回合并后链表的头指针。合并后的链表仍然有序。
LinkNode *MergeLinkList(LinkNode *a, LinkNode *b);
3、遍历并显示合并后的链表的元素。
void DisplayLinkList(LinkNode *linklist);
4. 释放链表空间：如果CreateLinkList中使用了new分配空间，这里循环使用delete释放
void DestroyLinkList(LinkNode *linklist);
注意：
1. 假设用户输入数据时，是按照数据从小到大输入的，即链表是一个有序链表，不需要排序操作；
2. 没有按要求编写函数的，即使通过也会被扣分。
3. 你的程序应该使用尽可能少的内存空间。(在MergeLinkList函数中尽量不要分配新的LinkNode)
关于输入

输入的第一行是一个整数m，代表第一个链表的元素个数（1 <= m <= 100000）；
第二行是m个整数，代表第一个链表的每个元素，题目保证m个整数从小到大排列。
第三行是一个整数n，代表第二个链表的元素个数（1 <= n <= 100000）；
第四行使n个整数，代表第二个链表的每个元素，题目保证n个整数从小到大排列。
关于输出

输出只有1行，输出以空格分隔的 m + n 个整数，按照从小到大的顺序排列。
例子输入

3
1 3 5
3
2 4 6

例子输出

1 2 3 4 5 6
*/

#include <iostream>

int n, m;

struct node {
    int val;
    node* next;
};

node* create_list(int size) {
    if (size <= 0) return nullptr;
    node *head = nullptr;
    node *tail = nullptr;
    for (int i = 0; i < size; ++i) {
        int num;
        std::cin >> num;
        node* new_node = new node{num, nullptr};
        if (head == nullptr) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }
    return head;
}

node* merge_list(node* head1, node* head2) {
    if (!head1) return head2;
    if (!head2) return head1;
    
    node* head = nullptr;
    node* tail = nullptr;
    node* p1 = head1;
    node* p2 = head2;
    
    if (p1->val <= p2->val) {
        head = tail = p1;
        p1 = p1->next;
    } else {
        head = tail = p2;
        p2 = p2->next;
    }
    
    while (p1 && p2) {
        if (p1->val <= p2->val) {
            tail->next = p1;
            tail = p1;
            p1 = p1->next;
        } else {
            tail->next = p2;
            tail = p2;
            p2 = p2->next;
        }
    }
    
    if (p1) {
        tail->next = p1;
    } else {
        tail->next = p2;
    }
    
    return head;
}

void show_list(node* head) {
    node* temp = head;
    bool flag=false;
    while (temp != nullptr) {
        if(!flag){
            flag=true;
            std::cout << temp->val;
        }else std::cout<<" "<<temp->val;
        temp = temp->next;
    }
    std::cout << std::endl;
}

void release(node* head) {
    node* temp = head;
    while (temp != nullptr) { 
        node* next = temp->next;
        delete temp;
        temp = next;
    }
}

int main() {
    std::cin >> m;
    node* head1 = create_list(m);
    std::cin >> n;
    node* head2 = create_list(n);
    node* head = merge_list(head1, head2);
    show_list(head);
    release(head);
    return 0;
}
