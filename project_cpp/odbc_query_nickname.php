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
<h3>Display team games given nickname:</h3>
<div>
    <table>
        <thread>
            <tr>
                <th>Team nickname</th>
            </tr>
        </thread>
        <tbody>
            <tr>
                <td>The Legion of Zoom</td>
            </tr>
            <tr>
                <td>Niners</td>
            </tr>
            <tr>
                <td>The Bolts</td>
            </tr>
            <tr>
                <td>No Fly Zone</td>
            </tr>   
        </tbody>
    </table>
</div>

<form action="odbc_query_nickname.php" method="post">
    NickName: <input type="text" name="NickName"><br>
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
    $PageId = "6";
    $NickName = escapeshellarg($_POST[NickName]);
    
    $command = '/home/egcastle/public_html/project_cpp/odbc_insert_item.exe ' . $PageId . ' '  . $NickName;

    // remove dangerous characters from command to protect web server
    $command = escapeshellcmd($command);
 
    // run odbc_insert_item.exe
    system($command);           
}
?>