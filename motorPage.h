R"(
<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0, maximum-scale=1.0, user-scalable=no" />
    <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css">
  </head>
  <body>
  <style>
   #rotateMode{
  border-radius: 50%;
   width: 300px;
  height: 200px;
  z-index: 15;
  background-color: gray;
  margin: -100px 0 0 -150px;
  color:white;
   top: 50%;
  left: 50%;
  position:absolute;
 
}

.btn-group-sm>.btn, .btn-sm {
    padding: 5
px
 10
px
;
    font-size: 58px;
    line-height: 1.5;
    border-radius: 3
px
;
}

#left{
	position:absolute;
  top:50%;
  left:20px;
  transform:translateY(-50%);
}

#right{
 position:absolute;
  top:50%;
  right:20px;
  transform:translateY(-50%);
}

#drive{
	 position:absolute;
  top:0px;
  left:50%;
  transform:translateX(-50%);
}

#back{
	position:absolute;
  bottom:0px;
  left:50%;
  transform:translateX(-50%);
}
</style>
   <div class ="circleBase" id="rotateMode">   
            <button id="drive" class="btn btn-default btn-sm" onmousedown='makeAjaxCall("forward")' onmouseup='makeAjaxCall("driveStop")' ontouchstart='makeAjaxCall("forward")' ontouchend='makeAjaxCall("driveStop")'><span class="glyphicon glyphicon-arrow-up"></span></button>

       
            <button id="left"  class="btn btn-default btn-sm" onmousedown='makeAjaxCall("left")' onmouseup='makeAjaxCall("steerStop")' ontouchstart='makeAjaxCall("left")' ontouchend='makeAjaxCall("steerStop")'><span class="glyphicon glyphicon-arrow-left"></span></button>
         
            <button id="right" class="btn btn-default btn-sm" onmousedown='makeAjaxCall("right")' onmouseup='makeAjaxCall("steerStop")' ontouchstart='makeAjaxCall("right")' ontouchend='makeAjaxCall("steerStop")'><span class="glyphicon glyphicon-arrow-right"></span></button>
       
            <button id="back" class="btn btn-default btn-sm" onmousedown='makeAjaxCall("back")' onmouseup='makeAjaxCall("driveStop")' ontouchstart='makeAjaxCall("back")' ontouchend='makeAjaxCall("driveStop")'><span class="glyphicon glyphicon-arrow-down"></span></button>
			</div>

    <script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>
    <script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.7/js/bootstrap.min.js"></script>
    <script> 
      function makeAjaxCall(url){
        $.ajax({"url": url});
      }
    </script>
    <script>
      let gamepadIndex;
      window.addEventListener('gamepadconnected', (event) => {
        gamepadIndex = event.gamepad.index;
        startGamepad(gamepadIndex);
      });

      var lastSteer = 0;
      var lastDrive = 0;

      function sendDrive(value){
        if(value == lastDrive){
          return;
        }

        lastDrive = value;

        if(value == 0){
          makeAjaxCall("driveStop");
        }
        else if(value == 1){
          makeAjaxCall("forward");
        }
        else if(value == -1){
          makeAjaxCall("back");
        }
      }
      function sendSteer(value){
        if(value == lastSteer){
          return;
        }

        lastSteer = value;
        
        if(value == 0){
          makeAjaxCall("steerStop");
        }
        else if(value == 1){
          makeAjaxCall("right");
        }
        else if(value == -1){
          makeAjaxCall("left");
        }
      }

      function startGamepad(gamepadIndex){
        setInterval(() =>{
          if(gamepadIndex !== undefined){
            const myGamepad = navigator.getGamepads()[gamepadIndex];

            if(myGamepad.buttons[5].pressed){
              sendDrive(1);
            }
            else if(myGamepad.buttons[4].pressed){
              sendDrive(-1);
            }
            else{
              sendDrive(0);
            }

            if(myGamepad.buttons[14].pressed){
              sendSteer(-1);
            }
            else if(myGamepad.buttons[15].pressed){
              sendSteer(1);
            }
            else{
              sendSteer(0);
            }
          }
        }, 10);
      }
    </script>
    <script>
       document.addEventListener('keydown', function(event) {
          if(event.keyCode == 37) {
              //Left Arrow
              makeAjaxCall("left");            
          }
          else if(event.keyCode == 39) {
              //Right Arrow
              makeAjaxCall("right");   
          } else if(event.keyCode == 38) {
              //Up Arrow
              makeAjaxCall("forward");   
          } else if(event.keyCode == 40) {
              //Down Arrow
              makeAjaxCall("back");   
          }
      });

      document.addEventListener('keyup', function(event) {
          if(event.keyCode == 37 ||event.keyCode == 39 ) {
              //Left or Right Arrow
              makeAjaxCall("steerStop");            
          }
          else if(event.keyCode == 38 ||event.keyCode == 40 ) {
              //Up or Down Arrow
              makeAjaxCall("driveStop");            
          }
      });
    </script>
  </body>
</html>
)"