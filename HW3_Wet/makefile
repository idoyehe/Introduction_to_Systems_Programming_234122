CC = gcc
OBJS = parser.o EscapeTechnion.o faculty.o order.o escape_room.o escaper.o company.o
EXEC = mtm_escape
DEBUG_FLAG = # now empty, assign -g for debug
COMP_FLAG = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
LIB = -L. -lmtm

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ $(LIB)
	
parser.o: parser.c EscapeTechnion.h mtm_ex3.h list.h constants.h faculty.h set.h escape_room.h company.h order.h escaper.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c
	
EscapeTechnion.o: EscapeTechnion.c EscapeTechnion.h mtm_ex3.h list.h constants.h faculty.h set.h escape_room.h company.h order.h escaper.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

faculty.o: faculty.c faculty.h list.h set.h escape_room.h company.h mtm_ex3.h constants.h order.h escaper.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

order.o: order.c order.h list.h escape_room.h set.h company.h mtm_ex3.h constants.h escaper.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

escape_room.o: escape_room.c escape_room.h set.h company.h mtm_ex3.h constants.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

escaper.o: escaper.c escaper.h set.h mtm_ex3.h constants.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

company.o: company.c company.h mtm_ex3.h set.h constants.h
	$(CC) -c $(DEBUG_FLAG) $(COMP_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)