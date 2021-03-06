
Pebble.addEventListener('ready',function(){
  console.log('ready!');
  Pebble.sendAppMessage({ KEY_JS_READY: true });

  Pebble.addEventListener('appmessage', function(e) {

    var trainID = e.payload;
    getTrainStatus(trainID,function(trainStatus){
      if(trainStatus) {
        console.log('got train status: ' + trainStatus.KEY_COD_STATUS);
        Pebble.sendAppMessage(trainStatus);
      }
      else {
        console.log('error getting train status');
        Pebble.sendAppMessage({ KEY_COD_STATUS: "error" });
      }
    });
  });
});

Pebble.addEventListener("showConfiguration",function(e){
  
    console.log('showConfiguration!');
    Pebble.openURL('https://powerful-plains-8811.herokuapp.com/');
});

function getTrainStatus(trainID,callback){
  var URL_VIAGGIATRENO = 'http://www.viaggiatreno.it/viaggiatrenonew/resteasy/viaggiatreno/andamentoTreno';

  var request = new XMLHttpRequest();
  var url = URL_VIAGGIATRENO + '/'+ trainID.KEY_COD_PARTENZA +'/' + trainID.KEY_COD_TRENO;
  console.log('GET ' + url);
  request.open('GET',url,true);
  request.onload = function(e){
    console.log('...viaggiatreno data acquired');
    console.log(this.responseText);
    var trainStatus = JSON.parse(this.responseText);
    var result = { KEY_COD_STATUS: trainStatus.compRitardo[0], KEY_COD_LAST_STATION: "non partito" };
    if(trainStatus.stazioneUltimoRilevamento) {      
        result.KEY_COD_LAST_STATION = trainStatus.stazioneUltimoRilevamento;
    }
//    console.log("result: " + JSON.stringify(result));
    callback(result);
  };
  request.send();
}
