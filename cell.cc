#include "cell.h"
Cell::Cell(size_t r, size_t c) : r{ r }, c{ c }{}
void Cell::setPiece(Colour colour){
    this->colour = colour;
    State state = { StateType::NewPiece, colour, Direction::SW };
    this->setState(state);
    this->notifyObservers();
}
void Cell::toggle(){
    if (colour == Colour::Black){
        colour = Colour::White;
    } else if (colour == Colour::White){
        colour = Colour::Black;
    } else{
        colour = Colour::NoColour;
    }
}
void Cell::notify(Subject<Info, State>& whoFrom){
    // unused cell
    if (colour == Colour::NoColour){
        return;
    }
    Info fromInfo = whoFrom.getInfo();
    State fromState = whoFrom.getState();
    Colour fromColor = fromState.colour;
    const size_t fromRow = fromInfo.row;
    const size_t fromCol = fromInfo.col;
    // Determine the direction
    Direction dir;
    if (fromRow == r && fromCol == c){
        // means it's the same cell
        return;
    } else if (fromRow == r && fromCol < c){
        dir = Direction::W;
    } else if (fromRow == r && fromCol > c){
        dir = Direction::E;
    } else if (fromRow < r && fromCol == c){
        dir = Direction::N;
    } else if (fromRow > r && fromCol == c){
        dir = Direction::S;
    } else if (fromRow < r && fromCol < c){
        dir = Direction::NW;
    } else if (fromRow < r && fromCol > c){
        dir = Direction::NE;
    } else if (fromRow > r && fromCol < c){
        dir = Direction::SW;
    } else if (fromRow > r && fromCol > c){
        dir = Direction::SE;
    }
    if (dir != fromState.direction && fromState.type != StateType::NewPiece){
        return;
    }
    // type of fromState is newPiece or relay
    if (fromState.type == StateType::NewPiece || fromState.type == StateType::Relay){
        // If color is not the same, relay the message
        if (colour != fromColor){
            State state = { StateType::Relay, fromColor, dir };
            this->setState(state);
            this->notifyObservers();
            return;
        }
        // If color is the same, reply back
        else if (colour == fromColor){
            // reverse the direction
            Direction reverseDir;
            if (dir == Direction::NW){
                reverseDir = Direction::SE;
            } else if (dir == Direction::N){
                reverseDir = Direction::S;
            } else if (dir == Direction::NE){
                reverseDir = Direction::SW;
            } else if (dir == Direction::W){
                reverseDir = Direction::E;
            } else if (dir == Direction::E){
                reverseDir = Direction::W;
            } else if (dir == Direction::SW){
                reverseDir = Direction::NE;
            } else if (dir == Direction::S){
                reverseDir = Direction::N;
            } else if (dir == Direction::SE){
                reverseDir = Direction::NW;
            }
            State state = { StateType::Reply, fromColor, reverseDir };
            this->setState(state);
            this->notifyObservers();
        }
    }
    // type of fromState is reply
    else{
        if (colour != fromColor){
            this->toggle();
            State state = { StateType::Reply, fromColor, dir };
            this->setState(state);
            this->notifyObservers();
        } else{
            return;
        }
    }
}

Info Cell::getInfo() const{
    return Info{ r, c, colour };
}
