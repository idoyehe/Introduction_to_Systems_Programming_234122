#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "EscapeTechnion.h"

#define COMPANY_ADD(e,w) !strcmp((e),"company")&&!strcmp((w),"add")
#define COMPANY_REMOVE(e,w) !strcmp((e),"company")&&!strcmp((w),"remove")
#define ROOM_ADD(e,w) !strcmp((e),"room")&&!strcmp((w),"add")
#define ROOM_REMOVE(e,w) !strcmp((e),"room")&&!strcmp((w),"remove")
#define ESCAPER_ADD(e,w) !strcmp((e),"escaper")&&!strcmp((w),"add")
#define ESCAPER_REMOVE(e,w) !strcmp((e),"escaper")&&!strcmp((w),"remove")
#define ESCAPER_ORDER(e,w) !strcmp((e),"escaper")&&!strcmp((w),"order")
#define ESCAPER_RECOMMEND(e,w) !strcmp((e),"escaper")&&!strcmp((w),"recommend")
#define REPORT_DAY(e,w) !strcmp((e),"report")&&!strcmp((w),"day")
#define REPORT_BEST(e,w) !strcmp((e),"report")&&!strcmp((w),"best")
#define IS_ODD(e) ((e)%2)
#define NO_FILE 1
#define ONE_FILE 3
#define TWO_FILES 5
#define EXIST_FLAG(e,w) !strcmp((e),(w))
#define INPUT_FLAG "-i\0"
#define OUTPUT_FLAG "-o\0"
#define EQUAL 0
#define COMMENT '#'

typedef char Command[MAX_LEN];
typedef char* Flag;

/**
* adding a company to the EscapeTechnion set
* @param
* system to add to company
* FILE to read company parameters
* @return
* MTM_OUT_OF_MEMORY if allocation fails
* MTM_INVALID_PARAMETER if one of the parameters is NOT valid
* MTM_EMAIL_ALREADY_EXISTS if email exists in the system
* MTM_SUCCESS else
*/
static MtmErrorCode companyAdd(EscapeTechnion system,FILE* input){
    assert(system!=NULL);
    assert(input!=NULL);
    char email_buffer[MAX_LEN]="";
    TechnionFaculty faculty_buffer=UNKNOWN;
#ifndef NDEBUG
    int arguments=
#endif
            fscanf(input," %s %u\n",email_buffer,&faculty_buffer);
    assert(arguments==2);
    SystemResult res1=systemCompanyAdd(system,email_buffer,faculty_buffer);
    switch (res1) {
        case SYSTEM_MEMORY_PROBLEM :
            return MTM_OUT_OF_MEMORY;
        case SYSTEM_EMAIL_ALREADY_EXIST :
            return MTM_EMAIL_ALREADY_EXISTS;
        case SYSTEM_ILLEGAL_PARAMETER:
            return MTM_INVALID_PARAMETER;
        default:
            break;
    }
    return MTM_SUCCESS;
}

/**
* removing a company from the EscapeTechnion set
* @param
* system to remove a company from
* FILE to read company parameters
* @return
* MTM_OUT_OF_MEMORY if allocation fails
* MTM_INVALID_PARAMETER if one of the parameters is NOT valid
* MTM_COMPANY_EMAIL_DOES_NOT_EXIST if email does NOT exists in the system
* MTM_RESERVATION_EXISTS if there is exists order to company's rooms
* MTM_SUCCESS else
*/
static MtmErrorCode companyRemove(EscapeTechnion system,FILE* input){
    assert(system!=NULL);
    assert(input!=NULL);
    char email_buffer[MAX_LEN]="";
#ifndef NDEBUG
    int arguments=
#endif
    fscanf(input," %s\n",email_buffer);
    assert(arguments==1);
    SystemResult res1=systemCompanyRemove(system,email_buffer);
    switch (res1) {
        case SYSTEM_MEMORY_PROBLEM :
            return MTM_OUT_OF_MEMORY;
        case SYSTEM_COMPANY_EMAIL_NOT_EXIST :
            return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
        case SYSTEM_ILLEGAL_PARAMETER:
            return MTM_INVALID_PARAMETER;
        case SYSTEM_RESERVATION_EXIST :
            return MTM_RESERVATION_EXISTS;
        default:
            break;
    }
    return MTM_SUCCESS;
}

