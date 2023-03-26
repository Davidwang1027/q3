#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char* argv[]){
  cin.exceptions(ios::eofbit | ios::failbit);
  string cmd;
  Grid g;
  // Add code here
  bool bTurn = true;
  Colour color;

  try{
    while (true){
      cin >> cmd;
      if (cin.eof()) break;
      if (cmd == "new"){
        int n;
        cin >> n;
        if (n >= 4 && (n / 2) * 2 == n){
          g.init(n);
          size_t mid = n / 2;
          // add 4 initial pieces
          g.setPiece(mid - 1, mid - 1, Colour::Black);
          g.setPiece(mid, mid, Colour::Black);
          g.setPiece(mid - 1, mid, Colour::White);
          g.setPiece(mid, mid - 1, Colour::White);
          cout << g;
        } else{
          continue;
        }
      } else if (cmd == "play"){
        int r = 0, c = 0;
        cin >> r >> c;
        // Add code here
        if (bTurn){
          color = Colour::Black;
        } else{
          color = Colour::White;
        }
        if (r < 0 || c < 0){
          continue;
        } else if (g.setPiece(r, c, color)){
          cout << g;
          bTurn = !bTurn;
        } else{
          continue;
        }
      }
      // check if the game is over
      if (g.isFull()){
        color = g.whoWon();
        if (color == Colour::Black){
          cout << "Black wins!" << endl;
        } else if (color == Colour::White){
          cout << "White wins!" << endl;
        } else{
          cout << "Tie!" << endl;
        }
        break;
      }
    }
  }
  catch (ios::failure&){}  // Any I/O failure quits
}
