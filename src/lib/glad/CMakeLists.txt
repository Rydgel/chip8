project(glad)

set(HEADER_FILES glad.h)
set(SOURCE_FILES glad.c)

add_library(glad STATIC ${SOURCE_FILES} ${HEADER_FILES})