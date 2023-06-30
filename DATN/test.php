<?php
$variable_from_php = "Hello from PHP"; // The variable you want to pass

// Construct the command to execute the Python script with the variable as an argument
$command = "python test.py " . escapeshellarg($variable_from_php);

// Execute the command
$output = shell_exec($command);

// Display the output from the Python script
echo $output;
?>
