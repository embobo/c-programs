#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

// Note: intptr_t

typedef struct Account {
    char* name;
    long  balance;
    pthread_mutex_t mutex;
} Account;

Account* accounts[4];

Account*
make_account(char* name, long balance)
{
    Account* acc = malloc(sizeof(Account));
    acc->name = strdup(name);
    acc->balance = balance;
    pthread_mutex_init(&acc->mutex,0);
    return acc;
}

void
free_account(Account* acc)
{
    free(acc->name);
    free(acc);
}

// Doesn't always work:
int
transfer1(Account* aa, Account* bb, long amount)
{
    pthread_mutex_lock(&(aa->mutex));
    if (aa->balance < amount) {
        return -1;
    }

    aa->balance -= amount;
    pthread_mutex_unlock(&(aa->mutex));
    // what if program crashed here? we'd lose this transfer to cyberspace
    pthread_mutex_lock(&(bb->mutex));
    bb->balance += amount;
    pthread_mutex_unlock(&(bb->mutex));
    return 0;
}

void
lock_both(pthread_mutex_t* aa, pthread_mutex_t* bb)
{
    // lock in ordered sequence
    if(aa < bb) {
        pthread_mutex_lock(aa);
        pthread_mutex_lock(bb);
    }
    else {
        pthread_mutex_lock(bb);
        pthread_mutex_lock(aa);
    }
}

int
transfer(Account* aa, Account* bb, long amount)
{
    // create helper
    lock_both(&(aa->mutex),&(bb->mutex));

    if (aa->balance < amount) {
        return -1;
    }

    aa->balance -= amount;
    bb->balance += amount;

    pthread_mutex_unlock(&(aa->mutex));
    pthread_mutex_unlock(&(bb->mutex));

    return 0;
}

void*
test_thread(void* seed_ptr)
{
    unsigned int seed = *((unsigned int*) seed_ptr);
    free(seed_ptr);

    for (int kk = 0; kk < 10000; ++kk) {
        int ii = rand_r(&seed) % 4;
        int jj = rand_r(&seed) % 4;
        int aa = 1 + rand_r(&seed) % 100;

        if (ii == jj) {
            continue;
        }
        //pthread_mutex_lock(&mutex);
        transfer(accounts[ii], accounts[jj], aa);
        //pthread_mutex_unlock(&mutex);
    }

    return 0;
}

int
main(int _ac, char* _av[]) 
{
    pthread_t threads[10];

    accounts[0] = make_account("Alice", 100000);
    accounts[1] = make_account("Bob",   100000);
    accounts[2] = make_account("Carol", 100000);
    accounts[3] = make_account("Dave",  100000);

    for (int ii = 0; ii < 10; ++ii) {
        unsigned int* seed = malloc(sizeof(unsigned int));
        *seed = ii + getpid();
        pthread_create(&(threads[ii]), 0, test_thread, seed);
    }

    for (int ii = 0; ii < 10; ++ii) {
        pthread_join(threads[ii], 0);
    }

    long sum = 0;
    for (int ii = 0; ii < 4; ++ii) {
        sum += accounts[ii]->balance;
        printf("%s:\t%ld\n", accounts[ii]->name, accounts[ii]->balance);
        free_account(accounts[ii]);
    }

    printf("\nSum:\t%ld\n", sum);

    return 0;
}