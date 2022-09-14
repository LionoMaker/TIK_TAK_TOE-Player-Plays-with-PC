
#include <Arduino.h>
char Array[3][3]; // 3x3 Matri Array, empty of the length of 3*3=9
const char Player = '%';
const char PC = '*';

int userInput()
{ // user input from Serial monitor
  int data;
  Serial.flush();
  // long t = millis();
  while (!Serial.available())
  {
    // if (millis() - t > 1000)
    // {
    //   t = millis();
    //   Serial.println("!");
    // }
  }
  String str = "";
  while (Serial.available())
  {
    char c = Serial.read();
    if (c == '\n')
      break;
    str += c;
  }
  Serial.println(str);
  data = str.toInt(); // Read integer type data
  return data;
}

char checkWinner()
{
  // check the rows, return ' '
  for (int i = 0; i < 3; i++)
  {
    if (Array[i][0] == Array[i][1] && Array[i][0] == Array[i][2])
    {
      return Array[i][0];
    }
  }
  // check the columns

  for (int i = 0; i < 3; i++)
  {
    if (Array[0][i] == Array[1][i] && Array[0][i] == Array[2][i])
    {
      return Array[0][i];
    }

    /* code */
  }
  // check diagonals
  if (Array[0][0] == Array[1][1] && Array[0][0] == Array[2][2])
  {
    return Array[0][0];
  }

  if (Array[0][2] == Array[1][1] && Array[0][2] == Array[2][0])
  {
    return Array[0][2];
  }

  return ' ';
}

void PrintWinnner(char winner)
{
  if (winner == Player)
  {
    printf(" YOU WIN!");
  }
  else if (winner == PC)
  {
    printf(" YOU LOSE!");
  }
  else
  {
    printf(" MATCH DRAW!");
  }
}

void resetUI() // reset the UI formate to blank spaces
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      Array[i][j] = ' '; // blank spaces
    }
  }
}

void GameUI() // print the TIK TAK TOE UI
{
  printf("\n<TIK_TAK_TOE GAME>\n");
  printf("\nUSER PLAYS WITH PC:\n\n");
  printf(" %c | %c | %c ", Array[0][0], Array[0][1], Array[0][2]);
  printf("\n---|---|---\n");
  printf(" %c | %c | %c ", Array[1][0], Array[1][1], Array[1][2]);
  printf("\n---|---|---\n");
  printf(" %c | %c | %c ", Array[2][0], Array[2][1], Array[2][2]);
  printf("\n");
}

int CheckFreeSpaces()
{
  int freespaces = 9;
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (Array[i][j] != ' ') // check if the spaces is empty or not
      {
        freespaces--; // return remaining Freespaces
      }
      /* code */
    }

    /* code */
  }
  return freespaces;
}

