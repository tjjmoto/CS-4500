#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

//function searchString searchs the given string for the number of occurences of a given string(stringToFind), and returns the number of occurences
int searchString(char string[], char stringToFind[30], FILE *filePtr, int sizeOfFile)
{
	//static int that records the numberOfStringsFound, this persits everytime we call the function meaning it can store values bettwen calls, it will store the number of the given word we have found. 
	static int numberOfStringsFound;
	
	//static int that records the startPlace, this persits everytime we call the function meaning it can store values bettwen calls, it will store ware we stoped looking last time
	//said another way this stores the end of the last place we found the string we are looking for and tells us where to pick up the search. 
	static int startPlace;
	
	//this function searches the string for the stringToFind and returns where it found stringToFind if it finds it else it returns null
	char *ptr = strstr(string, stringToFind);
	
	//if strstr did not find stringToFind in email
	if (ptr == NULL)
	{
		//declare tempInt to hold how many times we found the stringToFind before we found it no more 
		double tempInt = numberOfStringsFound;
		
		//resets both static varibles so they will be fresh next time we call searchString
		startPlace = 0;
		numberOfStringsFound = 0;
		
		//returens tempInt which is the numberOfStringsFound
		return tempInt;
	}
	//if strstr did find wordToFind in email
	else 
	{
		//count that we found another occurences of a the given string
		numberOfStringsFound = numberOfStringsFound + 1.00;
		
		//set the place to pick up looking to the total lenght of the string minus where we found wordToFind plus the length of the string we are looking for plus where we started last time
		//what all of this means is that we start looking right after where we found the last string in the total email.txt file. 
		//For example if the email.txt file was 50 chars long and we found wordToFind and the 35th char and word to find was 3 chars long and we had already searched the first 13 chars previosly
		//we would know to start looking at 31 char next time as that would be where we stoped this time.
		startPlace=(strlen(string) - strlen(ptr)) + strlen(stringToFind) + startPlace;
		
		char tempString[sizeOfFile];
		
		//trims of what we have already searched of the string
    	for(int i = 0; i <= sizeOfFile; i++) 
		{
        	tempString[i] = string[startPlace+i];
    	}
		
		//selfreference, meaning we call searchEmail from inside searchEmail, all that has changed from the last time we called it is email which is now shorter as we start from after we found the last
		//occurence of stringToFind, also remember that since numberOfStringsFound and startPlace are static thay will still be the same in this iteration of the function. 
    	searchEmail(tempString, stringToFind, filePtr, sizeOfFile);
	}
}





