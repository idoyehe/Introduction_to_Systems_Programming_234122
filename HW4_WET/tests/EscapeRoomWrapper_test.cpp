#include "../EscapeRoomWrapper.h"
#include "../mtmtest.h"
#include "../Exceptions.h"

#define NAME "ROOM1"
#define MAX_TIME 40
#define LEVEL 5
#define MAX_PAR 5
#define OUTPUT "ROOM1 (40/5/5)"
#define DEFAULT_TIME 60
#define DEFAULT_PARTICIPANTS 6
#define BASE "BASE_ROOM"


using std::set;
using namespace mtm::escaperoom;

static void testConstructor() {
    std::string room_name ="ROOM1";
    ASSERT_NO_THROW(EscapeRoomWrapper((char*) NAME,MAX_TIME,LEVEL,MAX_PAR));
    ASSERT_NO_THROW(EscapeRoomWrapper((char*) NAME,LEVEL));
    EscapeRoomWrapper room1((char*) NAME,MAX_TIME,LEVEL,MAX_PAR);
    EscapeRoomWrapper room2((char*) NAME,LEVEL);
    ASSERT_EQUALS(room1.getName(),room_name);
    ASSERT_EQUALS(room1.getMaxParticipants(),MAX_PAR);
    ASSERT_EQUALS(room1.getMaxTime(),MAX_TIME);
    ASSERT_EQUALS(room1.level(),LEVEL);
    ASSERT_EQUALS(room2.getName(),room_name);
    ASSERT_EQUALS(room2.getMaxParticipants(),DEFAULT_PARTICIPANTS);
    ASSERT_EQUALS(room2.getMaxTime(),DEFAULT_TIME);
    ASSERT_EQUALS(room2.level(),LEVEL);
}

static void testGetName(){
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    ASSERT_EQUALS(room1.getName(),NAME);
}

static void testAddEnigma() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    ASSERT_NO_THROW(room1.addEnigma(Enigma("c++", HARD_ENIGMA, 3, my_elements)));
    ASSERT_NO_THROW(room1.addEnigma(Enigma("c", EASY_ENIGMA, 3, my_elements)));
    ASSERT_NO_THROW(room1.addEnigma(Enigma("c#", MEDIUM_ENIGMA, 3, my_elements)));
    ASSERT_NO_THROW(room1.addEnigma(Enigma("bash", EASY_ENIGMA, 3, my_elements)));
    ASSERT_THROWS(EnigmaIllegalSizeParamException,room1.addEnigma(Enigma("bash", EASY_ENIGMA, 2, my_elements)));
}

