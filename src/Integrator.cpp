#include <nbody/Integrator.h>
#include <nbody/Vector3.h>
#include <iostream>

namespace nbody {

	void BasicIntegrator::integrate( size_t nBodies, Body *body, float dt, float dampingFactor ) {
	  Vector3f r, v, a;
    for( size_t i = 0; i < nBodies; ++i ) {
      r = body[i].position();
      v = body[i].velocity();
      a = body[i].force();

      v = v + ( a * dt );
      v = v * dampingFactor;
      r = r + v * dt;

      body[i].position() = r;
      body[i].velocity() = v;
    }
	}

  void TrapIntegrator::integrate( size_t nBodies, Body *body, float dt, float dampingFactor ) {
    Vector3f r, v, a;
    for( size_t i = 0; i < nBodies; ++i ) {
      r = body[i].position();
      v = body[i].velocity();
      a = body[i].force();

      v = ( v + ( v + a * dt ) ) / 2.0f;
      v = v * dampingFactor;
      r = ( r + ( r + v * dt ) ) / 2.0f;

      body[i].position() = r;
      body[i].velocity() = v;
    }
  }
}