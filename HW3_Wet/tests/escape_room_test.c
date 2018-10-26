#include "test_utilities.h"
#include "../set.h"
#include "../escape_room.h"
#include <string.h>

#define EQUAL 0
#define NEGATIVE -1
#define BAD_LEVEL1 11
#define BAD_PRICE1 -4
#define BAD_PRICE2 7
#define POSITIVE 5
#define GOOD_EMAIL1 "facebook@"
#define GOOD_EMAIL2 "mellanox@"
#define GOOD_LEVEL 2
#define GOOD_PRICE 32
#define OPEN_HOUR 5
#define CLOSE_HOUR 13
#define ID1 11
#define ID2 22

static bool testRoomCreate() {
    Room room=roomCreate();
    ASSERT_TEST(room!= NULL);
    roomDestroy(room);
    return true;
}

static Room buildRoomForTests(){
    Room my_room=roomCreate();
    ASSERT_TEST(my_room!=NULL);
    Company temp=companyCreate();
    ASSERT_TEST(temp!= NULL);
    ASSERT_TEST(companySetEmail(temp,GOOD_EMAIL1)==COMPANY_SUCCESS);
    ASSERT_TEST(roomSetEmailFromCompany(my_room,temp)==ROOM_SUCCESS);
    companyDestroy(temp);
    ASSERT_TEST(roomSetId(my_room,ID1)==ROOM_SUCCESS);
    ASSERT_TEST(roomSetPrice(my_room,GOOD_PRICE)==ROOM_SUCCESS);
    ASSERT_TEST(roomSetLevel(my_room,GOOD_LEVEL)==ROOM_SUCCESS);
    ASSERT_TEST(roomSetNumPeople(my_room,POSITIVE)==ROOM_SUCCESS);
    ASSERT_TEST(roomSetWorkingHours(my_room,OPEN_HOUR,CLOSE_HOUR)==ROOM_SUCCESS);
    return my_room;
}

static bool testRoomSetEmail(){
    Room my_room=buildRoomForTests();
    ASSERT_TEST(my_room!= NULL);
    Company temp=companyCreate();
    ASSERT_TEST(temp!= NULL);
    ASSERT_TEST(roomSetEmailFromCompany(my_room,NULL)==ROOM_NULL_PARAMETER);
    ASSERT_TEST(companySetEmail(temp,GOOD_EMAIL2)==COMPANY_SUCCESS);
    ASSERT_TEST(roomSetEmailFromCompany(my_room,temp)==ROOM_SUCCESS);
    companyDestroy(temp);
    const Email output= roomGetEmailR(my_room);
    ASSERT_TEST(strcmp(output,GOOD_EMAIL2)==EQUAL);
    roomDestroy(my_room);
    return true;
}

static bool testRoomGetEmailByRef() {
    Room my_room=buildRoomForTests();
    ASSERT_TEST(my_room!= NULL);
    const Email output= roomGetEmailR(my_room);
    ASSERT_TEST(strcmp(output,GOOD_EMAIL1)==EQUAL);
    roomDestroy(my_room);
    return true;
}


static bool testRoomSetNumPeople() {
    Room room=buildRoomForTests();
    ASSERT_TEST(room != NULL);
    ASSERT_TEST(roomSetNumPeople(room,NEGATIVE) == ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetNumPeople(room,0) == ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetNumPeople(room,POSITIVE+4) == ROOM_SUCCESS);
    Occapancy output;
    ASSERT_TEST(roomGetNumPeople(room, &output) == ROOM_SUCCESS);
    ASSERT_TEST(output == POSITIVE+4);
    roomDestroy(room);
    return true;
}

static bool testRoomGetNumPeople(){
    Room my_room=buildRoomForTests();
    ASSERT_TEST(my_room!= NULL);
    Occapancy output;
    ASSERT_TEST(roomGetNumPeople(my_room,NULL)==ROOM_NULL_PARAMETER);
    ASSERT_TEST(my_room!= NULL);
    ASSERT_TEST(roomGetNumPeople(my_room,&output)==ROOM_SUCCESS);
    ASSERT_TEST(output==POSITIVE);
    roomDestroy(my_room);
    return true;
}

