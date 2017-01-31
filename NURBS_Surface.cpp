#include "NURBS_Surface.h"

#include <stdio.h>		// cout
#include <iostream>		// cout


#include <stdio.h>		// cout
#include <iostream>

NURBS_Surface::NURBS_Surface()
{
	// test surface: quarter cylinder
	std::vector<Vec4f> pRow1;
	pRow1.push_back(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f) * 2.0f);
	controlPoints.push_back(pRow1);

	std::vector<Vec4f> pRow2;
	pRow2.push_back(Vec4f(0.0f, 2.0f, -1.0f, 1.0f));
	pRow2.push_back(Vec4f(2.0f, 2.0f, -1.0f, 1.0f) * 6.0f);
	pRow2.push_back(Vec4f(2.0f, 0.0f, -1.0f, 1.0f) * 2.0f);
	controlPoints.push_back(pRow2);

	std::vector<Vec4f> pRow3;
	pRow3.push_back(Vec4f(0.0f, 1.0f, -2.0f, 1.0f));
	pRow3.push_back(Vec4f(1.0f, 1.0f, -2.0f, 1.0f));
	pRow3.push_back(Vec4f(1.0f, 0.0f, -2.0f, 1.0f) * 2.0f);
	controlPoints.push_back(pRow3);

	knotVectorU.push_back(0.0f);
	knotVectorU.push_back(0.0f);
	knotVectorU.push_back(0.0f);
	knotVectorU.push_back(1.0f);
	knotVectorU.push_back(1.0f);
	knotVectorU.push_back(1.0f);

	knotVectorV.push_back(0.0f);
	knotVectorV.push_back(0.0f);
	knotVectorV.push_back(0.0f);
	knotVectorV.push_back(1.0f);
	knotVectorV.push_back(1.0f);
	knotVectorV.push_back(1.0f);

	degree = 2;

	transposeMesh();
	isValidNURBS();
}

/*
NURBS_Surface::NURBS_Surface() {

	
	std::vector<Vec4f> pRow1;
	pRow1.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(1.0f, 1.0f, 0.0f, 0.7071f));
	pRow1.push_back(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(-1.0f, 1.0f, 0.0f, 0.7071f));
	pRow1.push_back(Vec4f(-1.0f, 0.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(-1.0f, -1.0f, 0.0f, 0.7071f));
	pRow1.push_back(Vec4f(0.0f, -1.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(1.0f, -1.0f, 0.0f, 0.7071f));
	pRow1.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	controlPoints.push_back(pRow1);

	std::vector<Vec4f> pRow2;
	pRow2.push_back(Vec4f(1.0f, 0.0f, 2.0f, 1.0f));
	pRow2.push_back(Vec4f(1.0f, 1.0f, 2.0f, 0.7071f));
	pRow2.push_back(Vec4f(0.0f, 1.0f, 2.0f, 1.0f));
	pRow2.push_back(Vec4f(-1.0f, 1.0f, 2.0f, 0.7071f));
	pRow2.push_back(Vec4f(-1.0f, 0.0f, 2.0f, 1.0f));
	pRow2.push_back(Vec4f(-1.0f, -1.0f, 2.0f, 0.7071f));
	pRow2.push_back(Vec4f(0.0f, -1.0f, 2.0f, 1.0f));
	pRow2.push_back(Vec4f(1.0f, -1.0f, 2.0f, 0.7071f));
	pRow2.push_back(Vec4f(1.0f, 0.0f, 2.0f, 1.0f));
	controlPoints.push_back(pRow2);

	std::vector<Vec4f> pRow3;
	pRow3.push_back(Vec4f(1.0f, 0.0f, 3.0f, 1.0f));
	pRow3.push_back(Vec4f(1.0f, 1.0f, 3.0f, 0.7071f));
	pRow3.push_back(Vec4f(0.0f, 1.0f, 3.0f, 1.0f));
	pRow3.push_back(Vec4f(-1.0f, 1.0f, 3.0f, 0.7071f));
	pRow3.push_back(Vec4f(-1.0f, 0.0f, 3.0f, 1.0f));
	pRow3.push_back(Vec4f(-1.0f, -1.0f, 3.0f, 0.7071f));
	pRow3.push_back(Vec4f(0.0f, -1.0f, 3.0f, 1.0f));
	pRow3.push_back(Vec4f(1.0f, -1.0f, 3.0f, 0.7071f));
	pRow3.push_back(Vec4f(1.0f, 0.0f, 3.0f, 1.0f));
	controlPoints.push_back(pRow3);

	knotVectorU.push_back(0);
	knotVectorU.push_back(0);
	knotVectorU.push_back(0);
	knotVectorU.push_back(.25);
	knotVectorU.push_back(.25);
	knotVectorU.push_back(.5);
	knotVectorU.push_back(.5);
	knotVectorU.push_back(.75);
	knotVectorU.push_back(.75);
	knotVectorU.push_back(1);
	knotVectorU.push_back(1);
	knotVectorU.push_back(1);

	knotVectorV.push_back(0);
	knotVectorV.push_back(0);
	knotVectorV.push_back(0);
	knotVectorV.push_back(1);
	knotVectorV.push_back(1);
	knotVectorV.push_back(1);

	degree = 2;

	transposeMesh();
	isValidNURBS();
}*/


