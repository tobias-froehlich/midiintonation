
Installing GTest:

sudo aptitude install libgtest-dev
cd /usr/src/googletest/
sudo cmake .
sudo cmake --build . --target install

Building midiintonation:

in midiintonation/build/
rm -r *
cmake ..
make

Testing:

in midisplit/build/test
./Test


