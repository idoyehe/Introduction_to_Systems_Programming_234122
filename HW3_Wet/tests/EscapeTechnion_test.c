#include "test_utilities.h"
#include "../EscapeTechnion.h"
#include <string.h>

#define EQUAL 0
#define NEGATIVE -1
#define BAD_EMAIL1 "@@"
#define BAD_EMAIL2 "bad!!"
#define GOOD_EMAIL1 "facebook@"
#define GOOD_EMAIL2 "mellanox@"
#define GOOD_EMAIL3 "google@"
#define GOOD_EMAIL4 "osem@"
#define USER_EMAIL1 "ido@"
#define USER_EMAIL2 "shlomi@"
#define ID1 11
#define ID2 22
#define ID3 33
#define GOOD_PRICE 4
#define BAD_PRICE1 -4
#define BAD_PRICE2 7
#define PEOPLE 2
#define BAD_LEVEL1 11
#define GOOD_LEVEL 5
#define TODAY 0
#define TOMMOROW 1
#define OPEN "10"
#define OPEN_TIME 10
#define CLOSE "20"
#define BEST 3


static bool testSystemCreate(){
    EscapeTechnion new_system=systemCreate();
    ASSERT_TEST(new_system!=NULL);
    systemDestroy(new_system);
    return true;
}


static EscapeTechnion buildNewSystemForTests(){
    EscapeTechnion new_system=systemCreate();
    ASSERT_TEST(new_system!=NULL);
    return new_system;
}

static bool testSystemAddCompany(){
    EscapeTechnion my_system=buildNewSystemForTests();
    ASSERT_TEST(systemCompanyAdd(my_system,BAD_EMAIL1,CHEMISTRY)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemCompanyAdd(my_system,BAD_EMAIL2,CHEMISTRY)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL1,UNKNOWN)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL1,UNKNOWN+1)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL1,NEGATIVE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL1,COMPUTER_SCIENCE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL2,ELECTRICAL_ENGINEERING)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL3,COMPUTER_SCIENCE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL1,COMPUTER_SCIENCE)==SYSTEM_EMAIL_ALREADY_EXIST);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL2,ELECTRICAL_ENGINEERING)==SYSTEM_EMAIL_ALREADY_EXIST);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL3,COMPUTER_SCIENCE)==SYSTEM_EMAIL_ALREADY_EXIST);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(my_system,USER_EMAIL1,COMPUTER_SCIENCE)==SYSTEM_EMAIL_ALREADY_EXIST);
    systemDestroy(my_system);
    return true;
}

static EscapeTechnion buildSystemWithCompanies(){
    EscapeTechnion new_system=buildNewSystemForTests();
    ASSERT_TEST(systemCompanyAdd(new_system,GOOD_EMAIL1,CIVIL_ENGINEERING)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(new_system,GOOD_EMAIL2,ELECTRICAL_ENGINEERING)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(new_system,GOOD_EMAIL3,MECHANICAL_ENGINEERING)==SYSTEM_SUCCESS);
    return new_system;
}

static bool testSystemAddRoom(){
    EscapeTechnion my_system=buildSystemWithCompanies();
    ASSERT_TEST(systemRoomAdd(my_system,BAD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,"10","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,BAD_EMAIL2,ID1,GOOD_PRICE,PEOPLE,"10","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,NEGATIVE,GOOD_PRICE,PEOPLE,"10","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,BAD_PRICE1,PEOPLE,"10","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,BAD_PRICE2,PEOPLE,"10","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,NEGATIVE,"10","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,0,"10","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,"25","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,"AA","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,"24","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
	ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,"12","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
	ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,"15","12",GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,BAD_LEVEL1)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL4,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_COMPANY_EMAIL_NOT_EXIST);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL2,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL3,ID3,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_ROOM_ID_ALREADY_EXIST);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL2,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_ROOM_ID_ALREADY_EXIST);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL3,ID3,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_ROOM_ID_ALREADY_EXIST);
    systemDestroy(my_system);
    return true;
}

