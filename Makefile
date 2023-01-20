CC     := gcc
CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

CXXFLAGS  := -Wall -pipe -g --pedantic
CXXFLAGS  += -I. -Igosu `gosu/bin/gosu-config --cxxflags` -Iinclude

LDFLAGS   := -Wall
LDFLAGS   += `gosu/bin/gosu-config --libs --cxxflags` 

LIBS      := gosu/lib/libgosu.a

OUTPUT += freegemas

OBJDIR := obj
SRCDIR := src

SRCS := $(notdir $(shell ls -t $(SRCDIR)/*.cpp))

OBJS := $(addprefix $(OBJDIR)/, $(addsuffix .o,$(basename $(SRCS))))

all: $(OUTPUT)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@echo "Compiling..." $(notdir $<)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OUTPUT): $(OBJS)
	@echo "Linking binary..."
	@$(CXX) $(LDFLAGS) -o $@ $^ $(LIBS) 
	@echo "Done."

libgosu:
	cd gosu/linux ; make clean ; ./configure && make

regosu:
	make -C gosu/linux

clean:
	rm $(OBJS) $(OUTPUT) *~ -rf

obj/log.o: include/log.h
obj/game.o: include/game.h include/log.h include/state.h include/stateGame.h include/stateMainMenu.h include/resManager.h include/stateHowtoplay.h include/inter.h
obj/state.o: include/state.h include/log.h include/stateGame.h include/stateMainMenu.h include/stateHowtoplay.h include/inter.h
obj/stateGame.o: include/stateGame.h include/state.h include/game.h include/log.h include/board.h include/floatingScore.h include/scoreTable.h include/baseButton.h include/resManager.h include/sdlfont.h include/particulas.h include/inter.h
obj/stateMainMenu.o: include/stateMainMenu.h include/state.h include/game.h include/log.h include/resManager.h include/jewelGroupAnim.h include/sdlfont.h include/inter.h
obj/board.o: include/board.h include/log.h include/inter.h
obj/scoreTable.o: include/scoreTable.h include/game.h include/inter.h
obj/stateHowtoplay.o: include/stateHowtoplay.h include/state.h include/game.h include/resManager.h include/sdlfont.h	include/inter.h
obj/baseButton.o: include/baseButton.h include/resManager.h include/inter.h
obj/animation.o: include/animation.h	