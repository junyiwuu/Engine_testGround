#!/bin/bash

# Check if glslc is available
if ! command -v glslc &> /dev/null; then
    echo "Warning: glslc not found in PATH. Attempting to locate glslc..."
    GLSLC_PATH=$(find /usr -type f -name glslc 2>/dev/null | head -n 1)
    if [ -n "$GLSLC_PATH" ]; then
        echo "Found glslc at $GLSLC_PATH. Adding its directory to PATH."
        export PATH=$(dirname "$GLSLC_PATH"):$PATH
    else
        echo "Error: glslc not found. Please install glslc or add it to your PATH."
        exit 1
    fi
fi

# Example of compiling shaders using glslc
glslc shaders/shader.vert -o shaders/shader.vert.spv
glslc shaders/shader.frag -o shaders/shader.frag.spv
glslc shaders/skybox.vert -o shaders/skybox.vert.spv
glslc shaders/skybox.frag -o shaders/skybox.frag.spv
glslc shaders/BRDF_LUT.comp -o shaders/BRDF_LUT.comp.spv
glslc shaders/computePrefilIrrad.comp -o shaders/computePrefilIrrad.comp.spv



# /usr/bin/glslc shaders/shader.vert -o shaders/shader.vert.spv
# /usr/bin/glslc shaders/shader.frag -o shaders/shader.frag.spv
# /usr/bin/glslc shaders/skybox.vert -o shaders/skybox.vert.spv
# /usr/bin/glslc shaders/skybox.frag -o shaders/skybox.frag.spv
# /usr/bin/glslc shaders/BRDF_LUT.comp -o shaders/BRDF_LUT.comp.spv
# /usr/bin/glslc shaders/computePrefilIrrad.comp -o shaders/computePrefilIrrad.comp.spv


# if ! command -v glslc &> /dev/null; then
#     echo "Warning: glslc not found in PATH. Attempting to add /usr/local/bin to PATH..."
#     if [ -d "/usr/local/bin" ]; then
#         export PATH="/usr/local/bin:$PATH"
#         echo "Added /usr/local/bin to PATH."
#     else
#         echo "Error: glslc not found and /usr/local/bin does not exist. Please install glslc or add it to your PATH."
#         exit 1
#     fi
# fi
