#include "Enigma.h"
#include "Exceptions.h"

#define DEFAULT_NUM_ELEMENTS 0
using namespace mtm::escaperoom;

Enigma::Enigma(const std::string& name, const Difficulty& difficulty,
                const int& numOfElements, const set<string>& elements):
        name(name),difficulty(difficulty),numOfElements(numOfElements),enigma_elements(elements){
    if((int)enigma_elements.size()!=numOfElements){
        throw EnigmaIllegalSizeParamException();
    }
}
Enigma::Enigma(const std::string &name, const Difficulty &difficulty):name(name)
,difficulty(difficulty),numOfElements(DEFAULT_NUM_ELEMENTS){}

bool Enigma::operator==(const Enigma& enigma) const{
    return (name==enigma.name)&&(difficulty==enigma.difficulty);
}

bool Enigma::operator!=(const Enigma& enigma) const{
    return !(*this==enigma);
}

bool Enigma::operator<(const Enigma& enigma) const{
    return difficulty<enigma.difficulty;
}

bool Enigma::operator>(const Enigma& enigma) const{
    return difficulty>enigma.difficulty;
}

bool Enigma::areEqualyComplex(const Enigma& enigma) const{
   return(difficulty==enigma.difficulty)&&(numOfElements==enigma.numOfElements);
}

Difficulty Enigma::getDifficulty() const{
    return difficulty;
}

string Enigma::getName() const{
    return name;
}

std::ostream& mtm::escaperoom::operator<<(std::ostream& output, const Enigma& enigma) {
    output << enigma.name << " (" << enigma.difficulty << ") "
           << enigma.numOfElements;
    return output;
}

void Enigma::addElement(const string &element) {
    enigma_elements.insert(element);
    numOfElements=enigma_elements.size();
}

void Enigma::removeElement(const string& element){
    if(enigma_elements.empty()){
        throw EnigmaNoElementsException();
    }
    if(!enigma_elements.erase(element)){
        throw EnigmaElementNotFoundException();
    }
    numOfElements--;
}