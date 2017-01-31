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

#include "main.h"		// this header

#include <stdlib.h>		// standard library
#include <cmath>		// fmod
#include <stdio.h>		// cout
#include <iostream>		// cout
#include "RenderingSurface.h"
#include <algorithm>

// ==============
// === BASICS ===
// ==============

int main(int argc, char** argv)
{
	// initialize openGL window
	glutInit(&argc, argv);
	glutInitWindowPosition(300, 200);
	glutInitWindowSize(600, 400);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow("TU Darmstadt, GMCAD P3"); 
	// link functions to certain openGL events
	glutDisplayFunc(renderScene);
	glutReshapeFunc(reshape);  
	glutMouseFunc(mousePressed);
	glutMotionFunc(mouseMoved);
	glutKeyboardFunc(keyPressed);
	// further initializations
	setDefaults();
	calculatePoints();
	initializeGL();
	// activate main loop
	glutMainLoop();
	return 0;
}

void setDefaults()
{
	// scene Information
	transX = -1.0f;
	transY = -1.0f;
	transZ = -4.0f;
	angleX = 0.0f;
	angleY = 0.0f;
	// mouse information
	mouseX = 0;
	mouseY = 0;
	mouseButton = 0;
	mouseSensitivy = 1.0f;	

	enablePoints = false;
	enableNormal = false;
	enableCtrl = true;
	enableWire = true;
	enableSurface = true;
	enableEval = 0;
	u = 0.5f;
	v = 0.5f;
	nurbsSelect = 0;
	nrPoints = 30;
}

