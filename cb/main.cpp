#include <iostream>
#include <vector>

#include "Header.h"

int main()
{
    // get number of sections in batch
    int numberOfSections{getNumberOfSections()};
    
    // create a vector with each element representing a section
    std::vector<Section> sections(numberOfSections);
    
    // assign identifiers to sections
    assignIdentifiers(sections);
    
    // get number of students in certain section
    
    for (int i = 0; i < numberOfSections; ++i)
    {
        SectionIdentifier currentSection{sections[i].identifier};
        int numberOfStudentsInSection{getNumberOfStudentsInSection(currentSection)};
        allocateSectionSize(sections[i].students, numberOfStudentsInSection);
        fillSectionWithStudents(sections[i].students, sections[i].identifier);
        sortAlphabetically(sections[i].students);
        assignClassNumbers(sections[i].students);
    }
    
    printBatch(sections);
    
    
    return 0;
}
