char webpage[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<h1>Smart Socket</h1>
<head>
  <script>
    var Socket;
    function init() {
      Socket = new WebSocket('ws://' + window.location.hostname + ':81/');
      Socket.onmessage = function(event){
        var w = event.data;
        var btn =document.getElementById("toogle");
        var TimeSet =document.getElementById("set");
        console.log(w);
        if (w=="on  "){
          
          btn.value=event.data;
          btn.style.backgroundColor="green";
          btn.style.color="white";
        }
        else if(w=="off "){
          btn.value=event.data;
          btn.style.backgroundColor="rgb(231, 42, 42)"; 
          btn.style.color="white";
          
        }
        if (w=="1   ") {
          TimeSet.style.backgroundColor="green"; 
          TimeSet.style.color="white";         
        }
        else{
          TimeSet.style.backgroundColor="white"; 
          TimeSet.style.color="black";
         // console.log("r");
        }
      }
    
    }
    setTimeout(function(){      
      Socket.send("*");
       }, 500);
    function sendTime(){
      var M = parseInt(document.getElementById("Min").value, 10);
      var S = parseInt(document.getElementById("Sec").value, 10);
      var H = parseInt(document.getElementById("Hur").value, 10);
      var T = (H*3600)+(M*60) +S ;
      if(T!=0){
        Socket.send("#"+T);
      }
    
    }
    function toogle(){
      Socket.send(document.getElementById("toogle").value);
    }   
    function restTime(){
      Socket.send("#"+"0");
    }  
  </script>
  <style>
     h1{
    border-bottom-left-radius: 20px;
    border-bottom-right-radius: 20px;
    text-align: center ;    
    color:white;;
    background-color: rgb(167, 61, 12);
    font-family: 'Times New Roman';
    font-size:25px;
    border: 3px solid white;
   }    
  .input{
  margin-top: 25px;
    margin-bottom: 15px;
   margin-right: 44px;
   padding-left:10px; 
   width: 75px;
   height: 75px; 
   border: 1px;
   border-radius: 20px;
   background-color:  rgb(167, 61, 12);
   color: rgb(255, 255, 255);
   text-align: center;
   font-family:fantasy;
   font-size:30px;
  }


.btn{
  
    font-family:fantasy;  
    -webkit-transition-duration: 0.4s; /* Safari */
    transition-duration: 0.4s;
    border-radius: 40px;
    width:  75px;
    height: 75px; 
    border: 2px solid  rgb(167, 61, 12);
    background-color: white;
  }
  .btn:hover {
   box-shadow: 0 12px 16px 0 rgba(0,0,0,0.24), 0 17px 50px 0 rgba(0,0,0,0.19);
   border: 2px solid white;
   background-color: rgb(167, 61, 12);
}
.btn:active {
   background-color: rgb(167, 61, 12);
   box-shadow: 0 5px #666;
   transform: translateY(4px);
}
  #set{
   margin-top: 20px;
   margin-bottom: 15px;
   border-radius: 40px;
   width:  75px;
   height: 75px; 
  }
  #rest{
   -webkit-transition-duration: 0.4s; /* Safari */
   transition-duration: 0.4s;   
   border-radius: 40px;
   width:  75px;
   height: 30px; 
   background-color: white;
   color: rgb(231, 42, 42);
  }
  #rest:hover{
   background-color: rgb(231, 42, 42); 
   color: white;   
  }
  #toogle{
   border-radius: 40px;
   text-align:center;
   font-size:20px; 
  }
  </style>
</head>
<center>
<body onload="javascript:init()" style="background-color:rgb(255, 172, 133);">
    <input type="button" class="btn" id="toogle" value="Click"  onclick="toogle()" />
  <br>
  <hr/>
  <form>
        Hours:
        <input class="input" type="number" id="Hur" name="Hours"
         min="0" max="99" step="1" value="0">
        minutes:
        <input class="input" type="number" id="Min" name="minutes"
         min="0" max="99" step="1" value="0">
         seconds: <input class="input" type="number" id="Sec" name="seconds"
         min="0" max="60" step="5" value="0">
         <br>
         <input class="btn" type="button" id="set" value="SetTime" onclick="sendTime()" /><br>
        <input type="reset" value="Reset" id="rest" onclick="restTime()">
      </form>    
</center>
</body>
</html>
)=====";
