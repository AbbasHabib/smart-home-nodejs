const express = require('express')
const net = require('net');
const app = express()
const port = 3000


const ESP_port = 5045
const ESP_ip = '192.168.1.50'


app.use(express.static('public'))
app.use('/css', express.static(__dirname + '/public/css'))


app.get('/', (req, res) => {
    console.log("someone requested the webpage!!")
    res.sendFile(__dirname + '/public/index.html')
})

app.post('/lamp/:lampNumber/:command', (req, res) => {

    console.log("MMMMMMM");
    var esp_node = new net.Socket();
    try{
        esp_node.connect( ESP_port, ESP_ip);
        esp_node.on('error', (err) => {
            console.log(err)
            console.log("err hanged")
        });
    }
    catch(err){
        res.status(400)
        console.log("couldn't connect to socket")
        return
    }
    esp_node.on('connect', function () {
        // writing data to server
        try{
            esp_node.write(String(req.params.lampNumber) + '#' + String(req.params.command) + '\n');
        }
        catch(err){
            console.log("no socket connection")
        }
    });

    esp_node.setEncoding('utf8');

    esp_node.on('data', function(data) {
        console.log('Received: ' + data);
        try{
        esp_node.destroy(); // kill esp_node after server's response
        }
        catch(err){
            console.log("couldn't destroy socket")
        }
    });
    
    esp_node.on('close', function() {
        console.log('Connection closed');
    });

    console.log("gottem")
    console.log(req.params.lampNumber + '=>' + req.params.command )
    res.status(200);
    res.setHeader('Cache-Control', 'no-cache, no-store, must-revalidate');
    res.setHeader('Pragma', 'no-cache');
    res.setHeader('Expires', '0');
    res.json({data:"lol"});
})


app.listen(port, () => { console.log("started on port: " + port) })
