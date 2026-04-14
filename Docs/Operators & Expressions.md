<h1 align="center">Operators & Expressions</h1>

<p align="center">
  <img src="https://img.shields.io/badge/C++-Operators_&_Expressions-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Level-Beginner_Friendly-success?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Focus-Logic_&_Math-orange?style=for-the-badge" />
</p>

---

<h1 align="center">What Are Operators?</h1>

In C++, operators are not just the basic `+`, `-`, `*`, `/`, `%` like you'd see in Python or other languages. They go way deeper — from comparing values to controlling logic flow, to doing bit-level stuff that most beginners never touch. This is the **full breakdown**. For a fast-access overview, head back to the overview file.

> [!TIP]
> **My personal rule:** If your expression is getting long and confusing — just wrap parts of it in `()`. Always. Even if you know the precedence. Your future self will thank you.

---

<h1 align="center">Arithmetic Operators</h1>

The basics. These are the ones you already know from math class, just with a few C++ quirks that'll catch you off guard.

| Operator | What it does | Quick Example |
| :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-%2B-00599C?style=flat-square" /> | Addition — adds two values together | `5 + 3 = 8` |
| <img src="https://img.shields.io/badge/--minus--44CC11?style=flat-square" /> | Subtraction — subtracts one value from another | `10 - 4 = 6` |
| <img src="https://img.shields.io/badge/-%2A-orange?style=flat-square" /> | Multiplication — multiplies two numbers | `4 * 3 = 12` |
| <img src="https://img.shields.io/badge/-%2F-red?style=flat-square" /> | Division — divides (watch out for int division!) | `10 / 2 = 5` |
| <img src="https://img.shields.io/badge/-%25-9cf?style=flat-square" /> | Modulo — gives you the remainder after division | `10 % 3 = 1` |

> [!WARNING]
> `%` is NOT for percentage. `10 % 3` gives `1` (the leftover after dividing 10 by 3). Easy to mix up at first.

> [!TIP]
> Integer division in C++ **drops the decimal**: `7 / 2 = 3`, not `3.5`. Use `double` if you need the full result.

### Basic arithmetic in action:

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 10;
    int b = 3;

    cout << a + b << endl;
    cout << a - b << endl;
    cout << a * b << endl;
    cout << a / b << endl;
    cout << a % b << endl;
}
```

> **Output:**
> ```
> 13
> 7
> 30
> 3
> 1
> ```

### The int division trap — and how to fix it:

```cpp
#include <iostream>
using namespace std;

int main() {
    int a = 7;
    int b = 2;

    cout << a / b << endl;

    double c = 7;
    double d = 2;

    cout << c / d << endl;
}
```

> **Output:**
> ```
> 3
> 3.5
> ```

Notice the difference. The first division cuts off the decimal because both values are `int`. The second one gives you the real answer because we used `double`. This trips up beginners constantly.

### Real use-case — discount calculator:

```cpp
#include <iostream>
using namespace std;

int main() {
    double price = 149.99;
    double discountPercent = 20;
    double finalPrice = price - (price * (discountPercent / 100));
    cout << "Final price after discount: " << finalPrice << endl;
}
```

> **Output:** `Final price after discount: 119.992`

---

<h1 align="center">Comparison Operators</h1>

These always return a `bool` — either `true` or `false`. You'll use them constantly inside `if` statements and loops.

| Operator | Meaning | Example |
| :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-==-00599C?style=flat-square" /> | Equal to — checks if two values are the same | `5 == 5 → true` |
| <img src="https://img.shields.io/badge/-!=-red?style=flat-square" /> | Not equal to — true if values are different | `5 != 3 → true` |
| <img src="https://img.shields.io/badge/-%3C-orange?style=flat-square" /> | Less than | `3 < 7 → true` |
| <img src="https://img.shields.io/badge/-%3E-44CC11?style=flat-square" /> | Greater than | `9 > 4 → true` |
| <img src="https://img.shields.io/badge/-%3C=-9cf?style=flat-square" /> | Less than or equal to | `5 <= 5 → true` |
| <img src="https://img.shields.io/badge/-%3E=-blueviolet?style=flat-square" /> | Greater than or equal to | `6 >= 3 → true` |

> [!NOTE]
> `==` **compares** values. `=` **assigns** a value. Classic mistake — `if (x = 5)` sets x to 5 instead of checking it. The compiler won't always warn you either.

### Basic comparison example:

```cpp
#include <iostream>
using namespace std;

