#!/usr/bin/env python
import os
import sys

libName = "gdReshade"
interfaceExt = ".gdextension"
gdProjectPath = "demo/"

env = SConscript("./godot-cpp/SConstruct")

# For the reference:
# - CCFLAGS are compilation flags shared between C and C++
# - CFLAGS are for C-specific compilation flags
# - CXXFLAGS are for C++-specific compilation flags
# - CPPFLAGS are for pre-processor flags
# - CPPDEFINES are for pre-processor defines
# - LINKFLAGS are for linking flags

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
	library = env.SharedLibrary(
		f"{gdProjectPath}bin/{libName}.{env['platform']}.{env['target']}.framework/{libName}.{env['platform']}.{env['target']}",
		source=sources,
	)
	else:
	library = env.SharedLibrary(
		f"{gdProjectPath}bin/{libName}{env['suffix']}{env['SHLIBSUFFIX']}",
		source=sources,
	)

Default(library)

# auto generation of .gdextension file

with open(f"src/TEMPLATE{interfaceExt}") as f:
	gdextensionTemplate = f.read().replace("PROJET_NAME",libName)

# delete old interface file, in case was named diferently
for file in os.listdir(gdProjectPath):
	if file.endswith(interfaceExt):
		os.remove(os.path.join(gdProjectPath, file))

with open(f"{gdProjectPath}{libName}{interfaceExt}", "w") as f:
	f.write(gdextensionTemplate)

# NOTE : you still need to name your register_types funstions the right way,
#		notably the library's init function (which MUST be named : {libName}_init )