void check_pairs()
{
  Serial.println("In check pairs \n");

  // check the possible corners Pairig
  if ((Array[0][0] == Array[0][1]) || (Array[1][1] == Array[2][0]) || (Array[1][2] == Array[2][2]))
  {
    /*here we are taking first corner which is equal to following patterns:
    (0,0)==(0,1)---->(0,2)
    (2,0)==(1,1)---->(0,2)
    (1,2)==(2,2)---->(0,2)
   */
    Array[0][2] = PC;
  }
  else
  {
    Array[0][2] != PC;
  }

  if ((Array[0][1] == Array[0][2]) || (Array[1][1] == Array[2][2]) || (Array[1][0] == Array[2][0]))
  {
    /*here we are taking second corner which is equal to following patterns:
    (0,1)==(0,2)---->(0,0)
    (2,2)==(1,1)---->(0,0)
    (1,0)==(2,0)---->(0,0)
   */
    Array[0][0] = PC;
  }
  else
  {
    Array[0][0] != PC;
  }

  if ((Array[0][1] == Array[1][2]) || (Array[0][0] == Array[1][1]) || (Array[2][0] == Array[2][1]))
  {
    /*here we are taking third corner which is equal to following patterns:
    (0,0)==(1,1)---->(2,2)
    (0,1)==(1,2)---->(2,2)
    (2,0)==(2,1)---->(2,2)
   */
    Array[2][2] = PC;
  }
  else
  {
    Array[2][2] != PC;
  }

  if ((Array[0][0] == Array[1][0]) || (Array[0][2] == Array[1][1]) || (Array[2][2] == Array[2][1]))
  {
    /*here we are taking fourth corner which is equal to following patterns:
    (0,0)==(1,0)---->(2,0)
    (0,2)==(1,1)---->(2,0)
    (2,2)==(2,1)---->(2,0)
   */
    Array[2][0] = PC;
  }
  else
  {
    Array[2][0] != PC;
  }

  // checking the possible sides pairs
  if ((Array[0][0] == Array[0][2]) || (Array[1][1] == Array[2][1]))
  {
    /*here we are taking first side in 1st row, pattern is:
    (0,0)==(0,2)---->(0,1)
    (1,1)==(2,1)---->(0,1)
    */

    Array[0][1] = PC;
  }
  else
  {
    Array[0][1] != PC;
  }

  if ((Array[0][0] == Array[2][0]) || (Array[1][1] == Array[1][2]))
  {
    /*here we are taking 2nd side in 2nd row, pattern is:
    (0,0)==(2,0)---->(1,0)
    (1,1)==(1,2)---->(1,0)
    */

    Array[1][0] = PC;
  }
  else
  {
    Array[1][0] != PC;
  }

  if ((Array[2][0] == Array[2][2]) || (Array[1][1] == Array[0][1]))
  {
    /*here we are taking 3rd side in 3rd row, pattern is:
    (2,0)==(2,2)---->(2,1)
    (1,1)==(0,1)---->(2,1)
    */

    Array[2][1] = PC;
  }
  else
  {
    Array[2][1] != PC;
  }

  if ((Array[0][2] == Array[2][2]) || (Array[1][1] == Array[1][0]))
  {
    /*here we are taking 4rth side in 4rth row, pattern is:
    (2,2)==(0,2)---->(1,2)
    (1,1)==(1,0)---->(1,2)
    */

    Array[1][2] = PC;
  }
  else
  {
    Array[1][2] != PC;
  }
  // checking the possible pair on center point:
  if ((Array[0][1] == Array[2][1]) || (Array[1][0] == Array[1][2]) || (Array[0][0] == Array[1][1]) || (Array[0][2] == Array[2][0]) || (Array[0][0] == Array[2][2]))
  {
    /*here are the following patterns:
    (0,1)==(2,1)---->(1,1)
    (1,0)==(1,2)---->(1,1)
    (0,2)==(2,0)---->(1,1)
    (0,0)==(2,2)---->(1,1)
    */
    Array[1][1] = PC;
  }
  else
  {
    Array[1][1] != PC;
  }
}

void playerMove()
{ // player_1 plays its move
  int x, y;

  while (Array[x][y] != ' ')
  {

    x = userInput();
    x--; // limits numbers from 0----2
    printf("Enter Row #(1 to 3): ");

    y = userInput();
    y--; // limits numbers from 0----2
    printf("\nEnter column #(1 to 3): \n");

    if (Array[x][y] != ' ')
    {
      printf("Invalid move!\n"); // return this, for putting out of the limit of the number
    }
    else
    {
      Array[x][y] = Player; // return "%" at the relevant section, for within the limit of the number

      break;
    }
  }
}

void computer()
{ // computer plays, it uses the random functionn to create the random numb within the limit of (1 to 3)
  int x, y;
  if (CheckFreeSpaces() == 8)
  {
    do
    {
      x = random(3)%3; // 0-----2
      y = random(3)%3; // 0-----2
    } while (Array[x][y] != ' ');

    Array[x][y] = PC;
  }

  else
  {
    check_pairs();
  }

}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200); // Baud Rate
}

void loop()
{
  // put your main code here, to run repeatedly:
  char winner = ' '; // default case is empty chars

  resetUI();
  while (winner == ' ' && CheckFreeSpaces() != 0)
  {
    GameUI(); // Print user interface
    playerMove(); // player move 
    winner = checkWinner();
    if (winner != ' ' || CheckFreeSpaces() == 0)
    {
      break;
    }
    computer(); // pc moves
    winner = checkWinner();
    if (winner != ' ' || CheckFreeSpaces() == 0)
    {
      break;
    }
  }
  GameUI();
  PrintWinnner(winner);

  printf("\nThanks For Playing! \n");
  while(1);
}