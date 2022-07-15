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
#include <math.h>
#include "struct.h"

int editContact(FILE *fptr,contacts *record,strings *info,int i,int maxContacts){
    int phoneLoop = 0;
    char *buffer;
    char answer;
    fclose(fptr);
    fptr = fopen("myContactList.db","w+");
    unsigned long firstLength = 0;
    unsigned long lastLength = 0;
    unsigned long companyLength = 0;
    unsigned long emailLength = 0;
    buffer = malloc(sizeof(char)*1001);
    printf("First Name: %s\n",info[i].firstName);
    printf("Last Name: %s\n",info[i].lastName);
    printf("Company Name: %s\n",info[i].companyName);
    do{
        printf("Phone Number (enter only numbers): ");
        scanf("%lu",&info[i].phoneNumber);
        getchar();
        int phoneLength = log10(info[i].phoneNumber) + 1;
        if (phoneLength != 7 && phoneLength != 10){
            phoneLoop = 0;
            printf("You must enter either 7 or 10 digits\n");
        }
        else if (phoneLength == 7 || phoneLength == 10){
            phoneLoop = 1;
        }
    }while(phoneLoop == 0);
    printf("Email: ");
    fgets(buffer,1001,stdin);
    info[i].email = realloc(info[i].email,strlen(buffer)+1);
    strcpy(info[i].email,buffer);
    emailLength = strlen(info[i].email);
    info[i].email[emailLength-1] = '\0';
    
    printf("%s\n",info[i].firstName);
    printf("%s\n",info[i].lastName);
    printf("%s\n",info[i].companyName);
    printf("%ld\n",info[i].phoneNumber);
    printf("%s\n",info[i].email);
    int j = 0;
    printf("Action: ");
    answer = getchar();
    
    if (answer == 'D'){
        while (i<=maxContacts){
            info[i].firstName = info[i+1].firstName;
            info[i].lastName = info[i+1].lastName;
            info[i].companyName = info[i+1].companyName;
            info[i].phoneNumber = info[i+1].phoneNumber;
            info[i].email = info[i+1].email;
            i++;
        }
        maxContacts = maxContacts - 1;
        while(j<=maxContacts){
            /*convert phoneNumber into an unsigned long variable and store into record[i].phone_number*/
            record[j].phone_number = info[j].phoneNumber;
            
            /*if firstName isn't empty then calculate the length of firstName including the null character and calculate where the firstName will be stored in the file*/
            if (j == 0){
                if (info[j].firstName[0] != '\0'){
                    firstLength = strlen(info[j].firstName) + 1;
                    record[j].first_name_posn = 0 + 48;
                }
                /*if firstName is empty then set the firstLength to 0 and set the position of firstName in the file to 0*/
                if (info[j].firstName[0] == '\0'){
                    firstLength = 0;
                    record[j].first_name_posn = 0;
                }
                /*repeat this process for all other inputs as well*/
                
                
                if (info[j].lastName[0] != '\0'){
                    lastLength = strlen(info[j].lastName) + 1;
                    record[j].last_name_posn = 48 + 0 + firstLength;
                }
                else if (info[j].lastName[0] == '\0'){
                    lastLength = 0;
                    record[j].last_name_posn = 0;
                }
                
                
                if (info[j].companyName[0] != '\0'){
                    companyLength = strlen(info[j].companyName) + 1;
                    record[j].company_name_posn = 48 + 0 + firstLength + lastLength;
                }
                else if (info[j].companyName[0] == '\0'){
                    companyLength = 0;
                    record[j].company_name_posn = 0;
                }
                
                
                if (info[j].email[0] != '\0'){
                    emailLength = strlen(info[j].email) + 1;
                    record[j].email_posn = 48 + 0 + firstLength + lastLength + companyLength;
                }
                else if (info[j].email[0] == '\0'){
                    emailLength = 0;
                    record[j].email_posn = 0;
                }
                
                
                record[j].next = 48 + 0 + firstLength + lastLength + companyLength + emailLength;
            }
            else{
                if (info[j].firstName[0] != '\0'){
                    firstLength = strlen(info[j].firstName) + 1;
                    record[j].first_name_posn = record[j-1].next + 48;
                }
                /*if firstName is empty then set the firstLength to 0 and set the position of firstName in the file to 0*/
                if (info[j].firstName[0] == '\0'){
                    firstLength = 0;
                    record[j].first_name_posn = 0;
                }
                /*repeat this process for all other inputs as well*/
                
                
                if (info[j].lastName[0] != '\0'){
                    lastLength = strlen(info[j].lastName) + 1;
                    record[j].last_name_posn = 48 + record[j-1].next + firstLength;
                }
                else if (info[j].lastName[0] == '\0'){
                    lastLength = 0;
                    record[j].last_name_posn = 0;
                }
                
                
                if (info[j].companyName[0] != '\0'){
                    companyLength = strlen(info[j].companyName) + 1;
                    record[j].company_name_posn = 48 + record[j-1].next + firstLength + lastLength;
                }
                else if (info[j].companyName[0] == '\0'){
                    companyLength = 0;
                    record[j].company_name_posn = 0;
                }
                
                
                if (info[j].email[0] != '\0'){
                    emailLength = strlen(info[j].email) + 1;
                    record[j].email_posn = 48 + record[j-1].next + firstLength + lastLength + companyLength;
                }
                else if (info[j].email[0] == '\0'){
                    emailLength = 0;
                    record[j].email_posn = 0;
                }
                /*calculate where the position of where the next contact will be stored in file*/
                record[j].next = 48 + record[j-1].next + firstLength + lastLength + companyLength + emailLength;
            }
    
            /*write the current iteration of the struct into file*/
            fwrite(&record[j],sizeof(contacts),1,fptr);
            
            /*if firstName isn't empty then write firstName to the file*/
            if (info[j].firstName[0] != '\0'){
                fwrite(info[j].firstName,firstLength,1,fptr);
            }
            /*if firstName is empty then do nothing*/
            else if (info[j].firstName[0] == '\0'){
                
            }
            /*repeat this process for all the other inputs*/
            
            if (info[j].lastName[0] != '\0'){
                fwrite(info[j].lastName,lastLength,1,fptr);
            }
            else if (info[j].lastName[0] == '\0'){
                
            }
            
            if (info[j].companyName[0] != '\0'){
                fwrite(info[j].companyName,companyLength,1,fptr);
            }
            else if (info[j].companyName[0] == '\0'){
                
            }
            
            if (info[j].email[0] != '\0'){
                fwrite(info[j].email,emailLength,1,fptr);
            }
            else if (info[j].email[0] == '\0'){
                
            }
            j++;
        }
    }
    
    
    else if (answer == 'S'){
        while(j<=maxContacts){
            /*set record phoneNumber equal to the phoneNumber in my struct*/
            record[j].phone_number = info[j].phoneNumber;
            
            /*if firstName isn't empty then calculate the length of firstName including the null character and calculate where the firstName will be stored in the file*/
            if (j == 0){
                if (info[j].firstName[0] != '\0'){
                    firstLength = strlen(info[j].firstName) + 1;
                    record[j].first_name_posn = 0 + 48;
                }
                /*if firstName is empty then set the firstLength to 0 and set the position of firstName in the file to 0*/
                if (info[j].firstName[0] == '\0'){
                    firstLength = 0;
                    record[j].first_name_posn = 0;
                }
                /*repeat this process for all other inputs as well*/
                
                
                if (info[j].lastName[0] != '\0'){
                    lastLength = strlen(info[j].lastName) + 1;
                    record[j].last_name_posn = 48 + 0 + firstLength;
                }
                else if (info[j].lastName[0] == '\0'){
                    lastLength = 0;
                    record[j].last_name_posn = 0;
                }
                
                
                if (info[j].companyName[0] != '\0'){
                    companyLength = strlen(info[j].companyName) + 1;
                    record[j].company_name_posn = 48 + 0 + firstLength + lastLength;
                }
                else if (info[j].companyName[0] == '\0'){
                    companyLength = 0;
                    record[j].company_name_posn = 0;
                }
                
                
                if (info[j].email[0] != '\0'){
                    emailLength = strlen(info[j].email) + 1;
                    record[j].email_posn = 48 + 0 + firstLength + lastLength + companyLength;
                }
                else if (info[j].email[0] == '\0'){
                    emailLength = 0;
                    record[j].email_posn = 0;
                }
                
                record[j].next = 48 + 0 + firstLength + lastLength + companyLength + emailLength;
            }
            
            else{
                if (info[j].firstName[0] != '\0'){
                    firstLength = strlen(info[j].firstName) + 1;
                    record[j].first_name_posn = record[j-1].next + 48;
                }
                /*if firstName is empty then set the firstLength to 0 and set the position of firstName in the file to 0*/
                if (info[j].firstName[0] == '\0'){
                    firstLength = 0;
                    record[j].first_name_posn = 0;
                }
                /*repeat this process for all other inputs as well*/
                
                
                if (info[j].lastName[0] != '\0'){
                    lastLength = strlen(info[j].lastName) + 1;
                    record[j].last_name_posn = 48 + record[j-1].next + firstLength;
                }
                else if (info[j].lastName[0] == '\0'){
                    lastLength = 0;
                    record[j].last_name_posn = 0;
                }
                
                
                if (info[j].companyName[0] != '\0'){
                    companyLength = strlen(info[j].companyName) + 1;
                    record[j].company_name_posn = 48 + record[j-1].next + firstLength + lastLength;
                }
                else if (info[j].companyName[0] == '\0'){
                    companyLength = 0;
                    record[j].company_name_posn = 0;
                }
                
                
                if (info[j].email[0] != '\0'){
                    emailLength = strlen(info[j].email) + 1;
                    record[j].email_posn = 48 + record[j-1].next + firstLength + lastLength + companyLength;
                }
                else if (info[j].email[0] == '\0'){
                    emailLength = 0;
                    record[j].email_posn = 0;
                }
                /*calculate where the position of where the next contact will be stored in file*/
                record[j].next = 48 + record[j-1].next + firstLength + lastLength + companyLength + emailLength;
            }
            

            /*write the current iteration of the struct into file*/
            fwrite(&record[j],sizeof(contacts),1,fptr);
            
            /*if firstName isn't empty then write firstName to the file*/
            if (info[j].firstName[0] != '\0'){
                fwrite(info[j].firstName,firstLength,1,fptr);
            }
            /*if firstName is empty then do nothing*/
            else if (info[j].firstName[0] == '\0'){
                
            }
            /*repeat this process for all the other inputs*/
            
            if (info[j].lastName[0] != '\0'){
                fwrite(info[j].lastName,lastLength,1,fptr);
            }
            else if (info[j].lastName[0] == '\0'){
                
            }
            
            if (info[j].companyName[0] != '\0'){
                fwrite(info[j].companyName,companyLength,1,fptr);
            }
            else if (info[j].companyName[0] == '\0'){
                
            }
            
            if (info[j].email[0] != '\0'){
                fwrite(info[j].email,emailLength,1,fptr);
            }
            else if (info[j].email[0] == '\0'){
                
            }
            j++;
        }
    }
    
    free(buffer);
    return maxContacts;
}
