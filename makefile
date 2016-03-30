CXX = g++
CXXFLAGS = -I ./ -g

prog: main.o node.o element.o mesh.o problem.o
	$(CXX) $(CXXFLAGS) -o prog main.o node.o element.o mesh.o problem.o

main.o: src/main.cpp src/problem.h src/mesh.h src/element.h src/node.h
	$(CXX) $(CXXFLAGS) -c src/main.cpp

node.o: src/node.cpp src/node.h
	$(CXX) $(CXXFLAGS) -c src/node.cpp

element.o: src/element.cpp src/element.h src/node.h	
	$(CXX) $(CXXFLAGS) -c src/element.cpp

mesh.o: src/mesh.cpp src/mesh.h src/element.h src/node.h
	$(CXX) $(CXXFLAGS) -c src/mesh.cpp

problem.o: src/problem.cpp src/problem.h src/mesh.h src/element.h src/node.h
	$(CXX) $(CXXFLAGS) -c src/problem.cpp

#CPP_FILES := $(wildcard src/*.cpp)
#OBJ_FILES := $(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
##LD_FLAGS := ...
#CC_FLAGS := -I ./

#main: $(OBJ_FILES)
	#g++ -o $@ $^

#obj/%.o: src/%.cpp 
	#g++ $(CC_FLAGS) -c -o $@ $<

#g++ -I ./ -c -o obj/mesh.o src/mesh.cpp
#g++ -I ./ -c -o obj/element.o src/element.cpp
#g++ -I ./ -c -o obj/problem.o src/problem.cpp
#g++ -I ./ -c -o obj/node.o src/node.cpp
#g++ -I ./ -c -o obj/main.o src/main.cpp
#g++ -o main obj/mesh.o obj/element.o obj/problem.o obj/node.o obj/main.o

