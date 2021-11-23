<html>
<head>
<meta charset="UTF-8" />
<title>CN lab 10</title>
</head>
<body>
	<h1>PHP programming, Internet-based databases</h1><br />
	<?php



echo '<h3>Task CONNECTION:</h3><br />';

	$username = "root";
	$password = "";
	$database = "lab10db"; 
	$mysqli = new mysqli("localhost", $username, $password, $database); 
	$query = "SELECT * FROM People";


echo '<table border="0" cellspacing="2" cellpadding="2"> 
      <tr> 
          <td> <font face="Arial">PersonID</font> </td> 
          <td> <font face="Arial">LastName</font> </td> 
          <td> <font face="Arial">FirstName</font> </td> 
          <td> <font face="Arial">BirthDate</font> </td> 
          
      </tr>';

if ($result = $mysqli->query($query)) {
    while ($row = $result->fetch_assoc()) {
        $field1name = $row["PersonID"];
        $field2name = $row["LastName"];
        $field3name = $row["FirstName"];
        $field4name = $row["BirthDate"];
        

        echo '<tr> 
                  <td>'.$field1name.'</td> 
                  <td>'.$field2name.'</td> 
                  <td>'.$field3name.'</td> 
                  <td>'.$field4name.'</td> 
                 
              </tr>';
    }
    $result->free();
} 

	// Please provide the solution for the Task CONNECTION here.


	// Please provide the solution for the Task FORM here.
	
	echo '<form method="post" action="process.php">
			Name : <input type="text" name="first_name" placeholder="Enter Your Name" /><br />
			LastName : <input type="text" name="last_name" placeholder="Enter Your LastName" /><br />
			BirthDate : <input type="text" name="birth_date" placeholder="eg: YYYY-MM-DD" /><br />
			PersonID : <input type="number" name="person_id" placeholder="Enter Your ID" /><br />
			<input type="submit" value="Submit" />
		</form>'

//process.php
	


	
	?>
	
	</body>
</html>
