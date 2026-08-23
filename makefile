all: jtop

jtop: main.cpp modules/*.cpp
	g++ -std=c++17 -O2 -march=native -flto main.cpp modules/*.cpp -o jtop -lftxui-component -lftxui-dom -lftxui-screen
install: jtop
	cp jtop /usr/local/bin/jtop

uninstall:
	rm -f /usr/local/bin/jtop

clean:
	rm -f jtop

rebuild: clean all

.PHONY: all clean rebuild install uninstall

