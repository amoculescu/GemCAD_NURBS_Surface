// ========================================================================= //
// Authors: Felix Schuwirth                                                  //
// mailto:felix.schuwirth@igd.fraunhofer.de                                  //
//                                                                           //
// GRIS - Graphisch Interaktive Systeme                                      //
// Technische Universit�t Darmstadt                                          //
// Fraunhoferstrasse 5                                                       //
// D-64283 Darmstadt, Germany                                                //
//                                                                           //
// Creation Date: 12.01.2017                                                 //
// Content: Simple and extendable openGL program offering                    //
//   * basic navigation and basic pipeline rendering                         //
// ========================================================================= //

#include <GL/glut.h>	// openGL helper

#include "Vec4.h"
#include "Vec3.h"
#include "NURBS_Surface.h"

// ===================
// === GLOBAL DATA ===
// ===================

// TODO: define global variables here to present the exercises
// ===========================================================

// some points used for drawing point & line example
std::vector<NURBS_Surface> NURBSs;
unsigned int nrPoints;
std::vector<std::vector<Vec4f> > points;
std::vector<std::vector<Vec3f> > normals;
bool enableNormal, enablePoints, enableWire, enableSurface, enableCtrl;
int enableEval;
int nurbsSelect;
float u, v;
int tangentSize;

// ===========================================================

// do not modify data below unless you know what you do
// camera Information
float transX, transY, transZ;
float angleX, angleY;
// mouse information
int mouseX, mouseY, mouseButton;
float mouseSensitivy;

// ==============
// === BASICS ===
// ==============

int main(int argc, char **argv);

void setDefaults();

void initializeGL();

void calculatePoints();

void reshape(GLint width, GLint height);

// =================
// === RENDERING ===
// =================

void drawCS();

void drawObjects();

void renderScene(void);

// =================
// === CALLBACKS ===
// =================

void keyPressed(unsigned char key, int x, int y);

void mousePressed(int button, int state, int x, int y);

void mouseMoved(int x, int y);

// ===============
// === VARIOUS ===
// ===============

void coutHelp();
