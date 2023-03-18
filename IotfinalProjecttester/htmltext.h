


char page[] PROGMEM = R"(
<!DOCTYPE html>

<html>

  
<head>

  <title>Iot Project</title>

  <style>
  </style>

</head>

<body>
  <h1>Web page 1 @@ under test</h1>
  <p> Iot Final Project</p>


<button class = 'page2' id='page2' onclick="document.location='page2.html'" > Link to page 2
</button>





<br>
<p id=''>
  loaded??
</p>
<br>

<button class = 'startfan' id='startfan'
     onclick = 'sendData("startfan")'> start Fan
</button>
<p id="fandata">
  ......
</p>


<button class = 'stopfan' id='stopfan'
     onclick = 'sendData("stopfan")'> stop Fan
</button>

<button class = 'lastsaved' id='lastsaved' onclick = 'sendData("lastsaved")'> show last saved data

</button>

<p id='lastsaveddata'>The last saved data</p>



     

<script>

  function performStartStop(URL, variab){
    var xhr = new XMLHttpRequest();
    xhr.onload = function(){
      document.getElementById(variab).innerHTML = this.responseText;
    }
    xhr.open('GET', URL, true);
    xhr.send();
  }

  function sendData(butn){
    var URL, variab;
    if(butn == 'startfan'){
      URL = 'startfan';
      variab = "fandata";
      performStartStop(URL, variab);
    }
    else if(butn == 'stopfan'){
      URL = 'stopfan';
      variab = "fandata";
      performStartStop(URL, variab);
    }
    else if(butn == 'lastsaved'){
      URL = "http://localhost/sensorproject/IoTFinalProject/retrieve.php?";
      variab = "lastsaveddata";
       performStartStop(URL, variab);
    }

  }





</script>

</body>


</html>
)";
