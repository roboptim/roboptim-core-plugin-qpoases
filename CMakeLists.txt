# Copyright (c) 2015 CNRS
# Authors: Benjamin Chrétien
#
#
# This file is part of roboptim-core-plugin-qpoases
# roboptim-core-plugin-qpoases is free software: you can redistribute it
# and/or modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation, either version
# 3 of the License, or (at your option) any later version.
#
# roboptim-core-plugin-qpoases is distributed in the hope that it will be
# useful, but WITHOUT ANY WARRANTY; without even the implied warranty
# of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Lesser Public License for more details.  You should have
# received a copy of the GNU Lesser General Public License along with
# roboptim-core-plugin-qpoases  If not, see
# <http://www.gnu.org/licenses/>.

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#SET(CXX_DISABLE_WERROR TRUE)
INCLUDE(cmake/base.cmake)
INCLUDE(cmake/boost.cmake)
INCLUDE(cmake/eigen.cmake)

SET(PROJECT_NAME roboptim-core-plugin-qpoases)
SET(PROJECT_DESCRIPTION "RobOptim plugin for qpOASES.")
SET(PROJECT_URL "http://github.com/roboptim/roboptim-core-plugin-qpoases")

SET(PKG_CONFIG_ADDITIONAL_VARIABLES plugindir ${PKG_CONFIG_ADDITIONAL_VARIABLES})
SETUP_PROJECT()

# Declare headers
SET(${PROJECT_NAME}_HEADERS
  include/roboptim/core/plugin/qpoases/qpoases.hh
  )

# Search for dependencies.
SET(BOOST_COMPONENTS date_time filesystem system unit_test_framework)
SEARCH_FOR_BOOST()

ADD_REQUIRED_DEPENDENCY("eigen3 >= 3.2.0")
ADD_REQUIRED_DEPENDENCY("roboptim-core >= 3.0")

# FIXME: update once qpOASES supports pkg-config.
#ADD_REQUIRED_DEPENDENCY("qpoases")
FIND_PATH(QPOASES_INCLUDE_DIR qpOASES/QProblem.hpp
    /opt/local/include
    /usr/local/include
    /usr/include
    )
MESSAGE("-- qpOASES include directory: ${QPOASES_INCLUDE_DIR}")
FIND_LIBRARY(QPOASES_LIBRARY
    NAMES qpOASES
    PATHS
    /opt/local/lib/
    /usr/local/lib/
    /usr/lib
    )
MESSAGE("-- qpOASES library: ${QPOASES_LIBRARY}")

OPTION(DISABLE_TESTS "Disable test programs" OFF)

ADD_SUBDIRECTORY(src)

IF(NOT DISABLE_TESTS)
  ADD_SUBDIRECTORY(tests)
ELSE()
  MESSAGE(WARNING
    "Tests should only be disabled for speficic cases. Do it at your own risk.")
ENDIF()

HEADER_INSTALL("${HEADERS}")

SETUP_PROJECT_FINALIZE()
