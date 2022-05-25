/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    USSolver.h
 * @brief   USSolver class declaration.
 * 
 * This file defines ...
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail: 15pengyi@gmail.com
 * @date    2012/10/10
 */

#ifndef USSOLVER_H
#define USSOLVER_H

#include "Solver.h"

class USSolver : public Solver
{
public:
    USSolver()
    {};

    USSolver(const std::string &fileName)
        : Solver(fileName)
    {
        Solve(inputStream, outputStream);
    }
    ~USSolver()
    {};

    virtual void Solve(std::istream &inputStream, std::ostream &outputStream);
};

#endif // USSOLVER_H