#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <vector>

#include "Header.h"

void troubleshoot()
{
    std::cout << "ERROR: Invalid Input" << '\n';
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int getNumberOfSections()
{
    int numberOfSections{};
    do
    {
        if (std::cin.fail())
        {
            troubleshoot();
        }
        std::cout << "Number of sections: ";
        std::cin >> numberOfSections;
    } while (std::cin.fail() || numberOfSections < 0 || numberOfSections > Limitations::maximumNumberOfSections);
    
    return numberOfSections;
}

void assignIdentifiers(std::vector<Section>& sections)
{
    for (int i = 0; i < sections.size(); ++i)
    {
        SectionIdentifier letter{static_cast<SectionIdentifier>(i)};
        sections[i].identifier = letter;
    }
}

int getNumberOfStudentsInSection(SectionIdentifier identifier)
{
    int numberOfStudentsInSection{};
    do
    {
        if (std::cin.fail())
        {
            troubleshoot();
        }
        std::cout << "Number of students in Section " << identifier << ": ";
        std::cin >> numberOfStudentsInSection;
    } while (std::cin.fail() || numberOfStudentsInSection < Limitations::minimumNumberOfStudentsPerSection || numberOfStudentsInSection > Limitations::maximumNumberOfStudentsPerSection);
    
    return numberOfStudentsInSection;
}

void allocateSectionSize(std::vector<Student>& students, int numberOfStudentsInSection)
{
    students.resize(numberOfStudentsInSection);
}

bool checkIfValidName(const std::string& name)
{
    if (isalpha(name[0]) == 0)
    {
        return false;
    }
    else
    {
        if (isupper(name[0]) == 0)
        {
            return false;
        }
    }
    
    for (int i = 1; i < name.length(); ++i)
    {
        if (isalpha(name[i]) == 0)
        {
            return false;
        }
        
        int asciiConversion = static_cast<int>(name[i]);
        if (asciiConversion == 32)
        {
            char charAfterSpace = name[i + 1];
            if (isalpha(charAfterSpace) == 0)
            {
                return false;
            }
            else if (isupper(charAfterSpace) == 0)
            {
                return false;
            }
        }
    }
    
    return true;
}

void fillSectionWithStudents(std::vector<Student>& students, SectionIdentifier identifier)
{
    std::cout << "SECTION " << identifier << '\n';
    for (int i = 0; i < students.size(); ++i)
    {
        bool validName{};
        do
        {
            std::cout << "Name #" << i + 1 << ": ";
            std::getline(std::cin >> std::ws, students[i].name);
            validName = checkIfValidName(students[i].name);
        } while (std::cin.fail() || validName == false);
        
        std::cout << '\n';
    }
}

bool compareAlphabetically(const Student& student, const Student& anotherStudent)
{
    return student.name < anotherStudent.name;
}

void sortAlphabetically(std::vector<Student>& students)
{
    std::sort(students.begin(), students.end(), compareAlphabetically); // FIX
}

void assignClassNumbers(std::vector<Student>& students)
{
    for (int i = 1; i <= students.size(); ++i)
    {
        students[i].classNumber = i;
    }
}

void printBatch(std::vector<Section>& sections)
{
    for (int i = 0; i < sections.size(); ++i)
    {
        std::cout << "SECTION " << sections[i].identifier << '\n';
        for (int j = 0; j < sections[i].students.size(); ++j)
        {
            std::cout << "CN " << sections[i].students[j].classNumber << '\t' << sections[i].students[j].name << '\n';
        }
        std::cout << '\n';
    }
}
