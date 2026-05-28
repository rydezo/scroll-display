# LED Scroll Display (Sense HAT)

## Overview

This program runs on a Raspberry Pi Sense HAT and renders animated, scrollable initials on the 8×8 LED matrix. The display responds in real time to joystick input, allowing the user to move and accelerate the displayed letter in both horizontal and vertical directions while cycling through multiple characters.

The program uses velocity-based motion, meaning movement is smooth, continuous, and independent in both axes. The result is a responsive, physics-like scrolling effect where direction and speed evolve naturally from user input.

---

## Key Features

### Smooth velocity-based motion
The letter moves according to a continuous position model:

- Position updates use:  
  `x = x + vx * dt`  
  `y = y + vy * dt`

- This ensures:
  - No skipped pixels
  - Smooth animation
  - Independent control of X and Y movement

---

### Joystick-controlled interaction

The joystick provides real-time control of both motion and state:

- **Up / Down** → adjust vertical velocity
- **Left / Right** → adjust horizontal velocity
- **Press (enter)** → cycles through available initials

Each input modifies velocity incrementally, allowing acceleration up to a capped maximum speed in any direction. Opposing inputs reduce or reverse motion.

---

### Multi-initial sequencing

The program cycles through multiple predefined initials. Each press of the joystick button advances the displayed character.

- Once the final character is displayed, an additional button press clears the display and exits the program.

This creates a simple but effective state machine driven entirely by user interaction.

---

### Wrapping display system

The LED matrix is treated as a toroidal (wrap-around) surface:

- Moving off one edge causes the letter to reappear on the opposite side
- Coordinates are wrapped using modulo arithmetic

This ensures continuous motion without boundary constraints.

---

### Rotatable rendering

The display supports rotation of rendered letters without affecting movement logic:

- 0°, 90°, 180°, 270° counter-clockwise rotation supported
- Rotation changes only visual orientation
- Input directions remain consistent and unaffected

This separation keeps control intuitive regardless of display orientation.

---

### Color customization

The displayed letter color can be configured at runtime:

- Supports multiple preset colors (e.g., white, red, green, blue)
- Color selection is applied globally to all rendered frames
- Invalid selections fall back to default behavior

---

## Design

The program is structured around three independent subsystems:

### 1. Display subsystem
Responsible only for rendering letters to the LED matrix. It abstracts framebuffer access and ensures consistent drawing behavior regardless of position, rotation, or color.

### 2. Input subsystem
Handles joystick polling and translates hardware events into callback-driven commands. This allows asynchronous user interaction without blocking the main loop.

### 3. Control subsystem
Maintains program state including:
- Current letter
- Position
- Velocity
- Program lifecycle

It integrates input and display into a continuous update loop.

---

## Behavior Summary

At runtime, the program:

- Displays an initial letter immediately
- Continuously updates position based on velocity
- Responds to joystick input in real time
- Cycles through multiple initials
- Exits cleanly after the final state is reached

The result is a dynamic, interactive LED animation system where motion is smooth, controllable, and visually continuous.

---

## Impact

This program demonstrates several important systems programming concepts in a constrained hardware environment:

- Event-driven input handling
- Real-time animation using time-based motion
- Separation of hardware abstraction layers
- State management through a control loop
- Coordinate transformation and wrapping behavior
