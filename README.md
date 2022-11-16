# Kasumi: illumine the endless night.

[![Ubuntu Build](https://github.com/HinaPE/Kasumi-renderer/actions/workflows/ubuntu.yml/badge.svg)](https://github.com/HinaPE/Kasumi-renderer/actions/workflows/ubuntu.yml)
[![macOS Build](https://github.com/HinaPE/Kasumi-renderer/actions/workflows/macos.yml/badge.svg)](https://github.com/HinaPE/Kasumi-renderer/actions/workflows/macos.yml)
[![Windows Build](https://github.com/HinaPE/Kasumi-renderer/actions/workflows/windows.yml/badge.svg)](https://github.com/HinaPE/Kasumi-renderer/actions/workflows/windows.yml)

## Introduction

1. Kasumi is a cross-platform, light and easy-to-use research-oriented multi-backend renderer, including a workbench renderer, a software rasterizer and a pathtracer.  

## Build Instruction

As a cross-platform project, [Clion](https://www.jetbrains.com/clion/) is highly recommanded to build Kasumi.

### Prerequisites

- C++ 20
- cmake > 3.16

First recursively clone this repo and all submodules.

```shell
git clone --recursive https://github.com/Xayah-Hina/Kasumi-renderer.git
```

### macOS

```shell
cmake -S . -B Build
cmake --build Build --config Release
```

### Ubuntu

```shell
cmake -S . -B Build
cmake --build Build --config Release
```

### Windows

```shell
cmake -S . -B Build
cmake --build Build --config Release
```
