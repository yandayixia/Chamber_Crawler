CXX = g++
CXXFLAGS = -g -Wall -MMD
EXEC = cc3k

ENEM = Enemy.o Human.o Elf.o Dwarf.o Orc.o Halfling.o Merchant.o Dragon.o
ITEM = Item.o Potion.o Gold.o
HERO = Character.o Hero.o Shade.o Drow.o Vampire.o Troll.o Goblin.o
OBJECTS = ${ENEM} ${ITEM} ${HERO} test/Main.o helper.o Floor.o Chamber.o Entity.o Tile.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

rmex:
	rm ${EXEC}

clean:
	rm *.o *.d test/*d test/*o ${EXEC}

.PHONY: clean

.PHONY: rmex
