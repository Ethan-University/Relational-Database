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
<h3>Enter information about a player to add to the database:</h3>
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

<form action="odbc_insert_player.php" method="post">
    PlayerId: <input type="text" name="PlayerId"><br>
    TeamId: <input type="text" name="TeamId"><br>
    Name: <input type="text" name="Name"><br>
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
    $PageId = "2";
    $PlayerId = escapeshellarg($_POST[PlayerId]);
    $TeamId = escapeshellarg($_POST[TeamId]);
    $Name = escapeshellarg($_POST[Name]);
    $Position = escapeshellarg($_POST[Position]);
    

    $command = '/home/egcastle/public_html/project_cpp/odbc_insert_item.exe ' . $PageId . ' ' . $PlayerId . ' ' . $TeamId . ' ' . $Name . ' '.$Position;

    // remove dangerous characters from command to protect web server
    $command = escapeshellcmd($command);
 
    // run odbc_insert_item.exe
    system($command);           
}
?>


