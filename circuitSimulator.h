/*
 * Universidade Federal do Rio de Janeiro
 * Trabalho da disciplina Circuitos Elétricos 2
 * 2013/1
 * Por Ian Esteves do Nascimento e Igor Vital
 */

#ifndef CIRCUITSIMULATOR_H
#define CIRCUITSIMULATOR_H

#include <string>
#include <vector>
#include "netList.h"

class circuitSimulator{
public:
   double tFinal, step;
   int internalStep, varNumber;
   std::vector<circuitElement *> netList1;
   std::vector<circuitElement *> netList2;
   std::vector<circuitElement *> netList3;
   double **system1;
   double **system2;
   std::vector<std::string> varNames;
   std::vector<std::string> varInternalNames;
   double *prevResult1;
   double *prevResult2;
   double *prevAprox1;
   double *prevAprox2;
   std::vector<double> varInternal;
   std::vector<int> reducedLine;
   std::vector<int> reducedCol;
   ~circuitSimulator();
   int import(std::string fileName);
   void createSystem1(double t);
   void createSystem2(double t);
   int solveSystem1(void);
   int solveSystem2(void);
   int findLine(std::string varName);
   int findCol(std::string varName);
   double calcResultError(void);
   void keepAprox(void);
   void resetAprox(void);
   void disableIC(void);
};

#endif	/* CIRCUITSIMULATOR_H */

