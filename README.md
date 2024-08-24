# nextfloor

A 3d engine at very early stage and in working progress.

The program generates randomly some rooms with some moving cubes.
The camera can move with mouse (head orientation) and arrow keys (camera direction).

## Prerequisites

Needs Git Lfs Extension, Cmake (>3.1 and <3.13), TBB, OpenGL3 (>3.3) and GLew / GLM / SOIL / Glfw libraries.

On ubuntu or Debian, apt-get make most of prerequisites install
```
# apt-get install cmake make g++ git-lfs libx11-dev libgl1-mesa-dev libglu1-mesa-dev
# apt-get install libxrandr-dev libxext-dev libglfw3-dev libsoil-dev libglm-dev
# apt-get install libglew-dev opencl-headers libtbb-dev lsb-core libconfig++-dev
```

On OSX, we need XCode and install some libraries with brew (SOIL must be install manually)
```
$ brew install cmake glm glew glfw3 tbb libconfig git-lfs
```

And SOIL must be install manually
```bash
git clone https://github.com/childhood/libSOIL
cd libSOIL && make
sudo mkdir -p /opt/local/include/SOIL
sudo mkdir -p /opt/local/lib
sudo cp *.h /opt/local/include/SOIL/
sudo cp libSOIL.* /opt/local/lib/
```

## Compile

In build directory, generate MakeFiles and compile project
```
$ git lfs install && git lfs fetch && git lfs checkout
$ cd build && cmake ../
-- The C compiler identification is AppleClang 11.0.0.11000033
-- The CXX compiler identification is AppleClang 11.0.0.11000033
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc
-- Check for working C compiler: /Applications/Xcode.app/Contents/Developer/Toolchains/
...
-- Configuring done
-- Generating done
-- Build files have been written to: /Users/ericfehr/Desktop/nf/build

$ make
Scanning dependencies of target nextfloor
[  1%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/action/movedown_action.cc.o
[  2%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/action/moveleft_action.cc.o
[  4%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/action/moveright_action.cc.o
[  5%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/action/moveup_action.cc.o
[  7%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/action/sprite_action_factory.cc.o
[  8%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/camera/game_camera_factory.cc.o
[ 10%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/camera/head_camera.cc.o
[ 11%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/character/game_character_factory.cc.o
[ 13%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/character/player.cc.o
[ 14%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/core/common_services.cc.o
[ 15%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/core/file_config_parser.cc.o
...
[ 91%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/renderer/gl_shader_factory.cc.o
[ 92%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/renderer/vertex_gl_shader.cc.o
[ 94%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/thing/game_thing_factory.cc.o
[ 95%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/thing/rock.cc.o
[ 97%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor/thing/wall_brick.cc.o
[ 98%] Building CXX object CMakeFiles/nextfloor.dir/src/nextfloor.cc.o
[100%] Linking CXX executable ../bin/nextfloor
[100%] Built target nextfloor
```

## Features

- C++14
- TBB
- Opengl 3
- Use of Glew, GLM, SOIL, Glfw libraries
- CMake for compile

## Folders
```
+--assets/  Texture files
+--bin/     Binary folder where nextfloor executable is written
+--build/   Build folder for compile stuffs
+--cmake/   Cmake modules folder
+--config/  Config folder
+--glsl/    OpenGL Shaders folder
+--scripts/ Bash scripts
+--src/     Sources
```

## Settings

A default setting file is present at config/nextfloor.ini.default
For local config change, we can duplicate this file
```
$ cp config/nextfloor.ini.default config/nextfloor.ini
$ vi config/nextfloor.ini
```

It's also possible to change mostly setting on the fly with program parameters (See below).

## Run

Use mouse for head orientation and arrow keys for camera move.
And following keys are used
- 'esc': exit

Default run, without any parameter
```
bin/./nextfloor  # Use settings as setted in config file (config/nextfloor.ini or config/nextfloor.ini.default).
```

Program accept options who can override config settings
```
./bin/./nextfloor can be used with following options who overrides config file
-d n   Debug mode, 0: no debug, 1: test debug, 2: performance debug, 3: collision debug, 4: all debug
-e n   Execution Time, 0: no limit
-g n   Granularity on collision computes
-h     Display help
-l 1|0 Enable/Disable display config
-p serial|tbb
       serial: no parallellism
       tbb: uses intel tbb library
-v 1|0 Enable/Disable vsync
-w n   Workers (cpu core) count (disabled if -p serial), 0: no limit, all cpu cores
```

For example
```
./bin/./nextfloor -d 0 -p tbb -v 0 # no debug, tbb parallellism, vsync off
```
