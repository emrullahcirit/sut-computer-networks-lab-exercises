<?php

	if ($_SERVER["REQUEST_METHOD"] == "POST") {//Check it is comming from a form

	//credentials
	$mysql_host = "localhost";
	$mysql_username = "root";
	$mysql_password = "";
	$mysql_database = "lab10db";
	
	$u_first_name = $_POST["first_name"]; //set PHP variables like this so we can use them anywhere in code below
	$u_last_name = $_POST["last_name"];
	$u_birth_date = $_POST["birth_date"];
	$u_person_id = $_POST["person_id"];


	//Open a new connection to the MySQL server
	$mysqli2 = new mysqli($mysql_host, $mysql_username, $mysql_password, $mysql_database);
	
	//Output any connection error
	if ($mysqli2->connect_error) {
		die('Error : ('. $mysqli2->connect_errno .') '. $mysqli2->connect_error);
	}	
	
	$statement = $mysqli2->prepare("INSERT INTO People VALUES(?, ?, ?, ?)"); //prepare sql insert query
	//bind parameters for markers, where (s = string, i = integer, d = double,  b = blob)
	$statement->bind_param('isss', $u_person_id, $u_last_name, $u_first_name,$u_birth_date); //bind values and execute insert query
	
	if($statement->execute()){
		print "Hello " . $u_first_name . "!, your message has been saved!";
	}else{
		print $mysqli2->error; //show mysql error if any
	}
}

?>
