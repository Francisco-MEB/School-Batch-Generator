#ifndef STRUCTDEFS_H
#define STRUCTDEFS_H

#include <vector>

#include "EnumDefs.h"

struct Student
{
    int classNumber{};
    std::string firstName{};
    std::string lastName{};
};

struct Section
{
    SectionIdentifier identifier{};
    int classSize{};
    std::vector<Student> students{};
};

#endif

