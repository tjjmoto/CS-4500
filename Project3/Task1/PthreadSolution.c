#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

// Function Prototypes
void printData(void* startpos) ;
int matchData(char *a,char *b,int pos);

int n1 = 1000;
int n2 = 1000; 
char *s1;
char *s2;

// Total amount of substrings in the set
int totalSubstrings = 0;
int stringLength = 0 ;

// Mutex lock for totalSubstrings
pthread_mutex_t mutex_lock ;
	
int main(int argc, char *argv[])
{
	pthread_mutex_init (&mutex_lock, NULL) ;

	FILE *fp = fopen("strings.txt","r"); 
	s1 = (char*) malloc( n1 * sizeof( char* ));
	s2 = (char*) malloc( n2 *sizeof( char* ));	
	fgets( s1 , n1 , fp);
	fgets( s2, n2, fp);

    // N1 length of String 1
	n1 = strlen(s1);

    // N2 is length of String 2
 	n2 = strlen(s2);

	stringLength = n1 / 5 ;
	
	pthread_t worker[5];
	for (int i = 0 ; i < 5 ; i++)
	{	
		// Setting start position and printing position
		int startingPosition = (i* (n1/5)) ;
		printf ("Starting Position %d\n", startingPosition);
        pthread_create ( &worker[i] , NULL, printData, (void*)startingPosition);
	}	
	
	// Pthread Joining
	for (int i =0 ; i< 5 ; i++) 
	{
        pthread_join ( worker[i] , NULL);
	}	
    
    printf ("Total Number of Substrings is (in main): %d\n", totalSubstrings);
}


void printData(void* position)
{
	int temp = 0 ;
	for (int i = position; i < position+stringLength ; i++) {
		temp += matchData(s1,s2, i);
	}
	
	// Locking the mutex
	pthread_mutex_lock (&mutex_lock);
	totalSubstrings += temp;
	printf ("Current Substring Count is: %d\n", totalSubstrings);	
	pthread_mutex_unlock (&mutex_lock) ;	

	// Pthread function exit
	pthread_exit (0);
}

int matchData(char *a, char *b, int pos)
{
	int bLength = strlen (b) - 1 ;
	int matchCount = 0 ;
	for (int i = 0 ; i < bLength ; i++ ) {
		if ( a[pos+i] != '\0'  && b[i] != '\0' && a[pos+i] == b[i] ) {
			matchCount++;
		}
	}

	if ( matchCount == bLength ) {
		return 1;
	} else {
		return 0;
	}

}