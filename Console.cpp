#include "C:\Users\Engin\OneDrive\Documents\Programming Lib\ConsoleLibrary\ConsoleLibrary\Console.h"

namespace Con {

	Console& console = Console::getInstance();

	inline Console& Console::getInstance() {
		static Console instance;
		return instance;
	}

	inline Console::Console() {
		consoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		consoleInput = GetStdHandle(STD_INPUT_HANDLE);
		if (consoleOutput == INVALID_HANDLE_VALUE || consoleInput == INVALID_HANDLE_VALUE) {
			exit(1);
		}
		charsWritten = 0;
		DWORD consoleMode;
		GetConsoleMode(consoleOutput, &consoleMode);
		consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
		SetConsoleMode(consoleOutput, consoleMode);
		txtSetDefault();
		modeQuickEditEnable();
	}

	void Console::print(const std::string& message) {
		bool wasVisible = curVisible;
		//cursorSetInvisible();
		const char* charString = message.c_str();
		WriteConsoleA(consoleOutput, charString, message.length(), &charsWritten, NULL);
		lastPrint = message;
		history += message;
	}

	void Console::print(const char& c) {
		WriteConsoleA(consoleOutput, &c, 1, &charsWritten, NULL);
		lastPrint = c;
		history += lastPrint;
	}

	void Console::print(char c[]) {
		std::string message = c;
		print(message);
		lastPrint = c;
		history += lastPrint;
	}

	void Console::print(const int& integer) {
		std::string message = std::to_string(integer);
		print(message);
		lastPrint = message;
		history += message;
	}

	void Console::print(const double& decimal) {
		std::string message = std::to_string(decimal);
		print(message);
		lastPrint = message;
		history += message;
	}

	void Console::print(const float& decimal) {
		std::string message = std::to_string(decimal);
		print(message);
		lastPrint = message;
		history += message;
	}

	void Console::println(const std::string& message) {
		print(message);
		print('\n');
		lastPrint = message;
		history += message;
	}

	void Console::println() {
		print('\n');
		history += "\n";
	}

	void Console::println(const char* c[]) {
		print(*c);
		println();		
	}

	void Console::println(const int& integer) {
		print(integer);
		println();
	}

	void Console::println(const double& decimal) {
		print(decimal);
		println();
	}

	void Console::println(const float& decimal) {
		print(decimal);
		println();
	}

	void Console::printerr(const std::string& message) {
		ScreenColor lastColor = txColor;
		txtSetColor(errColor);
		if (debugging) {
			if (cursorColumn() != 0) println();
			println(message);
		}
		txtSetColor(lastColor);
	}

	void Console::input(std::string& input) {
		//set up font, if it's been set
		if (inputFontSet) {
			setupInputFont();
		}
		bool curWasVisible = curVisible;
		DWORD inputBytes;
		const int BUFFER_SIZE = 256;
		char buffer[BUFFER_SIZE];
		if (ReadConsoleA(consoleInput, buffer, BUFFER_SIZE - 1, &inputBytes, NULL)) {
			buffer[inputBytes] = '\0';
			input = buffer;
			input.erase(std::remove(input.begin(), input.end(), '\r'), input.end());
			input.erase(std::remove(input.begin(), input.end(), '\n'), input.end());
			lastIn = input;
			history += lastIn;
			history += "\r";
		}
		else {
			input = "";
		}
		if (inputFontSet) refreshSettings();
	}

	void Console::input(int& number) {
		std::string buffer;
		input(buffer);
		try {
			number = std::stoi(buffer);
		}
		catch (const std::invalid_argument& e) {
			printerr(buffer);
			printerr(" cannot be interpreted as an integer.\nPlease try again: ");
			input(number);
		}
		catch (const std::out_of_range& e) {
			printerr(buffer);
			printerr(" is out of range.\nPlease try again: ");
			input(number);
		}
	}

	void Console::input(double& decimal) {
		std::string buffer;
		input(buffer);
		try {
			decimal = std::stod(buffer);
		}
		catch (const std::invalid_argument& e) {
			printerr(buffer);
			printerr(" cannot be interpreted as a decimal.\nPlease try again: ");
			input(decimal);
		}
		catch (const std::out_of_range& e) {
			printerr(buffer);
			printerr(" is out of range.\nPlease try again: ");
			input(decimal);
		}
	}

