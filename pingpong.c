#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define PING 0
#define PONG 1

int state = PONG;
pthread_mutex_t lock_t = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_t = PTHREAD_COND_INITIALIZER;

int steps = 30;
int step = 0;

void *ping(void *arg) {
    while (step < steps) {
        pthread_mutex_lock(&lock_t);

        usleep(150000);
        while (state == PING) {
            pthread_cond_wait(&cond_t, &lock_t);
        }
        printf("Ping!\n");

        step++;
        state = PING;
        pthread_cond_signal(&cond_t);
        pthread_mutex_unlock(&lock_t);
    }
}

void *pong(void *arg) {
    while (step < steps) {
        pthread_mutex_lock(&lock_t);

        usleep(150000);
        while (state == PONG) {
            pthread_cond_wait(&cond_t, &lock_t);
        }
        printf("Pong!\n");

        step++;
        state = PONG;
        pthread_cond_signal(&cond_t);
        pthread_mutex_unlock(&lock_t);
    }
}

int main(int argc, char* argv[]) {
    pthread_t t_ping, t_pong;

    pthread_create(&t_ping, NULL, ping, NULL);
    pthread_create(&t_pong, NULL, pong, NULL);
    pthread_join(t_ping, NULL);
    pthread_join(t_pong, NULL);

    return 0;
}
