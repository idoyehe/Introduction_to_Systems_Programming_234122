#include "../Company.h"
#include "../mtmtest.h"
#include <cstdio>

using namespace mtm::escaperoom;

static void constructorTest(){
	ASSERT_NO_THROW(Company("lockheed martin", "0987536"));
	ASSERT_NO_THROW(Company("", ""));
	ASSERT_NO_THROW(Company("Boeing", "-98"));
}

static void createRoomTest(){
	Company airbus("we make airplanes", "066-555555");
	char room_name[] = "747";
	ASSERT_NO_THROW(airbus.createRoom(room_name,32,2,2));
	ASSERT_NO_THROW(airbus.createRoom(room_name,10,11,12));
	ASSERT_NO_THROW(airbus.createRoom(room_name,31,30,19));
}

static void createKidsRoomTest(){
	Company airbus("we make airplanes", "066-555555");
	char room_name[] = "";
	ASSERT_NO_THROW(airbus.createKidsRoom(room_name,32,2,2,0));
	ASSERT_NO_THROW(airbus.createKidsRoom(room_name,35,16,7,3));
	ASSERT_NO_THROW(airbus.createKidsRoom(room_name,35,16,8,2));
}

static void createScaryRoomTest(){
	Company airbus("we make airplanes", "066-555555");
	char room_name[] = "";
	ASSERT_NO_THROW(airbus.createScaryRoom(room_name,32,2,2,0,1));
	ASSERT_NO_THROW(airbus.createScaryRoom(room_name,35,16,7,3,8));
	ASSERT_NO_THROW(airbus.createScaryRoom(room_name,35,16,8,2,5));
}

static void testGetAllRooms(){
	Company management("we make airplanes", "066-555555");
	ASSERT_EQUALS(management.getAllRooms().size(),0);
	char room_name_1[] = "dorm room";
	management.createRoom(room_name_1,32,33,55);
	char room_name_2[] = "unicorns room";
	management.createKidsRoom(room_name_2,32,33,55,6);
	char room_name_3[] = "bloody room";
	management.createScaryRoom(room_name_3,32,33,55,6,3);
	set<EscapeRoomWrapper*> rooms = management.getAllRooms();
	ASSERT_TRUE(rooms.size() == 3);
}

static void testRemoveRoom(){
	Company management("we make airplanes", "066-555555");
	char room_name_1[] = "dorm room";
	management.createRoom(room_name_1,32,33,55);
	EscapeRoomWrapper wrapper(room_name_1,32,33,55);
	char room_name_2[] = "unicorns room";
	management.createKidsRoom(room_name_2,32,33,55,6);
	KidsRoom horsie(room_name_2,32,33,55,6);
	char room_name_3[] = "bloody room";
	management.createScaryRoom(room_name_3,32,33,55,6,3);
	ScaryRoom gore(room_name_3,32,33,55,6,3);
	set<EscapeRoomWrapper*> rooms = management.getAllRooms();
	ASSERT_TRUE(rooms.size() == 3);

	//And now we remove
	ASSERT_NO_THROW(management.removeRoom(wrapper));
	rooms = management.getAllRooms();
	ASSERT_TRUE(rooms.size() == 2);
	ASSERT_THROWS(CompanyRoomNotFoundException, management.removeRoom(wrapper));
	ASSERT_NO_THROW(management.removeRoom(horsie));
	rooms = management.getAllRooms();
	ASSERT_TRUE(rooms.size() == 1);
	ASSERT_THROWS(CompanyRoomNotFoundException, management.removeRoom(wrapper));
	ASSERT_THROWS(CompanyRoomNotFoundException, management.removeRoom(horsie));
	ASSERT_NO_THROW(management.removeRoom(gore));
	rooms = management.getAllRooms();
	ASSERT_TRUE(rooms.size() == 0);
	ASSERT_THROWS(CompanyRoomNotFoundException, management.removeRoom(gore));
}

static void testCopyConstructor(){
	Company pringles("we make chips", "067875");
	char room_name_1[] = "pizza";
	pringles.createRoom(room_name_1,32,33,55);
	pringles.createKidsRoom(room_name_1,32,33,55,6);
	pringles.createScaryRoom(room_name_1,32,33,55,6,2);
	Company lays(pringles);
	ASSERT_EQUALS(lays.getAllRooms().size(), pringles.getAllRooms().size());
}

static void testAssignmentOperator(){
	Company canon("we make cameras", "067875");
	char room_name_1[] = "lens";
	canon.createRoom(room_name_1,32,33,55);
	canon.createKidsRoom(room_name_1,32,33,55,6);
	canon.createScaryRoom(room_name_1,32,33,55,6,2);
	Company nikon("We make better camera","74147982");
	nikon = canon;
	ASSERT_EQUALS(nikon.getAllRooms().size(), canon.getAllRooms().size());
}

