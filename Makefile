CXX		?= g++
OBJ		= main.o spotify.o mainwin.o
OUT		= gspot
PREFIX 	?= /usr/local

CXXFLAGS	+=	`pkg-config --cflags libspotify gtkmm-2.4` 
LIBS		= 	`pkg-config --libs libspotify gtkmm-2.4`

all: $(OUT)

.cpp.o:
		@echo [CXX] $<
		@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
		@echo [LD] $@
		@$(CXX) $(OBJ) $(LIBS) -o $(OUT)

clean:
		rm -rf $(OBJ) $(OUT)

