#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <ESPmDNS.h>
#else
#error "Board not found"
#endif

#include <WebSocketsServer.h>
#include <SPIFFS.h>
#include <ArduinoJson.h>
#include <DHT.h> 
#include <Ticker.h> //https://github.com/sstaub/Ticker

#define DHTPIN 4
#define LED1 2
#define LED2 5

#define DHTTYPE    DHT11
DHT dht(DHTPIN, DHTTYPE);

void send_sensor();

Ticker timer;

char webpage[] PROGMEM = R"=====(

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Web Server</title>
    <script src="/raphael-min.js"></script>
    <script src="/justgage.min.js"></script>
    <script src="/Chart.js"></script>
    <script src="/Chart.min.js"></script>

<style>
        #heading{
            height: 18vh;
            width: auto;
            /* align-self: auto; */
            display: block;
            margin-left: none;
        }
        h1 {
            color: wheat;
            outline: rgb(255, 255, 136);
            /* display: flex;  */\
            font-size: 3em;
            margin-left: none;
            font-family: Candara;
            margin-right: 60vw;
            margin-top: 1vh;
        }
        body {
            text-align: center;
            /* background: #000000; */
            background-image: url("/bc.jpg");
        }
        .wrapper{
            position: relative;
            top: -75px;
            height: 50vh;
            width: 50vw;
            display: flex;
            flex-direction: column;
            justify-content: center;
            align-items: center;
            margin-top: 20vh;
            
        }
        .Buttons{
            height: 10vw;
            width: 50vw;
            display: flex;
            flex-direction: row;
            justify-content: center;
            align-items: center;
            
        }
        .circle{
            width: auto;
            height: auto;
            background: gray;
            border-radius: 30px;
            padding:5px;
            border-radius: 34px;
            position: relative;
        }
        .switch {
        position: relative;
        display: inline-block;
        width: 60px;
        height: 34px;
        color:aliceblue;
        border-radius: 20px;
        }

        /* Hide default HTML checkbox */
        .switch input {
        opacity: 0;
        width: 0;
        height: 0;
        }
        .circle:before {
        border-radius: 50%;
        }
        .circle {
        position: absolute;
        cursor: pointer;
        top: 0;
        left: 0;
        right: 0;
        bottom: 0;
        background-color: #ccc;
        -webkit-transition: .4s;
        transition: .4s;
        }
        .switch:hover {
            box-shadow: 0 0 10px cyan, 0 0 20px cyan, 0 0 40px cyan, 0 0 80px cyan; /* Neon effect */ 
            border-radius: 50%;            
        }     
        .circle:before {
        position: absolute;
        content: "";
        height: 26px;
        width: 26px;
        left: 5px;
        bottom: 4px;
        background-color: white;
        -webkit-transition: .3s;
        transition: .3s;
        top: 0.4vh;
        margin-bottom: auto;
        align-self: center;
        }

        input:checked + .circle {
        background-color: #d220ff;
        border: 2vh;
        border-color: #db4dff;
        }

        input:focus + .circle {
        box-shadow: 0 0 1px #2196F3;
        }

        input:checked + .circle:before {
        -webkit-transform: translateX(24px);
        -ms-transform: translateX(24px);
        transform: translateX(24px);
        }
        .head{
            color: wheat;
            font-size: 5vh;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            display: block;
            margin: 1.5vh;
            margin-left: 2vw;

        }
        .head2{
            color: wheat;
            font-size: 5vh;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            display: block;
            margin: 1vw;
            margin-left: 6vw;
        }
        .gauge-container {
            display: inline-block;
            margin: 10px;
        }
        
        h3{
          color: white;  
          font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }
        
        
        .gauge-container {
        display: inline-block;
        margin: 10px;
        transition: box-shadow 0.3s ease; /* Add smooth transition on box-shadow */
        border-radius: 50%;
        }
    
        .gauge-container:hover {
            box-shadow: 0 0 10px cyan, 0 0 20px cyan, 0 0 40px cyan, 0 0 80px cyan; /* Neon effect */ 
            border-radius: 50%;            
        }     
        .chart-container{
          position: relative;
          top: 190px;
          left: 150px;
          height: fit-content;
        }
        .chart-container:hover{
          transition: box-shadow 0.3s ease;
          transform: scale(1.2);
          top:225px;
          box-shadow: 0 0 10px cyan, 0 0 20px cyan, 0 0 40px cyan, 0 0 80px cyan; /* Neon effect */ 
          border-radius: 5px; 
          height: fit-content;
        }
        #temp_gauge text{
          fill: white;
        }
        #hum_gauge text{
          fill: white;
        }
        #heading-lnf{
          font-size: 20vh;
        }
        #gauge-div{
          margin
        }
        #main-content{
          display: flex;
        }
    </style>
