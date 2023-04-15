#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

char queue [5] ; 
int queueFront = 0;
int queueBack = 0 ;
int queueItems = 0 ; 
int fileReading = 1 ;

pthread_mutex_t mutex ;
pthread_cond_t item_available ;
pthread_cond_t space_available ;

// Function Prototypes
void prod_thread();
void cons_thread();

int main(int argc, char *argv[])
{
	// P thread variables for execution
	pthread_t p_prod , p_cons;
	pthread_cond_init (&item_available, NULL) ;
	pthread_cond_init (&space_available, NULL) ;
	pthread_mutex_init (&mutex, NULL) ;
	
	// Creating the pthread instance for producers
	pthread_create ( &p_prod , NULL, prod_thread, NULL);

	// Creating the pthread instance for consumers
	pthread_create ( &p_cons , NULL, cons_thread, NULL);
	pthread_join ( p_prod , NULL );
	pthread_join ( p_cons , NULL );

	return 0;
}

void prod_thread()
{	
	FILE *fp = fopen("message.txt","r");
	char c ;
	c = getc(fp);

	while (c != EOF) {
		sleep(1);
		pthread_mutex_lock (&mutex) ;

			while ( queueItems >= 5 ) {
				pthread_cond_wait ( &space_available , &mutex );
			}

			printf ("Queue Front: %d, Queue Back: %d\n", queueFront , queueBack);
			
			queue [queueFront] = c ;
			queueFront ++ ;

			if(queueFront==5) {
				queueFront = 0 ;
				queueItems ++ ;
			}

			printf ("Character Written to Queue: %c\n", c) ;
			printf ("Return to Consumer \n\n" ) ;
			pthread_cond_signal(&item_available);
			
		pthread_mutex_unlock (&mutex) ;
		sleep (1);
		c = getc(fp);		
	}
	pthread_mutex_lock (&mutex) ;
	fileReading = 0 ;
	pthread_cond_signal(&item_available);
	pthread_mutex_unlock (&mutex) ;
	
	fclose (fp);
	pthread_exit (0);
}

void cons_thread()
{	
	while ( fileReading != 0 ) {
		pthread_mutex_lock (&mutex);

			while ( queueItems <= 0 && fileReading!= 0 ) {
				pthread_cond_wait ( &item_available , &mutex ) ;
			}

			printf ("Queue Front: %d, Queue Back: %d\n", queueFront , queueBack );	

			char c = queue [queueBack] ;
			queueBack ++ ;

			if (queueBack==5) {
				queueBack = 0 ;
				queueItems -- ;
			}

			printf ("Character Read to Queue: %c\n", c );
			printf ("Return to Producer \n\n" );
			pthread_cond_signal(&space_available);
		
		pthread_mutex_unlock (&mutex);	
	}

	pthread_exit (0);
}