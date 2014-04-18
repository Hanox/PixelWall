<?php
    
    /* http://mydomain.com/webservice.php?id=thesecretid&data=012012012012012... */

    if( isset($_GET['id']) && isset($_GET['data']) )
    {
        $id = $_GET['id'];
        $data = $_GET['data'];
        
        echo "id: $id<br/>";
        echo "data: $data<br/>";
        
        //securely check if the id is valid (using a hidden php script, out of public html or with .htacces restrictions)
        $idValid = true;
        //bool idValid = hiddenPhp.isIdValid($id);

        //check if data is valid: 600 integers being 0,1 or 2
        $dataValid = true;
        //$dataValid = is_int($data) && strlen($data) == 600;
        
        if($dataValid && $idValid)
        {
            //write the file
            $file = 'pixeldata.txt';
            
            $current = file_get_contents($file);
            echo "file content before: $current<br/>";
            
            // Open the file to get existing content
            //$current = file_get_contents($file);
            
            // Append a new person to the file
            //$current .= "John Smith\n";
            $current = $data;
            
            // Write the contents back to the file
            file_put_contents($file, $current);
            
            $current = file_get_contents($file);
            echo "file content: $current<br/>";
        }
    }
?>