NURBS_Surface::NURBS_Surface(int example) {
	//funktioniert
	if (example == 0) {
		std::vector<Vec4f> pRow1;
		pRow1.push_back(Vec4f(1.0f, 1.0, 0.0f, 0.7071f));
		pRow1.push_back(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
		pRow1.push_back(Vec4f(-1.0f, 1.0f, 0.0f, 0.7071f));
		controlPoints.push_back(pRow1);

		std::vector<Vec4f> pRow2;
		pRow2.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
		pRow2.push_back(Vec4f(0.0f, 0.0f, 2.0f, 1.0f));
		pRow2.push_back(Vec4f(-1.0f, 0.0f, 0.0f, 1.0f));
		controlPoints.push_back(pRow2);

		std::vector<Vec4f> pRow3;
		pRow3.push_back(Vec4f(1.0f, -1.0f, 0.0f, 0.7071f));
		pRow3.push_back(Vec4f(0.0f, -1.0f, 0.0f, 1.0f));
		pRow3.push_back(Vec4f(-1.0f, -1.0f, 0.0f, 0.7071f));
		controlPoints.push_back(pRow3);


		knotVectorU.push_back(0.0f);
		knotVectorU.push_back(0.0f);
		knotVectorU.push_back(0.0f);
		knotVectorU.push_back(1.0f);
		knotVectorU.push_back(1.0f);
		knotVectorU.push_back(1.0f);

		knotVectorV.push_back(0.0f);
		knotVectorV.push_back(0.0f);
		knotVectorV.push_back(0.0f);
		knotVectorV.push_back(1.0f);
		knotVectorV.push_back(1.0f);
		knotVectorV.push_back(1.0f);

		degree = 2;
		transposeMesh();
		isValidNURBS();
	}
	else if (example == 1) {
		// test surface: quarter cylinder
		std::vector<Vec4f> pRow1;
		pRow1.push_back(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
		pRow1.push_back(Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
		pRow1.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f) * 2.0f);
		controlPoints.push_back(pRow1);

		std::vector<Vec4f> pRow2;
		pRow2.push_back(Vec4f(0.0f, 2.0f, -1.0f, 1.0f));
		pRow2.push_back(Vec4f(2.0f, 2.0f, -1.0f, 1.0f) * 6.0f);
		pRow2.push_back(Vec4f(2.0f, 0.0f, -1.0f, 1.0f) * 2.0f);
		controlPoints.push_back(pRow2);

		std::vector<Vec4f> pRow3;
		pRow3.push_back(Vec4f(0.0f, 1.0f, -2.0f, 1.0f));
		pRow3.push_back(Vec4f(1.0f, 1.0f, -2.0f, 1.0f));
		pRow3.push_back(Vec4f(1.0f, 0.0f, -2.0f, 1.0f) * 2.0f);
		controlPoints.push_back(pRow3);

		knotVectorU.push_back(0.0f);
		knotVectorU.push_back(0.0f);
		knotVectorU.push_back(0.0f);
		knotVectorU.push_back(1.0f);
		knotVectorU.push_back(1.0f);
		knotVectorU.push_back(1.0f);

		knotVectorV.push_back(0.0f);
		knotVectorV.push_back(0.0f);
		knotVectorV.push_back(0.0f);
		knotVectorV.push_back(1.0f);
		knotVectorV.push_back(1.0f);
		knotVectorV.push_back(1.0f);

		degree = 2;

		transposeMesh();
		isValidNURBS();
	} else if (example == 2) {
		// test surface: quarter cylinder
		std::vector<Vec4f> pRow1;
		pRow1.push_back(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
		pRow1.push_back(Vec4f(1.0f, 1.0f, 0.0f, 1.0f / sqrtf(2.0f)));
		pRow1.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
		pRow1.push_back(Vec4f(1.0f, -1.0f, 0.0f, 1.0f / sqrtf(2.0f)));
		pRow1.push_back(Vec4f(0.0f, -1.0f, 0.0f, 1.0f));
		controlPoints.push_back(pRow1);

		std::vector<Vec4f> pRow2;
		pRow2.push_back(Vec4f(0.0f, 1.0f, 0.5f, 1.0f));
		pRow2.push_back(Vec4f(1.0f, 1.0f, 0.5f, 1.0f / sqrtf(2.0f)));
		pRow2.push_back(Vec4f(1.0f, 0.0f, 0.5f, 1.0f));
		pRow2.push_back(Vec4f(1.0f, -1.0f, 0.5f, 1.0f / sqrtf(2.0f)));
		pRow2.push_back(Vec4f(0.0f, -1.0f, 0.5f, 1.0f));
		controlPoints.push_back(pRow2);

		std::vector<Vec4f> pRow3;
		pRow3.push_back(Vec4f(0.0f, 1.0f, 1.0f, 1.0f));
		pRow3.push_back(Vec4f(1.0f, 1.0f, 1.0f, 1.0f / sqrtf(2.0f)));
		pRow3.push_back(Vec4f(1.0f, 0.0f, 1.0f, 1.0f));
		pRow3.push_back(Vec4f(1.0f, -1.0f, 1.0f, 1.0f / sqrtf(2.0f)));
		pRow3.push_back(Vec4f(0.0f, -1.0f, 1.0f, 1.0f));
		controlPoints.push_back(pRow3);

		std::vector<Vec4f> pRow4;
		pRow4.push_back(Vec4f(0.0f, 1.0f, 1.5f, 1.0f));
		pRow4.push_back(Vec4f(1.0f, 1.0f, 1.5f, 1.0f / sqrtf(2.0f)));
		pRow4.push_back(Vec4f(1.0f, 0.0f, 1.5f, 1.0f));
		pRow4.push_back(Vec4f(1.0f, -1.0f, 1.5f, 1.0f / sqrtf(2.0f)));
		pRow4.push_back(Vec4f(0.0f, -1.0f, 1.5f, 1.0f));
		controlPoints.push_back(pRow4);

		std::vector<Vec4f> pRow5;
		pRow5.push_back(Vec4f(0.0f, 1.0f, 2.0f, 1.0f));
		pRow5.push_back(Vec4f(1.0f, 1.0f, 2.0f, 1.0f / sqrtf(2.0f)));
		pRow5.push_back(Vec4f(1.0f, 0.0f, 2.0f, 1.0f));
		pRow5.push_back(Vec4f(1.0f, -1.0f, 2.0f, 1.0f / sqrtf(2.0f)));
		pRow5.push_back(Vec4f(0.0f, -1.0f, 2.0f, 1.0f));
		controlPoints.push_back(pRow5);

		knotVectorU.push_back(0.0f);
		knotVectorU.push_back(0.0f);
		knotVectorU.push_back(0.0f);
		knotVectorU.push_back(0.5f);
		knotVectorU.push_back(0.5f);
		knotVectorU.push_back(1.0f);
		knotVectorU.push_back(1.0f);
		knotVectorU.push_back(1.0f);

		knotVectorV.push_back(0.0f);
		knotVectorV.push_back(0.0f);
		knotVectorV.push_back(0.0f);
		knotVectorV.push_back(0.5f);
		knotVectorV.push_back(0.5f);
		knotVectorV.push_back(1.0f);
		knotVectorV.push_back(1.0f);
		knotVectorV.push_back(1.0f);

		degree = 2;

		transposeMesh();
		isValidNURBS();

	}
	else if (example == 3) {
		std::vector<Vec4f> pRow1;
		pRow1.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
		pRow1.push_back(Vec4f(1.0f, 1.0f, 0.0f, 0.7071f));
		pRow1.push_back(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
		pRow1.push_back(Vec4f(-1.0f, 1.0f, 0.0f, 0.7071f));
		pRow1.push_back(Vec4f(-1.0f, 0.0f, 0.0f, 1.0f));
		pRow1.push_back(Vec4f(-1.0f, -1.0f, 0.0f, 0.7071f));
		pRow1.push_back(Vec4f(0.0f, -1.0f, 0.0f, 1.0f));
		pRow1.push_back(Vec4f(1.0f, -1.0f, 0.0f, 0.7071f));
		pRow1.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
		controlPoints.push_back(pRow1);

		std::vector<Vec4f> pRow2;
		std::vector<Vec4f> pRow3;
		std::vector<Vec4f> pRow4;
		std::vector<Vec4f> pRow5;
		std::vector<Vec4f> pRow6;
		std::vector<Vec4f> pRow7;
		std::vector<Vec4f> pRow8;
		std::vector<Vec4f> pRow9;
		
		for (int i = 0; i < pRow1.size(); i++)
		{
			pRow2[i] = pRow1[i];
			pRow2[i].z += 1;
			
		}
		controlPoints.push_back(pRow2);
		
		for (int i = 0; i < pRow1.size(); i++)
		{
			pRow3[i] = pRow2[i];
			pRow3[i].z += 1;
		}
		controlPoints.push_back(pRow3);

		for (int i = 0; i < pRow1.size(); i++)
		{
			pRow4[i] = pRow3[i];
			pRow4[i].z += 1;
		}
		controlPoints.push_back(pRow4);
		for (int i = 0; i < pRow1.size(); i++)
		{
			pRow5[i] = pRow4[i];
			pRow5[i].z += 1;
		}
		controlPoints.push_back(pRow5);
		for (int i = 0; i < pRow1.size(); i++)
		{
			pRow6[i] = pRow5[i];
			pRow6[i].z += 1;
		}
		controlPoints.push_back(pRow6);
		for (int i = 0; i < pRow1.size(); i++)
		{
			pRow7[i] = pRow6[i];
			pRow7[i].z += 1;
		}
		controlPoints.push_back(pRow7);

		for (int i = 0; i < pRow1.size(); i++)
		{
			pRow8[i] = pRow7[i];
			pRow8[i].z += 1;
		}
		controlPoints.push_back(pRow8);
		
		for (int i = 0; i < pRow1.size(); i++)
		{
			pRow9[i] = pRow8[i];
			pRow9[i].z += 1;
		}
		controlPoints.push_back(pRow9);

		knotVectorU.push_back(0);
		knotVectorU.push_back(0);
		knotVectorU.push_back(0);
		knotVectorU.push_back(.25);
		knotVectorU.push_back(.25);
		knotVectorU.push_back(.5);
		knotVectorU.push_back(.5);
		knotVectorU.push_back(.75);
		knotVectorU.push_back(.75);
		knotVectorU.push_back(1);
		knotVectorU.push_back(1);
		knotVectorU.push_back(1);

		knotVectorV.push_back(0);
		knotVectorV.push_back(0);
		knotVectorV.push_back(0);
		knotVectorV.push_back(.25);
		knotVectorV.push_back(.25);
		knotVectorV.push_back(.5);
		knotVectorV.push_back(.5);
		knotVectorV.push_back(.75);
		knotVectorV.push_back(.75);
		knotVectorV.push_back(1);
		knotVectorV.push_back(1);
		knotVectorV.push_back(1);
		
	}
}
/*
NURBS_Surface::NURBS_Surface() {
	std::vector<Vec4f> pRow1;
	pRow1.push_back(Vec4f(0.0f, 0.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(0.0f, 0.5f, 0.0f, 0.7071f));
	pRow1.push_back(Vec4f(0.0f, 1.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(0.5f, 1.0f, 0.0f, 0.7071f));
	pRow1.push_back(Vec4f(1.0f, 1.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(1.0f, 0.5f, 0.0f, 0.7071f));
	pRow1.push_back(Vec4f(1.0f, 0.0f, 0.0f, 1.0f));
	pRow1.push_back(Vec4f(0.5f, 0.0f, 0.0f, 0.7071f));
	controlPoints.push_back(pRow1);

	std::vector<Vec4f> pRow2;
	pRow2.push_back(Vec4f(0.0f, 0.0f, 0.5f, 1.0f));
	pRow2.push_back(Vec4f(0.0f, 0.5f, 0.5f, 0.7071f));
	pRow2.push_back(Vec4f(0.0f, 1.0f, 0.5f, 1.0f));
	pRow2.push_back(Vec4f(0.5f, 1.0f, 0.5f, 0.7071f));
	pRow2.push_back(Vec4f(1.0f, 1.0f, 0.5f, 1.0f));
	pRow2.push_back(Vec4f(1.0f, 0.5f, 0.5f, 0.7071f));
	pRow2.push_back(Vec4f(1.0f, 0.0f, 0.5f, 1.0f));
	pRow2.push_back(Vec4f(0.5f, 0.0f, 0.5f, 0.7071f));
	controlPoints.push_back(pRow2);

	std::vector<Vec4f> pRow3;
	pRow3.push_back(Vec4f(0.0f, 0.0f, 1.0f, 1.0f));
	pRow3.push_back(Vec4f(0.0f, 0.5f, 1.0f, 0.7071f));
	pRow3.push_back(Vec4f(0.0f, 1.0f, 1.0f, 1.0f));
	pRow3.push_back(Vec4f(0.5f, 1.0f, 1.0f, 0.7071f));
	pRow3.push_back(Vec4f(1.0f, 1.0f, 1.0f, 1.0f));
	pRow3.push_back(Vec4f(1.0f, 0.5f, 1.0f, 0.7071f));
	pRow3.push_back(Vec4f(1.0f, 0.0f, 1.0f, 1.0f));
	pRow3.push_back(Vec4f(0.5f, 0.0f, 1.0f, 0.7071f));
	controlPoints.push_back(pRow3);

	knotVectorU.push_back(0.0f);
	knotVectorU.push_back(0.0f);
	knotVectorU.push_back(0.0f);
	knotVectorU.push_back(0.1666f);
	knotVectorU.push_back(0.3332f);
	knotVectorU.push_back(0.4998f);
	knotVectorU.push_back(0.6664f);
	knotVectorU.push_back(0.833f);
	knotVectorU.push_back(1.0f);
	knotVectorU.push_back(1.0f);
	knotVectorU.push_back(1.0f);

	knotVectorV.push_back(0.0f);
	knotVectorV.push_back(0.0f);
	knotVectorV.push_back(0.0f);
	knotVectorV.push_back(1.0f);
	knotVectorV.push_back(1.0f);
	knotVectorV.push_back(1.0f);

	degree = 2;

	transposeMesh();
	isValidNURBS();
}*/



NURBS_Surface::NURBS_Surface(const std::vector<std::vector<Vec4f>>& controlPoints_, const std::vector<float>& knotVectorU_, const std::vector<float>& knotVectorV_, const unsigned int degree_)
	: controlPoints(controlPoints_)
	, knotVectorU(knotVectorU_)
	, knotVectorV(knotVectorV_)
	, degree(degree_)
{
	transposeMesh();
	isValidNURBS();
}

bool NURBS_Surface::isValidNURBS()
{
	// knot vector U verification
	bool validU = true;
	for (unsigned int i = 1; i < knotVectorU.size() && validU == true; ++i)
	{
		if (knotVectorU[i] < knotVectorU[i-1])
		{
			std::cout << "INVALID (unsorted) knotVectorU.\n";
			validU = false;
			break;
		}
	}
	// knot vector V verification
	bool validV = true;
	for (unsigned int i = 1; i < knotVectorV.size() && validV == true; ++i)
	{
		if (knotVectorV[i] < knotVectorV[i-1])
		{
			std::cout << "INVALID (unsorted) knotVectorV.\n";
			validV = false;
			break;
		}
	}
	// size verification
	bool validSize = true;
	for (unsigned int i = 1; i < controlPoints.size() && validSize == true; ++i)
	{
		if (controlPoints[i].size() != controlPoints[i-1].size())
		{
			std::cout << "INVALID mesh (Each row has to have the same number of control points).\n";
			validSize = false;
		}
	}
	if (controlPoints[0].size() + degree + 1 != knotVectorU.size()) 
	{
		std::cout << "INVALID size in u direction (controlPoints[0].size() + degree + 1 != knotVectorU.size()).\n";
		validSize = false;
	}
	if (controlPoints.size() + degree + 1 != knotVectorV.size()) 
	{
		std::cout << "INVALID size in v direction (controlPoints.size() + degree + 1 != knotVectorV.size()).\n";
		validSize = false;
	}
	return (validU && validV && validSize);
}

Vec4f NURBS_Surface::evaluteDeBoor(const float u, const float v, Vec4f& tangentU, Vec4f& tangentV)
{
	Vec4f evaluatedPoint;
	if (!isValidNURBS())
		return Vec4f();

	// TO DO: evaluate the surface by evaluating curves
	// ===============================================

	NURBSCurve tmp = NURBSCurve(controlPoints[0], knotVectorU, degree); // to avoid is valid nurbs print
	std::vector<Vec4f> ControlPointsTmp = std::vector<Vec4f>();
//	Vec4f& dummyTangent = tangentU;

	// evaluate the patch at u in all rows
	for (int i = 0; i < controlPoints.size(); i++) {

		tmp = NURBSCurve(controlPoints[i], knotVectorU, degree);

		Vec4f pointU = tmp.evaluteDeBoor(u, tangentV); // dummy tangentV

		ControlPointsTmp.push_back(pointU);
	}

	// evaluate curve-at-u at v
	tmp = NURBSCurve(ControlPointsTmp, knotVectorV, degree);
	evaluatedPoint = tmp.evaluteDeBoor(v, tangentV);

	// evaluate the patch at v in all columns
	ControlPointsTmp.clear();

	for (int i = 0; i < controlPoints.size(); i++) {
		tmp = NURBSCurve(controlPointsTransposed[i], knotVectorV, degree);
		Vec4f pointV = tmp.evaluteDeBoor(v, tangentU); // dummyTangentU
		ControlPointsTmp.push_back(pointV);
	}

	// evaluate curve-at-v at u
	tmp = NURBSCurve(ControlPointsTmp, knotVectorU, degree);
	tmp.evaluteDeBoor(u, tangentU);
	// ===============================================

	return evaluatedPoint;
}

std::ostream& operator<< (std::ostream& os, NURBS_Surface& nurbsSurface)
{
	// degree
	os << "NURBS surface, degree " << nurbsSurface.degree << "\n";
	// control points
	os << "  " << nurbsSurface.controlPoints.size() << " x " << nurbsSurface.controlPoints[0].size() << " controlPoints:\n";
	for (unsigned int i = 0; i < nurbsSurface.controlPoints.size(); ++i)
		for (unsigned int j = 0; j < nurbsSurface.controlPoints[i].size(); ++j)
			os << "    " << nurbsSurface.controlPoints[i][j] << "\n";
	// knot vector U 
	os << "  " << nurbsSurface.knotVectorU.size() << " knotVectorU: ";
	for (unsigned int i = 0; i < nurbsSurface.knotVectorU.size(); ++i) os << nurbsSurface.knotVectorU[i] << ", ";
	os << "\n";
	// knot vector V 
	os << "  " << nurbsSurface.knotVectorV.size() << " knotVectorV: ";
	for (unsigned int i = 0; i < nurbsSurface.knotVectorU.size(); ++i) os << nurbsSurface.knotVectorV[i] << ", ";
	os << "\n";
	// knot vector verification
	nurbsSurface.isValidNURBS();
	return os;
}

void NURBS_Surface::transposeMesh()
{
	controlPointsTransposed = controlPoints;
	for (int i = 0; i < controlPoints.size(); i++) {

		for (int j = 0; j < controlPoints.size(); j++) {
			controlPointsTransposed[i][j] = controlPoints[j][i];
		}
	}
}