static bool testClientAdd(){
    EscapeTechnion my_system=buildNewSystemForTests();
    ASSERT_TEST(systemClientAdd(my_system,BAD_EMAIL1,CHEMISTRY,GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientAdd(my_system,BAD_EMAIL2,CHEMISTRY,GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL1,UNKNOWN,GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL1,UNKNOWN+1,GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL1,NEGATIVE,GOOD_LEVEL)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,NEGATIVE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,GOOD_LEVEL+10)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL2,CHEMISTRY,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,GOOD_LEVEL)==SYSTEM_EMAIL_ALREADY_EXIST);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL2,CHEMISTRY,GOOD_LEVEL)==SYSTEM_EMAIL_ALREADY_EXIST);
    ASSERT_TEST(systemCompanyAdd(my_system,USER_EMAIL1,COMPUTER_SCIENCE)==SYSTEM_EMAIL_ALREADY_EXIST);
    systemDestroy(my_system);
    return true;
}

static EscapeTechnion buildSystemWithRoomsandClients(){
    EscapeTechnion new_system=buildSystemWithCompanies();
    ASSERT_TEST(systemRoomAdd(new_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(new_system,GOOD_EMAIL2,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(new_system,GOOD_EMAIL2,ID2,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(new_system,GOOD_EMAIL3,ID3,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientAdd(new_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientAdd(new_system,USER_EMAIL2,CIVIL_ENGINEERING,GOOD_LEVEL)==SYSTEM_SUCCESS);
    return new_system;
}

static bool testSystemClientOrder(){
    EscapeTechnion my_system=buildSystemWithRoomsandClients();
    ASSERT_TEST(systemCompanyAdd(my_system,"mtm@",CHEMISTRY)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(my_system,"mtm@",44,GOOD_PRICE,1,"00","24",GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,BAD_EMAIL1,CHEMISTRY,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,BAD_EMAIL2,CHEMISTRY,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,UNKNOWN,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,NEGATIVE,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,NEGATIVE,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,ID1,NEGATIVE,OPEN_TIME,PEOPLE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,ID1,TODAY,24,PEOPLE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,ID1,TODAY,-1,PEOPLE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,ID1,TODAY,OPEN_TIME,NEGATIVE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,ID1,TODAY,OPEN_TIME,0)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientOrder(my_system,"mtm@",CHEMISTRY,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_CLIENT_EMAIL_NOT_EXIST);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,ID3,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CHEMISTRY,44,TODAY,23,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,CIVIL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_CLIENT_IN_ROOM);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TOMMOROW,OPEN_TIME,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,MECHANICAL_ENGINEERING,ID3,TOMMOROW,OPEN_TIME+1,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TOMMOROW,23,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    systemDestroy(my_system);
    return true;
}

static EscapeTechnion buildSystemWithOrders(){
    EscapeTechnion new_system=buildSystemWithRoomsandClients();
    ASSERT_TEST(systemClientOrder(new_system,USER_EMAIL1,CIVIL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(new_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TOMMOROW,OPEN_TIME,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(new_system,USER_EMAIL2,MECHANICAL_ENGINEERING,ID3,TOMMOROW,OPEN_TIME+1,PEOPLE)==SYSTEM_SUCCESS);
    return new_system;
}

static bool testSystemRemoveClient(){
    EscapeTechnion my_system=buildSystemWithOrders();
    ASSERT_TEST(systemClientRemove(my_system,BAD_EMAIL1)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientRemove(my_system,BAD_EMAIL2)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientRemove(my_system,"mtm@")==SYSTEM_CLIENT_EMAIL_NOT_EXIST);
    ASSERT_TEST(systemClientAdd(my_system,"mtm@",COMPUTER_SCIENCE,10)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientRemove(my_system,"mtm@")==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    ASSERT_TEST(systemClientRemove(my_system,USER_EMAIL1)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientRemove(my_system,USER_EMAIL1)==SYSTEM_CLIENT_EMAIL_NOT_EXIST);
    ASSERT_TEST(systemClientRemove(my_system,USER_EMAIL2)==SYSTEM_SUCCESS);
    systemDestroy(my_system);
    return true;
}

static bool testSystemRemoveRoom(){
    EscapeTechnion my_system=buildSystemWithOrders();
    ASSERT_TEST(systemRoomRemove(my_system,NEGATIVE,ID1)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomRemove(my_system,UNKNOWN,ID1)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomRemove(my_system,CHEMISTRY,NEGATIVE)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemRoomRemove(my_system,CHEMISTRY,ID1)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemRoomRemove(my_system,CIVIL_ENGINEERING,ID2)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemRoomRemove(my_system,ELECTRICAL_ENGINEERING,ID2)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,ID2,TOMMOROW,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemRoomRemove(my_system,ELECTRICAL_ENGINEERING,ID2)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemRoomRemove(my_system,CIVIL_ENGINEERING,ID1)==SYSTEM_RESERVATION_EXIST);
    ASSERT_TEST(systemRoomRemove(my_system,MECHANICAL_ENGINEERING,ID3)==SYSTEM_RESERVATION_EXIST);
    ASSERT_TEST(systemClientRemove(my_system,USER_EMAIL1)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientRemove(my_system,USER_EMAIL2)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomRemove(my_system,CIVIL_ENGINEERING,ID1)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomRemove(my_system,MECHANICAL_ENGINEERING,ID3)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientAdd(my_system,USER_EMAIL2,CIVIL_ENGINEERING,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TOMMOROW,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL1,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TOMMOROW,OPEN_TIME,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomRemove(my_system,CIVIL_ENGINEERING,ID1)==SYSTEM_RESERVATION_EXIST);
    ASSERT_TEST(systemClientRemove(my_system,USER_EMAIL2)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomRemove(my_system,CIVIL_ENGINEERING,ID1)==SYSTEM_SUCCESS);
    systemDestroy(my_system);
    return true;
}

static bool testSystemRemoveCompany() {
    EscapeTechnion my_system=buildSystemWithOrders();
    ASSERT_TEST(systemCompanyRemove(my_system,BAD_EMAIL1)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemCompanyRemove(my_system,BAD_EMAIL2)==SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemCompanyRemove(my_system,"mtm@")==SYSTEM_COMPANY_EMAIL_NOT_EXIST);
    ASSERT_TEST(systemCompanyRemove(my_system,GOOD_EMAIL2)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,ELECTRICAL_ENGINEERING,ID1,10,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,ELECTRICAL_ENGINEERING,ID2,10,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_ID_NOT_EXIST);
    ASSERT_TEST(systemCompanyRemove(my_system,GOOD_EMAIL1)==SYSTEM_RESERVATION_EXIST);
    ASSERT_TEST(systemCompanyRemove(my_system,GOOD_EMAIL3)==SYSTEM_RESERVATION_EXIST);
    ASSERT_TEST(systemClientAdd(my_system,"mtm@",COMPUTER_SCIENCE,10)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,"mtm@",CIVIL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    ASSERT_TEST(systemClientOrder(my_system,"mtm@",CIVIL_ENGINEERING,ID1,TOMMOROW,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    ASSERT_TEST(systemClientOrder(my_system,"mtm@",MECHANICAL_ENGINEERING,ID3,TOMMOROW,OPEN_TIME+1,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    ASSERT_TEST(systemClientRemove(my_system,USER_EMAIL1)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientRemove(my_system,USER_EMAIL2)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyRemove(my_system,GOOD_EMAIL1)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyRemove(my_system,GOOD_EMAIL3)==SYSTEM_SUCCESS);
    systemDestroy(my_system);
    return true;
}
static bool testSystemClientRecommend() {
    EscapeTechnion my_system = systemCreate();
    ASSERT_TEST(systemClientAdd(my_system, USER_EMAIL1, ELECTRICAL_ENGINEERING,GOOD_LEVEL) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientAdd(my_system, USER_EMAIL2, CIVIL_ENGINEERING,GOOD_LEVEL) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientRecommend(my_system, BAD_EMAIL1, PEOPLE) == SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientRecommend(my_system, BAD_EMAIL2, PEOPLE) == SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientRecommend(my_system, USER_EMAIL1, NEGATIVE) == SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientRecommend(my_system, USER_EMAIL1, 0) == SYSTEM_ILLEGAL_PARAMETER);
    ASSERT_TEST(systemClientRecommend(my_system, "mtm@", PEOPLE) == SYSTEM_CLIENT_EMAIL_NOT_EXIST);
    ASSERT_TEST(systemClientRecommend(my_system, USER_EMAIL1, PEOPLE) == SYSTEM_NO_ROOMS_AVAILABLE);
    systemDestroy(my_system);
    my_system=buildSystemWithOrders();
    ASSERT_TEST(systemClientRecommend(my_system, USER_EMAIL1, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientRecommend(my_system, USER_EMAIL2, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientAdd(my_system, "mtm@",AEROSPACE_ENGINEERING,GOOD_LEVEL) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,"mtm@",ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    ASSERT_TEST(systemClientOrder(my_system,"mtm@",CIVIL_ENGINEERING,ID1,TODAY,OPEN_TIME+1,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    ASSERT_TEST(systemCompanyAdd(my_system,GOOD_EMAIL4,PHYSICS)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(my_system,GOOD_EMAIL4,ID1,GOOD_PRICE,PEOPLE,OPEN,CLOSE,GOOD_LEVEL)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientRecommend(my_system,"mtm@",PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientAdd(my_system, "mtm2@",CHEMICAL_ENGINEERING,GOOD_LEVEL) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,"mtm2@",ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    ASSERT_TEST(systemClientOrder(my_system,"mtm2@",ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME+1,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    ASSERT_TEST(systemClientRecommend(my_system,"mtm2@",PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,"mtm2@",ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME+2,PEOPLE)==SYSTEM_CLIENT_IN_ROOM);
    ASSERT_TEST(systemClientOrder(my_system,"mtm@",ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME+2,PEOPLE)==SYSTEM_ROOM_NOT_AVAILABLE);
    systemDestroy(my_system);
    return true;
}

static bool testSystemReportDay() {
    EscapeTechnion my_system = buildSystemWithRoomsandClients();
    List today_order = NULL;
    Day current_day;
    Revenue total_revenue;
    ASSERT_TEST(systemGetDay(my_system, &current_day) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetRevenue(my_system, &total_revenue) == SYSTEM_SUCCESS);
    ASSERT_TEST(current_day == 0 && total_revenue == 0);
    ASSERT_TEST(systemReportDay(my_system, NULL) == SYSTEM_NULL_PARAMETER);
    ASSERT_TEST(systemReportDay(my_system, &today_order) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetDay(my_system, &current_day) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetRevenue(my_system, &total_revenue) == SYSTEM_SUCCESS);
    ASSERT_TEST(listGetSize(today_order) == 0);
    listDestroy(today_order);
    today_order = NULL;
    ASSERT_TEST(current_day == 1 && total_revenue == 0);
    ASSERT_TEST(systemClientOrder(my_system, USER_EMAIL1, ELECTRICAL_ENGINEERING,ID1, TODAY, OPEN_TIME, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system, USER_EMAIL1, ELECTRICAL_ENGINEERING,ID2, TODAY,OPEN_TIME+1, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system, USER_EMAIL2, CIVIL_ENGINEERING, ID1,TODAY, OPEN_TIME, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system, USER_EMAIL2, ELECTRICAL_ENGINEERING,ID1, TODAY, OPEN_TIME+1, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system, USER_EMAIL1, ELECTRICAL_ENGINEERING, ID1, TOMMOROW, OPEN_TIME, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system, USER_EMAIL1, ELECTRICAL_ENGINEERING, ID2, TOMMOROW, OPEN_TIME+1, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system, USER_EMAIL2, CIVIL_ENGINEERING, ID1, TOMMOROW, OPEN_TIME, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system, USER_EMAIL2, ELECTRICAL_ENGINEERING, ID1, TOMMOROW, OPEN_TIME+1, PEOPLE) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemReportDay(my_system, &today_order) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetDay(my_system, &current_day) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetRevenue(my_system, &total_revenue) == SYSTEM_SUCCESS);
    ASSERT_TEST(current_day == 2 && total_revenue == 26);
    ASSERT_TEST(listGetSize(today_order)==4);
    Time order_hour;
    TechnionFaculty order_faculty;
    Room order_room = NULL;
    Room_Id order_room_id;
    Occapancy order_people;
    Cost order_price;
    Difficulty order_room_level;
    Skill client_skill;
    Client client = NULL;
    TechnionFaculty client_faculty;
    Day order_day;
    //first order
    Order iterator=listGetFirst(today_order);
    ASSERT_TEST(iterator!=NULL);
    ASSERT_TEST(orderGetClient(iterator, &client) == ORDER_SUCCESS);
    const Email client_email = clientGetEmailR(client);
    ASSERT_TEST(clientGetLevel(client, &client_skill) == CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(client, &client_faculty) == CLIENT_SUCCESS);
    ASSERT_TEST(orderGetRoom(iterator, &order_room) == ORDER_SUCCESS);
    ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
    ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
    const Email company_email = roomGetEmailR(order_room);
    ASSERT_TEST(orderGetFaculty(iterator, &order_faculty) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetTime(iterator, &order_day, &order_hour) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetPrice(iterator, &order_price) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetNumPeople(iterator, &order_people) == ORDER_SUCCESS);
    ASSERT_TEST(strcmp(client_email,USER_EMAIL2)==EQUAL);
    ASSERT_TEST(strcmp(company_email,GOOD_EMAIL1)==EQUAL);
    ASSERT_TEST(client_faculty==CIVIL_ENGINEERING&&client_skill==GOOD_LEVEL);
    ASSERT_TEST(order_room_id==ID1&&order_faculty==CIVIL_ENGINEERING);
    ASSERT_TEST(order_hour=OPEN&&order_room_level==GOOD_LEVEL);
    ASSERT_TEST(order_people==PEOPLE&&order_price==6);
    //second order
    iterator=listGetNext(today_order);
    ASSERT_TEST(iterator!=NULL);
    client=NULL;
    order_room=NULL;
    ASSERT_TEST(orderGetClient(iterator, &client) == ORDER_SUCCESS);
    const Email client_email1 = clientGetEmailR(client);
    ASSERT_TEST(clientGetLevel(client, &client_skill) == CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(client, &client_faculty) == CLIENT_SUCCESS);
    ASSERT_TEST(orderGetRoom(iterator, &order_room) == ORDER_SUCCESS);
    ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
    ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
    const Email company_email1 = roomGetEmailR(order_room);
    ASSERT_TEST(orderGetFaculty(iterator, &order_faculty) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetTime(iterator, &order_day, &order_hour) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetPrice(iterator, &order_price) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetNumPeople(iterator, &order_people) == ORDER_SUCCESS);
    ASSERT_TEST(strcmp(client_email1,USER_EMAIL1)==EQUAL);
    ASSERT_TEST(strcmp(company_email1,GOOD_EMAIL2)==EQUAL);
    ASSERT_TEST(client_faculty==ELECTRICAL_ENGINEERING&&client_skill==GOOD_LEVEL);
    ASSERT_TEST(order_room_id==ID1&&order_faculty==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(order_hour=OPEN&&order_room_level==GOOD_LEVEL);
    ASSERT_TEST(order_people==PEOPLE&&order_price==6);
    //third order
    iterator=listGetNext(today_order);
    ASSERT_TEST(iterator!=NULL);
    client=NULL;
    order_room=NULL;
    ASSERT_TEST(orderGetClient(iterator, &client) == ORDER_SUCCESS);
    const Email client_email2 = clientGetEmailR(client);
    ASSERT_TEST(clientGetLevel(client, &client_skill) == CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(client, &client_faculty) == CLIENT_SUCCESS);
    ASSERT_TEST(orderGetRoom(iterator, &order_room) == ORDER_SUCCESS);
    ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
    ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
    const Email company_email2 = roomGetEmailR(order_room);
    ASSERT_TEST(orderGetFaculty(iterator, &order_faculty) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetTime(iterator, &order_day, &order_hour) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetPrice(iterator, &order_price) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetNumPeople(iterator, &order_people) == ORDER_SUCCESS);
    ASSERT_TEST(strcmp(client_email2,USER_EMAIL2)==EQUAL);
    ASSERT_TEST(strcmp(company_email2,GOOD_EMAIL2)==EQUAL);
    ASSERT_TEST(client_faculty==CIVIL_ENGINEERING&&client_skill==GOOD_LEVEL);
    ASSERT_TEST(order_room_id==ID1&&order_faculty==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(order_hour=OPEN+1&&order_room_level==GOOD_LEVEL);
    ASSERT_TEST(order_people==PEOPLE&&order_price==8);
    //forth order
    iterator=listGetNext(today_order);
    ASSERT_TEST(iterator!=NULL);
    client=NULL;
    order_room=NULL;
    ASSERT_TEST(orderGetClient(iterator, &client) == ORDER_SUCCESS);
    const Email client_email3 = clientGetEmailR(client);
    ASSERT_TEST(clientGetLevel(client, &client_skill) == CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(client, &client_faculty) == CLIENT_SUCCESS);
    ASSERT_TEST(orderGetRoom(iterator, &order_room) == ORDER_SUCCESS);
    ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
    ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
    const Email company_email3 = roomGetEmailR(order_room);
    ASSERT_TEST(orderGetFaculty(iterator, &order_faculty) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetTime(iterator, &order_day, &order_hour) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetPrice(iterator, &order_price) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetNumPeople(iterator, &order_people) == ORDER_SUCCESS);
    ASSERT_TEST(strcmp(client_email3,USER_EMAIL1)==EQUAL);
    ASSERT_TEST(strcmp(company_email3,GOOD_EMAIL2)==EQUAL);
    ASSERT_TEST(client_faculty==ELECTRICAL_ENGINEERING&&client_skill==GOOD_LEVEL);
    ASSERT_TEST(order_room_id==ID2&&order_faculty==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(order_hour=OPEN+1&&order_room_level==GOOD_LEVEL);
    ASSERT_TEST(order_people==PEOPLE&&order_price==6);
    listDestroy(today_order);
    today_order=NULL;
    client=NULL;
    order_room=NULL;
    //next day
    ASSERT_TEST(systemReportDay(my_system,&today_order)==SYSTEM_SUCCESS);
    //first order
    iterator=listGetFirst(today_order);
    ASSERT_TEST(iterator!=NULL);
    ASSERT_TEST(orderGetClient(iterator, &client) == ORDER_SUCCESS);
    const Email client_email4 = clientGetEmailR(client);
    ASSERT_TEST(clientGetLevel(client, &client_skill) == CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(client, &client_faculty) == CLIENT_SUCCESS);
    ASSERT_TEST(orderGetRoom(iterator, &order_room) == ORDER_SUCCESS);
    ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
    ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
    const Email company_email4 = roomGetEmailR(order_room);
    ASSERT_TEST(orderGetFaculty(iterator, &order_faculty) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetTime(iterator, &order_day, &order_hour) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetPrice(iterator, &order_price) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetNumPeople(iterator, &order_people) == ORDER_SUCCESS);
    ASSERT_TEST(strcmp(client_email4,USER_EMAIL2)==EQUAL);
    ASSERT_TEST(strcmp(company_email4,GOOD_EMAIL1)==EQUAL);
    ASSERT_TEST(client_faculty==CIVIL_ENGINEERING&&client_skill==GOOD_LEVEL);
    ASSERT_TEST(order_room_id==ID1&&order_faculty==CIVIL_ENGINEERING);
    ASSERT_TEST(order_hour=OPEN&&order_room_level==GOOD_LEVEL);
    ASSERT_TEST(order_people==PEOPLE&&order_price==6);
    //second order
    iterator=listGetNext(today_order);
    ASSERT_TEST(iterator!=NULL);
    client=NULL;
    order_room=NULL;
    ASSERT_TEST(orderGetClient(iterator, &client) == ORDER_SUCCESS);
    const Email client_email5 = clientGetEmailR(client);
    ASSERT_TEST(clientGetLevel(client, &client_skill) == CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(client, &client_faculty) == CLIENT_SUCCESS);
    ASSERT_TEST(orderGetRoom(iterator, &order_room) == ORDER_SUCCESS);
    ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
    ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
    const Email company_email5 = roomGetEmailR(order_room);
    ASSERT_TEST(orderGetFaculty(iterator, &order_faculty) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetTime(iterator, &order_day, &order_hour) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetPrice(iterator, &order_price) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetNumPeople(iterator, &order_people) == ORDER_SUCCESS);
    ASSERT_TEST(strcmp(client_email5,USER_EMAIL1)==EQUAL);
    ASSERT_TEST(strcmp(company_email5,GOOD_EMAIL2)==EQUAL);
    ASSERT_TEST(client_faculty==ELECTRICAL_ENGINEERING&&client_skill==GOOD_LEVEL);
    ASSERT_TEST(order_room_id==ID1&&order_faculty==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(order_hour=OPEN&&order_room_level==GOOD_LEVEL);
    ASSERT_TEST(order_people==PEOPLE&&order_price==6);
    //third order
    iterator=listGetNext(today_order);
    ASSERT_TEST(iterator!=NULL);
    client=NULL;
    order_room=NULL;
    ASSERT_TEST(orderGetClient(iterator, &client) == ORDER_SUCCESS);
    const Email client_email6 = clientGetEmailR(client);
    ASSERT_TEST(clientGetLevel(client, &client_skill) == CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(client, &client_faculty) == CLIENT_SUCCESS);
    ASSERT_TEST(orderGetRoom(iterator, &order_room) == ORDER_SUCCESS);
    ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
    ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
    const Email company_email6 = roomGetEmailR(order_room);
    ASSERT_TEST(orderGetFaculty(iterator, &order_faculty) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetTime(iterator, &order_day, &order_hour) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetPrice(iterator, &order_price) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetNumPeople(iterator, &order_people) == ORDER_SUCCESS);
    ASSERT_TEST(strcmp(client_email6,USER_EMAIL2)==EQUAL);
    ASSERT_TEST(strcmp(company_email6,GOOD_EMAIL2)==EQUAL);
    ASSERT_TEST(client_faculty==CIVIL_ENGINEERING&&client_skill==GOOD_LEVEL);
    ASSERT_TEST(order_room_id==ID1&&order_faculty==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(order_hour=OPEN+1&&order_room_level==GOOD_LEVEL);
    ASSERT_TEST(order_people==PEOPLE&&order_price==8);
    //forth order
    iterator=listGetNext(today_order);
    ASSERT_TEST(iterator!=NULL);
    client=NULL;
    order_room=NULL;
    ASSERT_TEST(orderGetClient(iterator, &client) == ORDER_SUCCESS);
    const Email client_email7 = clientGetEmailR(client);
    ASSERT_TEST(clientGetLevel(client, &client_skill) == CLIENT_SUCCESS);
    ASSERT_TEST(clientGetFaculty(client, &client_faculty) == CLIENT_SUCCESS);
    ASSERT_TEST(orderGetRoom(iterator, &order_room) == ORDER_SUCCESS);
    ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
    ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
    const Email company_email7 = roomGetEmailR(order_room);
    ASSERT_TEST(orderGetFaculty(iterator, &order_faculty) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetTime(iterator, &order_day, &order_hour) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetPrice(iterator, &order_price) == ORDER_SUCCESS);
    ASSERT_TEST(orderGetNumPeople(iterator, &order_people) == ORDER_SUCCESS);
    ASSERT_TEST(strcmp(client_email7,USER_EMAIL1)==EQUAL);
    ASSERT_TEST(strcmp(company_email7,GOOD_EMAIL2)==EQUAL);
    ASSERT_TEST(client_faculty==ELECTRICAL_ENGINEERING&&client_skill==GOOD_LEVEL);
    ASSERT_TEST(order_room_id==ID2&&order_faculty==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(order_hour=OPEN+1&&order_room_level==GOOD_LEVEL);
    ASSERT_TEST(order_people==PEOPLE&&order_price==6);
    ASSERT_TEST(systemGetDay(my_system, &current_day) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetRevenue(my_system, &total_revenue) == SYSTEM_SUCCESS);
    ASSERT_TEST(current_day == 3 && total_revenue == 52);
    listDestroy(today_order);
    today_order=NULL;
    systemDestroy(my_system);
    return true;
}

static bool testSystemBest(){
    EscapeTechnion my_system=buildSystemWithRoomsandClients();
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME+1,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TODAY,OPEN_TIME+2,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TODAY,OPEN_TIME+4,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,CIVIL_ENGINEERING,ID1,TODAY,OPEN_TIME+3,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL1,ELECTRICAL_ENGINEERING,ID1,TODAY,OPEN_TIME+4,PEOPLE)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemClientOrder(my_system,USER_EMAIL2,MECHANICAL_ENGINEERING,ID3,TODAY,OPEN_TIME,PEOPLE)==SYSTEM_SUCCESS);
    List today_order=NULL;
    ASSERT_TEST(systemReportDay(my_system,&today_order)==SYSTEM_SUCCESS);
    listDestroy(today_order);
    today_order=NULL;
    List best=NULL;
    ASSERT_TEST(systemReportBest(my_system,NULL)==SYSTEM_NULL_PARAMETER);
    ASSERT_TEST(systemReportBest(my_system,&best)==SYSTEM_SUCCESS);
    Faculty iterator=listGetFirst(best);
    TechnionFaculty current_id;
    Revenue current_rev;
    ASSERT_TEST(facultyGetTotalRevenue(iterator,&current_rev)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyGetID(iterator,&current_id)==FACULTY_SUCCESS);
    ASSERT_TEST(current_id==CIVIL_ENGINEERING);
    ASSERT_TEST(current_rev==18);
    iterator=listGetNext(best);
    ASSERT_TEST(facultyGetTotalRevenue(iterator,&current_rev)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyGetID(iterator,&current_id)==FACULTY_SUCCESS);
    ASSERT_TEST(current_id==ELECTRICAL_ENGINEERING);
    ASSERT_TEST(current_rev==18);
    iterator=listGetNext(best);
    ASSERT_TEST(facultyGetTotalRevenue(iterator,&current_rev)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyGetID(iterator,&current_id)==FACULTY_SUCCESS);
    ASSERT_TEST(current_id==MECHANICAL_ENGINEERING);
    ASSERT_TEST(current_rev==8);
    ASSERT_TEST(systemGetRevenue(my_system,&current_rev)==SYSTEM_SUCCESS);
    ASSERT_TEST(current_rev==44);
    listDestroy(best);
    systemDestroy(my_system);
    return true;
}
int main(){
    RUN_TEST(testSystemCreate);
    RUN_TEST(testSystemAddCompany);
    RUN_TEST(testSystemAddRoom);
    RUN_TEST(testClientAdd);
    RUN_TEST(testSystemClientOrder);
    RUN_TEST(testSystemRemoveClient);
    RUN_TEST(testSystemRemoveRoom);
    RUN_TEST(testSystemRemoveCompany);
    RUN_TEST(testSystemClientRecommend);
    RUN_TEST(testSystemReportDay);
    RUN_TEST(testSystemBest);
    return 0;
}