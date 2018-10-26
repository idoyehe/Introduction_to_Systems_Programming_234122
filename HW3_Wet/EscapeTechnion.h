#ifndef HW3_WET_ESCAPETECHNION_H
#define HW3_WET_ESCAPETECHNION_H

#include "mtm_ex3.h"
#include "list.h"
#include "faculty.h"

/**
* Escape Technion data type
*
*This data type is for manage faculties save the system details
*
* The following functions are available:
*
*   systemCreate                 - Creates a new system object
*   systemDestroy                - Deletes an existing system and deallocate
*                                 all resources
*   systemRoomAdd                - add a room to the system
*   systemRoomRemove             - remove a room from the system
*   systemCompanyAdd             - add a company to faculty
*   systemCompanyRemove          - remove a company from the system
*   systemClientAdd             - add an Client to the system
*   systemClientRemove          - remove an client from the system
*   systemClientOrder           - making an order to client in the system
*   systemClientRecommend       - making an order to client by for most
*                                  recommended room in th system
*   systemReportDay              - Creating a report to the passing day
*                                  exporting a list of today oreders
*   systemReportBest             - Creating a report of the best 3 faculties
*                                  and export it
*   systemExportDay              - exporting the current day
*   systemExportRevenue          - exporting the day's revenue
*
*/
/** Type for defining the system */

typedef enum systemResult {
    SYSTEM_SUCCESS, SYSTEM_ILLEGAL_PARAMETER, SYSTEM_MEMORY_PROBLEM,
    SYSTEM_EMAIL_ALREADY_EXIST, SYSTEM_ROOM_ID_ALREADY_EXIST,
    SYSTEM_RESERVATION_EXIST, SYSTEM_COMPANY_EMAIL_NOT_EXIST,
    SYSTEM_ROOM_ID_NOT_EXIST,SYSTEM_CLIENT_EMAIL_NOT_EXIST,
    SYSTEM_CLIENT_IN_ROOM, SYSTEM_ROOM_NOT_AVAILABLE, SYSTEM_NO_ROOMS_AVAILABLE,
    SYSTEM_NULL_PARAMETER
} SystemResult;

/*For input set of working hours of a room*/
typedef char Hour[3];

typedef struct escapeTechnion_t*EscapeTechnion;


/*
* Allocates a new system.
* Allocate a set for faculties and a sert for companies and for clients
** @param
* @return
* 	NULL - if allocations failed.
* 	A new system in case of success.
*/
EscapeTechnion systemCreate();

/**
* Destroying the given system and free all resources.
* @param
* system to destroy
* @return
* void function
*/
void systemDestroy(EscapeTechnion system);

/**
* adding a room to the system set
* @param
* system to add to room
* room params - openning times email etc...
* @return
* SYSTEM_ILLEGAL_PARAMETER if any param isnt valid
* SYSTEM_COMPANY_EMAIL_NOT_EXIST the given email not belong to any company
* SYSTEM_ROOM_ID_ALREADY_EXIST the room already in the system
* SYSTEM_MEMORY_PROBLEM if allocation failed
* SYSTEM_SUCCESS else
*/
SystemResult systemRoomAdd(EscapeTechnion system, Email company_email,Room_Id
room_id, Room_Price room_price, Occapancy room_people, Hour open, Hour close,Difficulty room_level);

/**
* removing a room from the system companies set
*
* @param
* system to remove a room from
* faculty to add the room to
* room Id to be removed
* @return
* SYSTEM_ILLEGAL_PARAMETER if any param isnt valid
* SYSTEM_ROOM_ID_NOT_EXIST if the room id dewsnt exist
* SYSTEM_RESERVATION_EXIST the room has reservations - cannot be removed
* SYSTEM_SUCCESS else
*/
SystemResult systemRoomRemove(EscapeTechnion system, TechnionFaculty faculty_id,Room_Id room_id);

/**
* adding a company to the system set
* @param
* system to add to company
* room params - email faculty id
* @return
* SYSTEM_ILLEGAL_PARAMETER if any param isnt valid
* SYSTEM_COMPANY_EMAIL_NOT_EXIST the given email not belong to any company
* SYSTEM_MEMORY_PROBLEM if allocation failed
* SYSTEM_SUCCESS else
*/
SystemResult systemCompanyAdd(EscapeTechnion system, Email company_email,
                              TechnionFaculty faculty_id);

