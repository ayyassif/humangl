# humangl

A small OpenGL + Dear ImGui project for animating a stylized humanoid creature with a live body editor. The app renders a custom character, supports animation states, and exposes a UI for tweaking part colors and sizes in real time.

## Overview

This project combines:

- OpenGL rendering for the character and scene
- GLFW for window and input management
- GLAD for OpenGL loading
- Dear ImGui for the live editor UI
- A custom transform hierarchy for body parts, limbs, wings, and tail

The goal is to make the creature feel alive by blending skeletal transforms, simple animation cycles, and real-time tuning controls.

## Features

- Custom humanoid body built from connected `CordFrame` transforms
- Multiple animation modes including idle, run, jump, fly, and dance
- Real-time manipulation of limb scale and color through the body editor UI
- Camera movement and orbit-style model inspection
- Shader-based rendering pipeline with custom GLSL files
- Lightweight modular structure organized by system and object type

## Project structure

```text
.
├── README.md
├── makefile
├── humangl                  # built binary
├── imgui.ini                # ImGui window layout state
├── shaders/
│   ├── fragment.glsl
│   └── vertex.glsl
├── src/
│   ├── main.cpp
│   ├── humangl.hpp
│   ├── app/
│   ├── BodyEditorUI/
│   ├── camera/
│   ├── cordFrame/
│   ├── cubeMesh/
│   ├── debugger/
│   ├── human/
│   ├── input/ain your hierarchical model and
│   ├── math/
│   ├── part/
│   └── shader/
├── external/
│   ├── glad/
│   └── imgui/
├── glad/
│   ├── include/
│   └── src/
└── build/
```

## Build

From the project root:

```bash
make
```

Then run:

```bash
./humangl
```

## Clean build artifacts

```bash
make clean
```

To remove the binary as well:

```bash
make fclean
```

## Controls

The app exposes live interaction through the mouse and keyboard, and the ImGui editor allows changes to the character while it animates.

Typical interactions include:

- Mouse drag to rotate the model
- Mouse scroll to zoom the cameraain your hierarchical model and
- WASD movement for camera navigation
- Space / Shift for vertical movement
- Escape to exit

## Gallery

Use this section to add screenshots, gifs, and recordings of the project as it evolves.

### Body Editor

![Body Editor](gallery/body_editor.gif)

### Idle Pose

![Idle Pose](gallery/Idle.gif)

### Running Animation

![Running Animation](gallery/Run.gif)

### Jump Sequence

![Jump Sequence](gallery/Jump.gif)

### Flight Mode

![Flight Mode](gallery/Fly.gif)

### Default Pose

![Default Pose](gallery/None.gif)

## Notes

This project is intentionally lightweight and educational: it is built around direct OpenGL calls and simple custom math utilities rather than a large engine framework. It is a good fit for experimenting with animation, transform hierarchies, and UI-driven editing.
