ESP8266WebServer
======
* ESP8266WebServer是基于ESP8266开发板的演示代码，平台是Arduino，根据ESP8266示例代码HelloServer改变，使用了HTML异步控制引脚，异步获取模拟量数据显示在居于Highcharts的图表上，供参考学习。

****
## 文件目录表
HelloServer
> HelloServer.ino

HTML
> asd.html (Button)
> index.html (Highcharts)

## 运行代码
1. 配置好ESP8266 for Arduino 的环境
2. 打开HelloServer.ino文件，进入Arduino IDE
3. 修改宏定义中的 SSID（wifi名）和 Password（WiFi密码）
4. 烧写进ESP8266，打开串口监视器，获得IP，使用IP访问网站（直接使用IP，不用http://）