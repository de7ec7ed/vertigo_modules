TARGET := socmod

MKDIR := ../../make
BINARIESDIR := ../../binaries
INCLUDESDIR := ../../includes
OBJECTSDIR := ../../objects

include $(MKDIR)/Makefile.common

HDRFILES := $(INCLUDESDIR)/defines.h $(INCLUDESDIR)/types.h
HDRFILES += $(INCDIR)/main.h

SRCFILES := main.S main.c
SRCFILES += uart.c
SRCFILES += wdt.c
SRCFILES += ser.c
SRCFILES += soc.c

include $(MKDIR)/Makefile_arm_fb.common

OBJECTS := $(OBJECTSDIR)/fxplib.o

.PHONY : all
.PHONY : build
.PHONY : includes
.PHONY : clean

all:
	@$(MAKE) -s clean
	@$(MAKE) -s includes
	@$(MAKE) -s build

build:
	@mkdir -p $(OBJDIR)
	@$(MAKE) -s $(TARGET)

includes:
	@echo "including $(TARGET)"
	@mkdir -p $(INCLUDESDIR)/$(TARGET)
	@cp -R $(INCDIR)/* $(INCLUDESDIR)/$(TARGET)/

clean:
	@echo "cleaning $(TARGET)"
	@rm -rf $(INCLUDESDIR)/$(TARGET)
	@rm -f $(BINARIESDIR)/$(TARGET).*
	@rm -rf $(OBJDIR)
	@rm -rf *~
	@rm -rf $(INCDIR)/*~
	@rm -rf $(SRCDIR)/*~

$(OBJDIR)/%.S.o: $(SRCDIR)/%.S $(DEPS)
	@echo "assembling $<"
	@$(CC) $(CFLAGS) -c -D__ASSEMBLY__ -o $@ $<

$(OBJDIR)/%.c.o: $(SRCDIR)/%.c $(DEPS)
	@echo "compiling $<"
	@$(CC) $(CFLAGS) -c -D__C__ -o $@ $<

$(TARGET): $(OBJS)
	@echo "building $(TARGET)"
	@$(LD) $(LFLAGS) -o $(BINARIESDIR)/$(TARGET).elf $(OBJS) $(OBJECTS)
	@$(OBJCOPY) $(OBJCOPYFLAGS) $(BINARIESDIR)/$(TARGET).elf $(BINARIESDIR)/$(TARGET).bin
