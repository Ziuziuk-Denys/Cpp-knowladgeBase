<p align="center">
  <img src="https://img.shields.io/badge/C++-Loops-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
</p>

---

<h1 align="center">Loops in C++</h1>

Yo guys! Loops are super cool. They let your code repeat the same thing many times without copying the same lines again and again. I use them all the time for audio stuff, lists, counting and games. Without loops programming would be boring as hell.

This is the **full version** with lots of examples. For the short quick version check the main [README.md](../README.md).

---

<h1 align="center">Main Types of Loops</h1>

| Loop Type | When to use | Quick Look |
|-----------|-------------|------------|
| <img src="https://img.shields.io/badge/-for-00599C?style=flat-square" /> | When you know exactly how many times to repeat | Best for counting |
| <img src="https://img.shields.io/badge/-while-orange?style=flat-square" /> | When you don't know how many times, just keep going while something is true | Good for waiting |
| <img src="https://img.shields.io/badge/-do--while-red?style=flat-square" /> | Same as while but runs at least once | Useful for menus |

---

<h1 align="center">1. For Loop</h1>

This is my favorite one. Perfect when you know the exact number of repeats.

```cpp
#include <iostream>

int main() {
    for (int i = 0; i < 5; i++) {      // start at 0, go while i < 5, add 1 each time
        std::cout << "Count: " << i << std::endl;
    }
    return 0;
}
```

**Output:**
```
Count: 0
Count: 1
Count: 2
Count: 3
Count: 4
```

> [!TIP]
> You can count backwards: `for (int i = 10; i >= 0; i--)`

> [!TIP]
> Change step with `i += 2` or `i--`

---

<h1 align="center">2. While Loop</h1>

Keeps running as long as the condition is true.

```cpp
#include <iostream>

int main() {
    int lives = 3;

    while (lives > 0) {
        std::cout << "You have " << lives << " lives left!" << std::endl;
        lives--;                       // don't forget to change something!
    }

    std::cout << "Game Over!" << std::endl;
    return 0;
}
```

> [!WARNING]
> If you forget to change the condition you get an **infinite loop** and your program freezes. Be careful!

---

<h1 align="center">3. Do-While Loop</h1>

This one always runs at least once, even if the condition is false at the start.

```cpp
#include <iostream>

int main() {
    int number;

    do {
        std::cout << "Enter a positive number: ";
        std::cin >> number;
        std::cout << "You entered: " << number << std::endl;
    } while (number > 0);

    std::cout << "Goodbye!" << std::endl;
    return 0;
}
```

Good for asking the user something at least one time.

---

<h1 align="center">break and continue</h1>

- `break;` → jumps out of the loop completely
- `continue;` → skips the rest of this turn and goes to the next one

```cpp
for (int i = 0; i < 10; i++) {
    if (i == 3) continue;   // skip 3
    if (i == 7) break;      // stop at 7

    std::cout << i << " ";
}
// Output: 0 1 2 4 5 6
```

---

<h1 align="center">Range-based For Loop (Modern C++)</h1>

Super easy way to go through vectors and arrays:

```cpp
#include <iostream>
#include <vector>

int main() {
    std::vector<int> numbers = {10, 20, 30, 40, 50};

    for (int num : numbers) {
        std::cout << num << " ";
    }

    // If you want to change the numbers use reference:
    for (int& num : numbers) {
        num *= 2;
    }
    return 0;
}
```

---

<h1 align="center">My Tips</h1>

- Use `size_t` for loop counters when working with `.size()` of vectors.
- Nested loops (loop inside loop) are powerful but can make your program slow if you're not careful.
- I often use `for` loops to process audio samples one by one.
- Always think: "What if this loop never stops?"

For more examples with vectors and audio stuff check other files in Docs.

---

<p align="center">
  <img src="https://raw.githubusercontent.com/andreasbm/readme/master/assets/lines/aqua.png" width="100%" />
</p>

<p align="center">
  <b>Made by Denys </b><br>
  Back to main <a href="../README.md">README.md</a>
</p>
