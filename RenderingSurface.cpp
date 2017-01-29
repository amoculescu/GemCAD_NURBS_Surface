#define RADPERDEG 0.0174533

#include "RenderingSurface.h"
#include "RenderingCurve.h"

#include <GL/glut.h>
#include <NURBS_Curve.h>
#include <NURBS_Surface.h>
#include <algorithm>

	// fmod
#include <stdio.h>		// cout
#include <iostream>

void drawSurfacePoints(const std::vector<Vec4f> &points)
{
	// TODO: draw points of the surface
	// note: Vec4f provides a method to homogenize a vector
	// =====================================================
	glBegin(GL_POINTS);


	Vec3f testcol = Vec3f(1.0, 1.0, 1.0);
	glColor3fv(&testcol.x); //color

	for (Vec4f point : points) {

		Vec3f glpoint = {point.homogenized().x, point.homogenized().y, point.homogenized().z};
// TODO remove cout
//		std::cout << glpoint << std::endl;
		glVertex3fv(&glpoint.x);
	}
	glEnd();

	// =====================================================
}
void drawNormals(const std::vector<Vec4f> &points, const std::vector<Vec3f> &normals)
{
	// TODO: draw normals as lines (homogenized)
	// note: Vec4f provides a method to homogenize a vector
	// =====================================================
	for (int i = 0; i < points.size(); i++) {
		glBegin(GL_LINE_STRIP);

		Vec3f testcol = Vec3f(1.0, 1.0, 0.2);
		glColor3fv(&testcol.x); //color
			Vec4f point = points[i];
			Vec3f glpoint = {point.homogenized().x, point.homogenized().y, point.homogenized().z};

			glVertex3fv(&glpoint.x);
			Vec3f glnormal =(glpoint +  0.1f*normals[i]);
			glVertex3fv(&glnormal.x);

		glEnd();

	}


	// =====================================================
}
void drawNURBSSurfaceCtrlP(const NURBS_Surface &surface)
{
// TODO: draw control polygon an points (homogenized)
// =====================================================


	int umax = surface.controlPoints[1].size();
	int vmax = surface.controlPoints.size();
	for (int v = 0; v < vmax; v++) {

		glBegin(GL_LINE_STRIP);
			Vec3f testcol = Vec3f(1.0, 0.0, 0.0);
			glColor3fv(&testcol.x); //color
		for (int u = 0; u < umax; u++) {
			Vec3f point = { surface.controlPoints[v][u].x
					/ surface.controlPoints[v][u].w,
					surface.controlPoints[v][u].y
							/ surface.controlPoints[v][u].w,
					surface.controlPoints[v][u].z
							/ surface.controlPoints[v][u].w };
			glVertex3fv(&point.x);


		}
		glEnd();

	}

	for (int v = 0; v < vmax; v++) {

			glBegin(GL_LINE_STRIP);
				Vec3f testcol = Vec3f(1.0, 0.0, 0.0);
				glColor3fv(&testcol.x); //color
			for (int u = 0; u < umax; u++) {
				Vec3f point = { surface.controlPointsTransposed[v][u].x
						/ surface.controlPointsTransposed[v][u].w,
						surface.controlPointsTransposed[v][u].y
								/ surface.controlPointsTransposed[v][u].w,
						surface.controlPointsTransposed[v][u].z
								/ surface.controlPointsTransposed[v][u].w };
				glVertex3fv(&point.x);


			}
			glEnd();

		}



// =====================================================
}

