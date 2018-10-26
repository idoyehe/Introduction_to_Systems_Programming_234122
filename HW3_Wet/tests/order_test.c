#include "test_utilities.h"
#include "../list.h"
#include "../order.h"

#define EQUAL 0
#define ZERO 0
#define TODAY 0
#define TOMORROW 1
#define POSITIVE 5
#define GOOD_LEVEL1 5
#define GOOD_LEVEL2 1
#define GOOD_PRICE 16
#define NOON 12
#define DISCOUNT 0.75
#define GOOD_EMAIL1 "facebook@"
#define USER_EMAIL1 "ido@"
#define USER_EMAIL2 "shlomi@"
#define OPEN 5
#define CLOSE 13
#define ID1 11
#define ID2 22



static bool testOrderCreate() {
    Order order=orderCreate();
    ASSERT_TEST(order!= NULL);
    orderDestroy(order);
    return true;
}

static bool testOrderDestroy() {
    orderDestroy(NULL);
    Order order=orderCreate();
    orderDestroy(order);
    return true;
}

static Room buildRoomForTests() {
    Room my_room = roomCreate();
    ASSERT_TEST(my_room != NULL);
    Company temp = companyCreate();
    ASSERT_TEST(temp != NULL);
    ASSERT_TEST(companySetEmail(temp, GOOD_EMAIL1) == COMPANY_SUCCESS);
    ASSERT_TEST(roomSetEmailFromCompany(my_room, temp) == ROOM_SUCCESS);
    companyDestroy(temp);
    ASSERT_TEST(roomSetId(my_room, ID1) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetPrice(my_room, GOOD_PRICE) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetLevel(my_room, GOOD_LEVEL1) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetNumPeople(my_room, POSITIVE) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetWorkingHours(my_room,OPEN,CLOSE) == ROOM_SUCCESS);
    return my_room;
}

static Client buildEscaperForTests(){
    Client my_client=clientCreate();
    ASSERT_TEST(my_client!=NULL);
    ASSERT_TEST(clientSetEmail(my_client,USER_EMAIL1)==CLIENT_SUCCESS);
    ASSERT_TEST(clientSetFaculty(my_client,ELECTRICAL_ENGINEERING)==CLIENT_SUCCESS);
    ASSERT_TEST(clientSetLevel(my_client,GOOD_LEVEL2)==CLIENT_SUCCESS);
    return my_client;
}

static bool testOrderSetandGetNoDiscount(){
    Order my_order=orderCreate();
    ASSERT_TEST(my_order!= NULL);
    Client ido=buildEscaperForTests();
    Room room1=buildRoomForTests();
    ASSERT_TEST(orderSet(my_order,NULL,ido,CHEMISTRY,POSITIVE,ZERO,ZERO)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderSet(my_order,room1,NULL,CHEMISTRY,POSITIVE,ZERO,ZERO)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderSet(my_order,room1,ido,-1,POSITIVE,ZERO,ZERO)==ORDER_ILLEGAL_PARAMETERS);
    ASSERT_TEST(orderSet(my_order,room1,ido,UNKNOWN,POSITIVE,ZERO,ZERO)==ORDER_ILLEGAL_PARAMETERS);
    ASSERT_TEST(orderSet(my_order,room1,ido,CHEMISTRY,-1,ZERO,ZERO)==ORDER_ILLEGAL_PARAMETERS);
    ASSERT_TEST(orderSet(my_order,room1,ido,CHEMISTRY,ZERO,ZERO,ZERO)==ORDER_ILLEGAL_PARAMETERS);
    ASSERT_TEST(orderSet(my_order,room1,ido,CHEMISTRY,POSITIVE,-1,ZERO)==ORDER_ILLEGAL_PARAMETERS);
    ASSERT_TEST(orderSet(my_order,room1,ido,CHEMISTRY,POSITIVE,ZERO,-1)==ORDER_ILLEGAL_PARAMETERS);
    ASSERT_TEST(orderSet(my_order,room1,ido,CHEMISTRY,POSITIVE,ZERO,25)==ORDER_ILLEGAL_PARAMETERS);
    ASSERT_TEST(orderSet(my_order,room1,ido,CHEMISTRY,POSITIVE,TOMORROW,NOON)
                ==ORDER_SUCCESS);
    Room output_room=NULL;
    Client output_Escaper=NULL;
    Cost output_price;
    Day output_days;
    Time output_time;
    ASSERT_TEST(orderGetClient(my_order, NULL)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetClient(my_order, &output_Escaper)==ORDER_SUCCESS);
    ASSERT_TEST(output_Escaper==ido);
    ASSERT_TEST(orderGetRoom(my_order,NULL)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetRoom(my_order,&output_room)==ORDER_SUCCESS);
    ASSERT_TEST(output_room==room1);
    ASSERT_TEST(orderGetPrice(my_order,NULL)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetPrice(my_order,&output_price)==ORDER_SUCCESS);
    ASSERT_TEST(output_price==POSITIVE*GOOD_PRICE);
    ASSERT_TEST(orderGetTime(my_order,NULL,&output_time)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetTime(my_order,&output_days,NULL)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetTime(my_order,&output_days,&output_time)==ORDER_SUCCESS);
    ASSERT_TEST(output_days==TOMORROW&&output_time==NOON);
    clientDestroy(ido);
    roomDestroy(room1);
    orderDestroy(my_order);
    return true;
}

