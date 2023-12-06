# THE NAME OF YOUR EXECUTABLE
TARGET = Skedule
# ALL CPP COMPILABLE IMPLEMENTATION FILES THAT MAKE UP THE PROJECT
SRC_FILES = main.cpp Calendar.cpp Date.cpp Month.cpp Year.cpp CalendarItem.cpp Event.cpp MenuCreateEvent.cpp MenuBlank.cpp DrawUtil.cpp Menu.cpp

# NO EDITS NEEDED BELOW THIS LINE

CXX = g++
CXXFLAGS = 
CXXFLAGS_DEBUG = -g
CXXFLAGS_ERRORS = -Werror -Wall -Wextra -Wpedantic -pedantic-errors -Wshadow -Wunreachable-code -Wdouble-promotion
CXXVERSION = -std=c++17

OBJECTS = $(SRC_FILES:.cpp=.o)

ifeq ($(OS),Windows_NT)
	TARGET := $(TARGET).exe
	DEL = del
	Q =

	INC_PATH = Z:/CSCI200/include/
	LIB_PATH = Z:/CSCI200/lib/

	ARCH =
	RPATH =
else
	DEL = rm -f
	Q = "

	INC_PATH = /usr/local/include/
	LIB_PATH = /usr/local/lib/

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		CXXFLAGS += -D LINUX
		RPATH =
	endif
	ifeq ($(UNAME_S),Darwin)
		TARGET_MAKEFILE = Makefile.osx
		CXXFLAGS += -D OSX
		RPATH = -Wl,-rpath,/Library/Frameworks
	endif

	UNAME_P := $(shell uname -p)
	ifeq ($(UNAME_P),x86_64)
		ARCH =
	endif
	ifneq ($(filter %86,$(UNAME_P)),)
		ARCH =
	endif
	ifneq ($(filter arm%,$(UNAME_P)),)
		ARCH =
	endif
endif

LIBS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(ARCH) -o $@ $^ $(RPATH) -L$(LIB_PATH) $(LIBS)

.cpp.o:
	$(CXX) $(CXXVERSION) $(CXXFLAGS) $(CXXFLAGS_DEBUG) $(CXXFLAGS_ERRORS) $(ARCH) -o $@ -c $< -I$(INC_PATH)

clean:
	$(DEL) $(TARGET) $(OBJECTS)
	
depend:
	@sed -i.bak '/^# DEPENDENCIES/,$$d' Makefile
	@$(DEL) sed*
	@echo $(Q)# DEPENDENCIES$(Q) >> Makefile
	@$(CXX) -MM $(SRC_FILES) >> Makefile

.PHONY: all clean depend

# DEPENDENCIES
main.o: main.cpp Calendar.h CalendarItem.h Date.h Month.h Year.h Menu.h \
 Widget.h State.h Event.h
Calendar.o: Calendar.cpp Calendar.h CalendarItem.h Date.h Month.h Year.h \
 Menu.h Widget.h State.h MenuBlank.h MenuCreateEvent.h DrawUtil.h
Date.o: Date.cpp Date.h Month.h Year.h
Month.o: Month.cpp Month.h Year.h
Year.o: Year.cpp Year.h
CalendarItem.o: CalendarItem.cpp CalendarItem.h Date.h Month.h Year.h
Event.o: Event.cpp Event.h CalendarItem.h Date.h Month.h Year.h
MenuCreateEvent.o: MenuCreateEvent.cpp DrawUtil.h Event.h CalendarItem.h \
 Date.h Month.h Year.h MenuCreateEvent.h Menu.h Calendar.h Widget.h \
 State.h
MenuBlank.o: MenuBlank.cpp DrawUtil.h MenuBlank.h Menu.h Calendar.h \
 CalendarItem.h Date.h Month.h Year.h Widget.h State.h
DrawUtil.o: DrawUtil.cpp DrawUtil.h
Menu.o: Menu.cpp Menu.h Calendar.h CalendarItem.h Date.h Month.h Year.h \
 Widget.h State.h
