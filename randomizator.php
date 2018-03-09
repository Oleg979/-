<?php
function randomize($str) { // Функция рандомизации
///////////////////////////////////////////////
    // Координаты начала и конца изменяемой области
    $beginIdx = [];
    $endIdx = [];
    $stack = 0;
    for($i=0;$i<strlen($str);$i++) {
        if($str[$i]=="(") {
            $stack++;
            if($stack==1)array_push($beginIdx,$i);
        }
        else if($str[$i]==")") {
            $stack--;
           if($stack==0) array_push($endIdx,$i);
        } 
    }
///////////////////////////////////////////////
    if(count($beginIdx)==0) return $str;
    $result = "";
    for($i=0,$idx=0;$i<count($beginIdx);$i++) {
         $result .= substr($str, $idx, $beginIdx[$i]-$idx);
         //////////////////////////////////////////////////// 
         $randoms = 
         substr($str, $beginIdx[$i]+1, $endIdx[$i]-$beginIdx[$i]-1);
         //////////////////////////////////////////////////// 
         $stack = 0;
         $idx = 0;
         $choices = [];
         
         for($j=0;$j<strlen($randoms);$j++) {
             if($randoms[$j] == "(") $stack++;
             else if($randoms[$j] == ")") $stack--;
             else if($randoms[$j] == "|" and $stack==0) {
                  array_push($choices, substr($randoms,$idx,$j-$idx)); 
                  $idx = $j+1;
             }
         }
         array_push($choices, substr($randoms,$idx,strlen($randoms)-1));
         ///////////////////////////////////////////////////
         $choice = randomize($choices[rand(0,count($choices)-1)]);
         $result .= $choice;
         ///////////////////////////////////////////////////
         $idx = $endIdx[$i]+1;
         ///////////////////////////////////////////////////
    }
    $result .= substr($str, $idx, strlen($str));
    return $result; // Вывести результат
}
///////////////////////////////////////////////////////////////////////////////
$str = "go to (cinema|walk|cafe) and then (sleep on the (bed|(good|bad) chair)|eat|run) and all"; // Исходная строка
for($i=0;$i<10;$i++) echo randomize($str)."<br>"; // Тест функции
///////////////////////////////////////////////////////////////////////////////
?>