/**
* adding a room to the EscapeTechnion
* @param
* system to add to room
* FILE to read room parameters
* @return
* MTM_OUT_OF_MEMORY if allocation fails
* MTM_INVALID_PARAMETER if one of the parameters is NOT valid
* MTM_ID_ALREADY_EXIST if room id exists in the requested faculty
* MTM_SUCCESS else
*/
static MtmErrorCode roomAdd(EscapeTechnion system,FILE* input){
    assert(system!=NULL);
    assert(input!=NULL);
    char email_buffer[MAX_LEN]="";
    Id id_buffer;
    Price price_buffer;
    Num_People people_buffer;
    Hour open_buffer="";
    Hour close_buffer="";
    Level level_buffer;
#ifndef NDEBUG
    int arguments=
#endif
    fscanf(input," %s %d %d %d %2s-%2s %d\n",email_buffer,&id_buffer,
         &price_buffer,&people_buffer,open_buffer,close_buffer,&level_buffer);
    assert(arguments==7);
    SystemResult res1=systemRoomAdd(system,email_buffer,id_buffer,
                                    price_buffer,people_buffer,open_buffer,
                                    close_buffer,level_buffer);
    switch (res1) {
        case SYSTEM_MEMORY_PROBLEM :
            return MTM_OUT_OF_MEMORY;
        case SYSTEM_ILLEGAL_PARAMETER:
            return MTM_INVALID_PARAMETER;
        case SYSTEM_COMPANY_EMAIL_NOT_EXIST :
            return MTM_COMPANY_EMAIL_DOES_NOT_EXIST;
        case SYSTEM_ROOM_ID_ALREADY_EXIST :
            return MTM_ID_ALREADY_EXIST;
        default:
            break;
    }
    return MTM_SUCCESS;
}

/**
* removing a room from the EscapeTechnion
* @param
* system to remove a room from
* FILE to read room parameters
* @return
* MTM_OUT_OF_MEMORY if allocation fails
* MTM_INVALID_PARAMETER if one of the parameters is NOT valid
* MTM_ID_DOES_NOT_EXIST if room id does NOT exists in the system
* MTM_RESERVATION_EXISTS if there is exists order to room
* MTM_SUCCESS else
*/
static MtmErrorCode roomRemove(EscapeTechnion system,FILE* input){
    assert(system!=NULL);
    assert(input!=NULL);
    Id id_buffer;
    TechnionFaculty faculty_buffer=UNKNOWN;
#ifndef NDEBUG
    int arguments=
#endif
    fscanf(input," %u %d\n",&faculty_buffer,&id_buffer);
    assert(arguments==2);
    SystemResult res1=systemRoomRemove(system,faculty_buffer,id_buffer);
    switch (res1) {
        case SYSTEM_MEMORY_PROBLEM :
            return MTM_OUT_OF_MEMORY;
        case SYSTEM_ILLEGAL_PARAMETER:
            return MTM_INVALID_PARAMETER;
        case SYSTEM_ROOM_ID_NOT_EXIST :
            return MTM_ID_DOES_NOT_EXIST;
        case SYSTEM_RESERVATION_EXIST :
            return MTM_RESERVATION_EXISTS;
        default:
            break;
    }
    return MTM_SUCCESS;
}

/**
* adding an escaper to the EscapeTechnion set
* @param
* system to add to escaper
* FILE to read escaper parameters
* @return
* MTM_OUT_OF_MEMORY if allocation fails
* MTM_INVALID_PARAMETER if one of the parameters is NOT valid
* MTM_EMAIL_ALREADY_EXISTS if email already exists in the system
* MTM_SUCCESS else
*/
static MtmErrorCode escaperAdd(EscapeTechnion system,FILE* input) {
    assert(system != NULL);
    assert(input != NULL);
    char email_buffer[MAX_LEN] = "";
    Level level_buffer ;
    TechnionFaculty faculty_buffer = UNKNOWN;
#ifndef NDEBUG
    int arguments =
#endif
            fscanf(input, " %s %u %d\n", email_buffer, &faculty_buffer,
                   &level_buffer);
    assert(arguments == 3);
    SystemResult res1 = systemEscaperAdd
            (system, email_buffer, faculty_buffer, level_buffer);
    switch (res1) {
        case SYSTEM_MEMORY_PROBLEM :
            return MTM_OUT_OF_MEMORY;
        case SYSTEM_ILLEGAL_PARAMETER:
            return MTM_INVALID_PARAMETER;
        case SYSTEM_EMAIL_ALREADY_EXIST:
            return MTM_EMAIL_ALREADY_EXISTS;
        default:
            break;
    }
    return MTM_SUCCESS;
}

