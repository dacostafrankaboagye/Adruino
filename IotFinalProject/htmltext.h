


char page[] PROGMEM = R"(
  <!DOCTYPE html><html><head>
  <title>Local network</title>
  <style>
  
  .on {background-color:red}
  .off {background-color:blue}
  </style></head>
  <body>
  <h1>ESP32 as server, but also connects to web</h1>
  <p> Working in STA mode </p>
  
  <table style='width:100%'><tr>
  <td>Green LED is <span id='LEDG'>OFF</span> now</td>
  <td>Red LED is <span id='LEDR'>OFF</span> now</td>
  </tr></table>
  
  <table style='width:100%'><tr>
  <td><button class = 'btn off' id='Green LED'
       onclick = 'sendData(id)'>Press to control the motor
       </button></td>
       <td><button class = 'btn off' id='Red LED'
     onclick = 'sendData(id)'>Press to turn MANUAL ON
     </button></td>
</tr></table>

<button class = 'current' id='currentLevel'
     onclick = 'sendData(id)'> current water level
     </button>

<div id="extText"> </div>
     
<script>
function sendData(butn)
{
  var URL, variab, text;
  if(butn == 'Red LED')
  {
    URL = 'LEDRurl';
    variab = 'LEDR';
  }
  else if(butn == 'Green LED')
  {
    URL = 'LEDGurl';
    variab = 'LEDG';
  }
  else if(butn == 'currentLevel')
  {
    URL = 'zeroUrl';
    variab = 'extText';
  }
  if(butn == 'Red LED' || butn == 'Green LED')
{ // change button class and text 
  var state = document.getElementById(butn).className;
  state = (state == 'btn on' ? 'btn off' : 'btn on');
  text = (state == 'btn on' ? butn + ' OFF' : butn + ' ON');
    document.getElementById(butn).className = state;
    document.getElementById(butn).innerHTML = 'Press to turn ' + text;
  }
  var xhr = new XMLHttpRequest();
  xhr.onload = function(){
    document.getElementById(variab).innerHTML = this.responseText;
  }
  xhr.open('GET', URL, true);
  xhr.send();
}



</script>
</body></html>
)";
