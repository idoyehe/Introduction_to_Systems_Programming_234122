#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "visitor_room.h"

#define ASSERT(test_number, test_condition)  \
if (!(test_condition)) {printf("TEST %s FAILED\n", test_number); failed++; } \
else {printf("TEST %s OK\n", test_number); passed++;}

#define SUMMARIZE(p,f) {printf("Passed: %d, Failed: %d\n", p, f); }
#define FREE_NULL(e) free((e)); (e)=NULL;
#define BORDER "***********************************\n"

int main() {
    int passed = 0;
    int failed = 0;
    printf(BORDER);
    Challenge* challenge = malloc(sizeof(*challenge));
    init_challenge(challenge, 123, "challenge name", Medium);
    Visitor* visitor = malloc(sizeof(*visitor));
    ChallengeRoom* challenge_room = malloc(sizeof(*challenge_room));
    ChallengeActivity* challenge_activity = malloc(sizeof(*challenge_activity));
    
    printf("TESTING init_challenge_activity\n");
    ASSERT("1.1", init_challenge_activity(NULL, challenge)== NULL_PARAMETER);
    ASSERT("1.2", init_challenge_activity(challenge_activity, NULL)== NULL_PARAMETER);
    ASSERT("1.3", init_challenge_activity(challenge_activity, challenge) == OK);
    ASSERT("1.4", challenge_activity->start_time == 0);
    ASSERT("1.5", challenge_activity->visitor == NULL);
    ASSERT("1.6", challenge_activity->challenge == challenge);
    printf(BORDER);
    
    printf("TESTING reset_challenge_activity\n");
    challenge_activity->start_time = 1337;
    challenge_activity->visitor = visitor;
    ASSERT("2.1",reset_challenge_activity(NULL) == NULL_PARAMETER);
    ASSERT("2.2",reset_challenge_activity(challenge_activity) == OK);
    ASSERT("2.3",challenge_activity->challenge == NULL);
    ASSERT("2.4",challenge_activity->start_time == 0);
    ASSERT("2.5",challenge_activity->visitor == NULL);
    printf(BORDER);
    
    printf("TESTING init_visitor\n");
    ASSERT("3.1", init_visitor(NULL, "name", 123) == NULL_PARAMETER);
    ASSERT("3.2", init_visitor(visitor, NULL , 123) == NULL_PARAMETER);
    visitor->visitor_id = 1337;
    visitor->current_challenge = challenge_activity;
    char* str = "BLA";
    visitor->room_name = &str;
    visitor->visitor_name = NULL;
    ASSERT("3.3", init_visitor(visitor, "Ben" , 123) == OK);
    ASSERT("3.4", visitor->visitor_id == 123);
    ASSERT("3.5",  strcmp("Ben", visitor->visitor_name) == 0 );
    ASSERT("3.6", visitor->room_name == NULL);
    ASSERT("3.7", visitor->current_challenge == NULL);
    printf(BORDER);

    printf("TESTING reset_visitor\n");
    ASSERT("4.1", reset_visitor(NULL) == NULL_PARAMETER);
    visitor->room_name = &str;
    visitor->current_challenge = challenge_activity;
    ASSERT("4.2", reset_visitor(visitor) == OK);
    ASSERT("4.3", visitor->visitor_name == NULL);
    ASSERT("4.4", visitor->visitor_id == 0);
    ASSERT("4.5", visitor->visitor_name == NULL);
    ASSERT("4.6", visitor->current_challenge == NULL);
    printf(BORDER);
    
    printf("TESTING init_room\n");
    ASSERT("5.1", init_room(NULL, "Ben", 3) == NULL_PARAMETER);
    ASSERT("5.2", init_room(challenge_room, NULL, 3) == NULL_PARAMETER);
    ASSERT("5.3", init_room(challenge_room, "Ben", 0) == ILLEGAL_PARAMETER);
    ASSERT("5.4", init_room(challenge_room, "Ben", -4) == ILLEGAL_PARAMETER);
    challenge_room->name = NULL;
    challenge_room->num_of_challenges = -10;
    challenge_room->challenges = NULL;
    ASSERT("5.5", init_room(challenge_room, "Ben", 10) == OK);
    ASSERT("5.6", strcmp("Ben", challenge_room->name) == 0);
    ASSERT("5.7", challenge_room->num_of_challenges == 10);
    ASSERT("5.8", challenge_room->challenges != NULL);
    printf(BORDER);
    
    printf("TESTING reset_room\n");
    ASSERT("6.1", reset_room(NULL) == NULL_PARAMETER);
    ASSERT("6.2", reset_room(challenge_room) == OK);
    ASSERT("6.3", challenge_room->name == NULL);
    ASSERT("6.4", challenge_room->num_of_challenges == 0);
    ASSERT("6.5", challenge_room->challenges == NULL);
    printf(BORDER);
    
    printf("TESTING num_of_free_places_for_level\n");
    ChallengeRoom* main_room = malloc(sizeof(*main_room));
    init_room(main_room, "main room", 5);
    Challenge* challenge_1 = malloc(sizeof(*challenge_1));
    Challenge* challenge_2 = malloc(sizeof(*challenge_2));
    Challenge* challenge_3 = malloc(sizeof(*challenge_3));
    Challenge* challenge_4 = malloc(sizeof(*challenge_4));
    Challenge* challenge_5 = malloc(sizeof(*challenge_5));
    init_challenge(challenge_1, 11, "A", Easy);
    init_challenge(challenge_2, 22, "B", Hard);
    init_challenge(challenge_3, 33, "C", Easy);
    init_challenge(challenge_4, 44, "D", Hard);
    init_challenge(challenge_5, 55, "E", Easy);
    init_challenge_activity(&(main_room->challenges[0]), challenge_1);
    init_challenge_activity(&(main_room->challenges[1]), challenge_2);
    init_challenge_activity(&(main_room->challenges[2]), challenge_3);
    init_challenge_activity(&(main_room->challenges[3]), challenge_4);
    init_challenge_activity(&(main_room->challenges[4]), challenge_5);
    main_room->challenges[0].visitor = visitor;
    int places = -1;
    ASSERT("7.1", num_of_free_places_for_level(NULL, Easy, &places) == NULL_PARAMETER);
    ASSERT("7.2", num_of_free_places_for_level(main_room, Easy, &places) == OK);
    ASSERT("7.3", places == 2);
    ASSERT("7.4", num_of_free_places_for_level(main_room, Medium, &places) == OK);
    ASSERT("7.5", places == 0);
    ASSERT("7.6", num_of_free_places_for_level(main_room, Hard, &places) == OK);
    ASSERT("7.7", places == 2);
    ASSERT("7.8", num_of_free_places_for_level(main_room, All_Levels, &places) == OK);
    ASSERT("7.9", places == 4);
    printf(BORDER);
    
    printf("TESTING change_room_name\n");
    ChallengeRoom* change_name_room = malloc(sizeof(*change_name_room));
    init_room(change_name_room, "first name", 123);
    ASSERT("8.1",change_room_name(NULL, "second name") == NULL_PARAMETER);
    ASSERT("8.2",change_room_name(change_name_room, NULL) == NULL_PARAMETER);
    ASSERT("8.3",change_room_name(change_name_room, "second name") == OK);
    ASSERT("8.4",strcmp("second name", change_name_room->name) == 0);
    printf(BORDER);

    printf("TESTING room_of_visitor\n");
    ChallengeRoom* room1 = malloc(sizeof(*room1));
    init_room(room1, "cool room", 999);
    Visitor* cool_visitor = malloc(sizeof(*cool_visitor));
    init_visitor(cool_visitor, "Awesome dude", 111);
    Visitor* not_cool_visitor = malloc(sizeof(*not_cool_visitor));
    init_visitor(not_cool_visitor, "Totally not cool dude", 111);
    cool_visitor->room_name = &(room1->name);
    char* return_string = NULL;
    ASSERT("9.1",room_of_visitor(NULL, &return_string) == NULL_PARAMETER);
    ASSERT("9.2",room_of_visitor(cool_visitor, NULL) == NULL_PARAMETER);
    ASSERT("9.3",room_of_visitor(not_cool_visitor, &return_string) ==
            NOT_IN_ROOM);
    ASSERT("9.4",room_of_visitor(cool_visitor, &return_string) == OK);
    ASSERT("9.5",strcmp(return_string, "cool room") == 0);
    change_room_name(room1, "NEW COOL ROOM");
    ASSERT("9.6",strcmp(return_string, "cool room") == 0);
    printf(BORDER);

    printf("TESTING visitor_enter_room & visitor_quit_room\n");
    ChallengeRoom* best_room_ever = malloc(sizeof(*best_room_ever));
    init_room(best_room_ever, "Best room ever", 3);
    Challenge*  challenge1 = malloc (sizeof(*challenge1));
    Challenge*  challenge2 = malloc (sizeof(*challenge2));
    Challenge*  challenge3 = malloc (sizeof(*challenge3));
    init_challenge(challenge1, 1, "ZZZ", Easy);
    init_challenge(challenge2, 2, "HHH", Hard);
    init_challenge(challenge3, 3, "AAA", Easy);
    init_challenge_activity(&(best_room_ever->challenges[0]), challenge1);
    init_challenge_activity(&(best_room_ever->challenges[1]), challenge2);
    init_challenge_activity(&(best_room_ever->challenges[2]), challenge3);
    Visitor* visitor1 = malloc(sizeof((*visitor1)));
    Visitor* visitor2 = malloc(sizeof((*visitor2)));
    Visitor* visitor3 = malloc(sizeof((*visitor3)));
    Visitor* visitor4 = malloc(sizeof((*visitor4)));
    init_visitor(visitor1, "Alex", 1);
    init_visitor(visitor2, "Ben", 2);
    init_visitor(visitor3, "Charlie", 3);
    init_visitor(visitor4, "David", 4);
    ASSERT("10.1", visitor_enter_room(NULL, visitor4, Medium, 10) == NULL_PARAMETER);
    ASSERT("10.2", visitor_enter_room(best_room_ever, NULL, Medium, 10) == NULL_PARAMETER);
    ASSERT("10.3", visitor_enter_room(best_room_ever, visitor4, Medium, 10) == NO_AVAILABLE_CHALLENGES);
    ASSERT("10.4", visitor_enter_room(best_room_ever, visitor4, Easy, 10) == OK);
    ASSERT("10.5", best_room_ever->challenges[2].visitor == visitor4);
    ASSERT("10.6", best_room_ever->challenges[2].start_time == 10);
    ASSERT("10.7", visitor4->current_challenge = &(best_room_ever->challenges[2]));
    ASSERT("10.8", strcmp("Best room ever", *(visitor4->room_name) ) == 0);
    ASSERT("10.9", visitor_enter_room(best_room_ever, visitor4, Easy, 15) == ALREADY_IN_ROOM);
    ASSERT("10.10", visitor_enter_room(best_room_ever, visitor4, All_Levels, 15) == ALREADY_IN_ROOM);
    ASSERT("10.11", visitor_enter_room(best_room_ever, visitor4, Medium, 15) == ALREADY_IN_ROOM);
    ASSERT("10.12", visitor_enter_room(best_room_ever, visitor3, All_Levels, 15) == OK);
    ASSERT("10.13", best_room_ever->challenges[1].visitor == visitor3);
    ASSERT("10.14", best_room_ever->challenges[1].start_time == 15);
    ASSERT("10.15", visitor3->current_challenge = &(best_room_ever->challenges[1]));
    ASSERT("10.16", strcmp("Best room ever", *(visitor3->room_name) ) == 0);
    ASSERT("10.17", visitor_enter_room(best_room_ever, visitor2, Hard, 30) == NO_AVAILABLE_CHALLENGES);
    ASSERT("10.18", visitor_enter_room(best_room_ever, visitor2, All_Levels, 30) == OK);
    ASSERT("10.19", best_room_ever->challenges[0].visitor == visitor2);
    ASSERT("10.20", best_room_ever->challenges[0].start_time == 30);
    ASSERT("10.21", visitor2->current_challenge = &(best_room_ever->challenges[0]));
    ASSERT("10.22", strcmp("Best room ever", *(visitor2->room_name) ) == 0);
    ASSERT("10.23", challenge1->num_visits == 1);
    ASSERT("10.24", challenge2->num_visits == 1);
    ASSERT("10.25", challenge3->num_visits == 1);
    ASSERT("10.26", visitor_enter_room(best_room_ever, visitor1, Hard, 30) == NO_AVAILABLE_CHALLENGES);
    printf(BORDER);
    
    printf("TESTING visitor_enter_room & visitor_quit_room\n");
    ASSERT("11.1", visitor_quit_room(NULL, 40)== NULL_PARAMETER);
    ASSERT("11.2", visitor_quit_room(visitor4, 40)== OK);
    ASSERT("11.3", challenge3->best_time = 30);
    ASSERT("11.4", challenge3->num_visits = 1);
    ASSERT("11.5", best_room_ever->challenges[2].visitor == NULL);
    ASSERT("11.6", best_room_ever->challenges[2].start_time == 0);
    ASSERT("11.7", visitor4->current_challenge == NULL);
    ASSERT("11.8", visitor4->room_name == NULL);
    int free_places = -1;
    num_of_free_places_for_level(best_room_ever, Easy, &free_places);
    ASSERT("11.9", free_places == 1 );
    ASSERT("11.10", visitor_quit_room(visitor4, 40)== NOT_IN_ROOM);
    visitor_enter_room(best_room_ever, visitor4, All_Levels, 60);
    ASSERT("11.11", visitor_quit_room(visitor4, 65)== OK);
    ASSERT("11.12", challenge3->best_time = 5);
    ASSERT("11.13", challenge3->num_visits == 2);
    printf(BORDER);
    SUMMARIZE(passed,failed);
    reset_challenge(challenge);
    FREE_NULL(challenge);
    reset_visitor(visitor);
    FREE_NULL(visitor);
    reset_room(challenge_room);
    FREE_NULL(challenge_room);
    reset_challenge_activity(challenge_activity);
    FREE_NULL(challenge_activity);
    reset_challenge(challenge_1);
    FREE_NULL(challenge_1);
    reset_challenge(challenge_2);
    FREE_NULL(challenge_2);
    reset_challenge(challenge_2);
    FREE_NULL(challenge_2);
    reset_challenge(challenge_3);
    FREE_NULL(challenge_3);
    reset_challenge(challenge_4);
    FREE_NULL(challenge_4);
    reset_challenge(challenge_5);
    FREE_NULL(challenge_5);
    reset_room(main_room);
    FREE_NULL(main_room);
    reset_challenge(challenge1);
    FREE_NULL(challenge1);
    reset_challenge(challenge2);
    FREE_NULL(challenge2);
    reset_challenge(challenge2);
    FREE_NULL(challenge2);
    reset_challenge(challenge3);
    FREE_NULL(challenge3);
    reset_room(change_name_room);
    FREE_NULL(change_name_room);
    reset_visitor(cool_visitor);
    FREE_NULL(cool_visitor);
    reset_visitor(not_cool_visitor);
    FREE_NULL(not_cool_visitor);
    reset_room(room1);
    FREE_NULL(room1);
    reset_room(best_room_ever);
    FREE_NULL(best_room_ever);
    FREE_NULL(return_string);
    reset_visitor(visitor1);
    FREE_NULL(visitor1);
    reset_visitor(visitor2);
    FREE_NULL(visitor2);
    reset_visitor(visitor3);
    FREE_NULL(visitor3);
    reset_visitor(visitor4);
    FREE_NULL(visitor4);
    return 0;
}