/**
* removing an escaper from the EscapeTechnion
* @param
* system to remove an escaper from
* FILE to read room parameters
* @return
* MTM_INVALID_PARAMETER if one of the parameters is NOT valid
* MTM_CLIENT_EMAIL_DOES_NOT_EXIST if email does NOT exists in the system
* MTM_SUCCESS else
*/
static MtmErrorCode escaperRemove(EscapeTechnion system,FILE* input){
    assert(system!=NULL);
    assert(input!=NULL);
    char email_buffer[MAX_LEN]="";
#ifndef NDEBUG
    int arguments=
#endif
    fscanf(input," %s\n",email_buffer);
    assert(arguments==1);
    SystemResult res1=systemEscaperRemove(system,email_buffer);
    switch (res1) {
        case SYSTEM_ILLEGAL_PARAMETER:
            return MTM_INVALID_PARAMETER;
        case  SYSTEM_CLIENT_EMAIL_NOT_EXIST :
            return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
        default:
            break;
    }
    return MTM_SUCCESS;
}


/**
* adding an order for exists escaper
* @param
* system to add order
* FILE to read order parameters
* @return
* MTM_OUT_OF_MEMORY if allocation fails
* MTM_INVALID_PARAMETER if one of the parameters is NOT valid
* MTM_CLIENT_EMAIL_DOES_NOT_EXIST if email does NOT exists in the system
* MTM_ID_DOES_NOT_EXIST if room id does NOT exists in the system
* MTM_CLIENT_IN_ROOM if the escaper has already order to requested time
* MTM_ROOM_NOT_AVAILABLE if room is not available for that time
* MTM_SUCCESS else
*/
static MtmErrorCode escaperOrder(EscapeTechnion system,FILE* input) {
    assert(system != NULL);
    assert(input != NULL);
    char email_buffer[MAX_LEN] = "";
    TechnionFaculty faculty_buffer = UNKNOWN;
    Id id_buffer ;
    Day day_buffer ;
    Time time_buffer ;
    Num_People people_buffer ;
#ifndef NDEBUG
    int arguments =
#endif
            fscanf(input, " %s %u %d %d-%d %d\n", email_buffer, &faculty_buffer,
                   &id_buffer, &day_buffer, &time_buffer, &people_buffer);
    assert(arguments == 6);
    SystemResult res1 = systemEscaperOrder(system, email_buffer, faculty_buffer,
                                           id_buffer, day_buffer, time_buffer,
                                           people_buffer);
    switch (res1) {
        case SYSTEM_MEMORY_PROBLEM :
            return MTM_OUT_OF_MEMORY;
        case SYSTEM_ILLEGAL_PARAMETER:
            return MTM_INVALID_PARAMETER;
        case SYSTEM_CLIENT_EMAIL_NOT_EXIST :
            return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
        case SYSTEM_ROOM_ID_NOT_EXIST :
            return MTM_ID_DOES_NOT_EXIST;
        case SYSTEM_CLIENT_IN_ROOM :
            return MTM_CLIENT_IN_ROOM;
        case SYSTEM_ROOM_NOT_AVAILABLE :
            return MTM_ROOM_NOT_AVAILABLE;
        default:
            break;
    }
    return MTM_SUCCESS;
}

