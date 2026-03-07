# atestat-boids

[![Language](https://img.shields.io/badge/language-C%2B%2B-blue)](https://isocpp.org/)
[![Library](https://img.shields.io/badge/library-SFML-green)](https://www.sfml-dev.org/)
[![Platform](https://img.shields.io/badge/platform-Windows-lightgrey)]()

An interactive **Boids flocking simulation** built with C++ and SFML. This project simulates the emergent flocking behavior of 300 birds (boids) navigating around obstacles, with real-time parameter adjustment.

## 🔍 About the Project

This project implements Craig Reynolds' classic **Boids flocking algorithm** as part of an "Atestat" (final project). What makes this implementation unique is its:

- **Real-time interaction** with 4 adjustable parameters
- **Obstacle avoidance** system with 6 segment-based obstacles
- **Visual debugging** tools (toggleable rays)
- **Pause functionality** to fine-tune settings

The simulation demonstrates how complex flocking behavior emerges from three simple rules:
- **Separation**: Avoid crowding neighbors
- **Alignment**: Steer towards the average heading
- **Cohesion**: Move toward the center of the flock

## ✨ Features

- **300 simultaneous boids** with smooth performance
- **6 segment obstacles** that boids intelligently avoid
- **4 real-time adjustable parameters** via sliders:
  - Vision distance
  - Cohesion weight
  - Separation weight
  - Alignment weight
- **Interactive controls**:
  - Pause/play functionality
  - Regenerate random boids and obstacles
  - Toggle obstacle avoidance rays (debug mode)
  - Toggle slider visibility
- **On-screen information panel** (hold Tab)

## 🛠️ Built With

- **Language:** C++
- **Graphics Library:** [SFML](https://www.sfml-dev.org/) (Simple and Fast Multimedia Library)
- **Platform:** Windows (tested on Windows 10/11)
- **Build System:** PowerShell scripts

## 🚀 Getting Started

### Prerequisites

- **Windows OS** (the simulation only works on Windows)
- **SFML Library** (version 2.5 or later)
- **C++ Compiler** (MinGW-w64 or Visual Studio with C++ tools)
- **PowerShell** (pre-installed on Windows)

### Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/v3rd3-prely/atestat-boids.git
   cd atestat-boids
