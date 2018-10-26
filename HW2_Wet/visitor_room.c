#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "visitor_room.h"

#define STRLEN(e) strlen((e))+1
#define FREE_NULL(e) free((e)); (e)=NULL;

#define SIZE_CHAR sizeof(char)
#define SIZE_ACTIVITY sizeof(ChallengeActivity)
#define DEFAULT_VALUE 0
#define MIN_NUMBER_OF_CHALLENGES 1

Result init_challenge_activity(ChallengeActivity*activity,Challenge *challenge) {
/*Name: init_challenge_activity
 * gets ChallengeActivity struct and set struct fields to given parameters or
 * default values*/
    if(activity == NULL || challenge == NULL) return NULL_PARAMETER;
    activity->challenge=challenge;
    activity->start_time=DEFAULT_VALUE;
    activity->visitor=NULL;//mark no visitor using this activity
    return OK;
}

Result reset_challenge_activity(ChallengeActivity *activity){
/*Name: reset_challenge_activity
 * gets ChallengeActivity struct and set struct fields to default values*/
    if(activity == NULL) return NULL_PARAMETER;
    activity->challenge=NULL;
    activity->visitor=NULL;
    activity->start_time=DEFAULT_VALUE;
    return OK;
}

Result init_visitor(Visitor *visitor, char *name, int id){
/*Name: init_visitor
 * gets Visitor struct and allocating memory for given name and set
 * struct fields to given parameters or default values*/
    if(visitor==NULL||name==NULL) return NULL_PARAMETER;
    visitor->visitor_name=(char*)malloc(SIZE_CHAR*(STRLEN(name)));
    if(visitor->visitor_name==NULL) return MEMORY_PROBLEM;
    strcpy(visitor->visitor_name,name);//copying given name to struct variable
    visitor->visitor_id=id;
    visitor->room_name=NULL;//mark Visitor not using room
    visitor->current_challenge=NULL;//mark visitor not using challenge
    return OK;
}

Result reset_visitor(Visitor *visitor){
/*Name: reset_visitor
 * gets allocated struct Visitor and free it's string name and defaulting
 * all other fields*/
    if (visitor==NULL) return NULL_PARAMETER;
    FREE_NULL(visitor->visitor_name);
    visitor->visitor_id=DEFAULT_VALUE;
    visitor->room_name=NULL;//mark Visitor not using room
    visitor->current_challenge=NULL;//mark visitor not using challenge
    return OK;
}

Result init_room(ChallengeRoom *room, char *name, int num_challenges){
/*Name: init_room
 * gets ChallengeRoom struct and allocating memory for it's given name and
 * allocating array for it's activities*/
    if(room==NULL||name==NULL) return NULL_PARAMETER;
    if (num_challenges<MIN_NUMBER_OF_CHALLENGES) return ILLEGAL_PARAMETER;
    //checking valid input number of challenges
    room->name=(char*)malloc(SIZE_CHAR*(STRLEN(name)));//allocating room name
    if (room->name==NULL) return MEMORY_PROBLEM;
    strcpy(room->name,name);//copying given name to struct variable
    room->challenges=(ChallengeActivity*)malloc(SIZE_ACTIVITY*num_challenges);
    if (room->challenges==NULL){
        FREE_NULL(room->name);
        return MEMORY_PROBLEM;
    }
    room->num_of_challenges=num_challenges;
    for(int i=0;i<room->num_of_challenges;i++){
        reset_challenge_activity(room->challenges+i);
    }
    return OK;
}

Result reset_room(ChallengeRoom *room){
/*Name: reset_room
 * gets allocated struct ChallengeRoom and free it's string name, it's
 * activities array and defaulting all other fields*/
    if (room==NULL) return NULL_PARAMETER;
    FREE_NULL(room->challenges);
    room->num_of_challenges=DEFAULT_VALUE;
    FREE_NULL(room->name);
    return OK;
}

