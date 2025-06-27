# <h1 align = "center">EndGame - The Loop Place</h1>

<p align = "center">
  <a href = "https://campus.kpi.kharkov.ua/ua/">
    <img src = "https://i.imghippo.com/files/zjSc9678aE.png" alt = "Innovation Campus" width = "300" height = "300">
  </a>
  <br>
  <h2 align = "center"><strong>Innovation Campus | EndGame Project | 2023-2024</strong></h2>
</p>

<div align = "center">
  <img src = "https://i.imghippo.com/files/xxW3908Prw.png" alt = "SDL2" width = "80" height = "80">
  <br>
  <img src = "https://img.shields.io/badge/SDL2-Powered-blue?style=for-the-badge&logo=c" alt = "SDL2 Powered">
  <img src = "https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c" alt = "C Language">
  <img src = "https://img.shields.io/badge/Platform-Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black" alt = "Linux">
</div>

## 🌐 Available Languages / Verfügbare Sprachen / Доступні мови

<div align="center">
  
[🇺🇦 **Українська**](#українська-) | [🇬🇧 **English**](#english-) | [🇩🇪 **Deutsch**](#deutsch-)

</div>

### 🎮 Gameplay Preview

<div align = "center">
  
**🎬 Gameplay Video**

[📽️ Watch Game gameplay (no sound)](https://github.com/user-attachments/assets/62bf191f-57e5-4630-8f3b-5b96f7579424)

[🔊 Watch with sound on YouTube](https://youtu.be/Ynthj9Q90OY?si=rGc8KWwqgyggVEb7)

---

*🎮 Full gameplay demo of The Loop Place*

</div>

---

<details open>
  <summary>Українська 🇺🇦</summary>

<span style = "margin-top: 5px;"></span>

> ⚠️ **УВАГА:**
>
> Цей репозиторій містить нашу реалізацію гри з детекцією аномалій, розроблену командою з 5 осіб в рамках EndGame проекту Innovation Campus 2023-2024.  
> Гра створена на чистому C з використанням SDL2 бібліотеки для графіки, звуку та вводу.
>
> **Інноваційний геймплей** — знаходьте аномалії у звичайному середовищі та виживайте!

---

### 🎮 Про гру

**The Loop Place** — це захоплююча хорор-головоломка, де гравець повинен виявляти аномалії в повсякденному середовищі різних локацій. Досліджуйте школу, лікарню, бібліотеку та інші місця, кожне з яких має кілька поверхів. Гра поєднує атмосферу напруги з елементами детективного розслідування та логічного мислення.

### Цілі гри

1. **Шукай аномалії** — Ретельно досліджуй кожен поверх різних локацій
2. **Взаємодій з об'єктами** — Перевіряй підозрілі предмети натисканням миші
3. **Завжди стеж за тим, щоб об'єкт був "реальним"** — Виявляй підроблені або змінені об'єкти

### Ігрова механіка

**Структура локацій:**
- **Перші 5 поверхів** — безкоштовні для гравця  
- **Усього 10 поверхів** — повна версія гри
- **Різні локації** — школи, лікарні, бібліотеки та інші місця
- **Випадкові аномалії** — не на кожному поверсі є аномалії

**Що таке аномалії?**
Аномалії — це об'єкти з неправильними характеристиками:
- **Неправильна анімація** (наприклад, reverse анімація)
- **Неправильний розмір** об'єкта
- **Змінені текстури** або кольори
- **Незвичайна поведінка** при взаємодії

**Система детекції:**
- **ЛКМ** — Додати аномалію до списку
- **ПКМ** — Видалити об'єкт зі списку аномалій
- **Список у лівому верхньому куті** — Показує всі знайдені аномалії

**Ліфт та прогресія:**
- **Ліфт** — ключовий об'єкт в кінці кожної локації
- **Кнопка вниз** — якщо на поверсі БУЛИ аномалії
- **Кнопка вгору** — якщо на поверсі НЕ БУЛО аномалій
- **Правильний вибір** — запорука успішного проходження

### Основні особливості

- **Атмосферний саундтрек** з підтримкою SDL2_mixer
- **Високоякісна графіка** завдяки SDL2_image
- **Інтуїтивне керування** та плавна анімація спрайтів  
- **Динамічна система детекції аномалій**
- **Різноманітні візуальні ефекти** включаючи glitch та noise ефекти
- **Адаптивний інтерфейс** з підтримкою різних розширень

### Ігровий процес

**The Loop Place** — це розумова хорор-головоломка, де точність спостереження визначає ваш успіх:

**Мета:** Дослідити різні локації та виявити всі аномальні об'єкти, використовуючи:
- **Спостережливість** для виявлення неправильних анімацій та текстур
- **Логічне мислення** для аналізу поведінки об'єктів  
- **Швидкі рефлекси** для точної взаємодії з об'єктами

**Особливості геймплею:**
- Детальне дослідження кожного об'єкта на поверсі
- Ведення списку знайдених аномалій
- Розпізнавання підроблених елементів середовища
- Прийняття рішень про напрямок руху в ліфті

---

### 🛠️ Встановлення та запуск

#### Системні вимоги
- **ОС**: Linux (Ubuntu/Debian рекомендовано)
- **Компілятор**: GCC або Clang
- **Залежності**: SDL2, SDL2_image, SDL2_mixer, SDL2_ttf

#### Крок 1: Встановлення залежностей

```bash
# SDL2 основна бібліотека
sudo apt install libsdl2-dev libsdl2-2.0-0 -y

# SDL2_image для роботи з зображеннями
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y

# SDL2_mixer для аудіо
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y

# SDL2_ttf для шрифтів
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y
```

#### Крок 2: Клонування та збірка

```bash
# Клонування репозиторію
git clone https://github.com/lavanios/gameSDL.git
cd gameSDL

# Збірка проекту
make

# Запуск гри
./endgame
```

#### Альтернативний спосіб компіляції

```bash
gcc -std=c11 -g src/*.c -o endgame \
    -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf \
    `sdl2-config --cflags --libs`
```

---

### ⚙️ Налаштування розробницького середовища

#### Git конфігурація

```bash
# Встановити ім'я користувача та email
git config --global user.email "your.email@example.com"
git config --global user.name "YourUsername"
```

#### Клонування з автентифікацією

```bash
# Клонування репозиторію (замініть <username> на ваш GitHub username)
git clone https://<username>:YOUR_TOKEN@github.com/lavanios/gameSDL.git
cd gameSDL
```

#### VSCode Tasks конфігурація

Створіть файл `.vscode/tasks.json` у корені проекту:

```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc збірка проєкту",
            "command": "/usr/bin/gcc",
            "args": [
                "-std=c11",
                "-fdiagnostics-color=always",
                "-g",
                "src/*.c",
                "-o",
                "endgame",
                "-lSDL2",
                "-lSDL2_mixer",
                "-lSDL2_image",
                "-lSDL2_ttf",
                "`sdl2-config --cflags --libs`"
            ],
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Збірка The Loop Place проєкту"
        }
    ],
    "version": "2.0.0"
}
```

#### Налаштування VSCode

1. Відкрийте папку проекту у VSCode
2. Встановіть розширення **C/C++** від Microsoft
3. Для збірки використовуйте `Ctrl + Shift + P` → "Tasks: Run Build Task"

#### Виправлення Git проблем

```bash
# Якщо виникають проблеми з кешуванням Git
git rm -r --cached .
git add .
git commit -m "Fix git cache issues"
```

---

### 🎮 Керування

| Клавіша/Миша | Дія |
|--------------|-----|
| `A D` | Переміщення персонажа ліворуч/праворуч |
| `ЛКМ` | Додати аномалію до списку |
| `ПКМ` | Видалити об'єкт зі списку аномалій |
| `Mouse` | Взаємодія з об'єктами та перевірка |

### 🎯 Стратегія проходження

1. **Дослідження поверху:**
   - Ретельно оглядайте кожен об'єкт
   - Звертайте увагу на анімації та текстури
   - Взаємодійте з підозрілими предметами

2. **Управління списком аномалій:**
   - Використовуйте ЛКМ для додавання аномалій
   - ПКМ допоможе виправити помилки
   - Слідкуйте за списком у лівому верхньому куті

3. **Завершення поверху:**
   - Йдіть до ліфта в кінці локації
   - ⬇️ Натисніть "вниз" якщо знайшли аномалії
   - ⬆️ Натисніть "вгору" якщо поверх чистий

---

### 📁 Структура проекту

```
gameSDL/
├── src/                    # Вихідний код
│   ├── main.c             # Головний файл гри
│   ├── init.c             # Ініціалізація SDL
│   ├── music.c            # Аудіо система
│   ├── loadTexture.c      # Завантаження текстур
│   ├── animateSpriteAAA.c # Анімація спрайтів
│   ├── renderGlitch.c     # Візуальні ефекти
│   └── ...                # Інші модулі
├── inc/                   # Заголовні файли
│   └── Header.h           # Основний header
├── resources/             # Ресурси гри
│   ├── png/              # Графічні ресурси
│   ├── songs/            # Аудіо файли
│   ├── font/             # Шрифти
│   └── button/           # UI елементи
├── Makefile              # Система збірки
└── README.md             # Документація
```

---

### 👥 Команда Floppa Team

<div align = "center">
  <table>
    <tr>
      <th align = "center">🎯 Роль</th>
      <th align = "center">👤 Учасник</th>
      <th align = "center">📝 GitHub</th>
      <th align = "center">💡 Внесок</th>
    </tr>
    <tr>
      <td align = "center"><strong>Team Lead & Coder</strong></td>
      <td align = "center">Volodymyr Nevmyrych</td>
      <td align = "center"><a href = "https://github.com/THESAULGOODMAN">TheSaulGoodman</a></td>
      <td align = "center">Керівництво проектом, архітектура коду</td>
    </tr>
    <tr>
      <td align = "center"><strong>Main Coder</strong></td>
      <td align = "center">Danylo Lavunov</td>
      <td align = "center"><a href = "https://github.com/lavanios">lavanios</a></td>
      <td align = "center">Основна розробка, ігрова логіка</td>
    </tr>
    <tr>
      <td align = "center"><strong>Main Designer</strong></td>
      <td align = "center">Maksym Kopychko</td>
      <td align = "center"><a href = "https://github.com/Archie242">Archie242</a></td>
      <td align = "center">Дизайн, графіка, допомога в коді</td>
    </tr>
    <tr>
      <td align = "center"><strong>Designer</strong></td>
      <td align = "center">Yaroslav Fedun</td>
      <td align = "center"><a href = "https://github.com/Blumex7">Blum</a></td>
      <td align = "center">UI/UX дизайн, візуальні ефекти</td>
    </tr>
    <tr>
      <td align = "center"><strong>Sound Designer</strong></td>
      <td align = "center">Vladyslav Oryshchuk</td>
      <td align = "center"><a href = "">buymeprada</a></td>
      <td align = "center">Аудіо дизайн, саундтрек</td>
    </tr>
  </table>
</div>

---

### 🔧 Використані технології

<div align = "center">
  <table>
    <tr>
      <td align = "center"><h4>🧰 Мови</h4></td>
      <td align = "center"><h4>📚 Бібліотеки</h4></td>
      <td align = "center"><h4>🔨 Інструменти збірки</h4></td>
      <td align = "center"><h4>🛠️ Розробка</h4></td>
      <td align = "center"><h4>💻 Платформи</h4></td>
    </tr>
    <tr>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://skillicons.dev/icons?i=c" alt = "C" width = "60" height = "60">
          <br><strong>C</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://i.imghippo.com/files/xxW3908Prw.png" alt = "SDL2" width = "60" height = "60">
          <br><strong>SDL2</strong>
        </p>
        <p>
          <img src = "https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" alt = "SDL2 Extensions" width = "40" height = "40">
          <br><strong>SDL2_image</strong>
          <br><strong>SDL2_mixer</strong>
          <br><strong>SDL2_ttf</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://upload.wikimedia.org/wikipedia/commons/2/22/Heckert_GNU_white.svg" alt = "Make" width = "50" height = "50">
          <br><strong>GNU Make</strong>
        </p>
        <p>
          <img src = "https://cdn.jsdelivr.net/gh/devicons/devicon/icons/gcc/gcc-original.svg" alt = "GCC" width = "60" height = "60">
          <br><strong>GCC</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://skillicons.dev/icons?i=git" alt = "Git" width = "60" height = "60">
          <br><strong>Git</strong>
        </p>
        <p>
          <img src = "https://skillicons.dev/icons?i=vscode" alt = "VSCode" width = "60" height = "60">
          <br><strong>VSCode</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://skillicons.dev/icons?i=linux" alt = "Linux" width = "60" height = "60">
          <br><strong>Linux</strong>
        </p>
        <p>
          <img src = "https://skillicons.dev/icons?i=github" alt = "GitHub" width = "60" height = "60">
          <br><strong>GitHub</strong>
        </p>
      </td>
    </tr>
  </table>
  
  <div style = "margin-top: 20px;">
    <h4>🚀 Технологічний стек</h4>
    <img src = "https://img.shields.io/badge/C-Standard-blue?style=flat-square&logo=c" alt = "C">
    <img src = "https://img.shields.io/badge/SDL2-2.0+-green?style=flat-square" alt = "SDL2">
    <img src = "https://img.shields.io/badge/Build-Make-orange?style=flat-square" alt = "Make">
    <img src = "https://img.shields.io/badge/Compiler-GCC-red?style=flat-square&logo=gnu" alt = "GCC">
    <img src = "https://img.shields.io/badge/Platform-Linux-yellow?style=flat-square&logo=linux" alt = "Linux">
  </div>
  
  <div style = "margin-top: 15px;">
    <p><i>🎯 Створено з використанням сучасних практик розробки на C</i></p>
  </div>
</div>

---

### 🎯 Особливості реалізації

- **Модульна архітектура**: Кожен компонент гри винесений в окремий модуль
- **Оптимізована графіка**: Ефективне використання SDL2 для рендерингу
- **Система анімації**: Плавні переходи та спрайтова анімація
- **Візуальні ефекти**: Glitch, noise та інші кінематографічні ефекти

---

### 🌟 Досягнення команди

✅ **Успішно завершений проект** в рамках Innovation Campus  
✅ **Створена повноцінна гра** з нуля за обмежений час  
✅ **Командна робота** на високому рівні  
✅ **Інноваційний геймплей** з унікальними механіками  

---

---

<p align = "center"><i>🚀 Створено з любов'ю командою Floppa Team для EndGame Innovation Campus 2023-2024 🚀</i></p>

</details>

<details>
  <summary>English 🇬🇧</summary>

<span style = "margin-top: 5px;"></span>

> ⚠️ **WARNING:**
>
> This repository contains our implementation of an anomaly detection game developed by a team of 5 people as part of the EndGame project for Innovation Campus 2023-2024.  
> The game is built in pure C using the SDL2 library for graphics, sound, and input.
>
> **Innovative gameplay** — find anomalies in ordinary environments and survive!

---

### 🎮 About the Game

**The Loop Place** is an engaging horror-puzzle game where the player must detect anomalies in everyday environments of various locations. Explore schools, hospitals, libraries and other places, each having multiple floors. The game combines atmospheric tension with detective investigation elements and logical thinking.

### Game Objectives

1. **Search for anomalies** — Carefully explore each floor of different locations
2. **Interact with objects** — Check suspicious items by clicking
3. **Always ensure objects are "real"** — Detect fake or altered objects

### Game Mechanics

**Location structure:**
- **First 5 floors** — free to play
- **Total of 10 floors** — full game version
- **Various locations** — schools, hospitals, libraries and other places
- **Random anomalies** — not every floor has anomalies

**What are anomalies?**
Anomalies are objects with incorrect characteristics:
- **Wrong animation** (e.g., reverse animation)
- **Incorrect object size**
- **Changed textures** or colors
- **Unusual behavior** during interaction

**Detection system:**
- **LMB** — Add anomaly to list
- **RMB** — Remove object from anomaly list
- **List in top-left corner** — Shows all found anomalies

**Elevator and progression:**
- **Elevator** — key object at the end of each location
- **Down button** — if there WERE anomalies on the floor
- **Up button** — if there were NO anomalies on the floor
- **Correct choice** — key to successful completion

### Key Features

- **Atmospheric soundtrack** with SDL2_mixer support
- **High-quality graphics** powered by SDL2_image
- **Intuitive controls** and smooth sprite animation
- **Dynamic anomaly detection system**
- **Various visual effects** including glitch and noise effects
- **Adaptive interface** with support for different resolutions

### Gameplay

**The Loop Place** is an intellectual horror-puzzle where observation accuracy determines your success:

**Goal:** Explore various locations and detect all anomalous objects using:
- **Observation skills** to detect incorrect animations and textures
- **Logical thinking** to analyze object behavior
- **Quick reflexes** for precise object interaction

**Gameplay features:**
- Detailed examination of every object on the floor
- Maintaining a list of found anomalies
- Recognition of fake environmental elements
- Decision-making about elevator direction

---

### 🛠️ Installation and Setup

#### System Requirements
- **OS**: Linux (Ubuntu/Debian recommended)
- **Compiler**: GCC or Clang
- **Dependencies**: SDL2, SDL2_image, SDL2_mixer, SDL2_ttf

#### Step 1: Install Dependencies

```bash
# SDL2 core library
sudo apt install libsdl2-dev libsdl2-2.0-0 -y

# SDL2_image for image handling
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y

# SDL2_mixer for audio
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y

# SDL2_ttf for fonts
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y
```

#### Step 2: Clone and Build

```bash
# Clone repository
git clone https://github.com/lavanios/gameSDL.git
cd gameSDL

# Build project
make

# Run game
./endgame
```

#### Alternative Compilation

```bash
gcc -std=c11 -g src/*.c -o endgame \
    -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf \
    `sdl2-config --cflags --libs`
```

---

### ⚙️ Development Environment Setup

#### Git Configuration

```bash
# Set username and email
git config --global user.email "your.email@example.com"
git config --global user.name "YourUsername"
```

#### Clone with Authentication

```bash
# Clone repository (replace <username> with your GitHub username)
git clone https://<username>:YOUR_TOKEN@github.com/lavanios/gameSDL.git
cd gameSDL
```

#### VSCode Tasks Configuration

Create `.vscode/tasks.json` file in project root:

```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc build project",
            "command": "/usr/bin/gcc",
            "args": [
                "-std=c11",
                "-fdiagnostics-color=always",
                "-g",
                "src/*.c",
                "-o",
                "endgame",
                "-lSDL2",
                "-lSDL2_mixer",
                "-lSDL2_image",
                "-lSDL2_ttf",
                "`sdl2-config --cflags --libs`"
            ],
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "Build The Loop Place project"
        }
    ],
    "version": "2.0.0"
}
```

#### VSCode Setup

1. Open project folder in VSCode
2. Install **C/C++** extension by Microsoft
3. For building use `Ctrl+Shift+P` → "Tasks: Run Build Task"

#### Fixing Git Issues

```bash
# If you encounter Git caching issues
git rm -r --cached .
git add .
git commit -m "Fix git cache issues"
```

---

### 🎮 Controls

| Key/Mouse | Action |
|-----------|--------|
| `A D` | Character movement left/right |
| `LMB` | Add anomaly to list |
| `RMB` | Remove object from anomaly list |
| `Mouse` | Object interaction and checking |

### 🎯 Strategy Guide

1. **Floor exploration:**
   - Carefully examine every object
   - Pay attention to animations and textures
   - Interact with suspicious items

2. **Anomaly list management:**
   - Use LMB to add anomalies
   - RMB helps correct mistakes
   - Monitor the list in top-left corner

3. **Floor completion:**
   - Go to elevator at end of location
   - ⬇️ Press "down" if you found anomalies
   - ⬆️ Press "up" if floor is clean

---

### 📁 Project Structure

```
gameSDL/
├── src/                    # Source code
│   ├── main.c             # Main game file
│   ├── init.c             # SDL initialization
│   ├── music.c            # Audio system
│   ├── loadTexture.c      # Texture loading
│   ├── animateSpriteAAA.c # Sprite animation
│   ├── renderGlitch.c     # Visual effects
│   └── ...                # Other modules
├── inc/                   # Header files
│   └── Header.h           # Main header
├── resources/             # Game resources
│   ├── png/              # Graphics resources
│   ├── songs/            # Audio files
│   ├── font/             # Fonts
│   └── button/           # UI elements
├── Makefile              # Build system
└── README.md             # Documentation
```

---

### 👥 Floppa Team

<div align = "center">
  <table>
    <tr>
      <th align = "center">🎯 Role</th>
      <th align = "center">👤 Member</th>
      <th align = "center">📝 GitHub</th>
      <th align = "center">💡 Contribution</th>
    </tr>
    <tr>
      <td align = "center"><strong>Team Lead & Coder</strong></td>
      <td align = "center">Volodymyr Nevmyrych</td>
      <td align = "center"><a href = "https://github.com/THESAULGOODMAN">TheSaulGoodman</a></td>
      <td align = "center">Project management, code architecture</td>
    </tr>
    <tr>
      <td align = "center"><strong>Main Coder</strong></td>
      <td align = "center">Danylo Lavunov</td>
      <td align = "center"><a href = "https://github.com/lavanios">lavanios</a></td>
      <td align = "center">Core development, game logic</td>
    </tr>
    <tr>
      <td align = "center"><strong>Main Designer</strong></td>
      <td align = "center">Maksym Kopychko</td>
      <td align = "center"><a href = "https://github.com/Archie242">Archie242</a></td>
      <td align = "center">Design, graphics, coding assistance</td>
    </tr>
    <tr>
      <td align = "center"><strong>Designer</strong></td>
      <td align = "center">Yaroslav Fedun</td>
      <td align = "center"><a href = "https://github.com/Blumex7">Blum</a></td>
      <td align = "center">UI/UX design, visual effects</td>
    </tr>
    <tr>
      <td align = "center"><strong>Sound Designer</strong></td>
      <td align = "center">Vladyslav Oryshchuk</td>
      <td align = "center"><a href = "">buymeprada</a></td>
      <td align = "center">Audio design, soundtrack</td>
    </tr>
  </table>
</div>

---

### 🔧 Technologies Used

<div align = "center">
  <table>
    <tr>
      <td align = "center"><h4>🧰 Languages</h4></td>
      <td align = "center"><h4>📚 Libraries</h4></td>
      <td align = "center"><h4>🔨 Build Tools</h4></td>
      <td align = "center"><h4>🛠️ Development</h4></td>
      <td align = "center"><h4>💻 Platforms</h4></td>
    </tr>
    <tr>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://skillicons.dev/icons?i=c" alt = "C" width = "60" height = "60">
          <br><strong>C</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://i.imghippo.com/files/xxW3908Prw.png" alt = "SDL2" width = "60" height = "60">
          <br><strong>SDL2</strong>
        </p>
        <p>
          <img src = "https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" alt = "SDL2 Extensions" width = "40" height = "40">
          <br><strong>SDL2_image</strong>
          <br><strong>SDL2_mixer</strong>
          <br><strong>SDL2_ttf</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://upload.wikimedia.org/wikipedia/commons/2/22/Heckert_GNU_white.svg" alt = "Make" width = "50" height = "50">
          <br><strong>GNU Make</strong>
        </p>
        <p>
          <img src = "https://cdn.jsdelivr.net/gh/devicons/devicon/icons/gcc/gcc-original.svg" alt = "GCC" width = "60" height = "60">
          <br><strong>GCC</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://skillicons.dev/icons?i=git" alt = "Git" width = "60" height = "60">
          <br><strong>Git</strong>
        </p>
        <p>
          <img src = "https://skillicons.dev/icons?i=vscode" alt = "VSCode" width = "60" height = "60">
          <br><strong>VSCode</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://skillicons.dev/icons?i=linux" alt = "Linux" width = "60" height = "60">
          <br><strong>Linux</strong>
        </p>
        <p>
          <img src = "https://skillicons.dev/icons?i=github" alt = "GitHub" width = "60" height = "60">
          <br><strong>GitHub</strong>
        </p>
      </td>
    </tr>
  </table>
  
  <div style = "margin-top: 20px;">
    <h4>🚀 Tech Stack Highlights</h4>
    <img src = "https://img.shields.io/badge/C-Standard-blue?style=flat-square&logo=c" alt = "C">
    <img src = "https://img.shields.io/badge/SDL2-2.0+-green?style=flat-square" alt = "SDL2">
    <img src = "https://img.shields.io/badge/Build-Make-orange?style=flat-square" alt = "Make">
    <img src = "https://img.shields.io/badge/Compiler-GCC-red?style=flat-square&logo=gnu" alt = "GCC">
    <img src = "https://img.shields.io/badge/Platform-Linux-yellow?style=flat-square&logo=linux" alt = "Linux">
  </div>
  
  <div style = "margin-top: 15px;">
    <p><i>🎯 Built with modern C development practices and industry-standard tools</i></p>
  </div>
</div>

---

### 🎯 Implementation Features

- **Modular architecture**: Each game component is separated into individual modules
- **Optimized graphics**: Efficient use of SDL2 for rendering
- **Animation system**: Smooth transitions and sprite animation
- **Visual effects**: Glitch, noise, and other cinematic effects

---

### 🌟 Team Achievements

✅ **Successfully completed project** within Innovation Campus framework  
✅ **Created a full game** from scratch in limited time  
✅ **High-level teamwork**  
✅ **Innovative gameplay** with unique mechanics  

---

---

<p align = "center"><i>🚀 Created with love by Floppa Team for EndGame Innovation Campus 2023-2024 🚀</i></p>

</details>

<details>
  <summary>Deutsch 🇩🇪</summary>

<span style = "margin-top: 5px;"></span>

> ⚠️ **ACHTUNG:**
>
> Dieses Repository enthält unsere Implementierung eines Anomalie-Erkennungsspiels, das von einem 5-köpfigen Team im Rahmen des EndGame-Projekts für Innovation Campus 2023-2024 entwickelt wurde.  
> Das Spiel ist in reinem C mit der SDL2-Bibliothek für Grafik, Sound und Eingabe erstellt.
>
> **Innovatives Gameplay** — finden Sie Anomalien in gewöhnlichen Umgebungen und überleben Sie!

---

### 🎮 Über das Spiel

**The Loop Place** ist ein fesselndes Horror-Puzzle-Spiel, bei dem der Spieler Anomalien in alltäglichen Umgebungen verschiedener Standorte erkennen muss. Erkunden Sie Schulen, Krankenhäuser, Bibliotheken und andere Orte, von denen jeder mehrere Etagen hat. Das Spiel kombiniert atmosphärische Spannung mit Elementen der Detektivarbeit und logischem Denken.

### Spielziele

1. **Suche nach Anomalien** — Erkunde sorgfältig jede Etage verschiedener Standorte
2. **Interagiere mit Objekten** — Überprüfe verdächtige Gegenstände durch Klicken
3. **Stelle sicher, dass Objekte "real" sind** — Erkenne gefälschte oder veränderte Objekte

### Spielmechaniken

**Standortstruktur:**
- **Erste 5 Etagen** — kostenlos spielbar
- **Insgesamt 10 Etagen** — Vollversion des Spiels
- **Verschiedene Standorte** — Schulen, Krankenhäuser, Bibliotheken und andere Orte
- **Zufällige Anomalien** — nicht jede Etage hat Anomalien

**Was sind Anomalien?**
Anomalien sind Objekte mit falschen Eigenschaften:
- **Falsche Animation** (z.B. umgekehrte Animation)
- **Falsche Objektgröße**
- **Veränderte Texturen** oder Farben
- **Ungewöhnliches Verhalten** bei Interaktion

**Erkennungssystem:**
- **LMB** — Anomalie zur Liste hinzufügen
- **RMB** — Objekt aus Anomalienliste entfernen
- **Liste in der oberen linken Ecke** — Zeigt alle gefundenen Anomalien

**Aufzug und Fortschritt:**
- **Aufzug** — Schlüsselobjekt am Ende jeder Location
- **Nach-unten-Taste** — wenn es Anomalien auf der Etage GAB
- **Nach-oben-Taste** — wenn es KEINE Anomalien auf der Etage gab
- **Richtige Wahl** — Schlüssel zum erfolgreichen Abschluss

### Hauptmerkmale

- **Atmosphärischer Soundtrack** mit SDL2_mixer-Unterstützung
- **Hochwertige Grafiken** powered by SDL2_image
- **Intuitive Steuerung** und flüssige Sprite-Animation
- **Dynamisches Anomalie-Erkennungssystem**
- **Verschiedene visuelle Effekte** einschließlich Glitch- und Noise-Effekte
- **Adaptives Interface** mit Unterstützung für verschiedene Auflösungen

### Gameplay

**The Loop Place** ist ein intellektuelles Horror-Puzzle, bei dem die Genauigkeit der Beobachtung über Ihren Erfolg entscheidet:

**Ziel:** Erkunden Sie verschiedene Standorte und erkennen Sie alle anomalen Objekte mit:
- **Beobachtungsfähigkeiten** zur Erkennung falscher Animationen und Texturen
- **Logisches Denken** zur Analyse des Objektverhaltens
- **Schnelle Reflexe** für präzise Objektinteraktion

**Gameplay-Features:**
- Detaillierte Untersuchung jedes Objekts auf der Etage
- Führen einer Liste gefundener Anomalien
- Erkennung gefälschter Umgebungselemente
- Entscheidungsfindung über Aufzugrichtung

---

### 🛠️ Installation und Setup

#### Systemanforderungen
- **OS**: Linux (Ubuntu/Debian empfohlen)
- **Compiler**: GCC oder Clang
- **Abhängigkeiten**: SDL2, SDL2_image, SDL2_mixer, SDL2_ttf

#### Schritt 1: Abhängigkeiten installieren

```bash
# SDL2 Kernbibliothek
sudo apt install libsdl2-dev libsdl2-2.0-0 -y

# SDL2_image für Bildverarbeitung
sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y

# SDL2_mixer für Audio
sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y

# SDL2_ttf für Schriftarten
sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y
```

#### Schritt 2: Klonen und Erstellen

```bash
# Repository klonen
git clone https://github.com/lavanios/gameSDL.git
cd gameSDL

# Projekt erstellen
make

# Spiel ausführen
./endgame
```

#### Alternative Kompilierung

```bash
gcc -std=c11 -g src/*.c -o endgame \
    -lSDL2 -lSDL2_mixer -lSDL2_image -lSDL2_ttf \
    `sdl2-config --cflags --libs`
```

---

### ⚙️ Entwicklungsumgebung Setup

#### Git-Konfiguration

```bash
# Benutzername und E-Mail festlegen
git config --global user.email "your.email@example.com"
git config --global user.name "YourUsername"
```

#### Klonen mit Authentifizierung

```bash
# Repository klonen (ersetzen Sie <username> durch Ihren GitHub-Benutzernamen)
git clone https://<username>:YOUR_TOKEN@github.com/lavanios/gameSDL.git
cd gameSDL
```

#### VSCode Tasks-Konfiguration

Erstellen Sie die Datei `.vscode/tasks.json` im Projektstamm:

```json
{
    "tasks": [
        {
            "type": "cppbuild",
            "label": "C/C++: gcc Projekt erstellen",
            "command": "/usr/bin/gcc",
            "args": [
                "-std=c11",
                "-fdiagnostics-color=always",
                "-g",
                "src/*.c",
                "-o",
                "endgame",
                "-lSDL2",
                "-lSDL2_mixer",
                "-lSDL2_image",
                "-lSDL2_ttf",
                "`sdl2-config --cflags --libs`"
            ],
            "options": {
                "cwd": "${workspaceFolder}"
            },
            "problemMatcher": [
                "$gcc"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "detail": "The Loop Place-Projekt erstellen"
        }
    ],
    "version": "2.0.0"
}
```

#### VSCode-Setup

1. Projektordner in VSCode öffnen
2. **C/C++**-Erweiterung von Microsoft installieren
3. Zum Erstellen verwenden Sie `Ctrl+Shift+P` → "Tasks: Run Build Task"

#### Git-Probleme beheben

```bash
# Bei Git-Caching-Problemen
git rm -r --cached .
git add .
git commit -m "Fix git cache issues"
```

---

### 🎮 Steuerung

| Taste/Maus | Aktion |
|------------|--------|
| `A D` | Charakterbewegung links/rechts |
| `LMB` | Anomalie zur Liste hinzufügen |
| `RMB` | Objekt aus Anomalienliste entfernen |
| `Maus` | Objektinteraktion und Überprüfung |

### 🎯 Strategieleitfaden

1. **Etagenerkundung:**
   - Untersuche sorgfältig jedes Objekt
   - Achte auf Animationen und Texturen
   - Interagiere mit verdächtigen Gegenständen

2. **Anomalienlisten-Verwaltung:**
   - Verwende LMB zum Hinzufügen von Anomalien
   - RMB hilft bei der Korrektur von Fehlern
   - Überwache die Liste in der oberen linken Ecke

3. **Etagenabschluss:**
   - Gehe zum Aufzug am Ende der Location
   - ⬇️ Drücke "nach unten" wenn du Anomalien gefunden hast
   - ⬆️ Drücke "nach oben" wenn die Etage sauber ist

---

### 📁 Projektstruktur

```
gameSDL/
├── src/                    # Quellcode
│   ├── main.c             # Hauptspieldatei
│   ├── init.c             # SDL-Initialisierung
│   ├── music.c            # Audio-System
│   ├── loadTexture.c      # Textur-Laden
│   ├── animateSpriteAAA.c # Sprite-Animation
│   ├── renderGlitch.c     # Visuelle Effekte
│   └── ...                # Andere Module
├── inc/                   # Header-Dateien
│   └── Header.h           # Haupt-Header
├── resources/             # Spiel-Ressourcen
│   ├── png/              # Grafik-Ressourcen
│   ├── songs/            # Audio-Dateien
│   ├── font/             # Schriftarten
│   └── button/           # UI-Elemente
├── Makefile              # Build-System
└── README.md             # Dokumentation
```

---

### 👥 Floppa Team

<div align = "center">
  <table>
    <tr>
      <th align = "center">🎯 Rolle</th>
      <th align = "center">👤 Mitglied</th>
      <th align = "center">📝 GitHub</th>
      <th align = "center">💡 Beitrag</th>
    </tr>
    <tr>
      <td align = "center"><strong>Team Lead & Coder</strong></td>
      <td align = "center">Volodymyr Nevmyrych</td>
      <td align = "center"><a href = "https://github.com/THESAULGOODMAN">TheSaulGoodman</a></td>
      <td align = "center">Projektmanagement, Code-Architektur</td>
    </tr>
    <tr>
      <td align = "center"><strong>Main Coder</strong></td>
      <td align = "center">Danylo Lavunov</td>
      <td align = "center"><a href = "https://github.com/lavanios">lavanios</a></td>
      <td align = "center">Kernentwicklung, Spiellogik</td>
    </tr>
    <tr>
      <td align = "center"><strong>Main Designer</strong></td>
      <td align = "center">Maksym Kopychko</td>
      <td align = "center"><a href = "https://github.com/Archie242">Archie242</a></td>
      <td align = "center">Design, Grafiken, Code-Unterstützung</td>
    </tr>
    <tr>
      <td align = "center"><strong>Designer</strong></td>
      <td align = "center">Yaroslav Fedun</td>
      <td align = "center"><a href = "https://github.com/Blumex7">Blum</a></td>
      <td align = "center">UI/UX-Design, visuelle Effekte</td>
    </tr>
    <tr>
      <td align = "center"><strong>Sound Designer</strong></td>
      <td align = "center">Vladyslav Oryshchuk</td>
      <td align = "center"><a href = "">buymeprada</a></td>
      <td align = "center">Audio-Design, Soundtrack</td>
    </tr>
  </table>
</div>

---

### 🔧 Verwendete Technologien

<div align = "center">
  <table>
    <tr>
      <td align = "center"><h4>🧰 Sprachen</h4></td>
      <td align = "center"><h4>📚 Bibliotheken</h4></td>
      <td align = "center"><h4>🔨 Build-Tools</h4></td>
      <td align = "center"><h4>🛠️ Entwicklung</h4></td>
      <td align = "center"><h4>💻 Plattformen</h4></td>
    </tr>
    <tr>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://skillicons.dev/icons?i=c" alt = "C" width = "60" height = "60">
          <br><strong>C</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://i.imghippo.com/files/xxW3908Prw.png" alt = "SDL2" width = "60" height = "60">
          <br><strong>SDL2</strong>
        </p>
        <p>
          <img src = "https://cdn.jsdelivr.net/gh/devicons/devicon/icons/c/c-original.svg" alt = "SDL2 Extensions" width = "40" height = "40">
          <br><strong>SDL2_image</strong>
          <br><strong>SDL2_mixer</strong>
          <br><strong>SDL2_ttf</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://upload.wikimedia.org/wikipedia/commons/2/22/Heckert_GNU_white.svg" alt = "Make" width = "50" height = "50">
          <br><strong>GNU Make</strong>
        </p>
        <p>
          <img src = "https://cdn.jsdelivr.net/gh/devicons/devicon/icons/gcc/gcc-original.svg" alt = "GCC" width = "60" height = "60">
          <br><strong>GCC</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://skillicons.dev/icons?i=git" alt = "Git" width = "60" height = "60">
          <br><strong>Git</strong>
        </p>
        <p>
          <img src = "https://skillicons.dev/icons?i=vscode" alt = "VSCode" width = "60" height = "60">
          <br><strong>VSCode</strong>
        </p>
      </td>
      <td align = "center" valign = "top">
        <p>
          <img src = "https://skillicons.dev/icons?i=linux" alt = "Linux" width = "60" height = "60">
          <br><strong>Linux</strong>
        </p>
        <p>
          <img src = "https://skillicons.dev/icons?i=github" alt = "GitHub" width = "60" height = "60">
          <br><strong>GitHub</strong>
        </p>
      </td>
    </tr>
  </table>
  
  <div style = "margin-top: 20px;">
    <h4>🚀 Tech-Stack Highlights</h4>
    <img src = "https://img.shields.io/badge/C-Standard-blue?style=flat-square&logo=c" alt = "C">
    <img src = "https://img.shields.io/badge/SDL2-2.0+-green?style=flat-square" alt = "SDL2">
    <img src = "https://img.shields.io/badge/Build-Make-orange?style=flat-square" alt = "Make">
    <img src = "https://img.shields.io/badge/Compiler-GCC-red?style=flat-square&logo=gnu" alt = "GCC">
    <img src = "https://img.shields.io/badge/Plattform-Linux-yellow?style=flat-square&logo=linux" alt = "Linux">
  </div>
  
  <div style = "margin-top: 15px;">
    <p><i>🎯 Erstellt mit modernen C-Entwicklungspraktiken und branchenüblichen Tools</i></p>
  </div>
</div>

---

### 🎯 Implementierungsmerkmale

- **Modulare Architektur**: Jede Spielkomponente ist in individuelle Module aufgeteilt
- **Optimierte Grafiken**: Effiziente Nutzung von SDL2 für Rendering
- **Animationssystem**: Flüssige Übergänge und Sprite-Animation
- **Visuelle Effekte**: Glitch, Noise und andere kinematographische Effekte

---

### 🌟 Team-Erfolge

✅ **Erfolgreich abgeschlossenes Projekt** im Rahmen von Innovation Campus  
✅ **Vollständiges Spiel erstellt** von Grund auf in begrenzter Zeit   
✅ **Hochwertige Teamarbeit**  
✅ **Innovatives Gameplay** mit einzigartigen Mechaniken  

---

<p align = "center"><i>🚀 Mit Liebe erstellt vom Floppa Team für EndGame Innovation Campus 2023-2024 🚀</i></p>

</details>