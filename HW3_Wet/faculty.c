#include "faculty.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define NEW_DAY 0
#define MIN_ID 1
#define MIN_PEOPLE 1
#define TODAY 0
#define MIN 0
#define FIRST_BIGGER 1
#define SECOND_BIGGER -1
#define EQUAL 0
#define MAX_HOUR 23
#define FIRST 0

struct faculty_t{
    TechnionFaculty id;
    Set all_rooms;
    List all_orders;
    Revenue total_revenue;
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
* check if given time is valid
*
* @param
* time to check
* @return
* TRUE if given time is in [0,23]
* else FALSE
*/
static inline bool validTime(Time time) {
    return time<=MAX_HOUR&&time>=MIN;
}

inline bool facultyValidId(TechnionFaculty id){
    return (id>=FIRST)&&(id<UNKNOWN);
}

/**
* search for specific room by it's id
*
* @param
* room id to search for
* @return
* pointer to the requested room
* else NULL if room id does NOT found
*/
static Room findRoomById(Faculty faculty,Room_Id id){
    SET_FOREACH(Room, iterator, faculty->all_rooms) {
        Room_Id current_id;
#ifndef NDEBUG
        RoomResult res1 =
#endif
                roomGetId(iterator, &current_id);
        assert(res1 == ROOM_SUCCESS);
        if (current_id == id) {
            return iterator;
        }
    }
    return NULL;
}

Faculty facultyCreate(TechnionFaculty id){
    if(!facultyValidId(id)){
        return NULL;
    }
    Faculty new_faculty = (Faculty)malloc(sizeof(*new_faculty));
    if (!new_faculty){
        return NULL;
    }
    new_faculty->all_rooms=setCreate(roomCopy,roomDestroy,roomCompare);
    if (!new_faculty->all_rooms){
        free(new_faculty);
        return NULL;
    }
    new_faculty->all_orders=listCreate(orderCopy,orderDestroy);
    if(!new_faculty->all_orders){
        setDestroy(new_faculty->all_rooms);
        free(new_faculty);
        return NULL;
    }
    new_faculty->id=id;
    new_faculty->total_revenue=NEW_DAY;
    return new_faculty;
}

void facultyDestroy(ListElement faculty_element){
    if (!faculty_element){
        return;
    }
    Faculty faculty=(Faculty) faculty_element;
    listDestroy(faculty->all_orders);
    setDestroy(faculty->all_rooms);
    free(faculty);
    return;
}

bool facultyRoomIdExist(Faculty faculty, Room_Id id) {
    assert(faculty != NULL);
    assert(id >= MIN_ID);
    if(findRoomById(faculty,id)){
        return true;
    }
    return false;

}

FacultyResult facultyAddRoom(Faculty faculty,Room room){
    assert(faculty!=NULL);
    if(!room) {
        return FACULTY_NULL_PARAMETER;
    }
    SetResult res1=setAdd(faculty->all_rooms,room);
    if(res1==SET_OUT_OF_MEMORY){
        return FACULTY_MEMORY_PROBLEM;
    }
    if (res1==SET_ITEM_ALREADY_EXISTS){
        return FACULTY_ROOM_ALREADY_IN;
    }
    assert(res1==SET_SUCCESS);
    return FACULTY_SUCCESS;
}

/**
* check if room id can be removed from the set of rooms in the faculty
* ASSERTION the room id exists in the faculty
* @param
* room id to check
* @return
* TRUE if given room has no orders and can be removed
* else FALSE
*/
static bool roomCanBeRemoved(Faculty faculty,Room_Id id){
    assert(faculty!=NULL);
    assert(id>=MIN_ID);
    LIST_FOREACH(Order ,iterator,faculty->all_orders){
        Room current_room=NULL;
#ifndef NDEBUG
        OrderResult res1 =
#endif
                orderGetRoom(iterator, &current_room);//no allocation here
        assert(res1==ORDER_SUCCESS);
        Room_Id current_id;
#ifndef NDEBUG
      RoomResult  res2 =
#endif
        roomGetId(current_room,&current_id);
        assert(res2==ROOM_SUCCESS);
        if(current_id==id){
            return false;//found an order for the room
        }
    }
    return true;
}

FacultyResult facultyRemoveRoom(Faculty faculty,Room_Id id) {
    assert(faculty != NULL);
    if(!roomValidId(id)){
        return FACULTY_ILLEGAL_PARAMETERS;
    }
    if (!facultyRoomIdExist(faculty, id)) {
        return FACULTY_ROOM_NOT_EXIST;
    }
    if (!roomCanBeRemoved(faculty, id)) {
        return FACULTY_ROOM_CANNOT_REMOVED;
    }
    Room to_delete = findRoomById(faculty, id);
    assert(to_delete != NULL);
    setRemove(faculty->all_rooms, to_delete);
    return FACULTY_SUCCESS;
}

/**
* check if company's rooms can be removed from the set of rooms in the faculty
*
* @param
* room id to check
* @return
* TRUE if given company's rooms has no orders and can be removed
* else FALSE
*/
static bool companyCanRemove(Faculty faculty,Email company_email){
    assert(faculty!=NULL);
    assert(company_email!=NULL);
    SET_FOREACH(Room,iterator,faculty->all_rooms){
        const Email current_mail=roomGetEmailR(iterator);
        assert(current_mail!=NULL);
        if(!strcmp(current_mail,company_email)){//finding a room of the company
            Room_Id current_id;
#ifndef NDEBUG
            RoomResult res1 =
#endif
            roomGetId(iterator,&current_id);
            assert(res1==ROOM_SUCCESS);
            if(!roomCanBeRemoved(faculty,current_id)){
                return false;
            }
        }
    }
    return true;
}

FacultyResult facultyRemoveCompanyRooms(Faculty faculty,Email company_email) {
    assert(faculty != NULL);
    if (company_email == NULL) {
        return FACULTY_NULL_PARAMETER;
    }
    if(!validEmail(company_email)){
        return FACULTY_ILLEGAL_PARAMETERS;
    }
    if (!companyCanRemove(faculty, company_email)) {
        return FACULTY_COMPANY_CANNOT_REMOVED;
    }
    Room iterator=setGetFirst(faculty->all_rooms);
    while(iterator){
        const Email current_mail = roomGetEmailR(iterator);
        assert(current_mail != NULL);
        if (!strcmp(current_mail,company_email)) {
            //finding a room of the company
            Room to_delete = iterator;
            setRemove(faculty->all_rooms, to_delete);//iterator is invalid state
            iterator = setGetFirst(faculty->all_rooms);//restart iterator
        }
        else
            iterator=setGetNext(faculty->all_rooms);
    }
    return FACULTY_SUCCESS;
}

FacultyResult facultyClientCanSetOrder(Faculty faculty, Client escaper, Day day,
                                       Time hour_order) {
    assert(faculty!=NULL);
    if(!escaper){
        return FACULTY_NULL_PARAMETER;
    }
    if(day<TODAY||!validTime(hour_order)){
        return FACULTY_ILLEGAL_PARAMETERS;
    }
    LIST_FOREACH(Order,iterator,faculty->all_orders){
        Day current_days;
        Time current_order_hour;
#ifndef NDEBUG
        OrderResult res1 =
#endif
        orderGetTime(iterator,&current_days,&current_order_hour);
        assert(res1==ORDER_SUCCESS);
        Client current_escaper=NULL;
#ifndef NDEBUG
         res1 =
#endif
        orderGetClient(iterator,&current_escaper);
        //no allocation here
        assert(res1==ORDER_SUCCESS);
        if(escaper==current_escaper&&day==current_days&&
                hour_order==current_order_hour){
            return FACULTY_ORDER_CANNOT_SET;
        }
    }
    return FACULTY_SUCCESS;
}

/**
* check if room is available in given time
* @param
* room id to check
* time to check
* day to check
* @return
* TRUE if given rooms has no orders for that time
* else FALSE
*/
static  bool roomIsAvailable(Faculty faculty,Room_Id id,Day day, Time check_hour){
    assert(faculty!=NULL);
    assert(facultyRoomIdExist(faculty, id)==true);
    Room requested_room=findRoomById(faculty,id);
    assert(requested_room!=NULL);
    Time room_open,room_close;
#ifndef NDEBUG
    RoomResult res1 =
#endif
    roomGetWorkingHours(requested_room,&room_open,&room_close);
    assert(res1==ROOM_SUCCESS);
    if(check_hour>=room_close||check_hour<room_open){
        //check if check_hour is in working hour
        return false;
    }
    LIST_FOREACH(Order ,iterator,faculty->all_orders){
        Room current_room=NULL;
#ifndef NDEBUG
        OrderResult res2=
#endif
                orderGetRoom(iterator, &current_room);
        //no allocation here
        assert(res2==ORDER_SUCCESS);
        if(current_room==requested_room){//find order to requested room
            Day order_day;
            Time order_time;
#ifndef NDEBUG
            res2=
#endif
            orderGetTime(iterator,&order_day,&order_time);
            assert(res2==ORDER_SUCCESS);
            if(order_day==day&&order_time==check_hour){
                //check if order set to the requested check_hour
                return false;
            }
        }
    }
    return true;
}

FacultyResult facultyAddOrder(Faculty faculty, Client escaper, Room_Id id, Day
                                day, Time hour_order,Occapancy num_people){
    assert(faculty != NULL);
    if (!escaper) {
        return FACULTY_NULL_PARAMETER;
    }
    if(!roomValidId(id)||!orderValidTime(hour_order,day)
       ||!roomValidNumPeople(num_people)){
        return FACULTY_ILLEGAL_PARAMETERS;
    }
    if (!facultyRoomIdExist(faculty, id)) {
        return FACULTY_ROOM_NOT_EXIST;
    }
    assert(facultyClientCanSetOrder(faculty, escaper, day, hour_order)==FACULTY_SUCCESS);
    if (!roomIsAvailable(faculty, id, day, hour_order)) {
        return FACULTY_ORDER_CANNOT_SET;
    }
    Order new_order = orderCreate();
    if (!new_order) {
        return FACULTY_MEMORY_PROBLEM;
    }
    Room requested_room = findRoomById(faculty, id);
    assert(requested_room != NULL);
#ifndef NDEBUG
    OrderResult res1=
#endif
    orderSet(new_order,requested_room,escaper,
             faculty->id,num_people,day,hour_order);
    assert(res1 == ORDER_SUCCESS);
    ListResult res2 = listInsertFirst(faculty->all_orders, new_order);
    if (res2 != LIST_SUCCESS) {
        return FACULTY_MEMORY_PROBLEM;
    }
    orderDestroy(new_order);
    return FACULTY_SUCCESS;
}

FacultyResult facultyRemoveOrdersOfClient(Faculty faculty, Client escaper){
    assert(faculty!=NULL);
    if(!escaper) {
        return FACULTY_NULL_PARAMETER;
    }
    Order iterator=listGetFirst(faculty->all_orders);
    while(iterator){
        Client current_escaper=NULL;
#ifndef NDEBUG
        OrderResult res1=
#endif
        orderGetClient(iterator,&current_escaper);
        //no allocation here
        assert(res1==ORDER_SUCCESS);
        if(current_escaper==escaper) {
#ifndef NDEBUG
            ListResult res2 =
#endif
                    listRemoveCurrent(faculty->all_orders);
            assert(res2 == LIST_SUCCESS);
            iterator = listGetFirst(faculty->all_orders);
        }
        else
            iterator = listGetNext(faculty->all_orders);
    }
    return FACULTY_SUCCESS;
}

FacultyResult facultyGetRevenueDay(Faculty faculty,Revenue *revenue_of_today){
    assert(faculty != NULL);
    if (!revenue_of_today) {
        return FACULTY_NULL_PARAMETER;
    }
    Revenue sum_revenues=NEW_DAY;
    LIST_FOREACH(Order, iterator, faculty->all_orders) {
        Day current_order_day;
        Time time;//only for function
#ifndef NDEBUG
        OrderResult res1=
#endif
        orderGetTime(iterator,&current_order_day,&time);
        assert(res1==ORDER_SUCCESS);
        if(current_order_day==TODAY){
            Cost order_price;
#ifndef NDEBUG
            res1=
#endif
            orderGetPrice(iterator,&order_price);
            assert(res1==ORDER_SUCCESS);
            sum_revenues+=order_price;
        }
    }
    *revenue_of_today=sum_revenues;
    return FACULTY_SUCCESS;
}

FacultyResult facultyGetTotalRevenue(Faculty faculty, Revenue *revenue){
    assert(faculty!=NULL);
    if(!revenue){
        return FACULTY_NULL_PARAMETER;
    }
    assert(faculty->total_revenue>=NEW_DAY);
    *revenue=faculty->total_revenue;
    return FACULTY_SUCCESS;
}

/**
* updating the min rank of the recommended room of the faculty
*
* @param
* current_rank to compare with
* *min_rank the current min rank and a pointer to export it if makes change
* current_id to compare with
* *recommended_id the current recommended room and a pointer to export it
* @return
* void function
*/
static inline void updateRankandID(Rank current_rank,Room_Id current_id,Rank *min_rank,Room_Id *recommended_id){
    if (current_rank <= *min_rank) {
        if (current_rank < *min_rank) {
            *min_rank = current_rank;
            *recommended_id=current_id;
        }
        assert(current_rank == *min_rank);
        if (current_id < *recommended_id) {
            *recommended_id = current_id;
        }
    }
    return;
}

FacultyResult facultyGetRecommendedRoom(Faculty faculty, Client escaper,
                         Occapancy people, Rank *best_rank,Room_Id *room_id){
    assert(faculty != NULL);
    if (!escaper||!best_rank||!room_id) return FACULTY_NULL_PARAMETER;
    if(!roomValidNumPeople(people)) return FACULTY_ILLEGAL_PARAMETERS;
    assert(people >=MIN_PEOPLE);
    if(!setGetSize(faculty->all_rooms)){//check for exists rooms
        return FACULTY_ROOM_NOT_EXIST;
    }
    Room first = setGetFirst(faculty->all_rooms);
    Rank min_rank;
    Room_Id recommended_id;
#ifndef NDEBUG
    RoomResult res2 =
#endif
            roomClientRank(first,escaper, people, &min_rank);
    assert(res2 == ROOM_SUCCESS);
#ifndef NDEBUG
     res2 =
#endif
    roomGetId(first, &recommended_id);
    assert(res2 == ROOM_SUCCESS);
    SET_FOREACH(Room, iterator, faculty->all_rooms) {
        Rank current_rank;
        Room_Id current_id;
#ifndef NDEBUG
        res2 =
#endif
        roomClientRank(iterator, escaper, people, &current_rank);
        assert(res2 == ROOM_SUCCESS);
#ifndef NDEBUG
        res2 =
#endif
                roomGetId(iterator, &current_id);
        assert(res2 == ROOM_SUCCESS);
        updateRankandID(current_rank,current_id,&min_rank,&recommended_id);
    }
    *best_rank=min_rank;
    *room_id=recommended_id;
    return FACULTY_SUCCESS;
}

/**
* find the soon day and time asap that the room is available
*
* @param
* room id to check for
* *day to export the soon available day
* *time to export the soon available time
* @return
* void function
*/

static void findRoomAvailability(Faculty faculty,Room_Id room_id,Day*day,Time*time){
    assert(faculty!=NULL);
    Room room=findRoomById(faculty,room_id);
    assert(room!=NULL);
    Time room_open,room_close;
#ifndef NDEBUG
    RoomResult res1=
#endif
            roomGetWorkingHours(room,&room_open,&room_close);
    assert(res1==ROOM_SUCCESS);
    Day day_to_order=TODAY;
    Time time_to_order=room_open;
    while(!roomIsAvailable(faculty,room_id,day_to_order,time_to_order)){
        time_to_order++;
        if(time_to_order==room_close){
            time_to_order=room_open;//set for opening
            day_to_order++;//next day
        }
    }
    *day=day_to_order;
    *time=time_to_order;
    return;
}

FacultyResult facultyOrderRecommendedRoom(Faculty faculty, Client escaper,
                                          Occapancy num_people){
    assert(faculty!=NULL);
    if(!escaper){
        return FACULTY_NULL_PARAMETER;
    }
    Room_Id recommended_id;
    Rank best_rank;//only for function
#ifndef NDEBUG
    FacultyResult res1=
#endif
            facultyGetRecommendedRoom(faculty,escaper,num_people,&best_rank,&recommended_id);
    assert(res1==FACULTY_SUCCESS);
    Day best_day;
    Time best_time;
    findRoomAvailability(faculty,recommended_id,&best_day,&best_time);
    return facultyAddOrder
            (faculty,escaper,recommended_id,best_day,best_time,num_people);
}

/**
* remove from order list all today orders and advance the day fo others
*
* @param
* faculty to get today orders
* @return
* void function
*/
static void closeTodayOrdersandAdvanceDay(Faculty faculty) {
    assert(faculty != NULL);
    Order iterator1 = listGetFirst(faculty->all_orders);
    while(iterator1){
        Day order_day;
        Time order_time;//only for function
#ifndef NDEBUG
        OrderResult res1 =
#endif
                orderGetTime(iterator1, &order_day, &order_time);
        assert(res1 == ORDER_SUCCESS);
        if (order_day == TODAY) {
#ifndef NDEBUG
            ListResult res2 =
#endif
                    listRemoveCurrent(faculty->all_orders);
            assert(res2 == LIST_SUCCESS);
            iterator1 = listGetFirst(faculty->all_orders);
        }
        else
            iterator1 = listGetNext(faculty->all_orders);
    }
    LIST_FOREACH(Order, iterator2, faculty->all_orders) {
#ifndef NDEBUG
        OrderResult res1 =
#endif
                orderAdvanceDay(iterator2);
        assert(res1 == ORDER_SUCCESS);
    }
    return;
}

FacultyResult facultyEndOfDay(Faculty faculty,Revenue* revenue,List *today_order){
    assert(faculty != NULL);
    if (!revenue || !today_order) {
        return FACULTY_NULL_PARAMETER;
    }
    assert(*today_order == NULL);
    Day today=TODAY;
    *today_order = listFilter(faculty->all_orders, orderFilterDay, &today);
    if (!(*today_order)) {
        return FACULTY_MEMORY_PROBLEM;
    }
#ifndef NDEBUG
    FacultyResult res1=
#endif
            facultyGetRevenueDay(faculty,revenue);
    assert(res1==FACULTY_SUCCESS);
    faculty->total_revenue+=*revenue;
    closeTodayOrdersandAdvanceDay(faculty);
    return FACULTY_SUCCESS;
}

int facultyCompareByRevAndID(SetElement faculty1, SetElement faculty2){
    assert(faculty1!=NULL);
    assert(faculty2!=NULL);
    Faculty f1=(Faculty)faculty1;
    Faculty f2=(Faculty)faculty2;
    if(f1->id==f2->id){
        return EQUAL;
    }
    if(f1->total_revenue>f2->total_revenue){
        return SECOND_BIGGER;
    }
    if(f1->total_revenue==f2->total_revenue&&f1->id<f2->id){
        return SECOND_BIGGER;
    }
    return FIRST_BIGGER;
}
/**
* creating new faculty without allocating data structures
* USED ONLY FOR LIST COPY
 * @param
* @return
* new Faculty object
*/
static Faculty createForCopyList(){
    Faculty new_faculty = (Faculty)malloc(sizeof(*new_faculty));
    if (!new_faculty){
        return NULL;
    }
    new_faculty->all_rooms=NULL;
    new_faculty->all_orders=NULL;
    new_faculty->id=UNKNOWN;
    new_faculty->total_revenue=NEW_DAY;
    return new_faculty;
}

ListElement facultyCopy(ListElement faculty_to_copy){
    assert(faculty_to_copy!=NULL);
    Faculty copy_faculty= createForCopyList();
    if(!copy_faculty){
        return NULL;
    }
    Faculty faculty=(Faculty)faculty_to_copy;
    copy_faculty->id=faculty->id;
    copy_faculty->total_revenue=faculty->total_revenue;
    Set copy_room=setCopy(faculty->all_rooms);
    if(!copy_room){
        free(copy_faculty);
        return NULL;
    }
    List copy_orders=listCopy(faculty->all_orders);
    if(!copy_orders){
        setDestroy(copy_room);
        free(copy_faculty);
        return NULL;
    }
    copy_faculty->all_rooms=copy_room;
    copy_faculty->all_orders=copy_orders;
    return copy_faculty;
}

FacultyResult facultyGetID(Faculty faculty, TechnionFaculty *id){
    assert(faculty!=NULL);
    assert(faculty->id<UNKNOWN);
    if(!id){
        return FACULTY_NULL_PARAMETER;
    }
    *id=faculty->id;
    return FACULTY_SUCCESS;
}