# JUCE Plugin Template (CMake + C++23)

A **simple, lightweight** template designed to help transition from **Projucer** to **CMake**.

This template is built for **focused local development**. It strips away the complexity of CI/CD pipelines, installers, and code signing found in advanced frameworks (like Pamplejuce) so you can focus entirely on learning CMake and writing modern C++ audio code.

## Purpose
* **Simplicity First:** No Docker, no GitHub Actions, no complex Azure scripts. Easy transition from Projucer to CMake.
* **Local Focus:** Optimized for running, debugging, and testing plugins immediately on your own machine.
* **Modern Habits:** Enforces professional standards (C++23, LLVM Style).

## Key Features

* **Build System:** **CMake 3.25+**
    * No more manual `.jucer` file management.
    * Standard `CMakeLists.txt` workflow supported natively by CLion, VS Code, and Visual Studio.
* **Language Standard:** **C++23**
    * Strict warnings enabled (`-Wall`, `-Wextra`) to prevent sloppy code.
* **Dependency Management:** **CPM**
    * JUCE is fetched automatically via CMake. No manual download, installation, or path configuration required.
* **Code Style:** **LLVM Standard**
    * Enforced via `.clang-format`.
    * **Indentation:** 2 Spaces (Industry standard).
    * **Braces:** Attached (Java/One True Brace Style).
    * **Pointers:** Left-aligned (`int* x`) for type clarity.

## How to Use

### 1. Create a New Plugin
Click the green **"Use this template"** button at the top of this page to create a fresh repository for your new plugin.

### 2. Configure Your Project
Open `CMakeLists.txt` and change the project name on line 4:
```cmake
# Change "SimpleJucePluginTemplate" to your plugin name
project(MyNewReverb VERSION 0.0.1)

# ... scroll down ...

juce_add_plugin(MyNewReverb ...)

```

### 3. Build & Run

**In CLion:**

1. Open the project folder (CMake will auto-configure).
2. Select the `MyNewReverb_Standalone` target from the top dropdown.
3. Click the **Run** (Play) button.

**In Terminal:**

```bash
cmake -B build
cmake --build build

```

## File Structure

* **`CMakeLists.txt`** - The "brain" of the project. Replaces the `.jucer` file.
* **`Source/`** - C++ code (`PluginProcessor.cpp`, `PluginEditor.cpp`). Follows the standard JUCE module structure.
* **`.clang-format`** - Configuration file ensuring all code follows the LLVM standard automatically.
```