static bool testOrderSetandGetYesDiscount(){
    Order my_order=orderCreate();
    ASSERT_TEST(my_order!= NULL);
    ASSERT_TEST(orderSet(my_order,NULL,NULL,CHEMISTRY,POSITIVE,ZERO,ZERO)==ORDER_NULL_PARAMETER);
    Client ido=buildEscaperForTests();
    Room room1=buildRoomForTests();
    ASSERT_TEST(orderSet(my_order,room1,ido,ELECTRICAL_ENGINEERING,POSITIVE,TOMORROW,NOON)
                ==ORDER_SUCCESS);
    Room output_room=NULL;
    Client output_Escaper=NULL;
    Cost output_price;
    Day output_days;
    Time output_time;
    ASSERT_TEST(orderGetClient(my_order, NULL)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetClient(my_order, &output_Escaper)==ORDER_SUCCESS);
    ASSERT_TEST(output_Escaper==ido);
    ASSERT_TEST(orderGetRoom(my_order,NULL)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetRoom(my_order,&output_room)==ORDER_SUCCESS);
    ASSERT_TEST(output_room==room1);
    ASSERT_TEST(orderGetPrice(my_order,NULL)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetPrice(my_order,&output_price)==ORDER_SUCCESS);
    ASSERT_TEST(output_price==POSITIVE*GOOD_PRICE*DISCOUNT);
    ASSERT_TEST(orderGetTime(my_order,NULL,&output_time)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetTime(my_order,&output_days,NULL)==ORDER_NULL_PARAMETER);
    ASSERT_TEST(orderGetTime(my_order,&output_days,&output_time)==ORDER_SUCCESS);
    ASSERT_TEST(output_days==TOMORROW&&output_time==NOON);
    clientDestroy(ido);
    roomDestroy(room1);
    orderDestroy(my_order);
    return true;
}

