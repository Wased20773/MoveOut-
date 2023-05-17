#include "class.h"

Piece::Piece(){}

Piece::~Piece(){}

int Piece::Move_Out(){
  display();
  int exit_key = 0; 
  char column;
  char row;

  //Starting Phase
  cout << "Please choose your starting point by column and then row." << endl;
  cin >> column;
  cin >> row;
  column = toupper(column);
  row = toupper(row);

  calculate_position(column, row);

  for(int i = 0; i < 6; ++i){
    enemy_piece(rand()%16);
  }

  for(int i = 0; i < 15; ++i){
    loot_piece(rand()%16);
  }

  shop_piece(rand()%16);

  exit_piece();


  //The game starts here
  cout << "Lets Move Out!" << endl;
  cout << "Health: " << health << endl;
  cout << "Money: " << money << endl;
  do{
    if(reached_exit == true){
      cout << "currently you can exit, enter '1' to exit" << endl;
      cout << "Enter any other integer to continue your journey" << endl;
      cin >> exit_key;

    }
    if(exit_key == 1){
      cout << "You win" << endl;
    }
    else{
      cout << "______________________________" << endl;
      cout << "where will you go" << endl;
      cin >> column;
      cin >> row;
      column = toupper(column);
      row = toupper(row);

      calculate_position(column, row);
    }

    //Player statues
    cout << "Health: " << health << endl;
    cout << "Money: " << money << endl;
    
  }while(exit_key != 1 && health > 0); 

  cout << "You collected " << money << " coins" << endl;
  cout << "You killed " << enemys_killed << " enemys" << endl;
  cout << "You found " << empty_rooms_entered << " empty rooms" << endl;
  if(health > 0) {
    cout << "You decided to leave in " << move_counter << " moves" << endl;
  }
  else{
    cout << "You died in " << move_counter << " moves" << endl;
  }
  score = (health*((money*5) + (enemys_killed*20) + (empty_rooms_entered*3)));


  //collected EXP from game
  int collected_EXP = (enemys_killed*2) + (score/100);

  cout << "You collected " << collected_EXP << "EXP" << endl;

  EXP = EXP + (enemys_killed*2) + (score/100);
  return score;
}

int Piece::calculate_position(char column, char row){
  //check wheither or not its the first time moving
  if(first_move_done == true) {
    remove_from_origin(current_position);
  }
  else{
    first_move_done = true;
  }

  int column_value = 0;
  //Checking column value
  if(column == 'A') {
    column_value = 3;
  }
  if(column == 'B') {
    column_value = 2;
  }
  if(column == 'C') {
    column_value = 1;
  }
  if(column == 'D') {
    column_value = 0;
  }

  int row_value = 0;
  //Checking row value
  if(row == 'A') {
    row_value = 3;
  }
  if(row == 'B') {
    row_value = 7;
  }
  if(row == 'C') {
    row_value = 11;
  }
  if(row == 'D') {
    row_value = 15;
  }

  //Final calulation for position on the board
  int position = row_value - column_value;
  ++move_counter;

  //Player can now only move up, left, right, or down only
  //Lets check if they are actually inputting the right coordinates
  //before we send them through.
  if(move_counter > 1){
    int counter = 0;
    //Check if they can go up
    if(position == current_position - 4) {
      return move_your_piece(position);
    }
    ++counter;
    
    //Check if they can go left
    if(position == current_position - 1) {
      return move_your_piece(position);
    }
    ++counter;
    
    //Check if they can go right
    if(position == current_position + 1) {
      return move_your_piece(position);
    }
    ++counter;

    //Check if they can go down
    if(position == current_position + 4) {
      return move_your_piece(position);
    }
    ++counter;
    
    if(counter == 4){
      cout << "invalid move" << endl;
      return 0;
    }
  }


  return move_your_piece(position);
}

int Piece::move_your_piece(int position){
  //Case only possible at the start of the game
  if(move_counter == 1){
    board[position] = 'n';
    current_position = position;
    
    return display();
  }

  //Check if player landed on nothing
  if(cheat_board[position] == 'o'){
    cout << "you find an empty room" << endl;
    ++empty_rooms_entered;
  }
  //check if player landed on an enemy
  if(cheat_board[position] == 'x'){
    cout << "You've encounter an enemy" << endl;

    board[position] = 'x';
    board[current_position] = 'n';
    display();
    board[current_position] = 'o';

    int recieved_damage = rand()%5 + 1;
    cout << "They dealt " << recieved_damage << " damage" << endl;
    health = health - recieved_damage;
    

    if(health > 0){
      cout << "You killed them" << endl;
      ++enemys_killed;
      cheat_board[position] = 'X';

    }
    //You die so...
    else{
      display();
      cout << "Oopsie you died, goodluck next time!" << endl;
      return 0;
    }
  }

  //check if player landed on a loot spot
  if(cheat_board[position] == '$'){
    int collected = rand()%10 + 1;

    cout << "You found " << collected << "$" << endl;

    board[position] = '$';
    board[current_position] = 'n';
    display();
    board[current_position] = 'o';

    money = money + collected;
    cheat_board[position] = 'X';
  }
  //Check if player landed on a shop
  char response;
  if(cheat_board[position] == '@'){
    cout << "You found a store" << endl;
    cout << "would you like to enter and buy? y or n: " << endl;
    cin >> response;
    if(response == 'y'){
      cout << "You enter the shop and see 5 iteam on display" << endl;
      
      //Use randomizer to get random number which will be corrolated to a number
      obtain_rand_item(rand()%100);

      return 0;
    }
   
    
  }

  //check if the player found the exit
  if(cheat_board[position] == 'e'){
    cout << "You are at the exit" << endl;
    board[position] = 'e';
    current_position = position;
    reached_exit = true;
    return display(); //We dont want to overwrite the exit with n so lets just display the board

  }


  board[position] = 'n';

  if(reached_exit == true){
    board[current_position] = 'e';
    reached_exit = false; //switch back to false since we can move to the same position
  }

  current_position = position;
    
  return display();
}


