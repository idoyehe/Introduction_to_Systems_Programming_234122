#include "../Company.h"
#include "../mtmtest.h"
#include "../Exceptions.h"

#define NAME "MATAM"
#define TELEPHONE "234122"

using namespace mtm::escaperoom;



static void testConstructor(){
    ASSERT_NO_THROW(Company(NAME,TELEPHONE));
    ASSERT_NO_THROW(Company("ATAM","234118"));
}

static void testCreateRoom(){
    Company matam(NAME,TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createRoom((char *) "r2", 60, 3, 4));
    ASSERT_NO_THROW(matam.createRoom((char *) "r3", 60, 5, 6));
    ASSERT_EQUALS(matam.getAllRooms().size(),3);
}

static void testCreateScaryRoom(){
    Company matam(NAME,TELEPHONE);
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r1",60,1,1,1,1));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2",60,2,2,2,2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r3",60,3,3,3,3));
    ASSERT_EQUALS(matam.getAllRooms().size(),3);
}

static void testCreateKidsRoom(){
    Company matam(NAME,TELEPHONE);
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r1",60,1,1,1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r2",60,2,2,2));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3",60,3,3,3));
    ASSERT_EQUALS(matam.getAllRooms().size(),3);
}

static void testGetsAllRooms(){
    Company matam(NAME,TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createRoom((char *) "r2", 60, 3, 4));
    ASSERT_NO_THROW(matam.createRoom((char *) "r3", 60, 5, 6));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r4",60,1,1,1,1));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r5",60,2,2,2,2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r6",60,3,3,3,3));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r7",60,1,1,1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r8",60,2,2,2));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r9",60,3,3,3));
    ASSERT_NO_THROW(matam.getAllRooms());
    set<EscapeRoomWrapper*> all_rooms=matam.getAllRooms();
    ASSERT_EQUALS(all_rooms.size(),9);
    set<EscapeRoomWrapper*>::iterator it=all_rooms.begin();
    int count1=0,count2=0,count3=0,count4=0,count5=0,count6=0,count7=0,count8=0,count9=0;
    for(it=all_rooms.begin();it!=all_rooms.end();++it) {
        if((*it)->getName()=="r1") {
            count1++;
            continue;
        }
        if((*it)->getName()=="r2") {
            count2++;
            continue;
        }
        if((*it)->getName()=="r3") {
            count3++;
            continue;
        }
        if((*it)->getName()=="r4") {
            count4++;
            continue;
        }
        if((*it)->getName()=="r5") {
            count5++;
            continue;
        }
        if((*it)->getName()=="r6") {
            count6++;
            continue;
        }
        if((*it)->getName()=="r7") {
            count7++;
            continue;
        }
        if((*it)->getName()=="r8") {
            count8++;
            continue;
        }
        if((*it)->getName()=="r9") {
            count9++;
            continue;
        }
    }
    ASSERT_EQUALS(count1,1);
    ASSERT_EQUALS(count2,1);
    ASSERT_EQUALS(count3,1);
    ASSERT_EQUALS(count4,1);
    ASSERT_EQUALS(count5,1);
    ASSERT_EQUALS(count6,1);
    ASSERT_EQUALS(count7,1);
    ASSERT_EQUALS(count8,1);
    ASSERT_EQUALS(count9,1);
}



