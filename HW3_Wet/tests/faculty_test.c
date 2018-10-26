#include "test_utilities.h"
#include "../faculty.h"

#define BAD_FACULTY -1
#define EQUEL 0
#define ZERO 0
#define TODAY 0
#define TOMORROW 1
#define POSITIVE 1
#define GOOD_PRICE 100
#define GOOD_LEVEL 1
#define OPEN 10
#define OPEN1 11
#define GOOD_EMAIL1 "facebook@"
#define USER_EMAIL1 "ido@"
#define USER_EMAIL2 "shlomi@"
#define CLOSE 23
#define ID1 11
#define ID2 22


static bool testFacultyCreate(){
    Faculty my_faculty=facultyCreate(UNKNOWN);
    ASSERT_TEST(my_faculty==NULL);
    my_faculty=facultyCreate(BAD_FACULTY);
    ASSERT_TEST(my_faculty==NULL);
    my_faculty=facultyCreate(ELECTRICAL_ENGINEERING);
    ASSERT_TEST(my_faculty!=NULL);
    facultyDestroy(my_faculty);
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
    ASSERT_TEST(roomSetLevel(my_room, GOOD_LEVEL) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetNumPeople(my_room, POSITIVE) == ROOM_SUCCESS);
    ASSERT_TEST(
            roomSetWorkingHours(my_room, OPEN, CLOSE) == ROOM_SUCCESS);
    return my_room;
}

static Client buildClientForTests(){
    Client my_client=clientCreate();
    ASSERT_TEST(my_client!=NULL);
    ASSERT_TEST(clientSetEmail(my_client,USER_EMAIL1)==CLIENT_SUCCESS);
    ASSERT_TEST(clientSetFaculty(my_client,ELECTRICAL_ENGINEERING)==CLIENT_SUCCESS);
    ASSERT_TEST(clientSetLevel(my_client,GOOD_LEVEL)==CLIENT_SUCCESS);
    return my_client;
}


static bool testFacultyAddRoomAndRemoveRoom() {
    Room room1 = buildRoomForTests();
    Room room2 = buildRoomForTests();
    Room room3 = buildRoomForTests();
    ASSERT_TEST(room1 != NULL && room2 != NULL && room3 != NULL);
    ASSERT_TEST(roomSetId(room2, ID2) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetNumPeople(room2, POSITIVE+1) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetLevel(room2, GOOD_LEVEL+1) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetPrice(room2, 2*GOOD_PRICE) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetWorkingHours(room2, 2, 24) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetId(room3, ID1) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetNumPeople(room3, POSITIVE+2) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetLevel(room3, GOOD_LEVEL+2) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetPrice(room3, GOOD_PRICE*3) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetWorkingHours(room3, 3, 24) == ROOM_SUCCESS);
    Faculty my_faculty = facultyCreate(CHEMISTRY);
    ASSERT_TEST(my_faculty != NULL);
    ASSERT_TEST(facultyAddRoom(my_faculty, NULL) == FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyAddRoom(my_faculty, room1) == FACULTY_SUCCESS);
    ASSERT_TEST(roomCompare(room1, room3) == EQUEL);
    roomDestroy(room1);
    ASSERT_TEST(facultyAddRoom(my_faculty, room3) == FACULTY_ROOM_ALREADY_IN);
    ASSERT_TEST(facultyAddRoom(my_faculty, room2) == FACULTY_SUCCESS);
    roomDestroy(room2);
    ASSERT_TEST(facultyRemoveRoom(my_faculty, POSITIVE) == FACULTY_ROOM_NOT_EXIST);
    ASSERT_TEST(facultyRemoveRoom(my_faculty, ID1) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddRoom(my_faculty, room3) == FACULTY_SUCCESS);
    roomDestroy(room3);
    ASSERT_TEST(facultyRemoveCompanyRooms(my_faculty,NULL)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyRemoveCompanyRooms(my_faculty,GOOD_EMAIL1)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyRemoveRoom(my_faculty,ID2)==FACULTY_ROOM_NOT_EXIST);
    facultyDestroy(my_faculty);
    return true;
}

