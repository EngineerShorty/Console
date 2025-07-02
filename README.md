

# 🖥️ Con::Console – A Modern Console API for Windows C++

**Con::Console** is an object-oriented console abstraction for C++ on Windows. Designed to bring clarity and power to console I/O, it replaces the verbose legacy of `std::cout` with a simpler, (I think) more intuitive way to interact with input and output from the console.  It also makes features that are available on modern consoles easier to use (like changing colors and moving the cursor).  

If you do need or want the streaming functionality of cin and cout, that's certainly the better tool.  But if you don't need that functionality, this may be a more straightforward tool for you.

---

## ✨ Features at a Glance

- 🔤 Easy-to-read `print()` and `println()` methods for all major types
- 🎨 Text styling: bold, underline, italic, blinking, strike-through
- 🌈 Foreground and background color support with clean `ScreenColor` enums
- 🧭 Full cursor control: position, save/restore, movement, and screen metrics
- 💬 Input handling for strings, ints, floats, and typed styles
- 🐞 Debug-only output with `printerr()` toggle
- 📋 Clipboard support, console resizing, and window title control
- 🔁 Singleton design (`Console::getInstance()`) ensures consistent global access
- 🔔 Usability touches like `pause()`, `ringBell()`, and `screenClear()`

---

## 🚀 Getting Started

### 📦 Include the header

```cpp
#include "Console.h"
using namespace Con;
```

### 👋 Print Hello, World

```cpp
int main() {
    console.println("Hello, World!");
    return 0;
}
```

### 🎨 Set text color and style

```cpp
console.txtSetColor(RED);
console.txtBoldOn();
console.println("Warning: Something went wrong!");
```

### 📥 Gather typed input

```cpp
std::string name;
console.print("Enter your name: ");
console.input(name);
console.println("Hello, " + name + "!");
```

---

## 🧩 Platform Compatibility

🪟 **Windows Only (for now)**  
This library uses Windows console APIs under the hood. A cross-platform rewrite using ANSI escape sequences and termios is under consideration (see roadmap).

---

## 📚 API Highlights

| Capability        | Methods                                             |
|------------------|-----------------------------------------------------|
| Output           | `print()`, `println()` for string, int, float, etc. |
| Styling          | `txtBoldOn()`, `txtUnderlineOn()`, etc.             |
| Cursor           | `cursorMoveToPosition()`, `cursorMoveDownLines()`   |
| Input            | `input(str)`, `getNextChar()`, input styling flags  |
| Screen Control   | `screenClear()`, `screenResize()`, `titleSet()`     |
| Debugging        | `debugOn()`, `printerr()`                           |

---

## 🛣 Roadmap Ideas

- [ ] Linux/ANSI-compatible backend
- [ ] Stream-style `operator<<` bridge for power users
- [ ] Input validators and hints
- [ ] Embedded themes for styled CLI tools

---

## 🙌 Contributing & License

Coming soon! Planning to open-source this? Let’s wire up a `LICENSE.md`, contributor guidelines, and maybe even a demo project.

---

## 💬 Contact

Got feedback, suggestions, or want to contribute? Let’s connect.

---

Want me to tailor this more for an academic audience, potential contributors, or drop in actual code snippets from your library? Or would you like a second version with a less technical tone? We can flex this however you like.