/**
* removing an escaper from the EscapeTechnion
* @param
* system to remove an escaper from
* FILE to read room parameters
* @return
* MTM_OUT_OF_MEMORY if allocation fails
* MTM_INVALID_PARAMETER if one of the parameters is NOT valid
* MTM_CLIENT_EMAIL_DOES_NOT_EXIST if email does NOT exists in the system
* MTM_NO_ROOMS_AVAILABLE if there is no rooms at all in the system
* MTM_SUCCESS else
*/
static MtmErrorCode escaperRecommend(EscapeTechnion system,FILE* input) {
    assert(system != NULL);
    assert(input != NULL);
    char email_buffer[MAX_LEN] = "";
    Num_People people_buffer ;
#ifndef NDEBUG
    int arguments =
#endif
            fscanf(input, " %s %d\n", email_buffer, &people_buffer);
    assert(arguments == 2);
    SystemResult res1=systemEscaperRecommend(system,email_buffer,people_buffer);
    switch (res1) {
        case SYSTEM_MEMORY_PROBLEM :
            return MTM_OUT_OF_MEMORY;
        case SYSTEM_ILLEGAL_PARAMETER:
            return MTM_INVALID_PARAMETER;
        case  SYSTEM_CLIENT_EMAIL_NOT_EXIST :
            return MTM_CLIENT_EMAIL_DOES_NOT_EXIST;
        case SYSTEM_NO_ROOMS_AVAILABLE :
            return MTM_NO_ROOMS_AVAILABLE;
        default:
            break;
    }
    return MTM_SUCCESS;
}
/**
* get an order and extract all the data regards to the client
* @param
* order to extract data from
* pointers to exporting the data to caller
* @return
* Void function
*/
static void getEscaperDetails(Order order,Level *client_skill,
                           TechnionFaculty* client_faculty,Email*client_email){
    assert(order!=NULL&&client_email!=NULL&&client_faculty!=NULL&&client_skill!=NULL);
    Escaper client = NULL;
#ifndef NDEBUG
    OrderResult res1 =
#endif
            orderGetEscaper(order, &client);
    assert(res1 == ORDER_SUCCESS);
   *client_email = escaperGetEmailByRef(client);
    assert(*client_email != NULL);
#ifndef NDEBUG
    EscaperResult res3 =
#endif
            escaperGetFaculty(client, client_faculty);
    assert(res3 == ESCAPER_SUCCESS && *client_faculty != UNKNOWN);
#ifndef NDEBUG
    res3 =
#endif
            escaperGetLevel(client,client_skill);
    assert(res3 == ESCAPER_SUCCESS);
    return;
}

/**
* get an order and extract all the data regards to the ordered room
* @param
* order to extract data from
* pointers to exporting the data to caller
* @return
* Void function
*/
static void getRoomDetails(Order order,Id *room_id,Email*company_email,
                           Level *room_level) {
    assert(order!=NULL&&company_email!=NULL&&room_id!=NULL&&room_level!=NULL);
    Room order_room = NULL;
#ifndef NDEBUG
    OrderResult res1 =
#endif
            orderGetRoom(order, &order_room);
    assert(res1 == ORDER_SUCCESS);
#ifndef NDEBUG
    RoomResult res2 =
#endif
            roomGetId(order_room, room_id);
    assert(res2 == ROOM_SUCCESS);
    *company_email = roomGetEmailByRef(order_room);
    assert(*company_email != NULL);
#ifndef NDEBUG
    res2 =
#endif
            roomGetLevel(order_room, room_level);
    assert(res2 == ROOM_SUCCESS);
    return;
}

/**
* get list of today orders and extract all the requsted data regards the
* order that need to be printed
* @param
* today_orders a list of the today orders
* output file to write to
* @return
* Void function
*/
static void printTodayOrders(List today_orders,FILE* output){
    assert(today_orders!=NULL);
    assert(output!=NULL);
    LIST_FOREACH(Order, iterator, today_orders) {
        Time order_hour;
        Day order_day;
        TechnionFaculty order_faculty;
        Id order_room_id;
        Num_People order_people;
        Price order_price;
        Level order_room_level;
        Email company_email;
        Email client_email;
        Level client_skill;
        TechnionFaculty client_faculty;
        getEscaperDetails(iterator,&client_skill,&client_faculty,&client_email);
        getRoomDetails(iterator,&order_room_id,&company_email,
                       &order_room_level);

#ifndef NDEBUG
        OrderResult res1=
#endif
                orderGetFaculty(iterator, &order_faculty);
        assert(res1 == ORDER_SUCCESS && order_faculty != UNKNOWN);
#ifndef NDEBUG
        res1 =
#endif
                orderGetNumPeople(iterator, &order_people);
        assert(res1 == ORDER_SUCCESS);
#ifndef NDEBUG
        res1 =
#endif
                orderGetTime(iterator, &order_day, &order_hour);
        assert(res1 == ORDER_SUCCESS);
#ifndef NDEBUG
        res1 =
#endif
                orderGetPrice(iterator, &order_price);
        assert(res1 == ORDER_SUCCESS);
        mtmPrintOrder(output, client_email, client_skill, client_faculty,
                      company_email, order_faculty, order_room_id, order_hour,
                      order_room_level, order_people, order_price);
    }
    return;
}


