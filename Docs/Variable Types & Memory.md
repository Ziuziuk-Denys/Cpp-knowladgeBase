<h1 align="center">🧠 Variable Types & Memory</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C++-Variables_&_Types-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Level-Beginner_Friendly-success?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Focus-Memory_Optimization-blueviolet?style=for-the-badge" />
</p>

---

<h1 align="center">💡 What Are Variables?</h1>

A variable is basically a **named box in memory** that holds some value while your program runs. The *type* of that box tells C++ how much memory to allocate and how to interpret the bits stored inside.

Picking the wrong type won't always crash your program — but it *will* waste memory, slow things down, or cause weird bugs you won't see coming. So this stuff actually matters.

> [!TIP]
> **My personal rule:** Think about what kind of data you're storing *before* you write the variable. It saves you refactoring pain later.

---

<h1 align="center">🗂️ Core Types at a Glance</h1>

| Type | What it stores | Real-world Use Case |
| :--- | :--- | :--- |
| <img src="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Assets/int.png?raw=true" height="22"/> | **Integers** (whole numbers) | Loop counters, User IDs, request counts |
| <img src="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Assets/double.png?raw=true" height="22"/> | **Fractions** (floating-point) | Prices, audio amplitudes, neural net weights |
| <img src="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Assets/string.png?raw=true" height="22"/> | **Text** | Names, API keys, JSON payloads |
| <img src="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Assets/bool.png?raw=true" height="22"/> | **Logic** (true / false) | `isMicActive`, `isConnected`, `hasPaid` |
| <img src="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Assets/size_t.png?raw=true" height="22"/> | **Positive integers** | Safe loop indexing, `.size()` on vectors |

---

<h1 align="center">🔢 `int` — Whole Numbers</h1>

The most basic type. Perfect for counting things, loop variables, and any value that will never be a fraction.

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 0;
    for (int i = 1; i <= 10; i++) {
        x += 1;
        cout << x << endl;
    }
}
```

> **Output:** prints 1 through 10, each on a new line.

**Memory:** 4 bytes. **Range:** −2,147,483,648 to 2,147,483,647.

---

<h1 align="center">💰 `double` — Decimal Numbers</h1>

Use `double` whenever you need precision — prices, scientific calculations, audio signal amplitudes, anything with a decimal point.

```cpp
#include <iostream>
using namespace std;

int main() {
    double price = 99.99;
    double sale = 5;
    double priceWithSale = price - (price * (sale / 100));
    cout << "Price with sale will be: " << priceWithSale << endl;
}
```

> **Output:** `Price with sale will be: 94.9905`

**Memory:** 8 bytes. Way more precise than `float` — I always default to `double` unless memory is a serious concern.

### Real use-case with `double` in audio:

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<double> audioData = {0.1, 0.002, 0.8, 0.0001, 0.5};
    for (size_t i = 0; i < audioData.size(); i++) {
        if (audioData[i] < 0.01) {
            cout << "Silence detected at index: " << i << endl;
        }
    }
}
```

> **Output:** `Silence detected at index: 1` and `Silence detected at index: 3`

Notice I used `size_t` for the loop index — that's intentional (see below).

---

<h1 align="center">📝 `string` — Text</h1>

For anything text-based. `string` in C++ is part of the standard library, so you get a ton of built-in methods for free.

```cpp
#include <iostream>
using namespace std;

int main() {
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "your name is: " << name << endl;
}
```

> **Output (example):** `your name is: Denys`

**Important:** `string` is not a primitive type — it's an object, which means it manages its own memory dynamically. Don't stress about that for now, just know it's safe to use.

---

<h1 align="center">✅ `bool` — True or False</h1>

`bool` only holds two values: `true` or `false`. It's 1 byte in memory even though it only *needs* 1 bit — that's just how C++ handles alignment.

```cpp
#include <iostream>
using namespace std;

int main() {
    bool isRaining = true;
    if (isRaining) {
        cout << "It's raining outside. Don't forget to take an umbrella!" << endl;
    } else {
        cout << "It's not raining outside. Enjoy the sunshine!" << endl;
    }
}
```

> **Output:** `It's raining outside. Don't forget to take an umbrella!`

I use `bool` constantly for state flags — things like `isMicActive`, `isServerConnected`, or `hasPaid`. It makes your `if` conditions way more readable than comparing integers.

---

<h1 align="center">📏 `size_t` — Safe Indexing</h1>

`size_t` is an **unsigned integer** type, specifically designed for sizes and indices. You get it automatically when you use `.size()` on a container, and it's the "correct" type to use in loops over vectors or arrays.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<double> audioData = {0.1, 0.002, 0.8, 0.0001, 0.5};
    for (size_t i = 0; i < audioData.size(); i++) {
        if (audioData[i] < 0.01) {
            cout << "Silence detected at index: " << i << endl;
        }
    }
}
```

**Why not just use `int`?** If you mix a signed `int` with `.size()` (which returns `size_t`), you get compiler warnings about comparing signed and unsigned values. `size_t` keeps everything consistent and safe.

---

<h1 align="center">⚡ Advanced: `short` — Memory Saver</h1>

`short` is a 16-bit integer. That's half the size of `int`. When you're dealing with **millions** of small values — like raw audio samples in a buffer — this actually matters.

**Range:** −32,768 to 32,767
**Memory:** 2 bytes (vs 4 bytes for `int`)

```cpp
short rawSample = 24000; // a valid 16-bit audio sample value
```

---

<h1 align="center">🔒 The `const` Modifier</h1>

If a value is never going to change, mark it as `const`. The compiler will stop you from accidentally overwriting it, and it's a clear signal to anyone reading your code.

```cpp
const double HOURLY_RATE = 15.0;
const double PI = 3.14159265358979;
```

I use `const` for anything that's a fixed config value — API endpoints, math constants, thresholds. It's a tiny thing that makes your code much more intentional.

---

<h1 align="center">🧮 Memory Size Cheat Sheet</h1>

| Type | Size | Range (approximate) |
| :--- | :--- | :--- |
| `bool` | 1 byte | true / false |
| `short` | 2 bytes | ±32K |
| `int` | 4 bytes | ±2.1 billion |
| `size_t` | 4 or 8 bytes | 0 to max positive |
| `double` | 8 bytes | ±1.7 × 10³⁰⁸ |
| `string` | dynamic | as long as you need |

> [!NOTE]
> `size_t` is 4 bytes on 32-bit systems and 8 bytes on 64-bit systems. Modern machines are almost always 64-bit, so expect 8 bytes.

---

<p align="center">
  <img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png" width="100%" />
</p>

<p align="center">
  <b>Written by Denys</b> · Part of the <a href="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase">C++ Knowledge Base</a><br>
  Copyright © 2026
</p>