</head>
<body id="body" style="background-image: url('bc.jpg'); background-size: cover;">
    <section id="heading">
        <h1 id="heading-lnf">LostAndFound</h1>
    </section>
    <div id="main-content">
    <div class="wrapper">
        <div class="gauge">
            <span class="gola"></span>
        </div>
        <div class="Buttons">
            <h2 class="head">Switch 1: </h2>
            <label class="switch">
                <input type="checkbox" onchange="handleSwitch1Change(this)">
                <span class="circle"></span>
            </label>
            <h2 class="head2">Switch 2: </h2>
            <label class="switch">
                <input type="checkbox" onchange="handleSwitch2Change(this)">
                <span class="circle"></span>
            </label>
        </div>
         <div style="text-align: center;" id="guage-div">
                <!-- Temperature Gauge -->
                <div class="gauge-container">
                    <h3>Temperature</h3>
                    <div id="temp_gauge"></div>
                    <h3 id="temp_value" style="display: inline-block;">0</h3>
                </div>
                <!-- Humidity Gauge -->
                <div class="gauge-container">
                    <h3>Humidity</h3>
                    <div id="hum_gauge"></div>
                    <h3 id="hum_value" style="display: inline-block;">0</h3>
                    
                </div>
        </div>
    </div>
    <div class="chart-container">
<canvas id="temp_chart" width="600" height="300" style="background-color: white;"></canvas>
    </div>
    </div>
</body>
<script>
    var connection = new WebSocket('ws://' + location.hostname + ':81/');

    var button_1_status = 0;
    var button_2_status = 0;
    var temp_data = 0;
    var hum_data = 0;

      var temp_gauge = new JustGage({
        id: "temp_gauge",
        value: 0,
        min: 0,
        max: 100,
        title: "Temperature",
        label: "°C",
        gaugeWidthScale: 0.3,
        counter: true,
        formatNumber: true,
        pointer: true,
        pointerOptions: {
            toplength: -10,
            bottomlength: 10,
            bottomwidth: 8,
            color: 'cyan' // Set the pointer color to cyan
        },
        customSectors: [
            // ... (rest of the code)
        ],
    });

    // Create and initialize humidity gauge
    var hum_gauge = new JustGage({
        id: "hum_gauge",
        value: 0,
        min: 0,
        max: 100,
        title: "Humidity",
        label: "%",
        gaugeWidthScale: 0.3,
        counter: true,
        formatNumber: true,
        pointer: true,
        pointerOptions: {
            toplength: -10,
            bottomlength: 10,
            bottomwidth: 8,
            color: 'cyan' // Set the pointer color to cyan
        },
        customSectors: [
            // ... (rest of the code)
        ],
    });

var temperatureData = [];
var humidityData = [];
var timeLabels = [];
var canvas = document.getElementById('temp_chart');
var ctx = canvas.getContext('2d');

