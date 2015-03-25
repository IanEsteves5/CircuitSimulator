/*
 * Universidade Federal do Rio de Janeiro
 * Trabalho da disciplina Circuitos Elétricos 2
 * 2013/1
 * Por Ian Esteves do Nascimento e Igor Vital
 */

#include <string>
#include <vector>
#include <fstream>
#define _USE_MATH_DEFINES
#include <cmath>
#include "netList.h"
#include "myUti.h"

using namespace std;

void circuitR::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   r = fromStr<double>(line);
}

void circuitL::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   if(linePos == string::npos){
      l = fromStr<double>(line);
      ic = 0;
      return;
   }
   l = fromStr<double>(line.substr(0, linePos));
   line = line.substr(linePos+4);
   ic = fromStr<double>(line);
}

void circuitC::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   if(linePos == string::npos){
      c = fromStr<double>(line);
      ic = 0;
      return;
   }
   c = fromStr<double>(line.substr(0, linePos));
   line = line.substr(linePos+4);
   ic = fromStr<double>(line);
}

void circuitE::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n3 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n4 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   av = fromStr<double>(line);
}

void circuitF::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n3 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n4 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   ai = fromStr<double>(line);
}

void circuitG::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n3 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n4 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   gm = fromStr<double>(line);
}

void circuitH::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n3 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n4 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   rm = fromStr<double>(line);
}

void circuitI::parse(string line){
   int numParam;
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   signalType = line.substr(0, linePos);
   line = line.substr(linePos+1);
   switch(signalType[0]){
      case 'D':
         numParam = 1;
         break;
      case 'S':
         numParam = 7;
         break;
      case 'P':
         numParam = 8;
   }
   for(int i = 0 ; i < numParam-1 ; i++){
      linePos = line.find(' ');
      param[i] = fromStr<double>(line.substr(0, linePos));
      line = line.substr(linePos+1);
   }
   param[numParam-1] = fromStr<double>(line);
}

void circuitV::parse(string line){
   int numParam;
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   signalType = line.substr(0, linePos);
   line = line.substr(linePos+1);
   switch(signalType[0]){
      case 'D':
         numParam = 1;
         break;
      case 'S':
         numParam = 7;
         break;
      case 'P':
         numParam = 8;
   }
   for(int i = 0 ; i < numParam-1 ; i++){
      linePos = line.find(' ');
      param[i] = fromStr<double>(line.substr(0, linePos));
      line = line.substr(linePos+1);
   }
   param[numParam-1] = fromStr<double>(line);
}

void circuitO::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n3 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   n4 = fromStr<int>(line);
}

void circuitD::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   if(linePos == string::npos){
      n2 = fromStr<int>(line);
      is = 3.7751345e-14;
      vt = 25e-3;
      return;
   }
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   is = fromStr<double>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   vt = fromStr<double>(line);
}

void circuitQ::parse(string line){
   int linePos = line.find(' ');
   name = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n1 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n2 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   n3 = fromStr<int>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   if(linePos == string::npos){
      transistorType = line;
      alpha = 0.99;
      alphar = 0.5;
      isbe = 3.7751345e-14;
      vtbe = 25e-3;
      isbc = 3.7751345e-14;
      vtbc = 25e-3;
      va = 100;
      return;
   }
   transistorType = line.substr(0, linePos);
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   alpha = fromStr<double>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   alphar = fromStr<double>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   isbe = fromStr<double>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   vtbe = fromStr<double>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   isbc = fromStr<double>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   linePos = line.find(' ');
   vtbc = fromStr<double>(line.substr(0, linePos));
   line = line.substr(linePos+1);
   va = fromStr<double>(line);
}

double circuitI::i(double t){
   if(signalType == "SIN"){
      if(t<=param[3]||t>=param[3]+param[6]/param[2])
         return param[0]+param[1]*sin(param[5]*M_PI/180);
      return param[0]+param[1]*exp((param[3]-t)*param[4])*sin(2*M_PI*param[2]*(t-param[3])+param[5]*M_PI/180);
   }
   if(signalType == "PULSE"){
      if(t<=param[2]||t>=param[2]+param[6]*param[7])
         return param[0];
      t -= param[2];
      while(t > param[6])
         t -= param[6];
      if(t < param[3])
         return param[0]+t*(param[1]-param[0])/param[3];
      t -= param[3];
      if(t < param[5])
         return param[1];
      t -= param[5];
      if(t < param[4])
         return param[1]-t*(param[1]-param[0])/param[3];
      return param[0];
   }
   return param[0];
}

double circuitV::v(double t){
   if(signalType == "SIN"){
      if(t<=param[3]||t>=param[3]+param[6]/param[2])
         return param[0]+param[1]*sin(param[5]*M_PI/180);
      return param[0]+param[1]*exp((param[3]-t)*param[4])*sin(2*M_PI*param[2]*(t-param[3])+param[5]*M_PI/180);
   }
   if(signalType == "PULSE"){
      if(t<=param[2]||t>=param[2]+param[6]*param[7])
         return param[0];
      t -= param[2];
      while(t > param[6])
         t -= param[6];
      if(t < param[3])
         return param[0]+t*(param[1]-param[0])/param[3];
      t -= param[3];
      if(t < param[5])
         return param[1];
      t -= param[5];
      if(t < param[4])
         return param[1]-t*(param[1]-param[0])/param[3];
      return param[0];
   }
   return param[0];
}

double circuitD::i(double v){
   return is*(exp(v/vt)-1);
}

double circuitD::didv(double v){
   return is*exp(v/vt)/vt;
}

double circuitQ::i1(double v){
   return isbe*(exp(v/vtbe)-1);
}

double circuitQ::di1dv(double v){
   return isbe*exp(v/vtbe)/vtbe;
}

double circuitQ::i2(double v){
   return isbc*(exp(v/vtbc)-1);
}

double circuitQ::di2dv(double v){
   return isbc*exp(v/vtbc)/vtbc;
}
