import sys
import os
import subprocess
import shutil
from re import search
from pathlib import Path
import time
import shutil
import argparse
import pathlib

def LOG(log):
    print("[RUN]:    - " + log + " -")
    
def start():
    choices = [
        "[ commands ]",
        "0. Build release",
        "1. Clean build release",
        "2. Delete build folder",
        "3. Run program",
        "4. Build and run"
    ]

    for x in choices:
        print(x)
    print("----------")
    inp = str(input(">>>   Run command: "))
    print("")
    input_resolver(inp)

def run_program(change_to_build_dir = True):
    if(change_to_build_dir):
        os.chdir("build")
    run_cmd = "classy.exe"
    subprocess.run(run_cmd, shell=True)

def build(with_cmake=True, clean = True, debug = False):
    cwd = os.getcwd()
    build_folder = str(cwd) + str("/build")
    if folder_exists(build_folder):
        os.chdir(build_folder)
        LOG(">>> Building...")
        if(with_cmake == True):
            run_cmake(clean, debug)
        run_make()

### Cmake
def run_cmake(clean = True, debug = False):
    LOG("Cmake running...")
    if(clean):
        if(debug):
            cmake_cmd = 'cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_UNIT_TESTS=ON -G "MinGW Makefiles" && cmake --build .'
        else:
            cmake_cmd = 'cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DBUILD_UNIT_TESTS=OFF -G "MinGW Makefiles"'
        subprocess.run(cmake_cmd, shell=True)
    else:
        cmake_cmd = 'cmake ..'
        subprocess.run(cmake_cmd, shell=True)

def run_make():
    LOG("make running...")
    # make_cmd = "VERBOSE=1 make"
    make_cmd = "cmake --build ."
    subprocess.run(make_cmd, shell=True)

### Folder ###
def folder_exists(dir):
    if os.path.exists(dir):
        LOG("DIRECTORY EXISTS:")
        LOG(str(dir))
        return True
    else:
        LOG("DIRECTORY DOESNT EXIST!")
        LOG(str(dir))          
        return False

def clear_folder(dir):
    LOG("Clearing directory...")
    if folder_exists(dir):
        for files in os.listdir(dir):
            path = os.path.join(dir, files)
            try:
                shutil.rmtree(path)
            except OSError:
                os.remove(path)  

def delete_folder(dir):
    clear_folder(dir)
    LOG("Deleting this folder...")
    os.chdir(str(Path(dir).parents[0]))
    os.rmdir(dir)
    LOG("------------------ ")

### Input
def input_resolver(input_):
    cwd = os.getcwd()
    build_folder = str(cwd) + str("/build")  # go into build folder

    if folder_exists(build_folder):
        LOG("Build folder exists.")
    else:
        LOG("Build folder doesn't exists...")
        LOG("Creating build folder...")
        os.makedirs("build")
    if (input_ == "0" or input_ == ""):
        build(with_cmake=False, clean = False)
    if(input_ == "1"):
        delete_folder(build_folder)
        os.makedirs("build")
        build()
    if(input_ == "2"):
        delete_folder(build_folder)
    if(input_ == "3"):
        run_program(True)
    if(input_ == "4"):
        build(with_cmake=False, clean = False)
        run_program(False)


# main function
if __name__ == "__main__":
    start()
    print("")
    LOG(">> Script done <<")
    print("")
