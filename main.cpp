#include "class.h"

int main() {
  Piece move;

  int menu_opt = 0;
  srand(time(NULL)); //The games randomizor


//_________________________________
  //intro
  cout << "   Welcome to" << endl;
  do{
  cout << " ---------------" << endl;
  cout << "    Move Out! \n "
          "  --------------- \n " << endl;

  //Main menu screen
  cout << " (1) Play" << endl;
  cout << " (2) Tutorial" << endl;
  cout << " (3) Upgrades" << endl;
  cout << " (4) Exit " << endl;
  cout << "               EXP: " << move.display_EXP() << endl;
  cin >> menu_opt;
  
  //Options
    if(menu_opt == 1){
      int results = move.Move_Out();
      
      cout << "You got a score of: " << results << " Points" << endl;
      move.reset_board();

    }

    if(menu_opt == 2){
      move.tutorial();
      move.reset_board();
    }

    if(menu_opt == 3){
      move.upgrades();
      move.reset_board();
    }


    //move.display(); //This should display a clean slate of the board
  }while(menu_opt != 4);
  cout << "good-bye" << endl;

}
