#ifndef CONSOLE_H
#define CONSOLE_H

#include <string>
#include <array>

#ifdef _WIN32
#include <windows.h>
#else
#include <list>
#include <chrono>
#endif

namespace console {

	enum class ConsoleEventType {
		KEYDOWN,
		KEYUP,
		CONSOLERESIZE
	};

	enum class Color {
		BLACK,
		BLUE,
		GREEN,
		CYAN,
		RED,
		MAGENTA,
		YELLOW,
		WHITE
	};

	enum class Key {
		UNKNOWN,
		RETURN,
		BACKSPACE,
		TAB,
		ESCAPE,
		SPACE,
		PAGEUP,
		PAGEDOWN,
		END,
		HOME,
		LEFT,
		UP,
		RIGHT,
		DOWN,
		KEY_INSERT, // Using KEY_ due to be consistent with KEY_DELETE.
		KEY_DELETE, // Using KEY_ due to name conflict with macro.
		KEY_0,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_A,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		SIZE_ENUM
	};

	struct KeyEvent {
		ConsoleEventType type;
		Key key;
		char ascii;
	};

	struct ConsoleResize {
		ConsoleEventType type;
	};

	union ConsoleEvent {
		ConsoleEventType type;
		KeyEvent keyEvent;
		ConsoleResize consoleResize;
	};

	void sleep(double time);

	class Console {
	public:
		Console();
		~Console();

		void setTitle(std::string title);

		void clear();

		inline void quit() {
			quit_ = true;
		}

		void setCursorVisibility(bool visible);

		bool isCursorVisibility() const;

		void setCursorPosition(int x, int y);

		void getCursorPosition(int& x, int& y) const;

		void setTextColor(Color color);

		void setBackgroundColor(Color color);

		const Console& print(std::string str) const;

		const Console& print(int nbr) const;

		const Console& print(double nbr) const;

		const Console& operator<<(std::string str) const;

		const Console& operator<<(int nbr) const;

		const Console& operator<<(double nbr) const;

		// Start the loop which handle all inputs and graphics in the windows. It will not
		// return until the loop is ended. Is closed when the windows is closed, i.e. a
		// call to the function quit().
		void startLoop();

	protected:
		virtual void initPreLoop() {
		}

		virtual void closePostLoop() {
		}

	private:
		void init();
		void close();

		// Is called by the loop.
		inline virtual void update(double deltaTime) {
		}

		// Is called by the loop. Is called when ever a event occurs.
		inline virtual void eventUpdate(ConsoleEvent& consoleEvent) {
		}

		bool quit_;
		Color textColor_;
		Color backgroundColor_;
#ifdef _WIN32
		std::array<bool, static_cast<size_t>(Key::SIZE_ENUM)> keyIsPressed_;
		CONSOLE_SCREEN_BUFFER_INFO initScreenBufferInfo_;
		CONSOLE_CURSOR_INFO initCursorInfo_;
		HANDLE inputHandle_;
		HANDLE outputHandle_;
#else
		struct KeyInfo {
			std::chrono::time_point<std::chrono::high_resolution_clock> time_;
			Key key_;
		};
		std::list<KeyInfo> keyIsPressed_;
#endif // _WIN32
	};

} // console.

#endif // CONSOLE_H
