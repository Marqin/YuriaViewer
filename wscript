#!/usr/bin/env python

import sys
top = "."
out = "bin"

C_SOURCES = ["main.c", "shaders.c", "utils.c", "callbacks.c"]

from waflib.Tools.compiler_c import c_compiler
c_compiler["win32"] = ["gcc"]

def options(opt):
    opt.load("compiler_c")

def configure(conf):
    conf.load("compiler_c")
    conf.env.CFLAGS = ["-pedantic", "-Wall", "-Wextra", "-Wshadow",
                       "-Wstrict-overflow", "-Werror", "-std=c99",
                       "-O2", "-fno-strict-aliasing"]
    if sys.platform == "darwin":
        conf.env.FRAMEWORK = ["OpenGL", "Cocoa", "IOKit"]
    conf.check_cfg(package="glew", args=['--cflags', '--libs'], uselib_store='GLEW')
    conf.check_cfg(package="glfw3", args=['--cflags', '--libs'], uselib_store='GLFW3')

def build(bld):
    bld.program(features="c cprogram", source=C_SOURCES, target = "YuriaViewer", use = ["GLFW3", "GLEW"])