/**
* get a system and print out all today orders, increase the current day and
 * collect today revenue to the total revenue
* @param
* system to get today orders and end of day operations
* output file to print today orders
* @return
* MTM_OUT_OF_MEMORY if allocation og today orders list fails
* MTM_SUCCESS else
*/
static MtmErrorCode reportDay(EscapeTechnion system,FILE* output) {
    assert(system != NULL);
    Day day_buffer;
    SystemResult res1 = systemGetDay(system, &day_buffer);
    assert(res1 == SYSTEM_SUCCESS);
    List today_orders = NULL;
    res1 = systemReportDay(system, &today_orders);
    if (res1 == SYSTEM_MEMORY_PROBLEM) {
        return MTM_OUT_OF_MEMORY;
    }
    mtmPrintDayHeader(output, day_buffer, listGetSize(today_orders));
    printTodayOrders(today_orders,output);
    mtmPrintDayFooter(output,day_buffer);
    listDestroy(today_orders);
    return MTM_SUCCESS;
}
/**
* get a system and print out the 3 best faculties,by their revenue
* @param
* system to get best faculties
* output file to print best faculties
* @return
* MTM_OUT_OF_MEMORY if allocation of best list fails
* MTM_SUCCESS else
*/
static MtmErrorCode reportBest(EscapeTechnion system,FILE* output) {
    assert(system != NULL);
    Day day_buffer ;
    SystemResult res1 = systemGetDay(system, &day_buffer);
    Price revenue_buffer;
    assert(res1 == SYSTEM_SUCCESS);
    res1=systemGetRevenue(system,&revenue_buffer);
    assert(res1==SYSTEM_SUCCESS);
    List best=NULL;
    res1=systemReportBest(system,&best);
    if(res1==SYSTEM_MEMORY_PROBLEM){
        return MTM_OUT_OF_MEMORY;
    }
    mtmPrintFacultiesHeader(output,UNKNOWN,day_buffer,revenue_buffer);
    LIST_FOREACH(Faculty,iterator,best){
        Price current_rev;
        TechnionFaculty current_id;
#ifndef NDEBUG
        FacultyResult res1=
#endif
        facultyGetTotalRevenue(iterator,&current_rev);
        assert(res1==FACULTY_SUCCESS);
#ifndef NDEBUG
        res1=
#endif
                facultyGetID(iterator,&current_id);
        assert(res1==FACULTY_SUCCESS);
        mtmPrintFaculty(output,current_id,current_rev);
    }
    mtmPrintFacultiesFooter(output);
    listDestroy(best);
    return MTM_SUCCESS;
}

/**
* get an error code and check if is is fatal error that the program should be
* exist
* @param
* result MtmErrorCode to check
* @return
* TRUE <=> results=MTM_OUT_OF_MEMORY
*/
static inline bool isFatalError(MtmErrorCode result){
    return result==MTM_OUT_OF_MEMORY;
}
/**
* get an error code and print it using mtm print error funcation
* @param
* result MtmErrorCode to print
* @return
* TRUE <=> results=MTM_OUT_OF_MEMORY
*/
static inline bool printTheErrors(MtmErrorCode result){
    if(result!=MTM_SUCCESS){
        mtmPrintErrorMessage(stderr,result);
        return isFatalError(result);
    }
        return false;
}
/**
* get commend and check if it is comment in the file
* @param
* command to check
* @return
* TRUE <=> the first char is '#'
*/
 static inline bool isComment(Command command){
     return *command==COMMENT;
 }

/**
* get the first and second command ans decide to which function to call
* @param
* system to do the command on it
* first command argument to comapre with
* second command argument to comapre with
* input, output to write and reef from
* @return
* MtmErrorCode as the called function return
*/
static MtmErrorCode executeCommand(EscapeTechnion system,Command first,Command second,
                           FILE*input,FILE*output) {
    if (COMPANY_ADD(first,second)) {
        return companyAdd(system, input);
    }
    if (COMPANY_REMOVE(first, second)) {
        return companyRemove(system, input);
    }
    if (ROOM_ADD(first, second)) {
        return roomAdd(system, input);
    }
    if (ROOM_REMOVE(first, second)) {
        return roomRemove(system, input);
    }
    if (ESCAPER_ADD(first, second)) {
        return escaperAdd(system, input);
    }
    if (ESCAPER_REMOVE(first, second)) {
        return escaperRemove(system, input);
    }
    if (ESCAPER_ORDER(first, second)) {
        return escaperOrder(system, input);
    }
    if (ESCAPER_RECOMMEND(first, second)) {
        return escaperRecommend(system, input);
    }
    if (REPORT_DAY(first, second)) {
        return reportDay(system, output);
    }
    if (REPORT_BEST(first, second)) {
        return reportBest(system, output);
    }
    return MTM_SUCCESS;//should not be here
}

