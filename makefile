ifndef
	config=debug
endif

############################
#### MAKE VARS
############################
APP 	:= demo
CC 		:= g++
CCFLAGS := -Wall -pedantic -std=c++20
C		:= gcc
CFLAGS 	:=
LIBS 	:= -lglfw -lvulkan -ldl -lpthread -lX11 -lXxf86vm -lXrandr -lXi
INCDIRS := -Isrc
DEFINES :=

.PHONY: info

############################
#### DIRECTORI DATA
############################
MKDIR 	:= mkdir -p
SRC 	:= src
OBJ 	:= obj

############################
#### BUILD CONFIG
############################
ifeq ($(config),debug)
	DEFINES += -DDEBUG
	CCFLAGS += -g
else ifeq ($(config),release)
	DEFINES += -DRELEASE
	CCFLAGS += -O3
else ifeq ($(config),memcheck)
	DEFINES += -DDEBUG
	CCFLAGS += -g -fsanitize=address
	LIBS	+= -fsanitize=address
else
	$(error "Invalid config type $(config). Set config to debug or realease")
endif

############################
#### GENERATED MACROS
############################
define C20
$(patsubst %.c,%.o,$(patsubst %.cpp,%.o,$(patsubst $(SRC)%,$(OBJ)%,$(1))))
endef

define C2H
$(patsubst %.c,%.h,$(patsubst %.cpp,%.hpp,$(1)))
endef

############################
#### $(1) : File to compile
#### $(2) : Obj file
#### $(3) : Depedencies
#### $(4) : Compiler
#### $(5) : Compiler Flags
############################
define COMPILE
$(2) : $(1) $(3)
	$(4) -c -o $(2) $(1) $(5)
endef

############################
#### FILES & DIRECTORIES
############################
ALLCPPS := $(shell find $(SRC) -type f -iname *.cpp)
ALLCS 	:= $(shell find $(SRC) -type f -iname *.c)
ALLOBJS := $(call C20,$(ALLCPPS) $(ALLCS))
SRCDIRS := $(shell find $(SRC) -type d)
OBJDIRS := $(patsubst $(SRC)%,$(OBJ)%,$(SRCDIRS))

############################
#### MAKEFILE RULES
############################
$(APP) : $(OBJDIRS) $(ALLOBJS)
	$(CC) -o $(APP) $(ALLOBJS) $(CCFLAGS) $(LIBS)

$(foreach F,$(ALLCPPS),$(eval $(call COMPILE,$(F),$(call C20,$(F)),$(call C2H,$(F)),$(CC),$(CCFLAGS) $(INCDIRS) $(DEFINES))))

$(foreach F,$(ALLCS),$(eval $(call COMPILE,$(F),$(call C20,$(F)),$(call C2H,$(F)),$(C),$(CFLAGS) $(INCDIRS) $(DEFINES))))

$(OBJDIRS) :
	$(shell $(MKDIR) $(OBJDIRS))

info :
	$(info $(SRCDIRS))
	$(info $(OBJDIRS))
	$(info $(ALLCS))
	$(info $(ALLCPPS))
	$(info $(ALLOBJS))

clean :
	rm -rf $(OBJDIRS)
	rm $(APP)