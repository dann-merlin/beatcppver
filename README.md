<h1>BeatC++ver</h1>
What's up. This is my little attempt to write an okayish C++ Wrapper for the beatsaver REST API.

Probably won't go too far, so yeah.

Right now only simple text search works. But feel free to contribute!

<h2>Dependencies:</h2>
libcurl (and probably also libssl bc beatsaver is https)

<h3>Build dependencies</h3>
Linux:

cmake

g++

idk, lol. Normal build stuff...
Windows:
git

cmake

Visual Studio Build Tools for C++

OpenSSL ? (need confirmation)

<h2>Build Instructions</h2>
<h3>Linux (Maybe also Mac and BSD)</h3>

```
# Get git, cmake, make, libcurl from your Distro. libcurl might have to be libcurl-dev or something depending on your Distro
git clone https://gitlab.cs.fau.de/yp98ocaw/beatcppver.git
cd beatcppver
./install.sh #(asks for sudo password)
# You can now remove the directory again, if you like
```


That's it. The library is now installed under /usr/lib and /usr/include. And it generates a pkg-config file, but I don't really get that yet.

<h3>Windows</h3>
Install download and install vcpkg somewhere. I will reference this folder as <vcpkg_root> from now on.

I did all of this in git-bash, but you can also use Powershell or something. Even Visual Studio Code actually.

cd <vcpkg_root>

```
./vcpkg.exe integrate install

./vcpkg.exe install nlohmann-json:x64-windows

./vcpkg.exe install curl:x64-windows

# if you want to build the test:
./vcpkg.exe install catch2:x64-windows

cd <folder_where_beatcppver_should_be>

git clone https://gitlab.cs.fau.de/yp98ocaw/beatcppver.git

./configure "-DCMAKE_TOOLCHAIN_FILE=<vcpkg_root>/scripts/buildsystems/vcpkg.cmake"  -DCMAKE_BUILD_TYPE=RELEASE
# In case you forgot to replace the <vcpkg_root> or just called ./configure without any arguments
# it will probably tell you it doesn't find some libraries in the next step.
# In that case you have to remove the build directory again: rm -rf build/
./build.sh
```


<h2>Thanks to:</h2>
nlohmann's json header (gets pulled automatically in cmake)

beatsaver.com

Spotify Web API