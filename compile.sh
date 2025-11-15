#!/bin/bash

# Check if glslc is available
if ! command -v glslc &> /dev/null; then
    echo "Error: glslc not found. Please ensure it is installed and available in your PATH."
    exit 1
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
