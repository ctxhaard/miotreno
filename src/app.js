
Pebble.addEventListener('ready',function(){
  console.log('ready!');

  Pebble.addEventListener('appmessage', function(e) {
    console.log('AppMessage received!');
    // TODO: chiamare solo una volta!
    var trainID = e.payload;
    getTrainStatus(trainID,function(trainStatus){
      if(trainStatus) {
        Pebble.sendAppMessage(trainStatus);
      }
      else {
        Pebble.sendAppMessage({ .KEY_COD_STATUS: "error" });
      }
    });
  });
});

function getTrainStatus(trainID,callback){
  var URL_VIAGGIATRENO = 'http://www.viaggiatreno.it/viaggiatrenonew/resteasy/viaggiatreno/andamentoTreno';

  var request = new XMLHttpRequest();
  var url = URL_VIAGGIATRENO + '/'+ trainID.KEY_COD_PARTENZA +'/' + trainID.KEY_COD_TRENO;
  request.open('GET',url,true);
  request.onload = function(e){
    console.log('...viaggiatreno data acquired');
    var trainStatus = JSON.parse(this.responseText);
    var fermata;
    for(var idx = 0; idx < trainStatus.fermate.length; ++idx){
        fermata = trainStatus.fermate[idx];
        if(fermata.id == trainID.KEY_COD_STAZIONE){
          break;
      }
  }
  var trainStatus = null;
  if(!fermata){
      console.log('fermata non disponibile');
  }
  else{
    trainStatus = {};
    trainStatus.KEY_COD_STATUS = "non ancora partito";
    if(fermata.partenzaReale){
      trainStatus.KEY_COD_STATUS = fermata.ritardoPartenza;
  }
  callback(trainStatus);
}
