/*
//  readStrings.c
//  Assignment3
//
//  Created by Jonalton Jude Hamilton on 2019-03-12.
//  Copyright © 2019 Jonalton Jude Hamilton. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void readStrings(contacts *record,strings *info,int i,FILE *fptr){
    
    char *buffer;
    buffer = malloc(sizeof(char)*1001);
    
    
    printf("%d\n",i);

    
    
    if (i == 0){
        fseek(fptr,0,SEEK_SET);
        /*store the info in the file to the current iteration of record*/
        fread(&record[i],sizeof(contacts),1,fptr);
        
        /*go to the position where each contact is stored*/
        fseek(fptr,0,SEEK_SET);
        
        /*store the phone number that was read into my struct*/
        fread(&info[i].phoneNumber,sizeof(unsigned long),1,fptr);
    }
    
    else if (i != 0){
        fseek(fptr,record[i-1].next,SEEK_SET);
        /*store the info in the file to the current iteration of record*/
        fread(&record[i],sizeof(contacts),1,fptr);
        /*go to the position where each contact is stored*/
        fseek(fptr,record[i-1].next,SEEK_SET);
        /*store the phone number that was read into my struct*/
        fread(&info[i].phoneNumber,sizeof(unsigned long),1,fptr);
    }
    printf("first pos %lu\n",record[i].first_name_posn);
    printf("last pos %lu\n",record[i].last_name_posn);
    printf("comp pos %lu\n",record[i].company_name_posn);
    printf("email pos %lu\n",record[i].email_posn);
    printf("next pos %lu\n",record[i].next);
    printf("PN: %lu\n",info[i].phoneNumber);
    
    /*if firstName isn't stored at 0 then read in the value to firstName*/
    if (record[i].first_name_posn != 0){
        /*go to the position of firstName in the file*/
        fseek(fptr,record[i].first_name_posn,SEEK_SET);
        /*read the first name into a buffer*/
        fread(buffer,record[i].first_name_posn,1,fptr);
        /*allocate memory for firstName equivalent to the length of buffer plus one character for the null character*/
        info[i].firstName = malloc(strlen(buffer)+1);
        /*copy buffer into firstName*/
        strcpy(info[i].firstName,buffer);
    }
    /*if the position of firstName is at 0 set firstName equal to the null character*/
    else if(record[i].first_name_posn == 0){
        /*allocate memory for firstName equivalent to the size of a char */
        info[i].firstName = malloc(sizeof(char));
        /*copy the null character into firstName*/
        strcpy(info[i].firstName,"\0");
    }
    /*repeat this process for all the other credentials*/
    
    /*Last name*/
    
    if (record[i].last_name_posn != 0){
        fseek(fptr,record[i].last_name_posn,SEEK_SET);
        fread(buffer,record[i].last_name_posn,1,fptr);
        info[i].lastName = malloc(strlen(buffer)+1);
        strcpy(info[i].lastName,buffer);
    }
    else if (record[i].last_name_posn == 0){
        info[i].lastName = malloc(sizeof(char));
        strcpy(info[i].lastName,"\0");
    }
    
    /*Company Name*/
    
    if (record[i].company_name_posn != 0){
        fseek(fptr,record[i].company_name_posn,SEEK_SET);
        fread(buffer,record[i].company_name_posn,1,fptr);
        info[i].companyName = malloc(strlen(buffer)+1);
        strcpy(info[i].companyName,buffer);
    }
    else if(record[i].company_name_posn == 0){
        info[i].companyName = malloc(sizeof(char));
        strcpy(info[i].companyName,"\0");
    }
    
    
    /*Email*/
    
    if (record[i].email_posn != 0){
        fseek(fptr,record[i].email_posn,SEEK_SET);
        fread(buffer,record[i].email_posn,1,fptr);
        info[i].email = malloc(strlen(buffer)+1);
        strcpy(info[i].email,buffer);
    }
    else if (record[i].email_posn == 0){
        info[i].email = realloc(info[i].email,sizeof(char));
        strcpy(info[i].email,"\0");
    }
    
    
    /*print out all the credentials*/
    printf("First Name: %s\n",info[i].firstName);
    printf("Last Name: %s\n",info[i].lastName);
    printf("Company Name: %s\n",info[i].companyName);
    printf("Phone Number: %ld\n",info[i].phoneNumber);
    printf("Email: %s\n",info[i].email);
    
    
    
    fseek(fptr,record[i].next,SEEK_SET);
    
}
