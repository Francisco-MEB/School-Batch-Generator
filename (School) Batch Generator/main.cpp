#include <array>
#include <fstream>
#include <iostream>
#include <vector>

#include "EnumDefs.h"
#include "Header.h"
#include "RandomNumGen.h"
#include "StructDefs.h"

int main()
{
    std::ifstream file_listOfStudents;
    std::string filePath_listOfStudents{getFilePath("containing list of students")};
    file_listOfStudents.open(filePath_listOfStudents, std::ios::in);
    if (!file_listOfStudents.is_open())
    {
        std::cerr << "Could not open file containing list of students." << '\n';
        return 1;
    }
    
    std::array<std::string, Specifications::numberOfColumns> headers{};
    readHeaders(file_listOfStudents, headers);
    
    std::vector<Student> students{};
    readStudentInformation(file_listOfStudents, students);
    
    file_listOfStudents.close();
    
    const int batchSize{static_cast<int>(students.size())};
    const int estimatedClassSize{getEstimatedClassSize(batchSize)};
    const int numberOfSections{getNumberOfSections(batchSize, estimatedClassSize)};
    
    std::vector<Section> batch(numberOfSections);
    assignIdentifiers(batch, numberOfSections);
    
    int unassignedStudents = batchSize % estimatedClassSize;
    
    assignStudentsToSections(batch, students, batchSize, numberOfSections, estimatedClassSize, unassignedStudents);
    assignClassSize(batch, numberOfSections);
    
    sortByLastNames(batch, numberOfSections);
    assignClassNumbers(batch, numberOfSections);
    
    // printBatch(batch, numberOfSections);
    
    std::ofstream file_classList;
    std::string filePath_classList{getFilePath("for putting new class lists")};
    file_classList.open(filePath_classList, std::ios::out);
    if (!file_classList.is_open())
    {
        std::cerr << "Could not open file for putting new class lists." << '\n';
        return 1;
    }
    
    writeClassLists(file_classList, batch, numberOfSections);
    
    file_classList.close();
    
    return 0;
}
