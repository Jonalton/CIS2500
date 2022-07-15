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
#include "contactList.h"

int main() {
    /*initialize file*/
    FILE *fptr;
    /*open file*/
    fptr = fopen("myContactList.db","ab+");
    /*print if file could not be created and end program*/
    if (fptr == NULL){
        printf("file could not be created");
        return -1;
    }


    /*go back to the end of the file*/
    
    /*initialize variables and dynamically allocate memory*/
    int i = 1;
    char *answer = NULL;
    answer = malloc(sizeof(char)*4);
    contacts *record = NULL;
    record = malloc(sizeof(contacts));
    /*set first next value to 0*/
    record[0].next = 0;
    char *buffer = NULL;
    buffer = malloc(sizeof(char)*1000);
    
    
    long size = ftell(fptr);
    /*if the file is not empty read all the previously existing contacts and store it into record*/
    if (size != 0){
        fseek(fptr,0,SEEK_SET);
        while(!feof(fptr)){
            record = realloc(record,sizeof(contacts)*(i+1));
            fseek(fptr,record[i-1].next,SEEK_SET);
            fread(&record[i],sizeof(contacts),1,fptr);
            i++;
        }
        i=i-1;
    }

    /*free allocated memory*/
    free(buffer);
    
    int loop = 1;
    
    /*do while loop that continues as long as loop is equal to 1*/
    do{
        /*asks user if they want to enter a contact*/
        printf("Do you wish to enter a contact (Yes or No)?: ");
        fgets(answer,4,stdin);
    
        /*if user enters Yes reallocate memory for record and call function storeStrings*/
        if (strncmp(answer,"Yes",3) == 0){
            getchar();
            
            record = realloc(record,sizeof(contacts)*(i+2));
            storeStrings(fptr,record,i);
            i++;
        
        }
        
        /*if user enters No call on function readStrings and set loop to the return value of readStrings*/
        else if (strncmp(answer,"No",2) == 0){
            loop = readStrings(fptr);
        }
    }while(loop == 1);
    /*free allocated memory*/
    free(answer);
    free(record);
    
    /*close file*/
    fclose(fptr);
    return 0;
}