static bool testFacultyOrdersSystem() {
    Room room1 = buildRoomForTests();
    ASSERT_TEST(roomSetWorkingHours(room1,OPEN,CLOSE)== ROOM_SUCCESS);
    Faculty my_faculty = facultyCreate(CHEMISTRY);
    ASSERT_TEST(my_faculty != NULL);
    Client ido = buildClientForTests();
    Client shlomi = buildClientForTests();
    ASSERT_TEST(ido != NULL);
    ASSERT_TEST(clientSetEmail(ido,USER_EMAIL2) == CLIENT_SUCCESS);
    ASSERT_TEST(clientSetFaculty(shlomi, CHEMISTRY) == CLIENT_SUCCESS);
    ASSERT_TEST(clientSetLevel(ido, GOOD_LEVEL+4) == CLIENT_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty, NULL, POSITIVE,POSITIVE,OPEN,POSITIVE)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyAddOrder(my_faculty, ido, ID2, POSITIVE, OPEN, POSITIVE) ==FACULTY_ROOM_NOT_EXIST);
    ASSERT_TEST(facultyAddRoom(my_faculty, room1) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty, ido, ID1,TODAY,9,POSITIVE)==FACULTY_ORDER_CANNOT_SET);
    ASSERT_TEST(facultyClientCanSetOrder(my_faculty, NULL, TODAY, OPEN)==FACULTY_NULL_PARAMETER);
	ASSERT_TEST(facultyClientCanSetOrder(my_faculty, ido, TODAY, OPEN)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty, ido,ID1,TODAY,OPEN,POSITIVE)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyClientCanSetOrder(my_faculty, shlomi, TODAY, OPEN)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty, shlomi,ID1,TODAY,OPEN,POSITIVE)==FACULTY_ORDER_CANNOT_SET);
    ASSERT_TEST(facultyAddOrder(my_faculty, shlomi,ID1,TODAY,CLOSE,POSITIVE)==FACULTY_ORDER_CANNOT_SET);
    ASSERT_TEST(facultyAddOrder(my_faculty, shlomi,ID1,TODAY,OPEN1,POSITIVE)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyRemoveRoom(my_faculty,ID1)==FACULTY_ROOM_CANNOT_REMOVED);
    ASSERT_TEST(facultyRemoveCompanyRooms(my_faculty,"mellanox@")==FACULTY_SUCCESS);
    ASSERT_TEST(facultyRemoveCompanyRooms(my_faculty,GOOD_EMAIL1) ==FACULTY_COMPANY_CANNOT_REMOVED);
    ASSERT_TEST(facultyRemoveOrdersOfClient(my_faculty,NULL)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyRemoveOrdersOfClient(my_faculty,ido)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyRemoveOrdersOfClient(my_faculty,shlomi)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyRemoveCompanyRooms(my_faculty,GOOD_EMAIL1)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty, shlomi,ID1,TODAY,OPEN1,POSITIVE)
                ==FACULTY_ROOM_NOT_EXIST);
    ASSERT_TEST(facultyAddRoom(my_faculty, room1) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty, shlomi,ID1,TODAY,OPEN1,POSITIVE)==FACULTY_SUCCESS);
    roomDestroy(room1);
    clientDestroy(ido);
    clientDestroy(shlomi);
    facultyDestroy(my_faculty);
    return true;
}


