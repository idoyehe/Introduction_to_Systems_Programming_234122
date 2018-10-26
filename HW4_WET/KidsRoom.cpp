#include "KidsRoom.h"
#define KIDS_ROOM "KIDS_ROOM"

using namespace mtm::escaperoom;

KidsRoom::KidsRoom(char *name, const int &escapeTime, const int &level,
                     const int &maxParticipants, const int &ageLimit):
        EscapeRoomWrapper(name,escapeTime,level,maxParticipants),
        age_limit(ageLimit){
}

void KidsRoom::setNewAgeLimit(const int& limit){
    if(limit<0){
        throw KidsRoomIllegalAgeLimit();
    }
    age_limit=limit;
}

int KidsRoom::getAgeLimit() const{
    return age_limit;
}

void KidsRoom::print(std::ostream &output) const {
    const std::string type = "Kids Room: ";
    output << type;
    EscapeRoomWrapper::print(output);
    output <<'/'<< getAgeLimit();
}

const string KidsRoom::getType() const {
    return KIDS_ROOM;
}

KidsRoom* KidsRoom::copyToHeap() const{
    return new KidsRoom (*this);
}