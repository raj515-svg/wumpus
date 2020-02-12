/* prog5Wumpus.cpp
 
 Description: Navigate a maze to kill the Wumpus.
 Implementation of a 1972 game by Gregory Yob.
 
 Results of a program run are shown below:
 
 //***Park: You should put your personal information in this part of the header. 

      
 */
#include <iostream>
#include <iomanip>   // for setw()
#include <cctype>    // for toupper()
#include <cstdlib>   // for rand() and srand()
#include <ctime>     // to seed random number generator with time(0)
using namespace std;

// global constants
#define MAX_LINE_LENGTH 81
#define NUMBER_OF_ROOMS 20
#define MAX_NUM_CONNECTED 3

//--------------------------------------------------------------------------------
void displayCave()
{
        cout<< "       ______18______             \n"
            << "      /      |       \\           \n"
            << "     /      _9__      \\          \n"
            << "    /      /    \\      \\        \n"
            << "   /      /      \\      \\       \n"
            << "  17     8        10     19       \n"
            << "  | \\   / \\      /  \\   / |    \n"
            << "  |  \\ /   \\    /    \\ /  |    \n"
            << "  |   7     1---2     11  |       \n"
            << "  |   |    /     \\    |   |      \n"
            << "  |   6----5     3---12   |       \n"
            << "  |   |     \\   /     |   |      \n"
            << "  |   \\       4      /    |      \n"
            << "  |    \\      |     /     |      \n"
            << "  \\     15---14---13     /       \n"
            << "   \\   /            \\   /       \n"
            << "    \\ /              \\ /        \n"
            << "    16---------------20           \n"
            << endl;
}//end displayCave()


//--------------------------------------------------------------------------------
void displayInstructions()
{
    cout<< "Hunt the Wumpus:                                             \n"
        << "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
        << "room has 3 tunnels leading to other rooms.                   \n"
        << "                                                             \n"
        << "Hazards:                                                     \n"
        << "1. Two rooms have bottomless pits in them.  If you go there you fall and die.  \n"
        << "2. Two other rooms have super-bats.  If you go there, the bats grab you and    \n"
        << "   fly you to some random room, which could be troublesome.  Then those bats go\n"
        << "   to a new room different from where they came from and from the other bats.  \n"
        << "3. The Wumpus is not bothered by the pits or bats, as he has sucker feet and   \n"
        << "   is too heavy for bats to lift.  Usually he is asleep.  Two things wake      \n"
        << "   him up: Anytime you shoot an arrow, or you entering his room.  When he      \n"
        << "   wakes he moves if he is in an odd-numbered room, but stays still otherwise. \n"
        << "   After that, if he is in your room, he eats you and you die!                 \n"
        << "                                                                               \n"
        << "Moves:                                                                         \n"
        << "On each move you can do the following, where input can be upper or lower-case: \n"
        << "1. Move into an adjacent room.  To move enter 'M' followed by a space and      \n"
        << "   then a room number.                                                         \n"
        << "2. Shoot your guided arrow through a list of up to three adjacent rooms, which \n"
        << "   you specify.  Your arrow ends up in the final room.                         \n"
        << "   To shoot enter 'S' followed by the number of rooms (1..3), and then the     \n"
        << "   list of the desired number (up to 3) of adjacent room numbers, separated    \n"
        << "   by spaces. If an arrow can't go a direction because there is no connecting  \n"
        << "   tunnel, it ricochets and moves to the lowest-numbered adjacent room and     \n"
        << "   continues doing this until it has traveled the designated number of rooms.  \n"
        << "   If the arrow hits the Wumpus, you win! If the arrow hits you, you lose. You \n"
        << "   automatically pick up the arrow if you go through a room with the arrow in  \n"
        << "   it.                                                                         \n"
        << "3. Enter 'R' to reset the person and hazard locations, useful for testing.     \n"
        << "4. Enter 'C' to cheat and display current board positions.                     \n"
        << "5. Enter 'D' to display this set of instructions.                              \n"
        << "6. Enter 'P' to print the maze room layout.                                    \n"
        << "7. Enter 'X' to exit the game.                                                 \n"
        << "                                                                               \n"
        << "Good luck!                                                                     \n"
        << " \n"
        << endl;
}//end displayInstructions()

