#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "EscapeTechnion.h"


#define NEW_START 0
#define TODAY 0
#define FIRST 0
#define EQUAL 0
#define MIN 0
#define MAX_HOUR 24
#define PRICE_FACTOR 4
#define UNUSED -1
#define CHAR2INT(e) ((e)-'0')
#define HOUR2INT(e, w) (((e)*10)+(w))
#define MIN_LEVEL 1
#define MAX_LEVEL 10
#define BEST 3


struct escapeTechnion_t {
    List all_faculty;
    Set all_company;
    Set all_clients;
    Day current_day;
    Revenue revenue;
};

/**
* check if given faculty id is valid
*
* @param
* id to check
* @return
* TRUE if given Id is in [0,UNKNOWN)
* else FALSE
*/
static inline bool validEmail(const Email email) {
    assert(email != NULL);
    char *c_ptr = email;
    int at_counter = 0;
    while (*c_ptr) {
        at_counter += *c_ptr == '@';
        c_ptr++;
    }
    return (at_counter == 1);
}

/**
* convert char[3] to int and return it
*
* @param
* Hour to convert
* @return
* the converted hour
*/
static inline int hour2int(Hour hour){
    int tens=CHAR2INT(hour[0]);
    int ones=CHAR2INT(hour[1]);
    return HOUR2INT(tens,ones);
}


/**
* search for escper by it's email
*
* @param
* email to search for
* @return
* pointer to the requested client
* else NULL if client email does NOT found
*/
static Client findClientByEmail(EscapeTechnion system, Email client_email) {
    assert(system != NULL);
    assert(client_email != NULL);
    assert(validEmail(client_email) == true);
    SET_FOREACH(Client, iterator,system->all_clients) {
        const Email current_email = clientGetEmailR(iterator);
        if (strcmp(current_email, client_email) == EQUAL) {
            return iterator;
        }
    }
    return NULL;
}

/**
* create all faculties object and insert them to list
*
* @param
* system to insert the faculties ti it's list
* @return
* TRUE success to create all exist faculties and insert them to list
* else FALSE
*/
static bool setAllFaculty(EscapeTechnion system) {
    system->all_faculty =listCreate(facultyCopy,facultyDestroy);
    if (!system->all_faculty) {
        return false;
    }
    for (int i = 0; i < UNKNOWN; i++) {
        Faculty temp = facultyCreate(i);
        ListResult res1 = listInsertFirst(system->all_faculty, temp);
        if (!temp || res1 == LIST_OUT_OF_MEMORY) {
            listDestroy(system->all_faculty);
            facultyDestroy(temp);
            return false;
        }
        facultyDestroy(temp);
        assert(res1 == LIST_SUCCESS);
    }
    assert(listGetSize(system->all_faculty) == UNKNOWN);
    return true;
}

EscapeTechnion systemCreate() {
    EscapeTechnion new_system = (EscapeTechnion) malloc(sizeof(*new_system));
    if (!new_system) {
        return NULL;
    }
    if (!setAllFaculty(new_system)) {
        free(new_system);
        return NULL;
    }
    new_system->all_company = setCreate(companyCopy, companyDestroy,
                                        companyCompare);
    if (!new_system->all_company) {
        listDestroy(new_system->all_faculty);
        free(new_system);
        return NULL;
    }
    new_system->all_clients = setCreate(clientCopy,clientDestroy,clientCompare);
    if (!new_system->all_clients) {
        listDestroy(new_system->all_faculty);
        setDestroy(new_system->all_company);
        free(new_system);
        return NULL;
    }
    new_system->revenue = NEW_START;
    new_system->current_day = NEW_START;
    return new_system;
}

void systemDestroy(EscapeTechnion system) {
    if (!system) {
        return;
    }
    listDestroy(system->all_faculty);
    setDestroy(system->all_company);
    setDestroy(system->all_clients);
    free(system);
}

