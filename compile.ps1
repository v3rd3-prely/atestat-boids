# COMPILE

g++  -c src\main.cpp -Iext\SFML\include -Iinclude -o obj\main.o
g++  -c src\rest.cpp -Iext\SFML\include -Iinclude -o obj\rest.o
g++  -c src\fps.cpp -Iext\SFML\include -Iinclude -o obj\fps.o
g++  -c src\boid.cpp -Iext\SFML\include -Iinclude -o obj\boid.o
g++  -c src\ray.cpp -Iext\SFML\include -Iinclude -o obj\ray.o
g++  -c src\wall.cpp -Iext\SFML\include -Iinclude -o obj\wall.o
g++  -c src\slider.cpp -Iext\SFML\include -Iinclude -o obj\slider.o

# LINK

g++ obj\*.o -o bin\main.exe -Lext\SFML\lib -lsfml-graphics -lsfml-window -lsfml-system

# REMOVE TEMP FILES

rm obj\*.*