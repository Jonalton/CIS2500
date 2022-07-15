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

int writeContact(FILE *fptr,contacts *record,int i){
    
    /*initialize variables and allocate memory*/
    int valid = 0;
    char *firstName = NULL;
    char *lastName = NULL;
    char *companyName = NULL;
    char *phoneNumber = NULL;
    char *email = NULL;
    char *buffer = NULL;
    unsigned long firstLength;
    unsigned long lastLength;
    unsigned long companyLength;
    unsigned long emailLength;
    buffer = malloc(sizeof(char)*1001);
    
    /*Get input from user for First Name and store into a buffer*/
    printf("First Name: ");
    fgets(buffer,1001,stdin);
    /*allocate memory for firstName according to the length of buffer + 1*/
    firstName = realloc(firstName,(strlen(buffer)+1));
    /*copy the contents of buffer into firstName*/
    strcpy(firstName,buffer);
    /*set firstLength to the length of FirstName*/
    firstLength = strlen(firstName);
    /*set the last character of firstName to the null character*/
    firstName[firstLength-1] = '\0';
    /*repeat this process for the other inputs*/
    do{
        printf("Last Name: ");
        fgets(buffer,1001,stdin);
        lastName = realloc(lastName,strlen(buffer)+1);
        strcpy(lastName,buffer);
        lastLength = strlen(lastName);
        lastName[lastLength-1] = '\0';
        
        printf("Company Name: ");
        fgets(buffer,1001,stdin);
        companyName = realloc(companyName,strlen(buffer)+1);
        strcpy(companyName,buffer);
        companyLength = strlen(companyName);
        companyName[companyLength-1] = '\0';
        
        if (strcmp(lastName,"") == 0 && strcmp(companyName,"") == 0){
            printf("You must enter either a last name or a company name\n");
        }
        else if (strcmp(lastName,"") != 0 || strcmp(companyName,"") != 0){
            valid = 1;
        }
    }while(valid == 0);
    /*for the phone number input theres a dowhile loop that continues if the user doesn't input anything*/
    int phoneLoop = 1;
    int numeric = 1;
    do{
        
        printf("Phone Number (enter only numbers): ");
        fgets(buffer,1001,stdin);
        phoneNumber = realloc(phoneNumber,strlen(buffer)+1);
        strcpy(phoneNumber,buffer);
        unsigned long phoneLength = strlen(phoneNumber);
        phoneNumber[phoneLength-1] = '\0';
        printf("%lu\n",phoneLength);
        /*int j = 0;
         for (j=0;j<phoneLength;j++){
         if (isdigit(phoneNumber[j]) == 0){
         printf("%c\n",phoneNumber[j]);
         numeric = 0;
         }
         }
         if (numeric == 0){
         printf("You must enter numbers\n");
         }*/
        if ((phoneLength-1) != 7 && (phoneLength-1) != 10){
            phoneLoop = 0;
            printf("You must enter either 7 or 10 digits\n");
        }
        else if ((phoneLength-1) == 7 || (phoneLength-1) == 10){
            phoneLoop = 1;
        }
        
    }while((phoneLoop == 0) && (numeric == 0));
    
    
    printf("Email: ");
    fgets(buffer,1001,stdin);
    email = realloc(email,strlen(buffer)+1);
    strcpy(email,buffer);
    emailLength = strlen(email);
    email[emailLength-1] = '\0';
    
    
    printf("First Name: %s\n",firstName);
    printf("Last Name: %s\n",lastName);
    printf("Company Name: %s\n",companyName);
    printf("Phone Number: %s\n",phoneNumber);
    printf("Email: %s\n",email);
    
    /*free allocated memory for buffer*/
    free(buffer);
    char action;
    printf("Action: ");
    action = getchar();
    if (action == 'S'){
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
        
        fseek(fptr,0,SEEK_END);
        /*calculate where the position of where the next contact will be stored in file*/
        record[i].next = 48 + record[i-1].next + firstLength + lastLength + companyLength + emailLength;
        printf("first pos %lu\n",record[i].first_name_posn);
        printf("last pos %lu\n",record[i].last_name_posn);
        printf("comp pos %lu\n",record[i].company_name_posn);
        printf("email pos %lu\n",record[i].email_posn);
        printf("next pos %lu\n",record[i].next);
        
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
    }
    
    else if (action == 'R'){
        i = i-1;
    }
    
    free(firstName);
    free(lastName);
    free(companyName);
    free(phoneNumber);
    free(email);
    return i;
    /*call function freeStrings to free the inputs*/
}
