@echo off
chcp 65001 > nul

:: Clean old build
rmdir /s /q build 2>nul
mkdir build
cd build

:: Build using vcpkg toolchain
cmake .. -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake
cmake --build . --config Release

cd ..
bin\nona.exe
