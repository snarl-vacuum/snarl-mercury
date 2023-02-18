To install Catch2:
cd ~/dev/
git clone https://github.com/catchorg/Catch2.git
cd Catch2/
cmake -Bbuild -H. -DBUILD_TESTING=OFF
sudo cmake --build build/ --target install

To build mercury:
cd ~/dev/c++/mercury/
mkdir build/
cd build/
cmake ..
make

Debug mercury:
cd ~/dev/c++/mercury/
mkdir Debug/
cd Debug/
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

Release mercury:
cd ~/dev/c++/mercury/
mkdir Debug/
cd Debug/
cmake -DCMAKE_BUILD_TYPE=Release ..
make
