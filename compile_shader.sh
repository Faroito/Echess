#!/bin/zsh

SOURCE_DIR="shaders"
TARGET_DIR="build/shaders"
if [[ "$#" -eq 1 ]]; then
  SOURCE_DIR="${1}/${SOURCE_DIR}"
  TARGET_DIR="${1}/${TARGET_DIR}"
fi

mkdir -p ${TARGET_DIR}

FILES="${SOURCE_DIR}/*"
for file in $FILES; do
  FILENAME=$(echo "$(basename $file)" | sed "s/\..*//")
  EXTENSION=${file##*.}
  TARGET_NAME="${TARGET_DIR}/${FILENAME}_${EXTENSION}.spv"
  if [[ ! -f "${TARGET_NAME}" ]]; then
    if [[  "${EXTENSION}" =~ ^(frag|vert)$ ]]; then
      echo -n "-- Compiling shader from "
      glslangValidator -V "${file}" -o "${TARGET_NAME}"
    fi
  fi
done
