
var _timelineToken;
const VERBOSE_LOG = 0; // truthy: a verbose log is printed on the console
const PUSH_PIN = 0; // truthy: the PIN is actually pushed on the Pebble Timeline

Date.prototype.myToString = function(){
  var pad = function (str, max) {
    str = str.toString();
    return str.length < max ? pad("0" + str, max) : str;
  };
  return this.getHours() + ":" + pad(this.getMinutes(),2);
};

var _TRAINS = [{
  codPartenza: 'S03317', // trieste
  codTreno: '2216', // 17:55
  codStazione: 'S02670' // quarto d'altino
},{
  codPartenza: 'S03200', // portogruaro
  codTreno: '10046', // 18:17
  codStazione: 'S02670' // quarto d'altino
}];
var _trains;

Pebble.addEventListener('ready',function(){
  console.log('ready!');
  _trains = _TRAINS.slice();
  pinNextTrain(_trains);
});

function pinNextTrain(trains){
  var train = trains.pop();
  if(train){
    getTrainStatus(train.codPartenza,train.codTreno,train.codStazione);  
  }
}

function getTrainStatus(codPartenza,numeroTreno,codStazione){
  var URL_VIAGGIATRENO = 'http://www.viaggiatreno.it/viaggiatrenonew/resteasy/viaggiatreno/andamentoTreno';

  var request = new XMLHttpRequest();
  var url = URL_VIAGGIATRENO + '/'+ codPartenza +'/' + numeroTreno;
  request.open('GET',url,true);
  request.onload = function(e){
    console.log('...viaggiatreno data acquired');
    var trainStatus = JSON.parse(this.responseText);
    VERBOSE_LOG && console.log(this.responseText);
    var fermata;
    for(var idx = 0; idx < trainStatus.fermate.length; ++idx){
      fermata = trainStatus.fermate[idx];
      if(fermata.id == codStazione){
        break;
      }
    }
    if(!fermata){
      console.log('fermata non disponibile');
      pinNextTrain(_trains);
    } else {
      var partenzaPrevista = new Date(fermata.partenza_teorica);
      var title = fermata.stazione;
      var subtitle = "non ancora partito";

      var ritardoText = trainStatus.compRitardo[0];
      if(ritardoText){
        title = title + " (" + ritardoText + ")";

        var partenzaReale = new Date(fermata.partenzaReale);
        subtitle = " previsto: " + partenzaReale.myToString();      
      }
      var pin = {
        "id": fermata.stazione + "-" + partenzaPrevista.toISOString(),
        "time": partenzaPrevista.toISOString(),
        "createNotification": {
          "layout": {
            "type": "genericNotification",
            "title": title,
            "tinyIcon": "system://images/NOTIFICATION_FLAG",
            "body": subtitle
          }
        },
        "updateNotification": {
          "time": new Date().toISOString(),
          "layout": {
            "type": "genericNotification",
            "tinyIcon": "system://images/NOTIFICATION_FLAG",
            "title": title,
            "body": subtitle
          }
        },
        "layout": {
          "type": "genericPin",
          "title": title,
          "subtitle": subtitle
        }
      };

      VERBOSE_LOG && console.log(JSON.stringify(pin));
      if(!_timelineToken){
        Pebble.getTimelineToken(
          function(token){
            _timelineToken = token;
            VERBOSE_LOG && console.log('my timeline token is: ' + token);
            PUSH_PIN && pushTimelinePin(pin,_timelineToken);
            pinNextTrain(_trains);
          },function(error){
            console.log('error: ' + error + 'getting timeline token');
          });    
      }
      else{
        PUSH_PIN && pushTimelinePin(pin,_timelineToken);
        pinNextTrain(_trains);
      }

    }
  };
  console.log('getting viaggiatreno data from ' + url + ' ...');
  request.send();
}

function pushTimelinePin(pin,token){ 
    var url = 'https://timeline-api.getpebble.com/v1/user/pins/' + pin.id;

    var request = new XMLHttpRequest();
    request.onload = function(e){
    VERBOSE_LOG && console.log(request.responseText);
};
  request.open('PUT',url,true); // new or updated pin
  request.setRequestHeader('Content-Type','application/json');
  request.setRequestHeader('X-User-Token',token);
  console.log('pushing timeline pin');
  request.send(JSON.stringify(pin));
}
