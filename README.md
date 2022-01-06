# WordSequenceGenerator

Large Programming Assignment as part of the University Subject Data Structures and Algorithms

**Received 11/12 in Marking**

## Assignment Objective

* Implement a data structure that displays all possible word sequences (words that have one letter difference, or one letter more/less)
* Find the longest word sequences and display them
  * If there are equal longest word sequences students need to display them in alphabetical order
* Ensure that the data structure is presented through an Abstract Data Type (Graph.h)

## Developer Notes

This assignment essentially requires a program to complete three functions:
1. Ask the user to input a specified number of words
2. For each respective word find all possible word sequences for every word that was entered after it
3. From all the words, find the longest sequences of words and display them - if there are more than one that also needs to be displayed in alphabetical order

* To ensure all word sequences are recorded for each respective word a n*n matrix is required this is stored through the Graph data type mentioned in Graph.c
* From there we then apply the sequenceCheck function to compare all words against their sequential entries, recording all possible word sequences
  * The printGraph function then displays this
* In order to find the longest possible word sequence and to account that there may be more than one, the findMax function is applied
  * This function goes through every possible combination of word sequences and revises the max global variable 
* We then go through all possible word combinations again, storing each word sequence in an array, when the max count is reached, the word sequence is then printed.
  * This way the longest word sequences are printed in alphabetical order
* Finally we free the dynamic memory usage of the Graph data type through the freeGraph function

## Notes:
* A Makefile was utilised so that instant compilation each file and there respective of dependencies occur
