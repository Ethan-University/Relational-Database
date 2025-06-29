<html>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ethan Castleman Database Management Project</title>
    <link rel="stylesheet" href="styles.css">
</head>
<main>
<h3>Display all players in a given position:</h3>

<form action="odbc_query_position.php" method="post">
    Position: <input type="text" name="Position"><br>
    <input name="submit" type="submit" >
</form>
<br><br>

<button class="back-button" onclick="window.location.href='index.html'">Home</button>
</main>
</html>

<?php
if (isset($_POST['submit'])) 
{
    // replace ' ' with '\ ' in the strings so they are treated as single command line args
    $PageId = "4";
    $Position = escapeshellarg($_POST[Position]);
    
    $command = '/home/egcastle/public_html/project_cpp/odbc_insert_item.exe ' . $PageId . ' '  . $Position;

    // remove dangerous characters from command to protect web server
    $command = escapeshellcmd($command);
 
    // run odbc_insert_item.exe
    system($command);           
}
?>


