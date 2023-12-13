const express = require('express')
const { SerialPort } = require('serialport')
const app = express()
app.use(express.static('public'))
const port = 3000
var serialPort = new SerialPort({
    path: 'COM6',
    baudRate : 9600
})

var serialData = [0,0]

// Read from serial
serialPort.on('data', (data) => {
    serialData[0] = +data.toString().split(',')[0]
    serialData[1] = +data.toString().split(',')[1]
})

// Express events

app.get("/data", (req,res) => {
    res.setHeader('Content-Type', 'text/event-stream');
    res.setHeader('Cache-Control', 'no-cache');
    res.setHeader('Connection', 'keep-alive');
    res.send(serialData.toString())
})

app.listen(port, () => {
    console.log('Viewer is ready!')
})