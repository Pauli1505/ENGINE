You can build in 2 ways.
you need either UNIX (Linux, Not OSX), BSD (Includes Darwin OSX), or a DOS (NT, Windows, MSDOS) system.
The first way is Without Wi-FI but limited (only build for your current System, or more on dual-boot)
on Windows, to build without Wi-FI you will need to:
Install Msys2 Mingw64
install the mingw-w64-toolchain (mingw-w64-x86_64-toolchain) Package
Install the Engine
Run: "make ARCH=[insert your CPU Architecture here] -j$(nproc)"

Linux (no Wi-Fi)

1. Install the Mingw toolchain (for example on pacman, the package is mingw-w64-toolchain)
2. install make, gcc, base-devel (also examples for pacman, on APT this would be build-essential)
3. run "Make PLATFORM=mingw64 ARCH=[insert your CPU Architecture here] -j$(nproc)"

Mac:
Building has not been tested on OSX/Darwin systems, meaning it is completely unpredictable if it works
it is recommended to use a Seperate computer with a Linux System, as the Platform Specific code on Linux and Mac is not seperate, but rather UNIX specific code.
meaning if you compile for linux, it will likely work on OSX. one way is to use fatelf, but for now, compile to linux and if it works, use actions for mac.

Wifi build:

Upload the engine (including .github) to github, and use actions to build, these builds can take around 5 minutes.