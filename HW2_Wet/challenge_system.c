#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "challenge_system.h"

#define FREE_NULL(e) free((e)); (e)=NULL;
#define STRLEN(e) (strlen((e))+1)

#define SIZE_CHAR sizeof(char)
#define SIZE_ROOM sizeof(ChallengeRoom)
#define SIZE_ROOM_SYSTEM sizeof(ChallengeRoomSystem)
#define SIZE_CHALLENGE sizeof(Challenge)
#define SIZE_VISITOR sizeof(Visitor)
#define NON_TO_BE_RESET 0
#define UNUSED -1
#define BUFFER_SIZE 51
#define DEFAULT_VALUE 0

typedef struct SVisitorNode {
    Visitor* visitor;
    struct SVisitorNode *next;
} *VisitorNode;

static Challenge* find_challenge_by_name(ChallengeRoomSystem *sys,char *name){
/*Name: find_challenge_by_name
 * find Challenge in all_challenges array by given name, return NULL if name
 * isn't founded else return pointer to requested Challenge*/
    assert(sys!=NULL);
    assert(sys->all_challenges!=NULL);
    assert(name!=NULL);
    for(int i=0;i<sys->number_of_challenges;i++){
        if(!strcmp(sys->all_challenges[i].name,name)){
            //true when equal <=> strcmp is 0
            return sys->all_challenges+i;//return pointer to requested challenge
        }
    }
    return NULL;//in case requested Challenge hasn't been found
}

static Challenge* find_challenge_by_id(ChallengeRoomSystem *sys,int id){
/*Name: find_challenge_by_id
 * find Challenge in all_challenges array by given id, return NULL if id
 * isn't founded else return pointer to requested Challenge*/
    assert(sys!=NULL);
    assert(sys->all_challenges!=NULL);
    for(int i=0;i< sys->number_of_challenges;i++){
        if(sys->all_challenges[i].id==id){
            return sys->all_challenges+i;//return pointer to requested challenge
        }
    }
    return NULL;//in case requested Challenge hasn't been found
    //shouldn't get here while building the array,because assuming file
    // is correct
}

static ChallengeRoom* find_room_by_name(ChallengeRoomSystem *sys,char *name){
/*Name: find_room_by_name
 * find ChallengeRoom in all_rooms array by given name, return NULL if name
 * isn't founded else return pointer to requested ChallengeRoom*/
    assert(sys!=NULL);
    assert(sys->all_rooms!=NULL);
    assert(name!=NULL);
    for(int i=0;i<sys->number_of_rooms;i++){
        if(!strcmp(sys->all_rooms[i].name,name)){
            //true when equal <=> strcmp is 0
            return (sys->all_rooms)+i;//return pointer to requested room
        }
    }
    return NULL;//in case requested ChallengeRoom hasn't been found
}

static VisitorNode find_visitor_by_name(ChallengeRoomSystem *sys,char *name){
/*Name: find_visitor_by_name
 * find VisitorNode in all_visitors list by given name, return NULL if name
 * isn't founded else return pointer to requested VisitorNode*/
    assert(sys!=NULL);
    assert(name!=NULL);
    VisitorNode ptr=sys->all_visitors;//helper pointer
    while(ptr){
        if(!strcmp(ptr->visitor->visitor_name, name)){
            //true when equal <=> strcmp is 0
            return ptr;//return pointer to requested VisitorNode
        }
        ptr=ptr->next;
    }
    return NULL;//in case requested Visitor hasn't been found
}

static VisitorNode find_visitor_by_id(ChallengeRoomSystem *sys,int id){
/*Name: find_visitor_by_id
 * find VisitorNode in all_visitors list by given id, return NULL if id
 * isn't founded else return pointer to requested VisitorNode*/
    assert(sys!=NULL);
    VisitorNode ptr=sys->all_visitors;//helper pointer
    while(ptr){
        if(ptr->visitor->visitor_id==id){
            return ptr;//return pointer to requested VisitorNode
        }
        ptr=ptr->next;
    }
    return NULL;//in case requested Visitor hasn't been found
}