static void testGetroomByType(){
    Company matam(NAME,TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createRoom((char *) "r2", 60, 3, 4));
    ASSERT_NO_THROW(matam.createRoom((char *) "r3", 60, 5, 6));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r4",60,1,1,1,1));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r5",60,2,2,2,2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r6",60,3,3,3,3));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r7",60,1,1,1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r8",60,2,2,2));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r9",60,3,3,3));
    ASSERT_NO_THROW(matam.getAllRoomsByType(BASE_ROOM));
    set<EscapeRoomWrapper*> rooms_by_type=matam.getAllRoomsByType(BASE_ROOM);
    ASSERT_EQUALS(rooms_by_type.size(),3);
    set<EscapeRoomWrapper*>::iterator it=rooms_by_type.begin();
    for(it=rooms_by_type.begin();it!=rooms_by_type.end();++it){
       string name = (*it)->getName();
        ASSERT_TRUE(name=="r1"||name=="r2"||name=="r3");
    }
    ASSERT_NO_THROW(matam.getAllRoomsByType(SCARY_ROOM));
    rooms_by_type=matam.getAllRoomsByType(SCARY_ROOM);
    ASSERT_EQUALS(rooms_by_type.size(),3);
    it=rooms_by_type.begin();
    for(it=rooms_by_type.begin();it!=rooms_by_type.end();++it){
        string name = (*it)->getName();
        ASSERT_TRUE(name=="r4"||name=="r5"||name=="r6");
    }
    ASSERT_NO_THROW(matam.getAllRoomsByType(KIDS_ROOM));
    rooms_by_type=matam.getAllRoomsByType(KIDS_ROOM);
    ASSERT_EQUALS(rooms_by_type.size(),3);
    it=rooms_by_type.begin();
    for(it=rooms_by_type.begin();it!=rooms_by_type.end();++it){
        string name = (*it)->getName();
        ASSERT_TRUE(name=="r7"||name=="r8"||name=="r9");
    }
}

static void testGetroomByName(){
    Company matam(NAME,TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2",60,1,1,1,1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3",60,3,3,3));
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.getRoomByName("r4"));
    ASSERT_EQUALS((*(matam.getRoomByName("r1"))),EscapeRoomWrapper((char *) "r1",60,2,2));
    ASSERT_EQUALS((*(matam.getRoomByName("r2"))),EscapeRoomWrapper((char *) "r2",60,1,1));
    ASSERT_EQUALS((*(matam.getRoomByName("r3"))),EscapeRoomWrapper((char *) "r3",60,1,1));
}

static void testRemoveRoom(){
    Company matam(NAME,TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2",60,1,1,1,1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3",60,3,3,3));
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.removeRoom(EscapeRoomWrapper((char*)"r4",60,2,2)));
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.removeRoom(EscapeRoomWrapper((char*)"r1",70,2,2)));
    ASSERT_NO_THROW(matam.removeRoom(EscapeRoomWrapper((char*)"r1",60,2,2)));
    ASSERT_NO_THROW(matam.removeRoom(EscapeRoomWrapper((char*)"r2",60,1,1)));
    ASSERT_NO_THROW(matam.removeRoom(EscapeRoomWrapper((char*)"r3",60,3,3)));
    ASSERT_EQUALS(matam.getAllRooms().size(),0);
}

static void testAddEnigma(){
    Company matam(NAME,TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2",60,1,1,1,1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3",60,3,3,3));
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    Enigma e1=Enigma("C++",EASY_ENIGMA,3,my_elements);
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.addEnigma(EscapeRoomWrapper((char*)"r4",60,2,2),e1));
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.addEnigma(EscapeRoomWrapper((char*)"r1",70,2,2),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r1",60,2,2),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r2",60,1,1),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r3",60,3,3),e1));
    set<EscapeRoomWrapper*> all_rooms=matam.getAllRooms();
    ASSERT_EQUALS(all_rooms.size(),3);
    set<EscapeRoomWrapper*>::iterator it;
    for(it=all_rooms.begin();it!=all_rooms.end();it++){
        vector<Enigma> &enigmas=(*it)->getAllEnigmas();
        ASSERT_EQUALS(enigmas.size(),1);
        ASSERT_EQUALS(enigmas[0].getName(),"C++");
        ASSERT_EQUALS(enigmas[0].getDifficulty(),EASY_ENIGMA);
    }
}

