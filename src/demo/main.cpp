#include <nbody/Simulation.h>
#include <nbody/System.h>
#include <nbody/Body.h>
#include <nbody/Vector3.h>
#include <iostream>
#include <fstream>
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <chrono>
#include <thread>

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window* window = SDL_CreateWindow("OpenGL", 100, 100, 1000, 400, SDL_WINDOW_OPENGL);
  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_Event windowEvent;
  glewExperimental = GL_TRUE;
  glewInit();

  Vector3<float> vertices[3];
  glClear(GL_COLOR_BUFFER_BIT);
  GLuint vertexBuffer;
  glGenBuffers(1, &vertexBuffer);
  glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
  glEnable( GL_POINT_SMOOTH );
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  try {
    std::ifstream input{ "resources/nbody/2d-binary-system-simple.txt" };
    nbody::Simulation sim{input};
    for( int i = 0; i < 400; ++i ) {
      std::cout << "==EVOLUTION " << i + 1 << "\n";
      sim.saveRun();
      sim.evolveSystem( 1e4, 0.000001 );
      nbody::System *system = sim.getSystem();
      nbody::Body *bodies = system->getBodies();
      (void)bodies;
      for ( int j = 0; j < 2; j++ ) {
          std::cout << bodies[j].position() << "\n";
          vertices[0] = vertices[1];
          vertices[1] = vertices[2];
          vertices[2] = bodies[j].position();
          glPointSize( 10 );
          glBegin( GL_POINTS );
          glVertex3f( vertices[2].x(), vertices[2].y(), vertices[2].z() );
          glEnd();
          glPointSize( 9 );
          glBegin( GL_POINTS );
          glVertex3f( vertices[1].x(), vertices[1].y(), vertices[1].z() );
          glEnd();
          glPointSize( 8.5 );
          glBegin( GL_POINTS );
          glVertex3f( vertices[0].x(), vertices[0].y(), vertices[0].z() );
          glEnd();
          glFlush();
          
      }
      glEnd();
      int a = 0;
      SDL_GL_SwapWindow(window);
          while (a < 10000000) {
            a+=1;
          }
          glClear(GL_COLOR_BUFFER_BIT);

      // glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_DYNAMIC_DRAW);
      // glEnableVertexAttribArray(0);
      // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
      // glDrawArrays(GL_POINTS, 0, (GLsizei) 2);
      //
    }
    sim.saveRun();
  } catch( const std::exception &e ) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }

  printf("%u\n", vertexBuffer);
  while (true) {
    if (SDL_PollEvent(&windowEvent)) {
      if (windowEvent.type == SDL_QUIT) break;
      if (windowEvent.type == SDL_KEYUP &&
              windowEvent.key.keysym.sym == SDLK_ESCAPE) break;
    }
    SDL_GL_SwapWindow(window);
  }
  SDL_GL_DeleteContext(context);
  SDL_Quit();
  return 0;
}