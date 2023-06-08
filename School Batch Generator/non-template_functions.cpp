#include <algorithm>
#include <cctype>
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "EnumDefs.h"
#include "Header.h"
#include "StructDefs.h"

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
    } while (std::cin.fail() || numberOfSections < Limitations::minimumSections || numberOfSections > Limitations::maximumSections);
    
    return numberOfSections;
}

SectionIdentifier assignSectionIdentifier(int index)
{
    return static_cast<SectionIdentifier>(index);
}

int getClassSize()
{
    int classSize{};
    do
    {
        if (std::cin.fail())
        {
            troubleshoot();
        }
        std::cout << "Class size: ";
        std::cin >> classSize;
    } while (std::cin.fail() || classSize < Limitations::minimumStudentsPerClass || classSize > Limitations::maximumStudentsPerClass);
    
    return classSize;
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
        int asciiConversion = static_cast<int>(name[i]);
        
        if (isalpha(name[i]) == 0 && asciiConversion != 32)
        {
            return false;
        }
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
        if (isalpha(name[i]) != 0 && isalpha(name[i - 1]) != 0 && isalpha(name[i + 1]) != 0)
        {
            if (islower(name[i]) == 0)
            {
                return false;
            }
        }
    }
    
    return true;
}

void fullyCapitalize(std::string& name)
{
    for (int i = 0; i < name.length(); ++i)
    {
        name[i] = toupper(name[i]);
    }
}

std::string getFirstName()
{
    bool validName{};
    std::string firstName{};
    do
    {
        if (std::cin.fail())
        {
            troubleshoot();
        }
        std::cout << "First name: ";
        std::getline(std::cin >> std::ws, firstName);
        validName = checkIfValidName(firstName);
    } while (std::cin.fail() || validName == false);
    
    return firstName;
}

std::string getLastName()
{
    bool validName{};
    std::string lastName{};
    do
    {
        if (std::cin.fail())
        {
            troubleshoot();
        }
        std::cout << "Last name: ";
        std::getline(std::cin >> std::ws, lastName);
        validName = checkIfValidName(lastName);
    } while (std::cin.fail() || validName == false);
    
    fullyCapitalize(lastName);
    
    return lastName;
}

bool compareLastNames(const Student& student, const Student& anotherStudent)
{
    return student.lastName < anotherStudent.lastName;
}

void getFullNames(std::vector<Student>& section)
{
    for (int i = 0; i < section.size(); ++i)
    {
        std::cout << "NAME #" << i + 1 << '\n';
        section[i].firstName = getFirstName();
        section[i].lastName = getLastName();
    }
}

void sortAlphabetically(std::vector<Student>& section)
{
    std::sort(section.begin(), section.end(), compareLastNames);
}

void assignClassNumbers(std::vector<Student>& section)
{
    for (int i = 1; i <= section.size(); ++i)
    {
        section[i - 1].classNumber = i;
    }
}

void printBatch(std::vector<Section>& batch)
{
    for (int i = 0; i < batch.size(); ++i)
    {
        std::cout << "SECTION " << batch[i].identifier << '\n';
        for (int j = 0; j < batch[i].classSize; ++j)
        {
            std::cout << "CN " << batch[i].students[j].classNumber << '\t' << batch[i].students[j].firstName << ' ' << batch[i].students[j].lastName << '\n';
        }
        std::cout << '\n';
    }
}
