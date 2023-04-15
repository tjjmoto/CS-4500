#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

char queue [5] ; 
int front = 0 , rear = 0 ;
int items = 0 ; 
int fileRead = 1 ;

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
		//1
		sleep(1);
		pthread_mutex_lock (&mutex) ;
			//2
			printf ("	front<%d> rear<%d>\n", front , rear) ;	
			while ( items >= 5 ) // while there is no space in queu to write
				pthread_cond_wait ( &space_available , &mutex ) ;
			//3	
			printf ("	front<%d> rear<%d>\n", front , rear) ;
			
			// now we cAN write in queue
			queue [front] = c ;
			front ++ ;
			if(front==5) front = 0 ;
			items ++ ;
			printf ("	character write to queue: <%c>\n" , c ) ;
			printf ("	wake up a consumer \n" ) ;
			pthread_cond_signal(&item_available); // wake up a consumer
			
		pthread_mutex_unlock (&mutex) ;
		sleep (1);
		c = getc(fp);		
	}
	pthread_mutex_lock (&mutex) ;
	fileRead = 0 ; // we should tell the consumer that the file is finished
	pthread_cond_signal(&item_available);
	pthread_mutex_unlock (&mutex) ;
	
	fclose (fp);
	pthread_exit (0);
}

void cons_thread()
{	
	while ( fileRead != 0 ) {
		pthread_mutex_lock (&mutex);
			printf ("front<%d> rear<%d>\n", front , rear );	

			while ( items <= 0 && fileRead!= 0 ) {
				pthread_cond_wait ( &item_available , &mutex ) ;
			}

			printf ("front<%d> rear<%d>\n", front , rear );	

			char c = queue [rear] ;
			rear ++ ;
			if (rear==5) rear = 0 ;
			items -- ;
			printf ("character read from queue: <%c>\n" , c );
			printf ("wake up a producer \n" );
			pthread_cond_signal(&space_available);
		
		pthread_mutex_unlock (&mutex);	
	}

	pthread_exit (0);
}