#ifndef _EXRR_H_
#define _EXRR_H_

#include <iostream>
#include <sstream>

class Expression {
 public:
  Expression() {}
  virtual std::string toString() const = 0;
  virtual ~Expression() {}
};

class NumExpression : public Expression {
 public:
  long num;
  NumExpression() {}
  NumExpression(long n) : num(n) {}
  virtual std::string toString() const {
    std::stringstream result;
    result << num;
    return result.str();
  }
  virtual ~NumExpression() {}
};

class PlusExpression : public Expression {
 public:
  Expression * lhs;
  Expression * rhs;
  PlusExpression() {}
  PlusExpression(Expression * l, Expression * r) {
    this->lhs = l;
    this->rhs = r;
  }
  virtual std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " + " << rhs->toString() << ")";
    return result.str();
  }
  virtual ~PlusExpression() {
    delete rhs;
    delete lhs;
  }
};
class MinusExpression : public Expression {
 public:
  Expression * lhs;
  Expression * rhs;
  MinusExpression() {}
  MinusExpression(Expression * l, Expression * r) {
    this->lhs = l;
    this->rhs = r;
  }
  virtual std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " - " << rhs->toString() << ")";
    return result.str();
  }
  virtual ~MinusExpression() {
    delete rhs;
    delete lhs;
  }
};
class TimesExpression : public Expression {
 public:
  Expression * lhs;
  Expression * rhs;
  TimesExpression() {}
  TimesExpression(Expression * l, Expression * r) {
    this->lhs = l;
    this->rhs = r;
  }
  virtual std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " * " << rhs->toString() << ")";
    return result.str();
  }
  virtual ~TimesExpression() {
    delete rhs;
    delete lhs;
  }
};
class DivExpression : public Expression {
 public:
  Expression * lhs;
  Expression * rhs;
  DivExpression() {}
  DivExpression(Expression * l, Expression * r) {
    this->lhs = l;
    this->rhs = r;
  }
  virtual std::string toString() const {
    std::stringstream result;
    result << "(" << lhs->toString() << " / " << rhs->toString() << ")";
    return result.str();
  }
  virtual ~DivExpression() {
    delete rhs;
    delete lhs;
  }
};

#endif
