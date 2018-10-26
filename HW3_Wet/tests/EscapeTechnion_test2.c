#include "test_utilities.h"
#include "EscapeTechnion.h"
#include <string.h>
#include <stdlib.h>


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

static EscapeTechnion buildSystemToTest(){
    EscapeTechnion new_system=buildNewSystemForTests();
    ASSERT_TEST(systemCompanyAdd(new_system,"rnd@apple.com",13)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(new_system,"rnd@google.com",5)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(new_system,"rnd@qualcomm.com",3)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(new_system,"rnd@microsoft.com",13)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemCompanyAdd(new_system,"rnd@refael.com",13)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(new_system,"rnd@apple.com",1,100,3,"06","18",1)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(new_system,"rnd@google.com",2,120,4,"10","23",3)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(new_system,"rnd@google.com",1,240,6,"13","19",10)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(new_system,"rnd@microsoft.com",3,160,2,"11","14",5)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemRoomAdd(new_system,"rnd@apple.com",2,200,4,"09","20",7)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperAdd(new_system,"esc1@g.com",13,4)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperAdd(new_system,"esc2@g.com",13,6)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperAdd(new_system,"esc3@g.com",13,10)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperAdd(new_system,"esc4@g.com",13,6)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperAdd(new_system,"esc5@g.com",1,8)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperAdd(new_system,"esc6@g.com",5,8)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperAdd(new_system,"esc7@g.com",6,7)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperAdd(new_system,"esc8@g.com",7,4)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperOrder(new_system,"esc1@g.com",13,1,0,10,4)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperOrder(new_system,"esc7@g.com",5,1,0,13,3)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperRecommend(new_system,"esc6@g.com",5)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperOrder(new_system,"esc2@g.com",13,3,2,13,3)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemEscaperOrder(new_system,"esc2@g.com",13,1,1,10,3)==SYSTEM_SUCCESS);
    return new_system;
}

