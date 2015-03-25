/*
 * Universidade Federal do Rio de Janeiro
 * Trabalho da disciplina Circuitos Elétricos 2
 * 2013/1
 * Por Ian Esteves do Nascimento e Igor Vital
 */

#include <string>
#include <vector>

#ifndef NETLIST_H
#define NETLIST_H

class circuitElement{
   public:
      std::string name;
      int n1, n2;
      virtual void parse(std::string info) = 0;
};

class circuitR : public circuitElement{
   public:
      double r;
      void parse(std::string line);
};

class circuitL : public circuitElement{
   public:
      double l, ic;
      void parse(std::string line);
};

class circuitC : public circuitElement{
   public:
      double c, ic;
      void parse(std::string line);
};

class circuitE : public circuitElement{
   public:
      double av;
      int n3, n4;
      void parse(std::string line);
};

class circuitF : public circuitElement{
   public:
      double ai;
      int n3, n4;
      void parse(std::string line);
};

class circuitG : public circuitElement{
   public:
      double gm;
      int n3, n4;
      void parse(std::string line);
};

class circuitH : public circuitElement{
   public:
      double rm;
      int n3, n4;
      void parse(std::string line);
};

class circuitI : public circuitElement{
   public:
      std::string signalType;
      double param[8];
      double i(double t);
      void parse(std::string line);
};

class circuitV : public circuitElement{
   public:
      std::string signalType;
      double param[8];
      double v(double t);
      void parse(std::string line);
};

class circuitO : public circuitElement{
   public:
      int n3, n4;
      void parse(std::string line);
};

class circuitD : public circuitElement{
   public:
      double is, vt;
      double i(double v);
      double didv(double v);
      void parse(std::string line);
};

class circuitQ : public circuitElement{
   public:
      int n3;
      double alpha, alphar, isbe, vtbe, isbc, vtbc, va;
      std::string transistorType;
      double i1(double v);
      double di1dv(double v);
      double i2(double v);
      double di2dv(double v);
      void parse(std::string line);
};

#endif	/* NETLIST_H */
