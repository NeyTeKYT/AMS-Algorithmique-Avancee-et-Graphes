main: ./cpp/main.cpp point.o arc.o E.o noeud.o V.o graphe.o
	g++ -o main ./cpp/main.cpp point.o arc.o E.o noeud.o V.o graphe.o

point.o: ./cpp/point.cpp ./h/point.h
	g++ -c ./cpp/point.cpp

arc.o: ./cpp/arc.cpp ./h/arc.h ./h/point.h
	g++ -c ./cpp/arc.cpp

E.o: ./cpp/E.cpp ./h/E.h arc.o
	g++ -c ./cpp/E.cpp

noeud.o: ./cpp/noeud.cpp ./h/E.h arc.o
	g++ -c ./cpp/noeud.cpp

V.o: ./cpp/V.cpp ./h/V.h noeud.o
	g++ -c ./cpp/V.cpp

graphe.o: ./cpp/graphe.cpp ./h/graphe.h E.o V.o
	g++ -c ./cpp/graphe.cpp