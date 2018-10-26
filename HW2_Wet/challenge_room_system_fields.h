#ifndef CHALLENGE_ROOM_SYSTEM_FIELDS_H_
#define CHALLENGE_ROOM_SYSTEM_FIELDS_H_

#include "challenge.h"
#include "visitor_room.h"

char *system_name;
Challenge *all_challenges;
int number_of_challenges;
ChallengeRoom *all_rooms;
int number_of_rooms;
struct SVisitorNode *all_visitors;
int last_update_time;

#endif // CHALLENGE_ROOM_SYSTEM_FIELDS_H_