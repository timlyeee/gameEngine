arch=$1
platform=x64

cmake -A"${arch}"\
    -B"out/${arch}"\
    -DPLATFORM_WINDOWS=ON\
    -DPLATFORM_MAC=OFF