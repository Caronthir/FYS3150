#include "planet.h"

#define G 39.478417604357434475337963
#define c 63239.7263

Planet::Planet(const std::string& namme, double M, vec3 pos0, vec3 vel0, unsigned int n)
:name(namme), mass(M), pos(pos0), vel(vel0)
{
  pos_array = arma::zeros(3, n+1);
  pos_array(0, 0) = pos(0);
  pos_array(1, 0) = pos(1);
  pos_array(2, 0) = pos(2);
  writePosToMat(0);               // Save initial position
}

double Planet::distance(Planet otherPlanet){
  vec3 diff;
  diff = otherPlanet.pos - pos;
  return diff.length();
}

void Planet::force(Planet otherPlanet){
  vec3 diff = otherPlanet.pos - pos;
  F = diff*G*mass*otherPlanet.mass/(pow(distance(otherPlanet),3));
}

void Planet::relativisticForce(Planet otherPlanet){
  vec3 diff = otherPlanet.pos - pos;
  double r_squared  = diff.lengthSquared();
  double ang_mom_norm = diff.cross2d(otherPlanet.pos);
  force(otherPlanet); // SHOULD I ALSO DIVIDE BY THE MASS HERE?
  F *= (1 + 3*ang_mom_norm*ang_mom_norm/(r_squared*c*c));
}

void Planet::calculateAcc(Planet otherPlanet){
  force(otherPlanet);
  acc += F/mass;
}

void Planet::calculateAccRelativistic(Planet otherPlanet){
  relativisticForce(otherPlanet);
  acc += F/mass;
}

double Planet::potentialEnergy(Planet otherPlanet){
  return -G*mass*otherPlanet.mass/distance(otherPlanet);
}

void Planet::resetAcc(){
  acc[0] = 0.0;
  acc[1] = 0.0;
  acc[2] = 0.0;
}

void Planet::resetF(){
  F[0] = 0.0;
  F[1] = 0.0;
  F[2] = 0.0;
}

void Planet::writePosToMat(unsigned int i){
  pos_array(0,i) = pos[0];
  pos_array(1,i) = pos[1];
  pos_array(2,i) = pos[2];
}
