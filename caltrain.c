#include <pthread.h>
#include "caltrain.h"
#include <stdio.h>


void station_init(struct station *station)
{
    station->free_seats = 0;
    station->station_passengers = 0;
    station->to_train_passengers = 0;
    pthread_mutex_init(&station->train_mutex, NULL);
    pthread_cond_init(&station->train_arrive, NULL);
    pthread_cond_init(&station->train_move, NULL);
}

// train arriving
void station_load_train(struct station *station, int count) {

    pthread_mutex_lock(&station->train_mutex);
    station->free_seats = count;
    pthread_cond_broadcast(&station->train_arrive);// broad cast that there is a train

    // if there is free seats and passengers , wait for them to ride
    while (station->free_seats > 0 && station->station_passengers > 0)
        pthread_cond_wait(&station->train_move, &station->train_mutex);

    station->free_seats = 0; // clean free seats for the next trains

    pthread_mutex_unlock(&station->train_mutex);
}

// make new passenger in the station
void station_wait_for_train(struct station *station)
{
    pthread_mutex_lock(&station->train_mutex);
    station->station_passengers++;

    // while there is no more place in the train, wait for the next
    while(station->to_train_passengers -  station->free_seats == 0)
        pthread_cond_wait(&station->train_arrive, &station->train_mutex);

    // this passenger is now on his way to train
    station->station_passengers--;
    station->to_train_passengers++;

    pthread_mutex_unlock(&station->train_mutex);
}

// make passenger be on board and test for fullness
void station_on_board(struct station *station)
{
    pthread_mutex_lock(&station->train_mutex);

    // this passenger now on board
    station->to_train_passengers--;
    station->free_seats--;

    // if the train is full or no more passengers , move the train
    if(station->free_seats == 0 || station->to_train_passengers == 0)
        pthread_cond_signal(&station->train_move);

    pthread_mutex_unlock(&station->train_mutex);
}
