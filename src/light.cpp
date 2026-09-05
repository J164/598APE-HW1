
#include "light.h"
#include "shape.h"
#include "camera.h"
      
Light::Light(const Vector & cente, unsigned char* colo) : center(cente){
   color = colo;
}

unsigned char* Light::getColor(unsigned char a, unsigned char b, unsigned char c){
   unsigned char* r = (unsigned char*)malloc(sizeof(unsigned char)*3);
   r[0] = a;
   r[1] = b;
   r[2] = c;
   return r;
}

Autonoma::Autonoma(const Camera& c): camera(c){
   depth = 10;
   skybox = BLACK;
}

Autonoma::Autonoma(const Camera& c, Texture* tex): camera(c){
   depth = 10;
   skybox = tex;
}

void Autonoma::addShape(Shape* r){
   shapes.push_back(r);
}

void Autonoma::addLight(Light* r){
   lights.push_back(r);
}

void getLight(double* tColor, Autonoma* aut, const Vector& point, const Vector& norm, unsigned char flip){
   tColor[0] = tColor[1] = tColor[2] = 0.;
   for (auto light : aut->lights) {
      Vector ra = light->center-point;
      double perc = (norm.dot(ra)/(ra.mag()*norm.mag()));
      if(flip && perc<0) perc=-perc;

      if (perc > 0) {
         double lightColor[3];
         lightColor[0] = light->color[0]/255.;
         lightColor[1] = light->color[1]/255.;
         lightColor[2] = light->color[2]/255.;

         bool hit = false;
         Ray ray = Ray(point+ra*.01, ra);
         for (auto shape : aut->shapes) {
            if (shape->getLightIntersection(ray, lightColor)) {
               hit = true;
               break;
            }
         }

         if(!hit){
            tColor[0]+= perc*(lightColor[0]);
            tColor[1]+= perc*(lightColor[0]);
            tColor[2]+= perc*(lightColor[0]);
            if(tColor[0]>1.) tColor[0] = 1.;
            if(tColor[1]>1.) tColor[1] = 1.;
            if(tColor[2]>1.) tColor[2] = 1.;
         }
      }
   }
}
