#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "challenge_system.h"

#define FREE_NULL(e) free((e)); (e)=NULL;

#define ASSERT(test_number, test_condition)  \
if (!(test_condition)) {printf("TEST %s FAILED\n", test_number); (*failed)++;}\
else {printf("TEST %s OK\n", test_number); (*passed)++;}

#define SUMMARIZE(p,f) {printf("Passed: %d, Failed: %d\n", p, f); }

#define BORDER "***********************************\n"

int check_creation_system(ChallengeRoomSystem **sys,int *passed,int *failed ) {
/*check if creation of the system succeed by the file*/
    Result r = create_system("test_2.txt", sys);
    if (r == MEMORY_PROBLEM) {
        printf("\nMemory Problem While Reading From File\nCannot Continue..\n");
        return -1;
    }
    ASSERT("1.1", r == OK);
    ASSERT("1.2",!strcmp((*sys)->system_name,"Ido's_System"));
    printf("\nSystem Name is: %s\n",(*sys)->system_name);
    ASSERT("1.3",(*sys)->last_update_time==0);
    ASSERT("1.3.1",(*sys)->all_visitors==NULL);
    printf("\nSystem Time is: %d\n",(*sys)->last_update_time);
    printf("Number of Challenges is: %d\n", (*sys)->number_of_challenges);
    printf("\nChecking Challenges Array\n");
    Challenge *ptr_challenge=(*sys)->all_challenges;
    ASSERT("1.4",ptr_challenge->id==44&&ptr_challenge->level==Easy
                 &&ptr_challenge->best_time==0&&ptr_challenge->num_visits==0
                 &&!strcmp(ptr_challenge->name,"challenge_4"));
    ptr_challenge++;
    ASSERT("1.5",ptr_challenge->id==33&&ptr_challenge->level==Hard
                 &&ptr_challenge->best_time==0&&ptr_challenge->num_visits==0
                 &&!strcmp(ptr_challenge->name,"WILL_BE_CHANGE"));
    ptr_challenge++;
    ASSERT("1.6",ptr_challenge->id==22&&ptr_challenge->level==Medium
                 &&ptr_challenge->best_time==0&&ptr_challenge->num_visits==0
                 &&!strcmp(ptr_challenge->name,"challenge_2"));
    ptr_challenge++;
    ASSERT("1.7",ptr_challenge->id==55&&ptr_challenge->level==Hard
                 &&ptr_challenge->best_time==0&&ptr_challenge->num_visits==0
                 &&!strcmp(ptr_challenge->name,"challenge_5"));
    ptr_challenge++;
    ASSERT("1.8",ptr_challenge->id==66&&ptr_challenge->level==Hard
                 &&ptr_challenge->best_time==0&&ptr_challenge->num_visits==0
                 &&!strcmp(ptr_challenge->name,"challenge_6"));
    ptr_challenge++;
    ASSERT("1.9",ptr_challenge->id==11&&ptr_challenge->level==Easy
                 &&ptr_challenge->best_time==0&&ptr_challenge->num_visits==0
                 &&!strcmp(ptr_challenge->name,"challenge_1"));
    ptr_challenge++;
    ASSERT("1.9.1",ptr_challenge->id==88&&ptr_challenge->level==Medium
                 &&ptr_challenge->best_time==0&&ptr_challenge->num_visits==0
                 &&!strcmp(ptr_challenge->name,"challenge_8"));
    ptr_challenge++;
    ASSERT("1.9.2",ptr_challenge->id==77&&ptr_challenge->level==Hard
                   &&ptr_challenge->best_time==0&&ptr_challenge->num_visits==0
                   &&!strcmp(ptr_challenge->name,"challenge_7"));


    printf("\n\nNumber of Rooms is: %d\n", (*sys)->number_of_rooms);
    printf("Checking Rooms Array\n");
    ptr_challenge=(*sys)->all_challenges;
    ChallengeRoom *ptr_room=(*sys)->all_rooms;
    ChallengeActivity *ptr_activities=NULL;

    /*1st room*/
    ASSERT("2.1",!strcmp(ptr_room->name,"room_2")
                 &&ptr_room->num_of_challenges==1)
    ptr_activities=ptr_room->challenges;
    ASSERT("2.1.1",ptr_activities->challenge==ptr_challenge+2);

    /*2nd room*/
    ptr_room++;
    ASSERT("2.2",!strcmp(ptr_room->name,"room_1")
                 &&ptr_room->num_of_challenges==3)
    ptr_activities=ptr_room->challenges;
    ASSERT("2.2.1",ptr_activities->challenge==ptr_challenge+5);
    ptr_activities++;
    ASSERT("2.2.2",ptr_activities->challenge==ptr_challenge+0);
    ptr_activities++;
    ASSERT("2.2.3",ptr_activities->challenge==ptr_challenge+4);

    /*3rd room*/
    ptr_room++;
    ASSERT("2.3",!strcmp(ptr_room->name,"room_3")
                 &&ptr_room->num_of_challenges==3)
    ptr_activities=ptr_room->challenges;
    ASSERT("2.3.1",ptr_activities->challenge==ptr_challenge+3);
    ptr_activities++;
    ASSERT("2.3.2",ptr_activities->challenge==ptr_challenge+1);
    ptr_activities++;
    ASSERT("2.3.3",ptr_activities->challenge==ptr_challenge+5);

    /*4th room*/
    ptr_room++;
    ASSERT("2.4",!strcmp(ptr_room->name,"room_4")
                 &&ptr_room->num_of_challenges==4)
    ptr_activities=ptr_room->challenges;
    ASSERT("2.4.1",ptr_activities->challenge==ptr_challenge+2);
    ptr_activities++;
    ASSERT("2.4.2",ptr_activities->challenge==ptr_challenge+0);
    ptr_activities++;
    ASSERT("2.4.3",ptr_activities->challenge==ptr_challenge+3);
    ptr_activities++;
    ASSERT("2.4.4",ptr_activities->challenge==ptr_challenge+4);

    /*5th room*/
    ptr_room++;
    ASSERT("2.5",!strcmp(ptr_room->name,"room_5")
                 &&ptr_room->num_of_challenges==8)
    ptr_activities=ptr_room->challenges;
    ASSERT("2.5.1",ptr_activities->challenge==ptr_challenge+5);
    ptr_activities++;
    ASSERT("2.5.2",ptr_activities->challenge==ptr_challenge+2);
    ptr_activities++;
    ASSERT("2.5.3",ptr_activities->challenge==ptr_challenge+1);
    ptr_activities++;
    ASSERT("2.5.4",ptr_activities->challenge==ptr_challenge+0);
    ptr_activities++;
    ASSERT("2.5.5",ptr_activities->challenge==ptr_challenge+3);
    ptr_activities++;
    ASSERT("2.5.6",ptr_activities->challenge==ptr_challenge+4);
    ptr_activities++;
    ASSERT("2.5.7",ptr_activities->challenge==ptr_challenge+7);
    ptr_activities++;
    ASSERT("2.5.8",ptr_activities->challenge==ptr_challenge+6);

    /*6th room*/
    ptr_room++;
    ASSERT("2.6",!strcmp(ptr_room->name,"WILL_BE_CHANGE")
                 &&ptr_room->num_of_challenges==2)
    ptr_activities=ptr_room->challenges;
    ASSERT("2.6.1",ptr_activities->challenge==ptr_challenge+7);
    ptr_activities++;
    ASSERT("2.6.2",ptr_activities->challenge==ptr_challenge+6);
    return 0;
}

