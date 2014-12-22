FILE(GLOB SRC *.cc;*.h)
source_group("" FILES ${SRC})
add_executable(bisquit ${SRC})