static void testAddEnigma(){
	Company shell("we sell fuel", "235325");
	char room_name_1[] = "gas";
	shell.createKidsRoom(room_name_1,34,53,56,11);
	KidsRoom texaco(room_name_1,34,53,56,11);
	KidsRoom bp(room_name_1,37,53,56,11);
	Enigma pumping_fuel("1st gallon free", HARD_ENIGMA);
	ASSERT_NO_THROW(shell.addEnigma(texaco, pumping_fuel));
	ASSERT_THROWS(CompanyRoomNotFoundException, shell.addEnigma(bp, pumping_fuel));
	ASSERT_NO_THROW(shell.addEnigma(texaco, pumping_fuel));
}

static void testRemoveEnigma(){
	Company wallmart("we sell for cheap", "2676325");
	char room_name_1[] = "food";
	wallmart.createRoom(room_name_1,32,33,55);
	EscapeRoomWrapper bland_room(room_name_1,32,33,55);
	Enigma navigating_the_aisles("50% OFF", EASY_ENIGMA);
	ASSERT_NO_THROW(wallmart.addEnigma(bland_room, navigating_the_aisles));
	EscapeRoomWrapper costco(room_name_1,44,44,45);
	ASSERT_THROWS(CompanyRoomNotFoundException, wallmart.removeEnigma(costco, navigating_the_aisles));
	Enigma find_the_exit("1+1 discount", MEDIUM_ENIGMA);
	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, wallmart.removeEnigma(bland_room, find_the_exit));
	ASSERT_NO_THROW(wallmart.removeEnigma(bland_room, navigating_the_aisles));
	ASSERT_THROWS(CompanyRoomHasNoEnigmasException, wallmart.removeEnigma(bland_room, find_the_exit));

	//Same test as above with a scary room
	wallmart.createScaryRoom(room_name_1,39,37,16,9,9);
	ScaryRoom massacre(room_name_1,39,37,16,9,9);
	ASSERT_NO_THROW(wallmart.addEnigma(massacre, navigating_the_aisles));
	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, wallmart.removeEnigma(massacre, find_the_exit));
	ASSERT_NO_THROW(wallmart.removeEnigma(massacre, navigating_the_aisles));
	ASSERT_THROWS(CompanyRoomHasNoEnigmasException, wallmart.removeEnigma(massacre, navigating_the_aisles));
}

static void testAddItem(){
	//Creating company, room, enigma
	Company heineken("we sell beer", "8");
	char room_name_1[] = "a pint";
	heineken.createScaryRoom(room_name_1,32,33,55,6,7);
	ScaryRoom pale_ale(room_name_1,32,33,55,6,7);
	Enigma open_the_bottle("Beer is cold", EASY_ENIGMA);
	ASSERT_NO_THROW(heineken.addEnigma(pale_ale, open_the_bottle));

	//fake room
	KidsRoom carlsberg(room_name_1,32,33,77,55);
	ASSERT_THROWS(CompanyRoomNotFoundException, heineken.addItem(carlsberg, open_the_bottle, "stout"));

	//fake enigma
	Enigma should_i_drink_today("yes", EASY_ENIGMA);
	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, heineken.addItem(pale_ale, should_i_drink_today, "I'm the driver"));

	ASSERT_NO_THROW(heineken.addItem(pale_ale, open_the_bottle, "stout"));
	ASSERT_NO_THROW(heineken.addItem(pale_ale, open_the_bottle, "stout"));
	ASSERT_NO_THROW(heineken.addItem(pale_ale, open_the_bottle, ""));
	ASSERT_NO_THROW(heineken.addItem(pale_ale, open_the_bottle, "lager"));
}

static void testRemoveItem(){
	//Creating company, room, enigma
	Company volvo("we sell cars", "8");
	char room_name_1[] = "a model";
	volvo.createScaryRoom(room_name_1,32,33,55,6,7);
	ScaryRoom slippery_road(room_name_1,32,33,55,6,7);
	Enigma drive_tired("Below speed limit", MEDIUM_ENIGMA);
	ASSERT_NO_THROW(volvo.addEnigma(slippery_road, drive_tired));
	ASSERT_NO_THROW(volvo.addItem(slippery_road, drive_tired, "wheels"));
	ASSERT_NO_THROW(volvo.addItem(slippery_road, drive_tired, "wheels"));
	ASSERT_NO_THROW(volvo.addItem(slippery_road, drive_tired, "engine"));
	ASSERT_NO_THROW(volvo.addItem(slippery_road, drive_tired, "lights"));

	//fake room
	ScaryRoom dirt_road(room_name_1,32,36,55,6,7);
	ASSERT_THROWS(CompanyRoomNotFoundException, volvo.removeItem(dirt_road, drive_tired, "wheels"));

	//fake enigma
	Enigma drive_blind("No.", HARD_ENIGMA);
	ASSERT_THROWS(CompanyRoomEnigmaNotFoundException, volvo.removeItem(slippery_road, drive_blind, "wheels"));

	//fake element
	ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException, volvo.removeItem(slippery_road, drive_tired, "gear"));

	ASSERT_NO_THROW(volvo.removeItem(slippery_road, drive_tired, "wheels"));
	ASSERT_THROWS(CompanyRoomEnigmaElementNotFoundException, volvo.removeItem(slippery_road, drive_tired, "wheels"));
	ASSERT_NO_THROW(volvo.removeItem(slippery_road, drive_tired, "engine"));
	ASSERT_NO_THROW(volvo.removeItem(slippery_road, drive_tired, "lights"));

	//No elements now
	ASSERT_THROWS(CompanyRoomEnigmaHasNoElementsException, volvo.removeItem(slippery_road, drive_tired, "lights"));
}