static bool testOrderCompare(){
    Order order1=orderCreate();
    Order order2=orderCreate();
    ASSERT_TEST(order1!=NULL&&order2!=NULL);
    Client ido=buildEscaperForTests();
    Room room1=buildRoomForTests();
    ASSERT_TEST(orderSet(order1,room1,ido,COMPUTER_SCIENCE,POSITIVE,TOMORROW,NOON)==ORDER_SUCCESS);
    ASSERT_TEST(orderSet(order2,room1,ido,COMPUTER_SCIENCE,POSITIVE,TODAY,NOON)==ORDER_SUCCESS);
    ASSERT_TEST(orderCompare(order1,order2)>EQUAL);
    ASSERT_TEST(orderSet(order2,room1,ido,COMPUTER_SCIENCE,POSITIVE,1+TOMORROW,NOON)==ORDER_SUCCESS);
    ASSERT_TEST(orderCompare(order1,order2)<EQUAL);
    ASSERT_TEST(orderSet(order2,room1,ido,COMPUTER_SCIENCE,POSITIVE,TOMORROW,NOON-2)==ORDER_SUCCESS);
    ASSERT_TEST(orderCompare(order1,order2)>EQUAL);
    ASSERT_TEST(orderSet(order2,room1,ido,COMPUTER_SCIENCE,POSITIVE,TOMORROW,NOON+1) ==ORDER_SUCCESS);
    ASSERT_TEST(orderCompare(order1,order2)<EQUAL);
    ASSERT_TEST(roomSetId(room1,ID1)==ROOM_SUCCESS);
    Room room2=buildRoomForTests();
    ASSERT_TEST(roomSetId(room2,ID2)==ROOM_SUCCESS);
    ASSERT_TEST(orderSet(order2,room2,ido,COMPUTER_SCIENCE,POSITIVE,TOMORROW,NOON)==ORDER_SUCCESS);
    ASSERT_TEST(orderCompare(order1,order2)<EQUAL);
    ASSERT_TEST(orderSet(order2,room1,ido,ELECTRICAL_ENGINEERING,POSITIVE,TOMORROW,NOON) ==ORDER_SUCCESS);
    ASSERT_TEST(ELECTRICAL_ENGINEERING<COMPUTER_SCIENCE);
    ASSERT_TEST(orderCompare(order1,order2)>EQUAL);
    clientDestroy(ido);
    roomDestroy(room1);
    roomDestroy(room2);
    orderDestroy(order1);
    orderDestroy(order2);
    return true;
}

static bool testOrderCopy() {
    Order order=orderCreate();
    ASSERT_TEST(order!=NULL);
    Order order_copy=orderCopy(order);
    ASSERT_TEST(order_copy==NULL);
    Client ido=buildEscaperForTests();
    Room room1=buildRoomForTests();
    ASSERT_TEST(orderSet(order,room1,ido,COMPUTER_SCIENCE,POSITIVE,TOMORROW,NOON)==ORDER_SUCCESS);
    order_copy=orderCopy(order);
    ASSERT_TEST(order_copy!=NULL);
    Room output_room=NULL;
    Client output_Escaper=NULL;
    Cost output_price;
    Day output_days;
    Time output_time;
    ASSERT_TEST(orderGetClient(order_copy, &output_Escaper)==ORDER_SUCCESS);
    ASSERT_TEST(output_Escaper==ido);
    ASSERT_TEST(orderGetRoom(order_copy,&output_room)==ORDER_SUCCESS);
    ASSERT_TEST(output_room==room1);
    ASSERT_TEST(orderGetPrice(order_copy,&output_price)==ORDER_SUCCESS);
    ASSERT_TEST(output_price==POSITIVE*GOOD_PRICE);
    ASSERT_TEST(orderGetTime(order_copy,&output_days,&output_time)==ORDER_SUCCESS);
    ASSERT_TEST(output_days==TOMORROW&&output_time==NOON);
    clientDestroy(ido);
    roomDestroy(room1);
    orderDestroy(order);
    orderDestroy(order_copy);
    return true;
}

static bool testOrderAdvanceDay(){
    Order order1=orderCreate();
    ASSERT_TEST(order1!= NULL);
    Client ido=buildEscaperForTests();
    Room room1=buildRoomForTests();
    ASSERT_TEST(orderSet(order1,room1,ido,COMPUTER_SCIENCE,POSITIVE,TODAY,NOON)==ORDER_SUCCESS);
    ASSERT_TEST(orderAdvanceDay(order1)==ORDER_ILLEGAL_PARAMETERS);
    ASSERT_TEST(orderSet(order1,room1,ido,COMPUTER_SCIENCE,POSITIVE,TOMORROW+1,NOON)==ORDER_SUCCESS);
    ASSERT_TEST(orderAdvanceDay(order1)==ORDER_SUCCESS);
    ASSERT_TEST(orderAdvanceDay(order1)==ORDER_SUCCESS);
    ASSERT_TEST(orderAdvanceDay(order1)==ORDER_ILLEGAL_PARAMETERS);
    Day output_days;
    Time output_time;
    ASSERT_TEST(orderGetTime(order1,&output_days,&output_time)==ORDER_SUCCESS);
    ASSERT_TEST(output_days==TODAY&&output_time==NOON);
    clientDestroy(ido);
    roomDestroy(room1);
    orderDestroy(order1);
    return true;
}

