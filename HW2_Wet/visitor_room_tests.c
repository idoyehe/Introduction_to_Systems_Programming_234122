#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "visitor_room.h"

#define SIZE_CHAR sizeof(char)
#define SIZE_ACTIVITY sizeof(ChallengeActivity)
#define SIZE_CHALLENGE sizeof(Challenge)
#define SIZE_ROOM sizeof(ChallengeRoom)
#define SIZE_VISITOR sizeof(Visitor)
#define CHALLENGES_NUMBER 5

#define ASSERT(test_number, test_condition)  \
   if (!(test_condition)) {printf("\nTEST %s FAILED", test_number); } \
   else printf("\nTEST %s OK", test_number);


int main(int argc, char **argv) {
    Challenge *c1=(Challenge *) malloc(SIZE_CHALLENGE);
    if(c1 == NULL){
        printf("No Allocation Success Exist test");
        return 0;
    }
    Challenge *c2=(Challenge *) malloc(SIZE_CHALLENGE);
    if(c2 == NULL){
        printf("No Allocation Success Exist test");
        free(c1);
        return 0;
    }
    Challenge *c3=(Challenge *) malloc(SIZE_CHALLENGE);
    if(c3 == NULL){
        printf("No Allocation Success Exist test");
        free(c2);
        free(c1);
        return 0;
    }
    Challenge *c4=(Challenge *) malloc(SIZE_CHALLENGE);
    if(c4 == NULL){
        printf("No Allocation Success Exist test");
        free(c3);
        free(c2);
        free(c1);
        return 0;
    }
    Challenge *c5=(Challenge *) malloc(SIZE_CHALLENGE);
    if(c5 == NULL){
        printf("No Allocation Success Exist test");
        free(c4);
        free(c3);
        free(c2);
        free(c1);
        return 0;
    }

    ChallengeActivity *a1=(ChallengeActivity *) malloc(SIZE_ACTIVITY);
    if(a1 == NULL){
        printf("No Allocation Success Exist test");
        free(c4);
        free(c3);
        free(c2);
        free(c1);
        return 0;
    }
    ChallengeActivity *a2=(ChallengeActivity *) malloc(SIZE_ACTIVITY);
    if(a2 == NULL){
        printf("No Allocation Success Exist test");
        free(a1);
        free(c4);
        free(c3);
        free(c2);
        free(c1);
        return 0;
    }
    ChallengeActivity *a3=(ChallengeActivity *) malloc(SIZE_ACTIVITY);
    if(a3 == NULL){
        printf("No Allocation Success Exist test");
        free(a2);
        free(a1);
        free(c4);
        free(c3);
        free(c2);
        free(c1);
        return 0;
    }
    ChallengeActivity *a4=(ChallengeActivity *) malloc(SIZE_ACTIVITY);
    if(a4 == NULL){
        printf("No Allocation Success Exist test");
        free(a3);
        free(a2);
        free(a1);
        free(c4);
        free(c3);
        free(c2);
        free(c1);
        return 0;
    }
    ChallengeActivity *a5=(ChallengeActivity *) malloc(SIZE_ACTIVITY);
    if(a5 == NULL){
        printf("No Allocation Success Exist test");
        free(a4);
        free(a3);
        free(a2);
        free(a1);
        free(c4);
        free(c3);
        free(c2);
        free(c1);
        return 0;
    }
    Visitor *v1=(Visitor *) malloc(SIZE_VISITOR);
    if(v1 == NULL){
        printf("No Allocation Success Exist test");
        free(c5);
        free(c4);
        free(c3);
        free(c2);
        free(c1);
        free(a5);
        free(a4);
        free(a3);
        free(a2);
        free(a1);
        return 0;
    }

    Visitor *v2=(Visitor *) malloc(SIZE_VISITOR);
    if(v2 == NULL){
        printf("No Allocation Success Exist test");
        free(v1);
        free(c5);
        free(c4);
        free(c3);
        free(c2);
        free(c1);
        free(a5);
        free(a4);
        free(a3);
        free(a2);
        free(a1);
        return 0;
    }
    ChallengeRoom *test_room=(ChallengeRoom *) malloc(SIZE_ROOM);
    if(test_room == NULL){
        printf("No Allocation Success Exist test");
        free(v2);
        free(v1);
        free(c5);
        free(c4);
        free(c3);
        free(c2);
        free(c1);
        free(a5);
        free(a4);
        free(a3);
        free(a2);
        free(a1);
        return 0;
    }
    Result ic1=init_challenge(c1, 11, "Ch_1", Easy);
    Result ic2=init_challenge(c2, 22, "Ch_2", Medium);
    Result ic3=init_challenge(c3, 33, "Ch_3", Hard);
    Result ic4=init_challenge(c4, 44, "Ch_4", Easy);
    Result ic5=init_challenge(c5, 55, "Ch_5", Hard);
    ASSERT("1.1", ic1 == OK && ic2 == OK && ic3 == OK && ic4 == OK && ic5 == OK)
    Result ac1=init_challenge_activity(a1, c5);
    Result ac2=init_challenge_activity(a2, c4);
    Result ac3=init_challenge_activity(a3, c3);
    Result ac4=init_challenge_activity(a4, c2);
    Result ac5=init_challenge_activity(a5, c1);
    ASSERT("1.2", ac1 == OK && ac2 == OK && ac3 == OK && ac4 == OK && ac5 == OK)

    char rname[5]={'r', 'o', 'o', 'm', '\0'};
    Result cr1=init_room(test_room, NULL, CHALLENGES_NUMBER);
    ASSERT("2.1", cr1 == NULL_PARAMETER)
    cr1=init_room(NULL, "name", 5);
    ASSERT("2.2", cr1 == NULL_PARAMETER)
    cr1=init_room(test_room, rname, CHALLENGES_NUMBER);
    rname[0]='u';
    ASSERT("2.3", cr1 == OK && !strcmp(test_room->name, "room"))
    cr1=change_room_name(test_room, "my_Room");
    ASSERT("2.4", cr1 == OK && !strcmp(test_room->name, "my_Room"))


    Result iv1=init_visitor(v1, NULL, 204);
    ASSERT("3.1", iv1 == NULL_PARAMETER)
    iv1=init_visitor(NULL, "name", 204);
    ASSERT("3.2", iv1 == NULL_PARAMETER)
    char v1name[4]={'I', 'd', 'o', '\0'};
    iv1=init_visitor(v1, v1name, 204);
    v1name[0]='p';
    ASSERT("3.3", iv1 == OK && !strcmp(v1->visitor_name, "Ido") &&
                  v1->visitor_id == 204)
    ASSERT("3.4", v1->room_name == NULL && v1->current_challenge == NULL)
    printf("\n\nIf one of the tests failed got check your code and don't rely "
                   "next tests\n");
    Result iv2=init_visitor(v2, "Shlomi", 203);
    ASSERT("3.5", iv2 == OK)

    ASSERT("4.1", test_room->challenges[0].challenge == NULL
                  && test_room->challenges[0].start_time == 0 &&
                  test_room->challenges[0].visitor == NULL)
    ASSERT("4.2", test_room->challenges[1].challenge == NULL
                  && test_room->challenges[1]
                             .start_time == 0 && test_room->challenges[1]
                                                         .visitor == NULL)
    ASSERT("4.3", test_room->challenges[2].challenge == NULL
                  && test_room->challenges[2]
                             .start_time == 0 && test_room->challenges[2]
                                                         .visitor == NULL)
    ASSERT("4.4", test_room->challenges[3].challenge == NULL
                  && test_room->challenges[3]
                             .start_time == 0 && test_room->challenges[3]
                                                         .visitor == NULL)
    ASSERT("4.5", test_room->challenges[4].challenge == NULL
                  && test_room->challenges[4]
                             .start_time == 0 && test_room->challenges[4]
                                                         .visitor == NULL)

    test_room->challenges[0]=*a1;
    test_room->challenges[1]=*a2;
    test_room->challenges[2]=*a3;
    test_room->challenges[3]=*a4;
    test_room->challenges[4]=*a5;

    ASSERT("5.1", test_room->challenges[0].challenge == c5
                  && test_room->challenges[0].start_time == 0 &&
                  test_room->challenges[0].visitor == NULL)
    ASSERT("5.2", test_room->challenges[1].challenge == c4
                  && test_room->challenges[1]
                             .start_time == 0 && test_room->challenges[1]
                                                         .visitor == NULL)
    ASSERT("5.3", test_room->challenges[2].challenge == c3
                  && test_room->challenges[2]
                             .start_time == 0 && test_room->challenges[2]
                                                         .visitor == NULL)
    ASSERT("5.4", test_room->challenges[3].challenge == c2
                  && test_room->challenges[3]
                             .start_time == 0 && test_room->challenges[3]
                                                         .visitor == NULL)
    ASSERT("5.5", test_room->challenges[4].challenge == c1
                  && test_room->challenges[4]
                             .start_time == 0 && test_room->challenges[4]
                                                         .visitor == NULL)

    int free_places=-1;
    Result t6=num_of_free_places_for_level(NULL, Easy, &free_places);
    ASSERT("6.1", t6 == NULL_PARAMETER);
    t6=num_of_free_places_for_level(test_room, Easy, &free_places);
    ASSERT("6.2", t6 == OK && free_places == 2);
    t6=num_of_free_places_for_level(test_room, Medium, &free_places);
    ASSERT("6.3", t6 == OK && free_places == 1);
    t6=num_of_free_places_for_level(test_room, Hard, &free_places);
    ASSERT("6.4", t6 == OK && free_places == 2);
    t6=num_of_free_places_for_level(test_room, All_Levels, &free_places);
    ASSERT("6.5", t6 == OK && free_places == 5);
    t6=num_of_free_places_for_level(test_room, 4, &free_places);
    ASSERT("6.6", t6 == OK && free_places == 0);

    Result t7=visitor_quit_room(v1, 10);
    ASSERT("7.1", t7 == NOT_IN_ROOM);
    t7=visitor_enter_room(test_room, v1, All_Levels, 5);
    ASSERT("7.2", t7 == OK);
    /*c1 is chosen and room->activity[4] is taken*/
    ASSERT("7.3", c1->num_visits == 1);//should be OK if updating num_visits
    // of challenge when the visitor gets into the room
    ASSERT("7.4", test_room->challenges[4]
                          .start_time == 5 && test_room->challenges[4]
                                                      .visitor == v1)
    ASSERT("7.5", *(v1->room_name)
                  == test_room->name && v1->current_challenge == (test_room
            ->challenges) + 4)
    char *output=NULL;
    t7=room_of_visitor(v1,&output);
    ASSERT("7.6",t7==OK&&!strcmp(output,"my_Room"));
    t7=visitor_quit_room(v1,10);
    ASSERT("7.7",t7==OK);
    ASSERT("7.8",c1->best_time=5&&c1->num_visits==1)
    ASSERT("7.9",v1->current_challenge==NULL&&v1->room_name==NULL&&v1)
    ASSERT("7.9.1",test_room->challenges[4]
                         .start_time==0&&test_room->challenges[4].visitor==NULL)


    Result t8=visitor_enter_room(test_room,v2,Easy,20);
    ASSERT("8.1",t8==OK);
    ASSERT("8.2", c1->num_visits == 2);//should be OK if updating num_visits
    // of challenge when the visitor gets into the room
    t8=visitor_quit_room(v2,21);
    ASSERT("8.3", c1->num_visits == 2&&c1->best_time==1)


    Result t9=visitor_enter_room(test_room,v1,Medium,30);
    ASSERT("9.1",t9==OK);
    ASSERT("9.2", c2->num_visits == 1);//should be OK if updating num_visits
    // of challenge when the visitor gets into the room
    ASSERT("9.3", test_room->challenges[3]
                          .start_time == 30 && test_room->challenges[3]
                                                      .visitor == v1)
    ASSERT("9.4", *(v1->room_name)
                  == test_room->name && v1->current_challenge == (test_room
            ->challenges) + 3)
    t9=visitor_enter_room(test_room,v2,Medium,40);
    ASSERT("9.5",t9==NO_AVAILABLE_CHALLENGES);
    t9=visitor_quit_room(v1,40);
    ASSERT("9.6",t9==OK&&c2->best_time==10)
    t9=visitor_enter_room(test_room,v2,Medium,50);
    ASSERT("9.7", *(v2->room_name)
                  == test_room->name && v2->current_challenge == (test_room
            ->challenges) + 3)
    ASSERT("9.8", test_room->challenges[3]
                          .start_time == 50 && test_room->challenges[3]
                                                       .visitor == v2)
    t9=visitor_quit_room(v2,70);
    ASSERT("9.9",t9==OK&&c2->best_time==10&&c2->num_visits==2)

    ASSERT("10.1", reset_challenge(c1) == OK && reset_challenge(c2)
                                                == OK &&
                   reset_challenge(c3) == OK && reset_challenge(c4)
                                                == OK &&
                   reset_challenge(c5) == OK);
    ASSERT("10.2", reset_challenge_activity(NULL) == NULL_PARAMETER);
    ASSERT("10.3", reset_visitor(NULL) == NULL_PARAMETER);
    ASSERT("10.4", reset_visitor(v1) == OK&&reset_visitor(v2)==OK);
    ASSERT("10.5",reset_room(NULL)==NULL_PARAMETER);
    ASSERT("10.6",reset_room(test_room)==OK);

    free(output);
    free(v1);
    free(v2);
    free(test_room);
    free(c5);
    free(c4);
    free(c3);
    free(c2);
    free(c1);
    free(a5);
    free(a4);
    free(a3);
    free(a2);
    free(a1);
}
