/*
//  storeStrings.c
//  Assignment3
//
//  Created by Jonalton Jude Hamilton on 2019-03-12.
//  Copyright © 2019 Jonalton Jude Hamilton. All rights reserved.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

void storeStrings(FILE *fptr,contacts *record,int i){
    
    /*initialize variables and allocate memory*/
    char *firstName = NULL;
    char *lastName = NULL;
    char *companyName = NULL;
    char *phoneNumber = NULL;
    char *email = NULL;
    char *buffer = NULL;
    buffer = malloc(sizeof(char)*1001);
    
    /*Get input from user for First Name and store into a buffer*/
    printf("First Name: ");
    fgets(buffer,1001,stdin);
    /*allocate memory for firstName according to the length of buffer + 1*/
    firstName = realloc(firstName,(strlen(buffer)+1));
    /*copy the contents of buffer into firstName*/
    strcpy(firstName,buffer);
    /*set firstLength to the length of FirstName*/
    unsigned long firstLength = strlen(firstName);
    /*set the last character of firstName to the null character*/
    firstName[firstLength-1] = '\0';
    /*repeat this process for the other inputs*/
    
    printf("Last Name: ");
    fgets(buffer,1001,stdin);
    lastName = realloc(lastName,strlen(buffer)+1);
    strcpy(lastName,buffer);
    unsigned long lastLength = strlen(lastName);
    lastName[lastLength-1] = '\0';
    
    printf("Company Name: ");
    fgets(buffer,1001,stdin);
    companyName = realloc(companyName,strlen(buffer)+1);
    strcpy(companyName,buffer);
    unsigned long companyLength = strlen(companyName);
    companyName[companyLength-1] = '\0';
    
    /*for the phone number input theres a dowhile loop that continues if the user doesn't input anything*/
    do{
        printf("Phone Number (enter only numbers): ");
        fgets(buffer,1001,stdin);
        phoneNumber = realloc(phoneNumber,strlen(buffer)+1);
        strcpy(phoneNumber,buffer);
        unsigned long phoneLength = strlen(phoneNumber);
        phoneNumber[phoneLength-1] = '\0';
    }while(buffer[0] == '\n');
    
    printf("Email: ");
    fgets(buffer,1001,stdin);
    email = realloc(email,strlen(buffer)+1);
    strcpy(email,buffer);
    unsigned long emailLength = strlen(email);
    email[emailLength-1] = '\0';
    
    /*free allocated memory for buffer*/
    free(buffer);
    
    /*convert phoneNumber into an unsigned long variable and store into record[i].phone_number*/
    record[i].phone_number = strtoul(phoneNumber,NULL,0);

    /*if firstName isn't empty then calculate the length of firstName including the null character and calculate where the firstName will be stored in the file*/
    if (firstName[0] != '\0'){
        firstLength = strlen(firstName) + 1;
        record[i].first_name_posn = record[i-1].next + 48;
    }
    /*if firstName is empty then set the firstLength to 0 and set the position of firstName in the file to 0*/
    if (firstName[0] == '\0'){
        firstLength = 0;
        record[i].first_name_posn = 0;
    }
    /*repeat this process for all other inputs as well*/
    
    
    if (lastName[0] != '\0'){
        lastLength = strlen(lastName) + 1;
        record[i].last_name_posn = 48 + record[i-1].next + firstLength;
    }
    else if (lastName[0] == '\0'){
        lastLength = 0;
        record[i].last_name_posn = 0;
    }
    
    
    if (companyName[0] != '\0'){
        companyLength = strlen(companyName) + 1;
        record[i].company_name_posn = 48 + record[i-1].next + firstLength + lastLength;
    }
    else if (companyName[0] == '\0'){
        companyLength = 0;
        record[i].company_name_posn = 0;
    }
    
    
    if (email[0] != '\0'){
        emailLength = strlen(email) + 1;
        record[i].email_posn = 48 + record[i-1].next + firstLength + lastLength + companyLength;
    }
    else if (email[0] == '\0'){
        emailLength = 0;
        record[i].email_posn = 0;
    }
    
    
    /*calculate where the position of where the next contact will be stored in file*/
    record[i].next = 48 + record[i-1].next + firstLength + lastLength + companyLength + emailLength;

    /*write the current iteration of the struct into file*/
    fwrite(&record[i],sizeof(contacts),1,fptr);
    
    /*if firstName isn't empty then write firstName to the file*/
    if (firstName[0] != '\0'){
        fwrite(firstName,firstLength,1,fptr);
    }
    /*if firstName is empty then do nothing*/
    else if (firstName[0] == '\0'){
        
    }
    /*repeat this process for all the other inputs*/
    
    if (lastName[0] != '\0'){
        fwrite(lastName,lastLength,1,fptr);
    }
    else if (lastName[0] == '\0'){
        
    }
    
    if (companyName[0] != '\0'){
        fwrite(companyName,companyLength,1,fptr);
    }
    else if (companyName[0] == '\0'){
        
    }
    
    if (email[0] != '\0'){
        fwrite(email,emailLength,1,fptr);
    }
    else if (email[0] == '\0'){
        
    }
    
    /*call function freeStrings to free the inputs*/
    freeStrings(firstName, lastName, companyName,phoneNumber,email);
}