Result num_of_free_places_for_level(ChallengeRoom*room,Level level,int *places){
/*Name: num_of_free_places_for_level
 * gets exists ChallengeRoom struct, level parameter and output address and
 * expoting to given address the number of available challenges with given level
 * in the given room */
    assert(places!=NULL);
    if (room==NULL) return NULL_PARAMETER;
    *places=0;//initialing output counter
    for(int i=0;i<room->num_of_challenges;i++){
        if(room->challenges[i].visitor==NULL){
            //make sure ChallengeActivity is available
          Challenge *current=room->challenges[i].challenge;//helper pointer
            if(level==All_Levels||current->level==level){
                (*places)++;
            }
        }
    }
    return OK;
}

Result change_room_name(ChallengeRoom *room, char *new_name){
/*Name: change_room_name
 * gets new name for given ChallengeRoom, allocating memory for new name and
 * free and replace old name with new one, if allocation failed makes no changes
 * in ChallengeRoom*/
    if (room==NULL||new_name==NULL){
        return NULL_PARAMETER;
    }
    char *temp=(char*)malloc(SIZE_CHAR*(STRLEN(new_name)));
    if(temp==NULL) {
        return MEMORY_PROBLEM;
    }
    free(room->name);//free the old name
    room->name=strcpy(temp,new_name);//save new name in the pointer
    return OK;
}

Result room_of_visitor(Visitor *visitor, char **room_name) {
/*Name: room_of_visitor
 * exporting by copying to a given pointer the room the given visitor is
 * inside*/
    if(visitor == NULL || room_name == NULL) return NULL_PARAMETER;
    assert(*room_name==NULL);
    if(visitor->room_name==NULL) return NOT_IN_ROOM;
    char *temp=(char *) malloc(SIZE_CHAR * (STRLEN(*(visitor->room_name))));
    if(temp == NULL) return MEMORY_PROBLEM;
    *room_name=strcpy(temp,*(visitor->room_name));
    //copying from struct variable to output pointer
    return OK;
}

Result visitor_enter_room(ChallengeRoom *room, Visitor *visitor, Level level,
                          int start_time){
/*Name: visitor_enter_room
* gets ChallengeRoom and Visitor struct first check if the visitor can
* gets into the room then updating given ChallengeRoom and given Visitor
* parameters for visitor is entering the requested room*/
    if(room==NULL||visitor==NULL) return NULL_PARAMETER;
    if(visitor->room_name!=NULL) return ALREADY_IN_ROOM;
    int available_challenges=0;//initialing variable
    num_of_free_places_for_level(room,level,&available_challenges);
    if(available_challenges<1) return NO_AVAILABLE_CHALLENGES;
    ChallengeActivity *chosen_activity=NULL;//helper pointer
    for(int i=0;i<room->num_of_challenges;i++){
        if(room->challenges[i].visitor==NULL&&
           (level==All_Levels || room->challenges[i].challenge->level==level)){
            ChallengeActivity *temp=(room->challenges)+i;//helper pointer
            if(chosen_activity==NULL||strcmp(chosen_activity->challenge->name,
                                    temp->challenge->name)>0){
                //condition to find lowest lexicographic available Challenge
                chosen_activity=temp;
            }
        }
    }
    chosen_activity->visitor=visitor;//mark activity with visitor
    chosen_activity->start_time=start_time;//initialing start time in activity
    inc_num_visits(chosen_activity->challenge);
    //increase the number of visits in the Challenge struct
    visitor->room_name=&(room->name);//mark visitor is in room
    visitor->current_challenge=chosen_activity;
    //mark the current challenge in the visitor struct
return OK;
}

Result visitor_quit_room(Visitor *visitor, int quit_time){
/*Name: visitor_quit_room
* gets Visitor struct first check if the visitor is inside room then updating
* ChallengeRoom and given Visitor parameters for visitor is leaving the room*/
    if(visitor==NULL) return NULL_PARAMETER;
    if(visitor->room_name==NULL) return NOT_IN_ROOM;
    int visitor_total_time = quit_time-visitor->current_challenge->start_time;
    set_best_time_of_challenge(visitor->current_challenge->challenge,
                               visitor_total_time);
    visitor->current_challenge->start_time=DEFAULT_VALUE;//defaulting start time
    visitor->current_challenge->visitor=NULL;
    //defaulting the ChallengeActivity for the visitor left
    visitor->current_challenge=NULL;
    //defaulting the current Challenge of visitor
    visitor->room_name=NULL;//defaulting the current room of visitor
    return OK;
}