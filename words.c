/*     

Task 1: O(n^2)
- Each word needs to be checked against every other word in the graph
- This requires at most n^2 operations to complete this task

Task 2: O(2^n)
- Finding the maximum sequence number requires checking all of the possible combinations of word sequences
- Collecting all the words into an array to print all of the sequences also requires finding them and putting them into an array
- The variables max and max_words help reduce this but it it is still within O(2^n) notation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#include <assert.h>
#include <ctype.h>

//maximum number of characters in a word
#define MAXWORD 31

//make both the number of words and the max sequences a global variable to reference throughout the program
int n;

//max in particular assists with the recursive function findMax and word
int max=0;

//max_words is used to find the most word associations one particular word has
int max_words=0;



int strComparisonWordLengthDif(char sWord_1[],char lWord_2[], int len)
{
   //this is used when we find a letter that is not part of the smaller word in comparison to the larger word
   //This is only allowed once to stay true to defintion of a word sequence
   int extra = 0;

   //word count needs to be equal to the length of the smaller word to be considered true
   int word_count = 0;

   for(int i = 0; i<len; i++)
   {
      //here we check each letter of the smaller word
      if (sWord_1[i] == lWord_2[i+extra])
         {
            word_count +=1;
            sWord_1[i] = '0';
            lWord_2[i+extra] = '0';
         }

      //if the larger word has a letter that is not part of the smaller word, we allow one difference to occur and repeat the loop step with i incremented by 1
      //This takes the additional letter into consideration when it is applied
      else if (sWord_1[i] != lWord_2[i+extra])
         {
            if(extra ==1)
            {
               return 0;  
            }
            i--;
            extra++;
         }
   }
   //word count needs to be equal to the length of the smaller word to be considered true
   if (word_count == len)
   {
      return 1;
   }
   else
   {   
      return 0;
   }
}

int strComparison(char word_1[],char word_2[])
{
   //find the length of both words
   int str_1_len = strlen(word_1);
   int str_2_len = strlen(word_2);

   //create a copy so that we dont edit each word
   char str_1[str_1_len];
   char str_2[str_2_len];

   //cant use strcpy with CSE machines
   for(int w = 0; w<str_1_len; w++)
      {
         str_1[w] = word_1[w];
      }
   for(int w = 0; w<str_2_len; w++)
      {
         str_2[w] = word_2[w];
      }

   
   //if the second word length is 2 letters more or less than word 1 return false
   if(str_1_len> str_2_len +1 ||  str_1_len < str_2_len - 1)
   {
      return 0;
   }
   int word_count = 0;

   //we apply this check if the words have equal length
   if(str_1_len == str_2_len)
   {
      //we check each letter of each word to check if they are the same
      for(int i = 0; i<str_1_len; i++)
      {
         if(str_1[i] == str_2[i])
            word_count +=1;
      }     
      //if each letter of the words are the same except one we return true
      if (word_count == str_1_len -1)
      {   
         return 1;
      }
      else
      {
         return 0;
      }   
   }
   else if (str_1_len<str_2_len)
   {
      // If the second word has more letters than the first we apply the following function
      return strComparisonWordLengthDif(str_1, str_2, str_1_len);
   }
   else
   {
      // If the first word has more letters than the first we apply the following function
      // Note that we switch the function arguments around so the shortest word is compared and the comparison stays true
      return strComparisonWordLengthDif(str_2, str_1, str_2_len);
   }
   return 0;

}





void sequenceCheck(Graph g, int wordCount, char wordArray[][MAXWORD])
{
   //for each word
   for(int i=0; i<wordCount; i++) //O(n)
   {
      int maxS = 0;

      //for every word after
      for(int j=i+1; j<wordCount; j++) //O(n^2)
      {
         //if there is a word sequence
         if(strComparison(wordArray[i], wordArray[j]) )
         {
            maxS++;
            //add a one-way connection from word i to j
            Edge new;
            new.v = i;
            new.w = j;
            insertEdge(g, new);
         }
         //so we take the two words to be compared
         //if its true we insert an edge
      }
      if (maxS>max_words)
      {   
         max_words = maxS;
      }
   }
}


void printGraph(Graph g, int wordCount, char wordArray[][MAXWORD])
{
   //for each word i
   for(int i = 0; i<wordCount; i++)
   {  
      //print the word
      printf("\n%s:", wordArray[i]);
      
      //for every word sequence for word i, print
      for (int j = i+1; j<wordCount; j++) //O(n^2)
      {
         if(adjacent( g, i, j))
         {   
            printf(" %s", wordArray[j]);
         }
      }
   }
}


void findMax(Graph g, int wordCount, int i, int count)
{
   //so we have our max global variable
   //if the count is more than the max as we recursively go through the graph, then the max increases to count
   if(count>max)
   {
      max=count;
   }
   //we apply this for all word sequences:
   
   for(int j = i+1; j<wordCount && (count + wordCount - j) > max; j++)
   {
      if(adjacent(g, i, j) )
         {
            //if they are adjacent we apply the max sequences for that word
            findMax(g, wordCount, j, count+1);
         }
   }
   
   return;
}

void printSequence(Graph g, int wordCount, int i, int count, int arr[], char wordArray[][MAXWORD])
{
   //this condition will trigger the printing of the longest word sequences
   //The print sequence function checks each words potential word seqences in all possible combinations, alphabetically throughout the graph, all sequences will be printed in alphabetical order if the are multiple max sequences
   if (count==max)
   {  //the final word is added to the array
      arr[count-1] = i;
      for (int z = 0; z<max; z++)
      {  //if its the first word in the array we print it by itself
         if(z==0)
         {
            printf("%s", wordArray[arr[z]]);
            continue;
         }
         else
         {  //if its not the first word in the array we print it with the arrow sign behind it
            printf(" -> %s", wordArray[arr[z]]);
         }
      }
      printf("\n");
      return;
   }
   //we apply this for all word sequences:
   //we check all the posible word sequences for each word
   for (int j = i+1; j<wordCount && (count + wordCount - j) >= max; j++)
   {
      //if there is an adjacency we will apply the function again
      if(adjacent(g, i, j) )
      {  
         //we add the word that needs to be printed to the array
         //this array is different for each recursion instance (will leave stack if count is not at max)
         arr[count-1] = i;
         //if the the count is equal to the max we will print all the connections stated in the array
         printSequence(g, wordCount, j, count+1, arr, wordArray);
      }
   }

   return;
}

int main(void)
{

   // Recieve the number of words
   printf("Enter a number: ");
   scanf("%i", &n);
   
   // Initilise 2D string array with number of words
   char str[n][MAXWORD];

   //Initilise the graph (adjacency matrix) with a row for each word
   //Note that this Graph is a directed Graph (noted in Graph.h)
   //Each vertex in the graph corresponds to one of the words the user enters in
   //Every neighbour in the graph corresponds to one of the word sequences for a particular vertex
   Graph g = newGraph(n);

   //Prompt user to enter each word for 2D string Array
   for(int i = 0; i<n;i++)
   {
      printf("Enter a word: ");
      scanf("%s", str[i]);
   }

   //Apply function to find all words sequences and apply it to graph
   sequenceCheck(g, n, str);
   
   //function to print all word sequences for each individual word
   printGraph(g, n, str);
   printf("\n");

   //function to find the max sequence number
   //we apply the function for all the words so that we can obtain the highest max
   //max_words is used to reduce recursions calls needed when finding all word sequences
   for(int i = 0; i<n && (n - i) > max_words; i++)
   {   
      findMax(g, n, i, 1);
   }

   //initlise array to keep track of which words are part of maximum sequences
   int seqArr[max];

   printf("\nMaximum sequence length: %i\n", max);
   printf("Maximal sequence(s):\n");
   //application of printSequence function for all words
   // the function will calculate all possible word sequences that are of max length in alphabetical order
   for(int i = 0; i<n && (n - i) >= max; i++)
   {
      printSequence(g, n, i, 1, seqArr, str);
   }

   //function free memory allocation for Graph
   freeGraph(g);
}



/*
scp words.c z5375417@login.cse.unsw.edu.au:Desktop
scp Graph.h z5375417@login.cse.unsw.edu.au:Desktop
scp Graph.c z5375417@login.cse.unsw.edu.au:Desktop
*/