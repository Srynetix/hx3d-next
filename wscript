APP_NAME = "Engine"

def options(opt):
    opt.load("compiler_cxx")

def configure(cnf):
    cnf.load("compiler_cxx")

def build(bld):
    bld(features="cxx cxxprogram", source="Engine/main.cpp", target=APP_NAME)
