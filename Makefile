CC=g++
CFLAGS=-c -O2 -Wall -Wno-parentheses -fno-stack-protector
LDFLAGS=
CFLAGSDEBUG=-c -O -Wall `mysql_config --cflags` -D_DEBUG_

BinName=raytracer
CppFiles=CCamera.cpp  CLight.cpp  CMeshSceneObject.cpp  CObjMesh.cpp  CPPMImageWriter.cpp  CScene.cpp  CSceneLoader.cpp  CSphereSceneObject.cpp  Log.cpp  raytracer.cpp tinyxml2/tinyxml2.cpp
OFiles=$(CppFiles:.cpp=.o)

all: $(CppFiles) $(BinName)

$(BinDir)$(BinName): $(OFiles)
	$(CC) $(OFiles) $(LDFLAGS) -o $@

.cpp.o:
	$(CC) $< $(CFLAGS) -o $@

clean:
	find . -type f -iname "*.o" -exec rm -f {} \;