static void testGetRoomByName(){
	Company university("we sell degrees", "");
	char room_name_1[] = "MIT";
	university.createScaryRoom(room_name_1,32,33,55,6,7);
	ScaryRoom caltech(room_name_1,32,33,55,6,7);

	ASSERT_THROWS(CompanyRoomNotFoundException, university.getRoomByName("UC Berkley"));
	ASSERT_THROWS(CompanyRoomNotFoundException, university.getRoomByName(""));
	EscapeRoomWrapper* room = university.getRoomByName("MIT");
	ASSERT_EQUALS((*room).getName(),"MIT");
	ASSERT_EQUALS((*room).getMaxTime(), 32);
	ASSERT_EQUALS((*room).getMaxParticipants(), 55);
	ASSERT_EQUALS((*room).level(), 33);
}

static void testGetRoomByType(){
	Company israel("we sell startups", "+972");
	ASSERT_EQUALS((israel.getAllRoomsByType(BASE_ROOM)).size(), 0);
	ASSERT_EQUALS((israel.getAllRoomsByType(KIDS_ROOM)).size(), 0);
	ASSERT_EQUALS((israel.getAllRoomsByType(SCARY_ROOM)).size(), 0);

	char room_name_1[] = "Waze";
	israel.createRoom(room_name_1,32,33,55);
	ASSERT_EQUALS((israel.getAllRoomsByType(BASE_ROOM)).size(), 1);
	ASSERT_EQUALS((israel.getAllRoomsByType(KIDS_ROOM)).size(), 0);
	ASSERT_EQUALS((israel.getAllRoomsByType(SCARY_ROOM)).size(), 0);

	israel.createKidsRoom(room_name_1, 2, 3, 4, 5);
	israel.createKidsRoom(room_name_1, 2, 3, 4, 6);
	israel.createScaryRoom(room_name_1, 2, 3, 4, 5,7);
	israel.createScaryRoom(room_name_1, 2, 3, 4, 5,8);
	israel.createScaryRoom(room_name_1, 2, 3, 4, 5,9);
	ASSERT_EQUALS((israel.getAllRoomsByType(BASE_ROOM)).size(), 1);
	ASSERT_EQUALS((israel.getAllRoomsByType(KIDS_ROOM)).size(), 2);
	ASSERT_EQUALS((israel.getAllRoomsByType(SCARY_ROOM)).size(), 3);
}

static void testOutputOperator(){
	Company mexico("we make tasty food", "099");
	{
		std::stringstream out;
		out << mexico;
		ASSERT_TRUE(out.str()=="we make tasty food : 099\n");
	}

	//One base room
	char room_name_1[] = "Taco";
	mexico.createRoom(room_name_1,32,33,55);
	{
		std::stringstream out;
		out << mexico;
		ASSERT_TRUE(out.str()=="we make tasty food : 099\nTaco (32/33/55)\n");
	}
	EscapeRoomWrapper el_taco(room_name_1,32,33,55);
	mexico.removeRoom(el_taco);

	//One kids room
	char room_name_2[] = "Burrito";
	mexico.createKidsRoom(room_name_2,32,33,55,9);
	{
		std::stringstream out;
		out << mexico;
		ASSERT_TRUE(out.str()=="we make tasty food : 099\nKids Room: Burrito (32/33/55/9)\n");
	}
	KidsRoom el_burrito(room_name_2,32,33,55,9);
	mexico.removeRoom(el_burrito);



	//One scary room
	char room_name_3[] = "Cesadilla";
	mexico.createScaryRoom(room_name_3,32,33,55,9,66);
	{
		std::stringstream out;
		out << mexico;
		ASSERT_TRUE(out.str()=="we make tasty food : 099\nScary Room: Cesadilla (32/33/55/9)\n");
	}
}

int main(){

	RUN_TEST(constructorTest);
	RUN_TEST(createRoomTest);
	RUN_TEST(createKidsRoomTest);
	RUN_TEST(createScaryRoomTest);
	RUN_TEST(testGetAllRooms);
	RUN_TEST(testRemoveRoom);
	RUN_TEST(testCopyConstructor);
	RUN_TEST(testAssignmentOperator);
	RUN_TEST(testAddEnigma);
	RUN_TEST(testRemoveEnigma);
	RUN_TEST(testAddItem);
	RUN_TEST(testRemoveItem);
	RUN_TEST(testGetRoomByName);
	RUN_TEST(testGetRoomByType);
	RUN_TEST(testOutputOperator);
	return 0;
}
