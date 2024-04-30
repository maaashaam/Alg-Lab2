CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra
SRCDIR = src
OBJDIR = obj
BINDIR = bin

SRCS = $(wildcard $(SRCDIR)/*.cpp)

OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

TARGET = $(BINDIR)/main

all: $(TARGET) run

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: clean

$(shell mkdir -p $(OBJDIR) $(BINDIR))