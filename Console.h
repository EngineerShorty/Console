#pragma once

#include <Windows.h>
#include <string>
#include <stdexcept>

namespace Con {

	enum ScreenColor {
		BLACK,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE
	};

	class Console {
	public:
		static Console& getInstance();
		Console();

		void print(const std::string& message);
		void print(const char& c);
		void print(char c[]);
		void print(const int& integer);
		void print(const double& decimal);
		void print(const float& decimal);
		void println();
		void println(const std::string& message);
		void println(const char* c[]);
		void println(const int& integer);
		void println(const double& decimal);
		void println(const float& decimal);

		void input(std::string& input);
		void input(int& number);
		void input(double& decimal);
		void input(float& decimal);
		char getNextChar();

		//prints to screen if debugging is on
		void printerr(const std::string& message);
		void debugOn();
		void debugOff();
		bool isDebugging();//returns whether or not printerr lines will print to screen

		void txtBoldOn();
		void txtBoldOff();
		bool txtIsBold();
		void txtUnderlineOn();
		void txtUnderlineOff();
		bool txtIsUnderline();
		void txtItalicOn();
		void txtItalicOff();
		bool txtIsItalic();
		void txtBlinkingOn();
		void txtBlinkingOff();
		bool txtIsBlinking();
		void txtStrikeOn();
		void txtStrikeOff();
		bool txtIsStrikethrough();
		void txtSetColor(const ScreenColor& color);
		ScreenColor txtGetColor();
		void bkgdSetColor(const ScreenColor& color);
		ScreenColor bkgdGetColor();
		void txtSetDefault();


		void setInputMatchOutput();
		void setInputBoldOn();
		void setInputBoldOff();
		bool inputIsBold();
		void setInputUnderlineOn();
		void setInputUnderlineOff();
		bool inputIsUnderlined();
		void setInputItalicOn();
		void setInputItalicOff();
		bool inputIsItalic();
		void setInputBlinkingOn();
		void setInputBlinkingOff();
		bool inputIsBlinking();
		void setInputStrikeOn();
		void setInputStrikeOff();
		bool inputIsStrikethrough();
		void setInputColor(const ScreenColor& color);
		ScreenColor inputTextColor();
		void setInputBackground(const ScreenColor& color);
		ScreenColor inputBackgoundColor();

		void setErrColor(const ScreenColor& color) {

		}

		void refreshSettings();

		void ringBell();

		//void cursorSetVisible();		//Windows doesn't support cursor visibility
		//void cursorSetInvisible();	//Windows doesn't support cursor visibility
		void cursorMoveUp();
		void cursorMoveDown();
		void cursorMoveLeft();
		void cursorMoveRight();
		void cursorMoveUp(const int& lines);
		void cursorMoveDown(const int& lines);
		void cursorMoveLeft(const int& columns);
		void cursorMoveRight(const int& columns);
		void cursorMoveHome();
		void cursorMoveToPosition(const int& line, const int& column);
		void cursorMoveNextLine();
		void cursorMovePrevLine();
		void cursorMoveDownLines(const int& lines);
		void cursorMoveUpLines(const int& lines);
		void cursorPositionSave();
		void cursorPositionRestore();
		int cursorLine();
		int cursorColumn();

		int screenHeight();
		int screenWidth();
		void screenResize(int width, int height);
		int screenPositionX();
		int screenPositionY();
		void screenPositionSet(int x, int y);
		void screenClear();
		void screenSave();
		void screenRestore();
		void screenCopyToClipboard();

		void titleSet(const std::string& title);
		std::string titleGet();

		void pause();

		std::string lastOutput();
		std::string lastInput();

		void clearLine(int line);
		void modeQuickEditEnable();
		void modeQuickEditDisable();

	protected:
		HANDLE consoleOutput;
		HANDLE consoleInput;
		DWORD charsWritten;
		bool debugging = false;
		Console(const Console&) = delete;
		Console& operator=(const Console&) = delete;

		bool curVisible = true;

		bool txBold = false;
		bool txUnderline = false;
		bool txItalic = false;
		bool txBlinking = false;
		bool txStrikethrough = false;
		ScreenColor txColor = WHITE;
		ScreenColor bkColor = BLACK;

		bool inputFontSet = false;
		bool inputBold = false;
		bool inputUnderline = false;
		bool inputItalic = false;
		bool inputBlinking = false;
		bool inputStrike = false;
		ScreenColor inputColor = CYAN;
		ScreenColor inputBkgd = BLACK;

		ScreenColor errColor = RED;

		std::string lastPrint = "";
		std::string history = "";
		std::string lastIn = "";

		void setupInputFont();
	};

	extern Console& console;

}
