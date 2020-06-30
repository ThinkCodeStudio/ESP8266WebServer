#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "CU_CZ9C"          //WIFI SSID
#define STAPSK  "a0v204n8"   //WIFI password
#endif
#define LED LED_BUILTIN
#define PIN_LIGHT1 D4
#define PIN_DATA1 A0
#define PIN_LIGHT2 D3
#define PIN_LIGHT3 D2
#define PIN_LIGHT4 D1


const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer server(80);  //server端口号

String html1 = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\"content=\"width=device-width, initial-scale=1.0\"><meta http-equiv=\"X-UA-Compatible\"content=\"ie=edge\"><script>function local(pin,staut){var xmlhttp=new XMLHttpRequest();xmlhttp.open(\"GET\",\"/pin?pin=\"+pin+\"&light=\"+staut,true);xmlhttp.send()}</script><title>Welcome ESP8266 for Light</title></head><body><div><a href=\"#\"onclick=\"local(1,'on')\"><input type=\"button\"value=\"CLOSE\"style=\"font-size: 24px; padding: 10px; margin: 20px;\"></a><a href=\"#\"onclick=\"local(1,'off')\"><input type=\"button\"value=\"OPEN\"style=\"font-size: 24px; padding: 10px; margin: 20px; float: right;\"></a></div><div><a href=\"#\"onclick=\"local(2,'off')\"><input type=\"button\"value=\"OPEN\"style=\"font-size: 24px; padding: 10px; margin: 20px; float: right;\"></a><a href=\"#\"onclick=\"local(2,'on')\"><input type=\"button\"value=\"CLOSE\"style=\"font-size: 24px; padding: 10px; margin: 20px;\"></a></div><div><a href=\"#\"onclick=\"local(3,'off')\"><input type=\"button\"value=\"OPEN\"style=\"font-size: 24px; padding: 10px; margin: 20px; float: right;\"></a><a href=\"#\"onclick=\"local(3,'on')\"><input type=\"button\"value=\"CLOSE\"style=\"font-size: 24px; padding: 10px; margin: 20px;\"></a></div><div><a href=\"#\"onclick=\"local(4,'off')\"><input type=\"button\"value=\"OPEN\"style=\"font-size: 24px; padding: 10px; margin: 20px; float: right;\"></a><a href=\"#\"onclick=\"local(4,'on')\"><input type=\"button\"value=\"CLOSE\"style=\"font-size: 24px; padding: 10px; margin: 20px;\"></a></div></body></html>";
String html2 = "<html><head><meta charset=\"UTF-8\"/><title>ESP8266 DATA Show</title><script src=\"https://apps.bdimg.com/libs/jquery/2.1.4/jquery.min.js\"></script><script src=\"https://code.highcharts.com/highcharts.js\"></script></head><body><div id=\"container\"style=\"width: 550px; height: 400px; margin: 0 auto\"></div><script language=\"JavaScript\">$(document).ready(function(){var speel=5000;var chart={type:'spline',animation:Highcharts.svg,marginRight:10,events:{load:function(){var series=this.series[0];setInterval(function(){$.ajax({type:\"get\",url:\"http://192.168.18.10/data\",async:true,dataType:\"json\",success:function(reslut){myupdate(reslut)},error:function(errorMsg){myupdate(404)}})},speel);function myupdate(y){var x=(new Date()).getTime();series.addPoint([x,y],true,true)}}}};var title={text:'Light data'};var xAxis={type:'datetime',tickPixelInterval:150};var yAxis={title:{text:'Value'},plotLines:[{value:0,width:1,color:'#808080'}]};var tooltip={formatter:function(){return'<b>'+this.series.name+'</b><br/>'+Highcharts.dateFormat('%Y-%m-%d %H:%M:%S',this.x)+'<br/>'+Highcharts.numberFormat(this.y,2)}};var plotOptions={area:{pointStart:1940,marker:{enabled:false,symbol:'circle',radius:2,states:{hover:{enabled:true}}}}};var legend={enabled:false};var exporting={enabled:false};var series=[{name:'light value',data:(function(){var data=[],time=(new Date()).getTime(),i;for(i=-19;i<=0;i+=1){data.push({x:time+i*speel,y:Math.random()*20000})}return data}())}];var json={};json.chart=chart;json.title=title;json.tooltip=tooltip;json.xAxis=xAxis;json.yAxis=yAxis;json.legend=legend;json.exporting=exporting;json.series=series;json.plotOptions=plotOptions;Highcharts.setOptions({global:{useUTC:false}});$('#container').highcharts(json)});</script></body></html>";



