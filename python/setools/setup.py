#!/usr/bin/env python

# Author: Thomas Liu <tliu@redhat.com>
import os
from distutils.core import setup, Extension
LIBS=["apol", "qpol"]

try:
    inc=os.getenv("INCLUDES").split(" ")    
    INCLUDES=[x[2:] for x in inc]
    LIBDIRS=["/".join(x.split("/")[:-1]) for x in os.getenv("LIBS").split()]
except:
    INCLUDES=""
    LIBDIRS=""

extension_sesearch = Extension("setools._sesearch", [ "sesearch.c"])
extension_sesearch.include_dirs=INCLUDES
extension_sesearch.libraries=LIBS
extension_sesearch.library_dirs=LIBDIRS
extension_seinfo = Extension("setools._seinfo", [ "seinfo.c"])
extension_seinfo.include_dirs=INCLUDES
extension_seinfo.libraries=LIBS
extension_seinfo.library_dirs=LIBDIRS

setup(name = "setools", version="1.0", description="Python setools bindings", author="Thomas Liu", author_email="tliu@redhat.com", ext_modules=[extension_sesearch, extension_seinfo], packages=["setools"])
