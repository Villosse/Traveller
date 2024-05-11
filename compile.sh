#!/usr/bin/env bash

source "./.env"

new_line="set(EXECUTABLE_OUTPUT_PATH ${PROJECT_OUTPUT_DIR})"
sed -i "11s,.*,$new_line," CMakeLists.txt

mkdir -p "${PROJECT_OUTPUT_DIR}/build"

cd "${PROJECT_OUTPUT_DIR}/build"

#cmake ..

#make

if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable is located at: ${PROJECT_OUTPUT_DIR}/${PROJECT_NAME}"
else
    echo "Compilation failed."
fi

cd "${PROJECT_OUTPUT_DIR}"