//-----------控制light fun------//
void pin() {
  String data = server.arg("pin");
  switch(data[0]) {
    case '1':
      controller(PIN_LIGHT1);break;
    case '2':
      controller(PIN_LIGHT2);break;
    case '3':
      controller(PIN_LIGHT3);break;
    case '4':
      controller(PIN_LIGHT4);break;
  }
}
void controller(int Pin){
  String json = "{\"mag\":\"OK\"}";
  if (server.arg("light") == "on") {
//    myservo.write(servoon);
    server.send(200, "text/plain", json);

    digitalWrite(Pin,HIGH);
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW); 
  }
  else if (server.arg("light") == "off") {
//    myservo.write(servooff);
    server.send(200, "text/json", json);

    digitalWrite(Pin,LOW);
    digitalWrite(LED,HIGH);
    delay(500);
    digitalWrite(LED,LOW); 
  }
}


//----------data API-----------//
void data(){
  String json = "";
  int value = analogRead(PIN_DATA1);
  int data = map(value, 0, 1024, 0, 20000);
  json = String(data);
  server.send(200,"text/plain",json);
}

//--------返回html文件-----------//
void handleRoot() {
  responseHtml(html1);
}
void dataRoot() {
  responseHtml(html2);
}

void responseHtml(String html){
  digitalWrite(LED,LOW);
  server.send(200, "text/html", html);
  digitalWrite(LED,HIGH);
}


//----------响应信息--------------//
void handleNotFound() {
//  myservo.write(servooff);
//  digitalWrite(PIN_LIGHT,LOW);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
//  digitalWrite(PIN_LIGHT,HIGH);
}

void setup(void) {
//------------初始化------------//  

  pinMode(PIN_LIGHT1, OUTPUT);
  pinMode(PIN_LIGHT2, OUTPUT);
  pinMode(PIN_LIGHT3, OUTPUT);
  pinMode(PIN_LIGHT4, OUTPUT);
  
  pinMode(PIN_DATA1, INPUT);
  pinMode(LED,OUTPUT);
//  myservo.attach(D4);
//  myservo.write(servoon);
  Serial.begin(115200);
  
//-----------WIFI模式-------------
  WiFi.mode(WIFI_STA);
//  IPAddress ip(192, 168, 128, 1);
//  IPAddress ip2(192, 168, 128, 1);
//  IPAddress su(255, 255, 255, 0);
//  WiFi.softAPConfig(ip, ip2, su);
  WiFi.begin(ssid, password);
//  WiFi.softAP(ssid,password);
 
  Serial.println(WiFi.softAPIP());
  Serial.println("");

//------------检查连接----------------
  while (WiFi.status() != WL_CONNECTED) {
//    break;
    delay(200);
    Serial.print(".");
    digitalWrite(LED, HIGH);
    delay(200);
    Serial.print(".");
    digitalWrite(LED, LOW);
  }
  //WIFI connection 
  digitalWrite(LED, LOW);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
///******************************************///

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }

//-------------路由------------------
  server.on("/", handleRoot);        //主页
  server.on("/value", dataRoot);      //曲线图 
  server.on("/pin", HTTP_GET, pin);  //控制
  server.on("/data", HTTP_GET, data);//模拟量数据
 
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  
//-------------响应-----------------
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void) {
  server.handleClient();
  MDNS.update();
}
