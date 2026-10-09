# Real-Time 3D Rendering Engine

A lightweight, cross-platform real-time 3D renderer written in modern C++20 using OpenGL 3.3 (Core Profile), GLSL, and CMake. Designed from scratch to demonstrate low-level graphics pipeline architecture, deterministic memory ownership, and interactive scene inspection.

<p align="center">
  <img src="docs/screenshot.png" alt="Renderer Preview" width="800">
</p>

---

## Technical Highlights

- Cross-Platform Target-Based CMake: Configured for native toolchain execution using GCC 13+ (Linux/WSL) and MSVC 19+ (Windows) via automated dependency acquisition with FetchContent (GLFW, GLAD, GLM, Dear ImGui, tinyobjloader).
- Deterministic Memory Management (RAII): Encapsulated GPU resources (Shader, Mesh) with deleted copy constructors (= delete) and controlled destruction to eliminate duplicate handles and prevent GPU resource leaks.
- Indexed Rendering Pipeline (VAO / VBO / EBO): Efficient vertex caching via Element Buffer Objects (glDrawElements), minimizing data redundancy and vertex processing overhead.
- Automated Asset Processing: Wavefront .obj parsing using tinyobjloader, dynamic smooth normal computation via vector cross-products, and interleaved attribute layout.
- Lighting Model: Multi-component Blinn-Phong illumination (ambient, diffuse, specular) implemented with custom GLSL shaders in world coordinates.
- Real-Time Debug Overlay: Integrated Dear ImGui panel allowing real-time viewport telemetry (FPS, frame time, polygon count), light coordinate manipulation, and material property tuning.
- Decoupled Camera System: Euler-angle first-person camera with delta-time normalized keyboard translation and mouse-look navigation.

---

## Performance Metrics

- Framerate: Sustained 1,500+ FPS (sub-millisecond frame latency) on complex polygonal models (e.g., Stanford Bunny, 69K+ polygons) under modern hardware execution.
- Memory Footprint: Indexed geometry layout reducing raw buffer memory by ~50% compared to non-indexed draw arrays.

---

## Architecture Overview

cpp-3d-renderer/
├── assets/             # 3D models (.obj) and test meshes (ignored in git)
├── docs/               # Screenshots and visual documentation
├── shaders/            # Custom programmable GLSL shaders
│   ├── basic.vert      # Model-View-Projection transforms, normal propagation
│   └── basic.frag      # Blinn-Phong lighting and specular calculation
├── src/
│   ├── Camera.hpp      # First-person view matrix & input processing
│   ├── Mesh.hpp/cpp    # RAII-managed VAO, VBO, and EBO abstractions
│   ├── ModelLoader.hpp # OBJ parsing pipeline interfacing tinyobjloader
│   ├── Shader.hpp/cpp  # Shader compilation, linking, and uniform dispatch
│   └── main.cpp        # Window initialization, ImGui render loop, and events
├── .gitignore          # Build artifacts, IDE caches, and local assets
└── CMakeLists.txt      # Root modern CMake configuration

---

## Build and Run

### Prerequisites
- C++ Compiler: GCC 13+ (Linux) or MSVC 2022+ (Windows) supporting C++20.
- Build System: CMake 3.20+.
- Graphics: Hardware or driver supporting OpenGL 3.3 Core Profile.

### Linux / WSL (GCC)
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
./build/RendererApp

### Windows (MSVC / PowerShell)
cmake -B build
cmake --build build --config Release
.\build\Release\RendererApp.exe

---

## Controls

| Input | Action |
| :--- | :--- |
| W, A, S, D / Z, Q, S, D | Translate camera forward / left / backward / right |
| Mouse Motion | Free-look camera orientation (Pitch & Yaw) |
| TAB | Toggle cursor capture between Camera Control and ImGui Panel |
| ESC | Exit application |
