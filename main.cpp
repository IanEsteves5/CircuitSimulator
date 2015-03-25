/*
 * Universidade Federal do Rio de Janeiro
 * Trabalho da disciplina Circuitos Elétricos 2
 * 2013/1
 * Por Ian Esteves do Nascimento e Igor Vital
 */

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "netList.h"
#include "circuitSimulator.h"

#define MAX_ITERATIONS 1000
#define ERROR_LIMIT 0.001

using namespace std;

int main(int argc, char** argv) {
   string fileName, fileOutName;
   double t;
   int c, d;
   circuitSimulator cs;
   ofstream outputFile;
   
   if(argc > 1) {
      fileName = argv[1];
      if(fileName == "/?" || fileName == "-?") {
         cout << "Usage: ";
         cout << argv[0];
         cout << " filename.net" << endl;
         cout << "filename.net   A netlist file" << endl;
         exit(0);
      }
   }
   else {
      cout << "Type file name" << endl;
      cin >> fileName;
   }
   if(cs.import(fileName)){
      cout << "File not found!";
      exit(1);
   }
   
   c = fileName.find('.');
   fileOutName = fileName.substr(0, c)+".tab";
   outputFile.open(fileOutName.c_str());
   
   outputFile << 't';
   cout << "variables" << endl;
   for(int i = 0 ; i < cs.varNames.size() ; i++){
      cout << cs.varNames[i] << endl;
      outputFile << " " << cs.varNames[i];
   }
   outputFile << endl;
   if(cs.varInternalNames.size() > 0){
      cout << "internal variables" << endl;
      for(int i = 0 ; i < cs.varInternalNames.size() ; i++)
         cout << cs.varInternalNames[i] << endl;
   }
   
   if(cs.netList2.size()==0){
      cout << "linear analysis" << endl;
      t = 0;
      cs.createSystem1(t);
      if(cs.solveSystem1()){
         cout << "unsolvable t = " << t << endl;
         outputFile.close();
         exit(1);
      }
      while(t <= cs.tFinal){
         /*cout << "resultado t = " << t << endl;
         for(int i = 0 ; i < cs.varNames.size() ; i++)
            cout << cs.varNames[i] << " = " << cs.prevResult1[i] << endl;*/
         outputFile << t;
         for(int i=0;i<cs.varNames.size();i++){
            int varPos = cs.findCol(cs.varNames[i]);
            if(varPos==-1)
               outputFile << " 0";
            else
               outputFile << " " << cs.prevResult1[varPos];
         }
         outputFile << endl;
         for(c=0;c<cs.internalStep;c++){
            t += cs.step/cs.internalStep;
            cs.createSystem1(t);
            if(cs.solveSystem1()){
               cout << "unsolvable t = " << t << endl;
               outputFile.close();
               exit(1);
            }
         }
      }
   }
   else{
      cout << "non linear analysis" << endl;
      t = 0;
      cs.createSystem1(t);
      for(d = 0 ; d < MAX_ITERATIONS ; d++){
         cs.createSystem2(t);
         if(cs.solveSystem2()){
            cout << "unsolvable t = " << t << " iteration = " << d << endl;
            outputFile.close();
            exit(1);
         } 
         if(cs.calcResultError()<ERROR_LIMIT)
            break;
      }
      if(d==MAX_ITERATIONS){
         cout << "exceeded max iterations t = " << t << endl;
         outputFile.close();
         exit(2);
      }
      while(t <= cs.tFinal){
         /*cout << "result t = " << t << endl; // here
         for(int i = 0 ; i < cs.varNames.size() ; i++)
            cout << cs.varNames[i] << " = " << cs.prevResult1[i] << endl;*/
         outputFile << t;
         cs.keepAprox();
         for(int i=0;i<cs.varNames.size();i++){
            int varPos = cs.findCol(cs.varNames[i]);
            if(varPos==-1)
               outputFile << " 0";
            else
               outputFile << " " << cs.prevResult1[varPos];
         }
         outputFile << endl;
         //cs.resetAprox();
         for(c=0;c<cs.internalStep;c++){
            t += cs.step/cs.internalStep;
            cs.createSystem1(t);
            for(d = 0 ; d < MAX_ITERATIONS ; d++){
               cs.createSystem2(t);
               if(cs.solveSystem2()){
                  cout << "unsolvable t = " << t << " iteration = " << d << endl;
                  outputFile.close();
                  exit(1);
               }
               if(cs.calcResultError()<ERROR_LIMIT)
                  break;
            }
            if(d==MAX_ITERATIONS){
               cout << "exceeded max iterations t = " << t << endl;
               outputFile.close();
               exit(2);
            }
         }
      }
   }
   
   outputFile.close();

   return 0;
}
