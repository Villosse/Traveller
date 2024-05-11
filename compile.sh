#!/usr/bin/env bash

source "./.env"

if [[ $PROJECT_NAME =~ [^a-zA-Z0-9_] ]]; then
  echo "error : PROJECT_NAME contains a forbidden symbol"
  exit 1
fi

new_line="set(EXECUTABLE_OUTPUT_PATH ${PROJECT_OUTPUT_DIR})"
sed -i "11s,.*,$new_line," CMakeLists.txt

new_line="add_executable(${PROJECT_NAME} src/main.cpp)"
sed -i "8s,.*,$new_line," CMakeLists.txt

mkdir -p "${PROJECT_OUTPUT_DIR}/build"

cd "${PROJECT_OUTPUT_DIR}/build"

cmake ..

make

if [ $? -eq 0 ]; then
    echo "Compilation successful. Executable is located at: ${PROJECT_OUTPUT_DIR}/${PROJECT_NAME}"
else
    echo "Compilation failed."
fi

cd "${PROJECT_OUTPUT_DIR}"
