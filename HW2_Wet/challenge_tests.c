#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "constants.h"
#include "challenge.h"

#define ASSERT(test_number, test_condition)  \
   if (!(test_condition)) {printf("\nTEST %s FAILED", test_number); } \
   else printf("\nTEST %s OK", test_number);

#define SIZE_CHALLENGE sizeof(Challenge)

int main(int argc, char **argv) {
    Challenge *challenge = (Challenge *) malloc(SIZE_CHALLENGE);
    if (challenge == NULL) {
        printf("No Allocation Success Exist test");
        return 0;
    }
    Result t1 = init_challenge(challenge, 101, "C1", Easy);
    bool tb1 = (challenge->id == 101) && (!strcmp(challenge->name, "C1")) &&
               (challenge->level == Easy) && (challenge->num_visits == 0) &&
               (challenge->best_time == 0);
    ASSERT("1.1", t1 == OK)
    ASSERT("1.2", tb1)

    Result t2 = init_challenge(NULL, 1, "i", Hard);
    ASSERT("2.1", t2 == NULL_PARAMETER);

    Result t3 = init_challenge(challenge, 1, NULL, Hard);
    bool tb3 = (challenge->id == 101) && (!strcmp(challenge->name, "C1")) &&
               (challenge->level == Easy) && (challenge->num_visits == 0) &&
               (challenge->best_time == 0);

    ASSERT("3.1", t3 == NULL_PARAMETER);
    ASSERT("3.2", tb3);

    char new_name[4] = {'C', 'H', '1', '\0'};
    Result t4 = change_name(challenge, new_name);
    new_name[0] = 'I';
    ASSERT("4.1", t4 == OK);
    t4 = change_name(challenge, NULL);
    ASSERT("4.2", t4 == NULL_PARAMETER);
    bool tb4 = (challenge->id == 101) && (!strcmp(challenge->name, "CH1")) &&
               (challenge->level == Easy) && (challenge->num_visits == 0) &&
               (challenge->best_time == 0);
    ASSERT("4.3", tb4);

    Result t5 = set_best_time_of_challenge(challenge, -5);
    ASSERT("5.1",t5==ILLEGAL_PARAMETER);
    t5 = set_best_time_of_challenge(NULL, -5);
    ASSERT("5.2",t5==NULL_PARAMETER);

    Result t6 = set_best_time_of_challenge(challenge, 50);
    ASSERT("6.1",t6==OK);
    ASSERT("6.2",challenge->best_time==50);
    t6 = set_best_time_of_challenge(challenge, 60);
    ASSERT("6.3",t6==ILLEGAL_PARAMETER);
    ASSERT("6.4",challenge->best_time==50);
    t6 = set_best_time_of_challenge(challenge, 40);
    ASSERT("6.5",t6==OK);
    ASSERT("6.6",challenge->best_time==40);

    int time=-5;
    Result t7=best_time_of_challenge(NULL,&time);
    ASSERT("7.1",(t7==NULL_PARAMETER)&&time==-5);
    t7=best_time_of_challenge(challenge,&time);
    ASSERT("7.2",t7==OK);
    ASSERT("7.3",time==challenge->best_time);
    bool tb8 = (challenge->id == 101) && (!strcmp(challenge->name, "CH1")) &&
               (challenge->level == Easy) && (challenge->num_visits == 0) &&
               (challenge->best_time == time);
    ASSERT("7.4",tb8);

    Result t8=inc_num_visits(challenge);
    ASSERT("8.1",t8==OK);
    for(int i=0;i<10;++i){
        t8=inc_num_visits(challenge);
    }
    ASSERT("8.2",t8==OK);
    ASSERT("8.3",challenge->num_visits==11);


    int visits=-5;
    Result t9=num_visits(NULL,&visits);
    ASSERT("9.1",(t9==NULL_PARAMETER)&&visits==-5);
    t9=num_visits(challenge,&visits);
    ASSERT("9.2",t9==OK);
    ASSERT("9.3",visits==challenge->num_visits);
    bool tb9 = (challenge->id == 101) && (!strcmp(challenge->name, "CH1")) &&
               (challenge->level == Easy);
    ASSERT("9.4",tb9);

    Result t10=reset_challenge(NULL);
    ASSERT("10.1",t10==NULL_PARAMETER);
    t10=reset_challenge(challenge);
    ASSERT("10.2",t10==OK);
    bool tb10 = (challenge->id == 0) &&(challenge->name==NULL) &&
               (challenge->level == 0)&&(challenge->best_time==0)&&
            (challenge->num_visits==0);
    ASSERT("10.3",tb10);
    free(challenge);
    return 0;
}