static void testRemoveEnigma(){
    Company matam(NAME,TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2",60,1,1,1,1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3",60,3,3,3));
    set<string> my_elements;
    my_elements.insert("IDO");
    my_elements.insert("SHLOMI");
    my_elements.insert("MTM");
    Enigma e1=Enigma("C++",EASY_ENIGMA,3,my_elements);
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.removeEnigma(EscapeRoomWrapper((char*)"r4",60,2,2),e1));
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.removeEnigma(EscapeRoomWrapper((char*)"r1",70,2,2),e1));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,matam.removeEnigma(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e1));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,matam.removeEnigma(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e1));
    ASSERT_THROWS(CompanyRoomHasNoEnigmasException,matam.removeEnigma(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r1",60,2,2),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r2",60,1,1),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r3",60,3,3),e1));
    Enigma e2=Enigma("C",EASY_ENIGMA);
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.removeEnigma(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e2));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.removeEnigma(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e2));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.removeEnigma(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e2));
    ASSERT_NO_THROW(matam.removeEnigma(EscapeRoomWrapper((char*)"r1",60,2,2),e1));
    ASSERT_NO_THROW(matam.removeEnigma(EscapeRoomWrapper((char*)"r2",60,1,1),e1));
    ASSERT_NO_THROW(matam.removeEnigma(EscapeRoomWrapper((char*)"r3",60,3,3),e1));
    set<EscapeRoomWrapper*> all_rooms=matam.getAllRooms();
    ASSERT_EQUALS(all_rooms.size(),3);
    set<EscapeRoomWrapper*>::iterator it;
    for(it=all_rooms.begin();it!=all_rooms.end();it++){
        vector<Enigma> &enigmas=(*it)->getAllEnigmas();
        ASSERT_EQUALS(enigmas.size(),0);
    }
}

static void testAddItem() {
    Company matam(NAME, TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2", 60, 1, 1, 1, 1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3", 60, 3, 3, 3));
    Enigma e1 = Enigma("mtm_course", HARD_ENIGMA);
    Enigma e2=Enigma("atam_course",EASY_ENIGMA);
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.addItem(EscapeRoomWrapper((char*)"r4",60,2,2),e1,"IDO"));
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.addItem(EscapeRoomWrapper((char*)"r1",70,2,2),e1,"SHLOMI"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.addItem(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e1,"IDO"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.addItem(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e1,"IDO"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.addItem(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e1,"IDO"));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r1",60,2,2),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r2",60,1,1),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r3",60,3,3),e1));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.addItem(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e2,"IDO"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.addItem(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e2,"IDO"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.addItem(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e2,"IDO"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e1,"HW4"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e1,"HW4"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e1,"HW4"));
    set<EscapeRoomWrapper*> all_rooms=matam.getAllRooms();
    ASSERT_EQUALS(all_rooms.size(),3);
    set<EscapeRoomWrapper*>::iterator it;
    for(it=all_rooms.begin();it!=all_rooms.end();it++){
        vector<Enigma> &enigmas=(*it)->getAllEnigmas();
        ASSERT_EQUALS(enigmas.size(),1);
        ASSERT_NO_THROW(enigmas[0].removeElement("HW4"));
    }
}


static void testRemoveElement() {
    Company matam(NAME, TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2", 60, 1, 1, 1, 1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3", 60, 3, 3, 3));
    Enigma e1 = Enigma("mtm_course", HARD_ENIGMA);
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.removeItem(EscapeRoomWrapper((char*)"r4",60,2,2),e1,"IDO"));
    ASSERT_THROWS(CompanyRoomNotFoundException,matam.removeItem(EscapeRoomWrapper((char*)"r1",70,2,2),e1,"SHLOMI"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.removeItem(EscapeRoomWrapper((char*)"r1",60,2,2),e1,"IDO"));
    ASSERT_THROWS(CompanyRoomEnigmaNotFoundException,matam.removeItem(EscapeRoomWrapper((char*)"r2",60,1,1),e1,"SHLOMI"));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r1",60,2,2),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r2",60,1,1),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r3",60,3,3),e1));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,matam.removeItem(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e1,"IDO"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,matam.removeItem(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e1,"IDO"));
    ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException,matam.removeItem(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e1,"IDO"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e1,"HW4"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e1,"HW4"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e1,"HW4"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,matam.removeItem(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e1,"IDO"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,matam.removeItem(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e1,"IDO"));
    ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException,matam.removeItem(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e1,"IDO"));
    ASSERT_NO_THROW(matam.removeItem(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e1,"HW4"));
    ASSERT_NO_THROW(matam.removeItem(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e1,"HW4"));
    ASSERT_NO_THROW(matam.removeItem(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e1,"HW4"));
    set<EscapeRoomWrapper*> all_rooms=matam.getAllRooms();
    ASSERT_EQUALS(all_rooms.size(),3);
    set<EscapeRoomWrapper*>::iterator it;
    for(it=all_rooms.begin();it!=all_rooms.end();it++){
        vector<Enigma> &enigmas=(*it)->getAllEnigmas();
        ASSERT_EQUALS(enigmas.size(),1);
        ASSERT_THROWS(EnigmaNoElementsException,enigmas[0].removeElement("HW4"));
    }
}

