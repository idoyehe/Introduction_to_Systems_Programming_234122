#ifndef HW3_WET_client_H
#define HW3_WET_client_H

#include "set.h"
#include "mtm_ex3.h"
#include "company.h"
/**
* client data type
*
* This data type is for users in the system, save the the client email,
* faculty and level
*
* The following functions are available:
*
*   clientCreate            - Creates a new client
*   clientDestroy           - Deletes an existing client and frees all resources
*   clientCopy              - Copies an existing client
*   clientSetEmail          - set an Email for client
*   clientGetEmailR         - Exporting to const char* the client's email
*   clientSetFaculty        - set a faculty for client
*   clientGetFaculty        - Exporting to int* the client's Faculty
*   clientSetSkill          - set an skill level for client
*   clientGetSkill          - Exporting to int* the client's skill level
*   clientCompare           - compare between 2 clients' Email
*/

/** Type for defining the client */
typedef struct client_t* Client;

/*Client skill skill_level*/
typedef int Skill;

typedef enum clientResult {CLIENT_SUCCESS, CLIENT_NULL_PARAMETER,
    CLIENT_MEMORY_PROBLEM,CLIENT_ILLEGAL_PARAMETERS} ClientResult;

/*
* Allocates a new Client.
*
* Creates a new empty client. This function used by the functions which
* will be used for copying client.

* @return
* 	NULL - if allocations failed.
* 	A new Client in case of success.
*/
Client clientCreate();

/**
* creating a copy of given client
* creating new copy of the client and export it using void* pointer for set
* @param
* void* to copy
* @return
* NULL if the allocation for copy failed or client parameters has NEVER set
* else a new void* pointer
*/
SetElement clientCopy(SetElement client);

/**
* destroying the given client pointer and deallocate memory such as Email
* @param
* void* to destroy
* @return
 * void function
*/
void clientDestroy(SetElement client_element);

/**
* Type of function used by the set to identify equal clients by comparing
* their emails.
* This function will be used to deciding the iteration order of the set.
* @param
* Two client elements
* @return
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/
int clientCompare(SetElement client_element1, SetElement client_element2);

/**
* setting the client Email
* creating new copy of the given Email and setting the client Email as the copy
*
* @param
* client to set Email
* Email to set
* @return
* client_NULL_PARAMETER if the given Email is NULL
* client_ILLEGAL_PARAMETERS if email is NOT valid
* COMPANY_MEMORY_PROBLEM if the allocation for copy failed
* else COMPANY_SUCCESS
*/
ClientResult clientSetEmail(Client client,const Email email);

/**
* setting the client Faculty
*
* @param
* client to set faculty
* faculty to set
* @return
* client_ILLEGAL_PARAMETERS if faculty id is NOT valid
* else COMPANY_SUCCESS
*/
ClientResult clientSetFaculty(Client client,TechnionFaculty faculty);

/**
* setting the client Faculty
*
* @param
* client to set level
* level to set
* @return
* client_ILLEGAL_PARAMETERS if level is NOT VALID
* else COMPANY_SUCCESS
*/
ClientResult clientSetLevel(Client client,Skill skill_level);

/**
* getting the client Email by reference
*
* exporting the address in heap of client Email to const char*
*
* @param
* client to get Email
* @return
* NULL - if client Email has NEVER been set
* const char* with email of the room
*/
const Email clientGetEmailR(Client client);

/**
* getting the client Faculty
*
* creating new copy of the client Faculty and exporting it to given address
*
* @param
* client to get Faculty
* Faculty address to set
* @return
* client_NULL_PARAMETER if the given address is NULL
* client_ILLEGAL_PARAMETERS id client faculty id has NEVER been set
* else COMPANY_SUCCESS
*/
ClientResult clientGetFaculty(Client client,TechnionFaculty* faculty);

/**
* getting the client Level
*
* creating new copy of the client Level and exporting it to given address
*
* @param
* client to get Level
* Level address to set
* @return
* client_NULL_PARAMETER if the given address is NULL
* client_ILLEGAL_PARAMETERS id client level has never been ILLEGAL
* else COMPANY_SUCCESS
*/
ClientResult clientGetLevel(Client client,Skill* skill_level);
#endif //HW3_WET_client_H