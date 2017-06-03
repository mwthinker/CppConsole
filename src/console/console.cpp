#include "console.h"

#include <iostream>
#include <sstream>
#include <thread>
#include <array>
#include <chrono>

namespace console {

	void sleep(double time) {
		std::this_thread::sleep_for(std::chrono::duration<double>(time));
	}

	Console::Console() : quit_(false), keyIsPressed_({false}), textColor_(Color::WHITE), backgroundColor_(Color::BLACK) {
		init();
	}

	Console::~Console() {
		close();
	}

} // Namespace console.

#ifdef _WIN32

//#define STRICT

namespace console {

	namespace {

		inline Key convertKey(WORD keyCode, DWORD controlKeyState) {
			if (controlKeyState == RIGHT_CTRL_PRESSED) {
				std::cout << "RIGHT_CTRL_PRESSED" << std::endl;
			}

			switch (keyCode) {
				case VK_RETURN:	return Key::RETURN;
				case VK_TAB: return Key::TAB;
				case VK_BACK: return Key::RETURN;
				case VK_SHIFT: return Key::SHIFT;
				case VK_CONTROL: return Key::CTRL;
				case VK_CAPITAL: return Key::CAPSLOCK;
				case VK_ESCAPE:	return Key::ESCAPE;
				case VK_SPACE: return Key::SPACE;
				case VK_PRIOR: return Key::PAGEUP;
				case VK_NEXT:return Key::PAGEDOWN;
				case VK_HOME: return Key::HOME;
				case VK_END:return Key::END;
				case VK_LEFT: return Key::LEFT;
				case VK_UP: return Key::UP;
				case VK_RIGHT: return Key::RIGHT;
				case VK_DOWN: return Key::DOWN;
				case VK_INSERT: return Key::INSERT;
				case VK_DELETE: return Key::KEY_DELETE;
				case 0x30: return Key::KEY_0;
				case 0x31: return Key::KEY_1;
				case 0x32: return Key::KEY_2;
				case 0x33: return Key::KEY_3;
				case 0x34: return Key::KEY_4;
				case 0x35: return Key::KEY_5;
				case 0x36: return Key::KEY_6;
				case 0x37: return Key::KEY_7;
				case 0x38: return Key::KEY_8;
				case 0x39: return Key::KEY_9;
				case 0x41: return Key::KEY_A;
				case 0x42: return Key::KEY_B;
				case 0x43: return Key::KEY_C;
				case 0x44: return Key::KEY_D;
				case 0x45: return Key::KEY_E;
				case 0x46: return Key::KEY_F;
				case 0x47: return Key::KEY_G;
				case 0x48: return Key::KEY_H;
				case 0x49: return Key::KEY_I;
				case 0x4A: return Key::KEY_J;
				case 0x4B: return Key::KEY_K;
				case 0x4C: return Key::KEY_L;
				case 0x4D: return Key::KEY_M;
				case 0x4E: return Key::KEY_N;
				case 0x4F: return Key::KEY_O;
				case 0x50: return Key::KEY_P;
				case 0x51: return Key::KEY_Q;
				case 0x52: return Key::KEY_R;
				case 0x53: return Key::KEY_S;
				case 0x54: return Key::KEY_T;
				case 0x55: return Key::KEY_U;
				case 0x56: return Key::KEY_V;
				case 0x57: return Key::KEY_W;
				case 0x58: return Key::KEY_X;
				case 0x59: return Key::KEY_Y;
				case 0x5A: return Key::KEY_Z;
				case VK_F1: return Key::F1;
				case VK_F2: return Key::F2;
				case VK_F3: return Key::F3;
				case VK_F4: return Key::F4;
				case VK_F5: return Key::F5;
				case VK_F6: return Key::F6;
				case VK_F7: return Key::F7;
				case VK_F8: return Key::F8;
				case VK_F9: return Key::F9;
				case VK_F10: return Key::F10;
				case VK_F11: return Key::F11;
				case VK_F12: return Key::F12;
			}
			return Key::UNKNOWN;
		}

	} // Namespace anonymous.

	const Console& Console::operator<<(std::string str) const {
		std::cout << str;
		return *this;
	}

