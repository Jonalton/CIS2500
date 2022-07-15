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

int readStrings(FILE *fptr){
    /*initialize variables and dynamically allocate memory*/
    char *buffer = NULL;
    buffer = malloc(sizeof(char)*1001);
    char *firstName = NULL;
    char *lastName = NULL;
    char *companyName = NULL;
    char *phoneNumber = NULL;
    char *email = NULL;
    contacts *record = NULL;
    record = malloc(sizeof(contacts));
    int loop = 1;
    char *answer1 = malloc(sizeof(char)*4);
    
    /*set the first next value to 0*/
    record[0].next = 0;
    
    /*Ask the user if they want to retrieve a contact*/
    printf("Do you wish to retrieve a contact(Yes or No)?: ");
    fgets(answer1,4,stdin);
    
    /*if user enters Yes then print out information stored in file for the corresponding phone number*/
    if(strncmp(answer1,"Yes",3) == 0){
        getchar();
        /*initialize variable*/
        unsigned long tempNumber,posNumber;
        tempNumber = 0;
        posNumber = 0;
        /*user input for phone number and store it into a buffer*/
        printf("Phone Number: ");
        fgets(buffer,1001,stdin);
        /*printf("%lu\n",strlen(buffer));*/
        /*allocate memory for phoneNumber equivalent to the length of buffer*/
        phoneNumber = realloc(phoneNumber,strlen(buffer)+1);
        /*copy buffer into phoneNumber*/
        strcpy(phoneNumber,buffer);
        /*printf("length phone#:%lu\n",strlen(phoneNumber));*/
        /*set the last character of phoneNumber to the null character*/
        unsigned long phoneLength = strlen(phoneNumber);
        phoneNumber[phoneLength-1] = '\0';
        
        /*convert phoneNumber into an unsigned long variable as store in temp Number*/
        tempNumber = strtoul(phoneNumber,NULL,0);
        
        int j = 1;
        
        /*do while loop continues until the end of file has been reached*/
        do{
            /*reallocate memory for record*/
            record = realloc(record,sizeof(contacts)*(j+1));
            /*go to the position where each contact is stored*/
            fseek(fptr,record[j-1].next,SEEK_SET);
            /*store the info in the file to the current iteration of record*/
            fread(&record[j],sizeof(contacts),1,fptr);
            /*go to the position where each contact is stored*/
            fseek(fptr,record[j-1].next,SEEK_SET);
            /*store the phone number that was read into posNumber*/
            fread(&posNumber,sizeof(unsigned long),1,fptr);
            
            /*read from the file if tempNumbre and posNumber are the same*/
            if (tempNumber == posNumber){
                
                /*if firstName isn't stored at 0 then read in the value to firstName*/
                if (record[j].first_name_posn != 0){
                    /*go to the position of firstName in the file*/
                    fseek(fptr,record[j].first_name_posn,SEEK_SET);
                    /*read the first name into a buffer*/
                    fread(buffer,record[j].first_name_posn,1,fptr);
                    /*allocate memory for firstName equivalent to the length of buffer plus one character for the null character*/
                    firstName = realloc(firstName,strlen(buffer)+1);
                    /*copy buffer into firstName*/
                    strcpy(firstName,buffer);
                }
                /*if the position of firstName is at 0 set firstName equal to the null character*/
                else if(record[j].first_name_posn == 0){
                    /*allocate memory for firstName equivalent to the size of a char */
                    firstName = realloc(firstName,sizeof(char));
                    /*copy the null character into firstName*/
                    strcpy(firstName,"\0");
                }
                /*repeat this process for all the other credentials*/
                
                /*Last name*/
                if (record[j].last_name_posn != 0){
                    fseek(fptr,record[j].last_name_posn,SEEK_SET);
                    fread(buffer,record[j].last_name_posn,1,fptr);
                    lastName = realloc(lastName,strlen(buffer)+1);
                    strcpy(lastName,buffer);
                }
                else if (record[j].last_name_posn == 0){
                    lastName = realloc(lastName,sizeof(char));
                    strcpy(lastName,"\0");
                }
                
                /*Company Name*/
                if (record[j].company_name_posn != 0){
                    fseek(fptr,record[j].company_name_posn,SEEK_SET);
                    fread(buffer,record[j].company_name_posn,1,fptr);
                    companyName = realloc(companyName,(strlen(buffer)+1));
                    strcpy(companyName,buffer);
                }
                else if(record[j].company_name_posn == 0){
                    companyName = realloc(companyName,sizeof(char));
                    strcpy(companyName,"\0");
                }
                
                /*Email*/
                if (record[j].email_posn != 0){
                    fseek(fptr,record[j].email_posn,SEEK_SET);
                    fread(buffer,record[j].email_posn,1,fptr);
                    email = realloc(email,(strlen(buffer)+1));
                    strcpy(email,buffer);
                }
                else if (record[j].email_posn == 0){
                    email = realloc(email,sizeof(char));
                    strcpy(email,"\0");
                }
                
                /*print out all the credentials*/
                printf("First Name: %s\n",firstName);
                printf("Last Name: %s\n",lastName);
                printf("Company Name: %s\n",companyName);
                printf("Phone Number: %lu\n",tempNumber);
                printf("Email: %s\n",email);
                break;
            }
            /*increase the value of j by 1*/
            j++;
            
        }while(!feof(fptr));
        
        /*if tempNumber and posNumber are not equal print there was no match found*/
        if(tempNumber != posNumber){
            printf("No match found.\n");
        }
        
    }
    /*if the user does not want to retrieve a contact set loop to 0 and free record*/
    else if(strncmp(answer1,"No",2) == 0){
        loop = 0;
        free(record);
    }
    
    /*free dynamically allocated memory*/
    free(buffer);
    free(answer1);
    
    /*call function freeStrings to free allocated memory for these strings*/
    freeStrings(firstName, lastName, companyName,phoneNumber, email);
    
    /*return the value of loop*/
    return loop;
}
