/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    Solver.h
 * @brief   Solver class declaration.
 * 
 * This file defines ...
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail: 15pengyi@gmail.com
 * @date    2012/10/10
 */

#ifndef SOLVER_H
#define SOLVER_H

#include <fstream>
#include <sstream>
#include <string>

class Solver
{
public:
    Solver();
    Solver(const std::string &fileName);
    ~Solver();

    virtual void Solve(std::istream &inputStream, std::ostream &outputStream);
    const std::string GetAnswer();

protected:
    std::ifstream inputStream;
    std::ostringstream outputStream;
    bool error;
};

#endif // SOLVER_H