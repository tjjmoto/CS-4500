#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details.
#include <pthread.h>

// Function Prototypes
void *printData(void* startpos) ; // counting the number of matches
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
		int startpos = (i* (n1/5)) ;
		printf ("startpos %d\n", startpos);
        pthread_create ( &worker[i] , NULL, printData, (void*)startpos);
	}	
	
	for (int i =0 ; i< 5 ; i++) // wait for all to finish
	{
        pthread_join ( worker[i] , NULL);
	}	
    
    printf ("Total Number of Substrings is (in main): %d\n", totalSubstrings);
}


void *printData(void* startpos)
{	
	int pos = ((int)startpos); // the position in s1 that we should start from
	printf ("my start pos is<%d>\n", pos ) ;

	int temp = 0 ;
	for (int i = pos; i < pos+stringLength ; i++) // finding te matches
		temp += matchData(s1,s2, i);
	printf ("my start pos is<%d>\n", pos ) ;
	
	pthread_mutex_lock (&mutex_lock) ;
	totalSubstrings += temp ; // we need the lock to cange the total_num
	printf ("Current Substring Count is: %d\n", totalSubstrings);	
	pthread_mutex_unlock (&mutex_lock) ;	

	//return NULL;
	pthread_exit (0);
}

int matchData(char *a,char *b,int pos)
{
	int lenghtb = strlen (b) - 1 ;
	int num = 0 ;
	for (int i = 0 ; i < lenghtb ; i++ )
		if ( a[pos+i] != '\0'  && b[i] != '\0' && a[pos+i] == b[i] )
			num ++ ;
	if ( num == lenghtb )
		return 1;
	else
		return 0;

}