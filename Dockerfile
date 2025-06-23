FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    g++ \                            
    cmake \                          
    pdftk \                           
    libgl1-mesa-dev \                 
    libglu1-mesa-dev \                
    libsdl2-dev \                  
    libx11-dev \                     
    libxi-dev \                     
    libcurl4-openssl-dev \           
    libglfw3-dev \                
    && apt-get clean && rm -rf /var/lib/apt/lists/*

WORKDIR /workspace

COPY . /workspace

CMD ["bash"]