static void testCopyConstructor() {
    Company matam(NAME, TELEPHONE);
    EscapeRoomWrapper room1((char *) "r1", 60, 2, 2);
    ScaryRoom room2((char *) "r2", 60, 1, 1, 1, 1);
    KidsRoom room3((char *) "r3", 60, 3, 3, 3);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2", 60, 1, 1, 1, 1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3", 60, 3, 3, 3));
    Enigma e1 = Enigma("mtm_course", HARD_ENIGMA);
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r1",60,2,2),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r2",60,1,1),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r3",60,3,3),e1));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e1,"HW4"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e1,"HW4"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e1,"HW4"));
    Company atam(matam);
    set<EscapeRoomWrapper*> all_rooms_matam=matam.getAllRooms();
    set<EscapeRoomWrapper*> all_rooms_atam=atam.getAllRooms();
    ASSERT_EQUALS(all_rooms_atam.size(),3);
    ASSERT_EQUALS(all_rooms_matam.size(),3);
    ASSERT_EQUALS(atam.getAllRoomsByType(BASE_ROOM).size(),1);
    ASSERT_EQUALS(atam.getAllRoomsByType(KIDS_ROOM).size(),1);
    ASSERT_EQUALS(atam.getAllRoomsByType(SCARY_ROOM).size(),1);
    set<EscapeRoomWrapper*>::iterator it_atam=all_rooms_atam.begin();
    set<EscapeRoomWrapper*>::iterator it_matam=all_rooms_matam.begin();
    for(it_atam=all_rooms_atam.begin();it_atam!=all_rooms_atam.end();++it_atam){
        ASSERT_NOT_EQUAL(*it_atam,*it_matam);
        ASSERT_TRUE(*(*it_atam)==room1||*(*it_atam)==room2||*(*it_atam)==room3);
        ++it_matam;
    }
}

static void testAssignmentOperator(){
    Company matam(NAME, TELEPHONE);
    EscapeRoomWrapper room1((char *) "r1", 60, 2, 2);
    ScaryRoom room2((char *) "r2", 60, 1, 1, 1, 1);
    KidsRoom room3((char *) "r3", 60, 3, 3, 3);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2", 60, 1, 1, 1, 1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3", 60, 3, 3, 3));
    Enigma e1 = Enigma("mtm_course", HARD_ENIGMA);
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r1",60,2,2),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r2",60,1,1),e1));
    ASSERT_NO_THROW(matam.addEnigma(EscapeRoomWrapper((char*)"r3",60,3,3),e1));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r1", 60, 2, 2),e1,"HW4"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r2", 60, 1, 1),e1,"HW4"));
    ASSERT_NO_THROW(matam.addItem(EscapeRoomWrapper((char *) "r3", 60, 3, 3),e1,"HW4"));
    Company atam("assembly_course","234118");
    ASSERT_NO_THROW(atam.createRoom((char *) "Octal", 60, 2, 2));
    ASSERT_NO_THROW(atam.createScaryRoom((char *) "pdp11", 60, 1, 1, 1, 1));
    ASSERT_NO_THROW(atam.createKidsRoom((char *) "mips", 60, 3, 3, 3));
    matam=matam;
    atam=matam;
    set<EscapeRoomWrapper*> all_rooms_matam=matam.getAllRooms();
    set<EscapeRoomWrapper*> all_rooms_atam=atam.getAllRooms();
    ASSERT_EQUALS(all_rooms_atam.size(),3);
    ASSERT_EQUALS(all_rooms_matam.size(),3);
    ASSERT_EQUALS(atam.getAllRoomsByType(BASE_ROOM).size(),1);
    ASSERT_EQUALS(atam.getAllRoomsByType(KIDS_ROOM).size(),1);
    ASSERT_EQUALS(atam.getAllRoomsByType(SCARY_ROOM).size(),1);
    set<EscapeRoomWrapper*>::iterator it_atam=all_rooms_atam.begin();
    set<EscapeRoomWrapper*>::iterator it_matam=all_rooms_matam.begin();
    for(it_atam=all_rooms_atam.begin();it_atam!=all_rooms_atam.end();++it_atam){
        ASSERT_NOT_EQUAL(*it_atam,*it_matam);
        ASSERT_TRUE(*(*it_atam)==room1||*(*it_atam)==room2||*(*it_atam)==room3);
        ++it_matam;
    }
}

