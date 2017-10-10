//
//  example.c
//  circularlist
//
/*
 MIT License
 
 Copyright (c) 2017 Joost Markerink
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */


#include <stdio.h>
#include <stdlib.h>
#include "circularlist.h"

typedef struct{
    circularnode circularnode;
    int value;
}intnode;

intnode *intnode_create(int val){
    intnode *n=malloc(sizeof(intnode));
    n->value=val;
    return n;
}

intnode *intnode_create_list(const int *values,int number_of_values){
    intnode *circle=intnode_create(values[0]);
    intnode *rotation=circle;
    int i;
    for(i=1;i<number_of_values;i++)
        rotation=circularnode_add(rotation,intnode_create(values[i]));
    return circle;
}

void intnode_free_list(intnode *node){
    circularnode *n=node->circularnode.next;
    node->circularnode.next=NULL;//cut the loop
    while(n){
        acircularnode *next=n->next;
        free(n);
        n=next;
    }
}

void intnode_collect_values(intnode *circle,int *values){
    intnode *current;
    while(circularnode_rotate(&current,circle))
        *values++=current->value;
}



int main(int argc, const char * argv[]) {

    int vals[]={1,2,3,4,5,6};
    intnode *circle=intnode_create_list(vals,sizeof(vals)/sizeof(int));
    intnode *current=0;
    while(circularnode_rotate(&current, circle))
        printf("%i\n",current->value);
    
    intnode_free_list(circle);

    return 0;
}