static bool testRoomSetPrice(){
    Room my_room=buildRoomForTests();
    ASSERT_TEST(my_room!=NULL);
    ASSERT_TEST(roomSetPrice(my_room,BAD_PRICE1)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetPrice(my_room,BAD_PRICE2)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetPrice(my_room,GOOD_PRICE+4)==ROOM_SUCCESS);
    Room_Price output;
    ASSERT_TEST(roomGetPrice(my_room,&output)==ROOM_SUCCESS);
    ASSERT_TEST(output==GOOD_PRICE+4);
    roomDestroy(my_room);
   return true;
}

static bool testRoomGetPrice(){
    Room my_room=buildRoomForTests();
    Room_Price output;
    ASSERT_TEST(my_room!=NULL);
    ASSERT_TEST(roomGetPrice(my_room,NULL)==ROOM_NULL_PARAMETER);
    ASSERT_TEST(roomGetPrice(my_room,&output)==ROOM_SUCCESS);
    ASSERT_TEST(output==GOOD_PRICE);
    roomDestroy(my_room);
    return true;
}

static bool testRoomSetId(){
    Room my_room=buildRoomForTests();
    ASSERT_TEST(my_room!=NULL);
    ASSERT_TEST(roomSetId(my_room,0)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetId(my_room,NEGATIVE)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetId(my_room,ID2)==ROOM_SUCCESS);
    Room_Id output;
    ASSERT_TEST(roomGetId(my_room,&output)==ROOM_SUCCESS);
    ASSERT_TEST(output==ID2);
    roomDestroy(my_room);
    return true;
}

static bool testRoomGetId(){
    Room my_room=buildRoomForTests();
    Room_Price output;
    ASSERT_TEST(my_room!=NULL);
    ASSERT_TEST(roomGetId(my_room,NULL)==ROOM_NULL_PARAMETER);
    ASSERT_TEST(roomGetId(my_room,&output)==ROOM_SUCCESS);
    ASSERT_TEST(output==ID1);
    roomDestroy(my_room);
    return true;
}

static bool testRoomSetLevel(){
    Room my_room=buildRoomForTests();
    ASSERT_TEST(my_room!=NULL);
    ASSERT_TEST(roomSetLevel(my_room, 0)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetLevel(my_room, NEGATIVE)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetLevel(my_room, BAD_LEVEL1)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetLevel(my_room, GOOD_LEVEL+3)==ROOM_SUCCESS);
    Difficulty output;
    ASSERT_TEST(roomGetLevel(my_room,&output)==ROOM_SUCCESS);
    ASSERT_TEST(output==GOOD_LEVEL+3);
    roomDestroy(my_room);
    return true;
}

static bool testRoomGetLevel(){
    Room my_room=buildRoomForTests();
    Difficulty output;
    ASSERT_TEST(my_room!=NULL);
    ASSERT_TEST(roomGetLevel(my_room,NULL)==ROOM_NULL_PARAMETER);
    ASSERT_TEST(roomGetLevel(my_room,&output)==ROOM_SUCCESS);
    ASSERT_TEST(output==GOOD_LEVEL);
    roomDestroy(my_room);
    return true;
}

static bool testRoomSetWorkingHours(){
    Room my_room=buildRoomForTests();
    ASSERT_TEST(my_room!=NULL);
    ASSERT_TEST(roomSetWorkingHours(my_room,25,-1)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetWorkingHours(my_room,-2,-1)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetWorkingHours(my_room,24,1)==ROOM_ILLEGAL_PARAMETERS);
    ASSERT_TEST(roomSetWorkingHours(my_room,OPEN_HOUR+1,CLOSE_HOUR+1)==ROOM_SUCCESS);
    Time start_hour;
    Time close_hour;
    ASSERT_TEST(roomGetWorkingHours(my_room,&start_hour,&close_hour)==ROOM_SUCCESS);
    ASSERT_TEST(start_hour==OPEN_HOUR+1&&close_hour==CLOSE_HOUR+1);
    roomDestroy(my_room);
    return true;
}