	const Console& Console::operator<<(int nbr) const {
		std::stringstream stream;
		stream << nbr;
		std::cout << stream.str();
		return *this;
	}

	const Console& Console::operator<<(double nbr) const {
		std::stringstream stream;
		stream << nbr;
		std::cout << stream.str();
		return *this;
	}

	void Console::startLoop() {
		initPreLoop();
		
		auto time = std::chrono::high_resolution_clock::now();
		while (!quit_) {
			DWORD eventsRead = 0;
			DWORD nbr = 1;

			while (GetNumberOfConsoleInputEvents(inputHandle_, &nbr) && nbr > 0) {
				INPUT_RECORD inputRecord;
				DWORD inputLength = 1;
				ReadConsoleInput(inputHandle_, &inputRecord, inputLength, &eventsRead);
				if (inputRecord.EventType == KEY_EVENT) {
					ConsoleEvent consoleEvent;
					consoleEvent.keyEvent.type = inputRecord.Event.KeyEvent.bKeyDown ? ConsoleEventType::KEYDOWN : ConsoleEventType::KEYUP;
					consoleEvent.keyEvent.key = convertKey(inputRecord.Event.KeyEvent.wVirtualKeyCode, inputRecord.Event.KeyEvent.dwControlKeyState);
					switch (consoleEvent.keyEvent.key) {
						case Key::UNKNOWN:
							eventUpdate(consoleEvent);
							break;
						default:
							switch (consoleEvent.keyEvent.type) {
								case ConsoleEventType::KEYDOWN:
									if (keyIsPressed_[(int) consoleEvent.keyEvent.key]) {
										break;
									} else {
										keyIsPressed_[(int) consoleEvent.keyEvent.key] = true;
									}
									eventUpdate(consoleEvent);
									break;
								case ConsoleEventType::KEYUP:
									keyIsPressed_[(int) consoleEvent.keyEvent.key] = false;
									eventUpdate(consoleEvent);
									break;
							}
							break;
					}
				}
			}

			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> delta = currentTime - time;
			update(delta.count());
			time = currentTime;
		}
		closePostLoop();
		close();
	}

	void Console::setTitle(std::string title) {
		SetConsoleTitleA(title.c_str());
	}

	void Console::clear() {
		CONSOLE_SCREEN_BUFFER_INFO screen;
		GetConsoleScreenBufferInfo(outputHandle_, &screen);
		DWORD numberOfCharsWritten;
		COORD coord = {0, 0};
		FillConsoleOutputCharacterA(outputHandle_, ' ', screen.dwSize.X * screen.dwSize.Y, coord, &numberOfCharsWritten);
		FillConsoleOutputAttribute(outputHandle_, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
			screen.dwSize.X * screen.dwSize.Y, coord, &numberOfCharsWritten
		);
		SetConsoleCursorPosition(outputHandle_, coord);
	}

	void Console::setCursorVisibility(bool visible) {
		CONSOLE_CURSOR_INFO consoleCursorInfo;
		GetConsoleCursorInfo(outputHandle_, &consoleCursorInfo);
		consoleCursorInfo.bVisible = visible ? TRUE : FALSE;
		SetConsoleCursorInfo(outputHandle_, &consoleCursorInfo);
	}

	void Console::init() {
		outputHandle_ = GetStdHandle(STD_OUTPUT_HANDLE);
		inputHandle_ = GetStdHandle(STD_INPUT_HANDLE);

		// Save current console settings.
		GetConsoleScreenBufferInfo(outputHandle_, &initScreenBufferInfo_);
		GetConsoleCursorInfo(outputHandle_, &initCursorInfo_);
	}

	void Console::print(std::string str) const {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(outputHandle_, &csbi);
		DWORD nbr;
		WriteConsoleOutputCharacter(outputHandle_, str.c_str(), str.size(), csbi.dwCursorPosition, &nbr);
	}

	bool Console::isCursorVisibility() const {
		CONSOLE_CURSOR_INFO consoleCursorInfo;
		GetConsoleCursorInfo(outputHandle_, &consoleCursorInfo);
		return consoleCursorInfo.bVisible == TRUE ? true : false;
	}

