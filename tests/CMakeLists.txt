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


# Prepare test suite
SET(PLUGIN_PATH "${CMAKE_BINARY_DIR}/src")
INCLUDE(shared-tests/tests.cmake)

# QP test problems
SET(SOLVER_NAME "qpoases")
SET(FUNCTION_TYPE ::roboptim::EigenMatrixDense)
SET(PROGRAM_SUFFIX "")
SET(COST_FUNCTION_TYPE ::roboptim::GenericNumericQuadraticFunction)
SET(CONSTRAINT_TYPE_1 ::roboptim::GenericNumericLinearFunction)
BUILD_QP_PROBLEMS()
