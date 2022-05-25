/**
 * COPYRIGHT NOTICE
 * Copyright (c) 2012, Institute of CG & CAD, Tsinghua University.
 * All Rights Reserved.
 * 
 * @file    Solver.cpp
 * @brief   Solver class declaration.
 * 
 * This file declares ...
 * 
 * @version 1.0
 * @author  Jackie Pang
 * @e-mail: 15pengyi@gmail.com
 * @date    2012/10/10
 */

#include <iostream>

#include "Solver.h"

Solver::Solver()
    : error(true)
{}

Solver::~Solver()
{
    if (inputStream) inputStream.close();
}

Solver::Solver(const std::string &fileName)
    : error(false)
{
    inputStream.open(fileName.c_str());
    if (!inputStream)
    {
        std::cerr << " > ERROR: unable to open input file: \"" << fileName << "\"." <<  std::endl;
        error = true;
    }
}

const std::string Solver::GetAnswer()
{
    if (error) outputStream.str("ERROR");
    return outputStream.str();
}

void Solver::Solve(std::istream &inputStream, std::ostream &outputStream)
{

}