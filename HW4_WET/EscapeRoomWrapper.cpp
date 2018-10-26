#include <assert.h>
#include "EscapeRoomWrapper.h"
#include "Exceptions.h"

#define DEFAULT_TIME 60
#define DEFAULT_PARTICIPANTS 6
#define BASE "BASE_ROOM"
using namespace mtm::escaperoom;

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& escapeTime, const int& level,
                  const int& maxParticipants)
        :room_struct(escapeRoomCreate(name,escapeTime,maxParticipants,level)){
    if(room_struct==NULL){
        throw EscapeRoomMemoryProblemException();
    }
}

EscapeRoomWrapper::EscapeRoomWrapper(char* name, const int& level):
           room_struct(escapeRoomCreate(name,DEFAULT_TIME,DEFAULT_PARTICIPANTS,level)){
    if(room_struct==NULL){
        throw EscapeRoomMemoryProblemException();
    }
}

EscapeRoomWrapper::EscapeRoomWrapper(const EscapeRoomWrapper& room):
        room_struct(escapeRoomCopy(room.room_struct)),room_enigmas(room.room_enigmas){
    if(room_struct==NULL){
        throw EscapeRoomMemoryProblemException();
    }
}

EscapeRoomWrapper::~EscapeRoomWrapper(){
    escapeRoomDestroy(room_struct);
}

EscapeRoomWrapper& EscapeRoomWrapper::operator=(const EscapeRoomWrapper& room){
    if(this==&room){
        return *this;
    }
    escapeRoomDestroy(room_struct);
    room_struct=escapeRoomCopy(room.room_struct);
    room_enigmas=room.room_enigmas;
    return *this;
}

int EscapeRoomWrapper::level() const {
    assert(room_struct!=NULL);
    return getLevel(room_struct);
}

void EscapeRoomWrapper::rate(const int& newRate){
    assert(room_struct!=NULL);
    if(updateRate(room_struct, newRate)==ESCAPEROOM_BAD_PARAM){
        throw EscapeRoomIllegalRateException();
    }
}

std::string EscapeRoomWrapper::getName() const{
    assert(room_struct!=NULL);
    char* temp=roomGetName(room_struct);
    if(temp==NULL){
        return NULL;
    }
    std::string name(temp);
    free(temp);
    return name;
}

double EscapeRoomWrapper::getRate() const{
    assert(room_struct!=NULL);
    return roomGetRate(room_struct);
}

int EscapeRoomWrapper::getMaxTime() const{
    assert(room_struct!=NULL);
    return roomGetMaxTime(room_struct);
}

int EscapeRoomWrapper::getMaxParticipants() const{
    assert(room_struct!=NULL);
    return roomGetMaxParticipants(room_struct);
}

bool EscapeRoomWrapper::operator==(const EscapeRoomWrapper& room) const{
    assert(room_struct!=NULL);
    assert(room.room_struct!=NULL);
    return areEqualRooms(room_struct,room.room_struct);
}

bool EscapeRoomWrapper::operator!=(const EscapeRoomWrapper& room) const{
    return !(*this==room);
}

bool EscapeRoomWrapper::operator>(const EscapeRoomWrapper& room) const{
    assert(room_struct!=NULL);
    assert(room.room_struct!=NULL);
    return isBiggerRoom(room_struct,room.room_struct);
}

bool EscapeRoomWrapper::operator<(const EscapeRoomWrapper& room) const{
    assert(room_struct!=NULL);
    assert(room.room_struct!=NULL);
    return !isBiggerRoom(room_struct,room.room_struct);
}

void EscapeRoomWrapper::print(std::ostream &output) const {
    output << getName() << " (" << getMaxTime() <<
           '/' << level() << '/' << getMaxParticipants();
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output, const EscapeRoomWrapper& room) {
    assert(room.room_struct!=NULL);
    room.print(output);
    output << ')';
    return output;
}
void EscapeRoomWrapper::addEnigma(const Enigma& enigma){
    room_enigmas.push_back(enigma);
}

void EscapeRoomWrapper::removeEnigma(const Enigma &enigma) {
    if(room_enigmas.empty()){
        throw EscapeRoomNoEnigmasException();
    }
    for(int i=0;i<(int)room_enigmas.size();i++){
        if(room_enigmas[i]==enigma){
            room_enigmas.erase(room_enigmas.begin()+i);
            return;
        }
    }
    throw EscapeRoomEnigmaNotFoundException();
}

Enigma EscapeRoomWrapper::getHardestEnigma() const{
    if (room_enigmas.empty()) {
        throw EscapeRoomNoEnigmasException();
    }
    int max_enigma_index = 0;
    for (int i = 0; i <(int)room_enigmas.size(); i++) {
        if (room_enigmas[i].getDifficulty() >
            room_enigmas[max_enigma_index].getDifficulty()) {
            max_enigma_index = i;
        }
    }
    return room_enigmas[max_enigma_index];
}

vector<Enigma>& EscapeRoomWrapper::getAllEnigmas() {
    return room_enigmas;
}

const string EscapeRoomWrapper::getType() const {
    return BASE;
}

EscapeRoomWrapper* EscapeRoomWrapper::copyToHeap() const{
    return new EscapeRoomWrapper(*this);
}