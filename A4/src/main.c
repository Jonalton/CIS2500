/*
//  main.c
//  Assignment3
//
//  Created by Jonalton Jude Hamilton on 2019-03-05.
//  Copyright © 2019 Jonalton Jude Hamilton. All rights reserved.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include "contactList.h"

int main() {
    FILE *fptr;
    fptr = fopen("myContactList.db","ab+");
    if (fptr == NULL){
        printf("file could not be created");
        return -1;
    }
    fseek(fptr,0,SEEK_END);
    long fileSize = ftell(fptr);
    printf("%lu\n",fileSize);
    fseek(fptr,0,SEEK_SET);
    int (*compare_ptr)(const void *a, const void *b);
    int numberOfContacts = 0;
    int loop = 1;
    char answer;
    char *buffer;
    buffer = malloc(sizeof(char)*1000);
    
    contacts *record = NULL;
    record = malloc(sizeof(contacts));
    
    strings *info = NULL;
    info = malloc(sizeof(strings));
    do{
        record = realloc(record,sizeof(contacts)*(numberOfContacts+1));
        info = realloc(info,sizeof(contacts)*(numberOfContacts+1));
        readStrings(record,info,numberOfContacts,fptr);
        numberOfContacts++;
    }while(record[numberOfContacts-1].next != fileSize);
    numberOfContacts = numberOfContacts - 1;
    printf("%d\n",numberOfContacts);
    
    compare_ptr = &sort_lastName;
    
    do{
        printf("Number of Contacts = %d\n",numberOfContacts+1);
        qsort(info,numberOfContacts+1,sizeof(strings),compare_ptr);
        for(int j=0;j<=numberOfContacts;j++){
            if (strcmp(info[j].lastName,"") != 0){
                printf("%d. %s %s\n",j+1,info[j].firstName,info[j].lastName);
            }
            if (strcmp(info[j].lastName,"") == 0){
                printf("%d. %s\n",j+1,info[j].companyName);
            }
        }
        printf("Action: ");
        answer = getchar();
        
        if(answer == 'A'){
            fseek(fptr,0,SEEK_END);
            int tempNumber;
            tempNumber = numberOfContacts;
            getchar();
            record = realloc(record,sizeof(contacts)*(numberOfContacts+2));
            numberOfContacts = writeContact(fptr,record,numberOfContacts+1);

            if (tempNumber != numberOfContacts){
                info = realloc(info,sizeof(contacts)*(numberOfContacts+1));
                readStrings(record,info,numberOfContacts,fptr);
            }

            printf("#Contacts: %d\n",numberOfContacts);
            printf("#temp: %d\n",tempNumber);
            getchar();
        }
        
        else if(isdigit(answer) == 1){

            getchar();
            int contactNumber = answer - '0';
            if (contactNumber <= numberOfContacts +1 ){
                printf("Contact #%d\n",contactNumber);
                printf("First Name: %s\n",info[contactNumber-1].firstName);
                printf("Last Name: %s\n",info[contactNumber-1].lastName);
                printf("Company Name: %s\n",info[contactNumber-1].companyName);
                printf("Phone Number: %lu\n",info[contactNumber-1].phoneNumber);
                printf("Email: %s\n",info[contactNumber-1].email);
                printf("Action: ");
                char contactOption = getchar();
                if (contactOption == 'E'){
                    numberOfContacts = editContact(fptr,record,info,contactNumber-1,numberOfContacts);
                    info = realloc(info,sizeof(strings)*(numberOfContacts+1));
                    getchar();
                }
                if (contactOption == 'D'){
                    numberOfContacts = deleteContact(fptr,record,info,contactNumber-1,numberOfContacts);
                    info = realloc(info,sizeof(strings)*(numberOfContacts+1));
                    getchar();
                }
                if (contactOption == 'R'){
                    getchar();
                }
            }
            
        }
        
        else if (answer == 'X'){
            loop = 0;
        }
    }while (loop == 1);
    return 0;
}
