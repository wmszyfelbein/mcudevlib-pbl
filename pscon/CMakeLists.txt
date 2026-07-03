cmake_minimum_required(VERSION 3.6)
project("PiUE Simple Console" VERSION 1.0)
add_executable(pscon
    pscon.h
    pscon_conf.h
    pscon.c
    pscon_test.c
)
