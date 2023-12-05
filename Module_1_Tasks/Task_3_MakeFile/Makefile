CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Directories
SRCDIR = .
BUILDDIR = build
INSTALLDIR = $(BUILDDIR)/usr/bin

# Source file
SRCS = $(SRCDIR)/main.cpp

# Object files
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

# Executable
EXEC = $(BUILDDIR)/my_program

.PHONY: all clean install

all: $(EXEC)

$(EXEC): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf $(BUILDDIR)

install: $(EXEC)
	@mkdir -p $(INSTALLDIR)
	cp $(EXEC) $(INSTALLDIR)