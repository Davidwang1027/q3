#include "grid.h"
Grid::~Grid(){
    delete td;
    delete ob;
}

void Grid::setObserver(Observer<Info, State>* ob){
    this->ob = ob;
}

void Grid::toggle(size_t r, size_t c){
    theGrid[r][c].toggle();
}

bool Grid::setPiece(size_t r, size_t c, Colour colour){
    size_t size = theGrid.size();
    if (r <= size && c <= size && theGrid[r][c].getInfo().colour == Colour::NoColour){

        // attach the neighbours
        // check if r-1 is valid and attach
        if (r - 1 >= 0){
            theGrid[r][c].attach(&theGrid[r - 1][c]);
            if (c - 1 >= 0){
                theGrid[r][c].attach(&theGrid[r - 1][c - 1]);
            }
            if (c + 1 < size){
                theGrid[r][c].attach(&theGrid[r - 1][c + 1]);
            }
        }
        // check if r+1 is valid and attach
        if (r + 1 < size){
            theGrid[r][c].attach(&theGrid[r + 1][c]);
            if (c - 1 >= 0){
                theGrid[r][c].attach(&theGrid[r + 1][c - 1]);
            }
            if (c + 1 < size){
                theGrid[r][c].attach(&theGrid[r + 1][c + 1]);
            }
        }
        // check if c-1 is valid and attach
        if (c - 1 >= 0){
            theGrid[r][c].attach(&theGrid[r][c - 1]);
        }
        // check if c+1 is valid and attach
        if (c + 1 < size){
            theGrid[r][c].attach(&theGrid[r][c + 1]);
        }

        // attach the display 
        theGrid[r][c].attach(td);

        // set the piece
        theGrid[r][c].setPiece(colour);

        return true;
    } else{
        return false;
    }
}

bool Grid::isFull() const{
    size_t size = theGrid.size();
    for (size_t i = 0; i < size; ++i){
        for (size_t j = 0; j < size; ++j){
            if (theGrid[i][j].getInfo().colour == Colour::NoColour){
                return false;
            }
        }
    }
    return true;
}

Colour Grid::whoWon() const{
    int black = 0;
    int white = 0;
    size_t size = theGrid.size();
    for (size_t i = 0; i < size; ++i){
        for (size_t j = 0; j < size; ++j){
            if (theGrid[i][j].getInfo().colour == Colour::Black){
                ++black;
            } else if (theGrid[i][j].getInfo().colour == Colour::White){
                ++white;
            }
        }
    }
    if (black > white){
        return Colour::Black;
    } else if (white > black){
        return Colour::White;
    } else{
        return Colour::NoColour;
    }
}

void Grid::init(size_t n){
    // clear the old Grid
    for (size_t i = 0; i < theGrid.size(); i++){
        theGrid[i].clear();
    }
    theGrid.clear();
    if (td != nullptr){
        delete td;
    }


    // create a new Grid
    td = new TextDisplay(n);
    // ob = new Observer<Info, State>;
    for (size_t i = 0; i < n; i++){
        std::vector<Cell> tmp;
        for (size_t j = 0; j < n; j++){
            tmp.emplace_back(Cell(i, j));
        }
        theGrid.emplace_back(tmp);
    }
}

std::ostream& operator<<(std::ostream& out, const Grid& g){
    out << *(g.td);
    return out;
}
