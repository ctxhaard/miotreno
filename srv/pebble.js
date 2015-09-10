
var events = require('events').EventEmitter;
var util = require('util');

function Pebble()
{
    var self = this;
    events.EventEmitter.call(self);
}

util.inherits(Pebble,events.EventEmitter);

var obj = new Pebble();
var oldFunc = obj.on;
obj.on = function(eventName,eventHandler){
    var self = this;
    oldFunc.call(self,eventName,eventHandler);
    //console.log('obj.prototype: ' + obj.prototype);
    obj.prototype.on.call(self,eventName,eventHandler);
    if('ready' == eventName){
        self.emit('ready',self);
    }
}

module.exports = obj;