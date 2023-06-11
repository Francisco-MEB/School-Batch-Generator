#ifndef HEADER_H
#define HEADER_H

#include <array>
#include <fstream>
#include <string>
#include <vector>

#include "EnumDefs.h"
#include "StructDefs.h"

bool confirmFilePath(const std::string& filePath);
std::string getFilePath(const std::string& request);
void readHeaders(std::ifstream& file, std::array<std::string, 4>& headers);
void readStudentInformation(std::ifstream& file, std::vector<Student>& students);
int getEstimatedClassSize(int batchSize);
int getNumberOfSections(int batchSize, int estimatedClassSize);
void assignIdentifiers(std::vector<Section>& batch, int numberOfSections);
void assignStudentsToSections(std::vector<Section>& batch, const std::vector<Student>& students, int batchSize, int numberOfSections, int estimatedClassSize, int unassignedStudents);
void assignClassSize(std::vector<Section>& batch, int numberOfSections);
bool compareLastNames(const Student& name, const Student& anotherName);
void sortByLastNames(std::vector<Section>& batch, int numberOfSections);
void assignClassNumbers(std::vector<Section>& batch, int numberOfSections);
std::string fullyCapitalize(const std::string& name);
[[maybe_unused]] void printBatch(std::vector<Section>& batch, int numberOfSections);
void writeClassLists(std::ofstream& file, const std::vector<Section>& batch, int numberOfSections);

namespace Specifications
{
    inline constexpr int numberOfColumns{4};
    inline const std::string headerRowInCSV{"FirstName,MiddleName,LastName,Suffix"};
    inline constexpr int maximumClassSize{40};
    inline constexpr int maximumAllowance{3};
    inline std::array<std::string, 2> newHeaders{"CN", "Name"};
};

#endif
