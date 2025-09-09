# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/BitBand.release+ARMCLANG")
  file(MAKE_DIRECTORY "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/BitBand.release+ARMCLANG")
endif()
file(MAKE_DIRECTORY
  "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/1"
  "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/BitBand.release+ARMCLANG"
  "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/BitBand.release+ARMCLANG/tmp"
  "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/BitBand.release+ARMCLANG/src/BitBand.release+ARMCLANG-stamp"
  "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/BitBand.release+ARMCLANG/src"
  "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/BitBand.release+ARMCLANG/src/BitBand.release+ARMCLANG-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/BitBand.release+ARMCLANG/src/BitBand.release+ARMCLANG-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "D:/Projects/M4/M480/Git/BSP/bsp/SampleCode/CortexM4/BitBand/VSCode/tmp/BitBand.release+ARMCLANG/src/BitBand.release+ARMCLANG-stamp${cfgdir}") # cfgdir has leading slash
endif()
