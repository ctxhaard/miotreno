
var Pebble = require('./pebble');

Pebble.on('ready',function(){
    console.log('ready emitted');
});

//Pebble.emit('ready',Pebble);