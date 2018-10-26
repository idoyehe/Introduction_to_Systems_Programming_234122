#include "ScaryRoom.h"
#define SCARY_ROOM "SCARY_ROOM"
using namespace mtm::escaperoom;

ScaryRoom::ScaryRoom(char *name, const int &escapeTime, const int &level,
                     const int &maxParticipants, const int &ageLimit,
                     const int &numOfScaryEnigmas):
        EscapeRoomWrapper(name,escapeTime,level,maxParticipants),
        age_limit(ageLimit),num_of_enigmas(numOfScaryEnigmas){}

void ScaryRoom::setNewAgeLimit(const int& limit){
    if(limit<0){
        throw ScaryRoomIllegalAgeLimit();
    }
    age_limit=limit;
}

void ScaryRoom::incNumberOfScaryEnigmas() {
    num_of_enigmas++;
}

int ScaryRoom::getAgeLimit() const{
    return age_limit;
}

void ScaryRoom::print(std::ostream &output) const {
    const std::string type = "Scary Room: ";
    output << type;
    EscapeRoomWrapper::print(output);
    output <<'/'<< getAgeLimit();
}

const string ScaryRoom::getType() const {
    return SCARY_ROOM;
}

ScaryRoom* ScaryRoom::copyToHeap() const {
    return new ScaryRoom (*this);
}