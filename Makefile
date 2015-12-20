CC=g++
CFLAGS=-c -O2 -Wall
LDFLAGS=
CFLAGSDEBUG=-c -O -Wall `mysql_config --cflags` -D_DEBUG_

BinName=raymond
CppFiles=raytracer.cpp Sphere.cpp PPMWriter.cpp
OFiles=$(CppFiles:.cpp=.o)

all: $(CppFiles) $(BinName)

$(BinDir)$(BinName): $(OFiles)
	$(CC) $(OFiles) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $< $(CFLAGS) -o $@

clean:
	find . -type f -iname "*.o" -exec rm -f {} \;
