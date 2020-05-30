function insertAfter(referenceNode, newNode) {
  if (referenceNode.value !== 'opened') {
    referenceNode.parentNode.insertBefore(newNode, referenceNode.nextSibling);
    referenceNode.value = 'opened';
  }
}

function createResponseParagraph(Node, Message) {
  if (document.getElementById('popened')) {
    document.getElementById('popened').remove();
  } else {
    const p = document.createElement('p');
    p.id = 'popened';
    p.innerHTML = Message;
    const insertBeforeNode = Node.parentNode.parentNode.parentNode;
    insertBeforeNode.insertBefore(p, Node.parentNode.parentNode.nextSibling);
  }
}


function tdClick(clickedISBN) {
  const { id } = clickedISBN;
  const idSplitter = id.split('?');
  const ISBN = idSplitter[1];


  const xhr = new XMLHttpRequest();
  xhr.onreadystatechange = () => {
    if (xhr.readyState === 4 && xhr.status === 200) {
      const response = JSON.parse(xhr.responseText);


      const firstParent = clickedISBN.parentNode;
      const detailsTr = document.createElement('tr');
      const space = document.createElement('td');
      space.colSpan = '8';

      const contents = document.createElement('ul');
      const li = document.createElement('li');
      li.textContent = response;
      const li2 = document.createElement('li');
      li2.textContent = 'Click here to close the detail menu';

      li2.onclick = function () {
        detailsTr.remove();
        firstParent.value = '';
      };

      contents.appendChild(li);
      contents.appendChild(li2);
      space.appendChild(contents);

      detailsTr.appendChild(space);

      insertAfter(firstParent, detailsTr);
    }
  };

  xhr.open('POST', '/sendDetails');
  xhr.setRequestHeader('Content-Type', 'application/json');
  xhr.send(JSON.stringify({ ISBN }));
}

function deleteBook(clickedISBN) {
  const { id } = clickedISBN;
  const idSplitter = id.split('?');
  const ISBN = idSplitter[1];

  const firstParent = clickedISBN.parentNode;
  const secondParent = firstParent.parentNode;

  const xhr = new XMLHttpRequest();
  xhr.onreadystatechange = () => {
    if (xhr.readyState === 4 && xhr.status === 200) {
      const response = xhr.responseText;
      createResponseParagraph(secondParent, response);
      secondParent.remove();
    } else if (xhr.readyState === 4 && xhr.status === 401) {
      const errorResponse = xhr.responseText;
      createResponseParagraph(secondParent, errorResponse);
    }
  };

  xhr.open('POST', '/removeFromList');
  xhr.setRequestHeader('Content-Type', 'application/json');
  xhr.send(JSON.stringify({ ISBN }));
}
