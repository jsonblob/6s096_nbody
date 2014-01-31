#ifndef _NBODY_INTEGRATOR_H
#define _NBODY_INTEGRATOR_H

#include <nbody/Vector3.h>
#include <nbody/Body.h>

namespace nbody {

	class Integrator {
	public:
		virtual void integrate( size_t nBodies, Body *body, float dt, float dampingFactor ) = 0;
    virtual ~Integrator() {};
	};

  class BasicIntegrator : public Integrator {
  public:
    BasicIntegrator() {};
    void integrate( size_t nBodies, Body *body, float dt, float dampingFactor );
  };

  class TrapIntegrator : public Integrator {
  public:
    TrapIntegrator() {};
    void integrate( size_t nBodies, Body *body, float dt, float dampingFactor );
  };
}

#endif // _NBODY_INTEGRATOR_H