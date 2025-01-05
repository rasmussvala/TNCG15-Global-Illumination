# Ray Tracer in C++

## Overview

This project is a part of the course [TNCG15 Advanced Global Illumination and Rendering](https://studieinfo.liu.se/kurs/TNCG15/ht-2024) at Linköping University 2024. The project aimed to create a Monte Carlo ray tracer in C++ from scratch that simulates realistic global illumination featuring transparent, reflective, and Lambertian surfaces.

## Usage Windows

### Prerequisites

- CMake GUI
- VS 2022/2019

### Run it on your machine

1. Clone repo.
2. Create a build directory within the project.
3. Open CMake.
4. Select the TNGC15-Global-Illumination directory as the source.
5. Select the build directory created in step 2 as the build.
6. Press Generate.

Done! Now you can open the solution created in the build directory (.sln file).

## Usage MacOS

### Prerequisites

- CMake (Install via [Homebrew](https://brew.sh/): `brew install cmake`)
- A C++ compiler (e.g., Clang, included with Xcode Command Line Tools)

### Run it on your machine

1. **Clone the Repository**

2. **Install Xcode Command Line Tools**  
   If you don’t already have Xcode Command Line Tools installed, run:

   ```bash
   xcode-select --install
   ```

3. **Create a Build Directory**  
   Create a separate directory for the build files:

   ```bash
   mkdir build
   cd build
   ```

4. **Run CMake to Configure the Project**  
   Run the following command to configure the build system, specifying the parent directory as the source:

   ```bash
   cmake ..
   ```

5. **Build the Project**  
   Use CMake to compile the project:

   ```bash
   cmake --build .
   ```

   or

   ```bash
   make
   ```

6. **Run the Executable**  
   After the build completes, you’ll find the executable in the `build` directory. Run it using:
   ```bash
   ./Raytracing
   ```

That’s it! The ray tracer will run and generate the output based on the provided settings.

## Renders from Ray Tracer

![render2](https://github.com/user-attachments/assets/27657e2f-e40f-44a4-a799-ad6a233967e1)
![image2](https://github.com/user-attachments/assets/7208996f-4b73-4270-8b6c-43f52ce6319c)