static void testOperatorOutput() {
    using std::endl;
    Company matam(NAME, TELEPHONE);
    ASSERT_NO_THROW(matam.createRoom((char *) "r1", 60, 2, 2));
    ASSERT_NO_THROW(matam.createScaryRoom((char *) "r2", 60, 1, 1, 1, 1));
    ASSERT_NO_THROW(matam.createKidsRoom((char *) "r3", 60, 3, 3, 3));
    std::stringstream output;
    output << matam;
    std::stringstream option1;
    option1 << NAME << " : " << TELEPHONE << endl;
    option1 << "r1 (60/2/2)" << endl;
    option1 << "Scary Room: r2 (60/1/1/1)" << endl;
    option1 << "Kids Room: r3 (60/3/3/3)" << endl;
    std::stringstream option2;
    option2 << NAME << " : " << TELEPHONE << endl;
    option2 << "r1 (60/2/2)" << endl;
    option2 << "Kids Room: r3 (60/3/3/3)" << endl;
    option2 << "Scary Room: r2 (60/1/1/1)" << endl;
    std::stringstream option3;
    option3 << NAME << " : " << TELEPHONE << endl;
    option3 << "Kids Room: r3 (60/3/3/3)" << endl;
    option3 << "r1 (60/2/2)" << endl;
    option3 << "Scary Room: r2 (60/1/1/1)" << endl;
    std::stringstream option4;
    option4 << NAME << " : " << TELEPHONE << endl;
    option4 << "Kids Room: r3 (60/3/3/3)" << endl;
    option4 << "Scary Room: r2 (60/1/1/1)" << endl;
    option4 << "r1 (60/2/2)" << endl;
    std::stringstream option5;
    option5 << NAME << " : " << TELEPHONE << endl;
    option5 << "Scary Room: r2 (60/1/1/1)" << endl;
    option5 << "Kids Room: r3 (60/3/3/3)" << endl;
    option5 << "r1 (60/2/2)" << endl;
    std::stringstream option6;
    option6 << NAME << " : " << TELEPHONE << endl;
    option6 << "Scary Room: r2 (60/1/1/1)" << endl;
    option6 << "r1 (60/2/2)" << endl;
    option6 << "Kids Room: r3 (60/3/3/3)" << endl;
    ASSERT_TRUE(output.str()==option1.str()||output.str()==option2.str()||
                        output.str()==option3.str()||output.str()==option4.str()
                ||output.str()==option5.str()||output.str()==option6.str());
}

int main() {
    RUN_TEST(testConstructor);
    RUN_TEST(testCreateRoom);
    RUN_TEST(testCreateScaryRoom);
    RUN_TEST(testCreateKidsRoom);
    RUN_TEST(testGetsAllRooms);
    RUN_TEST(testGetroomByType);
    RUN_TEST(testGetroomByName);
    RUN_TEST(testRemoveRoom);
    RUN_TEST(testAddEnigma);
    RUN_TEST(testRemoveEnigma);
    RUN_TEST(testAddItem);
    RUN_TEST(testRemoveElement);
    RUN_TEST(testCopyConstructor);
    RUN_TEST(testAssignmentOperator);
    RUN_TEST(testOperatorOutput);
}