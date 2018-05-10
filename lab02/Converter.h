#pragma once

#include "Matrix.h"

class Converter {
  public:
    virtual void convertRepresentation(Matrix* matrix, RepresentationType to)=0;
    virtual ~Converter() {};
};

class AdjacencyListConverter: public Converter {
public:
    void convertRepresentation(Matrix* matrix, RepresentationType to) override;
    ~AdjacencyListConverter() override= default;

private:
    void adjListToAdjMat(Matrix *matrix);
    void adjListToIncMat(Matrix* matrix);
};


class AdjacencyMatrixConverter: public Converter {
public:
    void convertRepresentation(Matrix* matrix, RepresentationType to) override;
    ~AdjacencyMatrixConverter() override= default;

private:
    void adjMatToAdjList(Matrix* matrix);
    void adjMatToIncMat(Matrix* matrix);
};

class IncidenceMatrixConverter: public Converter {
public:
    void convertRepresentation(Matrix* matrix, RepresentationType to) override;
    ~IncidenceMatrixConverter() override= default;

private:
    void incMatToAdjMat(Matrix* matrix);
    void incMatToAdjList(Matrix* matrix);
};

class DegreeSequenceConverter: public Converter {
public:
  void convertRepresentation(Matrix* matrix, RepresentationType to) override;
  ~DegreeSequenceConverter() override= default;

private:
    void degreeSeqToAdjList(Matrix* matrix);
};
