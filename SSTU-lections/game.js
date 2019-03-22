let canvas = document.querySelector("#canvas")
let ctx = canvas.getContext("2d")
ctx.fillStyle = "green"
ctx.fillRect(10, 10, 100, 100)
ctx.clearRect(20, 20, 50, 100)
canvas.width = 400
canvas.height = 300
ctx.fillStyle = "black"

let coords = {
	x1: 50,
  y1: 260,
  x2: 10,
  y2: 40
}

let blocks = []
const createBlocks = () => {
	blocks.push([300, 10])
}



const renderCar = ({x1, y1, x2, y2}) => {
ctx.clearRect(0, 0, canvas.width, canvas.height);
ctx.fillRect(x1, y1, x2, y2)
ctx.fillRect(x1 + 10, y1 + 10, x2 - 6, y2 - 30 )
ctx.fillRect(x1 - 4, y1 + 10, x2 - 6, y2 - 30)
ctx.fillRect(x1 + 10, y1 + 30, x2 - 6, y2 - 30)
ctx.fillRect(x1 - 4, y1 + 30, x2 - 6, y2 - 30)

}

document.onkeydown = e => {
	const code = e.keyCode
  switch(code) {
  	case 37:
    coords = {...coords, x1: coords.x1 - 5}
    break;
    case 38:
    coords = {...coords, y1: coords.y1 - 5}
    break;
    case 39:
    coords = {...coords, x1: coords.x1 + 5 }
    break;
    case 40:
    coords = {...coords, y1: coords.y1 + 5 }
    break;
  }
}


setInterval(() => renderCar(coords), 1);
