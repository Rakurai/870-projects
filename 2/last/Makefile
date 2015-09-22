SRCDIR := src
OBJDIR := .obj

EXEC := run
SRCS := $(shell find $(SRCDIR) -name "*.cpp")
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS := $(OBJS:.o=.d)

CPPFLAGS += -I $(SRCDIR)
CPPFLAGS += `sdl-config --cflags`
CPPFLAGS += -MMD -MP

CXXFLAGS += -g -W -Wall -Weffc++ -Wextra -pedantic -O0

LDLIBS += `sdl-config --libs` -lSDL_ttf -lSDL_image -lexpat -lSDL_gfx

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)/
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

%/:
	mkdir $@

-include $(DEPS)

clean:
	rm -rf $(OBJDIR)/*
	rm -rf $(EXEC)
	rm -rf frames/*.bmp
