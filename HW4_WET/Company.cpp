#include <assert.h>
#include "Company.h"
#include "Exceptions.h"


#define BASE "BASE_ROOM"
#define SCARY "SCARY_ROOM"
#define KIDS "KIDS_ROOM"

using namespace mtm::escaperoom;


set<EscapeRoomWrapper*>::iterator Company::findRoom(const EscapeRoomWrapper& room) const{
    set<EscapeRoomWrapper*>::iterator it;
    for(it=all_rooms.begin();it!=all_rooms.end();it++) {
       if(*(*it)==room){
           return it;
       }
    }
    throw CompanyRoomNotFoundException();
}

Company::Company(string name, string phoneNumber):name(name),
                                                  telephone(phoneNumber){}

Company::Company(const Company &company):name(company.name),
                telephone(company.telephone){
    set<EscapeRoomWrapper*>::iterator it;
    for(it=company.all_rooms.begin();it!=company.all_rooms.end();it++){
        EscapeRoomWrapper* room_to_add=(*it)->copyToHeap();
        all_rooms.insert(room_to_add);
    }
}
Company& Company::operator=(const Company &company) {
    if(this==&company){
        return *this;
    }
    set<EscapeRoomWrapper*>::iterator it=all_rooms.begin();
    for(it=all_rooms.begin();it!=all_rooms.end();++it){
        EscapeRoomWrapper *to_delete=*it;
        delete(to_delete);
    }
    all_rooms.clear();
    assert(!all_rooms.size());
    name= company.name;
    telephone=company.telephone;
    for(it=company.all_rooms.begin();it!=company.all_rooms.end();it++){
        EscapeRoomWrapper* room_to_add=(*it)->copyToHeap();
        all_rooms.insert(room_to_add);
    }
    return *this;
}

void Company::createRoom(char *name, const int &escapeTime, const int &level,
                         const int &maxParticipants) {
    try {
        EscapeRoomWrapper *room_to_add = new
                EscapeRoomWrapper(
                EscapeRoomWrapper(name, escapeTime, level, maxParticipants));
        all_rooms.insert(room_to_add);
    }catch (EscapeRoomMemoryProblemException&){
        throw CompanyMemoryProblemException();
    }
}

void Company::createScaryRoom(char *name, const int &escapeTime,
                              const int &level, const int &maxParticipants,
                              const int &ageLimit,
                              const int &numOfScaryEnigmas) {
    try {
        EscapeRoomWrapper *room_to_add = new
                ScaryRoom(
                ScaryRoom(name, escapeTime, level, maxParticipants,ageLimit,numOfScaryEnigmas));
        all_rooms.insert(room_to_add);
    }catch (EscapeRoomMemoryProblemException&){
        throw CompanyMemoryProblemException();
    }
}

void Company::createKidsRoom(char *name, const int &escapeTime,
                             const int &level, const int &maxParticipants,
                             const int &ageLimit) {
    try {
        EscapeRoomWrapper *room_to_add = new
                KidsRoom(
                KidsRoom(name,escapeTime,level,maxParticipants,ageLimit));
        all_rooms.insert(room_to_add);
    }catch (EscapeRoomMemoryProblemException&){
        throw CompanyMemoryProblemException();
    }
}

set<EscapeRoomWrapper*> Company::getAllRooms() const {
    return all_rooms;
}

void Company::removeRoom(const EscapeRoomWrapper& room){
    try {
        set<EscapeRoomWrapper *>::iterator it = findRoom(room);
        delete (*it);
        all_rooms.erase(it);
    }catch(CompanyRoomNotFoundException&){
        throw CompanyRoomNotFoundException();
    }
}

void Company::addEnigma(const EscapeRoomWrapper &room, const Enigma &enigma) {
    try {
        set<EscapeRoomWrapper *>::iterator it = findRoom(room);
        (*it)->addEnigma(enigma);
    }
    catch(CompanyRoomNotFoundException&){
        throw CompanyRoomNotFoundException();
    }
}

void Company::removeEnigma(const EscapeRoomWrapper &room,
                           const Enigma &enigma) {
    try {
        set<EscapeRoomWrapper *>::iterator it = findRoom(room);
        (*it)->removeEnigma(enigma);
    }
    catch(CompanyRoomNotFoundException&){
        throw CompanyRoomNotFoundException();
    }
    catch (EscapeRoomNoEnigmasException&) {
        throw CompanyRoomHasNoEnigmasException();
    }
    catch (EscapeRoomEnigmaNotFoundException&) {
        throw CompanyRoomEnigmaNotFoundException();
    }
}

void Company::addItem(const EscapeRoomWrapper &room, const Enigma &enigma,
                      const string &element) {
    try {
        set<EscapeRoomWrapper *>::iterator it = findRoom(room);
        vector<Enigma>& room_enigmas=(*it)->getAllEnigmas();
        for(int i=0;i<(int)room_enigmas.size();i++) {
            if (room_enigmas[i] == enigma) {
                room_enigmas[i].addElement(element);
                return;
            }
        }
        throw CompanyRoomEnigmaNotFoundException();
    }
    catch(CompanyRoomNotFoundException&) {
        throw CompanyRoomNotFoundException();
    }
}

void Company::removeItem(const EscapeRoomWrapper &room, const Enigma &enigma,
                         const string &element) {
    try {
        set<EscapeRoomWrapper *>::iterator it = findRoom(room);
        vector<Enigma> &room_enigmas = (*it)->getAllEnigmas();
        for (int i = 0; i < (int) room_enigmas.size(); i++) {
            if (room_enigmas[i] == enigma) {
                room_enigmas[i].removeElement(element);
                return;
            }
        }
        throw CompanyRoomEnigmaNotFoundException();
    }
    catch (CompanyRoomNotFoundException &) {
        throw CompanyRoomNotFoundException();
    }
    catch (EnigmaNoElementsException &) {
        throw CompanyRoomEnigmaHasNoElementsException();
    }
    catch (EnigmaElementNotFoundException &) {
        throw CompanyRoomEnigmaElementNotFoundException();
    }
}


set<EscapeRoomWrapper *> Company::getAllRoomsByType(RoomType type) const {
    string requested_type;
    switch (type) {
        case SCARY_ROOM: requested_type = SCARY; break;
        case KIDS_ROOM:requested_type =KIDS; break;
        default: requested_type = BASE; break;
    }
    set <EscapeRoomWrapper*>::iterator it;
    set <EscapeRoomWrapper*> requested_set;
    for(it=all_rooms.begin();it!=all_rooms.end();it++) {
        if ((*it)->getType() == requested_type) {
            requested_set.insert(*it);
        }
    }
    return requested_set;
}

EscapeRoomWrapper* Company::getRoomByName(const string &name) const {
    set<EscapeRoomWrapper*>::iterator it;
    for(it=all_rooms.begin();it!=all_rooms.end();it++) {
        if((*it)->getName()==name){
            return *it;
        }
    }
    throw CompanyRoomNotFoundException();
}


std::ostream& mtm::escaperoom::operator<<(std::ostream &output,
                                          const Company &company) {
    output << company.name << " : " << company.telephone << std::endl;
    set<EscapeRoomWrapper*>::iterator it;
    for(it=company.all_rooms.begin();it!=company.all_rooms.end();it++) {
        output << *(*it) << std::endl;
    }
    return output;
}


Company::~Company() {
    set<EscapeRoomWrapper*>::iterator it;
    for(it=all_rooms.begin();it!=all_rooms.end();it++) {
        delete (*it);
    }
}