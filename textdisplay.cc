#include "textdisplay.h"
TextDisplay::TextDisplay(int n) : gridSize{ n }{
    // initialize td with n*n '-'
    for (int i = 0; i < n; ++i){
        std::vector<char> tmp;
        for (int j = 0; j < n; ++j){
            tmp.emplace_back('-');
        }
        theDisplay.emplace_back(tmp);
    }
}
void TextDisplay::notify(Subject<Info, State>& whoNotified){
    Info cellInfo = whoNotified.getInfo();
    const size_t r = cellInfo.row;
    const size_t c = cellInfo.col;
    if (cellInfo.colour == Colour::Black){
        theDisplay[r][c] = 'B';
    } else if (cellInfo.colour == Colour::White){
        theDisplay[r][c] = 'W';
    }
}

std::ostream& operator<<(std::ostream& out, const TextDisplay& td){
    size_t size = td.gridSize;
    for (size_t i = 0; i < size; ++i){
        for (size_t j = 0; j < size; ++j){
            out << td.theDisplay[i][j];
        }
        out << std::endl;
    }
    return out;
}
