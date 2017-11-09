#include <pthread.h>

struct station {
    int station_passengers;
    int to_train_passengers;
    int free_seats;
    pthread_mutex_t train_mutex;
    pthread_cond_t train_move;
    pthread_cond_t train_arrive;
};

void station_init(struct station *station);

void station_load_train(struct station *station, int count);

void station_wait_for_train(struct station *station);

void station_on_board(struct station *station);