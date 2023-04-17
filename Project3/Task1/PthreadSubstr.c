#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Function Prototypes
int num_substring(char *a,char *b,int pos);
void printData(void* startpos) ;

int n1 = 1000;
int n2 = 1000; 
char *s1;
char *s2;

// Total amount of substrings in the set
int substringTotal = 0;
int stringLength = 0;

// Mutex lock for totalSubstrings
pthread_mutex_t mutex;
	
int main(int argc, char *argv[])
{
	pthread_mutex_init (&mutex, NULL) ;

	FILE *fp = fopen("strings.txt","r"); 

	// Size of String
	s1 = (char*) malloc( n1 * sizeof(char*));

	// Size of Substring
	s2 = (char*) malloc( n2 * sizeof(char*));	

	fgets(s1 , n1, fp);
	fgets(s2, n2, fp);

    // N1 is length of String 1
	n1 = strlen(s1);

    // N2 is length of String 2
 	n2 = strlen(s2);

	stringLength = n1 / 5 ;
	pthread_t worker[5];

	for (int i = 0 ; i < 5 ; i++) {	
		// Setting start position and printing position
		int startingPosition = (i* (n1/5)) ;
		printf ("Set of data: %d\n", startingPosition);
        pthread_create ( &worker[i] , NULL, printData, (void*)startingPosition);
	}	
	
	// Wait for thread to exit and detach
	for (int i = 0 ; i < 5 ; i++) {
        pthread_join (worker[i], NULL);
	}	

    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf ("Total Number of Substrings of the string: %d\n", substringTotal);
}

int num_substring(char *a, char *b, int pos)
{
	int stringBLength = strlen (b) - 1 ;
	int matchCount = 0 ;

	for (int i = 0 ; i < stringBLength ; i++) {
		if (a[pos+i] != '\0'  && b[i] != '\0' && a[pos+i] == b[i]) {
			matchCount++;
		}
	}

	if (matchCount == stringBLength ) {
		return 1;
	} else {
		return 0;
	}

}

void printData(void* position)
{
	int subMatchCount = 0;
	for (int i = position; i < position+stringLength ; i++) {
		subMatchCount += num_substring(s1, s2, i);
	}
	
	// Locking the mutex
	pthread_mutex_lock(&mutex);
		substringTotal += subMatchCount;
		printf ("Current Substring Count is: %d\n", substringTotal);	
	pthread_mutex_unlock(&mutex);	
	pthread_exit(0);
}