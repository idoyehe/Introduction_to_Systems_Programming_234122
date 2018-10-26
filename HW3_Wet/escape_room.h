#ifndef HW3_WET_ROOM_H
#define HW3_WET_ROOM_H

#include "set.h"
#include "company.h"
#include "client.h"

/**
* Escape Room data type
*
* This data type is for rooms in the system, save the room company, id,
* level, operation hours, price and number of people
* The following functions are available:
*
*   roomCreate            - Creates a new room
*   roomDestroy           - Deletes an existing room and frees all resources
*   roomCopy              - Copies an existing room
*   roomSetEmailFromCompany  - set an Email for room from company
*   roomGetEmailByRef     - Exporting to const char* the room's email
*   roomSetId             - set an Id for room
*   roomGetId             - Exporting to int* the room's Id
*   roomSetLevel          - set a level for room
*   roomGetLevel          - Exporting to int* the room's level
*   roomSetPrice          - set a Price for room
*   roomGetPrice          - Exporting to int* the room's Price
*   roomSetNumPeople      - set a number of people for room
*   roomGetNumPeople      - Exporting to int* the room's number of people
*   roomSetWorkingHours   - set operation hours fo the room
*   roomGetWorkingHours   - Exporting to two int* the room's start and close
*                           hour
*   roomCompare           - compare between 2 rooms' Id
*   roomRank              - calculating the room rank according to parameters
*/

/** Type for defining the room */
typedef struct escape_room_t* Room;

/*For room id*/
typedef int Room_Id;

/*for room price and order price*/
typedef int Room_Price;

/*For room max number of people*/
typedef int Occapancy;

/*For room opening and closing time*/
typedef int Time;

/*For room difficulty*/
typedef int Difficulty;

/*For room rank*/
typedef int Rank;

typedef enum RoomResult{ROOM_SUCCESS, ROOM_NULL_PARAMETER,
    ROOM_MEMORY_PROBLEM,ROOM_ILLEGAL_PARAMETERS} RoomResult;

/*
* Allocates a new Room.
*
* Creates a new empty room. This function used by the functions which
* will be used for copying room.

* @return
* 	NULL - if allocations failed.
* 	A new Room in case of success.
*/
Room roomCreate();

/**
* setting the room Email
*
* creating new copy of the given company Email and setting the room Email as
* the copy that way we make sure the room is under certain company and room has
* VALID Email
*
* @param
* Room to set Email
* Company to copy it's Email
* @return
* ROOM_NULL_PARAMETER if the given Company is NULL
*                     or company email has NEVER been set
* ROOM_MEMORY_PROBLEM if the allocation for copy failed
* else ROOM_SUCCESS
*/
RoomResult roomSetEmailFromCompany(Room room,Company company);

/**
* getting the room Email by reference
*
* exporting the address room Email to const char* pointer
*
* @param
* Room to get Email
* @return
* NULL- if room email has NEVER been set
* const char* with email of the room
*/
const Email roomGetEmailR(Room room);

/**
* setting the room ID
*
* @param
* Room to set ID
* ID to set
* @return
* ROOM_ILLEGAL_PARAMETERS if given id is NOT VALID
* ROOM_SUCCESS
*/
RoomResult roomSetId(Room room, Room_Id id);

/**
* getting the room Id
*
* @param
* Room to get id
* id address to set
* @return
* ROOM_NULL_PARAMETER if the given address is NULL
* ROOM_ILLEGAL_PARAMETERS if room id has NEVER been set
* else ROOM_SUCCESS
*/
RoomResult roomGetId(Room room, Room_Id* id);

/**
* creating a copy of given room object
* creating new copy of the room and export it using void* pointer to a set
* @param
* void* to copy
* @return
* NULL - if the allocation for copy failed
*        or some of room parameters has NEVER been set
* else a new void* pointer the hold room
*/
SetElement roomCopy(SetElement room);

/**
* destroying the given room pointer and deallocate memory such as room email
* @param
* room to destroy using void*
* @return
 * void function
*/
void roomDestroy(SetElement room);

