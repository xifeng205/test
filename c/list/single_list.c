/*********************************************************************
 * Author        : cuiyunpeng
 * Email         : @163.com
 * Create time   : 2020-04-15 11:44
 * Last modified : 2020-04-15 11:44
 * Filename      : single_list.c
 * Description   : 
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>

struct node {
    void *data;
    struct node *next;
};

struct node *listcreat()
{
    struct node *head = (struct node *)malloc(sizeof(head));

    head->data = 1;
    head->next = NULL;
    return head;
}

void list_current_insert(struct node *parent, struct node *current )
{
    struct node *p = parent;
    struct node *c =current;

    if (!p->next) {
        p->next = c;
        c->next = NULL;
    } else {
        struct node *tmp = p->next;
        p->next = c;
        c->next = tmp;
    }
}

void list_tail_insert(struct node *parent, struct node *current )
{
    struct node *p = parent;
    struct node *c =current;
    
    while (p->next) p = p->next;
    p->next = current;
    c->next = NULL;
}

struct node *list_find(struct node *parent, void *search, int mode)
{
    struct node *p =parent;
    switch (mode) {
        case 1:
            /* char *sdata = (char *)search; */
            /* char *pdata = (char *)p->data; */
            /* if (strcmp(pdata, sdata)) return p; */
            /* while (p->next) { */
                /* p = p->next; */
                /* char *pdata = (char *)p->data; */
                /* if (strcmp(pdata, sdata)) return p; */
            /* } */
            /* return NULL; */
        case 2:
            /* int sdata = *((int *)search); */
            /* int pdata = *((int *)p->data); */
            /* if (sdata == pdata) return p; */
            /* while (p->next) { */
                /* p = p->next; */
                /* int sdata = *((int *)search); */
                /* int pdata = *((int *)p->data); */
                /* if (sdata == pdata) return p; */
                /* return NULL; */
            }
        case 3:
            break;
        case 4:
        default:break;
    }
}

void list_search_inseret(struct node *parent,  void *search, int mode )
{
    struct node *obj = list_find(parent, search, mode);
    list_current_insert(parent, obj);
}


void list_all_print(struct node *root)
{
    struct node *h = root;

    printf(" list->data= %d\n",  *(int *)h->data);
    while (h->next) {
        h = h->next;
        printf(" h->data= %d\n",  *(int *)h->data);
    }
}

void list_seatch_print(struct node *parent, struct node *current )
{

}

void list_current_del(struct node *parent, struct node *current )
{

}

void list_tail_del(struct node *parent, struct node *current )
{

}

void list_search_del(struct node *parent, struct node *current )
{

}

int main(int argc, char **argv)
{ 
    int a=1, b =2, c = 3;
    struct node *head = listcreat();
    struct node *option = listcreat();

    struct node *list1 = listcreat();
    list1->data = &a;
    list_tail_insert(head, list1);

    struct node *list2 = listcreat();
    list2->data = &b;
    list_tail_insert(head, list2);

    struct node *list3 = listcreat();
    list3->data = &c;
    list_tail_insert(head, list3);

    list_all_print(head);

    return 0;
}

