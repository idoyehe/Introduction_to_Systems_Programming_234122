#include "../KidsRoom.h"
#include "../mtmtest.h"
#include "../Exceptions.h"

#define NAME "ROOM1"
#define MAX_TIME 40
#define LEVEL 5
#define MAX_PAR 5
#define AGE 10
#define OUTPUT "Kids Room: ROOM1 (40/5/5/10)"
#define KIDS_ROOM "KIDS_ROOM"

using namespace mtm::escaperoom;


static void testConstructor(){
    std::string room_name = NAME;
    ASSERT_NO_THROW(KidsRoom((char*)NAME,MAX_TIME,LEVEL,MAX_PAR,AGE));
    KidsRoom room1((char*) NAME,MAX_TIME,LEVEL,MAX_PAR,AGE);
    ASSERT_EQUALS(room1.getName(),room_name);
    ASSERT_EQUALS(room1.getMaxParticipants(),MAX_PAR);
    ASSERT_EQUALS(room1.getMaxTime(),MAX_TIME);
    ASSERT_EQUALS(room1.level(),LEVEL);
    ASSERT_EQUALS(room1.getAgeLimit(),AGE);
}

static void testCopyConstructor(){
    KidsRoom room2((char *) NAME, MAX_TIME, LEVEL, MAX_PAR,AGE);
    set<string> my_elements;
    my_elements.insert("IDO");
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c++", HARD_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c", EASY_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c#", MEDIUM_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("bash", EASY_ENIGMA, 1, my_elements)));
    KidsRoom room1(room2);
    ASSERT_EQUALS(room1.getName(), NAME);
    ASSERT_EQUALS(room1.getMaxParticipants(), MAX_PAR);
    ASSERT_EQUALS(room1.getMaxTime(), MAX_TIME);
    ASSERT_EQUALS(room1.level(), LEVEL);
    ASSERT_EQUALS(room1.getAgeLimit(),AGE);
    vector<Enigma> &room1_enigmas = room1.getAllEnigmas();
    vector<Enigma> &room2_enigmas = room2.getAllEnigmas();
    ASSERT_EQUALS(room1_enigmas.size(), room2_enigmas.size());
    for (int i = 0; i < (int) room1_enigmas.size(); i++) {
        ASSERT_EQUALS(room1_enigmas[i], room2_enigmas[i]);
    }
    ASSERT_NOT_EQUAL(&room1_enigmas,&room2_enigmas);
}

static void testAssignmentOperator(){
    KidsRoom room2((char *) NAME, MAX_TIME, LEVEL, MAX_PAR,AGE);
    set<string> my_elements;
    my_elements.insert("IDO");
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c++", HARD_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c", EASY_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c#", MEDIUM_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("bash", EASY_ENIGMA, 1, my_elements)));
    KidsRoom room1((char *) "temp",50,5,3,2);
    room1=room2;
    ASSERT_EQUALS(room1.getName(), NAME);
    ASSERT_EQUALS(room1.getMaxParticipants(), MAX_PAR);
    ASSERT_EQUALS(room1.getMaxTime(), MAX_TIME);
    ASSERT_EQUALS(room1.level(), LEVEL);
    ASSERT_EQUALS(room1.getAgeLimit(),AGE);
    vector<Enigma> &room1_enigmas = room1.getAllEnigmas();
    vector<Enigma> &room2_enigmas = room2.getAllEnigmas();
    ASSERT_EQUALS(room1_enigmas.size(), room2_enigmas.size());
    for (int i = 0; i < (int) room1_enigmas.size(); i++) {
        ASSERT_EQUALS(room1_enigmas[i], room2_enigmas[i]);
    }
    ASSERT_NOT_EQUAL(&room1_enigmas,&room2_enigmas);
}

static void testGetAfeLimit(){
    KidsRoom room2((char *) NAME, MAX_TIME, LEVEL, MAX_PAR,AGE);
    ASSERT_EQUALS(room2.getAgeLimit(),AGE);
}

static void testSetAfeLimit(){
    KidsRoom room((char *) NAME, MAX_TIME, LEVEL, MAX_PAR,AGE);
    ASSERT_THROWS(KidsRoomIllegalAgeLimit,room.setNewAgeLimit(-1));
    ASSERT_NO_THROW(room.setNewAgeLimit(AGE+20));
    ASSERT_EQUALS(room.getAgeLimit(),AGE+20);
    ASSERT_NO_THROW(room.setNewAgeLimit(AGE+16));
    ASSERT_EQUALS(room.getAgeLimit(),AGE+16);
    ASSERT_NO_THROW(room.setNewAgeLimit(AGE+18));
    ASSERT_EQUALS(room.getAgeLimit(),AGE+18);
}


static void testOperatorOutput(){
    KidsRoom room((char *) NAME, MAX_TIME, LEVEL, MAX_PAR,AGE);
    std::stringstream output;
    output << room;
    ASSERT_TRUE(output.str()==OUTPUT);
}

static void testgetType(){
    KidsRoom room((char *) NAME, MAX_TIME, LEVEL, MAX_PAR,AGE);
    ASSERT_EQUALS(KIDS_ROOM,room.getType());
}

static void testCopyToHeap(){
    KidsRoom room((char *) NAME, MAX_TIME, LEVEL, MAX_PAR,AGE);
    KidsRoom* copy=room.copyToHeap();
    ASSERT_EQUALS(*copy,room);
    delete(copy);
}

int main() {
    RUN_TEST(testConstructor);
    RUN_TEST(testCopyConstructor);
    RUN_TEST(testAssignmentOperator);
    RUN_TEST(testGetAfeLimit);
    RUN_TEST(testSetAfeLimit);
    RUN_TEST(testOperatorOutput);
    RUN_TEST(testgetType);
    RUN_TEST(testCopyToHeap);
}