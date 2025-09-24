# Raylib and Emscripten Template

This is a basic template for creating a [raylib](https://www.raylib.com/) application with C++ compiled for web using Emscripten.

## Usage

- Open in VS Code and open in dev container.
- Wait for setup commands to finish.
- Build the project in one of three ways:
   - `Ctrl` + `Shift` + `B` (default build shortcut)
   - Run the `build` task manually
   - Execute `cmake --build build` in a terminal window within the dev container.
- Open the newly generated [dist/example.html](dist/example.html) file.
   - You can view this with a preview window with VS Code (open the file in VS Code and click the **Show Preview** icon in the upper right corner of the editor).

## Notes

Configuring CMake:

```
cmake -S . -B build -G Ninja -DPLATFORM=Web \"-DCMAKE_TOOLCHAIN_FILE=/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake\"
```

- The devcontainer image uses an Emscripten image, so the SDK exists in the root of the container at `/emsdk`.
- This action is performed when the container is created. If you need to reconfigure CMake, there is a task in [tasks.json](./.vscode/tasks.json).

To build:

```
cmake --build build
```

- This is hooked into the default build task in [tasks.json](./.vscode/tasks.json).

Note on assets:

- Files in the `assets` directory are bundled into Emscripten's virtual file system at build time. This is configured in `CMakeLists.txt` by adding `--preload-file assets` to the `CMAKE_EXE_LINKER_FLAGS` for the web platform.
