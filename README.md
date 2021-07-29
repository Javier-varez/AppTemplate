
# App Template

This project is a C++ application template for small embedded ARM Cortex-M MCUs.

After cloning make sure to update the following fields:
  * Update the `APPLICATION_NAME` variable in CMakeLists.txt with the name of your application
  * Update the `memory.ld` linker script to point to your RAM and FLASH memories.
  * Update the systick frequency in `systick_config.h`.
  * Write your own code and have tons of fun!

This template should work out of the box on a nRF52840 MCU.

To build you will need:
  * An up to date clang compiler (version >= 11).
  * A cross GCC ARM compiler (>= gcc-arm-none-eabi-10-2020-q4-major).
  * CMake >= 3.16
  * Optional: Ninja. It significantly speeds up the compilation process.
  * Git: used by Postform to detect the FW version being used and embed it into the ELF debug sections.

# Build instructions

Run the following commands in a terminal:

```bash
mkdir build
cd build

# Select the appropriate toolchain file for your MCU Architecture
cmake -G Ninja -D CMAKE_TOOLCHAIN_FILE=cmake/toolchains/armv7e-m.cmake -DCMAKE_SYSTEM_NAME=Generic ..
cmake --build .

# The output file will have the name given by the ${APPLICATION_NAME} variable in CMakeFiles.txt.
# By default this will be nrf52_app
```

In order to run the binary with `Postform` install `postform_rtt` with:

```bash
# Installs the latest version of Postform. It must match the firmware version used, which also
# tracks the main branch
cargo install postform_rtt --git https://github.com/Javier-varez/postform --branch main postform_rtt
```

Then run the program in the target, connect it to the computer using a JTAG/SWD interface and run:

```bash
postform_rtt --chip nRF52840_xxAA build/nrf52_app
```

You should see some logs being printed in your terminal now!

