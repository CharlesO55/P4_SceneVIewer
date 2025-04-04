# Terminal (Ctrl+`)

### Make sure sol is in same dir as proj.
Otherwise change the cd navigation.

## Cloned/Moved
1. Linking the vcpkg folder to VS

cd vcpkg

./bootstrap-vcpkg.bat

./vcpkg integrate install



## First time install or No vcpkg folder found
1. Creating vcpkg subfolder

git clone https://github.com/microsoft/vcpkg

cd vcpkg


2. Connecting VS to Vcpkg installations

./bootstrap-vcpkg.bat

./vcpkg integrate install


3. Installing new packages to vcpkg directory
#### [For GRPC]

./vcpkg install grpc

#### [For HO7]

#### [For MP]

./vcpkg install glfw3:x64-windows

./vcpkg install imgui[core,glfw-binding,opengl3-binding]:x64-windows

#### [NEW]
./vcpkg install tinyobjloader

./vcpkg install glad

./vcpkg install glm

./vcpkg install assimp

4. Restart VS & Add to dependencies:
#### [For HO7]

opengl32.lib

glfw3dll.lib