// this function will randomize the different variables in the game
void gettingRandomNum(int storingVariables[])
{
    int randomNumber = 0;   // initializing the variable
    srand(1);   // Use this version in what you turn in  
    for(int i=0; i<7;i++)
    {
        if(i==0){
          storingVariables[i] = (rand()%20)+1;
        }
        else if(i==1){
          storingVariables[i] = (rand()%20)+1;
        }
        else if(i==2){
         storingVariables[i] = (rand()%20)+1;
        }
        else if(i==3){
          storingVariables[i] = (rand()%20)+1;
        }
        else if(i==4){
          storingVariables[i] = (rand()%20)+1;
        }
        else if(i==5){
          storingVariables[i] = (rand()%20)-2;
        }
        else{
          storingVariables[i] = -1;
        }
    }// end of for loop
}// end gettingRandomNum()

//this function is a helper of the checkhazard function to verify the hazard of pit first than the hazard of bats
void hazardCheckHelperFunction(int maze[][MAX_NUM_CONNECTED], int storingVariables[], int validMoves[],int currentPlayerPosition)
{
    int pits1 =  storingVariables[2];  // this particular index of array has the position of pits
    int pits2 = storingVariables[3];   // this particular index of array has the position of another pits
  
    // loop is used to check the adjacent room in the array
    for (int j =0;j<3;j++)
    {
      validMoves[j] = maze[currentPlayerPosition][j];   //getting the valid rooms by checking it into the maze array according to the player position
      if(pits1 == validMoves[j] || pits2 == validMoves[j])  // checking if the pit is in one of the valid rooms according to player position
      {
        cout<<"You feel a draft.";
      }
      if(currentPlayerPosition == pits1 || currentPlayerPosition == pits2) // checking if the player entered the room which has pit in it
      {
        cout<<"Aaaaaaaaahhhhhh.... You fall into a pit and die.";
        cout<<"Exiting Program ..."<<endl;       
        exit(0);
      }
    }//end of foor loop
}// end hazardCheckHelperFunction()

//function checks the hazards present in the game
void hazardCheck(int maze[][MAX_NUM_CONNECTED], int storingVariables[], int validMoves[],int currentPlayerPosition)
{   
    int bats1 = storingVariables[0];         // this particular index of array has the position of the bats
    int bats2 = storingVariables[1];         // this particular index of array has the position of other bats
    int wumpus = storingVariables[4];        // this particular index of array has the position of the wumpus
  
    currentPlayerPosition = storingVariables [5]; // this particular index of array has the position of the player
    //enteringWumpusRoom(maze, storingVariables, validMoves, currentPlayerPosition); // called this function to avoid getting other conditions
    hazardCheckHelperFunction(maze, storingVariables, validMoves, currentPlayerPosition);
    for(int j =0 ;j<3;j++)
    {
      validMoves[j] = maze[currentPlayerPosition][j]; //getting the valid rooms by checking it into the maze array according to the player position
      if(wumpus == validMoves[j])  // checking if the wumpus is in one of the valid rooms according to player position
      {
        cout<<"You smell a stench."<<endl;
      }
      if(bats1 == validMoves[j] || bats2 == validMoves[j])  // checking if the bats are in one of the valid rooms according to player position
      {
         cout<<"You hear rustling of bat wings.";
       }
   }// end of for loop
}//end of hazardCheck()

// function will be used when player decides to shoot in  3 rooms
void shootingThreeRoomAndRichocet(int maze[][MAX_NUM_CONNECTED], int storingVariables[], int validMoves[],int currentPlayerPosition, 
                    int roomToShoot[] , int limitRoomToShoot)
{
    int wumpus = storingVariables[4];     // this particular index of array has the position of the wumpus
    int arrow = storingVariables[6];      // this particular index of array has the position of the arrow
    currentPlayerPosition = storingVariables[5];   // this particular index of array has the position of the player
    for (int j =0 ;j<3;j++)
    {
      if (roomToShoot[0] == validMoves[j] || roomToShoot[1] == validMoves[j] || roomToShoot[2] == validMoves[j]) //if the player is shooting within the adjacent rooms
      {
        if(roomToShoot[2] == wumpus) // if the person is shooting in the location where the wumpus is
        {
          cout<<"Wumpus has just been pierced by your deadly arrow!"<<endl;
          cout<<"Congratulations on your victory, you awesome hunter you."<<endl; 
          cout<<"Exiting Program ..."<<endl;
          exit(0); 
        } 
        else  // if the room entered to shoot is not adjacent
        {
         cout<<"Room "<<roomToShoot[2]<<"is not adjacent.  Arrow ricochets..."<<endl;
         cout<<"Your arrow ricochet killed the Wumpus, you lucky dog!"<<endl;
         cout<<"Accidental victory, but still you win!"<<endl;
         cout<<"Exiting Program ..."<<endl;
         exit(0);
        }
      } 
    }
}// end of shootingThreeRoomAndRichocet()

