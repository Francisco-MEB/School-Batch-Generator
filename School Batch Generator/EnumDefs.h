#ifndef ENUMDEFS_H
#define ENUMDEFS_H

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

inline std::ostream& operator<<(std::ostream& out, SectionIdentifier letter)
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
        default: return out << '?';
    }
}

#endif

