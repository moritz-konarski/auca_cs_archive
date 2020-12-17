CFLAGS  += -Ofast -std=gnu99 #-Wno-unused-result -g
#LDFLAGS += -static

TARGET  = xargs
OBJECTS = 	xargs.o				\
			string_utils.o		\
			command_line_utils.o\
			syscalls.o

.PHONY : all
all : $(TARGET)

$(TARGET) : $(OBJECTS)

$(OBJECTS) : %.o : %.c 

.PHONY : clean
clean :
	rm -rf $(TARGET) $(OBJECTS)
