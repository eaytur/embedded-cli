# embedded-cli

A command line interface (CLI) implementation for STM32F407-based embedded systems.

## Project Structure

```
embedded-cli/
├── app/            # Application layer
│   ├── inc/
│   └── src/
├── cli/            # CLI module
│   ├── inc/
│   └── src/
├── bsp/            # Board Support Package
│   ├── inc/
│   └── src/
├── config/         # Configuration files
├── docs/           # Documentation
├── tests/          # Tests
├── Core/           # STM32CubeMX generated core files
├── Drivers/        # STM32 HAL and CMSIS drivers
├── cmake/          # CMake toolchain files
├── CMakeLists.txt
├── CMakePresets.json
├── STM32F407XX_FLASH.ld
└── startup_stm32f407xx.s
```

## Requirements

- ARM GCC Toolchain (`arm-none-eabi-gcc`)
- CMake >= 3.22
- Ninja

## Build

```bash
cmake --preset Debug
cmake --build --preset Debug
```
