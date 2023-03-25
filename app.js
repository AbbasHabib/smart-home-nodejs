const express = require('express')
const app = express()
const port = 3000

app.use(express.static('public'))
app.use('/css', express.static(__dirname + '/public/css'))


app.get('/', (req, res) =>{
    res.sendFile(__dirname + '/public/index.html')
})

app.post('/lamp/:lampNumber', (req, res) =>{
    console.log("gottem")
    console.log(req.params.lampNumber)
    res.status(200)
})


app.listen(port ,()=>{console.log("started on port: " + port)})
