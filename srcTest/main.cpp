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
				print("BLACK");
				break;
			case console::Color::DARKBLUE:
				print("DARKBLUE");
				break;
			case console::Color::DARKGREEN:
				print("DARKGREEN");
				break;
			case console::Color::DARKCYAN:
				print("DARKCYAN");
				break;
			case console::Color::DARKRED:
				print("DARKRED");
				break;
			case console::Color::DARKMAGENTA:
				print("DARKMAGENTA");
				break;
			case console::Color::DARKYELLOW:
				print("DARKYELLOW");
				break;
			case console::Color::DARKGREY:
				print("DARKGREY");
				break;
			case console::Color::GREY:
				print("GREY");
				break;
			case console::Color::BLUE:
				print("BLUE");
				break;
			case console::Color::GREEN:
				print("GREEN");
				break;
			case console::Color::CYAN:
				print("CYAN");
				break;
			case console::Color::RED:
				print("RED");
				break;
			case console::Color::MAGENTA:
				print("MAGENTA");
				break;
			case console::Color::YELLOW:
				print("YELLOW");
				break;
			case console::Color::WHITE:
				print("WHITE");
				break;
		}
	}

	void initPreLoop() override {
		setTitle("Test");
		setCursorPosition(10, 10);
		print("testing1");
		print("testing1") << "testing2: " << 2 << "\n";
		print("             testing3") << 3.1;

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
		int x, y;
		getCursorPosition(x,y);
	}

	void closePostLoop() override {
	}

private:
	void update(double deltaTime) override {
		console::sleep(1.0/60.0);
	}

	// Is called by the loop. Is called when ever a event occurs.
	void eventUpdate(console::ConsoleEvent& consoleEvent) override {
		switch (consoleEvent.type) {
			case console::ConsoleEventType::KEYDOWN:
				switch (consoleEvent.keyEvent.key) {
					case console::Key::ESCAPE:
						quit();
						break;
				}
				print("KEYDOWN");
				break;
			case console::ConsoleEventType::KEYUP:
				switch (consoleEvent.keyEvent.key) {
					case console::Key::RETURN:
						print("RETURN");
						break;
				}
				print("KEYUP");
				break;
			case console::ConsoleEventType::CONSOLERESIZE:
				clear();
				initPreLoop();
				break;
		}
	}

};

int main() {
	TestConsole testConsole;
	testConsole.startLoop();
	
	return 0;
}
