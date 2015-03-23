// Copyright (c) 2015 CNRS
// Authors: Benjamin Chrétien


// This file is part of roboptim-core-plugin-qpoases
// roboptim-core-plugin-qpoases is free software: you can redistribute it
// and/or modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation, either version
// 3 of the License, or (at your option) any later version.

// roboptim-core-plugin-qpoases is distributed in the hope that it will be
// useful, but WITHOUT ANY WARRANTY; without even the implied warranty
// of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Lesser Public License for more details.  You should have
// received a copy of the GNU Lesser General Public License along with
// roboptim-core-plugin-qpoases  If not, see
// <http://www.gnu.org/licenses/>.

#include <cstring>
#include <map>
#include <limits> // epsilon

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/variant/apply_visitor.hpp>

#include <roboptim/core/function.hh>
#include <roboptim/core/problem.hh>
#include <roboptim/core/solver-error.hh>

#include "roboptim/core/plugin/qpoases/qpoases.hh"

namespace roboptim
{
  namespace qpoases
  {
    QPSolver::QPSolver (const problem_t& problem) :
      parent_t (problem),
      n_ (problem.function ().inputSize ()),
      m_ (problem.function ().outputSize ()),
      x_ (n_),
      solverState_ (problem)
    {
      // Initialize x
      x_.setZero ();

      epsilon_ = std::numeric_limits<double>::epsilon ();

      // Initialize solver parameters
      initializeParameters ();
    }

    QPSolver::~QPSolver ()
    {
    }

#define DEFINE_PARAMETER(KEY, DESCRIPTION, VALUE)	\
    do {						\
      parameters ()[KEY].description = DESCRIPTION;	\
      parameters ()[KEY].value = VALUE;			\
    } while (0)

    void QPSolver::initializeParameters ()
    {
      // Clear parameters
      parameters ().clear ();

      // Shared parameters
      DEFINE_PARAMETER ("max-iterations", "number of iterations", 2000);

      // TODO: qpOASES-specific parameters
    }

    void QPSolver::solve ()
    {
      using namespace Eigen;

      // Load optional starting point
      if (problem ().startingPoint ())
	{
	  x_ = *(problem ().startingPoint ());
	}

      // TODO: Create qpOASES solver

      // TODO: Solve problem with initial x
    }

  } // namespace qpoases
} // end of namespace roboptim

extern "C"
{
  using namespace roboptim::qpoases;
  typedef QPSolver::parent_t solver_t;

  ROBOPTIM_DLLEXPORT unsigned getSizeOfProblem ();
  ROBOPTIM_DLLEXPORT const char* getTypeIdOfConstraintsList ();
  ROBOPTIM_DLLEXPORT solver_t* create (const QPSolver::problem_t& pb);
  ROBOPTIM_DLLEXPORT void destroy (solver_t* p);

  ROBOPTIM_DLLEXPORT unsigned getSizeOfProblem ()
  {
    return sizeof (solver_t::problem_t);
  }

  ROBOPTIM_DLLEXPORT const char* getTypeIdOfConstraintsList ()
  {
    return typeid (solver_t::problem_t::constraintsList_t).name ();
  }

  ROBOPTIM_DLLEXPORT solver_t* create (const QPSolver::problem_t& pb)
  {
    return new QPSolver (pb);
  }

  ROBOPTIM_DLLEXPORT void destroy (solver_t* p)
  {
    delete p;
  }
}
