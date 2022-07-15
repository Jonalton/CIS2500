//
//  main.c
//  Assignment 2
//
//  Created by Jonalton Jude Hamilton on 2019-02-07.
//  Copyright © 2019 Jonalton Jude Hamilton. All rights reserved.
//

//include headers
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

//define functions
char *stringArray(FILE *myfile);
void freeString(char *readData);
int countWords(char *readData);
int countSyllables(char *readData);
int countSentences(char *readData);

//this is the main functions where the other functions are called and the flesch index is calculated
int main() {
    //declare variables

    int totalWords,totalSyllables,totalSentences;
    double fleschIndex;
    
    //open the file
    FILE *myfile = fopen("sample2.txt","r");
    //if the file could not be opened tell user it couldnt be opened on stdout
    if (myfile == NULL){
        printf("File did not open properly\n");
        return -1;
    }

    //create variable to store the file in
    char *readData = NULL;
    //the return value of stringArray is the file and gets stored in readData
    readData = stringArray(myfile);
    
    
    //set the return value of each function to its corresponding variable
    totalWords = countWords(readData);
    totalSyllables = countSyllables(readData);
    totalSentences = countSentences(readData);
    
    //calculate fleschIndex and round to the nearest integer
    fleschIndex = round(206.835 - 84.6 * (totalSyllables/totalWords) - 1.015*(totalWords/totalSentences));
    //print output
    printf("Flesch Index = %.0f\n",fleschIndex);
    printf("Syllable Count = %d\n",totalSyllables);
    printf("Word Count = %d\n",totalWords);
    printf("Sentence Count = %d\n",totalSentences);
    
    //close the file
    fclose(myfile);
    
    //call the function to free the array used to store the file
    //freeString(readData,&maxLines);
    return 0;
}

//this function stores the file into an array to be used for counting the number of words, syllables, and sentences
char *stringArray(FILE *myfile){
    //declare variables
    int j;
    char *readData = NULL;
    char *line;
    j=0;
    
    //allocate 1 byte of memory for the two variables, gets increased in the while loop
    readData = malloc(sizeof(char*)* 1);
    line = malloc(sizeof(char*)*1);
    
    //while loop runs as long as the end of file has not been reached
    while(!feof(myfile)){
        
        //get in character from the file at a time and store it into line
        line[j] = fgetc(myfile);
        //increase j by 1
        j++;
        //reallocate how much data can be stored by 1
        line = realloc(line,sizeof(char*)*(j+1));
        readData = realloc(readData,sizeof(char*)*(j+1));
        
        //copy line into readData
        strcpy(readData,line);
    }
    return readData;
}

//this function frees the data that was allocated in **stringArray
void freeString(char *readData){
    free(readData);
}

//this function counts the total number of words in the file
int countWords(char *readData){
    //declare variables
    int j,count,i,k;
    //allocate space for the number of possible scenarios symbolizing a word
    char *words = malloc(sizeof(char*)*7);
    words[0] = ' ';
    words[1] = '.';
    words[2] = '!';
    words[3] = '?';
    words[4] = ':';
    words[5] = ';';
    words[6] = '\n';
    
    count = 0;
    j=0;
    
    //do-while loop counts the number of words until it reaches the null character
    do{
        //if the value at readData is equal to one of the 7 possible scenarios increase count by 1
        for(i=0;i<7;i++){
            if (readData[j] == words[i]){
                count++;
            }
        }
        
        //if there is a repeated scenario right after eachother decrease count by 1
        for(i=0;i<7;i++){
            for(k=0;k<7;k++){
                if (readData[j] == words[i] && readData[j+1] == words[k]){
                    count--;
                }
            }
        }
        
        j++;
    }while(readData[j] != '\0');
    
    //free the data allocated for words
    free(words);
    //return the number of words counted
    return count;
}

//this function counts the number of syllables in the file
int countSyllables(char *readData){
    //declare variables
    int count,j,i,k;
    //allocate space for each vowel
    char *vowels;
    vowels = malloc(sizeof(char*)*5);
    vowels[0] = 'a';
    vowels[1] = 'e';
    vowels[2] = 'i';
    vowels[3] = 'o';
    vowels[4] = 'u';
    
    j = 0;
    count = 0;
    
    //do-while loops counts the number of syllables until it reaches the null character
    do{
        
        //if there is a vowel increase the count by 1
        for(i=0;i<5;i++){
            if (readData[j] == vowels[i]){
                count++;
            }
        }
        
        //for each adjacent vowel decrease the count by 1
        for(i=0;i<5;i++){
            for(k=0;k<5;k++){
                if (readData[j] == vowels[i] && readData[j+1] == vowels[k]){
                    count--;
                }
            }
        }
        if (readData[j] == vowels[1] && readData[j-2] == ' '){
            count++;
        }
        
        if (readData[j] == vowels[1] && readData[j-1] == 'h' && (readData[j-2] == 'T' || readData[j-2] == 't')){
            count++;
        }
        //if 'e' is at the end of a word, decrease the count by 1
        if (readData[j] == vowels[1] && readData[j+1] == ' '){
            count--;
        }
        
        j++;
    }while(readData[j] != '\0');
    
    //free the data allocated for the vowels
    free(vowels);
    //return the number of syllables counted
    return count;
}

//the function counts the number of sentences in the file
int countSentences(char *readData){
    //declare variables
    int count,i,j,k;
    //allocated space for each punctuation that symbolizes a sentence
    char *punctuation;
    punctuation = malloc(sizeof(char*)*5);
    punctuation[0] = '.';
    punctuation[1] = '!';
    punctuation[2] = '?';
    punctuation[3] = ':';
    punctuation[4] = ';';
    
    j = 0;
    count = 0;
    
    //do-while loop counts the number of sentences until it reaches the null character
    do{
        //if there is a punctuation that represents the end of a sentence increase the count by 1
        for(i=0;i<5;i++){
            if(readData[j] == punctuation[i]){
                count++;
            }
        }
        
        //if there is a repeated punctuation decrease the count by 1
        for(i=0;i<5;i++){
            for(k=0;k<5;k++){
                if(readData[j] == punctuation[i] && readData[j+1] == punctuation[k]){
                    count--;
                }
            }
        }
        
        j++;
    }while(readData[j] != '\0');
    
    //free the data allocated for each punctuation
    free(punctuation);
    //return the number of sentences counted
    return count;
}