void initializeGL()
{
	// black screen
	glClearColor(0, 0, 0, 0);
	// enable depth buffer
	glEnable(GL_DEPTH_TEST);
	// Use Point Smoothing
	glEnable(GL_POINT_SMOOTH);
	glPointSize(10.0f);
	glLineWidth(2.0f);
	// set shading model
	glShadeModel(GL_SMOOTH);
	// set lighting (white light)
	GLfloat global_ambient[] = { 0.1f, 0.1f, 0.1f, 1.0f };  
	GLfloat ambientLight[] =   { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat diffuseLight[] =   { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight[] =  { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat shininess = 0.9f * 128.0f;
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, global_ambient);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
	glLightf(GL_LIGHT0, GL_SHININESS, shininess);
	glEnable(GL_LIGHT0);
	GLfloat lp[] = { 10.0f, 20.0f, 0.0f, 1.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lp);
	// enable lighting by glColor
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
	// key bindings => cout
	coutHelp();
}

void calculatePoints()
 {
	points.clear();
	normals.clear();
	NURBSs.clear();

// TODO: create two NURBS surfaces with different degrees k >= 2
// calculate the points and their normals
// emplace the resulting nurbs,points and normals into the vectors
// =====================================================

// Create examples
	NURBS_Surface surf = NURBS_Surface(0);
	NURBS_Surface surf1 = NURBS_Surface(1);
	NURBSs.push_back(surf);
	NURBSs.push_back(surf1); 
	NURBS_Surface surf2 = NURBS_Surface(2);
	NURBSs.push_back(surf2);
	NURBS_Surface surf3 = NURBS_Surface(3);
	NURBSs.push_back(surf3);


// calculate Points & normals for each NURBS

	for (NURBS_Surface surfp : NURBSs) {

		std::vector<Vec4f> nurbs_points = std::vector<Vec4f>();
		std::vector<Vec3f> normalsVec = std::vector<Vec3f>();


		for (int i = 0; i <= nrPoints; i++) {
			for (int j = 0; j <= nrPoints; j++) {
				float ui = 1.0f * i / nrPoints;
				float vj = 1.0f * j / nrPoints;
				Vec4f tangentU = Vec4f();
				Vec4f tangentV = Vec4f();

			//	std::cout << "testxx" << std::endl;
				Vec4f point = surfp.evaluteDeBoor(ui, vj, tangentU, tangentV);
			//	std::cout << "testxx2" << std::endl;


				nurbs_points.push_back(point);


			//	std::cout << point << std::endl;

				tangentU.homogenize();
				tangentV.homogenize();

// normal product
				Vec3f tu = { tangentU.x, tangentU.y, tangentU.z };
				Vec3f tv = { tangentV.x, tangentV.y, tangentV.z };

				Vec3f normal = tu ^ tv;
				normalsVec.push_back(normal);
			}
		}

		points.push_back(nurbs_points);
		normals.push_back(normalsVec);

	}
}

void reshape(GLint width, GLint height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(65.0, (float)width / (float)height, 0.1f, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// =================
// === RENDERING ===
// =================

void drawCS()
{
	glDisable(GL_LIGHTING);
	glBegin(GL_LINES);
	// red X
	glColor3f(1, 0, 0); 
	glVertex3f(0, 0, 0);
	glVertex3f(1, 0, 0);
	// green Y
	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 1, 0);
	// blue Z
	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 1);
	glEnd();
}

void drawObjects()
{
	// draw nurbs surface
	// ========================
	if (NURBSs.empty() || nurbsSelect > NURBSs.size() || nurbsSelect < 0)
		return;

	auto &nurbs = NURBSs[nurbsSelect];
	auto &ps = points[nurbsSelect];
	auto &ns = normals[nurbsSelect];
	

	if (ps.size() > 1 && nurbs.controlPoints.size() > 1)
	{

		if(enableEval > 0)
			evaluateNURBSSurface(nurbs,u,v,enableEval == 1);

		if(enablePoints && !ps.empty())
			drawSurfacePoints(ps);

		if(enableNormal && !ps.empty() && !ns.empty())
			drawNormals(ps, ns);

		if (enableCtrl)
			drawNURBSSurfaceCtrlP(nurbs);

		if (!ps.empty() && !ns.empty())
			drawNURBSSurface(ps, ns, nrPoints, nrPoints, enableSurface, enableWire);
	}
	// ========================
}

void renderScene()
{
	// clear and set camera
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	// translate scene in viewing direction
	glTranslatef(transX, transY, transZ);  
	// rotate scene
	glRotatef(angleX, 0.0f, 1.0f, 0.0f);
	glRotatef(angleY, 1.0f, 0.0f, 0.0f);
	// draw coordinate system without lighting
	drawCS();
	drawObjects();
	// swap Buffers
	glFlush();
	glutSwapBuffers();
}

// =================
// === CALLBACKS ===
// =================

void keyPressed(unsigned char key, int x, int y)
{
	switch (key)
	{
		// esc => exit
	case 27:
		exit(0);
		break;
		// help file
	case 'h' :
	case 'H' :
		coutHelp();
		break;
		// reset view
	case 'r' :
	case 'R' :
		setDefaults();
		glutPostRedisplay();	// use this whenever 3d data changed to redraw the scene
		break;
	case 'l':
	case 'L':
		u = u >= 1.0f ? 1.0f : u + 0.01f;
		glutPostRedisplay();
		break;
	case 'k':
	case 'K':
		u = u <= 0.0f ? 0.0f : u - 0.01f;
		glutPostRedisplay();
		break;
	case 'o':
	case 'O':
		v = v >= 1.0f ? 1.0f : v + 0.01f;
		glutPostRedisplay();
		break;
	case 'i':
	case 'I':
		v = v <= 0.0f ? 0.0f : v - 0.01f;
		glutPostRedisplay();
		break;
	case 'n':
	case 'N':
		enableNormal = !enableNormal;
		glutPostRedisplay();
		break;
	case 'p':
	case 'P':
		enablePoints = !enablePoints;
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		enableSurface = !enableSurface;
		glutPostRedisplay();
		break;
	case 'w':
	case 'W':
		enableWire = !enableWire;
		glutPostRedisplay();
		break;
	case 'c':
	case 'C':
		enableCtrl = !enableCtrl;
		glutPostRedisplay();
		break;
	case 'e':
	case 'E':
		enableEval = (enableEval + 1) % 3;
		glutPostRedisplay();
		break;
	case 'a':
	case 'A':
		nurbsSelect = (nurbsSelect + 1) % NURBSs.size();
		glutPostRedisplay();
		break;

	// TODO: place custom functions on button events here to present your results
	// ==========================================================================


	// ==========================================================================
	}
}

void mousePressed(int button, int state, int x, int y)
{
	mouseButton = button;
	mouseX = x; 
	mouseY = y;
}

void mouseMoved(int x, int y)
{
	// rotate (cap angleY within [-85�, +85�])
	if (mouseButton == GLUT_LEFT_BUTTON)
	{
		angleX = fmod(angleX + (x-mouseX) * mouseSensitivy, 360.0f);
		angleY += (y-mouseY) * mouseSensitivy;
		if (angleY > 85) angleY = 85;
		if (angleY < -85) angleY = -85;
		glutPostRedisplay();
	}
	// zoom (here translation in z)
	if (mouseButton == GLUT_RIGHT_BUTTON)
	{
		transZ -= 0.2f * (y-mouseY) * mouseSensitivy;
		glutPostRedisplay();
	}
	// translation in xy
	if (mouseButton == GLUT_MIDDLE_BUTTON) 
	{
		transX += 0.2f * (x-mouseX) * mouseSensitivy;
		transY -= 0.2f * (y-mouseY) * mouseSensitivy;
		glutPostRedisplay();
	}
	// update mouse for next relative movement
	mouseX = x;
	mouseY = y;
}

// ===============
// === VARIOUS ===
// ===============

void coutHelp()
{
	std::cout << std::endl;
	std::cout << "====== KEY BINDINGS ======" << std::endl;
	std::cout << "ESC: exit" << std::endl;
	std::cout << "H: show this (H)elp file" << std::endl;

	std::cout << "P: toggle surface (P)oints" << std::endl;
	std::cout << "N: toggle surface (N)ormals" << std::endl;
	std::cout << "W: toggle surface (W)ire mesh" << std::endl;
	std::cout << "S: toggle (S)urface " << std::endl;
	std::cout << "C: toggle surface (C)ontrol polygon" << std::endl;
	std::cout << "E: switch (E)valuation visualization (none,u-first,v-fist)" << std::endl;
	std::cout << "A: switch between NURBS surfaces" << std::endl;

	std::cout << "I/O: change evalutaion parameter v [0;1]" << std::endl;
	std::cout << "K/L: change evalutaion parameter u [0;1]" << std::endl;
	// TODO: update help text according to your changes
	// ================================================


	// ================================================
	std::cout << "==========================" << std::endl;
	std::cout << std::endl;
}