/**
* Type of function used by the set to identify equal room by their id.
* This function will be used to deciding the iteration order of the set.
* @param
* Two escape_rooms elements
* @return
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*	  	A negative integer if the second element is greater.
*/
int roomCompare(SetElement room_element1, SetElement room_element2);

/**
* setting the room price
* ASSERTION PRICE IS VALID
* @param
* Room to set price
* price to set
* @return
* ROOM_ILLEGAL_PARAMETERS if given price is ILLEGAL
* ROOM_SUCCESS
 */
RoomResult roomSetPrice(Room room, Room_Price price);

/**
* setting the room number of people
* ASSERTION NUM_PEOPLE IS VALID
* @param
* Room to set number of people
* number of people to set
* @return
* ROOM_ILLEGAL_PARAMETER if given number of people is illegal
* ROOM_SUCCESS
*/
RoomResult roomSetNumPeople(Room room, Occapancy num_people);

/**
* getting the room price
*
* @param
* Room to get price
* price address to set
* @return
* ROOM_NULL_PARAMETER if the given address is NULL
* ROOM_ILLEGAL_PARAMETERS if room price has never been set
* else ROOM_SUCCESS
*/
RoomResult roomGetPrice(Room room, Room_Price* price);

/**
* getting the room num_ppl
*
* @param
* Room to get num_ppl
* num_ppl address to set
* @return
* ROOM_NULL_PARAMETER if the given address is NULL
* ROOM_ILLEGAL_PARAMETERS if room number of people has never been set
* else ROOM_SUCCESS
*/
RoomResult roomGetNumPeople(Room room, Occapancy* num_ppl);

/**
* setting the room start and closing hours
* ASSERTION HOURS IS VALID
* @param
* Room to set working hours
*start hour to set for room
* close hour to set for room
* @return
* ROOM_ILLEGAL_PARAMETERS if given working hours is ILLEGAL
* ROOM_SUCCESS
*/
RoomResult roomSetWorkingHours(Room room, Time open_hour,Time close_hour);

/**
* getting the room working hours in int format
*
* @param
* Room to get working hours
* start hour address to update te stating hour
* close hour address to update te closing hour
* @return
* ROOM_NULL_PARAMETER if one of the given addresses is NULL
* ROOM_ILLEGAL_PARAMETERS if room working hours has never been set
* else ROOM_SUCCESS
*/
RoomResult roomGetWorkingHours(Room room, Time* open_hour, Time* close_hour);

/**
* getting the room level
*
* @param
* Room to get level
* level address to set
* @return
* ROOM_NULL_PARAMETER if the given address is NULL
* ROOM_ILLEGAL_PARAMETERS if room level is ILLEGAL
* else ROOM_SUCCESS
*/
RoomResult roomGetLevel(Room room, Difficulty* level);

/**
* setting the level
* ASSERTION LEVEL IS VALID
* @param
* Room to set level
* level to set
* @return
* ROOM_ILLEGAL_PARAMETERS if given level is ILLEGAL
* ROOM_SUCCESS
*/
RoomResult roomSetLevel(Room room, Difficulty level);

/**
* Get room rank and export it to Rank pointer
* calculating the room rank by the given formula with given parameters
* ASSERTION: given parameters are Valid
* @param
* Room to get level and recommended number of people
* skill level of escaper
* p_e number of people to order
* @return
* ROOM_NULL_PARAMETER if rank pointer is NULL
* ROOM_SUCCESS
*/
RoomResult roomClientRank(Room room, Client client,Occapancy p_e,Rank *rank);

/**
* check if given room id is valid
*
* @param
* room id to check
* @return
* TRUE if given id is positive
* else FALSE
*/
bool roomValidId(Room_Id id);

/**
* check if given number of people is valid
*
* @param
* number of people to check
* @return
* TRUE if given number of people is positive
* else FALSE
*/
bool roomValidNumPeople(Occapancy num_people);
#endif //HW3_WET_ROOM_H