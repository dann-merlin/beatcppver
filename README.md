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

Visual Studio Build Tools

OpenSSL ? (need confirmation)

<h2>Build Instructions</h2>
<h3>Linux (Maybe also Mac and BSD)</h3>

```
./configure.sh

./build.sh

./install.sh #(asks for sudo password)
```


That's it. The library is now installed under /usr/lib and /usr/include. And it generates a pkg-config file, but I don't really get that yet.

<h3>Windows</h3>

<h2>Thanks to:</h2>
nlohmann's json header (gets pulled automatically in cmake)
beatsaver.com
Spotify Web API