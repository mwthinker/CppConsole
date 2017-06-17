#include <iostream>
#include <thread>
#include <sstream>

#include <console/console.h>

class Input {
public:
	Input() : left_(false), right_(false), up_(false), down_(false) {
	}

	bool left_;
	bool right_;
	bool up_;
	bool down_;
};

class TestConsole : public console::Console {
public:
	TestConsole() {
		x_ = 5;
		y_ = 5;
		xPos_ = 5;
		yPos_ = 5;
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
		setTextColor(console::Color::WHITE);
		setBackgroundColor(console::Color::BLACK);
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

		console::Console::setTextColor(console::Color::BLACK);
		for (int i = 0; i < 16; ++i) {
			for (int j = 0; j < 16; ++j) {
				console::Console::setTextColor((console::Color) i);
				console::Console::setBackgroundColor((console::Color) j);
				console::Console::setCursorPosition(20 + 5* i, 16 + j);
				print("Test");
			}
		}
		
		int x, y;
		getCursorPosition(x,y);
	}

	void closePostLoop() override {
	}

private:
	double x_, y_;
	int xPos_, yPos_;

	Input input_;

	void update(double deltaTime) override {
		double step = 10 * deltaTime;

		if (y_ - 1 > 1 && input_.up_) {
			y_ -= step;
		}
		if (y_ + 1 < 100 && input_.down_) {
			y_ += step;
		}
		if (x_ - 1 > 1 && input_.left_) {
			x_ -= step;
		}
		if (x_ + 1 < 100 && input_.right_) {
			x_ += step;
		}

		if ((int) x_ != xPos_) {
			xPos_ = (int) x_;
			setCursorPosition(xPos_, yPos_);
			setTextColor(console::Color::WHITE);
			setBackgroundColor(console::Color::RED);
			print(" ");
		} else if ((int) y_ != yPos_) {
			yPos_ = (int) y_;
			setCursorPosition(xPos_, yPos_);
			setTextColor(console::Color::WHITE);
			setBackgroundColor(console::Color::RED);
			print(" ");
		}

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
					case console::Key::UP:
						input_.up_ = true;
						break;
					case console::Key::DOWN:
						input_.down_ = true;
						break;
					case console::Key::LEFT:
						input_.left_ = true;
						break;
					case console::Key::RIGHT:
						input_.right_ = true;
						break;
					case console::Key::KEY_0:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(20, 5);
						print("0");
						break;
					case console::Key::KEY_1:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(22, 5);
						print("1");
						break;
					case console::Key::KEY_2:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(24, 5);
						print("2");
						break;
					case console::Key::KEY_3:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(26, 5);
						print("3");
						break;
					case console::Key::KEY_4:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(28, 5);
						print("4");
						break;
					case console::Key::KEY_5:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(30, 5);
						print("5");
						break;
					case console::Key::KEY_6:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(32, 5);
						print("6");
						break;
					case console::Key::KEY_7:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(34, 5);
						print("7");
						break;
					case console::Key::KEY_8:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(36, 5);
						print("8");
						break;
					case console::Key::KEY_9:
						setTextColor(console::Color::WHITE);
						setBackgroundColor(console::Color::RED);
						setCursorPosition(38, 5);
						print("9");
						break;
				}
				
				break;
			case console::ConsoleEventType::KEYUP:
				switch (consoleEvent.keyEvent.key) {
					case console::Key::RETURN:
						print("RETURN");
						break;
					case console::Key::UP:
						input_.up_ = false;
						break;
					case console::Key::DOWN:
						input_.down_ = false;
						break;
					case console::Key::LEFT:
						input_.left_ = false;
						break;
					case console::Key::RIGHT:
						input_.right_ = false;
						break;
				}
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
