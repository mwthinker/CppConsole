#include <iostream>
#include <thread>
#include <sstream>

#include <console/console.h>

class TestConsole : public console::Console {
public:
	TestConsole() {
	}

protected:
	void printColor(console::Color color) {
		switch (color) {
			case console::Color::BLACK:
				std::cout << "BLACK\n";
				break;
			case console::Color::DARKBLUE:
				std::cout << "DARKBLUE\n";
				break;
			case console::Color::DARKGREEN:
				std::cout << "DARKGREEN\n";
				break;
			case console::Color::DARKCYAN:
				std::cout << "DARKCYAN\n";
				break;
			case console::Color::DARKRED:
				std::cout << "DARKRED\n";
				break;
			case console::Color::DARKMAGENTA:
				std::cout << "DARKMAGENTA\n";
				break;
			case console::Color::DARKYELLOW:
				std::cout << "DARKYELLOW\n";
				break;
			case console::Color::DARKGREY:
				std::cout << "DARKGREY\n";
				break;
			case console::Color::GREY:
				std::cout << "GREY\n";
				break;
			case console::Color::BLUE:
				std::cout << "BLUE\n";
				break;
			case console::Color::GREEN:
				std::cout << "GREEN\n";
				break;
			case console::Color::CYAN:
				std::cout << "CYAN\n";
				break;
			case console::Color::RED:
				std::cout << "RED\n";
				break;
			case console::Color::MAGENTA:
				std::cout << "MAGENTA\n";
				break;
			case console::Color::YELLOW:
				std::cout << "YELLOW\n";
				break;
			case console::Color::WHITE:
				std::cout << "WHITE\n";
				break;
		}
	}

	void initPreLoop() override {
		clear();
		setTitle("Test");
		setCursorVisibility(true);
		setCursorPosition(10, 10);
		print("hello"); // Will not be shown, covered by
		print("HHHHHHHHHHHHHH");
		print("bb");

		console::Console::setTextColor(console::Color::RED);
		console::Console::setCursorPosition(20, 10);
		console::Console::setTextColor(console::Color::GREEN);

		console::Console::setBackgroundColor(console::Color::BLACK);
		for (int i = 0; i < 16; ++i) {
			console::Console::setTextColor((console::Color) i);
			console::Console::setCursorPosition(1, i);
			printColor((console::Color) i);
		}

		console::Console::setTextColor(console::Color::BLACK);
		for (int i = 0; i < 16; ++i) {
			console::Console::setBackgroundColor((console::Color) i);
			console::Console::setCursorPosition(1, 16 + i);
			printColor((console::Color) i);
		}
		
	}

	void closePostLoop() override {
	}

private:
	void update(double deltaTime) override {
	}

	// Is called by the loop. Is called when ever a event occurs.
	void eventUpdate(console::ConsoleEvent& consoleEvent) override {
		switch (consoleEvent.type) {
			case console::ConsoleEventType::KEYDOWN:
				switch (consoleEvent.keyEvent.key) {
					case console::Key::ESCAPE:
						quit();
						break;
					case console::Key::SPACE:
						quit();
						break;
				}
				break;
		}
	}

};

int main() {
	TestConsole testConsole;
	testConsole.startLoop();
	
	return 0;
}
