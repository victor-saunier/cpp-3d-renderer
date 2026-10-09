# Real-Time 3D Rendering Engine

A lightweight, cross-platform real-time 3D renderer written in modern **C++20** using **OpenGL 3.3 (Core Profile)**, **GLSL**, and **CMake**. Built from scratch to explore low-level graphics pipelines, memory ownership semantics, and interactive asset inspection.

---

## Technical Highlights

* **Cross-Platform Target-Based CMake:** Fully configured for native build environments using GCC 13+ (Linux/WSL) and MSVC 19+ (Windows) via automated dependency acquisition with `FetchContent` (GLFW, GLAD, GLM, Dear ImGui, tinyobjloader).
* **Deterministic Memory Management (RAII):** GPU resource encapsulation (`Shader`, `Mesh`) with deleted copy constructors (`= delete`) and explicit move semantics to eliminate resource duplication and prevent GPU memory leaks.
* **Indexed Rendering Pipeline (VAO / VBO / EBO):** Efficient vertex caching via Element Buffer Objects (`glDrawElements`), reducing vertex redundancy and GPU memory bandwidth.
* **Automated Asset Processing:** Wavefront `.obj` parsing using *tinyobjloader*, dynamic smooth normal computation, and geometry data alignment.
* **Dynamic Lighting Model:** Multi-component Blinn-Phong illumination (ambient, diffuse, specular) implemented with custom GLSL shaders.
* **Real-Time Debug Overlay:** Integrated *Dear ImGui* panel allowing real-time viewport telemetry (FPS, frame time, polygon count), light coordinate manipulation, and material property tuning[cite: 6].
* **Decoupled Camera System:** Euler-angle first-person camera with delta-time normalized keyboard translation and mouse-look navigation[cite: 6].

---

## Performance Metrics

* **Framerate:** Sustained **1,500+ FPS** (sub-millisecond frame latency) on complex polygonal models (e.g., Stanford Bunny, 69K+ polygons) under modern hardware execution[cite: 2, 6].
* **Memory Footprint:** Indexed geometry layout reducing raw buffer memory by ~50% compared to non-indexed draw arrays[cite: 6].

---

## Architecture Overview


