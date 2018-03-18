
<p>Введите выражение:</p>
<form action="StringCompute.php" method="get">
<input type="text" name="str" required></input>
<input type="checkbox" name="check"></input>
<label for="check">Подробности</label>
<br><br>
<input type="submit"></input>
</form>
<p>
<?php
    function parse($str) {
        $tokens = [];
        $buf = "";
        for($i=0;$i<strlen($str);$i++) {
            if(is_numeric($str[$i])) 
                $buf.=$str[$i];
            else switch($str[$i]) {
                case '+':
                case '-':
                case '*':
                case '/':
                case '(':
                case ')':
                    array_push($tokens,$buf);
                    $buf="";
                    array_push($tokens, $str[$i]);
                    break;
            }
        }
        array_push($tokens,$buf);
        return $tokens;
    }
    function compute($tokens) {
        $opStack = [];
        $digStack = [];
        for($i=0;$i<count($tokens);$i++) {
            if(is_numeric($tokens[$i]))
                array_push($digStack,$tokens[$i]);
            else if($tokens[$i]=="+" or $tokens[$i]=="-") {
                  $op = array_pop($opStack);
                  while($op!=null and($op=="+" or $op=="/" or "$op==+" or $op=="-") 
                  and $op!="(" and $op!=")"){
                       $a2 = array_pop($digStack);
                       $a1 = array_pop($digStack);
                       if($op == "*") $res = $a1*$a2;
                       else if($op == "/") $res = $a1/$a2;
                       else if($op == "+") $res = $a1+$a2;
                       else if($op == "-") $res = $a1-$a2;
                       array_push($digStack,$res);
                       $op = array_pop($opStack);
                  }
                  if($op == "(" or $op == ")") array_push($opStack,$op);
                  array_push($opStack,$tokens[$i]);
               }
            else if($tokens[$i]=="*" or $tokens[$i]=="/") 
                  array_push($opStack,$tokens[$i]);
            else if($tokens[$i]=="(")
                  array_push($opStack,$tokens[$i]);
            else if($tokens[$i]==")") {
                  $op = array_pop($opStack);
                  while($op!=null and $op!="("){
                       $a2 = array_pop($digStack);
                       $a1 = array_pop($digStack);
                       if($op == "*") $res = $a1*$a2;
                       else if($op == "/") $res = $a1/$a2;
                       else if($op == "+") $res = $a1+$a2;
                       else if($op == "-") $res = $a1-$a2;
                       array_push($digStack,$res);
                       $op = array_pop($opStack);
                  }
            }
            if($_GET[check]) {
                echo "Стек чисел: ".json_encode($digStack)."<br>";
                echo  "Стек операций: ".json_encode($opStack)."<br><br>";
            }
        }
        while(count($digStack)>1) {
             $a2 = array_pop($digStack);
             $a1 = array_pop($digStack);
             $op = array_pop($opStack);
             if($op == "+") $res = $a1+$a2;
             else if($op == "-") $res = $a1-$a2;
             else if($op=="*")$res = $a1*$a2;
             else if($op=="/")$res = $a1/$a2;
             array_push($digStack,$res);
             if($_GET[check]) {
                echo "Стек чисел: ".json_encode($digStack)."<br>";
                echo  "Стек операций: ".json_encode($opStack)."<br><br>";
            }
        }
        return $digStack[0];
    }
    if($_GET[str]) {
        $str = $_GET[str];
        $tokens = parse($str);
        $res = compute($tokens);
        echo "Результат: $res"; 
    }
    ?>
</p>
