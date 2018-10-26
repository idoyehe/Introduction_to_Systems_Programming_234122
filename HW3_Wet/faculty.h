#ifndef HW3_WET_FACULTY_H
#define HW3_WET_FACULTY_H

#include "list.h"
#include "set.h"
#include "escape_room.h"
#include "order.h"

/**
* Faculty data type
*
*This data type is for manage faculties save the faculty details
*
* The following functions are available:
*
*   facultyCreate                 - Creates a new faculty object
*   facultyDestroy                - Deletes an existing faculty
*   facultyAddRoom                - Exporting the faculty's Room
*   facultyRemoveRoom             - remove room by it's Id
*   facultyRemoveCompanyRooms     - remove all rooms by their Email
*   facultyAddOrder               - set an new order with given parameters
*   facultyRemoveOrdersOfEscaper  - remove all order that made by given escaper
*   facultyGetRecommendedRoom     - Exporting recommended room's id
*   facultyOrderRecommendedRoom   - set a new order to recommended room as
*                                  soon as possible
*  facultyGetRevenueDay           - Exporting the revenue of the current day
*  facultyGetTotalRevenue         - Exporting the total revenue
*  facultyEndOfDay                - make end of day operartion
*  facultyIsEscaperOrderExist     - checks if escaper has an order at that time
*  facultyCompareByID             - compare two faculties by their Ids
*  facultyGetID                   - get the faculty id to a given pointer
*  facultyRoomIdExist             - check if room with given id is exist
*/



/*Type for defining the faculty */
typedef struct faculty_t *Faculty;

/*For total revenue of the faculty*/
typedef int Revenue;

typedef enum facultyResult {
    FACULTY_SUCCESS,FACULTY_NULL_PARAMETER, FACULTY_MEMORY_PROBLEM,
    FACULTY_ROOM_NOT_EXIST,FACULTY_ROOM_ALREADY_IN,
    FACULTY_COMPANY_CANNOT_REMOVED, FACULTY_ROOM_CANNOT_REMOVED,
    FACULTY_ORDER_CANNOT_SET,FACULTY_ILLEGAL_PARAMETERS}FacultyResult;

/*
* Allocates a new faculty.
* Allocate a set for rooms ans a list for orders
* @param
* Id to set for the Faculty
* @return
* 	NULL - if allocations failed or id is ILLEGAL
* 	A new faculty in case of success.
*/
Faculty facultyCreate(TechnionFaculty id);

/**
* Destroying the given faculty, use for set also
* @param
* faculty to destroy
* @return
* void function
*/
void facultyDestroy(ListElement faculty);

/**
* adding a room to the faculty rooms set
* @param
* faculty to add to room
* room to add the faculty set
* @return
* FACULTY_NULL_PARAMETER if the given room is NULL
* FACULTY_ROOM_ALREADY_IN IF ROOM IS exist
* FACULTY_MEMORY_PROBLEM if setAdd failed
* FACULTY_SUCCESS
*/
FacultyResult facultyAddRoom(Faculty faculty, Room room);

/**
* removing a room from the faculty rooms set
*
* @param
* faculty to remove a room from
* room to be removed from the faculty set
* @return
* FACULTY_NULL_PARAMETER if the given room is NULL
* FACULTY_ILLEGAL_PARAMETERS if id is ILLEGAL
* FACULTY_ROOM_NOT_EXIST if the given room is not in the set
* FACULTY_ROOM_CANNOT_REMOVED if the room cannot removed due to exists orders
* FACULTY_SUCCESS
*/
FacultyResult facultyRemoveRoom(Faculty faculty, Room_Id id);

/**
* removing all company's rooms from the faculty rooms set
* @param
* faculty to remove a room from
* Email of the company to remove its rooms
* @return
* FACULTY_NULL_PARAMETER if the given Email is NULL
* FACULTY_ILLEGAL_PARAMETERS if email is ILLEGAL
* FACULTY_COMPANY_CANNOT_REMOVED if there are orders for company's rooms
* FACULTY_SUCCESS if removed or does not have room
*/
FacultyResult facultyRemoveCompanyRooms(Faculty faculty, Email email);

/**
* check if escaper has already an order in the same hour for another room
*
* @param
* Faculty to check if the order is there
* Escaper escaper to check for it
* Day to compare with the exist orders
* Hour to compare with exist orders
* @return
* FACULTY_NULL_PARAMETER if the escaper is NULL
* FACULTY_ILLEGAL_PARAMETERS if one of order parameters is NOT valid
* FACULTY_ORDER_CANNOT_SET if the escaper has an order to that time
* FACULTY_SUCCESS false
*/
FacultyResult facultyClientCanSetOrder(Faculty faculty, Client escaper, Day day,
                                       Time hour_order);

