/*
 * Universidade Federal do Rio de Janeiro
 * Trabalho da disciplina Circuitos Elétricos 2
 * 2013/1
 * Por Ian Esteves do Nascimento e Igor Vital
 */

#include <fstream>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <cmath>
#include "circuitSimulator.h"
#include "myUti.h"

#include <iostream>

#define FIRST_STEP_TIME_RATIO 1e9

using namespace std;

circuitSimulator::~circuitSimulator(){
   for(int i = 0 ; i < netList1.size() ; i++)
      delete netList1[i];
   for(int i = 0 ; i < netList2.size() ; i++)
      delete netList2[i];
   for(int i = 0 ; i < netList3.size() ; i++)
      delete netList3[i];
   if(system1)
      matrixDelete(varNumber, system1);
   if(system2)
      matrixDelete(varNumber, system2);
   if(prevResult1)
      delete[] prevResult1;
   if(prevResult2)
      delete[] prevResult2;
   if(prevAprox1)
      delete[] prevAprox1;
   if(prevAprox2)
      delete[] prevAprox2;
}

int circuitSimulator::import(string fileName){
   int linePos;
   string newVarName;
   tFinal = 10;
   step = 0.1;
   internalStep = 10;
   ifstream netListFile(fileName.c_str());
   if(!netListFile.is_open())
      return 1;
   while(!netListFile.eof()){
      string line;
      char lineType;
      circuitElement *newElement;
      getline(netListFile, line);
      lineType = line[0];
      if(lineType == '.'){
         linePos = line.find(' ');
         line = line.substr(linePos+1);
         linePos = line.find(' ');
         tFinal = fromStr<double>(line.substr(0, linePos));
         line = line.substr(linePos+1);
         linePos = line.find(' ');
         step = fromStr<double>(line.substr(0, linePos));
         line = line.substr(linePos+1);
         linePos = line.find(' ');
         line = line.substr(linePos+1);
         linePos = line.find(' ');
         internalStep = fromStr<int>(line.substr(0, linePos));
         continue;
      }
      
      switch(lineType){
         case 'R':
            newElement = new circuitR;
            netList1.push_back(newElement);
            break;
         case 'L':
            newElement = new circuitL;
            netList1.push_back(newElement);
            break;
         case 'C':
            newElement = new circuitC;
            netList1.push_back(newElement);
            break;
         case 'E':
            newElement = new circuitE;
            netList1.push_back(newElement);
            break;
         case 'F':
            newElement = new circuitF;
            netList1.push_back(newElement);
            break;
         case 'G':
            newElement = new circuitG;
            netList1.push_back(newElement);
            break;
         case 'H':
            newElement = new circuitH;
            netList1.push_back(newElement);
            break;
         case 'I':
            newElement = new circuitI;
            netList1.push_back(newElement);
            break;
         case 'V':
            newElement = new circuitV;
            netList1.push_back(newElement);
            break;
         case 'O':
            newElement = new circuitO;
            netList3.push_back(newElement);
            break;
         case 'D':
            newElement = new circuitD;
            netList2.push_back(newElement);
            break;
         case 'Q':
            newElement = new circuitQ;
            netList2.push_back(newElement);
            break;
         default:
            continue;
      }
      newElement->parse(line);
      if(newElement->n1!=0){
         int i;
         newVarName = toStr(newElement->n1);
         for(i = 0 ; i < varNames.size() ; i++)
            if(varNames[i] == newVarName)
               break;
         if(i == varNames.size())
            varNames.push_back(newVarName);
      }
      if(newElement->n2!=0){
         int i;
         newVarName = toStr(newElement->n2);
         for(i = 0 ; i < varNames.size() ; i++)
            if(varNames[i] == newVarName)
               break;
         if(i == varNames.size())
            varNames.push_back(newVarName);
      }
      switch(lineType){
         case 'L':
            if(1){
               int i;
               newVarName = "j" + newElement->name;
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            break;
         case 'C':
            if(1){
               int i;
               newVarName = "j" + newElement->name;
               for(i = 0 ; i < varInternalNames.size() ; i++)
                  if(varInternalNames[i] == newVarName)
                     break;
               if(i == varInternalNames.size())
                  varInternalNames.push_back(newVarName);
            }
            break;
         case 'E':
            circuitE *ce;
            ce = (circuitE *)newElement;
            if(ce->n3!=0){
               int i;
               newVarName = toStr(ce->n3);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            if(ce->n4!=0){
               int i;
               newVarName = toStr(ce->n4);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            if(1){
               int i;
               newVarName = "j" + ce->name;
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            break;
         case 'F':
            circuitF *cf;
            cf = (circuitF *)newElement;
            if(cf->n3!=0){
               int i;
               newVarName = toStr(cf->n3);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            if(cf->n4!=0){
               int i;
               newVarName = toStr(cf->n4);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            if(1){
               int i;
               newVarName = "j" + cf->name;
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            break;
         case 'G':
            circuitG *cg;
            cg = (circuitG *)newElement;
            if(cg->n3!=0){
               int i;
               newVarName = toStr(cg->n3);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            if(cg->n4!=0){
               int i;
               newVarName = toStr(cg->n4);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            break;
         case 'H':
            circuitH *ch;
            ch = (circuitH *)newElement;
            if(ch->n3!=0){
               int i;
               newVarName = toStr(ch->n3);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            if(ch->n4!=0){
               int i;
               newVarName = toStr(ch->n4);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            if(1){
               int i;
               newVarName = "j" + ch->name;
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            if(1){
               int i;
               newVarName = "j" + ch->name + "2";
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            break;
         case 'V':
            if(1){
               int i;
               newVarName = "j" + newElement->name;
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            break;
         case 'O':
            circuitO *co;
            co = (circuitO *)newElement;
            if(co->n3!=0){
               int i;
               newVarName = toStr(co->n3);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            if(co->n4!=0){
               int i;
               newVarName = toStr(co->n4);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            break;
         case 'Q':
            circuitQ *cq;
            cq = (circuitQ *)newElement;
            if(cq->n3!=0){
               int i;
               newVarName = toStr(cq->n3);
               for(i = 0 ; i < varNames.size() ; i++)
                  if(varNames[i] == newVarName)
                     break;
               if(i == varNames.size())
                  varNames.push_back(newVarName);
            }
            break;
      }
   }
   
   sort(varNames.begin(), varNames.end());
   varNumber = varNames.size();
   
   sort(varInternalNames.begin(), varInternalNames.end());
   for(int i = 0 ; i < varInternalNames.size() ; i++)
      varInternal.push_back(0);
   
   for(int i = 0 ; i < varNumber ; i++){
      reducedLine.push_back(i);
      reducedCol.push_back(i);
   }
   
   for(int i = 0 ; i < netList3.size() ; i++){
      string varName;
      circuitO *co;
      co = (circuitO *)netList3[i];
      int line1, line2, col1, col2;
      if(co->n1==0)
         line1 = -1;
      else{
         varName = toStr(co->n1);
         for(int j = 0; varNames[j]<varName ; j++)
            line1 = j+1;
      }
      if(co->n2==0)
         line2 = -1;
      else{
         varName = toStr(co->n2);
         for(int j = 0; varNames[j]<varName ; j++)
            line2 = j+1;
      }
      if(co->n3==0)
         col1 = -1;
      else{
         varName = toStr(co->n3);
         for(int j = 0; varNames[j]<varName ; j++)
            col1 = j+1;
      }
      if(co->n4==0)
         col2 = -1;
      else{
         varName = toStr(co->n4);
         for(int j = 0; varNames[j]<varName ; j++)
            col2 = j+1;
      }
      if(line2<line1){
         int aux = line2;
         line2 = line1;
         line1 = aux;
      }
      if(col2<col1){
         int aux = col2;
         col2 = col1;
         col1 = aux;
      }
      if(line1>=0)
         reducedLine[line2] = reducedLine[line1];
      else
         reducedLine[line2] = -1;
      for(int j = line2+1 ; j < reducedLine.size() ; j++)
         reducedLine[j]--;
      if(col1>=0)
         reducedCol[col2] = reducedCol[col1];
      else
         reducedCol[col2] = -1;
      for(int j = col2+1 ; j < reducedCol.size() ; j++)
         reducedCol[j]--;
      varNumber--;
   }

   prevResult1 = new double[varNumber];
   prevResult2 = new double[varNumber];
   prevAprox1 = new double[varNumber];
   prevAprox2 = new double[varNumber];
   for(int i = 0 ; i < varNumber ; i++){
      prevResult1[i] = 0;
      prevResult2[i] = 0;
      prevAprox1[i] = 0;
      prevAprox2[i] = 0;
   }
   
   system1 = 0;
   system2 = 0;
   
   netListFile.close();
   return 0;
}

void circuitSimulator::createSystem1(double t){
   //cout << "montando sistema 1 t = " << t << endl;
   if(system1)
      matrixDelete(varNumber, system1);
   system1 = matrixNew(varNumber, varNumber+1);
   for(int i = 0 ; i < varNumber ; i++)
      for(int j = 0 ; j <= varNumber; j++)
         system1[i][j] = 0;
   for(int i = 0 ; i < netList1.size() ; i++){
      int line1, line2, line3, line4, line5, line6,
          col1, col2, col3, col4, col5, col6;
      double v1;
      char circuitType = netList1[i]->name[0];
      switch(circuitType){
         case 'R':
            circuitR *cr;
            cr = (circuitR *)netList1[i];
            line1 = findLine(toStr(cr->n1));
            col1 = findCol(toStr(cr->n1));
            line2 = findLine(toStr(cr->n2));
            col2 = findCol(toStr(cr->n2));
            if(line1>=0){
               if(col1>=0)
                  system1[line1][col1]+=1/cr->r;
               if(col2>=0)
                  system1[line1][col2]-=1/cr->r;
            }
            if(line2>=0){
               if(col1>=0)
                  system1[line2][col1]-=1/cr->r;
               if(col2>=0)
                  system1[line2][col2]+=1/cr->r;
            }
            break;
         case 'C':
            circuitC *cc;
            cc = (circuitC *)netList1[i];
            line1 = findLine(toStr(cc->n1));
            col1 = findCol(toStr(cc->n1));
            line2 = findLine(toStr(cc->n2));
            col2 = findCol(toStr(cc->n2));
            double gc, ic;
            int icPrev;
            icPrev = 0;
            while(varInternalNames[icPrev] < "j"+cc->name)
               icPrev++;
            if(col1 >= 0){
               if(col2 >= 0)
                  v1 = prevResult1[col1]-prevResult1[col2];
               else
                  v1 = prevResult1[col1];
            }
            else
               v1 = -prevResult1[col2];
            if(t == step/internalStep)
               v1/=2;
            if(t == 0){
               gc = internalStep*FIRST_STEP_TIME_RATIO*cc->c/step;
               ic = cc->ic*gc;
            }
            else{
               gc = 2*internalStep*cc->c/step;
               ic = 2*gc*v1-varInternal[icPrev];
            }
            varInternal[icPrev]=ic;
            
            if(line1>=0){
               if(col1>=0)
                  system1[line1][col1]+=gc;
               if(col2>=0)
                  system1[line1][col2]-=gc;
               system1[line1][varNumber]+=ic;
            }
            if(line2>=0){
               if(col1>=0)
                  system1[line2][col1]-=gc;
               if(col2>=0)
                  system1[line2][col2]+=gc;
               system1[line2][varNumber]-=ic;
            }
            if(t==0)
               varInternal[icPrev]=0;
            break;
         case 'L':
            circuitL *cl;
            cl = (circuitL *)netList1[i];
            line1 = findLine(toStr(cl->n1));
            col1 = findCol(toStr(cl->n1));
            line2 = findLine(toStr(cl->n2));
            col2 = findCol(toStr(cl->n2));
            line3 = findLine("j"+cl->name);
            col3 = findCol("j"+cl->name);
            double rl, vl;
            if(col1>=0){
               if(col2>=0)
                  v1 = prevResult1[col1]-prevResult1[col2];
               else
                  v1 = prevResult1[col1];
            }
            else
               v1 = -prevResult1[col2];
            if(t == 0){
               rl = internalStep*FIRST_STEP_TIME_RATIO*cl->l/step;
               vl = rl*cl->ic;
            }
            else{
               rl = 2*internalStep*cl->l/step;
               vl = rl*prevResult1[col3]+v1;
            }
            if(line1>=0)
               system1[line1][col3]+=1;
            if(line2>=0)
               system1[line2][col3]-=1;
            if(col1>=0)
               system1[line3][col1]-=1;
            if(col2>=0)
               system1[line3][col2]+=1;
            system1[line3][col3]+=rl;
            system1[line3][varNumber]+=vl;
            break;
         case 'E':
            circuitE *ce;
            ce = (circuitE *)netList1[i];
            line1 = findLine(toStr(ce->n1));
            line2 = findLine(toStr(ce->n2));
            line3 = findLine("j"+ce->name);
            col1 = findCol(toStr(ce->n1));
            col2 = findCol(toStr(ce->n2));
            col3 = findCol(toStr(ce->n3));
            col4 = findCol(toStr(ce->n4));
            col5 = findCol("j"+ce->name);
            if(line1>=0)
               system1[line1][col5]+=1;
            if(line2>=0)
               system1[line2][col5]-=1;
            if(col1>=0)
               system1[line3][col1]-=1;
            if(col2>=0)
               system1[line3][col2]+=1;
            if(col3>=0)
               system1[line3][col3]+=ce->av;
            if(col4>=0)
               system1[line3][col4]-=ce->av;
            break;
         case 'F':
            circuitF *cf;
            cf = (circuitF *)netList1[i];
            line1 = findLine(toStr(cf->n1));
            line2 = findLine(toStr(cf->n2));
            line3 = findLine(toStr(cf->n3));
            line4 = findLine(toStr(cf->n4));
            line5 = findLine("j"+cf->name);
            col1 = findCol(toStr(cf->n3));
            col2 = findCol(toStr(cf->n4));
            col3 = findCol("j"+cf->name);
            if(line1>=0)
               system1[line1][col3]+=cf->ai;
            if(line2>=0)
               system1[line2][col3]-=cf->ai;
            if(line3>=0)
               system1[line3][col3]+=1;
            if(line4>=0)
               system1[line4][col3]-=1;
            if(col1>=0)
               system1[line5][col1]-=1;
            if(col2>=0)
               system1[line5][col2]+=1;
            break;
         case 'G':
            circuitG *cg;
            cg = (circuitG *)netList1[i];
            line1 = findLine(toStr(cg->n1));
            line2 = findLine(toStr(cg->n2));
            col1 = findCol(toStr(cg->n3));
            col2 = findCol(toStr(cg->n4));
            if(line1>=0){
               if(col1>=0)
                  system1[line1][col1]+=cg->gm;
               if(col2>=0)
                  system1[line1][col2]-=cg->gm;
            }
            if(line2>=0){
               if(col1>=0)
                  system1[line2][col1]-=cg->gm;
               if(col2>=0)
                  system1[line2][col2]+=cg->gm;
            }
            break;
         case 'H':
            circuitH *ch;
            ch = (circuitH *)netList1[i];
            line1 = findLine(toStr(ch->n1));
            line2 = findLine(toStr(ch->n2));
            line3 = findLine(toStr(ch->n3));
            line4 = findLine(toStr(ch->n4));
            line5 = findLine("j"+ch->name);
            line6 = findLine("j"+ch->name+"2");
            col1 = findCol(toStr(ch->n1));
            col2 = findCol(toStr(ch->n2));
            col3 = findCol(toStr(ch->n3));
            col4 = findCol(toStr(ch->n4));
            col5 = findCol("j"+ch->name);
            col6 = findCol("j"+ch->name+"2");
            if(line1>=0)
               system1[line1][col5]+=1;
            if(line2>=0)
               system1[line2][col5]-=1;
            if(line3>=0)
               system1[line3][col6]+=1;
            if(line4>=0)
               system1[line4][col6]-=1;
            if(col1>=0)
               system1[line5][col1]-=1;
            if(col2>=0)
               system1[line5][col2]+=1;
            if(col3>=0)
               system1[line6][col3]+=1;
            if(col4>=0)
               system1[line6][col4]+=1;
            system1[line5][col6]+=ch->rm;
            break;
         case 'I':
            circuitI *ci;
            ci = (circuitI *)netList1[i];
            line1 = findLine(toStr(ci->n1));
            line2 = findLine(toStr(ci->n2));
            if(line1>=0)
               system1[line1][varNumber]-=ci->i(t);
            if(line2>=0)
               system1[line2][varNumber]+=ci->i(t);
            break;
         case 'V':
            circuitV *cv;
            cv = (circuitV *)netList1[i];
            line1 = findLine(toStr(cv->n1));
            col1 = findCol(toStr(cv->n1));
            line2 = findLine(toStr(cv->n2));
            col2 = findCol(toStr(cv->n2));
            line3 = findLine("j"+cv->name);
            col3 = findCol("j"+cv->name);
            if(col3>=0){
               if(line1>=0)
                  system1[line1][col3]+=1;
               if(line2>=0)
                  system1[line2][col3]-=1;
            }
            if(line3>=0){
               if(col2>=0)
                  system1[line3][col2]+=1;
               if(col1>=0)
                  system1[line3][col1]-=1;
               system1[line3][varNumber]-=cv->v(t);
            }
            break;
      }
   }
   /*for(int i = 0 ; i < varNumber ; i++){
      for(int j = 0 ; j <= varNumber ; j++)
         cout << system1[i][j] << '\t';
      cout << endl;
   }*/
}

void circuitSimulator::createSystem2(double t){
   //cout << "montando sistema 2 t = " << t << endl;
   if(system2)
      matrixDelete(varNumber, system2);
   system2 = matrixNew(varNumber, varNumber+1, system1);
   for(int i = 0 ; i < netList2.size() ; i++){
      int line1, line2, line3,
          col1, col2, col3;
      char circuitType = netList2[i]->name[0];
      switch(circuitType){
         case 'D':
            circuitD *cd;
            cd = (circuitD *)netList2[i];
            line1 = findLine(toStr(cd->n1));
            col1 = findCol(toStr(cd->n1));
            line2 = findLine(toStr(cd->n2));
            col2 = findCol(toStr(cd->n2));
            double go, io, v1;
            if(col1>=0){
               if(col2>=0)
                  v1 = prevAprox1[col1]-prevAprox1[col2];
               else
                  v1 = prevAprox1[col1];
            }
            else
               v1 = -prevAprox1[col2];
            if(v1 > 0.7)
               v1 = 0.7;
            if(v1 < -0.2)
               v1 = -0.2;
            go = cd->didv(v1);
            io = cd->i(v1)-go*v1;
            if(line1>=0){
               if(col1>=0)
                  system2[line1][col1]+=go;
               if(col2>=0)
                  system2[line1][col2]-=go;
               system2[line1][varNumber]-=io;
            }
            if(line2>=0){
               if(col1>=0)
                  system2[line2][col1]-=go;
               if(col2>=0)
                  system2[line2][col2]+=go;
               system2[line2][varNumber]+=io;
            }
            break;
         case 'Q':
            circuitQ *cq;
            cq = (circuitQ *)netList2[i];
            line1 = findLine(toStr(cq->n1));
            col1 = findCol(toStr(cq->n1));
            line2 = findLine(toStr(cq->n2));
            col2 = findCol(toStr(cq->n2));
            line3 = findLine(toStr(cq->n3));
            col3 = findCol(toStr(cq->n3));
            double go1, io1, go2, io2, g1, g2, g3, IO, vbe, vbc, vce;
            if(col1>=0){
               if(col2>=0){
                  if(col3>=0){
                     vbe = prevAprox1[col2]-prevAprox1[col3];
                     vbc = prevAprox1[col2]-prevAprox1[col1];
                     vce = prevAprox1[col1]-prevAprox1[col3];
                  }
                  else{
                     vbe = prevAprox1[col2];
                     vbc = prevAprox1[col2]-prevAprox1[col1];
                     vce = prevAprox1[col1];
                  }
               }
               else{
                  vbe = -prevAprox1[col3];
                  vbc = -prevAprox1[col1];
                  vce = prevAprox1[col1]-prevAprox1[col3];
               }
            }
            else{
               vbe = prevAprox1[col2]-prevAprox1[col3];
               vbc = prevAprox1[col2];
               vce = -prevAprox1[col3];
            }
            if(vbe > 5)
               vbe = 5;
            if(vbe < -5)
               vbe = -5;
            if(vbc > 5)
               vbc = 5;
            if(vbc < -5)
               vbc = -5;
            go1 = cq->di1dv(vbe);
            io1 = cq->i1(vbe)-go1*vbe;
            go2 = cq->di2dv(vbc);
            io2 = cq->i2(vbc)-go2*vbc;
            g1 = 0;
            g2 = 0;
            g3 = 0;
            IO = 0;
            /*g1 = cq->alpha*go1*vce/cq->va; // EFEITO EARLY
            g2 = -go2*vce/cq->va;
            g3 = (cq->alpha*cq->i1(vbe)-cq->i2(vbc))/cq->va;
            IO = (cq->alpha*cq->i1(vbe)-cq->i2(vbe))*vce/cq->va-g1*vbe-g2*vbc-g3*vce;*/
            if(line1>=0){
               if(col1>=0){
                  system2[line1][col1]+=go2;
                  system2[line1][col1]-=g2;
                  system2[line1][col1]+=g3;
               }
               if(col2>=0){
                  system2[line1][col2]-=go2;
                  system2[line1][col2]+=cq->alpha*go1;
                  system2[line1][col2]+=g1;
                  system2[line1][col2]+=g2;
               }
               if(col3>=0){
                  system2[line1][col3]-=cq->alpha*go1;
                  system2[line1][col3]-=g1;
                  system2[line1][col3]-=g3;
               }
               system2[line1][varNumber]+=io2;
               system2[line1][varNumber]-=cq->alpha*io1;
               system2[line1][varNumber]-=IO;
            }
            if(line2>=0){
               if(col1>=0){
                  system2[line2][col1]-=go2;
                  system2[line2][col1]+=cq->alphar*go2;
               }
               if(col2>=0){
                  system2[line2][col2]+=go2;
                  system2[line2][col2]+=go1;
                  system2[line2][col2]-=cq->alpha*go1;
                  system2[line2][col2]-=cq->alphar*go2;
               }
               if(col3>=0){
                  system2[line2][col3]-=go1;
                  system2[line2][col3]+=cq->alpha*go1;
               }
               system2[line2][varNumber]-=io1;
               system2[line2][varNumber]-=io2;
               system2[line2][varNumber]+=cq->alpha*io1;
               system2[line2][varNumber]+=cq->alphar*io2;
            }
            if(line3>=0){
               if(col1>=0){
                  system2[line3][col1]-=cq->alphar*go2;
                  system2[line3][col1]+=g2;
                  system2[line3][col1]-=g3;
               }
               if(col2>=0){
                  system2[line3][col2]-=go1;
                  system2[line3][col2]+=cq->alphar*go2;
                  system2[line3][col2]-=g1;
                  system2[line3][col2]-=g2;
               }
               if(col3>=0){
                  system2[line3][col3]+=go1;
                  system2[line3][col3]+=g1;
                  system2[line3][col3]+=g3;
               }
               system2[line3][varNumber]+=io1;
               system2[line3][varNumber]-=cq->alphar*io2;
               system2[line3][varNumber]+=IO;
            }
            break;
      }
   }
   /*for(int i = 0 ; i < varNumber ; i++){
      for(int j = 0 ; j <= varNumber ; j++)
         cout << system2[i][j] << '\t';
      cout << endl;
   }*/
}

int circuitSimulator::solveSystem1(void){
   double *result = matrixSolveSystem(varNumber, system1);
   if(result == 0)
      return 1;
   delete[] prevResult2;
   prevResult2 = prevResult1;
   prevResult1 = result;
   return 0;
}

int circuitSimulator::solveSystem2(void){
   double *result = matrixSolveSystem(varNumber, system2);
   if(result == 0)
      return 1;
   delete[] prevAprox2;
   prevAprox2 = prevAprox1;
   prevAprox1 = result;
   return 0;
}

int circuitSimulator::findLine(string varName){
   if(varName == "0")
      return -1;
   int result = 0;
   while(varNames[result] < varName)
      result++;
   return reducedLine[result];
}

int circuitSimulator::findCol(string varName){
   if(varName == "0")
      return -1;
   int result = 0;
   while(varNames[result] < varName)
      result++;
   return reducedCol[result];
}

double circuitSimulator::calcResultError(void){
   double result = 0;
   double newResult;
   for(int i = 0 ; i < varNumber ; i++){
      if(prevAprox2[i]==0){
         if(prevAprox1[i]==0)
            continue;
         return 9999;
      }
      newResult = (prevAprox1[i]-prevAprox2[i])/prevAprox2[i];
      if(newResult<0)
         newResult = -newResult;
      if(newResult>result)
         result = newResult;
   }
   return result;
}

void circuitSimulator::keepAprox(){
   delete[] prevResult2;
   prevResult2 = prevResult1;
   prevResult1 = prevAprox1;
}

void circuitSimulator::resetAprox(){
   for(int i = 0 ; i < varNumber ; i++){
      prevAprox1[i] = 0;
      prevAprox2[i] = 0;
   }
}

void circuitSimulator::disableIC(){
   for(int i = 0 ; i < netList1.size() ; i++){
      if(netList1[i]->name[0] == 'C'){
         circuitC *cc;
         cc = (circuitC *)netList1[i];
         cc->ic = 0;
      }
      if(netList1[i]->name[0] == 'L'){
         circuitL *cl;
         cl = (circuitL *)netList1[i];
         cl->ic = 0;
      }
   }
}