int main() {
    int age = 17;

    if (age >= 18) {
        cout << "You can enter." << endl;
    } else {
        cout << "You're too young." << endl;
    }
}
```

> **Output:** `You're too young.`

### Comparing with user input:

```cpp
#include <iostream>
using namespace std;

int main() {
    int score;
    cout << "Enter your score: ";
    cin >> score;

    if (score == 100) {
        cout << "Perfect score!" << endl;
    } else if (score >= 60) {
        cout << "You passed." << endl;
    } else {
        cout << "Try again." << endl;
    }
}
```

> **Output (example with 75):** `You passed.`

---

<h1 align="center">Logical Operators</h1>

Used to combine or flip boolean conditions. Super useful for building more complex `if` checks without nesting them forever.

| Operator | Meaning | Example |
| :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-&&-00599C?style=flat-square" /> | AND — both conditions must be true | `isConnected && hasApiKey` |
| <img src="https://img.shields.io/badge/-%7C%7C-orange?style=flat-square" /> | OR — at least one condition must be true | `isAdmin \|\| isOwner` |
| <img src="https://img.shields.io/badge/-!-red?style=flat-square" /> | NOT — flips true to false and the other way around | `!isMuted` |

### AND example — both must be true:

```cpp
#include <iostream>
using namespace std;

int main() {
    bool hasTicket = true;
    bool isOldEnough = true;

    if (hasTicket && isOldEnough) {
        cout << "Welcome to the event!" << endl;
    } else {
        cout << "Sorry, you can't enter." << endl;
    }
}
```

> **Output:** `Welcome to the event!`

### OR example — only one needs to be true:

```cpp
#include <iostream>
using namespace std;

int main() {
    bool isAdmin = false;
    bool isOwner = true;

    if (isAdmin || isOwner) {
        cout << "Access granted." << endl;
    } else {
        cout << "Access denied." << endl;
    }
}
```

> **Output:** `Access granted.`

### NOT example — flip the condition:

```cpp
#include <iostream>
using namespace std;

int main() {
    bool isMuted = false;

    if (!isMuted) {
        cout << "Mic is active." << endl;
    } else {
        cout << "You're muted." << endl;
    }
}
```

> **Output:** `Mic is active.`

### Real use-case — login check:

```cpp
#include <iostream>
using namespace std;

int main() {
    string username = "denys";
    string password = "1234";

    string inputUser;
    string inputPass;

    cout << "Username: ";
    cin >> inputUser;
    cout << "Password: ";
    cin >> inputPass;

    if (inputUser == username && inputPass == password) {
        cout << "Logged in!" << endl;
    } else {
        cout << "Wrong credentials." << endl;
    }
}
```

> **Output (example):** `Logged in!`

---

<h1 align="center">Assignment Operators</h1>

You already know `=`. But C++ has a bunch of shorthand versions that save you from writing repetitive stuff.

| Operator | What it does | Example | Same as |
| :--- | :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-=-00599C?style=flat-square" /> | Assigns a value | `x = 5` | — |
| <img src="https://img.shields.io/badge/-%2B=-44CC11?style=flat-square" /> | Adds and assigns | `x += 3` | `x = x + 3` |
| <img src="https://img.shields.io/badge/--equal-orange?style=flat-square" /> | Subtracts and assigns | `x -= 2` | `x = x - 2` |
| <img src="https://img.shields.io/badge/-%2A=-red?style=flat-square" /> | Multiplies and assigns | `x *= 4` | `x = x * 4` |
| <img src="https://img.shields.io/badge/-%2F=-9cf?style=flat-square" /> | Divides and assigns | `x /= 2` | `x = x / 2` |
| <img src="https://img.shields.io/badge/-%25=-blueviolet?style=flat-square" /> | Modulo and assigns | `x %= 3` | `x = x % 3` |

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 10;

    x += 5;
    cout << x << endl;

    x -= 3;
    cout << x << endl;

    x *= 2;
    cout << x << endl;

    x /= 4;
    cout << x << endl;

    x %= 3;
    cout << x << endl;
}
```

> **Output:**
> ```
> 15
> 12
> 24
> 6
> 0
> ```

---

<h1 align="center">Increment & Decrement</h1>

These are shorthand for adding or subtracting 1. You'll see them everywhere — especially in `for` loops.

| Operator | What it does | Example |
| :--- | :--- | :--- |
| <img src="https://img.shields.io/badge/-%2B%2B-00599C?style=flat-square" /> | Adds 1 to the variable | `x++` or `++x` |
| <img src="https://img.shields.io/badge/----red?style=flat-square" /> | Subtracts 1 from the variable | `x--` or `--x` |

> [!NOTE]
> `x++` (post-increment) returns the value *before* adding 1. `++x` (pre-increment) adds 1 *first*, then returns the value. In simple loops it doesn't matter — but if you're using it inside an expression, it does.

```cpp
#include <iostream>
using namespace std;