static bool testRecommendedRoom(){
    Room room1 = buildRoomForTests();
    ASSERT_TEST(roomSetWorkingHours(room1,OPEN,CLOSE) == ROOM_SUCCESS);
    Room room2 = buildRoomForTests();
    ASSERT_TEST(roomSetId(room2,ID2) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetWorkingHours(room2,OPEN,12) == ROOM_SUCCESS);
    Faculty my_faculty = facultyCreate(CHEMISTRY);
    ASSERT_TEST(my_faculty != NULL);
    Client ido = buildClientForTests();
    ASSERT_TEST(clientSetLevel(ido,GOOD_LEVEL+4)==CLIENT_SUCCESS);
    Rank best_rank=ZERO;
    Room_Id room_id=ZERO;
    ASSERT_TEST(facultyGetRecommendedRoom(my_faculty,ido,POSITIVE,&best_rank,&room_id)==FACULTY_ROOM_NOT_EXIST);
    ASSERT_TEST(facultyAddRoom(my_faculty, room1) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddRoom(my_faculty, room2) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyGetRecommendedRoom(my_faculty,NULL,POSITIVE,&best_rank,&room_id)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyGetRecommendedRoom(my_faculty,ido,POSITIVE,NULL,&room_id)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyGetRecommendedRoom(my_faculty,ido,POSITIVE,&best_rank,NULL)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyGetRecommendedRoom(my_faculty,ido,POSITIVE,&best_rank,&room_id)==FACULTY_SUCCESS);
    ASSERT_TEST(best_rank==16);
    ASSERT_TEST(room_id==ID1);
    ASSERT_TEST(facultyRemoveRoom(my_faculty,ID1)==FACULTY_SUCCESS);
    ASSERT_TEST(roomSetNumPeople(room1, POSITIVE+4) == ROOM_SUCCESS);
    ASSERT_TEST(facultyAddRoom(my_faculty, room1) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyGetRecommendedRoom(my_faculty,ido,POSITIVE,&best_rank,&room_id)==FACULTY_SUCCESS);
    ASSERT_TEST(best_rank==16);
    ASSERT_TEST(room_id==ID2);
    ASSERT_TEST(facultyOrderRecommendedRoom(my_faculty,NULL,ZERO)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyAddOrder(my_faculty,ido,ID2,TODAY,OPEN,POSITIVE+1)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty,ido,ID2,TODAY,OPEN1,POSITIVE+1)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyOrderRecommendedRoom(my_faculty,ido,POSITIVE+1)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyClientCanSetOrder(my_faculty, ido, TOMORROW, OPEN)==FACULTY_ORDER_CANNOT_SET);
    roomDestroy(room1);
    roomDestroy(room2);
    clientDestroy(ido);
    facultyDestroy(my_faculty);
    return true;
}

static bool testEndOfDay(){
    Room room1 = buildRoomForTests();
    ASSERT_TEST(roomSetWorkingHours(room1,OPEN,CLOSE) == ROOM_SUCCESS);
    Room room2 = buildRoomForTests();
    ASSERT_TEST(roomSetId(room2,ID2) == ROOM_SUCCESS);
    ASSERT_TEST(roomSetWorkingHours(room2,OPEN,12) == ROOM_SUCCESS);
    Faculty my_faculty = facultyCreate(CHEMISTRY);
    ASSERT_TEST(my_faculty != NULL);
    List today_order=NULL;
    Revenue output;
    ASSERT_TEST(facultyEndOfDay(my_faculty,&output,&today_order)==FACULTY_SUCCESS);
    ASSERT_TEST(listGetSize(today_order)==0);
    listDestroy(today_order);
    today_order=NULL;
    Client ido = buildClientForTests();
    ASSERT_TEST(clientSetLevel(ido,GOOD_LEVEL+4)==CLIENT_SUCCESS);
    ASSERT_TEST(facultyAddRoom(my_faculty, room1) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddRoom(my_faculty, room2) == FACULTY_SUCCESS);
    roomDestroy(room1);
    roomDestroy(room2);
    ASSERT_TEST(facultyAddOrder(my_faculty,ido,ID1,TODAY,OPEN,POSITIVE+1)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty,ido,ID1,TODAY,OPEN1,POSITIVE)
                ==FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty,ido,ID2,TOMORROW,OPEN,POSITIVE)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty,ido,ID2,TOMORROW,OPEN1,POSITIVE)
                ==FACULTY_SUCCESS);
    ASSERT_TEST(facultyGetRevenueDay(my_faculty,NULL)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyGetRevenueDay(my_faculty,&output)==FACULTY_SUCCESS);
    ASSERT_TEST(output==3*GOOD_PRICE);
    ASSERT_TEST(facultyEndOfDay(my_faculty,NULL,&today_order)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyEndOfDay(my_faculty,&output,NULL)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyEndOfDay(my_faculty,&output,&today_order)==FACULTY_SUCCESS);
    ASSERT_TEST(output==3*GOOD_PRICE);
    ASSERT_TEST(facultyGetTotalRevenue(my_faculty,NULL)==FACULTY_NULL_PARAMETER);
    ASSERT_TEST(facultyGetTotalRevenue(my_faculty,&output)==FACULTY_SUCCESS);
    ASSERT_TEST(output==3*GOOD_PRICE);
    ASSERT_TEST(listGetSize(today_order)==2);
    listDestroy(today_order);
    today_order=NULL;
    ASSERT_TEST(facultyEndOfDay(my_faculty,&output,&today_order)==FACULTY_SUCCESS);
    ASSERT_TEST(output==2*GOOD_PRICE);
    ASSERT_TEST(listGetSize(today_order)==2);
    ASSERT_TEST(facultyGetTotalRevenue(my_faculty,&output)==FACULTY_SUCCESS);
    ASSERT_TEST(output==5*GOOD_PRICE);
    listDestroy(today_order);
    facultyDestroy(my_faculty);
    clientDestroy(ido);
    return true;
}

