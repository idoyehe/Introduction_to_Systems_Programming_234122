#include <assert.h>
#include <stdlib.h>
#include "order.h"

#define UNUSED -1
#define FIRST 0
#define TODAY 0
#define FIRST_BIGGER 1
#define SECOND_BIGGER -1
#define EQUAL 0
#define DISCOUNT 0.75
#define MIN 0
#define PRICE_FACTOR 4
#define MAX_HOUR 23

struct order_t{
    Room ordered_room;
    Client ordered_client;
    Cost order_cost;
    Day days_to_order;
    Time time_of_order;
    Occapancy num_people;
    TechnionFaculty order_faculty;
};

/**
* check if given time is valid
*
* @param
* time to check
* @return
* TRUE if given time is in [0,23]
* else FALSE
*/
inline bool orderValidTime(Time time,Day days) {
    return time<=MAX_HOUR&&time>=MIN&&days>=TODAY;
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
static inline bool validFacultyId(TechnionFaculty id){
    return (id>=FIRST)&&(id<UNKNOWN);
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
static inline bool validPrice(Cost price){
    return (price>=PRICE_FACTOR)&&(!(price%PRICE_FACTOR));
}

/**
* check if given room id is valid
*
* @param
* room id to check
* @return
* TRUE if given id is positive
* else FALSE
*/
static inline bool validRoomId(Room_Id id){
    return id>MIN;
}

Order orderCreate(){
    Order new_order=(Order)malloc(sizeof(*new_order));
    if(!new_order){
        return NULL;
    }
    new_order->ordered_room=NULL;
    new_order->ordered_client=NULL;
    new_order->days_to_order=UNUSED;
    new_order->num_people=UNUSED;
    new_order->time_of_order=UNUSED;
    new_order->order_cost=UNUSED;
    new_order->order_faculty=UNKNOWN;
    return new_order;
}

/**
* caculatiang the price of the order
*
* @param
* Escaper for it's faculty id
* room for it's price
* facultyId that makes the order
* num people that making the order
* @return
* the total price of the order with OR without discount
*/
static inline int calculatingPrice(Client escaper,Room room,TechnionFaculty
faculty,Occapancy num_people){
    assert(escaper!=NULL&&room!=NULL&&faculty!=UNKNOWN);
    Room_Price room_price;
#ifndef NDEBUG
    RoomResult res1=
#endif
            roomGetPrice(room,&room_price);
    assert(res1==ROOM_SUCCESS);
    TechnionFaculty escaper_faculty;
#ifndef NDEBUG
    ClientResult res2=
#endif
            clientGetFaculty(escaper,&escaper_faculty);
    assert(res2==CLIENT_SUCCESS);
    Cost regular=num_people*room_price;
    Cost discount=(Cost)(DISCOUNT*room_price*num_people);
    return (escaper_faculty==faculty) ? discount : regular;
}

/**
* gets all order parameters ans return true <=> all of them are valid
*
* @param
* faculty_id the faculty the order take place
* day number od days to order
* time of the order
* num_people number of people of the order
* @return
* NULL if the allocation for copy failed
* else a new void* pointer
*/
static bool orderValidParams (TechnionFaculty faculty_id,Room room,Day days,
                       Time time,Occapancy num_people){
    if(room==NULL) return false;
    Room_Id room_id;
#ifndef NDEBUG
    RoomResult res1=
#endif
            roomGetId(room,&room_id);
    assert(res1==ROOM_SUCCESS);
    if(!validFacultyId(faculty_id)||!orderValidTime(time,days)||
            !roomValidNumPeople(num_people)||!roomValidId(room_id)){
        return false;
    }
    return true;
}

OrderResult orderSet(Order order,Room room,Client escaper,TechnionFaculty
faculty,Occapancy people,Day days_to_order,Time time_of_order){
    assert(order!=NULL);
    if(!room||!escaper){
        return ORDER_NULL_PARAMETER;
    }
    if(!orderValidParams(faculty,room,days_to_order, time_of_order, people)){
        return ORDER_ILLEGAL_PARAMETERS;
    }
    order->order_faculty=faculty;
    order->ordered_room=room;
    order->ordered_client=escaper;
    order->days_to_order=days_to_order;
    order->time_of_order=time_of_order;
    order->num_people=people;
    order->order_cost=calculatingPrice(escaper,room,faculty,people);
    return ORDER_SUCCESS;
}

void orderDestroy(ListElement order){
    free(order);
    return;
}

ListElement orderCopy(ListElement order_element){
    if(!order_element){
        return NULL;
    }
    Order order=(Order)order_element;
    if(!orderValidParams(order->order_faculty,order->ordered_room,
           order->days_to_order,order->time_of_order,order->num_people)){
        return NULL;
    }
    Order order_copy=orderCreate();
    if(!order_copy){
        return NULL;
    }
#ifndef NDEBUG
    OrderResult result=
#endif
            orderSet(order_copy,order->ordered_room,
                                order->ordered_client,order->order_faculty,
                                order->num_people,order->days_to_order,
                                order->time_of_order);
    assert(result==ORDER_SUCCESS);
    return order_copy;
}

OrderResult orderGetRoom(Order order,Room* room){
    assert(order!=NULL);
    if(!room||!(order->ordered_room)){
        return ORDER_NULL_PARAMETER;
    }
    assert(*room==NULL);
    *room=order->ordered_room;
    return ORDER_SUCCESS;
}

OrderResult orderGetClient(Order order, Client* escaper){
    assert(order!=NULL);
    if(!escaper||(!order->ordered_client)){
        return ORDER_NULL_PARAMETER;
    }
    assert(*escaper==NULL);
    *escaper=order->ordered_client;
    return ORDER_SUCCESS;
}

OrderResult orderGetPrice(Order order,Cost* price){
    assert(order!=NULL);
    if(!price){
        return ORDER_NULL_PARAMETER;
    }
    *price=order->order_cost;
    return ORDER_SUCCESS;
}

OrderResult orderGetTime(Order order,Day* days,Time* hour){
    assert(order!=NULL);
    if(!days||!hour){
        return ORDER_NULL_PARAMETER;
    }
    if(!orderValidTime(order->time_of_order,order->days_to_order)){
        return ORDER_ILLEGAL_PARAMETERS;
    }
    *days=order->days_to_order;
    *hour=order->time_of_order;
    return ORDER_SUCCESS;
}

/**
* Type of function used by comparing function to compare two order
* only by their order time.
*
* @param
* Two orders elements
* @return
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/
static inline int compareByTime(Order order1,Order order2){
    Day order1_days,order2_days;
    Time order1_time,order2_time;
#ifndef NDEBUG
    OrderResult res1=
#endif
            orderGetTime(order1,&order1_days,&order1_time);
#ifndef NDEBUG
    OrderResult res2=
#endif
            orderGetTime(order2,&order2_days,&order2_time);
    assert(res1==ORDER_SUCCESS&&res2==ORDER_SUCCESS);
    if(order1_days>order2_days) return FIRST_BIGGER;
    if (order1_days < order2_days) return SECOND_BIGGER;
    assert(order1_days==order2_days);
    if(order1_time>order2_time) return FIRST_BIGGER;
    if(order1_time<order2_time) return SECOND_BIGGER;
    assert(order1_time==order2_time);
    return EQUAL;
}

/**
* Type of function used by comparing function to compare two order
* only by their faculty id.
*
* @param
* Two orders elements
* @return
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/
static inline int compareByFaculty(Order order1,Order order2){
    return order1->order_faculty-order2->order_faculty;
}

/**
* Type of function used by comparing function to compare two order
* only by their order room id
*
* @param
* Two orders elements
* @return
* 		A positive integer if the first element is greater;
* 		0 if they're equal;
*		A negative integer if the second element is greater.
*/
static inline int compareByRoomId(Order order1,Order order2){
    Room room1=NULL;
    Room room2=NULL;
#ifndef NDEBUG
    OrderResult res=
#endif
            orderGetRoom(order1,&room1);
    assert(res==ORDER_SUCCESS);
#ifndef NDEBUG
     res=
#endif
             orderGetRoom(order2,&room2);
    assert(res==ORDER_SUCCESS);
    Room_Id id1,id2;
#ifndef NDEBUG
    RoomResult res2=
#endif
            roomGetId(room1,&id1);
    assert(res2==ROOM_SUCCESS);
#ifndef NDEBUG
     res2=
#endif
    roomGetId(room2,&id2);
    assert(res2==ROOM_SUCCESS);
    return id1-id2;
}

int orderCompare(ListElement order_element1, ListElement order_element2) {
    assert(order_element1 != NULL && order_element2 != NULL);
    Order order1 = (Order) order_element1;
    Order order2 = (Order) order_element2;
    if (compareByTime(order1, order2) != EQUAL) {
        return compareByTime(order1, order2);
    }
    if (compareByFaculty(order1, order2) != EQUAL) {
        return compareByFaculty(order1, order2);
    }
    return compareByRoomId(order1, order2);
}

bool orderFilterRoom(ListElement order,ListFilterKey room){
    assert(order!=NULL&&room!=NULL);
    Order order1=(Order)order;
    Room room1=(Room)room;
    return order1->ordered_room==room1;
}

bool orderFilterEscaper(ListElement order,ListFilterKey escaper){
    assert(order!=NULL&&escaper!=NULL);
    Order order1=(Order)order;
    Client escaper1=(Client)escaper;
    return order1->ordered_client==escaper1;
}

bool orderFilterDay(ListElement order,ListFilterKey day){
    assert(order!=NULL&&day!=NULL);
    Order order1=(Order)order;
    Day days=*(Day*)day;
    return order1->days_to_order==days;
}

OrderResult orderAdvanceDay(Order order){
    assert(order!=NULL);
    if(order->days_to_order<=TODAY){
        return ORDER_ILLEGAL_PARAMETERS;
    }
    order->days_to_order--;
    assert(order->days_to_order>=TODAY);
    return ORDER_SUCCESS;
}

OrderResult orderGetFaculty(Order order,TechnionFaculty*output_id) {
    assert(order != NULL);
    if (!output_id) {
        return ORDER_NULL_PARAMETER;
    }
    if(order->order_faculty==UNKNOWN){
        return ORDER_ILLEGAL_PARAMETERS;
    }
    *output_id = order->order_faculty;
    return ORDER_SUCCESS;
}

OrderResult orderGetNumPeople(Order order,Occapancy *people) {
    assert(order != NULL);
    if (!people) {
        return ORDER_NULL_PARAMETER;
    }
    if(order->num_people==UNUSED){
        return ORDER_ILLEGAL_PARAMETERS;
    }
    *people = order->num_people;
    return ORDER_SUCCESS;
}