function updateTemperatureChart() {
  // Clear the canvas before drawing
  ctx.clearRect(0, 0, canvas.width, canvas.height);

  // Draw the graph background
  ctx.fillStyle = 'white';
  ctx.fillRect(0, 0, canvas.width, canvas.height);

  // Draw the X-axis (time)
  ctx.beginPath();
  ctx.moveTo(50, canvas.height - 30);
  ctx.lineTo(canvas.width - 30, canvas.height - 30);
  ctx.strokeStyle = 'black';
  ctx.lineWidth = 2;
  ctx.stroke();

  // Draw the Y-axis (temperature)
  ctx.beginPath();
  ctx.moveTo(50, 30);
  ctx.lineTo(50, canvas.height - 30);
  ctx.strokeStyle = 'black';
  ctx.lineWidth = 2;
  ctx.stroke();

  // Draw the tick marks and labels on the Y-axis (temperature)
  for (var temp = 0; temp <= 100; temp += 20) {
    var y = canvas.height - 30 - (temp * (canvas.height - 60) / 100);
    ctx.beginPath();
    ctx.moveTo(45, y);
    ctx.lineTo(50, y);
    ctx.strokeStyle = 'black';
    ctx.lineWidth = 1;
    ctx.stroke();

    ctx.fillStyle = 'black';
    ctx.font = '12px Arial';
    ctx.fillText(temp + '°C', 10, y + 5);
  }

  // Draw the temperature graph
  ctx.beginPath();
  ctx.strokeStyle = 'red';
  ctx.lineWidth = 2;

  for (var i = 0; i < temperatureData.length; i++) {
    var x = i * (canvas.width - 80) / temperatureData.length + 50;
    var y = canvas.height - 30 - (temperatureData[i] * (canvas.height - 60) / 100);

    if (i === 0) {
      ctx.moveTo(x, y);
    } else {
      ctx.lineTo(x, y);
    }
  }

  ctx.stroke();

  // Draw the humidity graph
  ctx.beginPath();
  ctx.strokeStyle = 'blue';
  ctx.lineWidth = 2;

  for (var i = 0; i < humidityData.length; i++) {
    var x = i * (canvas.width - 80) / humidityData.length + 50;
    var y = canvas.height - 30 - (humidityData[i] * (canvas.height - 60) / 100);

    if (i === 0) {
      ctx.moveTo(x, y);
    } else {
      ctx.lineTo(x, y);
    }
  }

  ctx.stroke();

  // Update the time labels
  ctx.fillStyle = 'black';
  ctx.font = '12px Arial';
  ctx.fillText(timeLabels[timeLabels.length - 1], canvas.width - 80, canvas.height - 10);
  ctx.fillText(timeLabels[0], 50, canvas.height - 10);
}

// Call the function once to initialize the graph
updateTemperatureChart();


 
    // WebSocket onmessage function
  connection.onmessage = function (event) {
  var full_data = event.data;
  console.log(full_data);
  var data = JSON.parse(full_data);
  temp_data = parseFloat(data.temp); // Convert to float if necessary
  hum_data = parseFloat(data.hum); // Convert to float if necessary

  // Update temperature gauge value and label
  temp_gauge.refresh(temp_data);
  document.getElementById("temp_value").innerHTML = temp_data;

  // Update humidity gauge value and label
  hum_gauge.refresh(hum_data);
  document.getElementById("hum_value").innerHTML = hum_data;

  // Update temperature chart data
  temperatureData.push(temp_data);
  var currentTime = new Date().toLocaleTimeString();
  timeLabels.push(currentTime);

  // Ensure only the last 10 temperature data points are shown on the chart
  if (temperatureData.length > 10) {
    temperatureData.shift();
    timeLabels.shift();
  }

  console.log("Updated temperatureData:", temperatureData);
  console.log("Updated timeLabels:", timeLabels);

  // Update the chart with the new data
  updateTemperatureChart();
};

  // Wait for the DOM to load completely before setting up the charts
 
    function button_1_on() {
        button_1_status = 1;
        console.log("LED 1 is ON");
        send_data();
    }

    function button_1_off() {
        button_1_status = 0;
        console.log("LED 1 is OFF");
        send_data();
    }

    function button_2_on() {
        button_2_status = 1;
        console.log("LED 2 is ON");
        send_data();
    }

    function button_2_off() {
        button_2_status = 0;
        console.log("LED 2 is OFF");
        send_data();
    }

    function send_data() {
        var full_data = '{"LED1":' + button_1_status + ',"LED2":' + button_2_status + '}';
        connection.send(full_data);
    }

    function handleSwitch1Change(checkbox) {
        if (checkbox.checked) {
            button_1_on();
        } else {
            button_1_off();
        }
    }

    function handleSwitch2Change(checkbox) {
        if (checkbox.checked) {
            button_2_on();
        } else {
            button_2_off();
        }
    }