/**
* create new company for the system with given email and faculty id
*
* @param
* pointer to export the new company
* company email to set
* faculty id to set
* @return
* SYSTEM_MEMORY_PROBLEM if allocation while creation fails
* SYSTEM_ILLEGAL_PARAMETER one of the given parameters are NOT valid
* SYSTEM_SUCCESS else
*/
static SystemResult buildNewCompany(Company *new_company, Email company_email,
                                    TechnionFaculty faculty_id) {
    assert(new_company != NULL);
    assert(*new_company == NULL);
    *new_company = companyCreate();
    if (!(*new_company)) {
        return SYSTEM_MEMORY_PROBLEM;
    }
    CompanyResult res1 = companySetEmail(*new_company, company_email);
    if(res1==COMPANY_ILLEGAL_PARAMETERS){
        companyDestroy(*new_company);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    if (res1 == COMPANY_MEMORY_PROBLEM) {
        companyDestroy(*new_company);
        return SYSTEM_MEMORY_PROBLEM;
    }
    assert(res1 == COMPANY_SUCCESS);
    res1 = companySetFaculty(*new_company, faculty_id);
    if(res1==COMPANY_ILLEGAL_PARAMETERS){
        companyDestroy(*new_company);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    assert(res1 == COMPANY_SUCCESS);
    return SYSTEM_SUCCESS;
}

SystemResult systemCompanyAdd(EscapeTechnion system, Email company_email,
                              TechnionFaculty faculty_id) {
    assert(system != NULL);
    Company new_company = NULL;
    SystemResult res1 = buildNewCompany(&new_company, company_email,faculty_id);
    if (res1 != SYSTEM_SUCCESS){
        return res1;
    }
    assert(res1==SYSTEM_SUCCESS);
    if (setIsIn(system->all_company, new_company)
        || findClientByEmail(system, company_email)) {
        companyDestroy(new_company);
        return SYSTEM_EMAIL_ALREADY_EXIST;
    }
    if (setAdd(system->all_company, new_company) == SET_OUT_OF_MEMORY) {
        companyDestroy(new_company);
        return SYSTEM_MEMORY_PROBLEM;
    }
    companyDestroy(new_company);
    return SYSTEM_SUCCESS;
}
/**
* create new room for the system with given parameters
*
* @param
* pointer to export the new room
* company to take email from
* room id to set
* room price to set
* number of people to set
* open hour to set
* close hour to set
* room level to set
* @return
* SYSTEM_MEMORY_PROBLEM if allocation while creation fails
* SYSTEM_ILLEGAL_PARAMETER one of the given parameters are NOT valid
* SYSTEM_SUCCESS else
*/
static SystemResult buildNewRoom(Room *new_room, Company temp,Room_Id room_id,
                                 Room_Price room_price, Occapancy room_people,
                                 Hour open, Hour close, Difficulty room_level){
    assert(new_room != NULL);
    assert(*new_room == NULL);
    *new_room = roomCreate();
    if (!(*new_room)) {
        return SYSTEM_MEMORY_PROBLEM;
    }
    RoomResult res1 = roomSetEmailFromCompany(*new_room, temp);
    if (res1 != ROOM_SUCCESS) {
        roomDestroy(*new_room);
        return SYSTEM_MEMORY_PROBLEM;
    }
    assert(res1 == ROOM_SUCCESS);
    res1=roomSetId(*new_room, room_id);
    if(res1==ROOM_ILLEGAL_PARAMETERS){
        roomDestroy(*new_room);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    assert(res1 == ROOM_SUCCESS);
    res1=roomSetPrice(*new_room, room_price);
    if(res1==ROOM_ILLEGAL_PARAMETERS){
        roomDestroy(*new_room);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    assert(res1 == ROOM_SUCCESS);
    res1=roomSetNumPeople(*new_room, room_people);
    if(res1==ROOM_ILLEGAL_PARAMETERS){
        roomDestroy(*new_room);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    assert(res1 == ROOM_SUCCESS);
    Time room_open=hour2int(open);
    Time room_close=hour2int(close);
    res1=roomSetWorkingHours(*new_room, room_open, room_close);
    if(res1==ROOM_ILLEGAL_PARAMETERS){
        roomDestroy(*new_room);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    assert(res1 == ROOM_SUCCESS);
    res1=roomSetLevel(*new_room, room_level);
    if(res1==ROOM_ILLEGAL_PARAMETERS){
        roomDestroy(*new_room);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    assert(res1 == ROOM_SUCCESS);
    return SYSTEM_SUCCESS;
}

/**
* search for specific faculty by company email
*
* @param
* system to search in
* email of company to search for
* @return
* valid id if exists company with that email
* else UNKNOWN
*/
static TechnionFaculty
findFacultyIDByEmail(EscapeTechnion system, const Email to_find) {
    SET_FOREACH(Company, iterator, system->all_company) {
        const Email current_email = companyGetEmailR(iterator);
        if (strcmp(current_email, to_find) == EQUAL) {
            TechnionFaculty requested_id = UNKNOWN;
#ifndef NDEBUG
            CompanyResult res2 =
#endif
                    companyGetFaculty(iterator, &requested_id);
            assert(res2 == COMPANY_SUCCESS && requested_id != UNKNOWN);
            return requested_id;
        }
    }
    return UNKNOWN;
}

/**
* search for specific faculty by id
*
* @param
* system to search in
* id of faculty to search for
* @return
* return pointer to faculty
* NULL - when not found
*/
static Faculty findFacultyById(EscapeTechnion system, TechnionFaculty id) {
    LIST_FOREACH(Faculty, iterator, system->all_faculty) {
        TechnionFaculty current_id = UNKNOWN;
#ifndef NDEBUG
        FacultyResult res3 =
#endif
                facultyGetID(iterator, &current_id);
        assert(res3 == FACULTY_SUCCESS);
        if (current_id == id) {
            return iterator;
        }
    }
    return NULL;
}

SystemResult systemRoomAdd(EscapeTechnion system, Email company_email,Room_Id
room_id,Cost room_price,Occapancy room_people, Hour open, Hour close,
                           Difficulty room_level) {
    assert(system != NULL);
    Company temp = NULL;
    SystemResult res1 = buildNewCompany(&temp, company_email, FIRST);
    //build fictive company just to confirm company with that email is exist
    if (res1 != SYSTEM_SUCCESS){
        return res1;
    }
    assert(res1==SYSTEM_SUCCESS);
    Room new_room = NULL;
    res1 = buildNewRoom(&new_room, temp, room_id, room_price, room_people, open,
                        close, room_level);
    if (res1 != SYSTEM_SUCCESS) {
        companyDestroy(temp);
        return res1;
    }
    assert(res1==SYSTEM_SUCCESS);
    if (!setIsIn(system->all_company,temp)){
        companyDestroy(temp);
        roomDestroy(new_room);
        return SYSTEM_COMPANY_EMAIL_NOT_EXIST;
    }
    companyDestroy(temp);
    TechnionFaculty requested_id=findFacultyIDByEmail(system,company_email);
    Faculty requested_faculty = findFacultyById(system, requested_id);
    assert(requested_faculty != NULL);
    FacultyResult res3 = facultyAddRoom(requested_faculty, new_room);
    if (res3 == FACULTY_ROOM_ALREADY_IN) {
        roomDestroy(new_room);
        return SYSTEM_ROOM_ID_ALREADY_EXIST;
    }
    if (res3 == FACULTY_MEMORY_PROBLEM) {
        roomDestroy(new_room);
        return SYSTEM_MEMORY_PROBLEM;
    }
    roomDestroy(new_room);
    return SYSTEM_SUCCESS;
}

SystemResult systemCompanyRemove(EscapeTechnion system, Email company_email) {
    assert(system != NULL);
    Company temp = NULL;
    SystemResult res1 = buildNewCompany(&temp, company_email, FIRST);
    //build fictive company just to confirm company with that email is exist
    if (res1 !=SYSTEM_SUCCESS) {
        return res1;
    }
    assert(res1==SYSTEM_SUCCESS);
    TechnionFaculty requested_id = findFacultyIDByEmail(system, company_email);
    if (requested_id == UNKNOWN) {
        companyDestroy(temp);
        return SYSTEM_COMPANY_EMAIL_NOT_EXIST;
    }
    Faculty requested_faculty = findFacultyById(system, requested_id);
    assert(requested_faculty != NULL);
    FacultyResult res2 = facultyRemoveCompanyRooms(requested_faculty,
                                                   company_email);
    if (res2 == FACULTY_COMPANY_CANNOT_REMOVED) {
        companyDestroy(temp);
        return SYSTEM_RESERVATION_EXIST;
    }
#ifndef NDEBUG
    SetResult res3 =
#endif
            setRemove(system->all_company, temp);
    assert(res3 == SET_SUCCESS);
    companyDestroy(temp);
    return SYSTEM_SUCCESS;
}

SystemResult systemRoomRemove(EscapeTechnion system, TechnionFaculty
faculty_id, Room_Id room_id) {
    assert(system != NULL);
    Faculty requested_faculty = findFacultyById(system, faculty_id);
    if(requested_faculty==NULL){
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    assert(requested_faculty != NULL);
    FacultyResult res1 = facultyRemoveRoom(requested_faculty, room_id);
    if(res1==FACULTY_ILLEGAL_PARAMETERS){
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    if (res1 == FACULTY_ROOM_NOT_EXIST) {
        return SYSTEM_ROOM_ID_NOT_EXIST;
    }
    if (res1 == FACULTY_ROOM_CANNOT_REMOVED) {
        return SYSTEM_RESERVATION_EXIST;
    }
    assert(res1 == FACULTY_SUCCESS);
    return SYSTEM_SUCCESS;
}

/**
* create new client for the system with given parameters
*
* @param
* pointer to export the new room
* client email to set
* faculty id to set
* client level to set
* @return
* SYSTEM_MEMORY_PROBLEM if allocation while creation fails
* SYSTEM_ILLEGAL_PARAMETER one of the given parameters are NOT valid
* SYSTEM_SUCCESS else
*/static SystemResult buildNewClient(Client *new_client, Email client_email,
                            TechnionFaculty faculty_id,Skill skill_level){
    assert(new_client != NULL);
    assert((*new_client) == NULL);
    *new_client = clientCreate();
    if (!(*new_client)) {
        return SYSTEM_MEMORY_PROBLEM;
    }
    ClientResult res1 = clientSetEmail(*new_client, client_email);
    if(res1==CLIENT_ILLEGAL_PARAMETERS){
        clientDestroy(*new_client);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    if (res1 == CLIENT_MEMORY_PROBLEM) {
        clientDestroy(*new_client);
        return SYSTEM_MEMORY_PROBLEM;
    }
    assert(res1 == CLIENT_SUCCESS);
    res1 = clientSetLevel(*new_client, skill_level);
    if(res1==CLIENT_ILLEGAL_PARAMETERS){
        clientDestroy(*new_client);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    assert(res1 == CLIENT_SUCCESS);
    res1 = clientSetFaculty(*new_client, faculty_id);
    if(res1==CLIENT_ILLEGAL_PARAMETERS){
        clientDestroy(*new_client);
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    assert(res1 == CLIENT_SUCCESS);
    return SYSTEM_SUCCESS;
}

SystemResult systemClientAdd(EscapeTechnion system, Email client_email,
                              TechnionFaculty faculty_id,Difficulty skill_level){
    assert(system != NULL);
    Client new_client = NULL;
    SystemResult res1 = buildNewClient(&new_client, client_email, faculty_id,
                                        skill_level);
    if (res1 != SYSTEM_SUCCESS) {
        return res1;
    }
    assert(res1==SYSTEM_SUCCESS);
    if(setIsIn(system->all_clients,new_client)
       ||findFacultyIDByEmail(system,client_email)!=UNKNOWN){
        //when find faculty by email <=> company with that email exists
        clientDestroy(new_client);
        return SYSTEM_EMAIL_ALREADY_EXIST;
    }
    SetResult res3 = setAdd(system->all_clients, new_client);
    if(res3==SET_OUT_OF_MEMORY){
        clientDestroy(new_client);
        return SYSTEM_MEMORY_PROBLEM;
    }
    assert(res3 == SET_SUCCESS);
    clientDestroy(new_client);
    return SYSTEM_SUCCESS;
}

SystemResult systemClientRemove(EscapeTechnion system, Email client_email) {
    assert(system != NULL);
    if (!validEmail(client_email)) {
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    Client to_delete = findClientByEmail(system, client_email);
    if (to_delete == NULL) {
        return SYSTEM_CLIENT_EMAIL_NOT_EXIST;
    }
    LIST_FOREACH(Faculty, iterator, system->all_faculty) {
#ifndef NDEBUG
        FacultyResult res1 =
#endif
                facultyRemoveOrdersOfClient(iterator, to_delete);
        assert(res1 == FACULTY_SUCCESS);
    }
#ifndef NDEBUG
    SetResult res2 =
#endif
            setRemove(system->all_clients, to_delete);
    assert(res2 == SET_SUCCESS);
    return SYSTEM_SUCCESS;
}

SystemResult systemGetDay(EscapeTechnion system, Day *day) {
    assert(system != NULL);
    if (!day) {
        return SYSTEM_NULL_PARAMETER;
    }
    assert(system->current_day >= NEW_START);
    *day = system->current_day;
    return SYSTEM_SUCCESS;
}

SystemResult systemGetRevenue(EscapeTechnion system, Revenue* revenue) {
    assert(system != NULL);
    if (!revenue) {
        return SYSTEM_NULL_PARAMETER;
    }
    assert(system->revenue >= NEW_START);
    *revenue = system->revenue;
    return SYSTEM_SUCCESS;
}
/**
* check if client has already an order in the same hour for another room
*
* @param
* system to get it's faculties
* Client client to check for it
* Day to compare with the exist orders
* Hour to compare with exist orders
* @return
* TRUE when escape can order for that time
* FALSE when order has an order to that time
*/
static bool clientCanSetOrder(EscapeTechnion system, Client client, Day day, Time time) {
    assert(system != NULL);
    assert(client != NULL);
    LIST_FOREACH(Faculty, iterator, system->all_faculty) {
        FacultyResult res1=facultyClientCanSetOrder(iterator, client, day, time);
        if (res1==FACULTY_ORDER_CANNOT_SET)
            return false;
        assert(res1==FACULTY_SUCCESS);
    }
    return true;
}

SystemResult systemClientOrder(EscapeTechnion system, Email client_email,
                                TechnionFaculty faculty_id,Room_Id room_id,
                               Day day,Time time,Occapancy num_people){
    assert(system != NULL);
    Faculty requested_faculty = findFacultyById(system, faculty_id);
    if(!validEmail(client_email)||!orderValidTime(time,day)||
            !roomValidNumPeople(num_people)||!roomValidId(room_id)
       ||!facultyValidId(faculty_id)){
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    Client client = findClientByEmail(system, client_email);
    if (!client) {
        return SYSTEM_CLIENT_EMAIL_NOT_EXIST;
    }
    if (!facultyRoomIdExist(requested_faculty, room_id)) {
        return SYSTEM_ROOM_ID_NOT_EXIST;
    }
    if (!clientCanSetOrder(system, client, day, time)) {
        return SYSTEM_CLIENT_IN_ROOM;
    }
    FacultyResult res1 = facultyAddOrder(requested_faculty, client, room_id,
                                         day, time, num_people);
    if(res1==FACULTY_MEMORY_PROBLEM){
        return SYSTEM_MEMORY_PROBLEM;
    }
    if(res1==FACULTY_ORDER_CANNOT_SET){
        return SYSTEM_ROOM_NOT_AVAILABLE;
    }
    assert(res1==FACULTY_SUCCESS);
    return SYSTEM_SUCCESS;
}

/**
* gets to faculties id and return the distance between them
*
* @param
* id1 to calculating with
* id2 to calculating with
* @return
* the distance in abs between the ids
*/
static inline int absId(TechnionFaculty id1, TechnionFaculty id2){
    return (id1>id2) ? (id1-id2) : (id2-id1);
}



/**
* check if current recommended room for client need to be changed
*
* @param
* min_rank current min rank to compare with
* current_rank to compare with
* client_faculty to compare with (refernce point)
* current_faculty_id to compare with
* win_faculty_id to compare with
* @return
* TRUE when the best faculty id need to be change
* FALSE else
*/
static bool filterRecommendedRoom(Rank min_rank,Rank current_rank,
        TechnionFaculty client_faculty,TechnionFaculty current_faculty_id,
                                  TechnionFaculty win_faculty_id) {
    if (min_rank == UNUSED || current_rank < min_rank) {
        return true;
    }
    assert(win_faculty_id != UNKNOWN);
    if (min_rank == current_rank) {
        if (absId(client_faculty,current_faculty_id)
            <absId(client_faculty,win_faculty_id)){
            return true;
        }
        if (absId(client_faculty, current_faculty_id) ==
                    absId(client_faculty, win_faculty_id) &&
            current_faculty_id < win_faculty_id) {
            return true;
        }
        assert(absId(client_faculty, current_faculty_id) >
                       absId(client_faculty, win_faculty_id));
        return false;
    }
    assert(current_rank > min_rank);
    return false;
}

/**
* finding the faculty that holds the most recommended room for this client
*
* @param
* system to gets it's faculties
* client to gets it's parameters
* num_people to order for
* *win_faculty to export the faculty that holds the recommended room
* @return
* SYSTEM_NO_ROOMS_AVAILABLE when there is noo rooms at all
* SYSTEM_SUCCESS find recommended room in some faculty
*/
static SystemResult findRecommendedRoom(EscapeTechnion system, Client client,
                                        Occapancy num_people,Faculty *win_faculty){
    assert(win_faculty != NULL);
    assert(*win_faculty == NULL);
    TechnionFaculty client_faculty;
#ifndef NDEBUG
    ClientResult res1 =
#endif
            clientGetFaculty(client, &client_faculty);
    assert(res1 == CLIENT_SUCCESS);
    TechnionFaculty win_faculty_id = UNKNOWN;
    Rank min_rank = UNUSED;
    LIST_FOREACH(Faculty, iterator, system->all_faculty) {
        Rank current_rank;
        Room_Id current_id;//only fo function
        FacultyResult res2 = facultyGetRecommendedRoom
                (iterator, client, num_people, &current_rank, &current_id);
        if (res2 == FACULTY_ROOM_NOT_EXIST) {
            continue;
        }
        assert(res2 == FACULTY_SUCCESS);
        TechnionFaculty current_faculty_id;
        res2 = facultyGetID(iterator, &current_faculty_id);
        assert(res2 == FACULTY_SUCCESS);
        if(filterRecommendedRoom(min_rank,current_rank,client_faculty,current_faculty_id,win_faculty_id)){
            min_rank=current_rank;
            win_faculty_id=current_faculty_id;
            *win_faculty=iterator;
        }
    }
    if (min_rank == UNUSED){
        return SYSTEM_NO_ROOMS_AVAILABLE;
    }
    return SYSTEM_SUCCESS;
}

SystemResult systemClientRecommend(EscapeTechnion system, Email
client_email, Occapancy num_people){
    assert(system!=NULL);
    if(!validEmail(client_email)||!roomValidNumPeople(num_people)){
        return SYSTEM_ILLEGAL_PARAMETER;
    }
    Client client= findClientByEmail(system, client_email);
    if(!client){
        return SYSTEM_CLIENT_EMAIL_NOT_EXIST;
    }
    Faculty win_faculty=NULL;
    if(findRecommendedRoom(system, client, num_people, &win_faculty)
       ==SYSTEM_NO_ROOMS_AVAILABLE){
        return SYSTEM_NO_ROOMS_AVAILABLE;
    }
    assert(win_faculty!=NULL);
    FacultyResult res3=
            facultyOrderRecommendedRoom(win_faculty,client,num_people);
    if(res3==FACULTY_MEMORY_PROBLEM){
        return SYSTEM_MEMORY_PROBLEM;
    }
    assert(res3==FACULTY_SUCCESS);
    return SYSTEM_SUCCESS;
}

/**
* gets 2 lists and chain then to each others
*
* @param
* add_to_me chain the other list to this one
* get_from_me chain this list to the other one
* @return
* SYSTEM_MEMORY_PROBLEM when allocation fails
* SYSTEM_SUCCESS else
*/
static SystemResult chain2OrderList(List add_to_me, List get_from_me){
    assert(add_to_me!=NULL&&get_from_me!=NULL);
    LIST_FOREACH(Order,iterator,get_from_me){
        if(listInsertFirst(add_to_me,iterator)==LIST_OUT_OF_MEMORY){
            return SYSTEM_MEMORY_PROBLEM;
        }
    }
    return SYSTEM_SUCCESS;
}

SystemResult systemReportDay(EscapeTechnion system, List *today_order){
    assert(system!=NULL);
    if(!today_order){
        return SYSTEM_NULL_PARAMETER;
    }
    assert(*today_order==NULL);
    *today_order=listCreate(orderCopy,orderDestroy);
    if(!(*today_order)){
        return SYSTEM_MEMORY_PROBLEM;
    }
    LIST_FOREACH(Faculty,iterator,system->all_faculty){
        Revenue current_revenue=0;
        List today_faculty_order=NULL;
      FacultyResult res1=
              facultyEndOfDay(iterator,&current_revenue,&today_faculty_order);
        if(res1==FACULTY_MEMORY_PROBLEM){
            listDestroy(*today_order);
            *today_order=NULL;
            return SYSTEM_MEMORY_PROBLEM;
        }
        if(chain2OrderList(*today_order, today_faculty_order)==SYSTEM_MEMORY_PROBLEM){
            listDestroy(today_faculty_order);
            listDestroy(*today_order);
            *today_order=NULL;
            return SYSTEM_MEMORY_PROBLEM;
        }
        listDestroy(today_faculty_order);
        system->revenue+=current_revenue;
    }
    system->current_day++;
    ListResult res2=listSort(*today_order,orderCompare);
    if(res2==LIST_OUT_OF_MEMORY){
        listDestroy(*today_order);
        *today_order=NULL;
        return SYSTEM_MEMORY_PROBLEM;
    }
    return SYSTEM_SUCCESS;
}


SystemResult systemReportBest(EscapeTechnion system, List*best) {
    assert(system != NULL);
    assert(system->all_faculty!=NULL);
    if(!best){
        return SYSTEM_NULL_PARAMETER;
    }
    assert((*best)==NULL);
    if(listSort(system->all_faculty,facultyCompareByRevAndID)==LIST_OUT_OF_MEMORY){
        return SYSTEM_MEMORY_PROBLEM;
    }
    *best=listCreate(facultyCopy,facultyDestroy);
    if(!(*best)){
        return SYSTEM_MEMORY_PROBLEM;
    }
    Faculty iterator=listGetFirst(system->all_faculty);
    for(int i=0;i<BEST&&iterator;i++){
        if(listInsertLast(*best,iterator)==LIST_OUT_OF_MEMORY){
            listDestroy(*best);
            best=NULL;
            return SYSTEM_NULL_PARAMETER;
        }
        iterator=listGetNext(system->all_faculty);
    }
    return SYSTEM_SUCCESS;
}