static Result add_visitor_to_list(ChallengeRoomSystem *sys,char
*visitor_name,int visitor_id) {
/*Name: add_visitor_to_list
 *Node and  gets system and allocating new VisitorNode and new Visitor, init
 * new visitor with given parameters and changing first node in visitor's
 * list to the new node with new visitor, if allocation fails makes no
 * changes*/
    assert(sys!=NULL);
    assert(find_visitor_by_id(sys,visitor_id)==NULL);
    if(visitor_name == NULL) return NULL_PARAMETER;
    VisitorNode temp=(VisitorNode) malloc(sizeof(*temp));
    if(temp == NULL) return MEMORY_PROBLEM;
    Visitor *new_visitor=(Visitor *) malloc(SIZE_VISITOR);
    if(new_visitor == NULL){
        FREE_NULL(temp);
        return MEMORY_PROBLEM;
    }
    if(init_visitor(new_visitor, visitor_name, visitor_id) == MEMORY_PROBLEM){
        FREE_NULL(new_visitor);
        FREE_NULL(temp);
        return MEMORY_PROBLEM;
    }
    temp->visitor=new_visitor;
    temp->next=sys->all_visitors;
    sys->all_visitors=temp;
    return OK;
}

static Result delete_visitor_from_list(ChallengeRoomSystem *sys,char
*visitor_name) {
/*Name: delete_visitor_from_list
 * delete a Visitor from all_visitors list by searching it by it's name free
 * it's Visitor struct and it's visitorNode, and fix the list*/
    assert(sys!=NULL);
    if(visitor_name == NULL||sys->all_visitors==NULL) return NULL_PARAMETER;
    VisitorNode ptr=find_visitor_by_name(sys,visitor_name);
    if(ptr==NULL) return OK;//here when no need to delete
    VisitorNode curr=sys->all_visitors;
    while(curr!=ptr&&curr->next!=ptr){
        curr=curr->next;
    }
    if(curr==ptr){//in case need to remove the first visitor
        sys->all_visitors=ptr->next;//skipping the one that need to be removed
    }
    else {//in case need to remove in the middle
        curr->next = ptr->next;//skipping the one that need to be removed
    }
    reset_visitor(ptr->visitor);//free visitor name
    FREE_NULL(ptr->visitor);//free Visitor struct
    FREE_NULL(ptr);//free VisitorNode
    return OK;
}

static Result init_system(ChallengeRoomSystem *sys,FILE *data) {
/*Name: init_system
 * reading system name and number of challenges from file and initialing all
 * other parameters to default value*/
    assert(sys != NULL);
    //defaulting rest parameters
    sys->all_challenges=NULL;
    sys->all_rooms=NULL;
    sys->number_of_rooms=DEFAULT_VALUE;
    sys->all_visitors=NULL;
    sys->last_update_time=DEFAULT_VALUE;
    char buffer[BUFFER_SIZE]="";
    fscanf(data,"%s\n%d\n", buffer, &sys->number_of_challenges);
    //gets system name and number of challenges
    sys->system_name=(char *) malloc(SIZE_CHAR * STRLEN(buffer));
    //allocating memory for name
    if(sys->system_name == NULL) return MEMORY_PROBLEM;
    strcpy(sys->system_name, buffer);//copy name to the system
    return OK;
}

static Result reset_system(ChallengeRoomSystem *sys,int rooms_to_reset,int challenge_to_reset) {
/*Name: reset_system
 * defaulting system parameters and only free memory that had allocated by
 * gets number of allocated rooms and challenges*/
    assert(sys!=NULL);
    sys->last_update_time=DEFAULT_VALUE;
    if(sys->all_rooms!=NULL){//checked if array of rooms was allocated
        for(int i=0;i<rooms_to_reset;i++){
            reset_room(sys->all_rooms+i);
            //free each room name and ChallengeActivities array
        }
    }
    FREE_NULL(sys->all_rooms);//free the array of rooms (can be NULL)
    sys->number_of_rooms=DEFAULT_VALUE;
    if(sys->all_challenges!=NULL){//checked if array of challenges was allocated
        for(int i=0; i < challenge_to_reset; i++){
            reset_challenge(sys->all_challenges + i);//free each Challenge name
        }
    }
    FREE_NULL(sys->all_challenges);//free allocation of the array
    sys->number_of_challenges=DEFAULT_VALUE;
    FREE_NULL(sys->system_name);//free system name
    while(sys->all_visitors) {//free all_visitor list
        VisitorNode toDelete = sys->all_visitors;
        sys->all_visitors=sys->all_visitors->next;
        reset_visitor(toDelete->visitor);//free visitor name
        free(toDelete->visitor);//free Visitor struct
        free(toDelete);//free VisitorNode
        }
    return OK;
}

