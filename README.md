# Hello MLVG

An extremely basic example of using Madrona Labs' MLVG library.

It is based on the example application from the mlvg repository, but further simplified, and using locally built and installed madronalib/mlvg dependencies. I locked the mlvg/madronalib versions using submodules to avoid unexpected issues.

Hopefully this should make getting started with these libraries a bit easier for the uninitiated.

Currently only documented and tested for MacOS environments.

## Building and installing dependencies

### Git submodules

First, you will need to fetch the madronalib and mlvg submodules

    git submodule update --init --recursive
    pushd mlvg
    git submodule update --init --recursive
    popd

### SDL2

Next, you'll need to download and install SDL2. This project was last tested with SL2 2.30.8.

`SDL2.framework` should be installed in `/Library/Frameworks/`

Direct download link: https://github.com/libsdl-org/SDL/releases/download/release-2.30.8/SDL2-2.30.8.dmg
    
### Building madronalib

    mkdir madronalib/build
    pushd madronalib/build
    cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX=../../ext_libs
    make
    make install
    popd

### Building mlvg

    mkdir mlvg/build
    pushd mlvg/build
    cmake .. -GXcode -DCMAKE_INSTALL_PREFIX=../../ext_libs
    xcodebuild -project mlvg.xcodeproj -target mlvg
    xcodebuild -project mlvg.xcodeproj -target install
    popd

# Building Sample 1

    mkdir sample_1/build
    cd sample_1/build
    cmake .. -GXcode
    xcodebuild -project HelloMadrona.xcodeproj -target helloMadrona
    # Finally, run the app!
    ./Debug/helloMadrona

This will fail once as Apple complains about SDL2 being untrusted. Navigate to System Settings -> Privacy and Security and click to Allow SDL2. Now you can try running the application again -- MacOS will bug you again about SDL2, but now you can click "Open Anyway".

Congratulations, you now have a running mlvg test app!