static bool testRoomGetWorkingHours(){
    Room my_room=buildRoomForTests();
    Time start_hour;
    Time close_hour;
    ASSERT_TEST(my_room!=NULL);
    ASSERT_TEST(roomGetWorkingHours(my_room,NULL,&close_hour)==ROOM_NULL_PARAMETER);
    ASSERT_TEST(roomGetWorkingHours(my_room,&start_hour,NULL)==ROOM_NULL_PARAMETER);
    ASSERT_TEST(roomGetWorkingHours(my_room,&start_hour,&close_hour)==ROOM_SUCCESS);
    ASSERT_TEST(start_hour==OPEN_HOUR&&close_hour==CLOSE_HOUR);
    roomDestroy(my_room);
    return true;
}

static bool testRoomCompare(){
    Room room1=buildRoomForTests();
    Room room2=buildRoomForTests();
    ASSERT_TEST(roomSetId(room2,ID2)==ROOM_SUCCESS);
    ASSERT_TEST(roomCompare(room1,room2)<EQUAL);
    ASSERT_TEST(roomCompare(room2,room1)>EQUAL);
    ASSERT_TEST(roomSetId(room2,ID1)==ROOM_SUCCESS);
    ASSERT_TEST(roomCompare(room1,room2)==EQUAL);
    roomDestroy(room1);
    roomDestroy(room2);
    return true;
}

static bool testRoomDestroy() {
    roomDestroy(NULL);
    Room room=roomCreate();
    roomDestroy(room);
    room=buildRoomForTests();
    roomDestroy(room);
    return true;
}

static bool testRoomCopy() {
    Room my_room=roomCreate();
    ASSERT_TEST(my_room!=NULL);
    Room room_copy=roomCopy(my_room);
    ASSERT_TEST(room_copy==NULL);
    Company temp=companyCreate();
    ASSERT_TEST(temp!= NULL);
    ASSERT_TEST(companySetEmail(temp,GOOD_EMAIL1)==COMPANY_SUCCESS);
    ASSERT_TEST(roomSetEmailFromCompany(my_room,temp)==ROOM_SUCCESS);
    companyDestroy(temp);
    room_copy=roomCopy(my_room);
    ASSERT_TEST(room_copy==NULL);
    ASSERT_TEST(roomSetId(my_room,ID1)==ROOM_SUCCESS);
    room_copy=roomCopy(my_room);
    ASSERT_TEST(room_copy==NULL);
    ASSERT_TEST(roomSetPrice(my_room,GOOD_PRICE)==ROOM_SUCCESS);
    room_copy=roomCopy(my_room);
    ASSERT_TEST(room_copy==NULL);
    ASSERT_TEST(roomSetNumPeople(my_room,POSITIVE)==ROOM_SUCCESS);
    room_copy=roomCopy(my_room);
    ASSERT_TEST(room_copy==NULL);
    ASSERT_TEST(roomSetWorkingHours(my_room,OPEN_HOUR,CLOSE_HOUR)==ROOM_SUCCESS);
    room_copy=roomCopy(my_room);
    ASSERT_TEST(room_copy==NULL);
    roomDestroy(my_room);
    my_room=buildRoomForTests();
    //here the my_room source is legal my_room
    room_copy=roomCopy(my_room);
    ASSERT_TEST(room_copy!=NULL);
    Room_Id output_id;
    Room_Price output_price;
    Occapancy output_ppl;
    Difficulty output_level;
    int start;
    int close;
    const Email output= roomGetEmailR(my_room);
    ASSERT_TEST(strcmp(output,GOOD_EMAIL1)==EQUAL);
    ASSERT_TEST(roomGetId(room_copy,&output_id)==ROOM_SUCCESS);
    ASSERT_TEST(output_id==ID1);
    ASSERT_TEST(roomGetNumPeople(room_copy,&output_ppl)==ROOM_SUCCESS);
    ASSERT_TEST(output_ppl==POSITIVE);
    ASSERT_TEST(roomGetPrice(room_copy,&output_price)==ROOM_SUCCESS);
    ASSERT_TEST(output_price==GOOD_PRICE);
    ASSERT_TEST(roomGetLevel(room_copy,&output_level)==ROOM_SUCCESS);
    ASSERT_TEST(output_level==GOOD_LEVEL);
    ASSERT_TEST(roomGetWorkingHours(room_copy,&start,&close)==ROOM_SUCCESS);
    ASSERT_TEST(start==OPEN_HOUR&&close==CLOSE_HOUR);
    roomDestroy(my_room);
    roomDestroy(room_copy);
    return true;
}

