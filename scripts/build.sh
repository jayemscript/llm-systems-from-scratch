# build.sh
#!/bin/bash
mkdir -p build
cd build
cmake ..
cmake --build .
# chmod +x scripts/build.sh