/**
* set a new order with proper params as given
* check if order can be set with givn parameters ans set it
* ASSERTION ID IS VALID, TIME IS VALID
* @param
* faculty to set an order to
* Escaper that make the order
* Id of the requested room
* Days to the order
* Hour of the order
* NUMBER OF PPL for the order
* @return
* FACULTY_NULL_PARAMETER if the given escaper is NULL
* FACULTY_ILLEGAL_PARAMETERS if one of order parameters is NOT valid
* FACULTY_ROOM_NOT_EXIST if the given room is not in the set
* FACULTY_ORDER_CANNOT_SET if the room is not available
* FACULTY_MEMORY_PROBLEM if listInsertElemenet failed
* FACULTY_SUCCESS
*/
FacultyResult facultyAddOrder(Faculty faculty,Client escaper, Room_Id id, Day
day, Time hour_order, Occapancy num_people);

/**
* remove all escaper's orders
* @param
* faculty to remove the orders
* Escaper to remove the orders from
* @return
* FACULTY_NULL_PARAMETER if the given escaper is NULL
* FACULTY_SUCCESS
*/
FacultyResult facultyRemoveOrdersOfClient(Faculty faculty, Client escaper);

/**
* exporting faculty revenue to a pointer
*
* @param
* faculty to get the revenue
* revenue to set the faculty's revenue
* @return
* FACULTY_NULL_PARAMETER if the given revenue pointer is NULL
* FACULTY_SUCCESS
*/
FacultyResult facultyGetTotalRevenue(Faculty faculty,Revenue *revenue);

/**
* search to escaper a recommended room
*
* @param
* faculty to remove the orders
* Escaper to check for it the recommended room
* NUM_PPL to search a room for
* best rank ptr to set the the best rank of the faculty
* room id ptr to save recommended room id
* @return
* FACULTY_NULL_PARAMETER if the given escaper or best rank ptr is NULL
* FACULTY_ILLEGAL_PARAMETERS if number of people is ILLEGAL
* FACULTY_ROOM_NOT_EXIST if set of rooms is empty
* FACULTY_SUCCESS
*/
FacultyResult facultyGetRecommendedRoom(Faculty faculty,Client escaper,
                         Occapancy people, Rank *best_rank,Room_Id *room_id);

/**
* set an order to escaper for the recommended room asap
*
* @param
* faculty to remove the orders
* Escaper to remove the orders from
* NUM_PPL to search a room for
* @return
* FACULTY_NULL_PARAMETER if the given escaper or id pointer is NULL
* FACULTY_ILLEGAL_PARAMETERS if number of people is ILLEGAL
* FACULTY_SUCCESS
*/
FacultyResult facultyOrderRecommendedRoom(Faculty faculty,Client escaper,Occapancy num_people);

/**
* exporting faculty revenue to of current day
*
* @param
* faculty to get the revenue
* revenue to set the faculty's revenue of today
* @return
* FACULTY_NULL_PARAMETER if the given revenue pointer is NULL
* FACULTY_SUCCESS
*/
FacultyResult facultyGetRevenueDay(Faculty faculty,Revenue *revenue_of_today);

/*
* collects statistics of the day and export the revenue and a list of orders
* that were accomplished today
* @param
* faculty to remove the orders
* Price ptr to set there the total revenue
* list ptr to set today orders
* @return
* FACULTY_NULL_PARAMETER if the given revenue is NULL
* FACULTY_MEMORY_PROBLEM if allocation of the list failed
* FACULTY_SUCCESS
*/
FacultyResult facultyEndOfDay(Faculty faculty,Revenue *revenue,List *today_order);

/**
* Type of function used by the set to identify equal faculties by their id and
* comparing by their total revenue
* This function will be used to sort a faculties list
* @param
* Two faculties elements
* @return
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*	  	A negative integer if the second element is greater.
*/
int facultyCompareByRevAndID(SetElement faculty1, SetElement faculty2);

/**
* creating a copy of given faculty with the same parameters
* creating new copy of the faculty and export it
* used for set
* @param
* faculty to copy
* @return
*
* NULL if the allocation for copy failed
* else the copy
*/
ListElement facultyCopy(ListElement faculty_to_copy);

/**
* exporting faculty id to a pointer
*
* @param
* faculty to get the id
* id to set the faculty's id
* @return
* FACULTY_NULL_PARAMETER if the given id pointer is NULL
* FACULTY_SUCCESS
*/
FacultyResult facultyGetID(Faculty faculty, TechnionFaculty *id);

/**
* check if room with given Id is exist in the faculty
* DOES NOT CHECK IF ID IS VALID ONLY ASSERT THAT
* @param
* faculty to search fo the room
* id to search
* @return
* TRUE if room found
* else FALSE
*/
bool facultyRoomIdExist(Faculty faculty,Room_Id id);

/**
* check if given faculty id is valid
*
* @param
* id to check
* @return
* TRUE if given Id is in [0,UNKNOWN)
* else FALSE
*/
bool facultyValidId(TechnionFaculty id);
#endif //HW3_WET_FACULTY_H
