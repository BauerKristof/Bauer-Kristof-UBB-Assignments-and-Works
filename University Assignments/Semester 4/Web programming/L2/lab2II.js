let numberOfLifes = 3;
let listOfBoxes = [];
let listOfLines = [];

const listOfColors = ['red', 'blue', 'green', 'violet', 'purple', 
                     'yellow', 'orange', 'pink', 'lime', 'brown'];

const moveTo = [[500,250], [450,100], [400,300], [200,100], [250,50],
               [200,150], [250,350], [300,340], [365,50], [200,200]];

const lineTo = [[250,180], [200,300], [400,100], [500,200],
             [450,280], [550,150], [500,125], [425,75], [385,350], [550,175]];

const canvas = document.getElementById('canvas');

function addListener() {
   canvas.addEventListener('click', event => {

   const x = event.pageX - canvas.offsetLeft;
   const y = event.pageY - canvas.offsetTop;
      
   if ((x >= 700) && (x <= 730)) {
      checkMelyikBox(y);
   }
   
   if ((x >= 500) && (x <= 600) && (y >= 400) && (y <= 450)) {
      restartGame();
      }
   });
}

function checkMelyikBox(y) {
   if ((y >= 50) && (y <= 65)) {
      checkMatching(listOfBoxes[0],0);
   } else if ((y >= 80) && (y <= 95)) {
      checkMatching(listOfBoxes[1],1);
   } else if ((y >= 110) && (y <= 125)) {
      checkMatching(listOfBoxes[2],2);
   } else if ((y >= 140) && (y <= 155)) {
      checkMatching(listOfBoxes[3],3);
   } else if ((y >= 170) && (y <= 185)) {
      checkMatching(listOfBoxes[4],4);
   } else if ((y >= 200) && (y <= 215)) {
      checkMatching(listOfBoxes[5],5);
   } else if ((y >= 230) && (y <= 245)) {
      checkMatching(listOfBoxes[6],6);
   } else if ((y >= 260) && (y <= 275)) {
      checkMatching(listOfBoxes[7],7);
   } else if ((y >= 290) && (y <= 305)) {
      checkMatching(listOfBoxes[8],8);
   } else if ((y >= 320) && (y <= 335)) {
      checkMatching(listOfBoxes[9],9);
   }
}

function checkMatching(clickedColor,deleteBoxIndex) {
   let i = 0;
   let n = listOfLines.length;

   for(i = 0; i < n; i++) {
      const  lineColor=listOfLines[i][0];
      const  orderOfLine=listOfLines[i][1];//megkeresni az objListaban az x szinu(fgvparamater) jatekost, megkapjuk a sorszamat

      if ((lineColor == clickedColor) && ((10-n) === orderOfLine)) {
            listOfLines.splice(i,1);
            listOfBoxes.splice(deleteBoxIndex,1);
            clearCanvas();
            redrawLines();
            redrawBoxes();
            initalizeLives();
            initializeRestart();
            break;
      }
   }

   if (i === n) {
      if (numberOfLifes === 1) {
         repeatRequest();
      } else {
         numberOfLifes -= 1;
         clearCanvas();
         redrawLines();
         redrawBoxes();
         initalizeLives();
         initializeRestart();
         }
      }
}

function clearCanvas() {
   const context = canvas.getContext('2d');
   context.clearRect(0, 0, canvas.width, canvas.height);
 }

function initializeLines() {
    let copyColors = listOfColors.slice();
    let orderNumber = 0;

    while(orderNumber < 10) {
    const pickedColor = copyColors.splice( Math.floor(Math.random()*copyColors.length), 1 );
    listOfLines.push([pickedColor[0],9-orderNumber]);
    orderNumber++;
    }

    const context = canvas.getContext('2d');
    if (canvas.getContext) {
        let i;
        
        for(i = 0; i < 10;i++) {
            context.beginPath();
            const currentColor = listOfLines[i][0];
            context.moveTo(moveTo[i][0], moveTo[i][1]);
            context.lineTo(lineTo[i][0], lineTo[i][1]);
            context.lineWidth = 5;
            context.strokeStyle = currentColor;
            context.stroke();
            context.closePath();
        }
   } else {
      console.log('Hiba');
   }
}

function initializeBoxes() {   
    let startPos = 50;
    let copyColor = listOfColors.slice();
    let orderNumber = 0;

    const context = canvas.getContext('2d');

    while(orderNumber < 10) {
      const pickedColor = copyColor.splice( Math.floor(Math.random()*copyColor.length), 1 );
      listOfBoxes.push(pickedColor);
      context.beginPath();
      context.fillStyle = pickedColor;
      context.fillRect(700, startPos, 30, 15);
      context.stroke();
      context.closePath();
      startPos += 30;
      orderNumber++;
    }
}

function redrawLines() {
   const context = canvas.getContext('2d');

   const n = listOfLines.length;

   if (canvas.getContext) {
        let i;
        for(i = 0; i < n; i++) {
            context.beginPath();
            const currentColor = listOfLines[i][0];
            context.moveTo(moveTo[i][0], moveTo[i][1]);
            context.lineTo(lineTo[i][0], lineTo[i][1]);
            context.lineWidth = 5;
            context.strokeStyle = currentColor;
            context.stroke();
            context.closePath();
        }
   } else {
        console.log('Hiba');
   }
}

function redrawBoxes() {
    let startPos = 50;
    let orderNumber = 0;
    const n =listOfBoxes.length;

    const context = canvas.getContext('2d');

    while(orderNumber < n) {      
      context.beginPath();
      context.fillStyle = listOfBoxes[orderNumber];
      context.fillRect(700, startPos, 30, 15);
      context.stroke();
      context.closePath();
      startPos += 30;
      orderNumber++;
    }
}

function initalizeLives() {
      const context = canvas.getContext('2d');
      context.font = '30px Arial';
      context.fillStyle ='grey';
      let curLife = `Current lives: ${numberOfLifes}`;
      context.fillText(curLife,10,450);
}

function repeatRequest() {
      clearCanvas();
      initializeRestart();
      const context = canvas.getContext('2d');

      context.beginPath();
      context.font = '28px Arial';
      context.fillStyle ='red';
      context.fillText('Vesztettel, kattints az ismetles gombra a jatek ismetleseert', 5, 250);
      context.closePath();
}

function initializeRestart() {
   const context = canvas.getContext('2d');
   context.beginPath();
   context.fillStyle = 'green';
   context.fillRect(500, 400, 100, 50);
   context.stroke();
   context.closePath();

   context.beginPath();
   context.font = '22px Arial';
   context.fillStyle ='black';
   context.fillText('Ismetles', 508, 430);
   context.closePath();
}

function restartGame() {
   clearCanvas();
   numberOfLifes=3;   
   listOfBoxes = [];
   listOfLines = []; 
   initializeLines();
   initializeBoxes();
   initalizeLives();
   initializeRestart();
}

function startGame() {
   initializeLines();
   initializeBoxes();
   initalizeLives();
   initializeRestart();
   addListener();
}