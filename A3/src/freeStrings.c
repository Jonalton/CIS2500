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
/*#include "contactList.h"*/

void freeStrings(char *firstName, char *lastName, char *companyName,char *phoneNumber,char *email){
    /*free allocated memory for these strings*/
    free(firstName);
    free(lastName);
    free(companyName);
    free(phoneNumber);
    free(email);
}
