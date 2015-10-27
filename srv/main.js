#!/usr/bin/env node --harmony

"use strict"


const express = require('express'),  
    app = express(),
    http = require('http').Server(app);
 

app.use(express.static('public/images/'));
app.use(express.static('public/javascripts/'));
app.use(express.static('views/'));

http.listen(80,function(){
    console.log('listening on *:80');
});