int Piece::remove_from_origin(int current_position){
  board[current_position] = 'o';
  return 0;
}

int Piece::enemy_piece(int enemy_position){
  if(board[enemy_position] == 'n'){
    return 1;
  }
  cheat_board[enemy_position] = 'x'; 
  return 0;
}

int Piece::loot_piece(int loot_position){
  if(cheat_board[loot_position] == 'o' && board[loot_position] != 'n') {
    cheat_board[loot_position] = '$';
    return 0;
  }

  return 1; //We dont want to replace enemys for loot so lets move on and leave
}

int Piece::shop_piece(int shop_position){
  cheat_board[shop_position] = '@';

  return 0;
}

int Piece::obtain_rand_item(int rand_item){
  

  return 0;
}

int Piece::exit_piece(){
  while(exit_determined == false){
    int exit_position = rand()%16;
    if(cheat_board[exit_position] == 'o' && board[exit_position] != 'n'){ //an empty slot
      cheat_board[exit_position] = 'e'; 
      exit_determined = true;
    }

  }

  return 0;
}

int Piece::display(){
  int count = 0;
  cout << "    A    B    C    D  \n";
  cout << row[0] << " ";
  for(int i = 0; i < 16; ++i) {
    if(i == 4 || i == 8 || i == 12) {
      cout << "\n";
      ++count;
      cout << row[count] << " ";
    }
    cout << "[ " << board[i] << " ]";
  }
  cout << "\n\n";
 
  return 0;
}

int Piece::tutorial(){
    display();
    char column;
    char row;
    cout << "Please choose your starting place using\n"
            "the letters on the outskirts\n" << endl;
    //Column
    cout << "First lets start with the column, Please\n"
            "choose the letters A through D\n" << endl;
    cin >> column;
    column = toupper(column);
    cout << column << endl;
    //Row
    cout << "Now lets get the row, Please choose\n"
            "the letters A through D\n" << endl;
    cin >> row;
    row = toupper(row);
    cout << row << endl;
    cout << "Great your position is getting calculated\n" << endl;

    //Calculation for starting position
    calculate_position(column, row);

    cout << "Great, This is where you will stand for now." << endl;
    cout << "Now move to a different location." << endl;
    cout << "You can only move up, left, right, or down." << endl;

    //Column
    cout << "Which column do you choose?" << endl;
    cin >> column;
    column = toupper(column);

    //Row
    cout << "Which row do you choose?" << endl;
    cin >> row;
    row = toupper(row);
    cout << "lets see if its valid" << endl;

    //Calculating new position
    calculate_position(column, row);
    //Let the player get a feel for the controls and have them exit
    //the tutorial when they feel most comftrable by entering the letter "x"
    cout << "thats about it. to leave the tutorial, enter x" << endl;

    do {
    cout << "Which column do you choose?" << endl;
    cin >> column;
    column = toupper(column);
    if(column == 'X'){
      return reset_board();
    }

    cout << "Which row do you choose?" << endl;
    cin >> row;
    row = toupper(row);
    if(row == 'X'){
      return reset_board();
    }
    //Calculating new position
    calculate_position(column, row);

    }while(column != 'X' || row != 'X');

    
    
    return reset_board();
}

int Piece::display_EXP(){

  return EXP;
}

int Piece::upgrades(){
  int shop_opt = 0;

  do{
    cout << " (1) Health upgrade | " << health_upgrade << "EXP\n" << endl;
    cout << " (2) Exit shop" << endl;
    cout << "                 EXP: " << EXP << endl;
    cin >> shop_opt;

    if(shop_opt == 1 && EXP >= health_upgrade){
      health_added = health_added + 2;
      EXP = EXP - health_upgrade;
      health_upgrade = health_upgrade * 1.5;
    }
    else{
      cout << "You dont have enough EXP" << endl;
      cout << "You currently have " << EXP << " and require " << health_upgrade - EXP << "EXP" << endl;
    }
  }while(shop_opt != 2);
  return 0;
}

int Piece::reset_board(){
  strcpy(cheat_board, back_up_save_board);
  strcpy(board, back_up_save_board);

  move_counter = 0;
  current_position = 0;
  first_move_done = false;
  exit_determined = false;
  reached_exit = false;

  health = 10 + health_added;
  money = 0;
  score = 0;
  return 1;
}
