#ifndef HEADER_H
#define HEADER_H

enum class SectionIdentifier
{
    A,
    B,
    C,
    D,
    E,
    F,
    G,
    H,
    I,
    J,
    K,
    L,
    M,
    N,
    O,
    P,
    Q,
    R,
    S,
    T,
    U,
    V,
    W,
    X,
    Y,
    Z
};

std::ostream& operator<<(std::ostream& out, SectionIdentifier letter)
{
    using enum SectionIdentifier;
    
    switch (letter)
    {
        case A: return out << 'A';
        case B: return out << 'B';
        case C: return out << 'C';
        case D: return out << 'D';
        case E: return out << 'E';
        case F: return out << 'F';
        case G: return out << 'G';
        case H: return out << 'H';
        case I: return out << 'I';
        case J: return out << 'J';
        case K: return out << 'K';
        case L: return out << 'L';
        case M: return out << 'M';
        case N: return out << 'N';
        case O: return out << 'O';
        case P: return out << 'P';
        case Q: return out << 'Q';
        case R: return out << 'R';
        case S: return out << 'S';
        case T: return out << 'T';
        case U: return out << 'U';
        case V: return out << 'V';
        case W: return out << 'W';
        case X: return out << 'X';
        case Y: return out << 'Y';
        case Z: return out << 'Z';
    }
}

struct Student
{
    std::string name{};
    int classNumber{};
};

struct Section
{
    SectionIdentifier identifier{};
    int numberOfStudents{};
    std::vector<Student> students{};
};

namespace Limitations
{
    inline constexpr int maximumNumberOfSections{26};
    inline constexpr int minimumNumberOfStudentsPerSection{10};
    inline constexpr int maximumNumberOfStudentsPerSection{50};
}

// functions

void troubleshoot();
int getNumberOfSections();
void assignIdentifiers(std::vector<Section>& sections);
int getNumberOfStudentsInSection(SectionIdentifier identifier);
void allocateSectionSize(std::vector<Student>& students, int numberOfStudentsInSection);
bool checkIfValidName(const std::string& name);
void fillSectionWithStudents(std::vector<Student>& students, SectionIdentifier identifier);
bool compareAlphabetically(const Student& student, const Student& anotherStudent);
void sortAlphabetically(std::vector<Student>& students); 
void assignClassNumbers(std::vector<Student>& students);
void printBatch(std::vector<Section>& sections);

#endif
