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

# Define the directory where plug-ins will be installed.
ADD_DEFINITIONS(-DPLUGIN_PATH="${LIBRARY_OUTPUT_PATH}")

MACRO(QPOASES_PLUGIN NAME)
  ADD_LIBRARY(roboptim-core-plugin-${NAME} MODULE ${NAME}.cc ${HEADERS})
  PKG_CONFIG_USE_DEPENDENCY(roboptim-core-plugin-${NAME} roboptim-core)
  # FIXME: update once qpOASES supports pkg-config
  #PKG_CONFIG_USE_DEPENDENCY(roboptim-core-plugin-${NAME} qpOASES)
  TARGET_LINK_LIBRARIES(roboptim-core-plugin-${NAME} qpOASES)
  SET_TARGET_PROPERTIES(roboptim-core-plugin-${NAME} PROPERTIES
    PREFIX ""
    SOVERSION 0.1.0)
  INSTALL(TARGETS roboptim-core-plugin-${NAME}
    DESTINATION ${ROBOPTIM_CORE_PLUGINDIR})
ENDMACRO()

# QP solver
QPOASES_PLUGIN("qpoases")