// function will be used when player decides to shoot in  2 rooms
void shootingTwoRoomAndRichocet(int maze[][MAX_NUM_CONNECTED], int storingVariables[], int validMoves[],int currentPlayerPosition, 
                    int roomToShoot[] , int limitRoomToShoot)
{
    int wumpus = storingVariables[4];     // this particular index of array has the position of the wumpus
    int arrow = storingVariables[6];      // this particular index of array has the position of the arrow
    currentPlayerPosition = storingVariables[5];   // this particular index of array has the position of the player
    for (int j =0 ;j<3;j++)
    {
        if (roomToShoot[0] == validMoves[j] || roomToShoot[1] == validMoves[j]) //if the player is shooting within the adjacent rooms
        {
          if(roomToShoot[1] == wumpus)  // if the person is shooting in the location where the wumpus is
          {
            cout<<"Wumpus has just been pierced by your deadly arrow!"<<endl;
            cout<<"Congratulations on your victory, you awesome hunter you."<<endl; 
            cout<<"Exiting Program ..."<<endl;
            exit(0); 
          }
         if (roomToShoot[1] == currentPlayerPosition) // if the person is shooting in the location where the he/she is
         {
           cout<<"You just shot yourself."<<endl;
           cout<<"Maybe Darwin was right.  You're dead."<<endl;
           cout<<"Exiting Program..."<<endl;
           exit(0);
         }
         else // if the room entered to shoot is not adjacent
         {
           cout<<"Room "<<roomToShoot[1]<<" is not adjacent.  Arrow ricochets..."<<endl;
           cout<<"You just shot yourself, and are dying."<<endl;
           cout<<"It didn't take long, you're dead."<<endl;
           cout<<"Exiting Program ..."<<endl;
           exit(0);
         }
       }
    }
}// end of shootingTwoRoomAndRichocet()

// function will be used when player decides to shoot in  1 room
void shootingOneRoomAndRichocet(int maze[][MAX_NUM_CONNECTED], int storingVariables[], int validMoves[],int currentPlayerPosition, 
                    int roomToShoot[] , int limitRoomToShoot)
{
    int wumpus = storingVariables[4];     // this particular index of array has the position of the wumpus
    int arrow = storingVariables[6];      // this particular index of array has the position of the arrow
    currentPlayerPosition = storingVariables[5];   // this particular index of array has the position of the player
    if (roomToShoot[0] == maze[currentPlayerPosition][0] || roomToShoot[0] == maze[currentPlayerPosition][1] 
             || roomToShoot[0] == maze[currentPlayerPosition][2]) //if the player is shooting within the adjacent rooms
    {
           if(roomToShoot[0] == wumpus) // if the person is shooting in the location where the wumpus is
           {
            cout<<"Wumpus has just been pierced by your deadly arrow!"<<endl;
            cout<<"Congratulations on your victory, you awesome hunter you."<<endl; 
            cout<<"Exiting Program ..."<<endl;
            exit(0); // to avoid infinite loop as wumpus is dead the game is over 
           }
           else // if person doesnot shoot 
           { 
             arrow = roomToShoot[0]; // changing the location of arrow to where the player shot
             storingVariables[6] = arrow; // storing the location of arrow in array 
             wumpus = maze[wumpus][0];  // sound of the arrow will cause wumpus to move in lowest index of its current position
             storingVariables[4] = wumpus; // storing the location of wumpus in array 
           }   
     }
     else // if the room entered to shoot is not adjacent 
     {
       cout<<"Room "<<roomToShoot[0]<<" is not adjacent.  Arrow ricochets..."<<endl; 
       storingVariables[6] = maze[currentPlayerPosition][0];  //storing the arrow in the lowest index of the player position 
       wumpus = maze[wumpus][0];  // sound of the arrow will cause wumpus to move in lowest index of its current position
       storingVariables[4] = wumpus; // storing the location of wumpus in array 
     } 
}// end of shootingOneRoomAndRichocet()