bool testFacultyCompare(){
    Faculty faculty1=facultyCreate(ELECTRICAL_ENGINEERING);
    Faculty faculty2=facultyCreate(ELECTRICAL_ENGINEERING);
    Faculty faculty3=facultyCreate(CIVIL_ENGINEERING);
    ASSERT_TEST(faculty1!=NULL&&faculty2!=NULL&&faculty3!=NULL);
    ASSERT_TEST(facultyCompareByRevAndID(faculty1, faculty2)==EQUEL);
    ASSERT_TEST(facultyCompareByRevAndID(faculty1, faculty3)>EQUEL);
    ASSERT_TEST(facultyCompareByRevAndID(faculty3, faculty1)<EQUEL);
    facultyDestroy(faculty1);
    facultyDestroy(faculty2);
    facultyDestroy(faculty3);
    return true;
}

static bool testFacultyCopy(){
    Faculty my_faculty=facultyCreate(ELECTRICAL_ENGINEERING);
    ASSERT_TEST(my_faculty!=NULL);
    Room room1=buildRoomForTests();
    Room room2=buildRoomForTests();
    ASSERT_TEST(roomSetId(room2,ID2)==ROOM_SUCCESS);
    Client ido=buildClientForTests();
    ASSERT_TEST(facultyAddRoom(my_faculty, room1) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddRoom(my_faculty, room2) == FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty,ido,ID1,TODAY,OPEN,POSITIVE)==FACULTY_SUCCESS);
    ASSERT_TEST(facultyAddOrder(my_faculty,ido,ID2,TODAY,OPEN1,POSITIVE) ==FACULTY_SUCCESS);
    Faculty copy_faculty= facultyCopy(my_faculty);
    ASSERT_TEST(copy_faculty!=NULL);
    facultyDestroy(my_faculty);
    ASSERT_TEST(facultyAddRoom(copy_faculty,room1)==FACULTY_ROOM_ALREADY_IN);
    ASSERT_TEST(facultyAddRoom(copy_faculty,room2)==FACULTY_ROOM_ALREADY_IN);
    ASSERT_TEST(facultyClientCanSetOrder(copy_faculty, ido, TODAY, OPEN)==FACULTY_ORDER_CANNOT_SET);
    ASSERT_TEST(facultyClientCanSetOrder(copy_faculty, ido, TODAY, OPEN1)==FACULTY_ORDER_CANNOT_SET);
    ASSERT_TEST(facultyClientCanSetOrder(copy_faculty, ido, TOMORROW, OPEN1)==FACULTY_SUCCESS);
    facultyDestroy(copy_faculty);
    roomDestroy(room1);
    roomDestroy(room2);
    clientDestroy(ido);
    return true;
}

int main(){
    RUN_TEST(testFacultyCreate);
    RUN_TEST(testFacultyAddRoomAndRemoveRoom);
    RUN_TEST(testFacultyOrdersSystem);
    RUN_TEST(testRecommendedRoom);
    RUN_TEST(testEndOfDay);
    RUN_TEST(testFacultyCompare);
    RUN_TEST(testFacultyCopy);
    return 0;
}


