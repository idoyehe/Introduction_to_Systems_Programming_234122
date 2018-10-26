#ifndef HW4_WET_KIDSROOM_H
#define HW4_WET_KIDSROOM_H

#include "EscapeRoomWrapper.h"
#include "Exceptions.h"

namespace mtm{
    namespace escaperoom {

        class KidsRoom : public EscapeRoomWrapper{
        private:
            int age_limit;

            // Prints the data of the Scary Room in the following format:
            //
            // Scary Room: "<name> (<maxTime>/<level>/<maxParticipants>/<ageLimit>)"
            //
            // @param output : the output stream to which the data is printed.
            // @param room : the room whose data is printed.
            void print(std::ostream& output) const override;
        public:
            // Constructs a new Kids Room with the specified data.
            //
            // @param name : the name of the escape room.
            // @param escapeTime : the maximal escape time allowed in the room.
            // @param level : the level of the escape room.
            // @param maxParticipants: the maximal participants allowed in the room.
            // @param age limit: the age limit for the room
            // The rest of the room's data is initialized as described in the exercise sheet.
            // @throws EscapeRoomMemoryProblemException in case of creation failure.
            //@throws KidsRoomIllegalAgeLimit in case ag limit is negative
            KidsRoom(char* name, const int& escapeTime,const int& level,
                      const int& maxParticipants, const int& ageLimit);
            // the method changes the age limit according to the limit given.
            //
            // @param limit : the new limit accepted to the room.
            //@throws KidsRoomIllegalAgeLimit in case ag limit is negative
            void setNewAgeLimit(const int& limit);

            // the method return the age limit of the room.
            //
            int getAgeLimit() const;

            //return by const string that say it is "KIDS_ROOM"
            //
            const string getType() const override;

            // copy the KidsRoom to the heap using new allocation
            //
            // return pointer to the allocation to the heap
            virtual KidsRoom* copyToHeap() const override ;
        };

} // end of namespace eascaperoom
} // end of namespace mtm

#endif //HW4_WET_KIDSROOM_H