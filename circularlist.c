//
//  circularlist.c
//  circularlist
//
//  Created by Joost Markerink on 10-10-17.
//  Copyright © 2017 Joost Markerink. All rights reserved.
//

#include "circularlist.h"


acircularnode *circularnode_get_previous(acircularnode *start){
    circularnode *c=start;
    if(c)
        while(c->next!=start)
            c=c->next;
    return c;
}

acircularnode *circularnode_add(acircularnode *start,acircularnode *node){
    circularnode *s=start;
    if(!s->next) s->next=s;
    
    circularnode *n=node;
    n->next=s->next;
    s->next=n;
    return node;
}

acircularnode *circularnode_remove(acircularnode *node){
    circularnode *n=node;
    circularnode *prev=circularnode_get_previous(n);
    prev->next=n->next;
    return prev;
}

int circularnode_rotate(const acircularnodelink c,const acircularnode *end){
    const void **current=(const void **)c;
    if(!*current){
        *current=end;
        return 1;
    }else *current=((circularnode *)*current)->next;    
    return *current==end?0:1;
}


unsigned circularnode_count(acircularnode *l){
    unsigned len=l?1:0;
    if(len){
        acircularnode *current;
        while(circularnode_rotate(&current, l)) len++;
    }
    return len;
}