</script>
</html>


)=====";

// ipaddress/led1/on
//ipaddress/led1/off

// ipaddress/led2/on
//ipaddress/led2/off
#include <ESPAsyncWebServer.h>

AsyncWebServer server(80); // server port 80
WebSocketsServer websockets(81);

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "Page Not found");
}


void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {

  switch (type) 
  {
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected!\n", num);
      break;
    case WStype_CONNECTED: {
        IPAddress ip = websockets.remoteIP(num);
        Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
      }
      break;
    case WStype_TEXT:
      Serial.printf("[%u] get Text: %s\n", num, payload);
      String message = String((char*)( payload));
      Serial.println(message);

      
     DynamicJsonDocument doc(200);
    // deserialize the data
    DeserializationError error = deserializeJson(doc, message);
    // parse the parameters we expect to receive (TO-DO: error handling)
      // Test if parsing succeeds.
  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return;
  }

  int LED1_status = doc["LED1"];
  int LED2_status = doc["LED2"];
  digitalWrite(LED1,LED1_status);
  digitalWrite(LED2,LED2_status);




  }
}
#include <FS.h> // Include the FS.h library to access SPIFFS

void setup(void)
{
  
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  dht.begin();
  
  WiFi.softAP("JjESP", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("ESP")) { //esp.local/
    Serial.println("MDNS responder started");
  }


  if (!SPIFFS.begin(true)) {
    Serial.println("An error occurred while mounting SPIFFS");
    return;
  }
  server.on("/", [](AsyncWebServerRequest * request)
  { 
   
  request->send_P(200, "text/html", webpage);
  });

   server.on("/led1/on", HTTP_GET, [](AsyncWebServerRequest * request)
  { 
    digitalWrite(LED1,HIGH);
  request->send_P(200, "text/html", webpage);
  });

  server.onNotFound(notFound);
  server.on("/", [](AsyncWebServerRequest *request)
  {
    // Serve the HTML page with the background image
    request->send(SPIFFS, "/index.html", "text/html");
  });
   server.on("/raphael-min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/raphael-min.js", "text/javascript");
    });

    server.on("/justgage.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/justgage.min.js", "text/javascript");
    });
    server.on("/Chart.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/Chart.js", "text/javascript");
    });
    server.on("/Chart.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/Chart.min.js", "text/javascript");
    });
  server.on("/bc.jpg", HTTP_GET, [](AsyncWebServerRequest *request) {
    request->send(SPIFFS, "/bc.jpg", "image/jpeg");
  });
  server.begin();  // it will start webserver
  websockets.begin();
  websockets.onEvent(webSocketEvent);
  timer.attach(2,send_sensor);

}


void loop(void)
{
 websockets.loop();
}

void send_sensor()
{
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  
    if (isnan(h) || isnan(t) ) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  // JSON_Data = {"temp":t,"hum":h}
  String JSON_Data = "{\"temp\":";
         JSON_Data += t;
         JSON_Data += ",\"hum\":";
         JSON_Data += h;
         JSON_Data += "}";
   Serial.println(JSON_Data);     
  websockets.broadcastTXT(JSON_Data);
}
