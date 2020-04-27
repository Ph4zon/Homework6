#  Name    		        Makefile
#  Date                 04/26/2020
#  Author               Nicholas Rhein
#  Email                ncr170130@utdallas.edu
#  Course               CS3377.502
#  Version              1.0
#  Copyright    		2020, All Rights Reserved
#
#  Description
#  Makefile to create the needed files for homework 6

# Set up needed values to support make's implicit commands
# for compiling C++ source files.

# The compiler to use
CXX = g++

# C pre-processor flags
CPPFLAGS = -I /scratch/perkins/include 

# compiler flags
CXXFLAGS = -Werror -g -std=c++11 -Wno-write-strings 

# linker flags
LDFLAGS = -L /scratch/perkins/lib -lcdk -lcurses


# Project name.  This is used in building the file name for the backup target
PROJECTNAME = HW6


# Enter the names of the C++ source files that you want to compile
# with this project

SRCS = HW6Cdk.cc fileInput.cc

# Enter the name for the executable to be created
EXEC = HW6Exec


#
# You normally don't need to change anything below here.
# ======================================================
#
OBJS = $(SRCS:cc=o)

.PHONY: all clean

all: $(EXEC)
clean:
	rm -f $(OBJS) *.d *~ $(EXEC)


# Pattern for .d files.
%.d:%.cc
	@echo Updating .d Dependency File
	@set -e; rm -f $@; \
	$(CXX) -MM $(CPPFLAGS) $< > $@.$$$$; \
	sed 's,\($*\)\.o[ :]*,\1.o $@ : ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$


#  This is a rule to link the files.  Pretty standard
$(EXEC): $(OBJS)
	$(CXX) -o $(EXEC) $(OBJS) $(LDFLAGS) 

Makefile: $(SRCS:.cc=.d)


# Backup Target
backup:	clean
	@mkdir -p ~/backups; chmod 700 ~/backups
	@$(eval CURDIRNAME := $(shell basename `pwd`))@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@$(eval MKBKUPNAME := ~/backups/$(PROJECTNAME)-$(shell date +'%Y.%m.%d-%H:%M:%S').tar.gz)
	@echo
	@echo Writing Backup file to: $(MKBKUPNAME)
	@echo
	@-tar zcfv $(MKBKUPNAME) ../$(CURDIRNAME)
	@chmod 600 $(MKBKUPNAME)
	@echo
	@echo Done!


# Include the dependency files created by the PreProcessor.  The
# dash in front of the command keeps the system from complaining
# if the files do not exist.

-include $(SRCS:.cc=.d)


