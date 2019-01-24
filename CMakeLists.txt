# Initialize the package, specifing its name, used later as ${PROJECT_NAME}
hyro_init_package(signal_generator VERSION 0.0.1)
# Here we search and include the package we depend on
#include ( FindPkgConfig  )
#find_package ( Qt4 COMPONENTS QtCore QtGui QtOpenGl )
#find_package ( QWT )

hyro_find_package(hyro_utils REQUIRED)
hyro_find_package(hyro_msgs REQUIRED)
hyro_find_package(hyro_widgets REQUIRED)

#include(${QT_USE_FILE} )
#add_definitions(${QT_DEFINITIONS})

## Specify additional locations of header files
## Your package locations should be listed before other locations
set(SIGNAL_GENERATOR_HEADERS
  include/hyro/DigitalConverterComponent.h
  include/hyro/SignalGeneratorComponent.h
  src/internal/SignalGenerator.h
  src/internal/Thresholding.h
  include/hyro/msgs/SignalMsgs.h
  include/hyro/msgs/SignalMsgs.proto.h
)
set(SIGNAL_GENERATOR_SOURCES
  src/components/DigitalConverterComponent.cpp
  src/components/SignalGeneratorComponent.cpp
  src/internal/SignalGenerator.cpp
  src/internal/Thresholding.cpp
)

include_directories(
  ${PROJECT_SOURCE_DIR}/src
)

hyro_add_library(
    ${PROJECT_NAME}_components
  HEADERS
    ${SIGNAL_GENERATOR_HEADERS}
  SOURCES
    ${SIGNAL_GENERATOR_SOURCES}
  DEPENDS_ON
    hyro_utils
    hyro_msgs
    hyro_widgets
  )   

hyro_compile_messages(
  ${PROJECT_NAME}_components
  SOURCES
    msgs/hyro/msgs/SignalMsgs.proto
  )

hyro_add_executable(
    ${PROJECT_NAME}
  SOURCES
    src/examples/signal_generator.cpp
  DEPENDS_ON
    ${PROJECT_NAME}_components
)
hyro_install_package(
    ${PROJECT_NAME}
  LIBS
    ${PROJECT_NAME}_components
  EXES
    ${PROJECT_NAME}
)

hyro_add_gtest(${PROJECT_NAME}
  SOURCES 
    tests/test_signal_generator.cpp
  DEPENDS_ON
    ${PROJECT_NAME}_components
)