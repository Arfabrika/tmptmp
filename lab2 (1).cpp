#include <cstring>
#include <semaphore.h>
#include "lab2.h"

#define THREAD_CNT 11
#define LETTER_CNT 3

pthread_mutex_t lock;
pthread_t tid[THREAD_CNT];
int err;
sem_t semB, semC, semD, semG;

unsigned int lab2_thread_graph_id() 
{
    return 7;
}

const char* lab2_unsynchronized_threads()
{
    return "dfgi";
}

const char* lab2_sequential_threads()
{
    return "bcdg";
}

void threadWork(char name, int out_num = LETTER_CNT)
{
    for (int i = 0; i < out_num; i++)
    {
        pthread_mutex_lock(&lock);
        std::cout << name << std::flush;
        pthread_mutex_unlock(&lock);
        computation();
    }
}

void *thread_b(void *ptr);
void *thread_c(void *ptr);
void *thread_d(void *ptr);
void *thread_e(void *ptr);
void *thread_g(void *ptr);
void *thread_f(void *ptr);
void *thread_i(void *ptr);
void *thread_k(void *ptr);
void *thread_m(void *ptr);
void *thread_n(void *ptr);

void *thread_a(void *ptr)
{
        //Era 1
        threadWork('a');
	err = pthread_create(&tid[1], NULL, thread_b, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

        err = pthread_create(&tid[2], NULL, thread_c, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        err = pthread_create(&tid[3], NULL, thread_d, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

        err = pthread_create(&tid[4], NULL, thread_g, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;      
	
	while (pthread_join(tid[4], NULL) != 0);
        return ptr;
}

void *thread_b(void *ptr)
{
	//Era 2
	for (int i = 0; i < LETTER_CNT; i++)
	{
		sem_wait(&semB);
		threadWork('b', 1);
		sem_post(&semC);	
	}
	return ptr;
}

void *thread_c(void *ptr)
{
	//Era 2
	for (int i = 0; i < LETTER_CNT; i++)
	{
		sem_wait(&semC);
		threadWork('c', 1);
		sem_post(&semD);	
	}
        sem_wait(&semB);
        err = pthread_create(&tid[5], NULL, thread_e, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        while (pthread_join(tid[5], NULL) != 0);
        
	//Era 3
	threadWork('c');
	return ptr;
}

void *thread_d(void *ptr)
{
	//Era 2
	for (int i = 0; i < LETTER_CNT; i++)
	{
		sem_wait(&semD);
		threadWork('d', 1);
		sem_post(&semG);	
	}

	//Era 3
        while (pthread_join(tid[2], NULL) != 0);
	threadWork('d');
	
	//Era 4
	err = pthread_create(&tid[6], NULL, thread_f, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        threadWork('d');
        return ptr;
}

void *thread_e(void *ptr)
{
	//Era 3
        threadWork('e');
        return ptr;
}


void *thread_f(void *ptr)
{
	//Era 4
        threadWork('f');
        return ptr;
}


void *thread_g(void *ptr)
{
	//Era 2
	for (int i = 0; i < LETTER_CNT; i++)
	{
		sem_wait(&semG);
		threadWork('g', 1);
		sem_post(&semB);	
	}	
	while (pthread_join(tid[1], NULL) != 0);

	//Era 3
        threadWork('g');
        while (pthread_join(tid[3], NULL) != 0);

	//Era 4
        err = pthread_create(&tid[7], NULL, thread_i, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;               
        threadWork('g');

	//Era 5
	while (pthread_join(tid[7], NULL) != 0);	
	err = pthread_create(&tid[8], NULL, thread_k, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
        threadWork('g');
	while (pthread_join(tid[8], NULL) != 0);
	err = pthread_create(&tid[9], NULL, thread_m, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
	while (pthread_join(tid[9], NULL) != 0);
        return ptr;
}

void *thread_i(void *ptr)
{
	//Era 4
        threadWork('i');
        while (pthread_join(tid[6], NULL) != 0);

	//Era 5
        threadWork('i');

        return ptr;
}

void *thread_k(void *ptr)
{
        //Era 5
        threadWork('k');
        return ptr;
}

void *thread_m(void *ptr)
{
        //Era 5
        threadWork('m');

	//Era 6
	err = pthread_create(&tid[10], NULL, thread_n, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;
	while (pthread_join(tid[10], NULL) != 0);
	threadWork('m');
        return ptr;
}

void *thread_n(void *ptr)
{
	//Era 6
        threadWork('n');
        return ptr;
}


int lab2_init()
{
	if (pthread_mutex_init(&lock, NULL) != 0) 
	{
        	std::cerr << "Mutex init failed" << std::endl;
	        return 1;
    	}

	if ( sem_init(&semB, 0, 1) != 0 ) 
	{
        	std::cerr << "Semaphore B init failed" << std::endl;
	        return 1;
	}
	
	if ( sem_init(&semC, 0, 0) != 0 ) 
	{
        	std::cerr << "Semaphore C init failed" << std::endl;
	        return 1;
	}

	if ( sem_init(&semD, 0, 0) != 0 ) 
	{
        	std::cerr << "Semaphore D init failed" << std::endl;
	        return 1;
	}

	if ( sem_init(&semG, 0, 0) != 0 ) 
        {
                std::cerr << "Semaphore G init failed" << std::endl;
                return 1;
        }

	err = pthread_create(&tid[0], NULL, thread_a, NULL);
        if (err != 0)
                std::cerr << "Can't create thread. Error: " << strerror(err) << std::endl;

	pthread_join(tid[0], NULL);
	pthread_mutex_destroy(&lock);
	sem_destroy(&semB);
	sem_destroy(&semC);
	sem_destroy(&semD);
	sem_destroy(&semG);
	std::cout << std::endl;
	return 0;
}
