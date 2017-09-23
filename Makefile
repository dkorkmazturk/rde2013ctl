# TARGET: Name of the output file
TARGET	= rde2013ctl

# Source and Build directories
OUTDIR	= build
SRCDIR	= src
INSDIR	= /usr/bin

# Binaries
CC 	= g++
RM      = rm -rf
MKDIR	= mkdir -p

# Compiler and Linker flags
LIBS	= -lusb-1.0
CFLAGS	= -march=x86-64 -mtune=generic -O2 -pipe -fstack-protector-strong -fno-plt

# Build
all: $(OUTDIR)/$(TARGET)

$(OUTDIR)/$(TARGET): $(OUTDIR)/main.o $(OUTDIR)/rde2013.o
	$(CC) $(LIBS) $^ -o $@

$(OUTDIR)/main.o: $(SRCDIR)/main.cpp | $(OUTDIR)
	$(CC) -c $(CFLAGS) $^ -o $@

$(OUTDIR)/rde2013.o: $(SRCDIR)/rde2013.cpp $(SRCDIR)/rde2013.h | $(OUTDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OUTDIR):
	$(MKDIR) $@

clean:
	$(RM) $(OUTDIR)

install:
	install -m 755 $(OUTDIR)/$(TARGET) $(INSDIR)/$(TARGET)

uninstall:
	$(RM) $(INSDIR)/$(TARGET)

.PHONY: all clean install uninstall
