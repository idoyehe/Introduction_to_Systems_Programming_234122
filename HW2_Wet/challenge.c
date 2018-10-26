#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "challenge.h"

#define SIZE_CHAR sizeof(char)
#define STRLEN(e) strlen((e))+1
#define FREE_NULL(e) free((e)); (e)=NULL;

#define DEFAULT_VALUE 0

Result init_challenge(Challenge *challenge, int id, char *name, Level level) {
/*Name: init_challenge
 * gets Challenge struct and allocating memory for given name and set struct
 * fields to given parameters or default values*/
    if (challenge==NULL||name==NULL) return NULL_PARAMETER;
    challenge->name=(char*)malloc(SIZE_CHAR*(STRLEN(name)));
    if(challenge->name==NULL) return MEMORY_PROBLEM;
    strcpy(challenge->name,name);//copying from input to struct variable
    challenge->best_time=DEFAULT_VALUE;
    challenge->num_visits=DEFAULT_VALUE;
    challenge->id=id;
    challenge->level=level;
    return OK;
}

Result reset_challenge(Challenge *challenge){
/*Name: reset_challenge
 * gets allocated struct Challenge and free it's string name and defaulting
 * all other fields*/
    if(challenge==NULL) return NULL_PARAMETER;
    FREE_NULL(challenge->name);
    challenge->id=DEFAULT_VALUE;
    challenge->level=DEFAULT_VALUE;
    challenge->best_time=DEFAULT_VALUE;
    challenge->num_visits=DEFAULT_VALUE;
return OK;
}

Result change_name(Challenge *challenge, char *name){
/*Name: change_name
 * gets new name for given Challenge, allocating memory for new name and
 * free and replace old name with new one, if allocation failed makes no changes
 * in Challenge*/
    if (challenge==NULL||name==NULL) return NULL_PARAMETER;
    char *temp=(char*)malloc(SIZE_CHAR*(STRLEN(name)));//allocating for new name
    if(temp==NULL) return MEMORY_PROBLEM;
    free(challenge->name);//free the old name
    challenge->name=strcpy(temp,name);//save new name in the pointer
    return OK;
}

Result set_best_time_of_challenge(Challenge *challenge, int time) {
/*Name:set_best_time_of_challenge
 * gets Challenge struct and time, updating the best time in the challenge if
 * time parameter is better than current best time*/
    if (challenge == NULL) return NULL_PARAMETER;
    if (time < 0 ||((time > challenge->best_time)&&challenge->best_time> 0)){
        //make sure time input is legal
        return ILLEGAL_PARAMETER;
    }
    challenge->best_time=time;
    return OK;
}

Result best_time_of_challenge(Challenge *challenge, int *time) {
/*Name: best_time_of_challenge
 * gets Challenge struct and output address of int, exporting challenge best
 * time field to the given address*/
    assert(time!=NULL);
    if (challenge == NULL) return NULL_PARAMETER;
    *time=challenge->best_time;
    return OK;
}

Result inc_num_visits(Challenge *challenge){
/*Name: inc_num_visits
 * gets Challenge struct and adding 1 to it's num visits field*/
    if (challenge == NULL) return NULL_PARAMETER;
    challenge->num_visits++;
    return OK;
}

Result num_visits(Challenge *challenge, int *visits) {
/*Name: num_visits
 * gets Challenge struct and output address of int, exporting challenge num
 * visits field to the given address*/
    assert(visits!=NULL);
    if (challenge == NULL) return NULL_PARAMETER;
    *visits=challenge->num_visits;
    return OK;
}