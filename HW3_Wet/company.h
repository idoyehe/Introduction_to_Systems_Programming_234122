#ifndef HW3_WET_COMPANY_H
#define HW3_WET_COMPANY_H

#include "mtm_ex3.h"
#include "set.h"

/**
* Company data type
*
*This data type is for companies save the the company email and faculty
*
* The following functions are available:
*
*   companyCreate            - Creates a new company struct
*   companyDestroy           - Free an existing company and frees all
*                              resources
*   companyCopy              - Copies an existing company
*   companySetEmail          - set an Email for company
*   roomGetEmailR            - Exporting to const char* the company's email
*   companySetFaculty        - set a faculty for company
*   companyGetFaculty        - Exporting to int* the company's Faculty
*   companyCompare           - compare between 2 companies' Email
*/

/** Type for defining the company */
typedef enum companyResult {COMPANY_SUCCESS,COMPANY_NULL_PARAMETER,
    COMPANY_MEMORY_PROBLEM,COMPANY_ILLEGAL_PARAMETERS} CompanyResult;

/*For client and company email*/
typedef char* Email;

typedef struct company_t* Company;

/*
* Allocates a new Company object
*
* Creates a new empty company.
* This function used by the functions which will be used for copying company.
* @return
* 	NULL - if allocations failed.
* 	A new Company in case of success.
*/
Company companyCreate();

/**
* setting the company Email
*
* creating new copy of the given Email and setting the company Email as the copy
*
* @param
* Company to set Email
* Email to set
* @return
* COMPANY_NULL_PARAMETER if the given Email is NULL
* COMPANY_ILLEGAL_PARAMETERS if given email is ILLEGAL
* COMPANY_MEMORY_PROBLEM if the allocation for copy failed
* else COMPANY_SUCCESS
*/
CompanyResult companySetEmail(Company company,const Email email);

/**
* setting the company ID
*
* @param
* Company to set ID
* ID to set
* @return
* COMPANY_ILLEGAL_PARAMETERS if given Id is ILLEGAL
* else COMPANY_SUCCESS
*/
CompanyResult companySetFaculty(Company company, TechnionFaculty id);

/**
* getting the company Email by reference
*
* exporting the address in heap of company Email to const char*
*
* @param
* company to get Email
* @return
* NULL- if company Email has NEVER been set
* const char* with email of the room
*/
const Email companyGetEmailR(Company company);

/**
* getting the company faculty Id
*
* exporting the company faculty ID to given address
*
* @param
* Company to get ID
* ID address to set the ID
* @return
* COMPANY_NULL_PARAMETER if the given address is NULL
* COMPANY_ILLEGAL_PARAMETERS if company faculty has NEVER been set
* else COMPANY_SUCCESS
*/
CompanyResult companyGetFaculty(Company company, TechnionFaculty *output_id);


/**
* creating a copy of given company with the same Email and ID
* creating new copy of the company and export it used for set
*
*
* @param
* Company to copy
* @return
* NULL if the allocation for copy failed or if not all parameters has been set
* else the copy
*/
SetElement companyCopy(SetElement company_element);


/**
* destroying the given company and deallocate memory, such as Email.
* @param
* Company to destroy
* @return
* void function
*/
void companyDestroy(SetElement company_element);

/**
* Type of function used by the set to identify equal companies by their emails.
* This function will be used to deciding the iteration order of the set.
* @param
* Two companies elements
* @return
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/
int companyCompare(SetElement company_element1, SetElement company_element2);

#endif //HW3_WET_COMPANY_H