#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "escape_room.h"

#define STRLEN(e) strlen((e))+1
#define MIN 0
#define UNUSED -1
#define MIN_LEVEL 1
#define MAX_LEVEL 10
#define PRICE_FACTOR 4
#define MAX_HOUR 24

struct escape_room_t{
    Room_Id id;
    Email email;
    Room_Price price;
    Occapancy num_people;
    Difficulty diff;
    Time start_hour,close_hour;
};

/**
* check if given time is valid
*
* @param
* time to check
* @return
* TRUE if given time is in [0,24]
* else FALSE
*/
static inline bool validTime(Time time) {
    return time<=MAX_HOUR&&time>=MIN;
}

inline bool roomValidId(Room_Id id){
    return id>MIN;
}

/**
* check if given room price is valid
*
* @param
* room id to check
* @return
* TRUE if price is factor by 4 and positive
* else FALSE
*/
static inline bool validPrice(Room_Price price){
    return (price>=PRICE_FACTOR)&&(!(price%PRICE_FACTOR));
}

inline bool roomValidNumPeople(Occapancy num_people){
    return (num_people>MIN);
}

/**
* check if given level is valid
*
* @param
* id to check
* @return
* TRUE if given level is in [1,10]
* else FALSE
*/
static inline bool validLevel(Difficulty level){
    return (level<=MAX_LEVEL&&level>=MIN_LEVEL);
}

Room roomCreate(){
    Room new_room=(Room)malloc(sizeof(*new_room));
    if (!new_room){
        return NULL;
    }
    new_room->id=UNUSED;
    new_room->email=NULL;
    new_room->price=UNUSED;
    new_room->diff=UNUSED;
    new_room->num_people=UNUSED;
    new_room->start_hour=UNUSED;
    new_room->close_hour=UNUSED;
    return new_room;
}

RoomResult roomSetEmailFromCompany(Room room,Company company){
    assert(room!=NULL);
    if(!company){
        return ROOM_NULL_PARAMETER;
    }
    const Email company_email= companyGetEmailR(company);
    if(!company_email){
        return ROOM_NULL_PARAMETER;
    }
    Email temp=(Email)malloc(STRLEN(company_email));
    if(!temp){
        return ROOM_MEMORY_PROBLEM;
    }     
    free(room->email);
    room->email=strcpy(temp,company_email);
    return ROOM_SUCCESS;
}

RoomResult roomSetId(Room room, Room_Id id) {
    assert(room != NULL);
    if (!roomValidId(id)) {
        return ROOM_ILLEGAL_PARAMETERS;
    }
    room->id = id;
    return ROOM_SUCCESS;
}

RoomResult roomSetLevel(Room room, Difficulty level) {
    assert(room != NULL);
    if (!validLevel(level)) {
        return ROOM_ILLEGAL_PARAMETERS;
    }
    room->diff = level;
    return ROOM_SUCCESS;
}

RoomResult roomGetLevel(Room room, Difficulty* level){
    assert(room!=NULL);
    if(!level){
        return ROOM_NULL_PARAMETER;
    }
    if (!validLevel(room->diff)) {
        return ROOM_ILLEGAL_PARAMETERS;
    }
    *level=room->diff;
    return ROOM_SUCCESS;
}

const Email roomGetEmailR(Room room){
    assert(room!=NULL);
    return room->email;
}

void roomDestroy(SetElement room_element) {
    if (!room_element) {
        return;
    }
    Room room = (Room) room_element;
    free(room->email);
    free(room);
}

int roomCompare(SetElement room_element1, SetElement room_element2){
    assert (room_element1!=NULL);
    assert (room_element2!=NULL);
    Room room1=(Room)room_element1;
    Room room2=(Room)room_element2;
    assert (room1->id!=UNUSED);
    assert(room2->id!=UNUSED);
    return room1->id-room2->id;
}

RoomResult roomSetPrice(Room room, Room_Price price) {
    assert(room != NULL);
    if (!validPrice(price)) {
        return ROOM_ILLEGAL_PARAMETERS;
    }
    room->price=price;
    return ROOM_SUCCESS;
}

