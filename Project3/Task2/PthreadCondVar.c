#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

char queue [12] ; 
int queueFront = 0;
int queueBack = 0;
int queueItems = 0; 
int fileReading = 1;

pthread_mutex_t mutex;
pthread_cond_t availItem;
pthread_cond_t availSpace;

// Function Prototypes
void prod_thread();
void cons_thread();

int main(int argc, char *argv[])
{
	// P thread variables for execution
	pthread_t p_prod, p_cons;
	pthread_cond_init (&availItem, NULL) ;
	pthread_cond_init (&availSpace, NULL) ;
	pthread_mutex_init (&mutex, NULL) ;
	
	// Creating the pthread instance for producers
	pthread_create (&p_prod, NULL, prod_thread, NULL);

	// Creating the pthread instance for consumers
	pthread_create (&p_cons, NULL, cons_thread, NULL);
	pthread_join (p_prod, NULL);
	pthread_join (p_cons, NULL);

	return 0;
}

void prod_thread()
{	
	FILE *fp = fopen("message.txt", "r");
	char character ;
	character = getc(fp);

	while (character != EOF) {
		sleep (1);
		pthread_mutex_lock (&mutex);

			while (queueItems >= 12) {
				pthread_cond_wait (&availSpace , &mutex);
			}

			printf ("Queue Front: %d, Queue Back: %d\n", queueFront, queueBack);
			
			queue [queueFront] = character;
			queueFront++;

			printf ("Character Written to Queue: %c\n\n", character) ;
			pthread_cond_signal(&availItem);

			if(queueFront == 12) {
				queueFront = 0;
				queueItems++;
			}
			
		pthread_mutex_unlock(&mutex);
		sleep (1);
		character = getc(fp);		
	}
	pthread_mutex_lock (&mutex);
	fileReading = 0 ;
	pthread_cond_signal(&availItem);
	pthread_mutex_unlock(&mutex);
	
	fclose (fp);
	pthread_exit (0);
}

void cons_thread()
{	
	int queueCount = 0;
	while(fileReading != 0) {
		pthread_mutex_lock(&mutex);

			while (queueItems <= 0 && fileReading != 0) {
				pthread_cond_wait(&availItem, &mutex) ;
			}

			printf("Queue Front: %d, Queue Back: %d\n", queueFront , queueBack);	

			char character = queue [queueBack];
			queueBack ++ ;

			printf("Character Read from Queue: %c\n", character);
			printf("Action: Popped from Queue\n\n" );
			pthread_cond_signal(&availSpace);

			if (queueBack == 12) {
				queueBack = 0;
				queueItems --;
			}
		
		pthread_mutex_unlock(&mutex);	
	}

	pthread_exit(0);
}