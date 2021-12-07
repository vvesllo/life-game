path = "src/main.cpp"
exit = "main.exe"

all:
	g++ $(path) -std=c++11 -o $(exit) 