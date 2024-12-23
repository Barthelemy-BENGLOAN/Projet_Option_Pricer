#pragma once
#include <iostream>
#include "BinaryTree.h"
#include "Option.h"

class CRRPricer {
private:
	Option* option;
	int N;
	double S_0;
	double U;
	double D;
	double R;
	BinaryTree<double> tree;
	BinaryTree<bool> exerciseTree;

public:
	CRRPricer(Option*, int, double, double, double, double);
	CRRPricer(Option*, int, double, double, double);
	void compute();
	double get(int, int);
	double operator()(bool closed_form = false);
	bool getExercise(int, int);

	~CRRPricer();
};
