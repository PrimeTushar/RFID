<form action="ardunio.php">
<input type="submit" name="submit" value="submit">
</form>
<?php
include "db.php";


	$id=filter_input(INPUT_POST,'para1');
	$id1=filter_input(INPUT_POST,'para2');
	$id2=filter_input(INPUT_POST,'para3');
	$id3=filter_input(INPUT_POST,'para4');
if($id1!=0 && $id2!=0 &&  $id3!=0)

{
//echo $id;
$sql="INSERT INTO table2(Para_1,Para_2,Para_3,Para_4)
        VALUES ('$id','$id1','$id2','$id3');";   
   }
    $run_query=mysqli_query($conn,$sql);	
if($run_query)
	{
		echo $id." ".$id1." ".$id2." ".$id3;
		echo "<b>Data has been send successfuly </b>";
	}
// }
mysqli_close($conn);

?>