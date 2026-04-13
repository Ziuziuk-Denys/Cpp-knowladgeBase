<p align="center">
  <img src="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Assets/welcome_banner.gif?raw=true" width="100%" alt="Welcome Banner" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-Learning_Path-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Status-Active-success?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Focus-AI%20&%20Audio-blueviolet?style=for-the-badge" />
</p>

---

<h1 align="center">Introduction</h1>

Hello everyone! This repository is a curated space created to **store my C++ knowledge**, document my projects, and organize technical insights. I'm building this as a personal wiki and a showcase of my journey into high-performance computing and AI.

---

<h1 align="center">Navigation Hub</h1>

<div align="center">

| Section | Description | Quick Link |
| :--- | :--- | :--- |
| **Projects** | Practical implementations and experiments. | [**Browse Code**](https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/tree/main/Projects) |
| **Docs** | Deep dives into sub-topics and theory. | [**Study Notes**](https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Docs/) |
| **Assets** | Media, diagrams, and visual references. | [**Media Gallery**](https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/tree/main/Assets) |

</div>

---

<h1 align="center">Learning Log & Quick Access</h1>

In this main **README.md**, I consolidate my core findings. Think of this as a **fast-access tool** for me and my visitors. For more accurate, detailed knowledge, head over to the [Docs](https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Docs/) section.

> [!TIP]
> **Current Focus:** Mastering memory management (Pointers & References) to optimize real-time audio processing.

---

<h1 align="center">Tech Stack & Tools</h1>

<p align="center">
  <a href="https://skillicons.dev">
    <img src="https://skillicons.dev/icons?i=cpp,visualstudio,clion,github,git,windows,cmake" />
  </a>
</p>

---

<h1 align="center">Visual Assets Showcase</h1>

<p align="center">
  <img src="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Assets/code_preview.gif?raw=true" width="600" alt="Code Preview" />
</p>

---

<p align="center">
  <img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png" width="100%" />
</p>

<p align="center">
  <img src="https://komarev.com/ghpvc/?username=Ziuziuk-Denys&color=00599C&style=flat-square&label=PROFILE+VIEWS" />
</p>

<p align="center">
  <b>Developed with precision by Denys</b><br>
  Copyright © 2026
</p>

---

<h1 align="center">Variable Types & Memory</h1>

In C++, variables are not just containers; they are tools for optimization. Choosing the right type can significantly **speed up your program** and **reduce memory consumption**.

---

<h1 align="center">Core Data Types</h1>

| Type | What it stores | Real-world Use Case |
| :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-int-00599C?style=flat-square" /> | **Integers** (whole numbers) | Request counters, User IDs, loop counts. |
| <img src="https://img.shields.io/badge/-double-44CC11?style=flat-square" /> | **Fractions** (floating point) | Prices, audio amplitudes, neural network weights. |
| <img src="https://img.shields.io/badge/-string-orange?style=flat-square" /> | **Text** | Client names, API keys, JSON payloads. |
| <img src="https://img.shields.io/badge/-bool-red?style=flat-square" /> | **Logic** (True/False) | `isMicActive`, `isServerConnected`, `hasPaid`. |
| <img src="https://img.shields.io/badge/-size__t-9cf?style=flat-square" /> | **Positive Integers** | Safe indexing in loops, vector sizes (`.size()`). |

---

<h1 align="center">Advanced Optimization Tips</h1>

### The `short` type
Contrary to popular belief, `short` is a **16-bit integer**. 
* **Use case:** When you need to store millions of small numbers (like raw 16-bit audio samples) and want to save 50% of memory compared to a standard `int`.
* **Range:** -32,768 to 32,767.

### The `const` Modifier
If a value is not going to change (like a fixed API endpoint or a math constant), always mark it as `const`. 
```cpp
const double HOURLY_RATE = 15.0; // Locked value
```



---

<h1 align="center">Operators & Expressions</h1>

In C++, operators are not just the basic `+, -, *, /, %` like you'd see in Python or other languages. They go way deeper - from comparing values to controlling logic flow. This is a **fast-access overview**. For full breakdowns with examples, head to the [Docs](https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Docs/).

---

<h1 align="center">Arithmetic Operators</h1>

| Operator | What it does | Quick Example |
| :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-%2B-00599C?style=flat-square" /> | **Addition** - adds two values together, works on numbers and strings | `5 + 3 = 8` |
| <img src="https://img.shields.io/badge/--minus--44CC11?style=flat-square" /> | **Subtraction** - subtracts one value from another | `10 - 4 = 6` |
| <img src="https://img.shields.io/badge/-%2A-orange?style=flat-square" /> | **Multiplication** - multiplies two numbers | `4 * 3 = 12` |
| <img src="https://img.shields.io/badge/-%2F-red?style=flat-square" /> | **Division** - divides one number by another (watch out for int division!) | `10 / 2 = 5` |
| <img src="https://img.shields.io/badge/-%25-9cf?style=flat-square" /> | **Modulo** - gives you the **remainder** after division, not a percentage | `10 % 3 = 1` |

> [!WARNING]
> `%` is **NOT** for percentage. `10 % 3` gives `1` (the leftover after dividing 10 by 3). Easy to mix up at first.

> [!TIP]
> Integer division in C++ drops the decimal: `7 / 2 = 3`, not `3.5`. Use `double` if you need the full result.

---

<h1 align="center">Comparison Operators</h1>

These always return a `bool` - either `true` or `false`. Used a lot inside `if` statements and loops.

| Operator | Meaning | Example |
| :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-==-00599C?style=flat-square" /> | **Equal to** - checks if two values are the same | `5 == 5` → `true` |
| <img src="https://img.shields.io/badge/-!=-red?style=flat-square" /> | **Not equal to** - true if values are different | `5 != 3` → `true` |
| <img src="https://img.shields.io/badge/-%3C-orange?style=flat-square" /> | **Less than** | `3 < 7` → `true` |
| <img src="https://img.shields.io/badge/-%3E-44CC11?style=flat-square" /> | **Greater than** | `9 > 4` → `true` |
| <img src="https://img.shields.io/badge/-%3C=-9cf?style=flat-square" /> | **Less than or equal to** | `5 <= 5` → `true` |
| <img src="https://img.shields.io/badge/-%3E=-blueviolet?style=flat-square" /> | **Greater than or equal to** | `6 >= 3` → `true` |

> [!NOTE]
> `==` compares values. `=` assigns a value. Classic mistake - `if (x = 5)` sets x to 5 instead of checking it.

---

<h1 align="center">Logical Operators</h1>

Used to combine or flip boolean conditions. Super useful for building more complex `if` checks.

| Operator | Meaning | Example |
| :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-&&-00599C?style=flat-square" /> | **AND** - both conditions must be true | `isConnected && hasApiKey` |
| <img src="https://img.shields.io/badge/-%7C%7C-orange?style=flat-square" /> | **OR** - at least one condition must be true | `isAdmin \|\| isOwner` |
| <img src="https://img.shields.io/badge/-!-red?style=flat-square" /> | **NOT** - flips `true` to `false` and the other way around | `!isMuted` |

---

<h1 align="center">Operator Precedence</h1>

C++ evaluates operators in a specific order - like math rules (multiplication before addition). Here's the rough priority from **highest to lowest**:

```
!  (NOT)            ← evaluated first
*  /  %             ← then multiplication/division/modulo
+  -                ← then addition/subtraction
<  >  <=  >=        ← then comparisons
== !=               ← then equality checks
&&                  ← then AND
||                  ← then OR
```

> [!TIP]
> When in doubt, just use parentheses `()` - they always override the default order and make your code easier to read anyway.

---
