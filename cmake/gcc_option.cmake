set(CMAKE_C_COMPILER gcc CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER g++ CACHE INTERNAL "C++ Compiler") #GNU 14.2.0

# ########## COMPILER FLAGS ###########
# Object build options
# -O0                   No optimizations, reduce compilation time and make debugging produce the expected results.
# -mthumb               Generat thumb instructions.
# -fno-builtin          Do not use built-in functions provided by GCC.
# -Wall                 Print only standard warnings, for all use Wextra
# -ffunction-sections   Place each function item into its own section in the output file.
# -fdata-sections       Place each data item into its own section in the output file.
# -fomit-frame-pointer  Omit the frame pointer in functions that don’t need one.
# -mabi=aapcs           Defines enums to be a variable sized type.
# -Wno-ignored-qualifiers
# -flto \
# -ffat-lto-objects \
set(COMMON_COMPILER_FLAGS
  " \
  -Wno-int-to-pointer-cast \
  -g \
  -O0 \
  "
)

# -Wuseless-cast \
set(CXX_SPECIFIC_COMPILER_FLAGS
  " \
  -std=c++17 \
  "
)