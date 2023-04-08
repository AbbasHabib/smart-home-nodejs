# SMART HOME SYSTEM USING NODE JS

### system diagram
![system_diag](./readme_imgs/sys_diag.png)

## What to modify

### in the ESP source code (main.cpp)
```c++
// your home wifi network SSID
const char* ssid = "smartHome";
// Wifi network password
const char* password = "12345678";
// ESP listens on this port
const uint16_t socketNo = 5045;
```
### apply changes in app.js
```js
const ESP_port = 5045
const ESP_ip = '192.168.1.50'
```
### modify the server ip in static html page
```html
<script>
        const serverIp = '192.168.1.5'
</script>
```

# Start the server with following command 
```bash
# at src/webserver/
$ node app.js
```