int main(int argc, char **argv) {
    ChallengeRoomSystem *sys=NULL;
    int p=0,f=0;
    int *passed=&p,*failed=&f;
    char *output_most_popular=NULL;
    char *output_record_challnge=NULL;
    if(check_creation_system(&sys,passed,failed))
        return 0;
    printf("\n\nNow Destroying System and start over\n");
    Result t2=destroy_system(sys, 0, &output_most_popular,
                             &output_record_challnge);
    ASSERT("2.7", t2 == OK && output_record_challnge == NULL &&
                  output_most_popular == NULL);
    if(check_creation_system(&sys,passed,failed))
        return 0;
    char new_name_for_room[7]={'r', 'o', 'o', 'm', '_', '6', '\0'};
    Result t3=change_system_room_name(NULL, "WILL_BE_CHANGE",
                                      new_name_for_room);
    ASSERT("3.1", t3 == NULL_PARAMETER);
    t3=change_system_room_name(sys, NULL, new_name_for_room);
    ASSERT("3.2", t3 == NULL_PARAMETER);
    t3=change_system_room_name(sys, "WILL_BE_CHANGE", NULL);
    ASSERT("3.3", t3 == NULL_PARAMETER);
    t3=change_system_room_name(sys, "WILL_BE_CHANGE", new_name_for_room);
    new_name_for_room[0]='#';
    ASSERT("3.4", t3 == OK && !strcmp((sys)->all_rooms[5].name, "room_6"));

    char new_name_for_challenge[]={'c', 'h', 'a', 'l', 'l', 'e', 'n', 'g', 'e',
                                   '_', '3', '\0'};
    Result t4=change_challenge_name(NULL, 33, new_name_for_challenge);
    ASSERT("4.1", t4 == NULL_PARAMETER);
    t4=change_challenge_name(sys, 33, NULL);
    ASSERT("4.2", t4 == NULL_PARAMETER);
    t4=change_challenge_name(sys, 33, new_name_for_challenge);
    new_name_for_challenge[0]='#';
    ASSERT("4.3",
           t4 == OK && !strcmp((sys)->all_challenges[1].name, "challenge_3"));

    Result t5=visitor_quit(NULL, 2, 0);
    ASSERT("5.1", t5 == NULL_PARAMETER);
   t5=visitor_quit(sys, 2, 0);
    ASSERT("5.2", t5==NOT_IN_ROOM);
    t5=visitor_arrive(NULL,"room_4","Ido", 204, All_Levels, 5);
    ASSERT("5.3", t5 == NULL_PARAMETER && sys->last_update_time == 0);
    t5=visitor_quit(sys, 204, 0);
    ASSERT("5.4", t5==NOT_IN_ROOM);
    t5=visitor_arrive(sys, NULL, "Ido", 204, All_Levels, 5);
    ASSERT("5.5", t5 == ILLEGAL_PARAMETER);
    t5=visitor_arrive(sys, "room_4", NULL, 204, All_Levels, 5);
    ASSERT("5.6", t5 == ILLEGAL_PARAMETER);
    t5=visitor_arrive(sys, "r", "Ido", 204, All_Levels, 5);
    ASSERT("5.7", t5 == NO_AVAILABLE_CHALLENGES && sys->all_visitors == NULL);
    t5=visitor_arrive(sys, "room_4", "Ido", 204, All_Levels, 5);
    ASSERT("5.8", t5 == OK && sys->all_challenges[2].num_visits == 1 &&
                  sys->all_rooms[3].challenges[0].visitor->visitor_id == 204 &&
                  !strcmp(sys->all_rooms[3].challenges[0].visitor->visitor_name,
                          "Ido"));

    t5=system_room_of_visitor(NULL, NULL, NULL);
    ASSERT("5.9.1", t5 == NULL_PARAMETER);
    t5=system_room_of_visitor(sys, "I", NULL);
    ASSERT("5.9.2", t5 == ILLEGAL_PARAMETER);
    char *output_room_name=NULL;
    t5=system_room_of_visitor(sys, NULL, &output_room_name);
    ASSERT("5.9.3", t5 == ILLEGAL_PARAMETER);
    t5=system_room_of_visitor(sys, "I", &output_room_name);
    ASSERT("5.9.4", t5 == NOT_IN_ROOM && output_room_name == NULL);
    t5=system_room_of_visitor(sys, "Ido", &output_room_name);
    ASSERT("5.9.5", t5 == OK && !strcmp(output_room_name, "room_4") && strlen
                                                                               (output_room_name) ==
                                                                       6 &&
                    output_room_name[6] == '\0');
    FREE_NULL(output_room_name);

    Result t6=visitor_arrive(sys, "room_2", "Shlomi", 203, Easy, 3);
    ASSERT("6.1", t6 == ILLEGAL_TIME && sys->last_update_time == 5);
    t6=visitor_arrive(sys, "room_2", "Shlomi", 203, Medium, 10);
    ASSERT("6.2", t6 == OK && sys->last_update_time == 10);
    ASSERT("6.3", sys->all_challenges[2].num_visits == 2 &&
                  sys->all_rooms[0].challenges[0].visitor->visitor_id == 203 &&
                  !strcmp(sys->all_rooms[0].challenges[0]
                                  .visitor->visitor_name, "Shlomi"));
    t6=visitor_arrive(sys, "room_3", "Eyal", 202, Hard, 15);
    ASSERT("6.4", t6 == OK && sys->last_update_time == 15);
    ASSERT("6.5", sys->all_challenges[1].num_visits == 1 &&
                  sys->all_rooms[2].challenges[1].visitor->visitor_id == 202 &&
                  !strcmp(sys->all_rooms[2].challenges[1]
                                  .visitor->visitor_name, "Eyal"));
    t6=visitor_arrive(sys, "room_3", "Gal", 201, Hard, 15);
    ASSERT("6.6", t6 == OK && sys->last_update_time == 15);
    ASSERT("6.7", sys->all_challenges[3].num_visits == 1 &&
                  sys->all_rooms[2].challenges[0].visitor->visitor_id == 201 &&
                  !strcmp(sys->all_rooms[2].challenges[0]
                                  .visitor->visitor_name, "Gal"));
    t6=visitor_arrive(sys, "room_3", "Tamir", 200, Hard, 15);
    ASSERT("6.8", t6 == NO_AVAILABLE_CHALLENGES && sys->last_update_time == 15);
    t6=system_room_of_visitor(sys, "Tamir", &output_room_name);
    ASSERT("6.9", t6 == NOT_IN_ROOM&&output_room_name==NULL);
    FREE_NULL(output_room_name);
    t6=visitor_arrive(sys, "room_5", "Tamir", 200, Hard, 15);
    ASSERT("6.9.1", sys->all_challenges[1].num_visits == 2 &&
                    sys->all_rooms[4].challenges[2].visitor->visitor_id ==
                    200 &&
                    !strcmp(sys->all_rooms[4].challenges[2]
                                    .visitor->visitor_name, "Tamir"));

    Result t7=visitor_quit(sys, 204, 10);
    ASSERT("7.1", t7 == ILLEGAL_TIME && sys->last_update_time == 15);
    t7=visitor_quit(sys, 204, 20);
    ASSERT("7.2", t7 == OK && sys->last_update_time == 20);
    t7=visitor_quit(sys, 204, 50);
    ASSERT("7.3", t7 == NOT_IN_ROOM && sys->last_update_time == 20);
    t7=all_visitors_quit(NULL, 30);
    ASSERT("7.4", t7=NULL_PARAMETER);
    t7=all_visitors_quit(sys, 14);
    ASSERT("7.5", t7=ILLEGAL_TIME);
    t7=all_visitors_quit(sys, 30);
    ASSERT("7.6", t7 == OK && sys->last_update_time == 30 &&
                  sys->all_visitors == NULL);

    Result t8=most_popular_challenge(NULL, &output_most_popular);
    ASSERT("8.1", t8 == NULL_PARAMETER);
    t8=most_popular_challenge(sys, NULL);
    ASSERT("8.2", t8 == NULL_PARAMETER);
    t8=most_popular_challenge(sys, &output_most_popular);
    ASSERT("8.2", t8 == OK && !strcmp(output_most_popular, "challenge_2"));
    FREE_NULL(output_most_popular);
    t8=best_time_of_system_challenge(NULL, NULL, NULL);
    ASSERT("8.3", t8 == NULL_PARAMETER);
    int time=-5;
    t8=best_time_of_system_challenge(sys, "I", &time);
    ASSERT("8.4", t8=ILLEGAL_PARAMETER);
    t8=best_time_of_system_challenge(sys, "challenge_3", &time);
    ASSERT("8.5", t8 == OK && time == 15);

    Result t9=visitor_arrive(sys, "room_4", "Ido", 206, Hard, 40);
    ASSERT("9.1", t9 == OK && sys->all_visitors != NULL &&
                  sys->last_update_time == 40);
    ASSERT("9.2", sys->all_challenges[3].num_visits == 2 &&
                  sys->all_rooms[3].challenges[2].visitor->visitor_id == 206 &&
                  !strcmp(sys->all_rooms[3].challenges[2]
                                  .visitor->visitor_name, "Ido"));
    Result t10=destroy_system(NULL, 55, &output_most_popular,
                              &output_record_challnge);
    ASSERT("10.1", t10 == NULL_PARAMETER && sys->last_update_time == 40 &&
                   sys->all_visitors !=
            NULL&&output_most_popular==NULL&&output_record_challnge==NULL);
   t10=destroy_system(sys, 39, &output_most_popular,&output_record_challnge);
    ASSERT("10.2", t10 == ILLEGAL_TIME && sys->last_update_time == 40
                   && sys->all_visitors != NULL);

    t10=destroy_system(sys, 55, &output_most_popular,&output_record_challnge);
    ASSERT("10.3", t10 == OK &&!strcmp(output_most_popular,"challenge_2")
            &&!strcmp(output_record_challnge,"challenge_2"));
    FREE_NULL(output_most_popular);
    FREE_NULL(output_record_challnge);
    printf(BORDER);
    SUMMARIZE(p,f);
    return 0;
}