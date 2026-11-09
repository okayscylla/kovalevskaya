# Kovalevskaya

## Features

**Kovalevskaya** has **four** main components:

1) A custom **linear algebra library** from which all other components are built upon.

2) A complete **3d graphics library** and scene representation supporting perfect primitives.

3) A **real time Whitted raytracer** implementing the Phong lighting model.

4) A small **GPU accelerated window / UI library** using raw Vulkan through SDL3's GPU API.

Additionally, several other small test renderers are available to demonstrate the window library's **hot swappable renderer** system.

## Build Instructions

It is **highly recommended** that kovalevskaya be **built and ran** on **Linux**.

While OpenMP does support Windows, I do not have access to a Windows machine and thus **did not enable OpenMP** support **for Windows** in CMakeLists.txt. Because of this, performance will be **significantly degraded** on **non-Linux** based operating systems.

This project was built using **Clang 23**, **CMake 4.4**, **SDL3 3.4**, and **OpenMP 23.1**. However, any somewhat recent version of any of these packages (combined with a semi-recent compiler) should be usable for building Kovalevskaya.

**Building** should be **relatively simple**. The provided CMakeLists.txt should handle everything, with a user only needing to **run configure (release)** and then **build all** to get a working executable. The \***NIX commands** to do so can be found below. A working CMake executable under "cmake" is assumed.

1) **mkdir build**  
2) **cmake \--B build**  
3) **cmake \--build build**

The resulting **"kovalevskaya" executable** should be in the **build folder**.

## Acknowledgments

**NO AI OF ANY SORT OF USED IN THE CREATION OF THIS PROJECT**

**Jamis Buck's** wonderful book *The Ray Tracer Challenge* describes a set of **unit tests** for a ray tracer and ray tracer related components to pass. I implemented many of these tests myself in order to ensure proper functionality. **All code is my own.** While the book describes the fundamentals of ray tracing and ray tracer implementation, it provides no code or direct instructions. Kovalevskaya additionally **expands significantly past what the book describes**, being real time and featuring a custom built graphics software stack, rendering pipeline, and set of associated libraries.

The **SDL3** and **OpenMP** libraries were used in Kovalevskaya as minimal dependecies. For unit tests, the **unittest** library was used.

This project has been going on for **two years** and only recently has been consolidated into one place.