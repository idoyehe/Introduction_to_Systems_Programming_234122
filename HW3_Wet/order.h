#ifndef HW3_WET_ORDER_H
#define HW3_WET_ORDER_H

#include "list.h"
#include "escape_room.h"
#include "client.h"

/**
* Order data type
*
*This data type is for manage orders save the order details
*
* The following functions are available:
*
*   orderCreate            - Creates a new order object
*   orderSet               - set new order with given parameter
*   orderDestroy           - Deletes an existing order
*   orderCopy              - Copies an existing order
*   orderGetRoom           - Exporting the order's Room
*   orderGetEscaper        - Exporting the order's User
*   orderGetPrice          - Exporting the order's Price to int*
*   orderGetTime           - Exporting to 2 int* the order's time
*   orderCompare           - compare between 2 orders' time
*   orderFilterRoom        - return true if the order is for this room
*   orderFilterEscaper     - return true if the order is of this user
*/

/** Type for defining the order */

typedef enum orderResult {ORDER_SUCCESS, ORDER_NULL_PARAMETER,
    ORDER_ILLEGAL_PARAMETERS}OrderResult;

/*for days to order and system day*/
typedef int Day;

/*for Total price of an order*/
typedef int Cost;

typedef struct order_t* Order;

/*
* Allocates a new order.
*
* @return
* 	NULL - if allocations failed.
* 	A new order in case of success.
*/
Order orderCreate();

/*
* Set a new order with given parameters.
* @param
* order to set it's parameters
* room to order
* escaper that makes the order
* ThechnionFaculty that order belongs
* number of people that ordering the order
* Days to order
* Time of order
*
* @return
* 	ORDER_NULL_PARAMETERS - if one of given pointers is null.
* 	ORDER_ILLEGAL_PARAMETERS- if one of the parameters is ILLEGAL
* 	ORDER_SUCCESS when set successfully.
*/
OrderResult orderSet(Order order,Room room,Client escaper,TechnionFaculty
faculty,Occapancy people,Day days_to_order,Time time_of_order);

/**
* destroying the given order object.
* @param
* void* to destroy
* @return
 * void function
*/
void orderDestroy(ListElement order);

/**
* creating a copy of given order object pointer
* creating new copy of the order and export it using void* pointer using in list
* @param
* order to copy
* @return
* NULL if the allocation for copy failed or some
*       order parameters has NEVER been set
* else a new void* pointer
*/
ListElement orderCopy(ListElement order);

/**
* Exporting a pointer of the order room
*
* @param
* Order to export it's room
* Room pointer to save the room
* @return
* ORDER_NULL_PARAMETERS if one of the pointers is null
*                       or room to order has NEVER been set
* ORDER_SUCCESS when exporting successfully
*/
OrderResult orderGetRoom(Order order,Room* room);

/**
* Exporting a pointer of the order Escaper
*
* @param
* Order to export it's client
* Escaper pointer to save the client
* @return
* ORDER_NULL_PARAMETERS if one of the pointers is null
*                       or escaper, the client has NEVER been set
* ORDER_SUCCESS when exporting successfully
*/
OrderResult orderGetClient(Order order, Client* escaper);

/**
* Exporting the price of the order
*
* @param
* Order to export it's price
* price pointer to save the price
* @return
* ORDER_NULL_PARAMETERS if one of the pointers is null
* ORDER_ILLEGAL_PARAMETERS if order price has never been set
* ORDER_SUCCESS when exporting successfully
*/
OrderResult orderGetPrice(Order order,Cost* price);

/**
* Exporting the time of order
*
* @param
* Order to export it's time
* int* to save days to order
* int* to save order's hour
* @return
* ORDER_NULL_PARAMETERS if one of the pointers is null
* ORDER_ILLEGAL_PARAMETERS if order time has never been set
* ORDER_SUCCESS when exporting successfully
*/
OrderResult orderGetTime(Order order,Day* days,Time* hour);

/**
* Type of function used by the list to compare two order by their order time,
* then their faculty and then room id.
* This function will be used to sorting the list.
* @param
* Two orders elements
* @return
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/
int orderCompare(ListElement order_element1, ListElement order_element2);

/**
* Check if order is set to the given room
* @param
* Order element
* Room to compare
* @return
* true if the order set to this room else false
*/
bool orderFilterRoom(ListElement order,ListFilterKey room);

/**
* Check if days to order of given order is set to the given day
* @param
* Order element
* Day to compare
* @return
* true if the days to order set to this day else false
*/
bool orderFilterDay(ListElement order,ListFilterKey Day);

/**
* Check if order is set to the given user
* @param
* Order element
* Escaper to compare
* @return
* true if the order set to this escaper else false
*/
bool orderFilterEscaper(ListElement order,ListFilterKey escaper);

/**
* Decrease the days to order by one
*
* @param
* Order decrease days
* @return
* ORDER_ILLEGAL_PARAMETERS if number of days of given order is 0
* ORDER_SUCCESS when decreasing successfully
*/
OrderResult orderAdvanceDay(Order order);

/**
* Exporting the faculty of order
*
* @param
* Order to export it's faculty
* output_id pointer to export the faculty id
* @return
* ORDER_NULL_PARAMETERS if the pointer is null
* ORDER_ILLEGAL_PARAMETERS if order faculty has NEVER been set
* ORDER_SUCCESS when exporting successfully
*/
OrderResult orderGetFaculty(Order order,TechnionFaculty*output_id);

/**
* Exporting the number of people of the order
* ASSERTION order has been set
*
* @param
* Order to export it's faculty
* people pointer to export the faculty id
* @return
* ORDER_NULL_PARAMETERS if the pointer is null
* ORDER_ILLEGAL_PARAMETERS if order faculty has never been set
* ORDER_SUCCESS when exporting successfully
*/
OrderResult orderGetNumPeople(Order order,Occapancy *people);

/**
* check if given time is valid
*
* @param
* time to check
* @return
* TRUE if given time is in [0,23]
* else FALSE
*/
bool orderValidTime(Time time,Day days);

#endif //HW3_WET_ORDER_H