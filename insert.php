<?php

include 'db.php';

header('Content-Type: application/json');

$data = json_decode(file_get_contents('php://input'), true);

if($data){

    $distance = $data['distance'];
    $status = $data['status'];

    $sql = mysqli_query(
        $conn,
        "INSERT INTO data(distance,status)
         VALUES('$distance','$status')"
    );

    if($sql){
        echo json_encode([
            "message"=>"Data inserted successfully"
        ]);
    }else{
        echo json_encode([
            "message"=>$conn->error
        ]);
    }

}

?>