	void Console::input(float& decimal) {
		std::string buffer;
		input(buffer);
		try {
			decimal = std::stof(buffer);
		}
		catch (const std::invalid_argument& e) {
			printerr(buffer);
			printerr(" cannot be interpreted as a decimal.\nPlease try again: ");
			input(decimal);
		}
		catch (const std::out_of_range& e) {
			printerr(buffer);
			printerr(" is out of range.\nPlease try again: ");
			input(decimal);
		}
	}

	void Console::debugOn() {
		debugging = true;
	}

	void Console::debugOff() {
		debugging = false;
	}

	bool Console::isDebugging() {
		return debugging;
	}

	char Console::getNextChar() {
		INPUT_RECORD inputRecord;
		DWORD eventsRead;
		while (true) {
			ReadConsoleInput(consoleInput, &inputRecord, 1, &eventsRead);
			if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
				return inputRecord.Event.KeyEvent.uChar.AsciiChar;
			}
		}
		
	}
	void Console::screenClear() {
		print("\033[2J\033[H");
	}
	void Console::txtBoldOn() {
		print("\033[1m");
		txBold = true;
	}
	void Console::txtBoldOff() {
		print("\033[22m");
		txBold = false;
	}
	bool Console::txtIsBold() {
		return txBold;
	}
	void Console::txtUnderlineOn() {
		print("\033[4m");
		txUnderline = true;
	}
	void Console::txtUnderlineOff() {
		print("\033[24m");
		txUnderline = false;
	}
	bool Console::txtIsUnderline() {
		return txUnderline;
	}
	void Console::txtItalicOn() {
		print("\033[3m");
		txItalic = true;
	}
	void Console::txtItalicOff() {
		print("\033[23m");
		txItalic = false;
	}
	bool Console::txtIsItalic() {
		return txItalic;
	}
	void Console::txtBlinkingOn() {
		print("\033[5m");
		txBlinking = true;
	}
	void Console::txtBlinkingOff() {
		print("\033[25m");
		txBlinking = false;
	}
	bool Console::txtIsBlinking() {
		return txBlinking;
	}
	void Console::txtStrikeOn() {
		print("\033[9m");
		txStrikethrough = true;
	}
	void Console::txtStrikeOff() {
		print("\033[29m");
		txStrikethrough = false;
	}
	bool Console::txtIsStrikethrough() {
		return txStrikethrough;
	}
	void Console::txtSetColor(const ScreenColor& color) {
		int colorNumber = 30 + static_cast<int>(color);
		std::string colorNumberString = std::to_string(colorNumber);
		std::string colorMessage = "\033[";
		colorMessage.append(colorNumberString);
		colorMessage.append("m");
		print(colorMessage);
		txColor = color;
	}
	ScreenColor Console::txtGetColor() {
		return txColor;
	}
	void Console::bkgdSetColor(const ScreenColor& color) {
		int colorNumber = 40 + static_cast<int>(color);
		std::string colorNumberString = std::to_string(colorNumber);
		std::string colorMessage = "\033[";
		colorMessage.append(colorNumberString);
		colorMessage.append("m");
		print(colorMessage);
		bkColor = color;
	}
	ScreenColor Console::bkgdGetColor() {
		return bkColor;
	}
	void Console::txtSetDefault() {
		txtBoldOff();
		txtUnderlineOff();
		txtItalicOff();
		txtBlinkingOff();
		txtStrikeOff();
		txtSetColor(WHITE);
		bkgdSetColor(BLACK);
	}
	void Console::setInputMatchOutput() {
		inputFontSet = false;
		inputBold = txBold;
		inputUnderline = txUnderline;
		inputItalic = txItalic;
		inputBlinking = txBlinking;
		inputStrike = txStrikethrough;
		inputColor = txColor;
		inputBkgd = bkColor;
	}
	void Console::setInputBoldOn() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputBold = true;
	}
	void Console::setInputBoldOff() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputBold = false;
	}
	bool Console::inputIsBold() {
		if (inputFontSet) {
			return inputBold;
		}
		else {
			return txBold;
		}
	}
	void Console::setInputUnderlineOn() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputUnderline = true;
	}
	void Console::setInputUnderlineOff() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputUnderline = false;
	}
	bool Console::inputIsUnderlined() {
		if (inputFontSet) {
			return inputUnderline;
		}
		else {
			return txUnderline;
		}
	}
	void Console::setInputItalicOn() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputItalic = true;
	}
	void Console::setInputItalicOff() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputItalic = false;
	}
	bool Console::inputIsItalic() {
		if (inputFontSet) {
			return inputItalic;
		}
		else {
			return txItalic;
		}
	}
	void Console::setInputBlinkingOn() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputBlinking = true;
	}
	void Console::setInputBlinkingOff() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputBlinking = false;
	}
	bool Console::inputIsBlinking() {
		if (inputFontSet) {
			return inputBlinking;
		}
		else {
			return txBlinking;
		}
	}
	void Console::setInputStrikeOn() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputStrike = true;
	}
	void Console::setInputStrikeOff() {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputStrike = false;
	}
	bool Console::inputIsStrikethrough() {
		if (inputFontSet) {
			return inputStrike;
		}
		else {
			return txStrikethrough;
		}
	}
	void Console::setInputColor(const ScreenColor& color) {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputColor = color;
	}
	ScreenColor Console::inputTextColor() {
		if (inputFontSet) {
			return inputColor;
		}
		else {
			return txColor;
		}
	}
	void Console::setInputBackground(const ScreenColor& color) {
		if (!inputFontSet) {
			setInputMatchOutput();
		}
		inputFontSet = true;
		inputBkgd = color;
	}
	ScreenColor Console::inputBackgoundColor() {
		if (inputFontSet) {
			return inputBkgd;
		}
		else {
			return bkColor;
		}
	}
	void Console::ringBell() {
		print('\a');
	}
	//Windows doesn't support cursor visibility settings
	/*void Console::cursorSetVisible() {
		print("\033[?25h");
		curVisible = true;
	}*/
	/*void Console::cursorSetInvisible() {
		//print("\033[?25l");
		curVisible = false;
	}*/
	void Console::cursorMoveUp() {
		print("\033[1A");
	}
	void Console::cursorMoveDown() {
		print("\033[1B");
	}
	void Console::cursorMoveLeft() {
		print("\033[1D");
	}
	void Console::cursorMoveRight() {
		print("\033[1C");
	}
	void Console::cursorMoveUp(const int& lines) {
		std::string ansiCode = "\033[";
		ansiCode += std::to_string(lines);
		ansiCode += "A";
		print(ansiCode);
	}
	void Console::cursorMoveDown(const int& lines) {
		std::string ansiCode = "\033[";
		ansiCode += std::to_string(lines);
		ansiCode += "B";
		print(ansiCode);
	}
	void Console::cursorMoveLeft(const int& columns) {
		std::string ansiCode = "\033[";
		ansiCode += std::to_string(columns);
		ansiCode += "D";
		print(ansiCode);
	}
	void Console::cursorMoveRight(const int& columns) {
		std::string ansiCode = "\033[";
		ansiCode += std::to_string(columns);
		ansiCode += "C";
		print(ansiCode);
	}
	void Console::cursorMoveHome() {
		print("\033[H");
	}
	void Console::cursorMoveToPosition(const int& line, const int& column) {
		std::string ansiCode = "\033[";
		ansiCode += std::to_string(line + 1);
		ansiCode += ";";
		ansiCode += std::to_string(column + 1);
		ansiCode += "H";
		print(ansiCode);
	}
	void Console::cursorMoveNextLine() {
		print("\033[1E");
	}
	void Console::cursorMovePrevLine() {
		print("\033[1F");
	}
	void Console::cursorMoveDownLines(const int& lines) {
		std::string ansiCode = "\033[";
		ansiCode += std::to_string(lines);
		ansiCode += "E";
		print(ansiCode);
	}
	void Console::cursorMoveUpLines(const int& lines) {
		std::string ansiCode = "\033[";
		ansiCode += std::to_string(lines);
		ansiCode += "F";
		print(ansiCode);
	}
	void Console::cursorPositionSave() {
		print("\033[s");
	}
	void Console::cursorPositionRestore() {
		print("\033[u");
	}
	void Console::screenSave() {
		print("\033[?47h");
	}
	void Console::screenRestore() {
		print("\033[?47l");
	}
	void Console::titleSet(const std::string& title) {
		SetConsoleTitleA(title.c_str());
	}
	std::string Console::titleGet() {
		char title[256];
		GetConsoleTitleA(title, 256);
		return std::string(title);
	}
	int Console::cursorLine() {
		CONSOLE_SCREEN_BUFFER_INFO info;
		if (GetConsoleScreenBufferInfo(consoleOutput, &info)) {
			COORD position = info.dwCursorPosition;
			return position.Y;
		}
		else {
			return 0;
		}
	}
	int Console::cursorColumn() {
		CONSOLE_SCREEN_BUFFER_INFO info;
		if (GetConsoleScreenBufferInfo(consoleOutput, &info)) {
			COORD position = info.dwCursorPosition;
			return position.X;
		}
		else {
			return 0;
		}
	}
	int Console::screenHeight() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	}
	int Console::screenWidth() {
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
		return csbi.srWindow.Right - csbi.srWindow.Left + 1;
	}
	void Console::screenResize(int width, int height) {
		SMALL_RECT windowSize = { 0, 0, width - 1, height - 1 };
		SetConsoleWindowInfo(consoleOutput, TRUE, &windowSize);
		COORD bufferSize = { width, height };
		SetConsoleScreenBufferSize(consoleOutput, bufferSize);
	}
	void Console::screenPositionSet(int x, int y) {
		HWND consoleWindow = GetConsoleWindow();
		SetWindowPos(consoleWindow, NULL, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
	}
	int Console::screenPositionX() {
		HWND consoleWindow = GetConsoleWindow();
		RECT rect;
		GetWindowRect(consoleWindow, &rect);
		return rect.left;
	}
	int Console::screenPositionY() {
		HWND consoleWindow = GetConsoleWindow();
		RECT rect;
		GetWindowRect(consoleWindow, &rect);
		return rect.top;
	}
	void Console::pause() {
		system("pause");
	}
	void Console::screenCopyToClipboard() {
		OpenClipboard(NULL);
		EmptyClipboard();
		HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, history.size() + 1);
		memcpy(GlobalLock(hGlobal), history.c_str(), history.size() + 1);
		GlobalUnlock(hGlobal);
		SetClipboardData(CF_TEXT, hGlobal);
		CloseClipboard();
	}
	std::string Console::lastOutput() {
		return lastPrint;
	}
	std::string Console::lastInput() {
		return lastIn;
	}
	void Console::clearLine(int line) {
		// Save the current cursor position
		cursorPositionSave();
		// Move the cursor to the specified line and the first column
		cursorMoveToPosition(line, 0);
		// Get the screen width to determine how many spaces to print
		int width = screenWidth();
		// Print spaces to clear the line
		for (int i = 0; i < width; ++i) {
			print(' ');
		}
		// Move the cursor back to the specified line and the first column
		cursorMoveToPosition(line, 0);
		// Restore the original cursor position
		cursorPositionRestore();
	}
	void Console::modeQuickEditEnable() {
		DWORD consoleMode;
		GetConsoleMode(consoleInput, &consoleMode);
		consoleMode |= ENABLE_QUICK_EDIT_MODE;
		SetConsoleMode(consoleInput, consoleMode);
	}
	void Console::modeQuickEditDisable() {
		DWORD consoleMode;
		GetConsoleMode(consoleInput, &consoleMode);
		consoleMode &= ~ENABLE_QUICK_EDIT_MODE;
		SetConsoleMode(consoleInput, consoleMode);
	}
	void Console::setupInputFont() {
		std::string breakCode = "\033[";

		std::string settingStream = breakCode;
		settingStream += (inputBold) ? "1m" : "22m";

		settingStream += breakCode;
		settingStream += (inputUnderline) ? "4m" : "24m";

		settingStream += breakCode;
		settingStream += (inputItalic) ? "3m" : "23m";

		settingStream += breakCode;
		settingStream += (inputBlinking) ? "5m" : "25m";

		settingStream += breakCode;
		settingStream += (inputStrike) ? "9m" : "29m";

		//set font color
		settingStream += breakCode;
		int colorNumber = 30 + static_cast<int>(inputColor);
		settingStream += std::to_string(colorNumber);
		settingStream += "m";

		//set background color
		settingStream += breakCode;
		int bkgdColorNumber = 40 + static_cast<int>(inputBkgd);
		settingStream += std::to_string(bkgdColorNumber);
		settingStream += "m";

		print(settingStream);

		//reset the output settings
	}
	void Console::refreshSettings() {
		if (txBold) txtBoldOn();
		else txtBoldOff();
		if (txUnderline) txtUnderlineOn();
		else txtUnderlineOff();
		if (txItalic) txtItalicOn();
		else txtItalicOff();
		if (txBlinking) txtBlinkingOn();
		else txtBlinkingOff();
		txtSetColor(txColor);
		bkgdSetColor(bkColor);
	}
}