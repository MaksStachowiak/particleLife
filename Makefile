all: compile link run

compile:
	@echo "Compiling..."
	@g++ -c *.cpp -std=c++17 #-E -IState -IEntities

link:
	@echo "Linking..."
	@g++ *.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system

run:
	@echo "Finished!"
	@./sfml-app

clean:
	@echo "Cleaning up..."
	@rm sfml-app -f
	@rm *.o -f
	@echo "Finished!"