#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "client.h"

#define STRLEN(e) strlen((e))+1
#define FIRST 0
#define MIN_LEVEL 1
#define MAX_LEVEL 10


struct client_t {
    Email email;
    TechnionFaculty faculty_id;
    Skill skill_level;
};

/**
* check if given Email is valid
*
* @param
* Email to check
* @return
* TRUE if given Email contains only 1 '@'
* else FALSE
*/
static inline bool validEmail(const Email email) {
    if(email==NULL) return false;
    char *c_ptr = email;
    int at_counter = 0;
    while (*c_ptr) {
        at_counter += *c_ptr == '@';
        c_ptr++;
    }
    return (at_counter == 1);
}

/**
* check if given faculty id is valid
*
* @param
* id to check
* @return
* TRUE if given Id is in [0,UNKNOWN)
* else FALSE
*/
static inline bool validFacultyId(TechnionFaculty id) {
    return (id >= FIRST) && (id < UNKNOWN);
}

/**
* check if given skill level is valid
*
* @param
* id to check
* @return
* TRUE if given level is in [1,10]
* else FALSE
*/
static inline bool validLevel(Skill skill_level) {
    return (skill_level <= MAX_LEVEL && skill_level >= MIN_LEVEL);
}

Client clientCreate() {
    Client new_client = (Client)malloc(sizeof(*new_client));
    if (!new_client) {
        return NULL;
    }
    new_client->email = NULL;
    new_client->faculty_id = UNKNOWN;
    new_client->skill_level = MIN_LEVEL;
    return new_client;
}

void clientDestroy(SetElement client_element) {
    if (!client_element) {
        return;
    }
    Client client=(Client)client_element;
    free(client->email);
    free(client);
}

ClientResult clientSetEmail(Client client, const Email email) {
    assert(client != NULL);
    if (!email) {
        return CLIENT_NULL_PARAMETER;
    }
    if (!validEmail(email)) {
        return CLIENT_ILLEGAL_PARAMETERS;
    }
    Email new_email = (Email) malloc(STRLEN(email));
    if (!new_email) {
        return CLIENT_MEMORY_PROBLEM;
    }
    free(client->email);
    client->email = strcpy(new_email, email);
    return CLIENT_SUCCESS;
}

ClientResult clientSetFaculty(Client client, TechnionFaculty id) {
    assert(client != NULL);
    if (!validFacultyId(id)){
        return CLIENT_ILLEGAL_PARAMETERS;
    }
    client->faculty_id = id;
    return CLIENT_SUCCESS;
}

ClientResult clientSetLevel(Client client, Skill level) {
    assert(client != NULL);
    if (!validLevel(level)) {
        return CLIENT_ILLEGAL_PARAMETERS;
    }
    client->skill_level = level;
    return CLIENT_SUCCESS;
}

const Email clientGetEmailR(Client client){
    assert(client != NULL);
    return client->email;
}

ClientResult clientGetFaculty(Client client, TechnionFaculty *output_id) {
    assert(client != NULL);
    if (!output_id) {
        return CLIENT_NULL_PARAMETER;
    }
    if (!validFacultyId(client->faculty_id)) {
        return CLIENT_ILLEGAL_PARAMETERS;
    }
    *output_id = client->faculty_id;
    return CLIENT_SUCCESS;
}

ClientResult clientGetLevel(Client client, Skill *level) {
    assert(client != NULL);
    if (!level) {
        return CLIENT_NULL_PARAMETER;
    }
    *level = client->skill_level;
    return CLIENT_SUCCESS;
}

SetElement clientCopy(SetElement client_element) {
    assert(client_element != NULL);
    Client client = (Client) client_element;
    if (!validEmail(clientGetEmailR(client))||
            !validFacultyId(client->faculty_id)){
        return NULL;
    }
    Client copy = clientCreate();
    if (!copy) {
        return NULL;
    }
    if (clientSetEmail(copy, clientGetEmailR(client))!= CLIENT_SUCCESS) {
        clientDestroy(copy);
        return NULL;
    }
    if (clientSetFaculty(copy, client->faculty_id) != CLIENT_SUCCESS) {
        clientDestroy(copy);
        return NULL;
    }
    if (clientSetLevel(copy, client->skill_level) != CLIENT_SUCCESS) {
        clientDestroy(copy);
        return NULL;
    }
    return copy;
}

int clientCompare(SetElement client_element1, SetElement client_element2) {
    assert(client_element1 != NULL);
    assert(client_element2 != NULL);
    Client client1 = (Client) client_element1;
    Client client2 = (Client) client_element2;
    assert(client1->email != NULL);
    assert(client2->email != NULL);
    return strcmp(client1->email, client2->email);
}