static Result build_challenges_array(ChallengeRoomSystem *sys, FILE *data) {
/*Name: build_challenges_array
 * allocating array of challenges and initialing each challenge in it with
 * parameters from file*/
    assert(sys != NULL);
    sys->all_challenges=(Challenge *) malloc(
            SIZE_CHALLENGE * sys->number_of_challenges);
    //allocating memory for array of all challenges
    if(sys->all_challenges == NULL){
        reset_system(sys, NON_TO_BE_RESET, NON_TO_BE_RESET);//free name memory
        return MEMORY_PROBLEM;
    }
    for(int i=0; i < sys->number_of_challenges; i++){
        char buffer[BUFFER_SIZE]="";//buffer for name
        int id=UNUSED;//buffer for id
        Level level=UNUSED;//buffer for level
        fscanf(data,"%s %d %u\n", buffer, &id, &level);//gets each challenge
        Challenge *curr=sys->all_challenges + i;//helper pointer
        level--;//in file level was writen with 1 offset
        if(init_challenge(curr, id, buffer, level) == MEMORY_PROBLEM){
            reset_system(sys, NON_TO_BE_RESET, i);
            return MEMORY_PROBLEM;
        }
        //initialing each Challenge in the array
    }
    return OK;
}

static Result build_activities_for_room(ChallengeRoomSystem *sys ,
                                        ChallengeRoom *room, FILE*data) {
/*Name: build_activities_for_room
* gets current ChallengeRoom and initialing it's activities array by reading
 * from the file the id's of Challenges for it*/
    assert(sys!=NULL);
    assert(room!=NULL);
    for(int i=0; i < room->num_of_challenges; i++){
        int id=UNUSED;//buffer for challenge id
        fscanf(data," %d", &id);
        ChallengeActivity *curr_activity=(room->challenges) + i;//helper pointer
        Challenge *requested_challenge=find_challenge_by_id(sys, id);
        assert(requested_challenge!=NULL);
        //assuming file is correct, so given id should be found
        curr_activity->challenge=requested_challenge;
    }
    return OK;
}

static Result build_rooms_array(ChallengeRoomSystem *sys, FILE *data) {
/*Name: build_rooms_array
* allocating array of ChallengeRooms and initialing each room
 * by reading from the file it's name and number of challenges*/
    assert(sys != NULL);
    fscanf(data,"%d", &(sys)->number_of_rooms);
    sys->all_rooms=(ChallengeRoom *)malloc(SIZE_ROOM*(sys)->number_of_rooms);
    if(sys->all_rooms == NULL){
        reset_system(sys, NON_TO_BE_RESET,sys->number_of_challenges);
        //free all allocated memory so far
        return MEMORY_PROBLEM;
    }
    for(int i=0; i < sys->number_of_rooms; i++){//build each room in a time
        ChallengeRoom *curr_room=sys->all_rooms + i;//helper pointer
        char buffer[BUFFER_SIZE]="";//buffer for room name
        int number_of_activities=UNUSED;
        //buffer for number of activities of room
        fscanf(data,"\n%s %d", buffer, &number_of_activities);
        //gets room name and number of activities
        if(init_room(curr_room, buffer, number_of_activities)==MEMORY_PROBLEM){
            reset_system(sys, i,sys->number_of_challenges);
            //free system name and all_challenge array and allocated room so far
            return MEMORY_PROBLEM;
        }//build each activity in the room
        build_activities_for_room(sys, curr_room,data);
    }
    return OK;
}

static inline bool check_valid_time(ChallengeRoomSystem *sys,int
requested_time ){
/*Name: check_valid_time
 * return TRUE if given time is valid else return FALSE*/
    return sys->last_update_time <= requested_time;
}

Result create_system(char *init_file, ChallengeRoomSystem **sys) {
/*Name: create_system
 * allocating system struct and call previous functions in order to create
 * system data bases by reading from given file, if some of the fails free
 * all allocated memory*/
    if(init_file==NULL||sys==NULL) return NULL_PARAMETER;
    (*sys)=(ChallengeRoomSystem*)malloc(SIZE_ROOM_SYSTEM);//memory for system
    if(*sys==NULL) return MEMORY_PROBLEM;
    FILE *data=fopen(init_file,"r");//open the data file
    assert(data!=NULL);//the assertion in PDF that the text file is legal
    if(init_system(*sys,data)==MEMORY_PROBLEM){
        fclose(data);//close file before return
        free(*sys);
        return MEMORY_PROBLEM;//when no allocated name or array of challenges
    }
    if(build_challenges_array(*sys, data)==MEMORY_PROBLEM
       ||build_rooms_array(*sys, data)==MEMORY_PROBLEM){
        fclose(data);//close file before return
        free(*sys);
        return MEMORY_PROBLEM;
    }
    fclose(data);//close file before return
    return OK;
}

