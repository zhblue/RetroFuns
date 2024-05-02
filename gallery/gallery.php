<html lang="cn" style="position:fixed; width: 100%; overflow: hidden; "><head>
<meta charset="utf-8">
<meta content="IE=edge" http-equiv="X-UA-Compatible">
<meta name="viewport" content="width=device-width, initial-scale=0.5">
<?php
$con = dirname(__FILE__);
echo "<title>$con</title>";
$filename = scandir($con);
$conname = array();
$title=basename(dirname(__FILE__));
$ftitle=rawurlencode(preg_replace('/\.|\\\|\\/|\:|\*|\?|\"|\<|\>|\|/','',$title));
$i=0;
$id=-1;
?>
<body>
	<center>
<?php
if(isset($_GET['id'])) $id=intval($_GET['id']);
foreach($filename as $k=>$v){
    if($v=="." || $v==".."||$v=="play.php"){continue;}
    if($id>$i){ $i++;continue;}
    $conname[] = substr($v,0,strpos($v,"."));
    $title=str_replace("[","",$v);
    $title=str_replace("]","",$title);
    echo "<a href='".basename(__FILE__)."?id=".($id<0?$i:$i+1)."' ><img width=450px src='http://".$_SERVER["HTTP_HOST"].substr(dirname(__FILE__),16)."/".rawurlencode($v)."' ></a>\n";
    if($id>0) {
       echo "<br><a href='".basename(__FILE__)."?id=".($i-1)."' >&lt;</a>\n";
     }
    if($id>=0) {
    	if($id==0) echo "<br>";
       echo "<a href='".basename(__FILE__)."?id=".($i+1)."' >&gt;</a>\n";
     }
    if($id==$i) break;
    if($i++ % 2 ==1) echo "<br>";
}
?>
</center>
	</body>
