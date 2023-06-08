#include <iostream>
#include <vector>

#include "EnumDefs.h"
#include "Header.h"
#include "StructDefs.h"

int main()
{
    int numberOfSections{getNumberOfSections()};
    
    std::vector<Section> batch(numberOfSections);
    
    // generate a section for each iteration
    for (int i = 0; i < numberOfSections; ++i)
    {
        batch[i].identifier = assignSectionIdentifier(i);
        
        std::cout << '\n';
        std::cout << "SECTION " << batch[i].identifier << '\n';
        
        batch[i].classSize = getClassSize();
        batch[i].students.resize(batch[i].classSize);
        
        std::cout << '\n';
        getFullNames(batch[i].students);
        sortAlphabetically(batch[i].students);
        assignClassNumbers(batch[i].students);
    }
    
    std::cout << '\n';
    printBatch(batch);
    
    
    return 0;
}