// function will be used to check the shooting conditions
void shootingArrow(int maze[][MAX_NUM_CONNECTED], int storingVariables[], int validMoves[],int currentPlayerPosition, 
                    int roomToShoot[] , int limitRoomToShoot)
{
    int wumpus = storingVariables[4];     // this particular index of array has the position of the wumpus
    int arrow = storingVariables[6];      // this particular index of array has the position of the arrow
    currentPlayerPosition = storingVariables[5];   // this particular index of array has the position of the player
    cin>>limitRoomToShoot;    //maximum limit to shoot in number of rooms
    for(int j = 0; j<limitRoomToShoot; j++)
      {
        cin>>roomToShoot[j];
      }
     if(limitRoomToShoot == 1) // condition for limit = 1
     {
       shootingOneRoomAndRichocet(maze, storingVariables, validMoves, currentPlayerPosition, roomToShoot, limitRoomToShoot); 
     }
  
     if(limitRoomToShoot == 2) // condition for limit = 2
     {
       shootingTwoRoomAndRichocet(maze, storingVariables, validMoves, currentPlayerPosition, roomToShoot, limitRoomToShoot);
     }
  
     if (limitRoomToShoot == 3) // condition for limit = 3
     {
       shootingThreeRoomAndRichocet(maze, storingVariables, validMoves, currentPlayerPosition, roomToShoot, limitRoomToShoot);
      }
}// end of shootingArrow()

//function will check different aspects if the player enters the room which has wumpus in it
void enteringWumpusRoom(int maze[][MAX_NUM_CONNECTED], int storingVariables[], int validMoves[],int currentPlayerPosition)
{
    int wumpus = storingVariables[4];    // this particular index of array has the position of the wumpus
  
    if((wumpus % 2) == 0 && currentPlayerPosition == wumpus) //checking if wumpus is in even numbered room and player enters that room, the player dies
    {
      cout<<"You briefly feel a slimy tentacled arm as your neck is snapped."<<endl;
      cout<<"It is over."<<endl;
      cout<<"Exiting Program ..."<<endl;
      exit(0);
    }
    if((wumpus % 2) == 1 && currentPlayerPosition == wumpus)  //checking if wumpus is in eodd numbered room and player enters that room
    {                                                         // wumpus will move to nearest valid smallest room
        storingVariables[4] = validMoves[0];   // to change the location of wumpus to the nearest smallest index room 
        cout<<"You hear a slithering sound, as the Wumpus slips away."<<endl;
        cout<<"Whew, that was close!"<<endl;
        cout<<"You are in room "<<currentPlayerPosition<<"."<<endl;
        hazardCheck(maze, storingVariables, validMoves, currentPlayerPosition);  // checking if the wumpus is still in one of the valid moves 
     }
}//end of enteringWumpusRoom()

// function will determine what will happen if a player enters a room who has bats in it
bool enteringBatsRoom(int maze[][MAX_NUM_CONNECTED], int storingVariables[], int validMoves[],int currentPlayerPosition)
{
    int bats1 = storingVariables[0];         // this particular index of array has the position of the bats1
    int bats2 = storingVariables[1];         // this particular index of array has the position of the bats2
    
    if(currentPlayerPosition == bats1 || currentPlayerPosition == bats2) //checking if the player entered one of the room which has bats
    {
        storingVariables[5] = (rand()%21);  // the bats will pick the player and drop in one of the random rooms
        if(currentPlayerPosition == bats1)  //if player enters which has bats1
        {  
          storingVariables[0] = (rand()%21);  //changing the location of the bats1 after they dropped the player to different room
        }
        if(currentPlayerPosition == bats2)   //if player enters which has bats2
        {
          storingVariables[1] = (rand()%21);  //changing the location of the bats1 after they dropped the player to different room
        }
        currentPlayerPosition = storingVariables[5]; // storing the location of player in the variable
        cout<<"Woah... you're flying!"<<endl;
        cout<<"You've just been transported by bats to room "<<currentPlayerPosition<<endl;
        cout<<"You are in room "<<currentPlayerPosition<<"."<<endl;
        hazardCheck(maze, storingVariables, validMoves, currentPlayerPosition); //checking for the hazards around the player's new location
      return true;
     }
  return false;
}// end of enteringBatsRoom()

