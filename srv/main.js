// load a mock Pebble object
var Pebble = require('./pebble');
// library to use XMLHttpRequest in node
var XMLHttpRequest = require('xmlhttprequest').XMLHttpRequest;
// 'include' of app.js to share codebase with Pebble App
var fs = require('fs');
eval(fs.readFileSync('../src/app.js') + '');
