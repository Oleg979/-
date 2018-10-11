function SvgToPng(selector) {
  var html = document.querySelector(selector).parentNode.innerHTML; 
  var imgsrc = 'data:image/svg+xml;base64,'+ btoa(html); 
  document.body.appendChild(document.createElement("canvas")); 
  var canvas = document.querySelector("canvas"), 
  context = canvas.getContext("2d"); 
  canvas.setAttribute('width', 2* document.querySelector(selector).clientWidth); 
  canvas.setAttribute('height', 2*document.querySelector(selector).clientHeight); 
  var image = new Image; 
  image.src = imgsrc; 
  image.onload = function() { 
    context.drawImage(image, 0, 0); 
    var canvasdata = canvas.toDataURL("image/png"); 
    var a = document.createElement("a"); 
    a.id = "downloaddd"; 
    a.textContent = "save"; 
    a.download = "export_"+Date.now()+".png"; 
    a.href = canvasdata; 
    document.body.appendChild(a); 
    canvas.parentNode.removeChild(canvas); 
    a.click(); 
  }
};
