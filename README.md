<h1>BeatC++ver</h1>
What's up. This is my little attempt to write an okayish C++ Wrapper for the beatsaver REST API.

Probably won't go too far, so yeah.

Right now only simple text search works. But feel free to contribute!

<h2>Dependencies:</h2>

libcurl

nlohmann_json

Build deps:

cmake

gcc/g++

git

idk, lol. Normal build stuff...

To build for Windows:

Visual Studio Build Tools for C++

<h2>Build Instructions</h2>
<h3>Linux (Maybe also Mac and BSD)</h3>

```
# Get git, cmake, make, libcurl from your Distro. libcurl might have to be libcurl-dev or something depending on your Distro
git clone https://gitlab.cs.fau.de/yp98ocaw/beatcppver.git
cd beatcppver
./install.sh #(asks for sudo password)
# You can now remove the directory again, if you like
```


That's it. The library is now installed under /usr/local/lib and /usr/local/include. And it generates a pkg-config file, but I don't really get that yet.

<h3>Windows</h3>
You could probably als build this without vcpkg. This is just how I managed to build the library on Windows 10.

Install download and install vcpkg somewhere. I will reference this folder as <vcpkg_root> from now on.

I did all of this in git-bash, but you can also use Powershell or something. Even Visual Studio Code actually.


```
cd <vcpkg_root>

# This next line might has to be run as root
./vcpkg.exe integrate install
# Copy the -DCMAKE_TOOLCHAIN_FILE Path in the output. You will need it later.

./vcpkg.exe install nlohmann-json:x64-windows

./vcpkg.exe install curl:x64-windows

# if you want to build the test:
./vcpkg.exe install catch2:x64-windows

cd <folder_where_beatcppver_should_be>

git clone https://gitlab.cs.fau.de/yp98ocaw/beatcppver.git

# You can also pass -G "MinGW Makefiles" to configure to compile the library using mingw. Both MSVC and MinGW work as of now.
./configure.sh "-DCMAKE_TOOLCHAIN_FILE=<insert the path from above>"  "-DCMAKE_BUILD_TYPE=Release"
# In case you forgot to replace the <vcpkg_root> or just called ./configure without any arguments
# it will probably tell you it doesn't find some libraries in the next step.
# In that case you have to remove the build directory: rm -rf build/
# Then you would have to rerun configure.
./build.sh

The dll should now be in the build/Debug directory. For some reason it won't create a Release directory on windows.
You can also pass the option "-DBEATCPPVER_STATIC=1" to configure.sh to build a static library
```


<h2>Thanks to:</h2>
nlohmann's json for the greates json header

beatsaver.com

Spotify Web API