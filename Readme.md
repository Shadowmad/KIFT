# Installation Guide
## Dependencies
* PocketSphinx

## Dependency Installation
In this section we will help you install dependencies with ease. Before you process any further, make sure that you have following prerequisites:
- gcc
- automake
- autoconf
- libtool
- bison
- swig (at least version 2.0)
- Python development package
- Pulseaudio development package.

#### To test if you are missing any of the stated systems, run following commands for each:
    $> gcc -v
    $> automake --version
    $> autoconf --version
    $> libtool -V
    $> bison -V
    $> swig -version
    $> python --version
    $> pulseaudio --version

If you are missing any of the following after testing, use package manager of your system to intsall them

##### For MacOS(Hish Sierra)
    $> brew install <all missing pakages>

    Usually missing ones:
    $> brew install swig pulseaudio

------------

### PocketSphinx
To install PocketSphinx first you need to install SphinxCore. To do so follow below steps.
#### SphinxBase Installation
- Git clone https://github.com/cmusphinx/sphinxbase.git to any directory.
- CD into spinxbase directory.
- After that completes, do sh autogen.sh
	- By default autogen will configure everything into /var/local/, but you can change that using --prefix. For example: sh autogen.sh --prefix=your_directory.
	- If you don't have sudo access and on MacOS install everything into .brew folder,
	for example: sh autogen.sh --prefix=$HOME/.brew
- After autogen.sh completes run ./configure
	- If you ran autogen with prefix, use same logic for this step as well.
	- For example, ./configure --prefix=$HOME/.brew
- After that is done, perform make
- After make completes do make install.
- Leave directory one level up

#### PocketSphinx
- Git clone https://github.com/cmusphinx/pocketsphinx.git
	- Make sure you use same folder where SphinxBase folder is located.
- Enter pocketsphinx directory
- Do: sh autogen.sh
	- Note: By default this will install into /var/local/. If you need to change directory use --prefix.
	- For example, sh autogen.sh --prefix=$HOME/.brew
- Then ./configure
	- Note: This operation behaves exatcly the same as autogen and will try to install intp /var/local. To change this use --prefix
	- For example: ./configure --prefix=$HOME/.brew
- Then run make
- Optional: make check
- After all is done run: make install

#### libwebsockets
- brew install libwebsockets

#### How to Launch
- cd server/cserver/
- make
- ./cserver/launch.sh
