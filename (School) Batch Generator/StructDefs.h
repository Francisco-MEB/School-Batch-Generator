#ifndef STRUCTDEFS_H
#define STRUCTDEFS_H

#include <vector>

#include "EnumDefs.h"

struct Student
{
    int classNumber{};
    std::string firstName{};
    std::string middleName{};
    std::string lastName{};
    std::string suffix{};
};

struct Section
{
    SectionIdentifier identifier{};
    int classSize{};
    std::vector<Student> students{};
};

#endif
