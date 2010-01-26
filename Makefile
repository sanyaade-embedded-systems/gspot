CXX		?= g++
OBJ		= main.o spotify.o
OUT		= gspot
PREFIX 	?= /usr/local

CXXFLAGS	+=	`pkg-config --cflags libspotify` 
LIBS		= 	`pkg-config --libs libspotify`

all: $(OUT)

.cpp.o:
		@echo [CXX] $<
		@$(CXX) $(CXXFLAGS) -c -o $@ $<

$(OUT): $(OBJ)
		@echo [LD] $@
		@$(CXX) $(OBJ) $(LIBS) -o $(OUT)

clean:
		rm -rf $(OBJ) $(OUT)

