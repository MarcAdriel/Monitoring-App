# Use Ubuntu as the base image
FROM ubuntu:22.04

# Set working directory
WORKDIR /app

# Install dependencies (including nlohmann-json3-dev)
RUN apt-get update && apt-get install -y \
    g++ libpqxx-dev libpq-dev pkg-config git curl libcurl4-openssl-dev meson python3-pip \
    nlohmann-json3-dev \
    && rm -rf /var/lib/apt/lists/*

# Install Ninja using pip (fix for ARM64)
RUN pip3 install ninja

# Install the latest CMake manually
RUN curl -fsSL https://github.com/Kitware/CMake/releases/download/v3.27.7/cmake-3.27.7-linux-aarch64.sh -o cmake.sh \
    && chmod +x cmake.sh \
    && ./cmake.sh --prefix=/usr/local --skip-license \
    && rm cmake.sh

# Verify CMake version
RUN cmake --version

# Build and Install Pistache manually (Using Meson)
RUN git clone https://github.com/pistacheio/pistache.git \
    && cd pistache \
    && git submodule update --init \
    && meson setup build --prefix=/usr \
    && ninja -C build \
    && ninja -C build install \
    && cd .. && rm -rf pistache  # Clean up

# Copy all project files
COPY . .

# Build the project
RUN cmake .
RUN make

# Expose the API port
EXPOSE 8080

# Run the application
CMD ["./CRUD"]
