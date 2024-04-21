<?php
ini_set("display_errors", "Off");  //set this to "On" for debugging  ,especially when no reason blank shows up.
//error_reporting(E_ALL);
header("Content-Type:text/html;charset=utf8");
        $now=date("Ymd",time());
        $code=$_GET['code'];
        $t=90;
        if(isset($_GET['t']))$t=intval($_GET['t']);
        if($t<20)$t=20;
        $start=date("Ymd",time()-$t/2*3*3600*24);
        $url="http://q.stock.sohu.com/hisHq?code=cn_$code&start=$start&end=$now&stat=1&order=D&period=d&callback=historySearchHandler&rt=json";
        $json=file_get_contents($url);
        //$json=substr($json,1,strlen($json)-3);
        $json=mb_convert_encoding($json, "utf8", "gbk");
        $data=json_decode($json);
        //echo ($json);
        $hq=$data[0]->hq;
        echo count($hq)."\r\n";
        foreach($hq as $day){

                echo str_replace("-","",$day[0])." ".($day[1]*100)." ".($day[2]*100)." ".($day[5]*100)." ".($day[6]*100)." ".$day[7]."\r\n";
        }