static bool testRoomRank(){
    Room room=buildRoomForTests();
    Rank output;
    Client ido=clientCreate();
    ASSERT_TEST(ido!=NULL);
    ASSERT_TEST(clientSetLevel(ido,3)==CLIENT_SUCCESS);
    ASSERT_TEST(roomClientRank(room,NULL,POSITIVE,NULL)==ROOM_NULL_PARAMETER);
    ASSERT_TEST(roomClientRank(room, ido, POSITIVE, NULL)==ROOM_NULL_PARAMETER);
    ASSERT_TEST(roomClientRank(room, ido, 4, &output)==ROOM_SUCCESS);
    ASSERT_TEST(output==2);
    roomDestroy(room);
    clientDestroy(ido);
    return true;
}

/************test the behavior of room in set*************/
static bool testRoomInSet(){
    Room room1=buildRoomForTests();
    Room room2=buildRoomForTests();
    Set two= setCreate(roomCopy, roomDestroy, roomCompare);
    ASSERT_TEST(two!=NULL);
    ASSERT_TEST(setAdd(two,room1)==SET_SUCCESS);
    ASSERT_TEST(setAdd(two,room2)==SET_ITEM_ALREADY_EXISTS);
    ASSERT_TEST(roomSetId(room2,ID2)==ROOM_SUCCESS);
    ASSERT_TEST(setAdd(two,room2)==SET_SUCCESS);
    roomDestroy(room1);//make sure room inserted by copy
    roomDestroy(room2);
    Room new_room=buildRoomForTests();
    ASSERT_TEST(setIsIn(two,new_room));
    SET_FOREACH(Room,iterator,two){
        Room_Id output_id;
        ASSERT_TEST(roomGetId(iterator,&output_id)==ROOM_SUCCESS);
        ASSERT_TEST(output_id==ID1||output_id==ID2);
    }
    ASSERT_TEST(setRemove(two,new_room)==SET_SUCCESS);
    ASSERT_TEST(setIsIn(two,new_room)==false);
    roomDestroy(new_room);
    setDestroy(two);
    return true;
}
int main(int argv, char **arc) {
    RUN_TEST(testRoomCreate);
    RUN_TEST(testRoomSetEmail);
    RUN_TEST(testRoomGetEmailByRef);
    RUN_TEST(testRoomSetNumPeople);
    RUN_TEST(testRoomGetNumPeople);
    RUN_TEST(testRoomSetPrice);
    RUN_TEST(testRoomGetPrice);
    RUN_TEST(testRoomSetId);
    RUN_TEST(testRoomGetId);
    RUN_TEST(testRoomSetLevel);
    RUN_TEST(testRoomGetLevel);
    RUN_TEST(testRoomSetWorkingHours);
    RUN_TEST(testRoomGetWorkingHours);
    RUN_TEST(testRoomCompare);
    RUN_TEST(testRoomDestroy);
    RUN_TEST(testRoomCopy);
    RUN_TEST(testRoomRank);
    RUN_TEST(testRoomInSet);
    return 0;
}