static bool testSystemReportDay() {
    EscapeTechnion my_system = buildSystemToTest();
    List today_order = NULL;
    List best=NULL;
    ASSERT_TEST(systemReportBest(my_system,&best)==SYSTEM_SUCCESS);
    Day current_day;
    Price total_revenue;
    ASSERT_TEST(systemGetDay(my_system, &current_day) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetRevenue(my_system, &total_revenue) == SYSTEM_SUCCESS);
    mtmPrintFacultiesHeader(stdout,UNKNOWN,current_day,total_revenue);
    Faculty iterator=listGetFirst(best);
    for(int i=0;i<3;i++){
        Price current_rev;
        TechnionFaculty current_id;
        ASSERT_TEST(facultyGetTotalRevenue(iterator,&current_rev)==FACULTY_SUCCESS);
        ASSERT_TEST(facultyGetID(iterator,&current_id)==FACULTY_SUCCESS);
        mtmPrintFaculty(stdout,current_id,current_rev);
        iterator=listGetNext(best);
    }
    listDestroy(best);
    best=NULL;
    ASSERT_TEST(systemReportDay(my_system,&today_order)==SYSTEM_SUCCESS);
    mtmPrintDayHeader(stdout,current_day,listGetSize(today_order));
    LIST_FOREACH(Order,iterator2,today_order){
        Time order_hour;
        TechnionFaculty order_faculty;
        Room order_room = NULL;
        Id order_room_id;
        Num_People order_people;
        Price order_price;
        Level order_room_level;
        Level client_skill;
        Escaper client = NULL;
        TechnionFaculty client_faculty;
        Day order_day;
        ASSERT_TEST(iterator2!=NULL);
        ASSERT_TEST(orderGetEscaper(iterator2, &client) == ORDER_SUCCESS);
        const Email client_email = escaperGetEmailByRef(client);
        ASSERT_TEST(escaperGetLevel(client, &client_skill) == ESCAPER_SUCCESS);
        ASSERT_TEST(escaperGetFaculty(client, &client_faculty) == ESCAPER_SUCCESS);
        ASSERT_TEST(orderGetRoom(iterator2, &order_room) == ORDER_SUCCESS);
        ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
        ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
        const Email company_email = roomGetEmailbyRef(order_room);
        ASSERT_TEST(orderGetFaculty(iterator2, &order_faculty) == ORDER_SUCCESS);
        ASSERT_TEST(orderGetTime(iterator2, &order_day, &order_hour) == ORDER_SUCCESS);
        ASSERT_TEST(orderGetPrice(iterator2, &order_price) == ORDER_SUCCESS);
        ASSERT_TEST(orderGetNumPeople(iterator2, &order_people) == ORDER_SUCCESS);
        mtmPrintOrder(stdout,client_email,client_skill,client_faculty,company_email,order_faculty,order_room_id,order_hour,order_room_level,order_people,order_price);
    }
    mtmPrintDayFooter(stdout,current_day);
    listDestroy(today_order);
    today_order=NULL;
    ASSERT_TEST(systemEscaperOrder(my_system,"esc8@g.com",13,2,0,17,4)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetDay(my_system, &current_day) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetRevenue(my_system, &total_revenue) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemReportBest(my_system,&best)==SYSTEM_SUCCESS);
    mtmPrintFacultiesHeader(stdout,UNKNOWN,current_day,total_revenue);
    iterator=listGetFirst(best);
    for(int i=0;i<3;i++){
        Price current_rev;
        TechnionFaculty current_id;
        ASSERT_TEST(facultyGetTotalRevenue(iterator,&current_rev)==FACULTY_SUCCESS);
        ASSERT_TEST(facultyGetID(iterator,&current_id)==FACULTY_SUCCESS);
        mtmPrintFaculty(stdout,current_id,current_rev);
        iterator=listGetNext(best);
    }
    listDestroy(best);
    best=NULL;
ASSERT_TEST(systemEscaperRecommend(my_system,"esc3@g.com",3)==SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetDay(my_system, &current_day) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemReportDay(my_system,&today_order)==SYSTEM_SUCCESS);
    mtmPrintDayHeader(stdout,current_day,listGetSize(today_order));
    LIST_FOREACH(Order,iterator2,today_order){
        Time order_hour;
        TechnionFaculty order_faculty;
        Room order_room = NULL;
        Id order_room_id;
        Num_People order_people;
        Price order_price;
        Level order_room_level;
        Level client_skill;
        Escaper client = NULL;
        TechnionFaculty client_faculty;
        Day order_day;
        ASSERT_TEST(iterator2!=NULL);
        ASSERT_TEST(orderGetEscaper(iterator2, &client) == ORDER_SUCCESS);
        const Email client_email = escaperGetEmailByRef(client);
        ASSERT_TEST(escaperGetLevel(client, &client_skill) == ESCAPER_SUCCESS);
        ASSERT_TEST(escaperGetFaculty(client, &client_faculty) == ESCAPER_SUCCESS);
        ASSERT_TEST(orderGetRoom(iterator2, &order_room) == ORDER_SUCCESS);
        ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
        ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
        const Email company_email = roomGetEmailbyRef(order_room);
        ASSERT_TEST(orderGetFaculty(iterator2, &order_faculty) == ORDER_SUCCESS);
        ASSERT_TEST(orderGetTime(iterator2, &order_day, &order_hour) == ORDER_SUCCESS);
        ASSERT_TEST(orderGetPrice(iterator2, &order_price) == ORDER_SUCCESS);
        ASSERT_TEST(orderGetNumPeople(iterator2, &order_people) == ORDER_SUCCESS);
        mtmPrintOrder(stdout,client_email,client_skill,client_faculty,company_email,order_faculty,order_room_id,order_hour,order_room_level,order_people,order_price);
    }
    mtmPrintDayFooter(stdout,current_day);
    listDestroy(today_order);
    today_order=NULL;
    ASSERT_TEST(systemGetDay(my_system, &current_day) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemReportDay(my_system,&today_order)==SYSTEM_SUCCESS);
    mtmPrintDayHeader(stdout,current_day,listGetSize(today_order));
    LIST_FOREACH(Order,iterator2,today_order){
        Time order_hour;
        TechnionFaculty order_faculty;
        Room order_room = NULL;
        Id order_room_id;
        Num_People order_people;
        Price order_price;
        Level order_room_level;
        Level client_skill;
        Escaper client = NULL;
        TechnionFaculty client_faculty;
        Day order_day;
        ASSERT_TEST(iterator2!=NULL);
        ASSERT_TEST(orderGetEscaper(iterator2, &client) == ORDER_SUCCESS);
        const Email client_email = escaperGetEmailByRef(client);
        ASSERT_TEST(escaperGetLevel(client, &client_skill) == ESCAPER_SUCCESS);
        ASSERT_TEST(escaperGetFaculty(client, &client_faculty) == ESCAPER_SUCCESS);
        ASSERT_TEST(orderGetRoom(iterator2, &order_room) == ORDER_SUCCESS);
        ASSERT_TEST(roomGetId(order_room, &order_room_id) == ROOM_SUCCESS);
        ASSERT_TEST(roomGetLevel(order_room, &order_room_level) == ROOM_SUCCESS);
        const Email company_email = roomGetEmailbyRef(order_room);
        ASSERT_TEST(orderGetFaculty(iterator2, &order_faculty) == ORDER_SUCCESS);
        ASSERT_TEST(orderGetTime(iterator2, &order_day, &order_hour) == ORDER_SUCCESS);
        ASSERT_TEST(orderGetPrice(iterator2, &order_price) == ORDER_SUCCESS);
        ASSERT_TEST(orderGetNumPeople(iterator2, &order_people) == ORDER_SUCCESS);
        mtmPrintOrder(stdout,client_email,client_skill,client_faculty,company_email,order_faculty,order_room_id,order_hour,order_room_level,order_people,order_price);
    }
    mtmPrintDayFooter(stdout,current_day);
    listDestroy(today_order);
    today_order=NULL;
    ASSERT_TEST(systemGetDay(my_system, &current_day) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemGetRevenue(my_system, &total_revenue) == SYSTEM_SUCCESS);
    ASSERT_TEST(systemReportBest(my_system,&best)==SYSTEM_SUCCESS);
    mtmPrintFacultiesHeader(stdout,UNKNOWN,current_day,total_revenue);
    iterator=listGetFirst(best);
    for(int i=0;i<3;i++){
        Price current_rev;
        TechnionFaculty current_id;
        ASSERT_TEST(facultyGetTotalRevenue(iterator,&current_rev)==FACULTY_SUCCESS);
        ASSERT_TEST(facultyGetID(iterator,&current_id)==FACULTY_SUCCESS);
        mtmPrintFaculty(stdout,current_id,current_rev);
        iterator=listGetNext(best);
    }
    listDestroy(best);
    best=NULL;
    systemDestroy(my_system);
    return true;
}

int main(){
    RUN_TEST(testSystemCreate);
    RUN_TEST(testSystemReportDay);
    return 0;
}