int main() {
    int x = 5;

    cout << x++ << endl;
    cout << x << endl;

    cout << ++x << endl;
    cout << x << endl;
}
```

> **Output:**
> ```
> 5
> 6
> 7
> 7
> ```

---

<h1 align="center">Operator Precedence</h1>

C++ evaluates operators in a specific order — like math rules (multiplication before addition). Here's the priority from highest to lowest:

```
!             ← evaluated first (NOT)
*  /  %       ← multiplication / division / modulo
+  -          ← addition / subtraction
<  >  <=  >=  ← comparisons
== !=         ← equality checks
&&            ← AND
||            ← OR
=  +=  -= ... ← assignment (evaluated last)
```

> [!TIP]
> When in doubt, just use parentheses `()` — they always override the default order and make your code way easier to read.

### Precedence in action — without parentheses:

```cpp
#include <iostream>
using namespace std;

int main() {
    bool result = 5 + 3 > 7 && 10 % 3 == 1;
    cout << result << endl;
}
```

> **Output:** `1` (which means `true`)

Here's how C++ actually read that:
1. `5 + 3` → `8`
2. `10 % 3` → `1`
3. `8 > 7` → `true`
4. `1 == 1` → `true`
5. `true && true` → `true`

### Same thing but with parentheses — way more readable:

```cpp
#include <iostream>
using namespace std;

int main() {
    bool result = ((5 + 3) > 7) && ((10 % 3) == 1);
    cout << result << endl;
}
```

> **Output:** `1`

Same result, but now you can actually read what's happening without thinking about it.

---

<h1 align="center">Expressions — Putting It All Together</h1>

An expression is any combination of values, variables, operators that produces a result. Everything from `5 + 3` to a full `if` condition is an expression.

### Complex expression example — temperature checker:

```cpp
#include <iostream>
using namespace std;

int main() {
    double temp;
    cout << "Enter temperature in Celsius: ";
    cin >> temp;

    bool isFreezing = temp <= 0;
    bool isHot = temp >= 35;
    bool isComfortable = temp > 15 && temp < 30;

    if (isFreezing) {
        cout << "It's freezing outside." << endl;
    } else if (isHot) {
        cout << "It's really hot today." << endl;
    } else if (isComfortable) {
        cout << "Nice weather!" << endl;
    } else {
        cout << "Somewhere in between." << endl;
    }
}
```

> **Output (example with 22):** `Nice weather!`

### Expression in a loop — FizzBuzz (classic):

```cpp
#include <iostream>
using namespace std;

int main() {
    for (int i = 1; i <= 20; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            cout << "FizzBuzz" << endl;
        } else if (i % 3 == 0) {
            cout << "Fizz" << endl;
        } else if (i % 5 == 0) {
            cout << "Buzz" << endl;
        } else {
            cout << i << endl;
        }
    }
}
```

> **Output:** 1, 2, Fizz, 4, Buzz, Fizz, 7, 8, Fizz, Buzz, 11, Fizz, 13, 14, FizzBuzz, 16, 17, Fizz, 19, Buzz

This one actually uses `%`, `==`, `&&` all together in real logic. Good example of everything combined.

---

<h1 align="center">Quick Reference Cheat Sheet</h1>

| Category | Operators |
| :--- | :--- |
| Arithmetic | `+` `-` `*` `/` `%` |
| Comparison | `==` `!=` `<` `>` `<=` `>=` |
| Logical | `&&` `\|\|` `!` |
| Assignment | `=` `+=` `-=` `*=` `/=` `%=` |
| Increment / Decrement | `++` `--` |

> [!NOTE]
> This doc covers the operators you'll use 99% of the time. There are also bitwise operators (`&`, `|`, `^`, `~`, `<<`, `>>`) but those are advanced territory — separate doc for that.

---

<p align="center">
  <img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png" width="100%" />
</p>

<p align="center">
  <b>Written by Denys</b> · Part of the <a href="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase">C++ Knowledge Base</a><br>
  Copyright © 2026
</p>
