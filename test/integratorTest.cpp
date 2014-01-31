#include <nbody/Vector3.h>
#include <nbody/Integrator.h>
#include <nbody/Body.h>
#include <gtest/gtest.h>

TEST( integratorTest, noMotion ) {
  nbody::Body bodies[1];
  auto position = Vector3f{ 0, 0, 0 };
  auto velocity = Vector3f{ 0, 0, 0};
  auto force = Vector3f{ 0, 0, 0};
  nbody::Body body = nbody::Body{ position, velocity, force, 1 };

  bodies[0] = body;

  nbody::Integrator *integrator = new nbody::BasicIntegrator();

  integrator->integrate( 1, bodies, 0.000001, 1.0f );

  ASSERT_FLOAT_EQ( bodies[0].position().x() , position.x() );
  ASSERT_FLOAT_EQ( bodies[0].position().y() , position.y() );
  ASSERT_FLOAT_EQ( bodies[0].position().z() , position.z() );

  ASSERT_FLOAT_EQ( bodies[0].velocity().x() , velocity.x() );
  ASSERT_FLOAT_EQ( bodies[0].velocity().y() , velocity.y() );
  ASSERT_FLOAT_EQ( bodies[0].velocity().z() , velocity.z() );

  ASSERT_FLOAT_EQ( bodies[0].force().x() , force.x() );
  ASSERT_FLOAT_EQ( bodies[0].force().y() , force.y() );
  ASSERT_FLOAT_EQ( bodies[0].force().z() , force.z() );
}

TEST( integratorTest, simpleMotion1 ) {
  nbody::Body bodies[1];
  auto position = Vector3f{ 0, 0, 0 };
  auto velocity = Vector3f{ 0, 0, 0};
  auto force = Vector3f{ 1, 1, 1};
  nbody::Body body = nbody::Body{ position, velocity, force, 1 };

  bodies[0] = body;

  nbody::Integrator *integrator = new nbody::BasicIntegrator();

  integrator->integrate( 1, bodies, 1, 1.0f );

  ASSERT_FLOAT_EQ( bodies[0].position().x() , 1 );
  ASSERT_FLOAT_EQ( bodies[0].position().y() , 1 );
  ASSERT_FLOAT_EQ( bodies[0].position().z() , 1 );

  ASSERT_FLOAT_EQ( bodies[0].velocity().x() , 1 );
  ASSERT_FLOAT_EQ( bodies[0].velocity().y() , 1 );
  ASSERT_FLOAT_EQ( bodies[0].velocity().z() , 1 );

  ASSERT_FLOAT_EQ( bodies[0].force().x() , 1 );
  ASSERT_FLOAT_EQ( bodies[0].force().y() , 1 );
  ASSERT_FLOAT_EQ( bodies[0].force().z() , 1 );
}

TEST( integratorTest, simpleMotion10 ) {
  nbody::Body bodies[1];
  auto position = Vector3f{ 0, 0, 0 };
  auto velocity = Vector3f{ 0, 0, 0};
  auto force = Vector3f{ 1, 1, 1};
  nbody::Body body = nbody::Body{ position, velocity, force, 1 };

  bodies[0] = body;

  nbody::Integrator *integrator = new nbody::BasicIntegrator();

  integrator->integrate( 1, bodies, 10, 1.0f );

  ASSERT_FLOAT_EQ( bodies[0].position().x() , 100 );
  ASSERT_FLOAT_EQ( bodies[0].position().y() , 100 );
  ASSERT_FLOAT_EQ( bodies[0].position().z() , 100 );

  ASSERT_FLOAT_EQ( bodies[0].velocity().x() , 10 );
  ASSERT_FLOAT_EQ( bodies[0].velocity().y() , 10 );
  ASSERT_FLOAT_EQ( bodies[0].velocity().z() , 10 );

  ASSERT_FLOAT_EQ( bodies[0].force().x() , 1 );
  ASSERT_FLOAT_EQ( bodies[0].force().y() , 1 );
  ASSERT_FLOAT_EQ( bodies[0].force().z() , 1 );
}