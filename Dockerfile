FROM debian:sid as builder
WORKDIR /src

RUN apt-get --allow-unauthenticated update -y && \
    apt-get --allow-unauthenticated dist-upgrade  -y && \
    apt-get install -y build-essential cmake ninja-build mold python3 python3-pip nlohmann-json3-dev && \
    pip3 install conan

COPY ["engine/CMakeLists.txt", "engine/conanfile.txt", "/src/engine/"]
RUN conan profile new default --detect && \
    conan profile update settings.compiler.libcxx=libstdc++11 default && \
    mkdir build && \
    conan install engine/conanfile.txt -if build --build=missing && \
    echo "Store conan caches"

# Leave the functional logics beyond conan cache  
COPY ["engine/", "/src/engine/"]
RUN cd build && \
    cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_LINKER=$(which mold) ../engine -G Ninja && \
    ninja -v

FROM debian:unstable-slim
WORKDIR /app

COPY --from=builder --chown=1000:1000 /src/build/bin/engine .
COPY ["template/", "../template/"]

CMD ./engine