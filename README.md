# Robot Navigation

Robot Navigation provides local path planning and sensor packet handling for Caldova delivery robots. It turns compact lidar packets and route files into short navigation plans that can be consumed by the rover control loop.

## Features

- Parse compact lidar frames from the rover sensor bus
- Load route grids and waypoint files from disk
- Plan stepwise movement across a weighted grid
- Keep the most recent route available for telemetry and operator review
- Emit concise navigation events for fleet diagnostics

## Layout

- `include/caldova/nav/` public headers
- `src/` implementation and command entry point
- `config/` route file used for local runs

## Setup

Requirements:

- CMake 3.16 or newer
- A C++17 compiler

Build:

```powershell
cmake -S . -B build
cmake --build build
```

## Usage

```powershell
.\build\caldova-nav.exe config\downtown.route
```

The route file starts with grid dimensions, followed by one waypoint per line:

```text
24 18
hub 2 2
market 8 4
customer 17 12
```

The executable loads the route, ingests a sensor frame, computes a path, and prints the next rover command.