	void Console::close() {
		// Restore console settings.
		SetConsoleTextAttribute(outputHandle_, (WORD) initScreenBufferInfo_.wAttributes);
		SetConsoleCursorInfo(outputHandle_, &initCursorInfo_);
	}

	void Console::setCursorPosition(int x, int y) {
		SetConsoleCursorPosition(outputHandle_, {(SHORT) x, (SHORT) y});
	}

	void Console::getCursorPosition(int& x, int& y) const {
		tagPOINT point;
		GetCursorPos(&point);
		x = point.x;
		y = point.y;
	}

	void Console::setTextColor(Color color) {
		textColor_ = color;
		SetConsoleTextAttribute(outputHandle_, (WORD) backgroundColor_ << 4 | (WORD) textColor_);
	}

	void Console::setBackgroundColor(Color color) {
		backgroundColor_ = color;
		SetConsoleTextAttribute(outputHandle_, (WORD) backgroundColor_ << 4 | (WORD) textColor_);
	}

} // Namespace console.

#else

#include <sstream>
#include <curses.h>

namespace console {

	namespace {

		inline Key convertKey(int keyCode) {
			switch (keyCode) {
				case KEY_ENTER:	return Key::RETURN;
				case 9: return Key::TAB;
				//case VK_BACK: return Key::RETURN;
				case KEY_SLEFT: return Key::SHIFT;
				//case VK_CONTROL: return Key::CTRL;
				//case VK_CAPITAL: return Key::CAPSLOCK;
				case 27: return Key::ESCAPE;
				case ' ': return Key::SPACE;
				case KEY_PPAGE: return Key::PAGEUP;
				case KEY_NPAGE: return Key::PAGEDOWN;
				case KEY_HOME: return Key::HOME;
				case KEY_END: return Key::END;
				case KEY_LEFT: return Key::LEFT;
				case KEY_UP: return Key::UP;
				case KEY_RIGHT: return Key::RIGHT;
				case KEY_DOWN: return Key::DOWN;
				case KEY_IC: return Key::INSERT;
				case KEY_DC: return Key::KEY_DELETE;
				case '0': return Key::KEY_0;
				case '1': return Key::KEY_1;
				case '2': return Key::KEY_2;
				case '3': return Key::KEY_3;
				case '4': return Key::KEY_4;
				case '5': return Key::KEY_5;
				case '6': return Key::KEY_6;
				case '7': return Key::KEY_7;
				case '8': return Key::KEY_8;
				case '9': return Key::KEY_9;
				case 'a': // Fall trough.
				case 'A': return Key::KEY_A;
				case 'b': // Fall trough.
				case 'B': return Key::KEY_B;
				case 'c': // Fall trough.
				case 'C': return Key::KEY_C;
				case 'd': // Fall trough.
				case 'D': return Key::KEY_D;
				case 'e': // Fall trough.
				case 'E': return Key::KEY_E;
				case 'f': // Fall trough.
				case 'F': return Key::KEY_F;
				case 'g': // Fall trough.
				case 'G': return Key::KEY_G;
				case 'h': // Fall trough.
				case 'H': return Key::KEY_H;
				case 'i': // Fall trough.
				case 'I': return Key::KEY_I;
				case 'j': // Fall trough.
				case 'J': return Key::KEY_J;
				case 'k': // Fall trough.
				case 'K': return Key::KEY_K;
				case 'l': // Fall trough.
				case 'L': return Key::KEY_L;
				case 'm': // Fall trough.
				case 'M': return Key::KEY_M;
				case 'n': // Fall trough.
				case 'N': return Key::KEY_N;
				case 'p': // Fall trough.
				case 'P': return Key::KEY_P;
				case 'q': // Fall trough.
				case 'Q': return Key::KEY_Q;
				case 'r': // Fall trough.
				case 'R': return Key::KEY_R;
				case 's': // Fall trough.
				case 'S': return Key::KEY_S;
				case 't': // Fall trough.
				case 'T': return Key::KEY_T;
				case 'u': // Fall trough.
				case 'U': return Key::KEY_U;
				case 'v': // Fall trough.
				case 'V': return Key::KEY_V;
				case 'w': // Fall trough.
				case 'W': return Key::KEY_W;
				case 'x': // Fall trough.
				case 'X': return Key::KEY_X;
				case 'y': // Fall trough.
				case 'Y': return Key::KEY_Y;
				case 'z': // Fall trough.
				case 'Z': return Key::KEY_Z;
			}
			return Key::UNKNOWN;
		}

