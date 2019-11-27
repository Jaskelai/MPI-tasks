# !!SET YOUR PROJECT NAME HERE (instead of OMP-tasks)!!
project(OMP-tasks)

cmake_minimum_required(VERSION 3.6)

# !!SET YOUR PROJECT NAME HERE (instead of OMP-tasks)!!
add_executable(OMP-tasks mpi/launcherMPI.cpp mpi/taskMPI1.cpp mpi/taskMPI1.h mpi/taskMPI2.cpp mpi/taskMPI2.h mpi/taskMPI3.cpp mpi/taskMPI3.h mpi/taskMPI4.cpp mpi/taskMPI4.h mpi/taskMPI5.cpp mpi/taskMPI5.h mpi/taskMPI6.cpp mpi/taskMPI6.h mpi/taskMPI7.cpp mpi/taskMPI7.h mpi/taskMPI8.cpp mpi/taskMPI8.h mpi/taskMPI9.cpp mpi/taskMPI9.h mpi/taskMPI10.cpp mpi/taskMPI10.h mpi/taskMPI11.cpp mpi/taskMPI11.h)

find_package(MPI REQUIRED)
include_directories(${MPI_INCLUDE_PATH})

SET(CMAKE_C_COMPILER mpicc)

set(CMAKE_CXX_COMPILE_FLAGS ${CMAKE_CXX_COMPILE_FLAGS} ${MPI_COMPILE_FLAGS})
set(CMAKE_CXX_LINK_FLAGS ${CMAKE_CXX_LINK_FLAGS} ${MPI_LINK_FLAGS})
target_link_libraries(OMP-tasks ${MPI_LIBRARIES})