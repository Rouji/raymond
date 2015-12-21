CC=g++
CFLAGS=-c -O2 -Wall -Wno-parentheses
LDFLAGS=
CFLAGSDEBUG=-c -O -Wall `mysql_config --cflags` -D_DEBUG_

BinName=raymond
CppFiles=CPPMImageWriter.cpp CLight.cpp raytracer.cpp CCamera.cpp CSceneLoader.cpp tinyxml2/tinyxml2.cpp CScene.cpp CSphere.cpp
OFiles=$(CppFiles:.cpp=.o)

all: $(CppFiles) $(BinName)

$(BinDir)$(BinName): $(OFiles)
	$(CC) $(OFiles) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $< $(CFLAGS) -o $@

clean:
	find . -type f -iname "*.o" -exec rm -f {} \;
