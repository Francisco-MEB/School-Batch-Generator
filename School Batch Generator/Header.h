#ifndef HEADER_H
#define HEADER_H

#include <vector>

#include "EnumDefs.h"
#include "StructDefs.h"

namespace Limitations
{
    inline constexpr int minimumSections{1};
    inline constexpr int maximumSections{26};
    inline constexpr int minimumStudentsPerClass{5};
    inline constexpr int maximumStudentsPerClass{50};
}

void troubleshoot();
int getNumberOfSections();
SectionIdentifier assignSectionIdentifier(int index);
int getClassSize();
bool checkIfValidName(const std::string& name);
void fullyCapitalize(std::string& lastName);
std::string getFirstName();
std::string getLastName();
bool compareLastNames(const Student& student, const Student& anotherStudent);
void getFullNames(std::vector<Student>& section);
void sortAlphabetically(std::vector<Student>& section);
void assignClassNumbers(std::vector<Student>& section);
void printBatch(std::vector<Section>& batch);

#endif

