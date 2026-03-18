# embedded-cli

UART CLI demo application for STM32F4 using [tinycli](https://github.com/eaytur/tinycli).

## Project Structure

```
embedded-cli/
├── app/            # Application layer (commands, app_main)
│   ├── inc/
│   └── src/
├── bsp/            # Board Support Package (UART driver)
│   ├── inc/
│   └── src/
├── libs/
│   └── tinycli/    # CLI engine (git submodule)
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

## Clone

```bash
git clone https://github.com/eaytur/embedded-cli.git
cd embedded-cli
git submodule update --init
```

## Build

```bash
cmake --preset Debug
cmake --build --preset Debug
```