RoomResult roomSetNumPeople(Room room, Occapancy num_people) {
    assert(room != NULL);
    if (!roomValidNumPeople(num_people)) {
        return ROOM_ILLEGAL_PARAMETERS;
    }
    room->num_people = num_people;
    return ROOM_SUCCESS;
}

RoomResult roomGetId(Room room, Room_Id* id){
    assert(room!=NULL);
    if(!id){
        return ROOM_NULL_PARAMETER;
    }
    if(!roomValidId(room->id)){
        return ROOM_ILLEGAL_PARAMETERS;
    }
    *id= room->id;
    return ROOM_SUCCESS;
}

RoomResult roomGetPrice(Room room, Room_Price* price){
    assert(room != NULL);
    if (!price) {
        return ROOM_NULL_PARAMETER;
    }
    if (!validPrice(room->price)) {
        return ROOM_ILLEGAL_PARAMETERS;
    }
    *price = room->price;
    return ROOM_SUCCESS;
}

RoomResult roomGetNumPeople(Room room, Occapancy* num_ppl){
    assert(room!=NULL);
    if(!num_ppl){
        return ROOM_NULL_PARAMETER;
    }
    if(!roomValidNumPeople(room->num_people)){
        return ROOM_ILLEGAL_PARAMETERS;
    }
    *num_ppl=room->num_people;
    return ROOM_SUCCESS;
}

RoomResult roomSetWorkingHours(Room room, Time open_hour,Time close_hour){
    assert(room!=NULL);
    if(!validTime(open_hour)||!validTime(close_hour)||open_hour>=close_hour){
        return ROOM_ILLEGAL_PARAMETERS;
    }
    assert(open_hour<close_hour);
    room->start_hour=open_hour;
    room->close_hour=close_hour;
    return ROOM_SUCCESS;
}

RoomResult roomGetWorkingHours(Room room, Time* start_hour,Time* close_hour){
    assert(room!=NULL);
    if(!close_hour||!start_hour){
        return ROOM_NULL_PARAMETER;
    }
    Time open=room->start_hour;
    Time close= room->close_hour;
    if(!validTime(open)||!validTime(close)||open>=close){
        return ROOM_ILLEGAL_PARAMETERS;
    }    *start_hour=room->start_hour;
    *close_hour=room->close_hour;
    return ROOM_SUCCESS;
}

/**
* check if room's all parameters has all been set
*
* @param
* room to check
* @return
* TRUE if room's all parameters has all been set
* else FALSE
*/static inline bool validRoom(Room room){
    assert(room!=NULL);
    return !(room->email==NULL||room->close_hour==UNUSED||room->start_hour ==UNUSED
            ||room->num_people==UNUSED||room->price==UNUSED||room->id==UNUSED
             ||room->diff==UNUSED);
}

SetElement roomCopy(SetElement room_element){
    assert(room_element!=NULL);
    Room room=(Room)room_element;
    if(!validRoom(room)){//in case one of room has NEVER been set
        return NULL;
    }
    Room copy_room=roomCreate();
    if(!copy_room){
        return NULL;
    }
    Email temp=(Email)malloc(STRLEN(room->email));
    if(!temp){
        roomDestroy(copy_room);
        return NULL;
    }
    copy_room->email=strcpy(temp,room->email);
    copy_room->id=room->id;
    copy_room->price=room->price;
    copy_room->diff=room->diff;
    copy_room->num_people=room->num_people;
    copy_room->start_hour=room->start_hour;
    copy_room->close_hour=room->close_hour;
    return copy_room;
}


RoomResult roomClientRank(Room room, Client client,Occapancy p_e,Rank *rank){
    assert(room!=NULL);
    if(!rank||!client){
        return ROOM_NULL_PARAMETER;
    }
    if(!validRoom(room)){
        return ROOM_ILLEGAL_PARAMETERS;
    }
    Occapancy p_r=room->num_people;
    Difficulty difficulty=room->diff;
    Skill skill_level;
#ifndef NDEBUG
     ClientResult res=
#endif
            clientGetLevel(client,&skill_level);
    assert(res==CLIENT_SUCCESS);
    *rank=(p_r-p_e)*(p_r-p_e)+(difficulty-skill_level)*(difficulty-skill_level);
    return ROOM_SUCCESS;
}