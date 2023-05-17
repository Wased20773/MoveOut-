#include <iostream>
#include <cctype>
#include <cstring>
#include <ctime>
using namespace std;

//class
class Piece {
  public:
    ~Piece();
    Piece();
    int Move_Out();
    int calculate_position(char column, char row);
    int move_your_piece(int position);
    int remove_from_origin(int current_position);
    int enemy_piece(int enemy_position); //uses a random number generator to 
                                         //determine where to place the enemys
    int loot_piece(int loot_position);
    int shop_piece(int shop_position);
    int exit_piece();
    int tutorial();
    int reset_board();
    int display();

    //Items for the shop function
    int obtain_rand_item(int rand_item);

    int upgrades();
    int display_EXP();

  private:
    bool first_move_done = false;
    bool exit_determined = false;
    bool reached_exit = false;
    int current_position = 0;
    char board[17] = "oooooooooooooooo"; //16
    char cheat_board[17] = "oooooooooooooooo"; //16
    char back_up_save_board[17] = "oooooooooooooooo"; //16
    char row[5] = "ABCD";


    //Players variables
    int move_counter = 0;
    int empty_rooms_entered = 0;
    int enemys_killed = 0;
    int money = 0;
    int health = 10;
    int attack = 4;

    int score = 0; //score increases with each coin and how much health you are left with, including the kills.
                   //Also how few moves you managed to find the exit increases your score.
                   //Finally, entering empty rooms also increases score but its the least amount of points.
    int EXP = 0;
    int health_upgrade = 10;
    int health_added = 0; 

};
