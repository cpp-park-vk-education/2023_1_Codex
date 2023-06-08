project(ppocr CXX C)
cmake_minimum_required(VERSION 3.14)

option(WITH_MKL "Compile demo with MKL/OpenBlas support, default use MKL." ON)
option(WITH_GPU "Compile demo with GPU/CPU, default use CPU." OFF)
option(WITH_STATIC_LIB "Compile demo with static/shared library, default use static." OFF)
option(WITH_TENSORRT "Compile demo with TensorRT." OFF)

SET(PADDLE_LIB "/mnt/c/users/user/prog/PaddleOCR/deploy/cpp_infer/Paddle/build/paddle_inference_install_dir" CACHE PATH "Location of libraries")
SET(OPENCV_DIR "/usr/lib/x86_64-linux-gnu/cmake/opencv4" CACHE PATH "Location of libraries")
SET(CUDA_LIB "/usr/local/cuda-11.0/bin" CACHE PATH "Location of libraries")
SET(CUDNN_LIB "/usr/local/cuda/lib64" CACHE PATH "Location of libraries")
SET(TENSORRT_DIR "" CACHE PATH "Compile demo with TensorRT")

set(DEMO_NAME "ppocr")

macro(safe_set_static_flag)
    foreach (flag_var
            CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
            CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
        if (${flag_var} MATCHES "/MD")
            string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
        endif (${flag_var} MATCHES "/MD")
    endforeach (flag_var)
endmacro()

if (WITH_MKL)
    ADD_DEFINITIONS(-DUSE_MKL)
endif ()

find_package(OpenCV REQUIRED PATHS /usr/lib/x86_64-linux-gnu/cmake/opencv4 NO_DEFAULT_PATH)
include_directories("${PADDLE_LIB}/paddle/include")
link_directories("${PADDLE_LIB}/paddle/lib")

include_directories(${OpenCV_INCLUDE_DIRS})

if (WITH_MKL)
    set(FLAG_OPENMP "-fopenmp")
endif ()

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${FLAG_OPENMP} -std=c++11")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

find_package(REQUIRED CONFIG PATHS "${PADDLE_LIB}/third_party/install/onnxruntime/include")

include_directories("${PADDLE_LIB}/third_party/install/protobuf/include")
include_directories("${PADDLE_LIB}/third_party/install/glog/include")
include_directories("${PADDLE_LIB}/third_party/install/gflags/include")
include_directories("${PADDLE_LIB}/third_party/install/xxhash/include")
include_directories("${PADDLE_LIB}/third_party/install/zlib/include")
include_directories("${PADDLE_LIB}/third_party/install/onnxruntime/include")
include_directories("${PADDLE_LIB}/third_party/install/paddle2onnx/include")
include_directories("${PADDLE_LIB}/third_party/boost")
include_directories("${PADDLE_LIB}/third_party/eigen3")

include_directories("${CMAKE_SOURCE_DIR}/")

link_directories("${PADDLE_LIB}/third_party/install/zlib/lib")

link_directories("${PADDLE_LIB}/third_party/install/protobuf/lib")
link_directories("${PADDLE_LIB}/third_party/install/glog/lib")
link_directories("${PADDLE_LIB}/third_party/install/gflags/lib")
link_directories("${PADDLE_LIB}/third_party/install/xxhash/lib")
link_directories("${PADDLE_LIB}/third_party/install/onnxruntime/lib")
link_directories("${PADDLE_LIB}/third_party/install/paddle2onnx/lib")
link_directories("${PADDLE_LIB}/paddle/lib")


if (WITH_MKL)
    include_directories("${PADDLE_LIB}/third_party/install/mklml/include")

    set(MATH_LIB ${PADDLE_LIB}/third_party/install/mklml/lib/libmklml_intel${CMAKE_SHARED_LIBRARY_SUFFIX}
            ${PADDLE_LIB}/third_party/install/mklml/lib/libiomp5${CMAKE_SHARED_LIBRARY_SUFFIX})
    execute_process(COMMAND cp -r ${PADDLE_LIB}/third_party/install/mklml/lib/libmklml_intel${CMAKE_SHARED_LIBRARY_SUFFIX} /usr/lib)
    set(MKLDNN_PATH "${PADDLE_LIB}/third_party/install/mkldnn")
    if (EXISTS ${MKLDNN_PATH})
        include_directories("${MKLDNN_PATH}/include")

        set(MKLDNN_LIB ${MKLDNN_PATH}/lib/libmkldnn.so.0)
    endif ()
else ()
    set(MATH_LIB ${PADDLE_LIB}/third_party/install/openblas/lib/libopenblas${CMAKE_STATIC_LIBRARY_SUFFIX})
endif ()

# Note: libpaddle_inference_api.so/a must put before libpaddle_inference.so/a
if (WITH_STATIC_LIB)
    set(DEPS ${PADDLE_LIB}/paddle/lib/libpaddle_inference${CMAKE_STATIC_LIBRARY_SUFFIX})
else ()
    set(DEPS ${PADDLE_LIB}/paddle/lib/libpaddle_inference${CMAKE_SHARED_LIBRARY_SUFFIX})
endif ()

set(DEPS ${DEPS}
        ${MATH_LIB} ${MKLDNN_LIB}
        )
if (EXISTS "${PADDLE_LIB}/third_party/install/snappystream/lib")
    set(DEPS ${DEPS} snappystream)
endif ()
if (EXISTS "${PADDLE_LIB}/third_party/install/snappy/lib")
    set(DEPS ${DEPS} snappy)
endif ()

set(EXTERNAL_LIB "-ldl -lrt -lgomp -lz -lm -lpthread")
set(DEPS ${DEPS} ${EXTERNAL_LIB})

set(DEPS ${DEPS} ${OpenCV_LIBS})

include(FetchContent)
include(external-cmake/auto-log.cmake)
include_directories(${FETCHCONTENT_BASE_DIR}/extern_autolog-src)
include_directories(include)

set(SRCS /
        src/utility.cpp /
        src/preprocess_op.cpp /
        src/ocr_cls.cpp /
        src/ocr_rec.cpp /
        src/paddleocr.cpp /
        src/ocr.cpp /
        )

add_executable(${DEMO_NAME} ${SRCS} src/main.cpp)
target_link_libraries(${DEMO_NAME} ${DEPS})

add_library(ppocrLib STATIC ${SRCS})

target_link_libraries(ppocrLib ${DEPS})

install(TARGETS ppocrLib
        EXPORT ppocrLibTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        )

install(EXPORT ppocrLibTargets
        FILE ppocrLibConfig.cmake
        NAMESPACE ppocrLib::
        DESTINATION lib/cmake/ppocrLib
        )