Result visitor_arrive(ChallengeRoomSystem *sys, char *room_name, char
*visitor_name, int visitor_id, Level level, int start_time) {
/*Name: visitor_arrive
 * enter visitor to the system visitor list and a room if it is available*/
    if (sys == NULL) return NULL_PARAMETER;
    if (!check_valid_time(sys, start_time)) return ILLEGAL_TIME;
    if (visitor_name == NULL || room_name == NULL) return ILLEGAL_PARAMETER;
    if (find_visitor_by_id(sys, visitor_id) != NULL) return ALREADY_IN_ROOM;
    ChallengeRoom *requested_room = find_room_by_name(sys, room_name);
    if (add_visitor_to_list(sys, visitor_name,visitor_id) == MEMORY_PROBLEM) {
        return MEMORY_PROBLEM;
    }
    Visitor *new_visitor=sys->all_visitors->visitor;//always new added first
    if (requested_room==NULL||//in case requested room does't exist
        visitor_enter_room(requested_room,new_visitor, level, start_time)
        == NO_AVAILABLE_CHALLENGES){
        delete_visitor_from_list(sys, visitor_name);
        return NO_AVAILABLE_CHALLENGES;
    }
    sys->last_update_time=start_time;
    return OK;
}

Result visitor_quit(ChallengeRoomSystem *sys, int visitor_id, int quit_time) {
/*Name: visitor_quit
 * quit the visitor out of room and delete it from visitor list*/
    if (sys == NULL) return NULL_PARAMETER;
    if (!check_valid_time(sys, quit_time)) return ILLEGAL_TIME;
    VisitorNode need_to_remove_node = find_visitor_by_id(sys, visitor_id);
    if (need_to_remove_node == NULL)return NOT_IN_ROOM;
    visitor_quit_room(need_to_remove_node->visitor, quit_time);
    sys->last_update_time = quit_time;
    char *visitor_name_to_remove=need_to_remove_node->visitor->visitor_name;
    return delete_visitor_from_list(sys,visitor_name_to_remove);
}

Result all_visitors_quit(ChallengeRoomSystem *sys, int quit_time){
/*Name: all_visitors_quit
 * quit all visitors out their room and delete them from visitor list*/
    if(sys==NULL) return NULL_PARAMETER;
    if(!check_valid_time(sys,quit_time)) return ILLEGAL_TIME;
    VisitorNode curr=sys->all_visitors;
    while(curr){
        visitor_quit(sys,curr->visitor->visitor_id,quit_time);
        //removing visitors from the list from first to last
        curr=sys->all_visitors;//updating new fist
    }
    sys->last_update_time=quit_time;//make sure to updating operation time
    return OK;
}

Result system_room_of_visitor(ChallengeRoomSystem *sys, char *visitor_name,
                              char **room_name){
/*Name: system_room_of_visitor
 * finding the requested visitor and exporting his current room name to
 * by copying it to a given pointer*/
    if(sys==NULL) return NULL_PARAMETER;
    if(visitor_name==NULL||room_name==NULL) return ILLEGAL_PARAMETER;
    VisitorNode requested_visitor_node=find_visitor_by_name(sys,visitor_name);
    if(requested_visitor_node==NULL) return NOT_IN_ROOM;
    //when requested visitor doesn't exist in the visitors list
    return room_of_visitor(requested_visitor_node->visitor,room_name);
}

Result change_challenge_name(ChallengeRoomSystem *sys, int challenge_id, char *new_name){
/*Name: change_challenge_name
 * gets new name for challenge, first finding the requested challenge by
 * a given id and if founded changing it's name by using function from
 * challenge.h*/
    if (sys==NULL || new_name==NULL) return NULL_PARAMETER;
    assert(sys->all_rooms!=NULL);
    Challenge *need_to_be_changed=find_challenge_by_id(sys,challenge_id);
    if(need_to_be_changed==NULL) return ILLEGAL_PARAMETER;
    return change_name(need_to_be_changed,new_name);
    //changing wanted challenge name by internal function from challenge.c
}

Result change_system_room_name(ChallengeRoomSystem *sys, char *current_name, char *new_name) {
/*Name: change_system_room_name
 * gets new name for room, first finding the requested room by
 * a given name and if founded changing it's name by using function from
 * visitor_room.h*/
    if(sys == NULL || new_name == NULL || current_name ==
                                                           NULL){
        return NULL_PARAMETER;
    }
    assert(sys->all_rooms!=NULL);
    ChallengeRoom *need_to_be_changed=find_room_by_name(sys,current_name);
    if(need_to_be_changed == NULL) return ILLEGAL_PARAMETER;
    return change_room_name(need_to_be_changed, new_name);
    //changing wanted room name by internal function from visitor_room.c
}