void drawNURBSSurface(std::vector<Vec4f> &points, const std::vector<Vec3f> &normals, const int numPointsU, const int numPointsV, bool enableSurf, bool enableWire)
{

	if (enableWire)
	{

		glDisable(GL_LIGHTING);
		glColor3f(0.0f,0.0f,1.0f);
		// TODO: draw surface wire mesh
		// =====================================================
		for (int i = 0; i < points.size() - numPointsV - 2; i++) {
			Vec4f hpoint1 = points[i].homogenized();
			Vec4f hpoint2 = points[numPointsV + i + 1].homogenized();
			Vec4f hpoint3 = points[numPointsV + i + 2].homogenized();
			glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glVertex3f(hpoint1.x, hpoint1.y, hpoint1.z);
			glNormal3f(normals[numPointsV + i + 1].x, normals[numPointsV + i + 1].y, normals[numPointsV + i + 1].z);
			glVertex3f(hpoint2.x, hpoint2.y, hpoint2.z);
			glNormal3f(normals[numPointsV + i + 2].x, normals[numPointsV + i + 2].y, normals[numPointsV + i + 2].z);
			glVertex3f(hpoint3.x, hpoint3.y, hpoint3.z);
		}

		for (int j = 0; j < points.size() - numPointsV - 1; j++) {
			Vec4f hpoint1 = points[j].homogenized();
			Vec4f hpoint2 = points[j + 1].homogenized();
			Vec4f hpoint3 = points[numPointsV + j + 1].homogenized();
			glBegin(GL_TRIANGLE_STRIP);
			glNormal3f(normals[j].x, normals[j].y, normals[j].z);
			glVertex3f(hpoint1.x, hpoint1.y, hpoint1.z);
			glNormal3f(normals[j + 1].x, normals[j + 1].y, normals[j + 1].z);
			glVertex3f(hpoint2.x, hpoint2.y, hpoint2.z);
			glNormal3f(normals[numPointsV + j + 1].x, normals[numPointsV + j + 1].y, normals[numPointsV + j + 1].z);
			glVertex3f(hpoint3.x, hpoint3.y, hpoint3.z);
			glEnd();
		}
		// =====================================================

	}

	if (enableSurf)
	{
		glEnable(GL_LIGHTING);
		glColor3f(0.99f, 0.99f, 0.99f);
		// TODO: draw surface with quads
		// =====================================================
	/*	for (int i = 0; i < points.size() - 3; i = i++) {
			Vec4f hpoint1 = points[i].homogenized();
			Vec4f hpoint2 = points[i + 1].homogenized();
			Vec4f hpoint3 = points[i + 2].homogenized();
			Vec4f hpoint4 = points[i + 3].homogenized();
			glBegin(GL_QUAD_STRIP);
			glNormal3f(normals[i].x, normals[i].y, normals[i].z);
			glVertex3f(hpoint1.x, hpoint1.y, hpoint1.z);
			glNormal3f(normals[i + 1].x, normals[i + 1].y, normals[i + 1].z);
			glVertex3f(hpoint2.x, hpoint2.y, hpoint2.z);
			glNormal3f(normals[i + 2].x, normals[i + 2].y, normals[i + 2].z);
			glVertex3f(hpoint3.x, hpoint3.y, hpoint3.z);
			glNormal3f(normals[i + 3].x, normals[i + 3].y, normals[i + 3].z);
			glVertex3f(hpoint4.x, hpoint4.y, hpoint4.z);
			glEnd();
		}*/
		// =====================================================
	}
}
void evaluateNURBSSurface(const NURBS_Surface &surface,float u, float v, bool vFirst /*= true*/)
{
	Vec3f colorPolyU =  {1.0f, 0.7f, 0.4f};
	Vec3f colorPolyV =  {0.6f, 1.0f, 0.6f};
	Vec3f colorCurveU = {1.0f, 0.5f, 0.0f};
	Vec3f colorCurveV = {0.0f, 0.8f, 0.0f};
	Vec3f colorPoint =  {0.0f, 0.5f, 1.0f};
	Vec4f evaluatedPoint;
	NURBSCurve tmp = NURBSCurve(surface.controlPoints[0], surface.knotVectorU, surface.degree); // to avoid is valid nurbs print
	std::vector<Vec4f> ControlPointsTmp = std::vector<Vec4f>();
	Vec4f dummyTangent = Vec4f();
	Vec4f point = Vec4f();
	// TODO: implement the visualization of the point evaluation starting with u and v direction whether vFirst is true or not
	// note: use the NURBSCurve class and the CurveRendering functions 'drawNURBSCtrlPolygon_H' 'drawNURBS_H'
	// =====================================================

	if (vFirst)
	{

		// 1. draw the nurbs curves and its control polygons first in v direction
		// evaluate the patch at v in all columns
		for (int i = 0; i < surface.controlPoints.size(); i++) {
			tmp = NURBSCurve(surface.controlPointsTransposed[i], surface.knotVectorV, surface.degree);
			Vec4f pointV = tmp.evaluteDeBoor(v, dummyTangent); // dummyTangentU
			ControlPointsTmp.push_back(pointV);

			drawNURBS_H(tmp, colorCurveU);
			drawNURBSCtrlPolygon_H(tmp, colorPolyU);
		}

		// 2. then the resulting curve and its control polygon at v in u direction.
		// evaluate curve-at-v at u
		tmp = NURBSCurve(ControlPointsTmp, surface.knotVectorU, surface.degree);
		point = tmp.evaluteDeBoor(u, dummyTangent);

		drawNURBS_H(tmp, colorCurveV);
		drawNURBSCtrlPolygon_H(tmp, colorPolyV);

		// 3. draw the evaluated surface point
		glBegin(GL_POINTS);
		glColor3fv(&colorPoint.x);
		Vec3f glpoint = { point.homogenized().x, point.homogenized().y, point.homogenized().z };
		glVertex3fv(&glpoint.x);
		glEnd();

	}
	else
	{
		// 1. draw the nurbs curves and its control polygons first in u direction
		// evaluate the patch at u in all rows
		for (int i = 0; i < surface.controlPoints.size(); i++) {
			tmp = NURBSCurve(surface.controlPoints[i], surface.knotVectorU, surface.degree);
			Vec4f pointU = tmp.evaluteDeBoor(u, dummyTangent); // dummy tangentV
			ControlPointsTmp.push_back(pointU);

			drawNURBS_H(tmp, colorCurveU);
			drawNURBSCtrlPolygon_H(tmp, colorPolyU);
		}

		// 2. then the resulting curve and its control polygon at u in v direction.
		// evaluate curve-at-u at v
		tmp = NURBSCurve(ControlPointsTmp, surface.knotVectorV, surface.degree);
		point = tmp.evaluteDeBoor(v, dummyTangent);

		drawNURBS_H(tmp, colorCurveU);
		drawNURBSCtrlPolygon_H(tmp, colorPolyU);

		// 3. draw the evaluated surface point
		glBegin(GL_POINTS);
		glColor3fv(&colorPoint.x);
		Vec3f glpoint = { point.homogenized().x, point.homogenized().y, point.homogenized().z };
		glVertex3fv(&glpoint.x);
		glEnd();

	}

	// =====================================================

	
}
