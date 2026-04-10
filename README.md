<p align="center">
  <img src="https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Assets/welcome_banner.gif?raw=true" width="100%" alt="Welcome Banner" />
</p>

<p align="center">
  <img src="https://img.shields.io/badge/C++-Learning_Path-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white" />
  <img src="https://img.shields.io/badge/Status-Active-success?style=for-the-badge" />
  <img src="https://img.shields.io/badge/Focus-AI%20&%20Audio-blueviolet?style=for-the-badge" />
</p>

---

## 💫 Introduction

Hello everyone! This repository is a curated space created to **store my C++ knowledge**, document my projects, and organize technical insights. I'm building this as a personal wiki and a showcase of my journey into high-performance computing and AI.

---

## 🗺️ Navigation Hub

<div align="center">

| Section | Description | Quick Link |
| :--- | :--- | :--- |
| 🚀 **Projects** | Practical implementations and experiments. | [**Browse Code**](https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/tree/main/Projects) |
| 📖 **Docs** | Deep dives into sub-topics and theory. | [**Study Notes**](https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/blob/main/Docs/) |
| 📂 **Assets** | Media, diagrams, and visual references. | [**Media Gallery**](https://github.com/Ziuziuk-Denys/Cpp-knowladgeBase/tree/main/Assets) |

</div>

---

## 📝 Learning Log & Quick Access

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

## 🎨 Visual Assets Showcase

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

## 🔬 Advanced Optimization Tips

### ⚡ The `short` type
Contrary to popular belief, `short` is a **16-bit integer**. 
* **Use case:** When you need to store millions of small numbers (like raw 16-bit audio samples) and want to save 50% of memory compared to a standard `int`.
* **Range:** -32,768 to 32,767.

### 🛡️ The `const` Modifier
If a value is not going to change (like a fixed API endpoint or a math constant), always mark it as `const`. 
```cpp
const double HOURLY_RATE = 15.0; // Locked value
