Compiling:
I provided a Makefile (using g++), so switching into the source 
directory and running "make" should successfully build the project.
A Visual Studio project is also included, should you feel like 
Windows-ing today. 

Running:
-The executable ("raytracer") requires a path to a scene .xml file 
passed as its first argument.
i.e. running "./raytracer scenes/example2.xml" will render the 
second example file provided.
-It outputs the rendered image as a PPM file (simply the output name 
specified in the scene with ".ppm" appended), put in the current 
working directory, which is most likely the same as the executable 
lies in.
-Further resources referenced in the .xml (e.g. .obj files) are 
searched for relative to the directory, that contains the .xml. 

Notes:
-Textured materials are not yet implemented, so I have included 
a modified version of example 4, found in scenes/example4_mod.xml, 
which is the exact same scene, except with a non-textured material 
for the room mesh.
-Transformations are not implemented either, so example5.xml won't 
really work at all.


Libraries/3rd-Party Code:
TinyXML-2, for reading scene files (obviously). It's released 
under ZLib license, for details, see tinyxml2/tinyxml.h 

External Resources Used:
Mainly slides from the classes/tutorials, the links provided in
the assignment's description, and the odd look at Wikipedia.