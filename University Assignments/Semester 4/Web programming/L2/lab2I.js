  function validateWeb(input) {
      const errorMessage = document.getElementById('errorWebMsg');

      if (input.match(/([a-zA-Z0-9\_\-]+\.)*[a-zA-z0-9\_\-]+\.[a-z]/) === null) {
            errorMessage.className = 'errorStateMsg';
            return false;        
      } else {
                errorMessage.className = 'normalStateMsg';
                return true;
      }    
}

function validateEmail(input) {
    const errorMessage = document.getElementById('errorEmailMsg');

    if(input.length <= 10) { //Magyarazat:mivel a @gmail.com es a @yahoo.com is 10 karakter, igy ha ez a minimalis feltetel nincs meg mar biztos nem jo
      errorMessage.className = 'errorStateMsg';
      return false; 
    } else {
        let i = 0;

        for (i = 0; i < input.length; i++) {
          let oneCharacter = input.charAt(i);
          if (oneCharacter === '@') {
              break;
          }
        }

        const remainingStr = input.substring(i + 1,input.length)

        if ((remainingStr === 'gmail.com') || (remainingStr === 'yahoo.com')) {
          errorMessage.className = 'normalStateMsg';
          return true;   
        } else {
          errorMessage.className = 'errorStateMsg';
          return false; 
        }
    }
}

function checkValid() {
    const webLink = document.getElementById('favWeb').value;
    const emailAdr = document.getElementById('emailAdress').value;
    const usrName = document.getElementById('userName');
    const typedDate = document.getElementById('birthDate');
    const validateMsg = document.getElementById('validateMessage');
    const validName = usrName.checkValidity();
    const validDate = typedDate.checkValidity();
    const submitButton = document.getElementById('submitButton');

    if (validateEmail(emailAdr) && validateWeb(webLink) && validDate && validName) {
      validateMsg.innerText = 
      'Az osszes adat helyes, mostmar submittolhatod oket';
      validateMsg.style.color ='green';
      submitButton.disabled = false;
    } else {
      validateMsg.style.color = 'red';
      validateMsg.innerText = 
      'Az adatok hibasak, nezd at oket, utana submittolhatod';
    }
}
  
function setFooter() {
    const modifyMessage = `Utolso modositasi datuma:  ${document.lastModified}`;
    const footerElement = document.getElementById('modifyFooter');
    footerElement.innerText = modifyMessage;
    footerElement.style.textAlign = 'center';
}
  