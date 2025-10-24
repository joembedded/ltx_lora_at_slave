# LoRaWAN AT Slave

## Overview
STM32WLE5-based LoRa AT modem with custom bare-metal functionality. Built on STMCubeWL framework for flexible hardware platform support.

## Hardware
- **Development Board**: Nucleo-WL55JC1 EVK (ST)
- **MCU**: STM32WLE5
- **Target Platform**: Configurable via `device.h`

## Project Structure
- **Core Functionality**: `STM32CubeIDE\Application\User\JoEmSTB\stb_tools.c`
- **Platform Configuration**: `device.h`
- **Framework**: STMCubeWL

## Hardware Variants
Generate platform variants using STM32CubeMX.

## Features
- LoRaWAN AT command interface
- Custom bare-metal functions
- Multi-platform support

## Version
**v0.1b** - Initial beta release