		inline const char * colorToBackgroundAnsi(Color color) {
			switch (color) {
				case Color::BLACK:
				case Color::DARKGREY:
					return "\e[40m";
				case Color::BLUE:
				case Color::DARKBLUE:
					return "\e[44m";
				case Color::GREEN:
				case Color::DARKGREEN:
					return "\e[42m";
				case Color::CYAN:
				case Color::DARKCYAN:
					return "\e[46m";
				case Color::RED:
				case Color::DARKRED:
					return "\e[41m";
				case Color::MAGENTA:
				case Color::DARKMAGENTA:
					return "\e[45m";
				case Color::YELLOW:
				case Color::DARKYELLOW:
					return "\e[43m";
				case Color::GREY:
				case Color::WHITE:
					return "\e[47m";
			}
			return "";
		}

		inline const char * colorToTextAnsi(Color color) {
			switch (color) {
				case Color::BLACK:
					return "\e[22;30m";
				case Color::GREY:
					return "\e[22;37m";
				case Color::BLUE:
					return "\e[22;34m";
				case Color::DARKBLUE:
					return "\e[22;34m";
				case Color::GREEN:
					return "\e[22;32m";
				case Color::DARKGREEN:
					return "\e[01;32m";
				case Color::CYAN:
					return "\e[22;36m";
				case Color::DARKCYAN:
					return "\e[01;36m";
				case Color::RED:
					return "\e[22;31m";
				case Color::DARKRED:
					return "\e[01;31m";
				case Color::MAGENTA:
					return "\e[22;35m";
				case Color::DARKMAGENTA:
					return "\e[01;35m";
				case Color::DARKYELLOW:
					return "\e[22;33m";
				case Color::YELLOW:
					return "\e[01;33m";
				case Color::DARKGREY:
					return "\e[01;30m";
				case Color::WHITE:
					return "\e[01;37m";
			}
			return "";
		}
		
	} // Namespace anonymous.

	void Console::startLoop() {
		initPreLoop();

		auto time = std::chrono::high_resolution_clock::now();
		while (!quit_) {
			while (int ch = getch() != ERR ) {
				ConsoleEvent consoleEvent;
				consoleEvent.keyEvent.type = ConsoleEventType::KEYDOWN;
				consoleEvent.keyEvent.key = convertKey(ch);
				eventUpdate(consoleEvent);
			}

			auto currentTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> delta = currentTime - time;
			update(delta.count());
			time = currentTime;
		}
	}

	void Console::print(std::string str) const {
	}

	const Console& Console::operator<<(std::string str) const {
		std::cout << str;
		return *this;
	}

	const Console& Console::operator<<(int nbr) const {
		std::stringstream stream;
		stream << nbr;
		std::cout << stream.str();
		return *this;
	}

	const Console& Console::operator<<(double nbr) const {
		std::stringstream stream;
		stream << nbr;
		std::cout << stream.str();
		return *this;
	}

	void Console::setCursorVisibility(bool visible) {
	}

	bool Console::isCursorVisibility() const{
		return true;
	}

	void Console::clear() {
		::clear();
	}

	void Console::setCursorPosition(int x, int y) {
		wmove(stdscr, y, x);
	}

	void Console::getCursorPosition(int& x, int& y) const {
	}

	void Console::setTextColor(Color color) {
		textColor_ = color;
		std::cout << colorToBackgroundAnsi(backgroundColor_) << colorToTextAnsi(textColor_);
	}

	void Console::setBackgroundColor(Color color) {
		backgroundColor_ = color;
		std::cout << colorToBackgroundAnsi(backgroundColor_);
	}

	void Console::setTitle(std::string title) {
		std::cout << "\033]0;" << title << "\007";
	}

	void Console::init() {
		initscr();
		cbreak();
		nodelay(stdscr, TRUE);
		noecho();
		keypad(stdscr, TRUE);
	}

	void Console::close() {
		endwin();
	}

} // Namespace console.

#endif // _WIN32
