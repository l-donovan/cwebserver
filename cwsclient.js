const ADDR = 'http://localhost:1928';

let req = new XMLHttpRequest();
req.open('GET', ADDR);
req.onreadystatechange = () => {
    if(req.readyState === 4 && req.status > 199 && req.status < 300) {
        console.log(req.responseText);
    }
};
req.send();
