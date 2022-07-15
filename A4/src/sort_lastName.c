/*
//  freeStrings.c
//  Assignment3
//
//  Created by Jonalton Jude Hamilton on 2019-03-12.
//  Copyright © 2019 Jonalton Jude Hamilton. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

int sort_lastName(const void *a, const void *b){
    
    struct strings *first = (struct strings *)a;
    struct strings *second = (struct strings *)b;
    int result = 0;
    
    if (strcmp(first->lastName,"") == 0){
        result = strcmp(first->companyName,second->lastName);
    }
    if (strcmp(second->lastName,"") == 0){
        result = strcmp(first->lastName,second->companyName);
    }
    if (strcmp(first->lastName,"") == 0 && strcmp(second->lastName,"") == 0){
        result = strcmp(first->companyName,second->companyName);
    }
    if (strcmp(first->lastName,"") != 0 && strcmp(second->lastName,"") != 0){
        result = strcmp(first->lastName,second->lastName);
    }
    return result;
    
}
