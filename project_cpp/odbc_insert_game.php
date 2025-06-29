<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Ethan Castleman Database Management Project</title>
    <link rel="stylesheet" href="styles.css">
</head>
<body>
<main>
<h3>Enter information about a game to add to the database:</h3>
<div>
    <b>Teams</b>
    <table>
        <thread>
            <tr>
                <th>Team ID</th>
                <th>Team Name</th>
            </tr>
        </thread>
        <tbody>
            <tr>
                <td>1</td>
                <td>Kansas City Cheifs</td>
            </tr>
            <tr>
                <td>2</td>
                <td>San Francisco 49ers</td>
            </tr>
            <tr>
                <td>3</td>
                <td>Los Angeles Rams</td>
            </tr>
            <tr>
                <td>4</td>
                <td>Denver Broncos</td>
            </tr>   
        </tbody>
    </table>
</div>

<form action="odbc_insert_game.php" method="post">
    TeamId1: <input type="text" name="TeamId1"><br>
    TeamId2: <input type="text" name="TeamId2"><br>
    Score1: <input type="text" name="Score1"><br>
    Score2: <input type="text" name="Score2"><br>
    <input name="submit" type="submit" >
</form>
<br><br>

<button class="back-button" onclick="window.location.href='index.html'">Home</button>
</main>
</body>
</html>

<?php
if (isset($_POST['submit'])) 
{
    // replace ' ' with '\ ' in the strings so they are treated as single command line args
    $PageId = "1";
    $TeamId1 = escapeshellarg($_POST[TeamId1]);
    $TeamId2 = escapeshellarg($_POST[TeamId2]);
    $Score1 = escapeshellarg($_POST[Score1]);
    $Score2 = escapeshellarg($_POST[Score2]);
    


    $command = '/home/egcastle/public_html/project_cpp/odbc_insert_item.exe ' . $PageId . ' ' . $TeamId1 . ' ' . $TeamId2 . ' ' . $Score1 . ' '.$Score2;
    
    // remove dangerous characters from command to protect web server
    $command = escapeshellcmd($command);
 
    // run odbc_insert_item.exe
    system($command);           
}
?>


