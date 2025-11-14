#ifndef UTILITY_H
#define UTILITY_H
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define MAX_SLOTS 50
#define MAX_PLATES 32
#define MAX_OWNER 64
#define RATE_PER_HOUR 10
#define DATAFILE "parking_db.txt"


typedef enum
{
    exist=-5,
    not_exist,
    full
}Status;

typedef struct
{
    int occupied;
    int slot_no;
    char plate[MAX_PLATES];
    char owner[MAX_OWNER];
    time_t in_time;

}Vehicle;


void load_state(Vehicle *parking);
void trim_newline(char *str);
void display_time(time_t t);
void display_status(Vehicle *parking);
void park_vehicle(Vehicle *parking);
Status find_by_plate(const char *plate,Vehicle *parking);
Status find_free_slot(Vehicle *parking);
void save_state(Vehicle *parking);
void remove_vehicle(Vehicle *parking);
double compute_fee_hours(time_t in_t, time_t out_t);
void search_vehicle(Vehicle *parking);
void change_total_slots(Vehicle *parking);
void press_enter_to_continue();

#endif