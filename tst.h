#ifndef TST_H
#define TST_H

typedef struct node TST;
struct node {
    int val;
    unsigned char c;
    TST *l, *m, *r;
};

#endif