//this function will make the player move and also check for the hazards
void makingPersonMove(int maze[][MAX_NUM_CONNECTED], int currentPlayerPosition, int storingVariables[], int roomToMove, int &index)
{
    int validMoves[MAX_NUM_CONNECTED];       // this array will store rooms to which player can move
    int bats1 = storingVariables[0];         // this particular index of array has the position of the bats1
    int bats2 = storingVariables[1];         // this particular index of array has the position of the bats2
    int pits1 =  storingVariables[2];        // this particular index of array has the position of the pits1
    int pits2 = storingVariables[3];         // this particular index of array has the position of the pits2
    int wumpus = storingVariables[4];        // this particular index of array has the position of the wumpus
    bool batsRoom = false;                   // batsroom to be false 
    int previousPlayerPosition = storingVariables[5];  // making temp variable for player location to check invalid moves
  
    for(int j=0;j<3;j++)
    {
        validMoves[j] = maze[storingVariables[5]][j];  //getting the valid rooms by checking it into the maze array according to the player position
        if(roomToMove == validMoves[j])  //checking if the userinput is within room allowed to go
        {
            storingVariables[5] = roomToMove;  // changing the player location to the room entered by the user
            currentPlayerPosition = storingVariables[5];  // storing the location of player in a variable

            if(currentPlayerPosition != wumpus  && currentPlayerPosition != pits1 && currentPlayerPosition != pits2
               && currentPlayerPosition != bats2 && currentPlayerPosition != bats1 && currentPlayerPosition != storingVariables[6]) 
            {                                                                   // if the player enters the room containing the hazards it should 
              cout<<"You are in room "<<currentPlayerPosition<<"."<<endl;      //now print the room player is in
            }
            hazardCheck(maze, storingVariables, validMoves, currentPlayerPosition);  //checking of hazards as the position of player is changed
            enteringWumpusRoom(maze, storingVariables, validMoves, currentPlayerPosition);  //checking if the player entered th room with the wumpus
            batsRoom = enteringBatsRoom(maze, storingVariables, validMoves, currentPlayerPosition);  // checking if the player entered the room with bats
        
        }
    }// end of for loop
  
    if (storingVariables[5] == storingVariables[6]) // when person shot an arrow ann went into that room
    {
      storingVariables[6] = -1;
      cout<<"Congratulations, you found the arrow and can once again shoot."<<endl;
      cout<<"You are in room "<<currentPlayerPosition<<"."<<endl;
    }
  
    if((previousPlayerPosition != validMoves[0] && previousPlayerPosition != validMoves[1] && previousPlayerPosition != validMoves[2]) && !batsRoom)
    {                    //checking if the user input was within the valid room and also when bats took the player to different room it should
      index--;           // not be counted as an invalid room
      cout<<"\nInvalid move.  Please retry."<<endl;
      cout<<"You are in room "<<storingVariables[5]<<"."<<endl;
      hazardCheck(maze, storingVariables, validMoves, currentPlayerPosition);  // checking hazard even if the player did not move to another room
    }
    cout<<endl;
    cout<<index<<". Enter your move (or 'D' for directions):"<<endl;
    
}// end of makingPersonMove()