static void testRemoveEnigma() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    ASSERT_THROWS(EscapeRoomNoEnigmasException,room1.removeEnigma(Enigma("c++", HARD_ENIGMA)));
    set<string> my_elements;
    my_elements.insert("IDO");
    ASSERT_NO_THROW(room1.addEnigma(Enigma("c++", HARD_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room1.addEnigma(Enigma("c", EASY_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room1.addEnigma(Enigma("c#", MEDIUM_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room1.addEnigma(Enigma("bash", EASY_ENIGMA, 1, my_elements)));
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,room1.removeEnigma(Enigma("java", HARD_ENIGMA)));
    ASSERT_NO_THROW(room1.removeEnigma(Enigma("c++", HARD_ENIGMA)));
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,room1.removeEnigma(Enigma("c++", HARD_ENIGMA)));
    ASSERT_NO_THROW(room1.removeEnigma(Enigma("c", EASY_ENIGMA)));
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,room1.removeEnigma(Enigma("c", EASY_ENIGMA)));
    ASSERT_NO_THROW(room1.removeEnigma(Enigma("c#", MEDIUM_ENIGMA)));
    ASSERT_THROWS(EscapeRoomEnigmaNotFoundException,room1.removeEnigma(Enigma("c#", MEDIUM_ENIGMA)));
    ASSERT_NO_THROW(room1.removeEnigma(Enigma("bash", EASY_ENIGMA)));
    ASSERT_THROWS(EscapeRoomNoEnigmasException,room1.removeEnigma(Enigma("bash", EASY_ENIGMA)));
}

static void testGetEnigmasVector() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    set<string> my_elements;
    my_elements.insert("IDO");
    ASSERT_NO_THROW(room1.addEnigma(Enigma("c++", HARD_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room1.addEnigma(Enigma("c", EASY_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room1.addEnigma(Enigma("c#", MEDIUM_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room1.addEnigma(Enigma("bash", EASY_ENIGMA, 1, my_elements)));
    vector<Enigma>& all_enigmas=room1.getAllEnigmas();
    ASSERT_TRUE(all_enigmas[0]==Enigma("c++", HARD_ENIGMA));
    ASSERT_TRUE(all_enigmas[1]==Enigma("c", EASY_ENIGMA));
    ASSERT_TRUE(all_enigmas[2]==Enigma("c#", MEDIUM_ENIGMA));
    ASSERT_TRUE(all_enigmas[3]==Enigma("bash", EASY_ENIGMA));
    all_enigmas.clear();
    ASSERT_THROWS(EscapeRoomNoEnigmasException,room1.removeEnigma(Enigma("c++", HARD_ENIGMA)));
}

static void testCopyConstructor() {
    EscapeRoomWrapper room2((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    set<string> my_elements;
    my_elements.insert("IDO");
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c++", HARD_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c", EASY_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c#", MEDIUM_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("bash", EASY_ENIGMA, 1, my_elements)));
    EscapeRoomWrapper room1(room2);
    ASSERT_EQUALS(room1.getName(), NAME);
    ASSERT_EQUALS(room1.getMaxParticipants(), MAX_PAR);
    ASSERT_EQUALS(room1.getMaxTime(), MAX_TIME);
    ASSERT_EQUALS(room1.level(), LEVEL);
    vector<Enigma> &room1_enigmas = room1.getAllEnigmas();
    vector<Enigma> &room2_enigmas = room2.getAllEnigmas();
    ASSERT_EQUALS(room1_enigmas.size(), room2_enigmas.size());
    for (int i = 0; i < (int) room1_enigmas.size(); i++) {
        ASSERT_EQUALS(room1_enigmas[i], room2_enigmas[i]);
    }
    ASSERT_NOT_EQUAL(&room1_enigmas,&room2_enigmas);
}


static void testOperatorAssignment() {
    EscapeRoomWrapper room2((char*) NAME,MAX_TIME,LEVEL,MAX_PAR);
    set<string> my_elements;
    my_elements.insert("IDO");
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c++", HARD_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c", EASY_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("c#", MEDIUM_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2.addEnigma(Enigma("bash", EASY_ENIGMA, 1, my_elements)));
    ASSERT_NO_THROW(room2=room2);
    EscapeRoomWrapper room1((char*) NAME,LEVEL);
    ASSERT_EQUALS(room1.getMaxParticipants(),DEFAULT_PARTICIPANTS);
    ASSERT_EQUALS(room1.getMaxTime(),DEFAULT_TIME);
    ASSERT_EQUALS(room1.level(),LEVEL);
    room1=room2;
    ASSERT_EQUALS(room1.getName(), NAME);
    ASSERT_EQUALS(room1.getMaxParticipants(), MAX_PAR);
    ASSERT_EQUALS(room1.getMaxTime(), MAX_TIME);
    ASSERT_EQUALS(room1.level(), LEVEL);
    vector<Enigma> &room1_enigmas = room1.getAllEnigmas();
    vector<Enigma> &room2_enigmas = room2.getAllEnigmas();
    ASSERT_EQUALS(room1_enigmas.size(), room2_enigmas.size());
    for (int i = 0; i < (int) room1_enigmas.size(); i++) {
        ASSERT_EQUALS(room1_enigmas[i], room2_enigmas[i]);
    }
    ASSERT_NOT_EQUAL(&room1_enigmas,&room2_enigmas);
}

static void testOperatorEqual() {
    EscapeRoomWrapper room1((char*) NAME,MAX_TIME,LEVEL,MAX_PAR);
    EscapeRoomWrapper room2((char*) NAME,MAX_TIME,LEVEL,MAX_PAR);
    EscapeRoomWrapper room3((char*) NAME,MAX_TIME+1,LEVEL,MAX_PAR);
    EscapeRoomWrapper room4((char*) "ROOM2",MAX_TIME,LEVEL,MAX_PAR);
    ASSERT_EQUALS(room1,room2);
    ASSERT_NOT_EQUAL(room1,room4);
    ASSERT_NOT_EQUAL(room1,room3);
}

static void testOperatorNOTEqual() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    EscapeRoomWrapper room3((char *) NAME, MAX_TIME + 1, LEVEL, MAX_PAR);
    EscapeRoomWrapper room4((char *) "ROOM2", MAX_TIME, LEVEL, MAX_PAR);
    ASSERT_NOT_EQUAL(room1, room4);
    ASSERT_NOT_EQUAL(room1, room3);
}

static void testOperatorBigger() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    EscapeRoomWrapper room2((char *) NAME, MAX_TIME + 1, LEVEL, MAX_PAR);
    EscapeRoomWrapper room3((char *) NAME, MAX_TIME, LEVEL, MAX_PAR-1);
    EscapeRoomWrapper room4((char *) NAME, MAX_TIME, LEVEL+1, MAX_PAR-1);
    ASSERT_TRUE(room2>room1);
    ASSERT_TRUE(room3>room1);
    ASSERT_TRUE(room4>room3);
}

static void testOperatorSmaller() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    EscapeRoomWrapper room2((char *) NAME, MAX_TIME + 1, LEVEL, MAX_PAR);
    EscapeRoomWrapper room3((char *) NAME, MAX_TIME, LEVEL, MAX_PAR-1);
    EscapeRoomWrapper room4((char *) NAME, MAX_TIME, LEVEL+1, MAX_PAR-1);
    ASSERT_TRUE(room1<room2);
    ASSERT_TRUE(room1<room3);
    ASSERT_TRUE(room3<room4);
}

static void testLevel() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    ASSERT_EQUALS(room1.level(),LEVEL);
}

static void testGetRate(){
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    ASSERT_EQUALS(room1.getRate(),0);
}

static void testRate(){
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    ASSERT_THROWS(EscapeRoomIllegalRateException,room1.rate(-1));
    ASSERT_EQUALS(room1.getRate(),0);
    ASSERT_THROWS(EscapeRoomIllegalRateException,room1.rate(6));
    ASSERT_EQUALS(room1.getRate(),0);
    ASSERT_NO_THROW(room1.rate(1));
    ASSERT_NO_THROW(room1.rate(2));
    ASSERT_NO_THROW(room1.rate(3));
    ASSERT_NO_THROW(room1.rate(4));
    ASSERT_NO_THROW(room1.rate(5));
    ASSERT_EQUALS(room1.getRate(),3);
}

static void testGetMAxTime() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    ASSERT_EQUALS(room1.getMaxTime(), MAX_TIME);
}

static void testgetMaxParticipants() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    ASSERT_EQUALS(room1.getMaxParticipants(), MAX_PAR);
}

static void testOperatorOutput() {
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    std::stringstream output;
    output << room1;
    ASSERT_TRUE(output.str()==OUTPUT);
}

static void testgetType(){
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    ASSERT_EQUALS(BASE,room1.getType());
}

static void testCopyToHeap(){
    EscapeRoomWrapper room1((char *) NAME, MAX_TIME, LEVEL, MAX_PAR);
    EscapeRoomWrapper* copy=room1.copyToHeap();
    ASSERT_EQUALS(*copy,room1);
    delete(copy);
}

int main() {
    RUN_TEST(testConstructor);
    RUN_TEST(testGetName);
    RUN_TEST(testAddEnigma);
    RUN_TEST(testRemoveEnigma);
    RUN_TEST(testGetEnigmasVector);
    RUN_TEST(testCopyConstructor);
    RUN_TEST(testOperatorAssignment);
    RUN_TEST(testOperatorEqual);
    RUN_TEST(testOperatorNOTEqual);
    RUN_TEST(testOperatorBigger);
    RUN_TEST(testOperatorSmaller);
    RUN_TEST(testLevel);
    RUN_TEST(testGetRate);
    RUN_TEST(testRate);
    RUN_TEST(testGetMAxTime);
    RUN_TEST(testgetMaxParticipants);
    RUN_TEST(testOperatorOutput);
    RUN_TEST(testgetType);
    RUN_TEST(testCopyToHeap);
}