/*test behavior of Order inside a List*/
static bool testOrderInList() {
    Client ido=buildEscaperForTests();
    Client shlomi=buildEscaperForTests();
    ASSERT_TEST(clientSetEmail(shlomi,USER_EMAIL2)==CLIENT_SUCCESS);
    ASSERT_TEST(clientSetFaculty(shlomi,COMPUTER_SCIENCE)==CLIENT_SUCCESS);
    Room room1=buildRoomForTests();
    ASSERT_TEST(room1!=NULL);
    Room room2=buildRoomForTests();
    ASSERT_TEST(roomSetPrice(room2,GOOD_PRICE/2)==ROOM_SUCCESS);
    ASSERT_TEST(roomSetId(room2,ID2)==ROOM_SUCCESS);
    Order order1=orderCreate();
    ASSERT_TEST(order1!=NULL);
    Order order2=orderCreate();
    ASSERT_TEST(order2!=NULL);
    ASSERT_TEST(orderSet(order1,room1,ido,COMPUTER_SCIENCE,POSITIVE,TOMORROW,NOON)==ORDER_SUCCESS);
    ASSERT_TEST(orderSet(order2,room2,shlomi,COMPUTER_SCIENCE,POSITIVE-1,TODAY,NOON)==ORDER_SUCCESS);
    List two= listCreate(orderCopy, orderDestroy);
    ASSERT_TEST(two!=NULL);
    ASSERT_TEST(listInsertFirst(two,order2)==LIST_SUCCESS);
    ASSERT_TEST(listInsertFirst(two,order1)==LIST_SUCCESS);
    ASSERT_TEST(listSort(two,orderCompare)==LIST_SUCCESS);
    Order ptr=listGetFirst(two);
    ASSERT_TEST(orderCompare(ptr,order2)==EQUAL);
    ptr=listGetNext(two);
    ASSERT_TEST(orderCompare(ptr,order1)==EQUAL);
    ptr=NULL;
    List filtered_room=listFilter(two,orderFilterRoom,room1);
    ptr=listGetFirst(filtered_room);
    ASSERT_TEST(orderCompare(ptr,order1)==EQUAL);
    listDestroy(filtered_room);
    ptr=NULL;
    List filtered_client=listFilter(two,orderFilterEscaper,shlomi);
    ptr=listGetFirst(filtered_client);
    ASSERT_TEST(orderCompare(ptr,order2)==EQUAL);
    listDestroy(filtered_client);
    ptr=NULL;
    Day today=ZERO;
    List filtered_today=listFilter(two,orderFilterDay,&today);
    ptr=listGetFirst(filtered_today);
    ASSERT_TEST(orderCompare(ptr,order2)==EQUAL);
    listDestroy(filtered_today);
    orderDestroy(order1);
    orderDestroy(order2);
    listDestroy(two);
    roomDestroy(room1);
    roomDestroy(room2);
    clientDestroy(ido);
    clientDestroy(shlomi);
    return true;
}

int main(int argv, char **arc) {
    RUN_TEST(testOrderCreate);
    RUN_TEST(testOrderDestroy);
    RUN_TEST(testOrderSetandGetNoDiscount);
    RUN_TEST(testOrderSetandGetYesDiscount);
    RUN_TEST(testOrderAdvanceDay);
    RUN_TEST(testOrderCompare);
    RUN_TEST(testOrderCopy);
    RUN_TEST(testOrderInList);
    return 0;
}

