# 🚀 C++ Knowledge Base: Variable Types & Memory Management 🧠

<p align="center">
  <img src="https://media.giphy.com/media/v1.Y2lkPTc5MGI3NjExNHJueXByeHpsZnd4ZzJueHpsZnd4ZzJueHpsZnd4ZzJueHpsZnd4ZyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Qss0AsBCpSUT8E9ZGV/giphy.gif" width="300">
</p>

---

## 🛠 1. Взаимодействие с пользователем (`Strings` & `Input`) 💬
Используется для получения текстовой информации. Это база любого интерфейса, от чат-ботов до систем ввода в **ElevenLabs**.

### 💻 Чистый код для теста:
```cpp
#include <iostream>
#include <string>

using namespace std;

int main() {
    string name;
    cout << "Enter your name: ";
    cin >> name;
    cout << "your name is: " << name << endl;
}
