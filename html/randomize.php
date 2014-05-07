<?php
    
    $id = "test";
    $data = "";
    for ($i = 0; $i < 600; $i++)
    {
        $data .= rand(0,2);
    }
    $today = getdate();
    $time = rtrim($today[mday]." ".$today[mon]." ".$today[year]." ".$today[hours]." ".$today[seconds]." ".$today[minutes]);
    
    //write the file
    $file = 'pixeldata.txt';
    $current = file_get_contents($file);
    $data = "$time|$data\n";
    $current .= $data;
    file_put_contents($file, $current);
    echo $data;
    
?>