/**
* removing a company from the system companies set
*
* @param
* system to remove a room from
* faculty to add the room to
* room Id to be removed
* @return
* SYSTEM_ILLEGAL_PARAMETER if any param isn't valid
* SYSTEM_COMPANY_EMAIL_NOT_EXIST if the room id dewsnt exist
* SYSTEM_RESERVATION_EXIST the company has reservations - cannot be removed
* SYSTEM_SUCCESS else
*/
SystemResult systemCompanyRemove(EscapeTechnion system, Email company_email);

/**
* adding an client to the system set
* @param
* system to add to room
* client params - opening times email etc...
* @return
* SYSTEM_ILLEGAL_PARAMETER if any param isn't valid
* SYSTEM_EMAIL_ALREADY_EXIST if the client already in the system
* SYSTEM_MEMORY_PROBLEM if allocation failed
* SYSTEM_SUCCESS else
*/
SystemResult systemClientAdd(EscapeTechnion system, Email client_email,
                              TechnionFaculty faculty_id,Skill skill_level);

/**
* removing an client from the system clients set
*
* @param
* system to remove a room from
* client's email to be removed
* @return
* SYSTEM_ILLEGAL_PARAMETER if any param isnt valid
* SYSTEM_CLIENT_DOES_NOT_EXIST if the client email doesnt exist
* SYSTEM_SUCCESS else
*/
SystemResult systemClientRemove(EscapeTechnion system, Email client_email);


/**
* creating an order to the client
*
* @param
* system to remove a room from
* user email
* user faculty
* reservation hours
* people number
* @return
* SYSTEM_ILLEGAL_PARAMETER if any param isnt valid
* SYSTEM_CLIENT_DOES_NOT_EXIST if the client email doesnt exist
* SYSTEM_ROOM_ID_NOT_EXIST if the room not exsits
* SYSTEM_CLIENT_IN_ROOM if the user already in room
* SYSTEM_ROOM_NOT_AVAILABLE if the room not free in the requsted hours
* SYSTEM_SUCCESS else
*/
SystemResult systemClientOrder(EscapeTechnion system, Email client_email,
                                TechnionFaculty faculty_id,Room_Id room_id, Day day,
                                Time time, Occapancy num_people);

/**
* creating an order to the client to the recommened room
*
* @param
* system to remove a room from
* user email
* number od people
* @return
* SYSTEM_ILLEGAL_PARAMETER if any param isnt valid
* SYSTEM_CLIENT_DOES_NOT_EXIST if the client email doesnt exist
* SYSTEM_NO_ROOMS_AVAILABLE if there are no rooms at the system
* SYSTEM_SUCCESS else
*/
SystemResult systemClientRecommend(EscapeTechnion system, Email
client_email,Occapancy num_people);

/**
* creating a report of the today- exporting a list af all today orders
* advence current day of the system
* @param
* system to remove a room from
* @return
* SYSTEM_MEMORY_PROBLEM- memory allocation failed
* SYSTEM_SUCCESS
*/
SystemResult systemReportDay(EscapeTechnion system, List *today_order);

/**
* creating a report iof the last day - for the best 3 faculties..
*
* @param
* system to remove a room from
* pointer to matrix to be updated
* @return
* SET_NULL_ARGUMENT if pointer to export list is NULL
* SYSTEM_NULL_PARAMETER if the pointer is Null
* SYSTEM_SUCCESS
*/
SystemResult systemReportBest(EscapeTechnion system, List * best);

/**
* creating a report iof the last day - for the best 3 faculties..
*
* @param
* system to remove a room from
* pointer to day to be updated
* @return
* SYSTEM_NULL_PARAMETER if the pointer is Null
* SYSTEM_SUCCESS
*/
SystemResult systemGetDay(EscapeTechnion system, Day *day);

/**
* creating a report iof the last day - for the best 3 faculties..
*
* @param
* system to remove a room from
* pointer to revenue to be updated
* @return
* SYSTEM_NULL_PARAMETER if the pointer is Null
* SYSTEM_SUCCESS
*/
SystemResult systemGetRevenue(EscapeTechnion system,Revenue *revenue);
#endif //HW3_WET_ESCAPETECHNION_H
