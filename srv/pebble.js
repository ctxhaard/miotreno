
var events = require('events').EventEmitter;
var util = require('util');

function Pebble()
{
}

Pebble.prototype.addEventListener = function(eventName,eventHandler){
	if('ready' == eventName){
		eventHandler();
	}
};

Pebble.prototype.getTimelineToken = function(doneFunction,errorFunction){
	doneFunction('SBYM2GEc9fmjY2L25Bsh2tFf3rOwRJ08');
};

module.exports = new Pebble();