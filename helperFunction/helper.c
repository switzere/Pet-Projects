#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

#include "helper.h"

/*
Input: number of delimeters, array of strings for the output to go into, delimeters
Output: number of tokens the string has been split up into
If -1 is returned that means an error occured
*/
int strsplt(int num, char*** tokens, char* input,...){

  char** tempTokens;
  int tokenNum = 1;

  int tStart = 0;
  int tEnd = 0;
  int tokenPos = 0;
  int delimHit = 0;//0 means no delim hit, 1 means delim hit
  int tempK = 0;

  va_list valist;
  va_start(valist, input);

  char* delimeters = malloc(sizeof(char)*num);

  for(int i = 0; i < num; i++){
    delimeters[i] = va_arg(valist, int);
    for(int j = i-1; j >= 0; j--){
      if(delimeters[i] == delimeters[j]){
        printf("ERROR: Duplicate delimeters\n");
        return -1;
      }
    }
  }

  //printf("%s\n",input);
  for(int i = 0; i < strlen(input); i++){
    for(int j = 0; j < num; j++){
      if(delimeters[j] == input[i]){
        tokenNum++;
      }
    }
  }

  tempTokens = malloc(sizeof(char*)*(tokenNum+1));
  for(int i = 0; i < tokenNum; i++){
    tempTokens[i] = malloc(0);
  }

  for(int i = 0; i < strlen(input); i++){

    delimHit = 0;
    for(int j = 0; j < num; j++){
      if(delimeters[j] == input[i]){

        delimHit = 1;

      }
    }
      if(delimHit == 1){
        //printf("end-start: %d\n",tEnd-tStart);
        tempTokens[tokenPos] = realloc(tempTokens[tokenPos], sizeof(char)*((tEnd-tStart)+1));
        tempK = tStart;
        for(int k = tStart; k < tEnd; k++){
          tempTokens[tokenPos][(k-tStart)] = input[k];
          tempK = k;
        }
        //printf("tokenPos: %d, tempK: %d, tStart: %d\n",tokenPos,tempK,tStart);
        if(tempK-tStart != 0){
          tempTokens[tokenPos][(tempK-tStart)+1] = '\0';
        }
        else{
          tempTokens[tokenPos][(tempK-tStart)] = '\0';
        }

        tEnd++;
        tStart = tEnd;
        tokenPos++;

      }
      else{
        tEnd++;
      }


  }

  tempTokens[tokenPos] = realloc(tempTokens[tokenPos], sizeof(char)*(tEnd-tStart+1));

  tempK = tStart;
  for(int k = tStart; k < tEnd; k++){
    tempTokens[tokenPos][k-tStart] = input[k];
    tempK = k;
  }
  if(tempK-tStart != 0){
    tempTokens[tokenPos][(tempK-tStart)+1] = '\0';
  }
  else{
    tempTokens[tokenPos][(tempK-tStart)] = '\0';
  }

  (*tokens) = tempTokens;


  free(delimeters);
  //free(tempTokens);




  return tokenNum;
}

/*
Input: Array where file lines will end up, file name
Output: number of lines
If -1 is returned that means an error occured
*/
int readFile(char*** fileLines, char* fileName){

  FILE* fp;
  char* buffer;
  int bufferSize;
  int ret = -1;



  fp = fopen(fileName, "r");

  if(fp != NULL){

    fseek(fp, 0, SEEK_END);
    bufferSize = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    //bufferSize+=sizeof(char);
    buffer = malloc(bufferSize);

    if(buffer != NULL){
      fread(buffer, 1, bufferSize, fp);
    }
    fclose(fp);


    buffer[(bufferSize/sizeof(char))-1] = '\0';
    //printf("buffer @ 0: %c\n",buffer[(bufferSize/sizeof(char))-1]);

  }

  if(buffer != NULL){
     ret = strsplt(1, fileLines, buffer, '\n');
  }

  //free(fp);
  free(buffer);

  return ret;

}

/*
Input: array of ints to be sorted, size of array, OPTIONAL: 1 or -1 for ascending/descending(defaults to 1)
*/
void sortInt(int** array, int size,...){

  int upOrDown = 1;
  int* tempArray; //= malloc(sizeof(int)*size); //IF THIS GETS MALLOCED and then set to a different point the mallced stuff gets lost in space
  tempArray = (*array);

  va_list valist;
  va_start(valist, size);
  upOrDown = va_arg(valist, int);

  if(upOrDown != -1){
    upOrDown = 1;
  }


  for(int i = 0; i < size - 1; i++){
    for(int j = i+1; j < size; j++){
      printf("i: %d, j: %d\n",i,j);
      if(tempArray[j]*upOrDown < tempArray[i]*upOrDown){
        tempArray[j] = tempArray[j] + tempArray[i];
        tempArray[i] = tempArray[j] - tempArray[i];
        tempArray[j] = tempArray[j] - tempArray[i];
      }
    }
  }

  (*array) = tempArray;


}


/*
Input: array of strings to be sorted, size of array, OPTIONAL: 1 or -1 for ascending/descending(defaults to 1)
*/
void sortStr(char*** array, int size,...){

  int upOrDown = 1;
  char** tempArray; //= malloc(sizeof(int)*size); //IF THIS GETS MALLOCED and then set to a different point the mallced stuff gets lost in space
  tempArray = (*array);
  char tempStr[1000];

  va_list valist;
  va_start(valist, size);
  upOrDown = va_arg(valist, int);

  if(upOrDown != -1){
    upOrDown = 1;
  }


  for(int i = 0; i < size - 1; i++){
    for(int j = i+1; j < size; j++){
      //printf("i: %d, j: %d\n",i,j);
      if(strcmp(tempArray[j], tempArray[i]) > 0 && upOrDown == -1){
        strcpy(tempStr, tempArray[j]);
        strcpy(tempArray[j], tempArray[i]);
        strcpy(tempArray[i], tempStr);
      }
      else if(strcmp(tempArray[j], tempArray[i]) < 0 && upOrDown == 1){
        strcpy(tempStr, tempArray[j]);
        strcpy(tempArray[j], tempArray[i]);
        strcpy(tempArray[i], tempStr);
      }
    }
  }

  (*array) = tempArray;


}



void swap(void** A, void** B){
  void* C;
  C = (*A);
  (*A) = (*B);
  (*B) = C;
}