//***Park: Nice function decompositions. 
//--------------------------------------------------------------------------------
int main()
{   
    // Seed the random number generator.  Change seed to time(0) to change output each time.
    //srand(time(0));
    int validMoves[MAX_NUM_CONNECTED];   // this array will store rooms to which player can move 
    int currentPlayerPosition;          // this particular index of array has the position of the player
    int storingVariables[7];           // storing all the different variables required for this game in an array
    char userIn= ' ';         // input from the user to get different aspects of the game
    int roomToMove = 0;      //the room selected by the player to move
    int index =1;           // counter for the moves 
  
    gettingRandomNum(storingVariables); //calling the fucntion to set random numbers to variables and storing it in the array
    int maze[NUMBER_OF_ROOMS + 1][MAX_NUM_CONNECTED] = {{0,0,0},{2,5,8},{1,3,10},{2,4,12},{3,5,14},{1,4,6},{5,7,15},{6,8,17},{1,7,9},{8,10,18},
                                                    {2,9,11},{10,12,19},{3,11,13},{12,14,20},{4,13,15},{6,14,16},{15,17,20},{7,16,18},
                                                    {9,17,19},{11,18,20},{13,16,19}};  // rooms connected to a particular index of the array
  
    currentPlayerPosition = storingVariables[5];  //location of the player stored in a variable
    cout<<"You are in room "<<currentPlayerPosition<<"."<<endl;  //keeping track of what room player is in
  
    hazardCheck(maze, storingVariables, validMoves, currentPlayerPosition);  //checking for the hazards when the game starts
    cout<<index<<". Enter your move (or 'D' for directions):"<<endl;  //asking palyer for next move

    // the event loop which will keep the game going untill user win, lose or chooses to exit
    while(true)
    {
        index++;
        cin>>userIn; // input from the user to get different aspects of the ga,e
        userIn = toupper(userIn); // converting the input to upper case
      
        if(userIn == 'D') // this input will display the instructions and direction of the game
        {
          index--;
           displayCave();  // display the map of the cave
           displayInstructions(); // display the instructions to the user
           cout<<index<<". Enter your move (or 'D' for directions):"<<endl;
        }
      
        if(userIn == 'P') // this  input will print the map of the game
        {
           index--;
           displayCave();  // display the map of the cave
           cout<<index<<". Enter your move (or 'D' for directions):"<<endl;
        }
      
        if (userIn == 'C') // this input will show the location of all the hazards in the game
        {
            index--;
            cout<<"Cheating! Game elements are in the following rooms:"<<endl;
            cout<<"Player Wumpus Bats1 Bats2 Pit1 Pit2 Arrow"<<endl;
          
            cout<<storingVariables[5]<<setw(5)<<storingVariables[4]<<setw(5)<<storingVariables[0]<<setw(5)<<storingVariables[1]<<setw(5)
             <<storingVariables[2]<<setw(5)<<storingVariables[3]<<setw(5)<<storingVariables[6]<<endl;
          
            cout<<"You are in room "<<storingVariables[5]<<"."<<endl;
            cout<<index<<". Enter your move (or 'D' for directions):"<<endl;
        }
        if(userIn == 'X') // this input will let player exit the game
        {
           cout << "\nExiting Program ..." << endl;
           exit(0);
        }
      
        if(userIn == 'M') // this input will be used to move a player
        {
           cin>>roomToMove; // next room where player want to move
           makingPersonMove(maze,currentPlayerPosition,storingVariables,roomToMove,index); // fucntion will be used to check different aspects of the move
           
        }
      
        if (userIn == 'R') // this input can reset the values of the all the hazards and player location
        { 
          index--;
          cout<<endl;
          cout<<"(Remember arrow value of -1 means it is with the person.)"<<endl;
          cout<<"Enter the 7 room locations (1..20) for player, wumpus, bats1, bats2, pit1, pit2, and arrow:"<<endl;
          
          cin>>storingVariables[5]>>storingVariables[4]>>storingVariables[0]>> storingVariables[1]>>storingVariables[2]
            >>storingVariables[3]>>storingVariables[6];
          
          cout<<"You are in room "<<storingVariables[5]<<"."<<endl;
          hazardCheck(maze, storingVariables, validMoves, currentPlayerPosition); //this function will check the hazards around the player's room
          cout<<index<<". Enter your move (or 'D' for directions):"<<endl;
        }
      
        if (userIn == 'S')  // this input will let the player shoot
        {  
           if(storingVariables[6] == -1)
           {
              storingVariables[6]=0;  // changing the value of arrow once the palyer shoots     
              int limitRoomToShoot = 0 ; // limit of rooms allowed to shoot
              int roomToShoot[3]; // storing the output of room number which player input
             
              cout<<"Enter the number of rooms (1..3) into which you want to shoot, followed by the rooms themselves:"<<endl;
             //fumction will check different aspects of shooting
              shootingArrow(maze, storingVariables, validMoves, currentPlayerPosition, roomToShoot, limitRoomToShoot);
             
              cout<<"You are in room "<<storingVariables[5]<<"."<<endl;
              cout<<index<<". Enter your move (or 'D' for directions):"<<endl;
           }
           else // if person doesnot have the arrow
           {
            cout<<"Sorry, you can't shoot an arrow you don't have.  Go find it."<<endl;
            cout<<"You are in room "<<currentPlayerPosition<<"."<<endl;
            cout<<index<<". Enter your move (or 'D' for directions):"<<endl;
           }
        }
    }// end of while loop
  return 0;
}//end main()
