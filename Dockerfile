# Environnement de build Linux reproductible : compile l'app + les tests, lance les tests.
# Aucun écran nécessaire : les tests n'utilisent pas OpenGL, seuls les en-têtes sont requis pour compiler.
FROM ubuntu:24.04

# python3 : glad 0.1 génère son loader en Python à la configuration CMake
# lib*-dev X11 + libgl-dev : en-têtes pour compiler GLFW (backend X11) et l'app
RUN apt-get update && apt-get install -y --no-install-recommends \
        build-essential cmake ninja-build git ca-certificates python3 \
        libgl-dev libx11-dev libxrandr-dev libxinerama-dev libxcursor-dev libxi-dev libxkbcommon-dev \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /src
COPY . .

RUN cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release -DRENDERER_WARNINGS_AS_ERRORS=ON \
    && cmake --build build

CMD ["ctest", "--test-dir", "build", "--output-on-failure"]