Result best_time_of_system_challenge(ChallengeRoomSystem *sys, char *challenge_name, int *time) {
/*Name: best_time_of_system_challenge
 * exporting the best time of a challenge by a given name to a given output
 * address*/
    if(sys == NULL || time == NULL || challenge_name == NULL){
        return NULL_PARAMETER;
    }
    assert(sys->all_challenges!=NULL);
    Challenge *requested_challenge=find_challenge_by_name(sys,challenge_name);
    if(requested_challenge==NULL) return ILLEGAL_PARAMETER;
    return best_time_of_challenge(requested_challenge,time);
    //using internal function in challenge.c
}

Result most_popular_challenge(ChallengeRoomSystem *sys, char **challenge_name){
/*Name: most_popular_challenge
 * exporting the most popular Challenge's name by number of visits and copy
 * it's name to output pointer*/
    if (sys==NULL||challenge_name==NULL) return NULL_PARAMETER;
    assert(sys->all_challenges!=NULL);
    assert(*challenge_name==NULL);
    Challenge *most_popular=NULL;//helper pointer
    for (int i=0;i<sys->number_of_challenges;i++){
        int current_visits=UNUSED;
        num_visits(sys->all_challenges+i,&current_visits);
        if(current_visits== 0){
            continue;//ignoring unvisited challenges
        }
        Challenge *ptr=sys->all_challenges+i;
        assert(ptr!=NULL);
        if(most_popular==NULL||current_visits>=most_popular->num_visits){
            if(most_popular==NULL||current_visits > most_popular->num_visits
               || strcmp(sys->all_challenges[i].name, most_popular->name) < 0){
                //condition to find lowest lexicographic most popular Challenge
                most_popular=ptr;

            }
        }
    }
    if(most_popular==NULL){
        *challenge_name=NULL;
        return OK;
    }
    char *temp=(char *)malloc(SIZE_CHAR * STRLEN(most_popular->name));
    if(temp == NULL) return MEMORY_PROBLEM;
    *challenge_name=strcpy(temp, most_popular->name);
    return OK;
}

static  Result record_system_challenge(ChallengeRoomSystem *sys,char
**challenge_name) {
/*Name: record_system_challenge
 * exporting the record time Challenge's name by best time and copy
 * it's name to output pointer*/
    if(sys == NULL || challenge_name == NULL) return NULL_PARAMETER;
    assert(sys->all_challenges != NULL);
    assert(*challenge_name == NULL);
    Challenge *record=NULL;//helper pointer
    for(int i=0; i < sys->number_of_challenges; i++){
        if(sys->all_challenges[i].best_time== 0){
            continue;//ignoring unvisited challenges
        }
        Challenge *ptr=sys->all_challenges+i;
        assert(ptr!=NULL);
        if(record==NULL||ptr->best_time <= record->best_time){
            if(record==NULL||ptr->best_time < record->best_time ||
               strcmp(ptr->name, record->name) < 0){
                //condition to find lowest lexicographic record Challenge
                record=ptr;
            }
        }
    }
    if(record==NULL){//when not finding challenge with best time > 0
        *challenge_name=NULL;
        return OK;
    }
    char *temp=(char *) malloc(SIZE_CHAR * STRLEN(record->name));
    if(temp == NULL) return MEMORY_PROBLEM;
    *challenge_name=strcpy(temp, record->name);
    return OK;
}

Result destroy_system(ChallengeRoomSystem *sys, int destroy_time,
                      char **most_popular_challenge_p, char
                      **challenge_best_time){
/*Name: destroy_system
 * first makes all visitor to quit then run run requested statistics based on
 * former functions,  free all allocated memory using reset_system
 * function after all free the system struct*/
    if(sys==NULL||most_popular_challenge_p==NULL||challenge_best_time==NULL){
        return NULL_PARAMETER;
    }
    if(!check_valid_time(sys,destroy_time)) return ILLEGAL_TIME;
    all_visitors_quit(sys,destroy_time);
    if(most_popular_challenge(sys,most_popular_challenge_p)==MEMORY_PROBLEM) {
        return MEMORY_PROBLEM;
    }
    if(record_system_challenge(sys,challenge_best_time)==MEMORY_PROBLEM) {
        free(*most_popular_challenge_p);
        return MEMORY_PROBLEM;
    }
    reset_system(sys,sys->number_of_rooms,sys->number_of_challenges);
    //call reset_system to free all allocated memory
    free(sys);
    return OK;
}