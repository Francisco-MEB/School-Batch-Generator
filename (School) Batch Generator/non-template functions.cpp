#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "EnumDefs.h"
#include "Header.h"
#include "RandomNumGen.h"
#include "StructDefs.h"

bool confirmFilePath(const std::string& filePath)
{
    char confirm{};
    do
    {
        std::cout << "Are you sure " << filePath << " is the correct file path (y, n)? ";
        std::cin >> confirm;
        confirm = tolower(confirm);
    } while (confirm != 'y' && confirm != 'n');
    
    switch (confirm)
    {
        case 'y': return true;
        case 'n': return false;
        default: return false;
    }
}

std::string getFilePath(const std::string& request)
{
    std::string filePath{};
    bool correctPath{false};
    do
    {
        std::cout << "Enter file path " << request << ": ";
        std::getline(std::cin >> std::ws, filePath);
        
        correctPath = confirmFilePath(filePath);
    } while (correctPath == false);
    
    return filePath;
}

void readHeaders(std::ifstream& file, std::array<std::string, 4>& headers)
{
    std::string line{};
    while (std::getline(file, line))
    {
        if (line.find(Specifications::headerRowInCSV) != std::string::npos)
        {
            for (int i = 0, j = 0; j < Specifications::headerRowInCSV.length(); ++j)
            {
                if (Specifications::headerRowInCSV[j] != ',')
                {
                    headers[i] += Specifications::headerRowInCSV[j];
                }
                else if (j == 0 && Specifications::headerRowInCSV[j] == ',')
                {
                    continue;
                }
                else if (Specifications::headerRowInCSV[j] == ',' && (Specifications::headerRowInCSV[j - 1] == ',' || Specifications::headerRowInCSV[j + 1] == ','))
                {
                    continue; 
                }
                else
                {
                    ++i;
                    continue;
                }
            }
            
            break;
        }
    }
}

void readStudentInformation(std::ifstream& file, std::vector<Student>& students)
{
    std::string line{};
    while (std::getline(file, line))
    {
        Student student{};
        std::istringstream iss(line);
        std::string val{};
        for (int i = 0; i < Specifications::numberOfColumns; ++i)
        {
            if (!std::getline(iss, val, ','))
            {
                break;
            }
            
            switch (i)
            {
                case 0: student.firstName = val;
                    break;
                case 1: student.middleName = val;
                    break;
                case 2: student.lastName = val;
                    break;
                case 3: student.suffix = val;
                    break;
            }
        }
        
        students.push_back(student);
    }
}

int getEstimatedClassSize(int batchSize)
{
    int estimatedClassSize{};
    for (int i = 2; i == 2 || estimatedClassSize > Specifications::maximumClassSize; ++i)
    {
        estimatedClassSize = floor(batchSize / i);
    }
    
    return estimatedClassSize;
}

int getNumberOfSections(int batchSize, int estimatedClassSize)
{
    return floor(batchSize / estimatedClassSize);
}

void assignIdentifiers(std::vector<Section>& batch, int numberOfSections)
{
    for (int i = 0; i < numberOfSections; ++i)
    {
        batch[i].identifier = static_cast<SectionIdentifier>(i);
    }
}

void assignStudentsToSections(std::vector<Section>& batch, const std::vector<Student>& students, int batchSize, int numberOfSections, int estimatedClassSize, int unassignedStudents)
{
    for (int i = 0; i < batchSize - unassignedStudents; ++i)
    {
        int section{};
        do
        {
            section = Random::get(0, numberOfSections - 1);
        } while (batch[section].students.size() > estimatedClassSize);
        
        batch[section].students.push_back(students[i]);
    }
    
    if (unassignedStudents != 0)
    {
        for (int i = 0; i < unassignedStudents; ++i)
        {
            int section{};
            do
            {
                section = Random::get(0, numberOfSections - 1);
            } while (batch[section].students.size() > estimatedClassSize + Specifications::maximumAllowance);
            
            batch[section].students.push_back(students[batchSize - unassignedStudents - 1 + i]);
        }
    }
}

void assignClassSize(std::vector<Section>& batch, int numberOfSections)
{
    for (int i = 0; i < numberOfSections; ++i)
    {
        batch[i].classSize = static_cast<int>(batch[i].students.size());
    }
}

bool compareLastNames(const Student& name, const Student& anotherName)
{
    return name.lastName < anotherName.lastName;
}

void sortByLastNames(std::vector<Section>& batch, int numberOfSections)
{
    for (int i = 0; i < numberOfSections; ++i)
    {
        std::sort(batch[i].students.begin(), batch[i].students.end(), compareLastNames);
    }
}

void assignClassNumbers(std::vector<Section>& batch, int numberOfSections)
{
    for (int i = 0; i < numberOfSections; ++i)
    {
        for (int j = 0; j < batch[i].classSize; ++j)
        {
            batch[i].students[j].classNumber = j + 1;
        }
    }
}

std::string fullyCapitalize(const std::string& name)
{
    std::string capitalizedName{};
    for (int i = 0; i < name.length(); ++i)
    {
        capitalizedName += toupper(name[i]);
    }
    
    return capitalizedName;
}

[[maybe_unused]] void printBatch(std::vector<Section>& batch, int numberOfSections)
{
    std::cout << '\n';
    for (int i = 0; i < numberOfSections; ++i)
    {
        std::cout << "SECTION " << batch[i].identifier << '\n';
        for (int j = 0; j < batch[i].classSize; ++j)
        {
            std::cout << "CN "
            << batch[i].students[j].classNumber << '\t'
            << batch[i].students[j].firstName << ' '
            << batch[i].students[j].middleName << ' '
            << fullyCapitalize(batch[i].students[j].lastName) << ' '
            << batch[i].students[j].suffix << '\n';
        }
        std::cout << '\n';
    }
}

void writeClassLists(std::ofstream& file, const std::vector<Section>& batch, int numberOfSections)
{
    for (int i = 0; i < numberOfSections; ++i)
    {
        file << "SECTION " << batch[i].identifier << '\n';
        for (int j = 0; j < Specifications::newHeaders.size(); ++j)
        {
            file << Specifications::newHeaders[j] << ',';
        }
        file << '\n';
        
        for (int j = 0; j < batch[i].classSize; ++j)
        {
            file << batch[i].students[j].classNumber << ','
            << fullyCapitalize(batch[i].students[j].lastName) << ' '
            << batch[i].students[j].firstName << ' '
            << batch[i].students[j].middleName << '\n';
        }
        file << '\n';
    }
}
