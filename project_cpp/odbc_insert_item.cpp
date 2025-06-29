/* Compile using:
g++ -Wall -I/usr/include/cppconn -o odbc odbc_insert_restaurant.cpp -L/usr/lib -lmysqlcppconn 
run: 
./odbc */
#include "odbc_db.h"
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char *argv[])
{
   string Username = "egcastle";   // Change to your own username
   string mysqlPassword = "aeDoo3tu";  // Change to your mysql password
   string SchemaName = "egcastle"; // Change to your username

   odbc_db myDB;
   myDB.Connect(Username, mysqlPassword, SchemaName);
   myDB.initDatabase();
   
   string pageId;

   pageId = argv[1];

   if (pageId == "1")
   {
      // For debugging purposes:  Show the database before insert
      string builder = "";
      string query1 = "SELECT * from Game;";
   
      // Parse input string to get first team ID, second team ID, first team score, and seacond team score
      string TeamId1;
      string TeamId2;
      string Score1;
      string Score2;

      // Read command line arguments
      // First arg, arg[0] is the name of the program
      // Next args are the parameters
      TeamId1 = argv[2];
      TeamId2 = argv[3];
      Score1 = argv[4];
      Score2 = argv[5];

      if ((TeamId1 != "1" && TeamId1 != "2" && TeamId1 != "3" && TeamId1 != "4") || (TeamId2 != "1" && TeamId2 != "2" && TeamId2 != "3" && TeamId2 != "4"))

      {
         cout << "ERROR: Invalid Team ID" << endl;
      }

      else
      {
         // Get the next id
         string q = "select IFNULL(max(GameId), 0) as max_id from Game";
         sql::ResultSet *result = myDB.rawQuery(q);
         int next_id = 1;
         if (result->next()) // get first row of result set
            next_id += result->getInt("max_id");

         // Insert the new game
         string input = "'" + to_string(next_id) + "','" + TeamId1 + "','" + TeamId2 + "','" + Score1 + "','" + Score2 + "', CURRENT_DATE()";

         // DEBUG:
         //printf("%s", input.c_str());
         myDB.insert("Game", input);    // insert new Team 
         //For debugging purposes: Show the database after insert
         builder.append(myDB.query(query1));
         cout << builder;
      } 
   }

   if (pageId == "2")
   {
      // For debugging purposes:  Show the database before insert
      string builder = "";
      string query1 = "SELECT * from Player;";
   
      // Parse input string to get player ID, team ID and player name, and position
      string PlayerId;
      string TeamId;
      string Name;
      string Position;

      // Read command line arguments
      // First arg, arg[0] is the name of the program
      // Next args are the parameters
      PlayerId = argv[2];
      TeamId = argv[3];
      Name = argv[4];
      Position = argv[5];
      
      if (TeamId != "1" && TeamId != "2" && TeamId != "3" && TeamId != "4")
      {
         cout << "ERROR: Invalid Team ID" << endl;
      }

      else 
      {
         // Insert the new player
      string input = "'" + PlayerId + "','" + TeamId + "','" + Name + "','" + Position + "'";

      // DEBUG:
      //printf("%s", input.c_str());
      myDB.insert("Player", input);    // insert new player
      //For debugging purposes: Show the database after insert
      builder.append("<br><br><br> Table Player after:" + myDB.query(query1));
      cout << builder; 
      }
   }

   if (pageId == "3")
   {
      string TeamId = argv[2];
      if (TeamId != "1" && TeamId != "2" && TeamId != "3" && TeamId != "4")
      {
         cout << "ERROR: Invalid Team ID" << endl;
      }
      else
      {
         string input = "SELECT PlayerId, Name, Position FROM Player WHERE TeamId = '" + TeamId + "';";
         cout << myDB.query(input) << endl;
      }
   }

   if (pageId == "4")
   {
      string Position = argv[2];
      string input = "SELECT PlayerId, TeamId, Name, Position FROM Player WHERE Position = '" + Position + "';";
      cout << myDB.query(input) << endl;
   }
   
   if (pageId == "5")
   {
      //string input = "SELECT t.TeamId, t.Location, t.NickName, t.Conference, SUM(CASE WHEN g.TeamId1 = t.TeamId AND g.Score1 > g.Score2 THEN 1 WHEN g.TeamId2 = t.TeamId AND g.Score2 > g.Score1 THEN 1 ELSE 0 END) AS OverallWins, SUM(CASE WHEN (g.TeamId1 = t.TeamId OR g.TeamId2 = t.TeamId) AND t1.Conference = t.Conference THEN 1 ELSE 0 END) AS ConferenceWins FROM Team t LEFT JOIN Game g ON t.TeamId = g.TeamId1 OR t.TeamId = g.TeamId2 LEFT JOIN Team t1 ON (g.TeamId1 = t1.TeamId OR g.TeamId2 = t1.TeamId) AND t1.Conference = t.Conference GROUP BY t.TeamId, t.Location, t.NickName, t.Conference ORDER BY t.Conference ASC, ConferenceWins DESC, OverallWins DESC, t.Location ASC;";
      // string input = "SELECT t.TeamId, t.Location, t.NickName, SUM(CASE WHEN t.TeamId = g.TeamId1 AND g.Score1 > g.Score2 THEN 1 WHEN t.TeamId = g.TeamId2 AND g.Score2 > g.Score1 THEN 1 ELSE 0 END) AS Wins FROM Team t LEFT JOIN Game g ON t.TeamId = g.TeamId1 OR t.TeamId = g.TeamId2 GROUP BY t.TeamId, t.Location, t.NickName;";
      // cout << myDB.query(input) << endl;
      // input = "SELECT t.Conference, SUM(CASE WHEN ((t.TeamId = g.TeamId1 AND g.Score1 > g.Score2) OR (t.TeamId = g.TeamId2 AND g.Score2 > g.Score1)) THEN 1 ELSE 0 END) AS ConferenceWins FROM Team t LEFT JOIN Game g ON t.TeamId = g.TeamId1 OR t.TeamId = g.TeamId2 WHERE g.TeamId1 IS NOT NULL AND g.TeamId2 IS NOT NULL GROUP BY t.Conference;";
      // cout << myDB.query(input);
      string input = "SELECT t.TeamId, t.Location, t.NickName, t.Conference FROM Team t LEFT JOIN Game g ON t.TeamId = g.TeamId1 OR t.TeamId = g.TeamId2 LEFT JOIN Team t1 ON (g.TeamId1 = t1.TeamId OR g.TeamId2 = t1.TeamId) GROUP BY t.TeamId, t.Location, t.NickName, t.Conference ORDER BY t.Conference ASC, SUM(CASE WHEN t.TeamId = g.TeamId1 AND g.Score1 > g.Score2 THEN 1 WHEN t.TeamId = g.TeamId2 AND g.Score2 > g.Score1 THEN 1 ELSE 0 END) DESC, SUM(CASE WHEN (t.TeamId = g.TeamId1 OR t.TeamId = g.TeamId2) AND t.Conference = t1.Conference AND ((t.TeamId = g.TeamId1 AND g.Score1 > g.Score2) OR (t.TeamId = g.TeamId2 AND g.Score2 > g.Score1)) THEN 1 ELSE 0 END) DESC;";
      cout << myDB.query(input);
   }

   if (pageId == "6")
   {
      string NickName = argv[2];
      string input = "SELECT t1.Location AS Team_Location, t1.NickName AS Team_Nickname, g.Score1, g.date, t2.Location AS Opponent_Location, t2.NickName, g.Score2, CASE WHEN g.Score1 > g.Score2 THEN 'W' WHEN g.Score1 < g.Score2 THEN 'L' ELSE 'TIE' END AS Result FROM Game g JOIN Team t1 ON g.TeamId1 = t1.TeamId JOIN Team t2 ON g.TeamId2 = t2.TeamId WHERE t1.NickName = '" + NickName + "' ORDER BY g.date;";
      cout << myDB.query(input);
   }

   if (pageId == "7")
   {
      string date = argv[2];
      string input = "SELECT t1.NickName, t1.Location, g.Score1, t2.NickName, t2.Location, g.Score2, CASE WHEN g.Score1 > g.Score2 THEN t1.NickName WHEN g.Score1 < g.Score2 THEN t2.NickName END AS Winner FROM Game g JOIN Team t1 ON g.TeamId1 = t1.TeamId JOIN Team t2 ON g.TeamId2 = t2.TeamId WHERE g.date = '" + date +"';";
      cout << myDB.query(input);
   }
       
   myDB.disConnect();//disconect Database

   return 0;
}