/**
* get system, input and output files and do command on the system as reading
* from file
* @param
* system to do the command on it
* input, output to write and reef from
* @return
* void function
*/
static void readingFile(EscapeTechnion system,FILE *input,FILE*output){
    assert(system!=NULL);
    assert(input!=NULL&&output!=NULL);
    Command first_command="";
    while(fscanf(input,"%s[^\n]",first_command)!=EOF) {
        if (isComment(first_command)) {
            fscanf(input, "%*[^\n]\n");
            continue;
        }
        Command second_command = "";
#ifndef NDEBUG
        int res1 =
#endif
                fscanf(input, "%s ", second_command);
        assert(res1);
        if (printTheErrors(executeCommand(system, first_command, second_command,
                                          input, output))) {
            return;
        }
    }
    return;
}

/**
* closing pointer to file, if is is stdin or stdout do nothing
* @param
* file pointer to close
* @return
* void
*/
static void closeFilePointer(FILE * file){
    if(file==stdin||file==stdout){
        return;
    }
    fclose(file);
    return;
}

/**
* get argc and argv and check if them together can be a valid command line:
* argc is lower than 5 and is it odd I/O flags only in odd index in argv
* and each flag appear in the command at most one time
* @param
* argc to check
* argv to check
* @return
* True <=> the command is valid, else false
*/
static bool validCommandLine(int argc,char** argv){
    if(argc>TWO_FILES||!IS_ODD(argc)){
        return false;
    }
    int counter_input=0, counter_output=0;
    for(int i=1;i<argc;i+=2){
        assert(IS_ODD(i));
        if(!EXIST_FLAG(argv[i],INPUT_FLAG)&&!EXIST_FLAG(argv[i],OUTPUT_FLAG)){
            return false;
        }
        counter_input+=EXIST_FLAG(argv[i],INPUT_FLAG);//count "-i" in command
        counter_output+=EXIST_FLAG(argv[i],OUTPUT_FLAG);//count "-o" in command
    }
    return counter_input<=1&&counter_output<=1;//True <=> at most one of each
}

/**
* get argc and argv and return pointer to requested file I/O by flag
* @param
* argc to read from
* argv to read from
* flag in order to know I/O
* @return
* pointer to the open file
* NULL - when open the file fails
*/
static FILE* getFiles(int argc, char**argv, Flag flag){
    if(argc==NO_FILE){
        return (strcmp(flag,INPUT_FLAG)==EQUAL) ? stdin : stdout;
    }
    if(argc==ONE_FILE&&EXIST_FLAG(argv[1],flag)){
        FILE*file = fopen(argv[2],(strcmp(flag,INPUT_FLAG)==EQUAL) ? "r" : "w");
        if (!file) {
            return NULL;
        }
        return file;
    }
    if(argc==TWO_FILES) {
        FILE *input;
        if (EXIST_FLAG(argv[1],flag)) {
            input = fopen(argv[2],(strcmp(flag,INPUT_FLAG)==EQUAL) ? "r" : "w");
        }else {
            input = fopen(argv[4],(strcmp(flag,INPUT_FLAG)==EQUAL) ? "r" : "w");
        }
        if (!input) {
            return NULL;
        }
        return input;
    }
    return (!strcmp(flag,INPUT_FLAG)) ? stdin : stdout;
}

/**
* first manage the files to red from and to write to
* second allocating the system
* third calling the reading function
* get back when reading is finish and closing all files and free all resources
*
* @param
* argc to read from
* argv to read from
* @return
* always return 0
*/
int main(int argc,char** argv) {
    if(!validCommandLine(argc,argv)){
        printTheErrors(MTM_INVALID_COMMAND_LINE_PARAMETERS);
        return 0;
    }
    FILE *input=getFiles(argc,argv,INPUT_FLAG);
    if(!input){
        printTheErrors(MTM_CANNOT_OPEN_FILE);
        return 0;
    }
    FILE *output=getFiles(argc,argv,OUTPUT_FLAG);
    if(!output){
        closeFilePointer(input);
        printTheErrors(MTM_CANNOT_OPEN_FILE);
        return 0;
    }
    EscapeTechnion system = systemCreate();
    if (!system) {
        printTheErrors(MTM_OUT_OF_MEMORY);
        return 0;
    }
    readingFile(system, input, output);
    closeFilePointer(input);
    closeFilePointer(output);
    systemDestroy(system);
    return 0;
}