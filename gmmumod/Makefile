TARGET := gmmumod

MKDIR := ../../make
BINARIESDIR := ../../binaries
INCLUDESDIR := ../../includes
OBJECTSDIR := ../../objects

include $(MKDIR)/Makefile.common

HDRFILES := $(INCLUDESDIR)/defines.h $(INCLUDESDIR)/types.h
HDRFILES += $(INCDIR)/main.h

SRCFILES := main.S main.c
SRCFILES += gmmu.c

include $(MKDIR)/Makefile_arm_fb.common

OBJECTS := $(OBJECTSDIR)/fxplib.o

.PHONY : all
.PHONY : build
.PHONY : exports
.PHONY : includes
.PHONY : clean

all:
	@$(MAKE) clean
	@$(MAKE) exports
	@$(MAKE) includes
	@$(MAKE) build

build:
	@mkdir -p $(OBJDIR)
	@$(MAKE) -s $(TARGET)

exports: 
	@grep -r ^'EXPORT ' $(SRCDIR) > tmp
	@sed -i 's/(/ /;s/)/ /;s/*/ /' tmp
	@awk '{printf "GEN_EXPORT_FUNCTION %s\n", $$3;}' tmp > $(TARGET).exports
	@sort -u $(TARGET).exports -o $(TARGET).exports
	@rm -f tmp

includes:
	@echo "including $(TARGET)"
	@mkdir -p $(INCLUDESDIR)/$(TARGET)
	@cp -R $(INCDIR)/* $(INCLUDESDIR)/$(TARGET)/

clean:
	@echo "cleaning $(TARGET)"
	@rm -rf $(INCLUDESDIR)/$(TARGET)
	@rm -f $(OBJECTSDIR)/$(TARGET).o
	@rm -f $(BINARIESDIR)/$(TARGET).*
	@rm -rf $(OBJDIR)
	@rm -f *.exports
	@rm -f *.imports
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
